#include "module_motor.hpp"

void initMotor() {
    ledcAttach(MOTOR_PIN_L1, MOTOR_FREQ_1000HZ, MOTOR_FREQ_10BITS);
    ledcAttach(MOTOR_PIN_L2, MOTOR_FREQ_1000HZ, MOTOR_FREQ_10BITS);
    ledcAttach(MOTOR_PIN_R1, MOTOR_FREQ_1000HZ, MOTOR_FREQ_10BITS);
    ledcAttach(MOTOR_PIN_R2, MOTOR_FREQ_1000HZ, MOTOR_FREQ_10BITS);
}

void setMotorDirAndSpeed(int p_motor, float p_pwm) {
    p_pwm = (int)p_pwm;
    if (p_motor == MOTOR_L) {
        if (p_pwm < 0) {
            ledcWrite(MOTOR_PIN_L1, 0);
            ledcWrite(MOTOR_PIN_L2, -p_pwm);
        }
        else {
            ledcWrite(MOTOR_PIN_L1, p_pwm);
            ledcWrite(MOTOR_PIN_L2, 0);
        }
    }
    else if (p_motor == MOTOR_R) {
        if (p_pwm < 0) {
            ledcWrite(MOTOR_PIN_R1, -p_pwm);
            ledcWrite(MOTOR_PIN_R2, 0);
        }
        else {
            ledcWrite(MOTOR_PIN_R1, 0);
            ledcWrite(MOTOR_PIN_R2, p_pwm);
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
