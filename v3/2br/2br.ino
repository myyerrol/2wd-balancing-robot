#include "driver_motor.hpp"
#include "driver_encoder.hpp"
#include "driver_imu.hpp"
#include "driver_bth_serial.hpp"

void setup() {
    Serial.begin(9600);
    // initMotor();
    // initEncoder();
    initIMU();
    initBTHSerial();
}

void loop() {
    // testMotor();
    // testEncoder();
    testIMU();
}
