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
    // Background Effects
    JsonObject bgEffect = effectConfig["bgEffect"];
    if (!bgEffect.isNull())
    {
        if (!bgEffect["solidColor"].isNull())
        {
            led->effectConfig.bgEffect.solidColor.color = LED::colorFromHexString(bgEffect["solidColor"]["color"]);
        }
        if (!bgEffect["rainbow"].isNull())
        {
            led->effectConfig.bgEffect.rainbow.duration = bgEffect["rainbow"]["duration"];
        }
        led->reloadBgEffect();
    }

    // Accel Effects
    JsonObject accelEffect = effectConfig["accelEffect"];
    if (!accelEffect.isNull())
    {
        if (!accelEffect["rainbowStrike"].isNull())
        {
            led->effectConfig.accelEffect.rainbowStrike.duration = accelEffect["rainbowStrike"]["duration"];
        }
        if (!accelEffect["colorStrike"].isNull())
        {
            led->effectConfig.accelEffect.colorStrike.duration = accelEffect["colorStrike"]["duration"];
            led->effectConfig.accelEffect.colorStrike.color = LED::colorFromHexString(accelEffect["colorStrike"]["color"]);
        }
    }
}

void SocketHandler::handleBoardState(JsonObject state)
{
    // Global power and brightness
    if (!state["active"].isNull())
        led->setGlobalPower(state["active"]);
    if (!state["globalBrightness"].isNull())
        led->setGlobalBrightness(state["globalBrightness"]);

    // Effect active state
    if (!state["bgActive"].isNull())
        led->setBgEffectActive(state["bgActive"]);
    if (!state["accelActive"].isNull())
        led->setAccelEffectActive(state["accelActive"]);
    if (!state["steeringActive"].isNull())
        led->setSteeringEffectActive(state["steeringActive"]);

    // Effect selection
    if (!state["bgSelected"].isNull())
        led->selectBgEffect(state["bgSelected"].as<const char *>());
    if (!state["accelSelected"].isNull())
        led->selectAccelEffect(state["accelSelected"].as<const char *>());
    // if (!state["steeringSelected"].isNull())
    //     led->selectSteeringEffect(state["steeringSelected"].as<const char*>());
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
        os_printf("ws[%s][%u] disconnect: %u\n", server->url(), client->id(), client->id());
    }
    else if (type == WS_EVT_ERROR)
    {
        // error was received from the other end
        os_printf("ws[%s][%u] error(%u): %s\n", server->url(), client->id(), *((uint16_t *)arg), (char *)data);
    }
    else if (type == WS_EVT_PONG)
    {
        // pong message was received (in response to a ping request maybe)
        os_printf("ws[%s][%u] pong received[%u]: %s\n", server->url(), client->id(), len, (len) ? (char *)data : "");
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
                    // os_printf("ws[%s][%u] pong sent\n", server->url(), client->id());
                }
                else
                {
                    handleMessage(msg);
                    // server->textAll(msg);
                    socketRecvBuffer.clear();
                }
            }
            else
            {
                // binary
                for (size_t i = 0; i < info->len; i++)
                {
                    os_printf("%02x ", data[i]);
                }
                os_printf("\n");
            }
        }
        else
        {
            // message is comprised of multiple frames or the frame is split into multiple packets
            // if (info->index == 0)
            // {
            //     if (info->num == 0)
            //         os_printf("ws[%s][%u] %s-message start\n", server->url(), client->id(), (info->message_opcode == WS_TEXT) ? "text" : "binary");
            //     os_printf("ws[%s][%u] frame[%u] start[%llu]\n", server->url(), client->id(), info->num, info->len);
            // }

            // os_printf("ws[%s][%u] frame[%u] %s[%llu - %llu]: ", server->url(), client->id(), info->num, (info->message_opcode == WS_TEXT) ? "text" : "binary", info->index, info->index + len);
            if (info->message_opcode == WS_TEXT)
            {
                data[len] = 0;
                // os_printf("%s\n", (char *)data);
                socketRecvBuffer += (char *)data;
            }
            else
            {
                // binary
                for (size_t i = 0; i < len; i++)
                {
                    os_printf("%02x ", data[i]);
                }
                os_printf("\n");
            }

            if ((info->index + len) == info->len)
            {
                // os_printf("ws[%s][%u] frame[%u] end[%llu]\n", server->url(), client->id(), info->num, info->len);
                if (info->final)
                {
                    // os_printf("ws[%s][%u] %s-message end\n", server->url(), client->id(), (info->message_opcode == WS_TEXT) ? "text" : "binary");
                    if (info->message_opcode == WS_TEXT)
                    {
                        handleMessage(socketRecvBuffer);
                        socketRecvBuffer.clear();
                        // server->textAll(msg);
                    }
                    else
                        Serial.println("Binary msg received");
                }
            }
        }
    }
}