#ifndef BNO085_H
#define BNO085_H

#include <Adafruit_BNO08x.h>

// BNO085 data struct
struct BnoData {
    // rotation vector (absolute, uses magnetometer)
    float quat_i        = 0.0f;
    float quat_j        = 0.0f;
    float quat_k        = 0.0f;
    float quat_real     = 1.0f;
    float quat_accuracy = 0.0f;

    // game rotation vector (no magnetometer, no yaw drift correction)
    float game_quat_i    = 0.0f;
    float game_quat_j    = 0.0f;
    float game_quat_k    = 0.0f;
    float game_quat_real = 1.0f;

    // linear acceleration — gravity removed (m/s^2)
    float lin_acc_x = 0.0f;
    float lin_acc_y = 0.0f;
    float lin_acc_z = 0.0f;

    // raw accelerometer (m/s^2)
    float acc_x = 0.0f;
    float acc_y = 0.0f;
    float acc_z = 0.0f;

    // calibrated gyroscope (rad/s)
    float gyro_x = 0.0f;
    float gyro_y = 0.0f;
    float gyro_z = 0.0f;

    // gravity vector (m/s^2)
    float grav_x = 0.0f;
    float grav_y = 0.0f;
    float grav_z = 0.0f;

    // step counter
    uint32_t steps = 0;

    // stability classifier
    // 0=unknown 1=on_table 2=stationary 3=stable 4=motion
    uint8_t stability = 0;

    bool valid = false;
};

// global instance — accessible from publisher
extern BnoData bno_data;
extern bool    bno_ok;

// initialise BNO085 and enable reports
void bno085_init();

// drain all pending BNO085 reports into bno_data
void bno085_read();

#endif // BNO085_H