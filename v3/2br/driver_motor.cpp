#include "driver_motor.hpp"

void initMotor() {
    ledcAttach(PIN_MOTOR_L1, LEDC_FREQ_1000HZ, LEDC_RESO_10BITS);
    ledcAttach(PIN_MOTOR_L2, LEDC_FREQ_1000HZ, LEDC_RESO_10BITS);
    ledcAttach(PIN_MOTOR_R1, LEDC_FREQ_1000HZ, LEDC_RESO_10BITS);
    ledcAttach(PIN_MOTOR_R2, LEDC_FREQ_1000HZ, LEDC_RESO_10BITS);
}

void setMotorDirAndSpeed(int motor, float pwm) {
    pwm = (int)pwm;
    if (motor == MOTOR_L) {
        if (pwm < 0) {
            ledcWrite(PIN_MOTOR_L1, 0);
            ledcWrite(PIN_MOTOR_L2, -pwm);
        }
        else {
            ledcWrite(PIN_MOTOR_L1, pwm);
            ledcWrite(PIN_MOTOR_L2, 0);
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
    int speed_arr[] = {1024, 0, -1024, 0, 512, 0};

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < ARR_LEN(speed_arr); j++) {
            setMotorDirAndSpeed(i, speed_arr[j]);
            delay(1000);
        }
    }
}
