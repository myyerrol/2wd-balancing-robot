void countEncoderA(void)
{
    if (micros() - g_timer_encoder_a > 1000) {
        if (digitalRead(PIN_ENCODER_A_C2) == HIGH) {
            g_count_encoder_a++;
        }
        else if (digitalRead(PIN_ENCODER_A_C2 == LOW)) {
            g_count_encoder_a--;
        }
        else {
            return;
        }
        g_timer_encoder_a = micros();

    }
}

void countEncoderB(void)
{
    if (digitalRead(PIN_ENCODER_B_C2) == HIGH) {
        g_count_encoder_b++;
    }
    else if (digitalRead(PIN_ENCODER_B_C2 == LOW)) {
        g_count_encoder_b--;
    }
    else {
        return;
    }
}

void initEncoders(void)
{
    pinMode(PIN_ENCODER_A_C1, INPUT);
    pinMode(PIN_ENCODER_A_C2, INPUT);
    pinMode(PIN_ENCODER_B_C1, INPUT);
    pinMode(PIN_ENCODER_B_C2, INPUT);

    attachInterrupt(digitalPinToInterrupt(2), countEncoderA, FALLING);
    attachInterrupt(digitalPinToInterrupt(3), countEncoderB, FALLING);
}
