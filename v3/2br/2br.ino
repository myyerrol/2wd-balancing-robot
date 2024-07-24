#include "driver_motor.hpp"
#include "driver_encoder.hpp"
#include "driver_imu.hpp"
#include "driver_ble.hpp"

void setup() {
    Serial.begin(9600);
    initMotor();
    initEncoder();
    initIMU();
    initBLE();
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
}
