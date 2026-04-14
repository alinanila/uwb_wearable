#include "bno085.h"
#include "config.h"
#include <Arduino.h>

static Adafruit_BNO08x bno08x;
static sh2_SensorValue_t bno_value;

BnoData bno_data;
bool    bno_ok = false;

static void enable_reports() {
    bno08x.enableReport(SH2_ROTATION_VECTOR,       BNO_FAST_INTERVAL_US);
    bno08x.enableReport(SH2_GAME_ROTATION_VECTOR,  BNO_FAST_INTERVAL_US);
    bno08x.enableReport(SH2_LINEAR_ACCELERATION,   BNO_FAST_INTERVAL_US);
    bno08x.enableReport(SH2_ACCELEROMETER,         BNO_FAST_INTERVAL_US);
    bno08x.enableReport(SH2_GYROSCOPE_CALIBRATED,  BNO_FAST_INTERVAL_US);
    bno08x.enableReport(SH2_GRAVITY,               BNO_FAST_INTERVAL_US);
    bno08x.enableReport(SH2_STEP_COUNTER,          BNO_SLOW_INTERVAL_US);
    bno08x.enableReport(SH2_STABILITY_CLASSIFIER,  BNO_SLOW_INTERVAL_US);
}

void bno085_init() {
    if (bno08x.begin_I2C()) {
        Serial.println("BNO085 found");
        enable_reports();
        bno_ok = true;
    } else {
        Serial.println("BNO085 not found — check wiring");
    }
}

void bno085_read() {
    if (!bno_ok) return;

    while (bno08x.getSensorEvent(&bno_value)) {
        switch (bno_value.sensorId) {
            case SH2_ROTATION_VECTOR:
                bno_data.quat_i        = bno_value.un.rotationVector.i;
                bno_data.quat_j        = bno_value.un.rotationVector.j;
                bno_data.quat_k        = bno_value.un.rotationVector.k;
                bno_data.quat_real     = bno_value.un.rotationVector.real;
                bno_data.quat_accuracy = bno_value.un.rotationVector.accuracy;
                break;
            case SH2_GAME_ROTATION_VECTOR:
                bno_data.game_quat_i    = bno_value.un.gameRotationVector.i;
                bno_data.game_quat_j    = bno_value.un.gameRotationVector.j;
                bno_data.game_quat_k    = bno_value.un.gameRotationVector.k;
                bno_data.game_quat_real = bno_value.un.gameRotationVector.real;
                break;
            case SH2_LINEAR_ACCELERATION:
                bno_data.lin_acc_x = bno_value.un.linearAcceleration.x;
                bno_data.lin_acc_y = bno_value.un.linearAcceleration.y;
                bno_data.lin_acc_z = bno_value.un.linearAcceleration.z;
                break;
            case SH2_ACCELEROMETER:
                bno_data.acc_x = bno_value.un.accelerometer.x;
                bno_data.acc_y = bno_value.un.accelerometer.y;
                bno_data.acc_z = bno_value.un.accelerometer.z;
                break;
            case SH2_GYROSCOPE_CALIBRATED:
                bno_data.gyro_x = bno_value.un.gyroscope.x;
                bno_data.gyro_y = bno_value.un.gyroscope.y;
                bno_data.gyro_z = bno_value.un.gyroscope.z;
                break;
            case SH2_GRAVITY:
                bno_data.grav_x = bno_value.un.gravity.x;
                bno_data.grav_y = bno_value.un.gravity.y;
                bno_data.grav_z = bno_value.un.gravity.z;
                break;
            case SH2_STEP_COUNTER:
                bno_data.steps = bno_value.un.stepCounter.steps;
                break;
            case SH2_STABILITY_CLASSIFIER:
                bno_data.stability = bno_value.un.stabilityClassifier.classification;
                break;
            default:
                break;
        }
        bno_data.valid = true;
    }
}