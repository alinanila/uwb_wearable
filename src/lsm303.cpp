#include "lsm303.h"
#include <Arduino.h>
#include <math.h>

static Adafruit_LSM303DLH_Mag_Unified lsm_mag(12345);
static Adafruit_LSM303_Accel_Unified  lsm_acc(54321);

LsmData lsm_data;
bool    lsm_ok = false;

void lsm303_init() {
    bool mag_ok = lsm_mag.begin();
    bool acc_ok = lsm_acc.begin();

    if (mag_ok && acc_ok) {
        Serial.println("LSM303 found");
        lsm_ok = true;
    } else {
        if (!mag_ok) Serial.println("LSM303 mag not found — check wiring");
        if (!acc_ok) Serial.println("LSM303 accel not found — check wiring");
    }
}

void lsm303_read() {
    if (!lsm_ok) return;

    sensors_event_t mag_event, acc_event;
    lsm_mag.getEvent(&mag_event);
    lsm_acc.getEvent(&acc_event);

    lsm_data.mag_x = mag_event.magnetic.x;
    lsm_data.mag_y = mag_event.magnetic.y;
    lsm_data.mag_z = mag_event.magnetic.z;

    lsm_data.acc_x = acc_event.acceleration.x;
    lsm_data.acc_y = acc_event.acceleration.y;
    lsm_data.acc_z = acc_event.acceleration.z;

    // tilt-compensated heading
    float roll  = atan2(acc_event.acceleration.y, acc_event.acceleration.z);
    float pitch = atan2(
        -acc_event.acceleration.x,
        sqrt(acc_event.acceleration.y * acc_event.acceleration.y +
             acc_event.acceleration.z * acc_event.acceleration.z)
    );

    float mx = mag_event.magnetic.x * cos(pitch)
             + mag_event.magnetic.z * sin(pitch);
    float my = mag_event.magnetic.x * sin(roll) * sin(pitch)
             + mag_event.magnetic.y * cos(roll)
             - mag_event.magnetic.z * sin(roll) * cos(pitch);

    float heading = atan2(my, mx) * 180.0f / M_PI;
    if (heading < 0.0f) heading += 360.0f;

    lsm_data.heading = heading;
    lsm_data.valid   = true;
}