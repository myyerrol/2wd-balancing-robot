#include "driver_motor.hpp"
#include "driver_encoder.hpp"
#include "driver_imu.hpp"

void setup() {
    Serial.begin(9600);
    // initMotor();
    // initEncoder();
    initIMU();
}

void loop() {
    // double *angleX;
    // double *angleY;
    // double *angleZ;
    // mpu6050_get_angel(angleX, 'X');
    // mpu6050_get_angel(angleY, 'Y');
    // mpu6050_get_angel(angleZ, 'Z');
    // Serial.print("X: ");
    // Serial.print(*angleX, DEC);
    // Serial.println("X: %f Y: %f Z: %f", *angleX, *angleY, *angleZ);
    // mpu6050_get_angel(angle, 'Y');
    // Serial.printf("Y: %f ", *angle);
    // mpu6050_get_angel(angle, 'Z');
    // Serial.printf("Z: %f", *angle);


    // testMotor();
    // testEncoder();
    testIMU();
}
