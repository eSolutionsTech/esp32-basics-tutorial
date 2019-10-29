#include "ota_service.h"

void OtaService::begin() {
    ArduinoOTA.onStart([]() {
        String type;
        if (ArduinoOTA.getCommand() == U_FLASH)
            type = "sketch";
        else // U_SPIFFS
            type = "filesystem";

        syslog.logf(LOG_DEBUG, "start updating %s", type.c_str());
    });
    ArduinoOTA.onEnd([]() {
        syslog.log(LOG_DEBUG, "end");
    });
    ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
        syslog.logf(LOG_DEBUG, "progress: %u%%", (progress / (total / 100)));
    });
    ArduinoOTA.onError([](ota_error_t error) {
        syslog.logf(LOG_DEBUG, "error[%u]:", error);
        if (error == OTA_AUTH_ERROR) {
            syslog.log(LOG_DEBUG, "Auth Failed");
        } else if (error == OTA_BEGIN_ERROR) {
            syslog.log(LOG_DEBUG, "Begin Failed");
        } else if (error == OTA_CONNECT_ERROR) {
            syslog.log(LOG_DEBUG, "Connect Failed");
        } else if (error == OTA_RECEIVE_ERROR) {
            syslog.log(LOG_DEBUG, "Receive Failed");
        } else if (error == OTA_END_ERROR) {
            syslog.log(LOG_DEBUG, "End Failed");
        }
    });

    ArduinoOTA.begin();
}

void OtaService::loop() {
    ArduinoOTA.handle();
}
