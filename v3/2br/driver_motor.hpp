#ifndef DRIVER_MOTOR
#define DRIVER_MOTOR

#include <Arduino.h>
#include "2br.hpp"

#define PIN_MOTOR_L1 0
#define PIN_MOTOR_L2 1
#define PIN_MOTOR_R1 2
#define PIN_MOTOR_R2 3

#define LEDC_FREQ_1000HZ 1000
#define LEDC_RESO_10BITS 10

#define MOTOR_L 0
#define MOTOR_R 1

void initMotor();
void setMotorDirAndSpeed(int motor, float pwm);
void testMotor();

#endif
