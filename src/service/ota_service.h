#ifndef ESP32_BASICS_TUTORIAL_OTA_SERVICE_H
#define ESP32_BASICS_TUTORIAL_OTA_SERVICE_H

#include <ArduinoOTA.h>
#include <Syslog.h>

extern Syslog syslog;

class OtaService {
public:
    void begin();

    void loop();
};


#endif //ESP32_BASICS_TUTORIAL_OTA_SERVICE_H
