void countEncoderA(void) {
    if (micros() - g_timer_encoder_a > 1000) {
        // Turn A wheel forward.
        if (digitalRead(PIN_ENCODER_A_C2) == LOW) {
            g_count_encoder_a++;
        }
        // Turn A wheel backward.
        else if (digitalRead(PIN_ENCODER_A_C2 == HIGH)) {
            g_count_encoder_a--;
        }
        else {
            return;
        }
        g_timer_encoder_a = micros();
        g_robot_state |= STATE_EC_A_CHANGE;
    }

#ifdef DEBUG_ENCODERS
    Serial.print("Encoder a: ");
    Serial.println(g_count_encoder_a);
#endif
}

void countEncoderB(void) {
    if (micros() - g_timer_encoder_b > 1000) {
        // Turn B wheel forward.
        if (digitalRead(PIN_ENCODER_B_C2) == HIGH) {
            g_count_encoder_b++;
        }
        // Turn B wheel backward.
        else if (digitalRead(PIN_ENCODER_B_C2 == LOW)) {
            g_count_encoder_b--;
        }
        else {
            return;
        }
        g_timer_encoder_b = micros();
        g_robot_state |= STATE_EC_B_CHANGE;
    }

#ifdef DEBUG_ENCODERS
    Serial.print("Encoder b: ");
    Serial.println(g_count_encoder_b);
#endif
}

void initEncoder(void)
{
    pinMode(PIN_ENCODER_A_C1, INPUT);
    pinMode(PIN_ENCODER_A_C2, INPUT);
    pinMode(PIN_ENCODER_B_C1, INPUT);
    pinMode(PIN_ENCODER_B_C2, INPUT);

    attachInterrupt(digitalPinToInterrupt(2), countEncoderA, FALLING);
    attachInterrupt(digitalPinToInterrupt(3), countEncoderB, FALLING);
}
