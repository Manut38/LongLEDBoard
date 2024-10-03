#include "WebServer.h"

void onStationConnected(const WiFiEventStationModeConnected &evt)
{
    Serial.println("🛜 WiFi connected!");
    Serial.print("SSID: ");
    Serial.println(evt.ssid);
}

void onGotIP(const WiFiEventStationModeGotIP &evt)
{
    Serial.print("Got IP: ");
    Serial.println(evt.ip);
}

void WebServer::setup()
{
    WiFi.disconnect();
    WiFi.persistent(false);
    WiFi.mode(WIFI_AP_STA);
    Serial.print("🆔 MAC: ");
    Serial.println(WiFi.macAddress());

    // Start WiFi AP
    Serial.println("📡 Starting AP...");
    IPAddress ap_localIp = IPAddress(1, 2, 3, 4);
    IPAddress ap_gateway = IPAddress(1, 2, 3, 4);
    IPAddress ap_subnet = IPAddress(255, 255, 255, 0);
    WiFi.softAPConfig(ap_localIp, ap_gateway, ap_subnet);
    WiFi.softAP(HOSTNAME, AP_PASSWORD);

    // Connect to external WiFi
    Serial.println("⏳ Connecting to WiFi...");
    wifiConnectHandler = WiFi.onStationModeConnected(onStationConnected);
    wifiGotIPHandler = WiFi.onStationModeGotIP(onGotIP);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    // Set mDNS
    if (!MDNS.begin(HOSTNAME))
    {
        Serial.println("Error starting mDNS");
    }
    else
    {
        MDNS.addService("http", "tcp", 80);
        Serial.println("🪪 mDNS started");
    }

    // Start file system
    bool fsok = LittleFS.begin();
    Serial.printf_P(PSTR("📂 FS init: %s\n"), fsok ? PSTR("ok") : PSTR("fail!"));
    if (fsok)
    {
// Start FTP server
#ifndef DISABLE_FTP
        ftpSrv.begin(FTP_USER, FTP_PASSWORD);
#endif
    };

    // Configure web server
    defineRoutes();
    // Attach WebSocket Handler
    webSocket.onEvent([this](AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len)
                      { socketHandler->onWsEvent(server, client, type, arg, data, len); });
    server.addHandler(&webSocket);
    // Start web server
    server.begin();
}

void WebServer::loop()
{
    MDNS.update();

#ifndef DISABLE_FTP
    ftpSrv.handleFTP();
#endif

    if ((WiFi.status() != WL_CONNECTED) && (millis() - wifiReconnectTimer >= WIFI_RECONNECT_INTERVAL))
    {
        Serial.println("🔄 Reconnecting to WiFi...");
        WiFi.reconnect();
        wifiReconnectTimer = millis();
    }
}

void WebServer::defineRoutes()
{
    server.serveStatic("/", LittleFS, "/").setDefaultFile("index.html");

    server.on("/heap", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(200, "text/plain", String(ESP.getFreeHeap())); });

    server.onNotFound([](AsyncWebServerRequest *request)
                      { request->send(404); });
}