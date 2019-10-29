#include "wifi_service.h"

extern Syslog syslog;

void WifiService::begin() {
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    syslog.log("connecting to serial...\n");
    int retry = 0;
    while (WiFiClass::status() != WL_CONNECTED && retry < 20) {
        printf(".");
        delay(500);
        retry++;
    }
    printf("\n");

    if (WiFiClass::status() == WL_CONNECTED) {
        syslog.logf("connected to WiFi, ip: %s\n", WiFi.localIP().toString().c_str());
    } else {
        syslog.log(LOG_ERR, "wifi connection failed\n");
    }
}
