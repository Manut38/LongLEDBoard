#include "WebFrontend.h"
#include "Config.h"

AsyncWebServer server(80);
FTPServer ftpSrv(LittleFS);

void WifiStationConnected(WiFiEvent_t event, WiFiEventInfo_t info)
{
    Serial.println("WiFi connected!");
    Serial.print("SSID: ");
    for (int i = 0; i < info.wifi_sta_connected.ssid_len; i++)
    {
        Serial.print((char)info.wifi_sta_connected.ssid[i]);
    }
    Serial.println("");
}

void WiFiGotIP(WiFiEvent_t event, WiFiEventInfo_t info)
{
    Serial.print("Got IP Address: ");
    Serial.println(IPAddress(info.got_ip.ip_info.ip.addr));
}

void WebFrontend::setup()
{
    WiFi.mode(WIFI_AP_STA);

    Serial.println("Starting AP...");
    // Set AP preferences
    IPAddress ap_localIp = IPAddress(1, 2, 3, 4);
    IPAddress ap_gateway = IPAddress(1, 2, 3, 4);
    IPAddress ap_subnet = IPAddress(255, 255, 255, 0);
    WiFi.softAPConfig(ap_localIp, ap_gateway, ap_subnet);
    WiFi.softAP(HOSTNAME, AP_PASSWORD);

    Serial.println("Connecting to WiFi...");
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    WiFi.onEvent(WifiStationConnected, WiFiEvent_t::ARDUINO_EVENT_WIFI_STA_CONNECTED);
    WiFi.onEvent(WiFiGotIP, WiFiEvent_t::ARDUINO_EVENT_WIFI_STA_GOT_IP);

    // Set mDNS
    if (!MDNS.begin(HOSTNAME))
    {
        Serial.println("Error starting mDNS");
    }
    else
    {
        MDNS.addService("http", "tcp", 80);
    }

    // Start file system
    bool fsok = LittleFS.begin();
    Serial.printf_P(PSTR("FS init: %s\n"), fsok ? PSTR("ok") : PSTR("fail!"));
    if (fsok)
    {
        // Start FTP server
        ftpSrv.begin(FTP_USER, FTP_PASSWORD);
    };

    // Start web server
    defineRoutes();
    server.begin();
}

void WebFrontend::loop()
{
    ftpSrv.handleFTP();

    if ((WiFi.status() != WL_CONNECTED) && (millis() - wifiReconnectTimer >= WIFI_RECONNECT_INTERVAL))
    {
        Serial.println("Reconnecting to WiFi...");
        WiFi.reconnect();
        wifiReconnectTimer = millis();
    }
}

void WebFrontend::defineRoutes()
{
    server.serveStatic("/", LittleFS, "/").setDefaultFile("index.htm");

    server.on("/heap", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(200, "text/plain", String(ESP.getFreeHeap())); });

    // TEST
    server.on("/test", HTTP_GET,
              [this](AsyncWebServerRequest *request)
              {
                  FrontendRequestData data;
                  data.time = 1000;
                  frhfn(data);
                  request->send(200, "text/plain", "magic");
              });

    server.onNotFound([](AsyncWebServerRequest *request)
                      { request->send(404); });
}

void WebFrontend::onFrontendRequest(FrontendRequestHandlerFunction fn) { frhfn = fn; }