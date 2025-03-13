#ifndef DRIVER_IMU
#define DRIVER_IMU

#include <Arduino.h>
#include <MPU6050_tockn.h>

void mpu6050_init();//mpu6050初始化
void mpu6050_get_angel(double* getAngel,char Axis); //获取角度，参数例如'X'

#endif
