#include "driver_motor.hpp"

void initMotor() {
    ledcAttach(PIN_MOTOR_L1, LEDC_FREQ_1000HZ, LEDC_RESO_10BITS);
    ledcAttach(PIN_MOTOR_L2, LEDC_FREQ_1000HZ, LEDC_RESO_10BITS);
    ledcAttach(PIN_MOTOR_R1, LEDC_FREQ_1000HZ, LEDC_RESO_10BITS);
    ledcAttach(PIN_MOTOR_R2, LEDC_FREQ_1000HZ, LEDC_RESO_10BITS);
}

void setMotorDirAndSpeed(uint8_t motor, float pwm) {
    if (motor == MOTOR_L) {
        if (pwm < 0) {
            ledcWrite(PIN_MOTOR_L1, -pwm);
            ledcWrite(PIN_MOTOR_L2, 0);
        }
        else {
            ledcWrite(PIN_MOTOR_L1, 0);
            ledcWrite(PIN_MOTOR_L2, pwm);
        }
    }
    else if (motor == MOTOR_R) {
        if (pwm < 0) {
            ledcWrite(PIN_MOTOR_R1, -pwm);
            ledcWrite(PIN_MOTOR_R2, 0);
        }
        else {
            ledcWrite(PIN_MOTOR_R1, 0);
            ledcWrite(PIN_MOTOR_R2, pwm);
        }
    }
    else {
        ;
    }
}

void testMotor() {
    setMotorDirAndSpeed(MOTOR_L, 1024);
    delay(1000);
    setMotorDirAndSpeed(MOTOR_L, 0);
    delay(1000);
    setMotorDirAndSpeed(MOTOR_R, 1024);
    delay(1000);
    setMotorDirAndSpeed(MOTOR_R, 1024);
}
