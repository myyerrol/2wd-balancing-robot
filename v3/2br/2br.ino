#include "driver_serial.hpp"
#include "driver_ble.hpp"
#include "driver_wifi.hpp"
#include "module_motor.hpp"
#include "module_encoder.hpp"
#include "module_imu.hpp"

void setup() {
    initSerial();
    // initMotor();
    // initEncoder();
    // initIMU();
    // initBLE();
    initWIFI();
}

void loop() {
#ifdef DEBUG_MOTOR
    testMotor();
#endif
#ifdef DEBUG_ENCODER
    testEncoder();
#endif
#ifdef DEBUG_IMU
    testIMU();
#endif
#ifdef DEBUG_BLE
    testBLE();
#endif
#ifdef DEBUG_WIFI
    testWIFI();
#endif
}
