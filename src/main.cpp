#include <HardwareSerial.h>
#include <Syslog.h>
#include <ESP32WebServer.h>
#include <DHT_U.h>
#include <PubSubClient.h>

#include <service/wifi_service.h>
#include <service/ota_service.h>
#include <handlers/root_handler.h>
#include <service/temperature_service.h>

#define DHT_PIN 15

const char *HOSTNAME = "temp-sensor";
const char *SYSLOG_SERVER = "logs5.papertrailapp.com";
const int SYSLOG_SERVER_PORT = 50807;

const char *MQTT_SERVER = "farmer.cloudmqtt.com";
int MQTT_PORT = 13872;

static unsigned long lastMqttConnectAttempt = 0;

WiFiUDP wifiUdp;
Syslog syslog(wifiUdp, SYSLOG_SERVER, SYSLOG_SERVER_PORT, HOSTNAME, "tempmon", LOG_INFO);
ESP32WebServer server(80);

WifiService wifiService;
OtaService otaService;

RootHandler rootHandler(&server);

DHT_Unified dht(DHT_PIN, DHT22);

WiFiClient wiFiClient;
PubSubClient mqttClient(wiFiClient);
TemperatureService temperatureService(&dht, &mqttClient);

void setup() {
    Serial.begin(115200);

    SPIFFS.begin(true);

    wifiService.begin();
    otaService.begin();

    server.on("/", [] { rootHandler.currentStatus(); });
    server.begin();

    mqttClient.setServer(MQTT_SERVER, MQTT_PORT);
    temperatureService.begin();
}

void reconnect() {
    // Loop until we're reconnected
    if (!mqttClient.connected() && millis() - lastMqttConnectAttempt > 2000) {
        syslog.log(LOG_INFO, "attempting MQTT connection...");
        if (mqttClient.connect("temp1", "fntaeinw", "9GbqJ7pB_SgO")) {
            syslog.log(LOG_INFO, "connected");
            // Once connected, publish an announcement...
            //client.publish("Say", "-t 'hello world'");
            // ... and resubscribe
            mqttClient.subscribe("toTemp1");
        } else {
            syslog.logf(LOG_ERR, "failed, rc=%d", mqttClient.state());
            syslog.log(LOG_INFO, "try again in 2 seconds");
            // Wait 5 seconds before retrying
        }
        lastMqttConnectAttempt = millis();
    }
}

void loop() {
    otaService.loop();
    server.handleClient();

    if (!mqttClient.connected()) {
        reconnect();
    }

    mqttClient.loop();
    temperatureService.loop();
}