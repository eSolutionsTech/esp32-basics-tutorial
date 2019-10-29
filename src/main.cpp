#include <HardwareSerial.h>
#include <ArduinoOTA.h>

#include <service/wifi_service.h>

WifiService wifiService;

void setup() {
    Serial.begin(115200);

    wifiService.begin();
    ArduinoOTA.begin();
}

void loop() {
    ArduinoOTA.handle();
}