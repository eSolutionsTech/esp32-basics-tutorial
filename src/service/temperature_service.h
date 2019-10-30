#ifndef ESP32_BASICS_TUTORIAL_TEMPERATURE_SERVICE_H
#define ESP32_BASICS_TUTORIAL_TEMPERATURE_SERVICE_H


#include <DHT_U.h>
#include <Syslog.h>
#include <PubSubClient.h>

extern Syslog syslog;

static unsigned long lastSent;

class TemperatureService {
public:
    TemperatureService(DHT_Unified *dht, PubSubClient *mqttClient);

    void begin();

    void loop();

private:
    DHT_Unified *__dht;
    PubSubClient *__mqttClient;
};


#endif //ESP32_BASICS_TUTORIAL_TEMPERATURE_SERVICE_H
