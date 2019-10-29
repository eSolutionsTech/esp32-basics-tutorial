#include "wifi_service.h"

void WifiService::begin() {
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    printf("connecting to serial...\n");
    int retry = 0;
    while (WiFiClass::status() != WL_CONNECTED && retry < 20) {
        printf(".");
        delay(500);
        retry++;
    }
    printf("\n");

    if (WiFiClass::status() == WL_CONNECTED) {
        printf("connected to WiFi, ip: %s\n", WiFi.localIP().toString().c_str());
    } else {
        printf("wifi connection failed\n");
    }
}
