#include <HardwareSerial.h>
#include <ArduinoOTA.h>
#include <Syslog.h>

#include <service/wifi_service.h>
#include <service/ota_service.h>

const char *HOSTNAME = "temp-sensor";
const char *SYSLOG_SERVER = "logs5.papertrailapp.com";
const int SYSLOG_SERVER_PORT = 50807;

WiFiUDP wifiUdp;
Syslog syslog(wifiUdp, SYSLOG_SERVER, SYSLOG_SERVER_PORT, HOSTNAME, "tempmon", LOG_INFO);

WifiService wifiService;
OtaService otaService;

void setup() {
    Serial.begin(115200);

    wifiService.begin();
    otaService.begin();
}

void loop() {
    otaService.loop();
}