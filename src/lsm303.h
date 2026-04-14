#ifndef LSM303_H
#define LSM303_H

#include <Adafruit_LSM303DLH_Mag.h>
#include <Adafruit_LSM303_Accel.h>
#include <Adafruit_Sensor.h>

// LSM303 data struct
struct LsmData {
    // magnetometer (uT)
    float mag_x = 0.0f;
    float mag_y = 0.0f;
    float mag_z = 0.0f;

    // accelerometer (m/s^2)
    float acc_x = 0.0f;
    float acc_y = 0.0f;
    float acc_z = 0.0f;

    // tilt-compensated heading (degrees, 0=North, 0-360)
    float heading = 0.0f;

    bool valid = false;
};

// global instance — accessible from publisher
extern LsmData lsm_data;
extern bool    lsm_ok;

// initialise LSM303 magnetometer and accelerometer
void lsm303_init();

// read latest LSM303 measurements into lsm_data
void lsm303_read();

#endif // LSM303_H