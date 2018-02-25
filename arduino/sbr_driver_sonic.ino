void initSonic(void)
{
    pinMode(PIN_TRIG, OUTPUT);
    pinMode(PIN_ECHO, INPUT);
}

float getSonicDistance(void)
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
