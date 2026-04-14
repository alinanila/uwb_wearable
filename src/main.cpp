#include <Arduino.h>
#include <WiFi.h>

#include "config.h"
#include "wifi_manager.h"
#include "bno085.h"
#include "lsm303.h"
#include "publisher.h"

void setup() {
    Serial.begin(115200);
    delay(1000);
    Serial.println("booting...");

    Wire.begin();

    bno085_init();
    lsm303_init();
    wifi_connect();
    publisher_init();

    Serial.println("ready");
}

void loop() {
    static uint32_t last_publish = 0;

    bno085_read();
    lsm303_read();

    uint32_t now = millis();
    if (now - last_publish >= PUBLISH_INTERVAL_MS) {
        last_publish = now;

        if (!wifi_check()) return;

        publisher_send();
    }
}