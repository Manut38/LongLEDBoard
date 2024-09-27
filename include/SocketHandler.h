#pragma once

#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>
#include "Config.h"
#include "LED.h"

#include "LedEffect/LedEffect.h"
#include "LedEffect/EffectSolidColor.h"

class SocketHandler
{

public:
    SocketHandler(LED *led) : led(led) {};

    void onWsEvent(AsyncWebSocket *ws, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len);
    void handleMessage(String msg);

    void handleEffectConfig(JsonObject &effectConfig);
    void handleBoardState(JsonObject &state);

private:
    LED *led;
};