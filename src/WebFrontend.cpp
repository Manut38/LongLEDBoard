#include "WebFrontend.h"
#include "Config.h"

AsyncWebServer server(80);
FTPServer ftpSrv(LittleFS);

void WebFrontend::setup()
{
    WiFi.mode(WIFI_AP_STA);
    WiFi.softAP(HOSTNAME, AP_PASSWORD);

    Serial.println("Connecting to WIFI...");
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    if (WiFi.waitForConnectResult() != WL_CONNECTED)
    {
        Serial.println("WIFI connection failed!");
        WiFi.disconnect(false);
        delay(200);
        WiFi.begin(WIFI_SSID, WIFI_SSID);
    }

    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

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

    // HTTP routes
    server.serveStatic("/", LittleFS, "/").setDefaultFile("index.htm");

    server.on("/heap", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(200, "text/plain", String(ESP.getFreeHeap())); });

    server.onNotFound([](AsyncWebServerRequest *request)
                      { request->send(404); });

    // Start web server
    server.begin();
}

void WebFrontend::loop()
{
    ftpSrv.handleFTP();
}