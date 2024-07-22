#ifndef DRIVER_IMU
#define DRIVER_IMU

#include <Arduino.h>
#include <MPU6050_tockn.h>
#include "2br.hpp"

#define IMU_PIN_SDA 13
#define IMU_PIN_SCL 12

void initIMU();
void getIMUAngle(float *p_angle_x, float *p_angle_y, float *p_angle_z);
void testIMU();

#endif
