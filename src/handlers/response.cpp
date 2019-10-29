#include "response.h"

#define JSON_CONTENT_TYPE "application/json"

void sendJsonResponse(ESP32WebServer *server, int code, const String &json) {
    setupCORS(server);
    server->send(code, JSON_CONTENT_TYPE, json);
}

void sendSuccessResponse(ESP32WebServer *server, int code, const String &message) {
    StaticJsonDocument<256> root;
    root["success"] = true;
    root["message"] = message;
    String json;
    serializeJson(root, json);

    setupCORS(server);
    server->send(code, JSON_CONTENT_TYPE, json);
}

void sendErrorResponse(ESP32WebServer *server, int code, const String &message) {
    StaticJsonDocument<256> root;
    root["success"] = false;
    root["message"] = message;
    String json;
    serializeJson(root, json);

    setupCORS(server);
    server->send(code, JSON_CONTENT_TYPE, json);
}

void setupCORS(ESP32WebServer *server) {
    server->sendHeader("Access-Control-Allow-Origin", "*");
    server->sendHeader("Access-Control-Max-Age", "10000");
    server->sendHeader("Access-Control-Allow-Methods", "POST,GET,DELETE,OPTIONS");
    server->sendHeader("Access-Control-Allow-Headers", "Origin, X-Requested-With, Content-Type, Accept");
}