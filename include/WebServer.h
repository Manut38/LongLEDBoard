#include <ESP8266WiFi.h>
#include <ESPAsyncWebServer.h>
#include <LittleFS.h>
#include <ESP8266mDNS.h>
#include <FTPServer.h>
#include <ArduinoJson.h>
#include "Config.h"
#include "SocketHandler.h"

struct FrontendRequestData
{
    int time;
};

typedef std::function<void(FrontendRequestData data)> FrontendRequestHandlerFunction;

class WebServer
{
public:
    WebServer() : server(80),
                  webSocket("/ws"),
                  ftpSrv(LittleFS) {};

    void setup();
    void loop();
    void onFrontendRequest(FrontendRequestHandlerFunction fn);
    void setSocketHandler(SocketHandler *handler) { socketHandler = unique_ptr<SocketHandler>(handler); };

private:
    AsyncWebServer server;
    AsyncWebSocket webSocket;
    FTPServer ftpSrv;
    WiFiEventHandler wifiConnectHandler;
    WiFiEventHandler wifiGotIPHandler;

    unique_ptr<SocketHandler> socketHandler;

    unsigned long wifiReconnectTimer = 0;
    FrontendRequestHandlerFunction frhfn;

    void defineRoutes();
};