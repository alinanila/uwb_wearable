#include <Arduino.h>
#include <WiFi.h>

#include "config.h"
#include "wifi_manager.h"
#include "bno085.h"
#include "lsm303.h"
#include "publisher.h"

void i2c_scan() {
    Serial.println("scanning I2C bus...");
    int found = 0;
    for (uint8_t addr = 1; addr < 127; addr++) {
        Wire.beginTransmission(addr);
        uint8_t err = Wire.endTransmission();
        if (err == 0) {
            Serial.printf("  found device at 0x%02X\n", addr);
            found++;
        }
    }
    if (found == 0) {
        Serial.println("  no devices found");
    } else {
        Serial.printf("  %d device(s) found\n", found);
    }
}

void setup() {
    Serial.begin(115200);
    delay(1000);
    Serial.println("booting...");

    Wire.begin();

    delay(20000);

    i2c_scan();
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