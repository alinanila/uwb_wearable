#ifndef CONFIG_H
#define CONFIG_H

#include <stdint.h>

// wifi
const char* const WIFI_SSID     = "ARouter";
const char* const WIFI_PASSWORD = "arfyp2026";

// server
const char* const SERVER_IP = "192.168.8.104";
const uint16_t    UDP_PORT  = 5570;

// device
const char* const DEVICE_ID = "PERFORMER";

// timing
const uint32_t PUBLISH_INTERVAL_MS = 50;  // 20Hz

// BNO085 report intervals (microseconds)
const uint32_t BNO_FAST_INTERVAL_US = 10000;   // 100Hz
const uint32_t BNO_SLOW_INTERVAL_US = 200000;  // 5Hz

// LSM303 I2C addresses 
const uint8_t LSM303_MAG_ADDR  = 0x1E;
const uint8_t LSM303_ACCEL_ADDR = 0x18;

#endif // CONFIG_H