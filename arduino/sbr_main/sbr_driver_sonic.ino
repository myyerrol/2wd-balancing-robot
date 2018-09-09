void initSonic(void)
{
    pinMode(PIN_TRIG, OUTPUT);
    pinMode(PIN_ECHO, INPUT);
}

void runSonic(void)
{
    float distance = getSonicData();
    g_timer_sonic  = micros();
#ifdef DEBUG_SONIC
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.print("cm\n");
#endif
    if (!(g_robot_state & STATE_REMOTE_CONTROL)) {
        if (distance > 10 && distance < 15) {
            g_speed_setpoint = 30;
            LED_ON;
        }
        else if (distance > 0 && distance < 8) {
            g_speed_setpoint = -30;
            LED_ON;
        }
        else {
            g_speed_setpoint = 0;
            LED_OFF;
        }
    }

    calculateAnglePID();
}

float getSonicData(void)
{
    float duration = 0.0;
    float distance = 0.0;

    digitalWrite(PIN_TRIG, LOW);
    delayMicroseconds(10);
    digitalWrite(PIN_TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(PIN_TRIG, LOW);

    duration = pulseIn(PIN_ECHO, HIGH, TIMEOUT_SONIC);

    if (duration == 0.0) {
        return 0.0;
    }
    else {
        distance = duration * 0.017;
        return distance;
    }
}
