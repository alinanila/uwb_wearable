#include "wifi_manager.h"
#include "config.h"
#include <Arduino.h>
#include <WiFi.h>

void wifi_connect() {
    Serial.printf("connecting to %s\n", WIFI_SSID);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.printf("\nconnected — IP: %s\n", WiFi.localIP().toString().c_str());
}

bool wifi_check() {
    if (WiFi.status() == WL_CONNECTED) return true;
    Serial.println("wifi disconnected — reconnecting...");
    WiFi.reconnect();
    return false;
}