void initMotors(void) {
    pinMode(PIN_MOTOR_IN1, OUTPUT);
    pinMode(PIN_MOTOR_IN2, OUTPUT);
    pinMode(PIN_MOTOR_IN3, OUTPUT);
    pinMode(PIN_MOTOR_IN4, OUTPUT);
    pinMode(PIN_MOTOR_ENA, OUTPUT);
    pinMode(PIN_MOTOR_ENB, OUTPUT);

    setMotorDirection(MOTOR_A, MOTOR_STOP);
    setMotorDirection(MOTOR_B, MOTOR_STOP);
}

void setMotorDirection(uint8_t motor, MotorState state) {
    if (state == MOTOR_FRONT) {
        if (motor == MOTOR_A) {
            digitalWrite(PIN_MOTOR_IN3, LOW);
            digitalWrite(PIN_MOTOR_IN4, HIGH);
        }
        else if (motor == MOTOR_B) {
            digitalWrite(PIN_MOTOR_IN1, HIGH);
            digitalWrite(PIN_MOTOR_IN2, LOW);
        }
        else {
            return;
        }
    }
    else if (state == MOTOR_BACK) {
        if (motor == MOTOR_A) {
            digitalWrite(PIN_MOTOR_IN3, HIGH);
            digitalWrite(PIN_MOTOR_IN4, LOW);
        }
        else if (motor == MOTOR_B) {
            digitalWrite(PIN_MOTOR_IN1, LOW);
            digitalWrite(PIN_MOTOR_IN2, HIGH);
        }
        else {
            return;
        }
    }
    else if (state == MOTOR_STOP) {
        if (motor == MOTOR_A) {
            digitalWrite(PIN_MOTOR_IN3, LOW);
            digitalWrite(PIN_MOTOR_IN4, LOW);
        }
        else if (motor == MOTOR_B) {
            digitalWrite(PIN_MOTOR_IN1, LOW);
            digitalWrite(PIN_MOTOR_IN2, LOW);
        }
        else {
            return;
        }
    }
    else {
        return;
    }
}

void setMotorSpeed(uint8_t motor, int16_t speed) {
    speed = constrain(abs(speed), 0, 255);

    if (motor == MOTOR_A) {
        analogWrite(PIN_MOTOR_ENA, speed);
    }
    else if (motor == MOTOR_B) {
        analogWrite(PIN_MOTOR_ENB, speed);
    }
}

void testMotors(void) {
    while (Serial.available() > 0) {
        char ch = char(Serial.read());
        if (ch == 'w') {
            setMotorDirection(MOTOR_A, MOTOR_FRONT);
            setMotorDirection(MOTOR_B, MOTOR_FRONT);
        }
        else if (ch == 's') {
            setMotorDirection(MOTOR_A, MOTOR_BACK);
            setMotorDirection(MOTOR_B, MOTOR_BACK);
        }
        else if (ch == 'a') {
            setMotorDirection(MOTOR_A, MOTOR_FRONT);
            setMotorDirection(MOTOR_B, MOTOR_BACK);
        }
        else if (ch == 'd') {
            setMotorDirection(MOTOR_A, MOTOR_BACK);
            setMotorDirection(MOTOR_B, MOTOR_FRONT);
        }
        else if (ch == 'x') {
            setMotorDirection(MOTOR_A, MOTOR_STOP);
            setMotorDirection(MOTOR_B, MOTOR_STOP);
        }
        else if (ch == 'q') {
            g_motor_speed++;
            Serial.print("Speed: ");
            Serial.println(g_motor_speed);
        }
        else if (ch == 'e') {
            g_motor_speed--;
            Serial.print("Speed: ");
            Serial.println(g_motor_speed);
        }

        setMotorSpeed(MOTOR_A, g_motor_speed);
        setMotorSpeed(MOTOR_B, g_motor_speed);
    }
}

