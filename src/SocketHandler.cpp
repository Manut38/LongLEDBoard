#include "SocketHandler.h"

void SocketHandler::handleMessage(String msg)
{
#ifdef DEBUG_SOCKET_MSGS
    Serial.println(msg);
#endif
    JsonDocument doc;
    DeserializationError error = deserializeJson(doc, msg);
    if (error != DeserializationError::Ok)
    {
        Serial.println("DeserializationError");
    }

    JsonObject effectConfig = doc["effectConfig"];
    if (!effectConfig.isNull())
        handleEffectConfig(effectConfig);

    JsonObject boardState = doc["state"];
    if (!boardState.isNull())
        handleBoardState(boardState);
}

void SocketHandler::handleEffectConfig(JsonObject effectConfig)
{
    JsonObject bgEffect = effectConfig["bgEffect"];
    if (!bgEffect.isNull())
    {
        if (!bgEffect["solidColor"].isNull())
        {
            String color = bgEffect["solidColor"]["color"];
            led->setBgEffect(new EffectSolidColor(LED::colorFromHexString(color)));
        }
        if (!bgEffect["rainbow"].isNull())
        {
            int16_t duration = bgEffect["rainbow"]["duration"];
            led->setBgEffect(new EffectRainbowLoop(duration));
        }
    }
}

void SocketHandler::handleBoardState(JsonObject state)
{
    if (!state["globalBrightness"].isNull())
        led->setGlobalBrightness(state["globalBrightness"]);
    if (!state["active"].isNull())
        led->setGlobalPower(state["active"]);
    if (!state["bgActive"].isNull())
        led->setBgEffectActive(state["bgActive"]);
}

void SocketHandler::onWsEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len)
{
    if (type == WS_EVT_CONNECT)
    {
        // client connected
        os_printf("ws[%s][%u] connect\n", server->url(), client->id());
        client->printf("Hello Client %u :)", client->id());
        client->ping();
    }
    else if (type == WS_EVT_DISCONNECT)
    {
        // client disconnected
        os_printf("ws[%s][%u] disconnect: %u\n", server->url(), client->id());
    }
    else if (type == WS_EVT_ERROR)
    {
        // error was received from the other end
        os_printf("ws[%s][%u] error(%u): %s\n", server->url(), client->id(), *((uint16_t *)arg), (char *)data);
    }
    else if (type == WS_EVT_PONG)
    {
        // pong message was received (in response to a ping request maybe)
        os_printf("ws[%s][%u] pong[%u]: %s\n", server->url(), client->id(), len, (len) ? (char *)data : "");
    }
    else if (type == WS_EVT_DATA)
    {
        // data packet
        AwsFrameInfo *info = (AwsFrameInfo *)arg;
        if (info->final && info->index == 0 && info->len == len)
        {
            // the whole message is in a single frame and we got all of it's data
            // os_printf("ws[%s][%u] %s-message[%llu]: ", server->url(), client->id(), (info->opcode == WS_TEXT) ? "text" : "binary", info->len);
            if (info->opcode == WS_TEXT)
            {
                data[len] = 0;
                String msg = (char *)data;
                if (msg.equals("ping"))
                {
                    server->text(client->id(), "pong");
                }
                else
                {
                    handleMessage(msg);
                    // server->textAll(msg);
                }
            }
            else
            {
                for (size_t i = 0; i < info->len; i++)
                {
                    os_printf("%02x ", data[i]);
                }
                os_printf("\n");
            }
            // if (info->message_opcode == WS_TEXT)
            // {
            //     Serial.println("Text msg received");
            //     // handleMessage(msg);
            //     // server->textAll(msg);
            // }
            // else
            //     Serial.println("Binary msg received");
        }
        else
        {
            // // message is comprised of multiple frames or the frame is split into multiple packets
            // if (info->index == 0)
            // {
            //     if (info->num == 0)
            //         os_printf("ws[%s][%u] %s-message start\n", server->url(), client->id(), (info->message_opcode == WS_TEXT) ? "text" : "binary");
            //     os_printf("ws[%s][%u] frame[%u] start[%llu]\n", server->url(), client->id(), info->num, info->len);
            // }

            // os_printf("ws[%s][%u] frame[%u] %s[%llu - %llu]: ", server->url(), client->id(), info->num, (info->message_opcode == WS_TEXT) ? "text" : "binary", info->index, info->index + len);
            // if (info->message_opcode == WS_TEXT)
            // {
            //     data[len] = 0;
            //     os_printf("%s\n", (char *)data);
            // }
            // else
            // {
            //     for (size_t i = 0; i < len; i++)
            //     {
            //         os_printf("%02x ", data[i]);
            //     }
            //     os_printf("\n");
            // }

            // if ((info->index + len) == info->len)
            // {
            //     os_printf("ws[%s][%u] frame[%u] end[%llu]\n", server->url(), client->id(), info->num, info->len);
            //     if (info->final)
            //     {
            //         os_printf("ws[%s][%u] %s-message end\n", server->url(), client->id(), (info->message_opcode == WS_TEXT) ? "text" : "binary");
            //         if (info->message_opcode == WS_TEXT)
            //         {
            //             Serial.println("Text msg received");

            //             // handleMessage(msg);
            //             // server->textAll(msg);
            //         }
            //         else
            //             Serial.println("Binary msg received");
            //     }
            // }
        }
    }
}