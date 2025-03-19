#ifndef DRIVER_MOTOR
#define DRIVER_MOTOR

#include <Arduino.h>
#include "2br.hpp"

#define MOTOR_PIN_L1 0
#define MOTOR_PIN_L2 1
#define MOTOR_PIN_R1 2
#define MOTOR_PIN_R2 3

#define MOTOR_FREQ_1000HZ 1000
#define MOTOR_FREQ_10BITS 10

#define MOTOR_L 0
#define MOTOR_R 1

void initMotor();
void setMotorDirAndSpeed(int p_motor, float p_pwm);
void testMotor();

#endif
