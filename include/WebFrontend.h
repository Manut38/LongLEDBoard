#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <FS.h>
#include <LittleFS.h>
#include <ESPmDNS.h>
#include <FTPServer.h>
#include <ArduinoOTA.h>

#include "Config.h"

class WebFrontend
{
private:
public:
    void setup();
    void loop();
};