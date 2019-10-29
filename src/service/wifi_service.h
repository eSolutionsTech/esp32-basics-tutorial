#ifndef ESP32_BASICS_TUTORIAL_WIFI_SERVICE_H
#define ESP32_BASICS_TUTORIAL_WIFI_SERVICE_H

#include <WiFi.h>
#include <Syslog.h>

#ifndef WIFI_SSID
#define WIFI_SSID "wifi_ssid"
#endif

#ifndef WIFI_PASSWORD
#define WIFI_PASSWORD "wifi_password"
#endif

class WifiService {
public:
    void begin();
};


#endif //ESP32_BASICS_TUTORIAL_WIFI_SERVICE_H
