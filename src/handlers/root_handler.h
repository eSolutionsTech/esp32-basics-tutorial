#ifndef ESP32_BASICS_TUTORIAL_ROOT_HANDLER_H
#define ESP32_BASICS_TUTORIAL_ROOT_HANDLER_H

#include <ESP32WebServer.h>
#include <ArduinoJson.h>
#include <SPIFFS.h>

#include "response.h"

class RootHandler {
public:
    explicit RootHandler(ESP32WebServer *server);

    void currentStatus();

private:
    ESP32WebServer *__server = nullptr;
};


#endif //ESP32_BASICS_TUTORIAL_ROOT_HANDLER_H
