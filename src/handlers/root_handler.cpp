#include <HTTPClient.h>
#include "root_handler.h"

RootHandler::RootHandler(ESP32WebServer *server) {
    __server = server;
}

void RootHandler::currentStatus() {
    StaticJsonDocument<512> root;
    root["ap_enabled"] = !WiFi.isConnected();
    root["ap_ip"] = WiFi.softAPIP().toString();
    root["wifi_enabled"] = WiFi.isConnected();
    root["wifi_ip"] = WiFi.localIP().toString();
    root["min_free_heap"] = esp_get_minimum_free_heap_size();
    root["free_heap"] = esp_get_free_heap_size();
    root["total_bytes"] = SPIFFS.totalBytes();
    root["used_bytes"] = SPIFFS.usedBytes();
    root["internal_clock"] = esp_timer_get_time();

    String json;
    serializeJson(root, json);

    sendJsonResponse(__server, HTTP_CODE_OK, json);
}
