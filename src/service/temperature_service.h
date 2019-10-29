#ifndef ESP32_BASICS_TUTORIAL_TEMPERATURE_SERVICE_H
#define ESP32_BASICS_TUTORIAL_TEMPERATURE_SERVICE_H


#include <DHT_U.h>
#include <Syslog.h>

extern Syslog syslog;

static unsigned long lastSent;

class TemperatureService {
public:
    explicit TemperatureService(DHT_Unified *dht);

    void begin();

    void loop();

private:
    DHT_Unified *__dht;
};


#endif //ESP32_BASICS_TUTORIAL_TEMPERATURE_SERVICE_H
