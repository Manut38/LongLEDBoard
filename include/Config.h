#pragma once

// Hardware config
#define LED_PIN 16
#define NUM_LEDS 120

// LED config
#define DEFAULT_BRIGHTNESS 128

// Network host name
#define HOSTNAME "LongLEDBoard"

// WIFI Connection Setup
#define WIFI_RECONNECT_INTERVAL 10000
#ifndef WIFI_SSID
#define WIFI_SSID "wifi"
#warning No WIFI_SSID supplied, using default
#endif
#ifndef WIFI_PASSWORD
#define WIFI_PASSWORD "pass"
#warning No WIFI_PASSWORD supplied, using default
#endif

// WIFI AP Setup
#define AP_SSID HOSTNAME
#ifndef AP_PASSWORD
#define AP_PASSWORD "longledboard"
#warning No AP_PASSWORD supplied, using default
#endif

// FTP Credentials
#define FTP_USER "ftp"
#define FTP_PASSWORD "ChangeMe"
