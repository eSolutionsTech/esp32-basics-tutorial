#ifndef RESPONSE_H
#define RESPONSE_H

#include <ESP32WebServer.h>
#include <ArduinoJson.h>

void setupCORS(ESP32WebServer *server);

void sendJsonResponse(ESP32WebServer *server, int code, const String &json);

void sendSuccessResponse(ESP32WebServer *server, int code, const String &message);

void sendErrorResponse(ESP32WebServer *server, int code, const String &message);

#endif //RESPONSE_H
