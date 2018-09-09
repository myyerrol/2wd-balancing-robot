void initMotors(void)
{
    pinMode(PIN_MOTOR_IN1, OUTPUT);
    pinMode(PIN_MOTOR_IN2, OUTPUT);
    pinMode(PIN_MOTOR_IN3, OUTPUT);
    pinMode(PIN_MOTOR_IN4, OUTPUT);
    pinMode(PIN_MOTOR_ENA, OUTPUT);
    pinMode(PIN_MOTOR_ENB, OUTPUT);

    setMotorDirection(MOTOR_A, MOTOR_STOP);
    setMotorDirection(MOTOR_B, MOTOR_STOP);
}

void setMotor(uint8_t motor, int16_t speed)
{
    if (motor == MOTOR_A) {
        // Move front.
        if (speed > 0) {
            digitalWrite(PIN_MOTOR_IN1, HIGH);
            digitalWrite(PIN_MOTOR_IN2, LOW);
            analogWrite(PIN_MOTOR_ENA, 255 - speed);
        }
        // Move back.
        else {
            digitalWrite(PIN_MOTOR_IN1, LOW);
            digitalWrite(PIN_MOTOR_IN2, HIGH);
            analogWrite(PIN_MOTOR_ENA, speed);
        }
    }
    else if (motor == MOTOR_B) {
        // Move front.
        if (speed > 0) {
            digitalWrite(PIN_MOTOR_IN3, LOW);
            digitalWrite(PIN_MOTOR_IN4, HIGH);
            analogWrite(PIN_MOTOR_ENB, 255 - speed);
        }
        // Move back.
        else {
            digitalWrite(PIN_MOTOR_IN3, HIGH);
            digitalWrite(PIN_MOTOR_IN4, LOW);
            analogWrite(PIN_MOTOR_ENB, speed);
        }
    }
    else {
        return;
    }
}

void setMotorDirection(uint8_t motor, MotorState state)
{
    if (state == MOTOR_FRONT) {
        if (motor == MOTOR_A) {
            digitalWrite(PIN_MOTOR_IN1, HIGH);
            digitalWrite(PIN_MOTOR_IN2, LOW);
        }
        else if (motor == MOTOR_B) {
            digitalWrite(PIN_MOTOR_IN3, LOW);
            digitalWrite(PIN_MOTOR_IN4, HIGH);
        }
        else {
            return;
        }
    }
    else if (state == MOTOR_BACK) {
        if (motor == MOTOR_A) {
            digitalWrite(PIN_MOTOR_IN1, LOW);
            digitalWrite(PIN_MOTOR_IN2, HIGH);
        }
        else if (motor == MOTOR_B) {
            digitalWrite(PIN_MOTOR_IN3, HIGH);
            digitalWrite(PIN_MOTOR_IN4, LOW);
        }
        else {
            return;
        }
    }
    else if (state == MOTOR_STOP) {
        if (motor == MOTOR_A) {
            digitalWrite(PIN_MOTOR_IN1, LOW);
            digitalWrite(PIN_MOTOR_IN2, LOW);
        }
        else if (motor == MOTOR_B) {
            digitalWrite(PIN_MOTOR_IN3, LOW);
            digitalWrite(PIN_MOTOR_IN4, LOW);
        }
        else {
            return;
        }
    }
    else {
        return;
    }
}

void setMotorSpeed(uint8_t motor, int16_t speed)
{
    if (speed > 0) {
        if (motor == MOTOR_A) {
            analogWrite(PIN_MOTOR_ENA, speed);
        }
        else if (motor == MOTOR_B) {
            analogWrite(PIN_MOTOR_ENB, speed);
        }
    }
    else if (speed < 0) {
        if (motor == MOTOR_A) {
            analogWrite(PIN_MOTOR_ENA, -speed - 50);
        }
        else if (motor == MOTOR_B) {
            analogWrite(PIN_MOTOR_ENB, -speed - 50);
        }
    }

}
