#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <FS.h>
#include <LittleFS.h>
#include <ESPmDNS.h>
#include <FTPServer.h>
#include <ArduinoOTA.h>

#include "Config.h"

#define WIFI_RECONNECT_INTERVAL 8000

struct FrontendRequestData
{
    int time;
};

typedef std::function<void(FrontendRequestData data)> FrontendRequestHandlerFunction;

class WebFrontend
{
private:
    unsigned long wifiReconnectTimer = 0;
    FrontendRequestHandlerFunction frhfn;

    void defineRoutes();

public:
    void setup();
    void loop();
    void onFrontendRequest(FrontendRequestHandlerFunction fn);
};