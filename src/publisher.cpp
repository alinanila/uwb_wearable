#include "publisher.h"
#include "config.h"
#include "bno085.h"
#include "lsm303.h"
#include <Arduino.h>
#include <WiFiUdp.h>
#include <ArduinoJson.h>

static WiFiUdp udp;

void publisher_init() {
    udp.begin(UDP_PORT);
    Serial.printf("UDP publisher -> %s:%d\n", SERVER_IP, UDP_PORT);
}

void publisher_send() {
    JsonDocument doc;

    doc["schema"]         = "uwb.sensors";
    doc["schema_version"] = 1;
    doc["timestamp"]      = millis() / 1000.0;
    doc["device_id"]      = DEVICE_ID;

    // BNO085
    if (bno_ok && bno_data.valid) {
        JsonObject bno = doc["bno085"].to<JsonObject>();

        JsonObject quat = bno["rotation_vector"].to<JsonObject>();
        quat["i"]        = bno_data.quat_i;
        quat["j"]        = bno_data.quat_j;
        quat["k"]        = bno_data.quat_k;
        quat["real"]     = bno_data.quat_real;
        quat["accuracy"] = bno_data.quat_accuracy;

        JsonObject game_quat = bno["game_rotation_vector"].to<JsonObject>();
        game_quat["i"]    = bno_data.game_quat_i;
        game_quat["j"]    = bno_data.game_quat_j;
        game_quat["k"]    = bno_data.game_quat_k;
        game_quat["real"] = bno_data.game_quat_real;

        JsonObject lin_acc = bno["linear_acceleration"].to<JsonObject>();
        lin_acc["x"] = bno_data.lin_acc_x;
        lin_acc["y"] = bno_data.lin_acc_y;
        lin_acc["z"] = bno_data.lin_acc_z;

        JsonObject acc = bno["accelerometer"].to<JsonObject>();
        acc["x"] = bno_data.acc_x;
        acc["y"] = bno_data.acc_y;
        acc["z"] = bno_data.acc_z;

        JsonObject gyro = bno["gyroscope"].to<JsonObject>();
        gyro["x"] = bno_data.gyro_x;
        gyro["y"] = bno_data.gyro_y;
        gyro["z"] = bno_data.gyro_z;

        JsonObject grav = bno["gravity"].to<JsonObject>();
        grav["x"] = bno_data.grav_x;
        grav["y"] = bno_data.grav_y;
        grav["z"] = bno_data.grav_z;

        bno["steps"]     = bno_data.steps;
        bno["stability"] = bno_data.stability;
    }

    // LSM303
    if (lsm_ok && lsm_data.valid) {
        JsonObject lsm = doc["lsm303"].to<JsonObject>();

        JsonObject mag = lsm["magnetometer"].to<JsonObject>();
        mag["x"] = lsm_data.mag_x;
        mag["y"] = lsm_data.mag_y;
        mag["z"] = lsm_data.mag_z;

        JsonObject acc = lsm["accelerometer"].to<JsonObject>();
        acc["x"] = lsm_data.acc_x;
        acc["y"] = lsm_data.acc_y;
        acc["z"] = lsm_data.acc_z;

        lsm["heading"] = lsm_data.heading;
    }

    char buf[1024];
    size_t len = serializeJson(doc, buf, sizeof(buf));
    udp.beginPacket(SERVER_IP, UDP_PORT);
    udp.write((uint8_t*)buf, len);
    udp.endPacket();
}