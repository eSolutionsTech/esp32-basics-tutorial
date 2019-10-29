#include <HardwareSerial.h>
#include <Syslog.h>
#include <ESP32WebServer.h>

#include <DHT_U.h>
#include <Adafruit_Sensor.h>

#define DHT_PIN 15

#include <service/wifi_service.h>
#include <service/ota_service.h>
#include <handlers/root_handler.h>
#include <service/temperature_service.h>

const char *HOSTNAME = "temp-sensor";
const char *SYSLOG_SERVER = "logs5.papertrailapp.com";
const int SYSLOG_SERVER_PORT = 50807;

WiFiUDP wifiUdp;
Syslog syslog(wifiUdp, SYSLOG_SERVER, SYSLOG_SERVER_PORT, HOSTNAME, "tempmon", LOG_INFO);
ESP32WebServer server(80);

WifiService wifiService;
OtaService otaService;

RootHandler rootHandler(&server);

DHT_Unified dht(DHT_PIN, DHT22);
TemperatureService temperatureService(&dht);

void setup() {
    Serial.begin(115200);

    SPIFFS.begin(true);

    wifiService.begin();
    otaService.begin();

    server.on("/", [] { rootHandler.currentStatus(); });
    server.begin();

    temperatureService.begin();
}

void loop() {
    otaService.loop();
    server.handleClient();
    temperatureService.loop();
}