#include "temperature_service.h"

TemperatureService::TemperatureService(DHT_Unified *dht) {
    __dht = dht;
}

void TemperatureService::begin() {
    lastSent = 0;

    __dht->begin();

    syslog.log("DHTxx Unified Sensor Example");
    // Print temperature sensor details.
    sensor_t sensor;
    __dht->temperature().getSensor(&sensor);
    syslog.log("------------------------------------");
    syslog.log("Temperature");
    syslog.logf("Sensor:           %s", sensor.name);
    syslog.logf("Driver Ver:       %d", sensor.version);
    syslog.logf("Unique ID:        %d", sensor.sensor_id);
    syslog.logf("Min Value:        %.2f *C", sensor.min_value);
    syslog.logf("Max Value:        %.2f *C", sensor.max_value);
    syslog.logf("Resolution:       %.2f *C", sensor.resolution);
    syslog.log("------------------------------------");

    // Print humidity sensor details.
    __dht->humidity().getSensor(&sensor);
    syslog.log("------------------------------------");
    syslog.log("Humidity");
    syslog.logf("Sensor:           %s", sensor.name);
    syslog.logf("Driver Ver:       %d", sensor.version);
    syslog.logf("Unique ID:        %d", sensor.sensor_id);
    syslog.logf("Min Value:        %.2f %%", sensor.min_value);
    syslog.logf("Max Value:        %.2f %%", sensor.max_value);
    syslog.logf("Resolution:       %.2f %%", sensor.resolution);
    syslog.log("------------------------------------");
    // Set delay between sensor readings based on sensor details.
}

void TemperatureService::loop() {
    if (millis() - lastSent > 3000) {
        syslog.log(LOG_DEBUG, "reading sensors... ");
        sensors_event_t temp;
        __dht->temperature().getEvent(&temp);
        sensors_event_t humidity;
        __dht->humidity().getEvent(&humidity);

        if (!isnan(temp.temperature)) {
            syslog.logf(LOG_INFO, "temperature: %f", temp.temperature);
        }

        if (!isnan(temp.relative_humidity)) {
            syslog.logf(LOG_INFO, "humidity %f", humidity.relative_humidity);
        }

        lastSent = millis();
    }
}
