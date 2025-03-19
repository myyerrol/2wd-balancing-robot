void initBuzzer(void) {
    pinMode(PIN_BUZZER, OUTPUT);
    playBuzzerSound(1000, 3000);
}

void playBuzzerAlert(uint8_t num) {
    for(uint8_t i = 0; i < num; i++) {
        for (uint8_t j = 0; j < 80; j++) {
            digitalWrite(PIN_BUZZER, HIGH);
            delay(1);
            digitalWrite(PIN_BUZZER, LOW);
            delay(1);
        }
        for (uint8_t j = 0; j < 100; j++) {
            digitalWrite(PIN_BUZZER, HIGH);
            delay(2);
            digitalWrite(PIN_BUZZER, LOW);
            delay(2);
        }
    }
}

void playBuzzerMusic(void) {
    uint8_t length = sizeof(g_buzzer_tune) / sizeof(g_buzzer_tune[0]);
    for (uint8_t i = 0; i < length; i++) {
        tone(PIN_BUZZER, g_buzzer_tune[i]);
        delay(g_buzzer_speed * g_buzzer_durt[i]);
        noTone(PIN_BUZZER);
    }
}

void playBuzzerSound(uint16_t freq, uint16_t time) {
    tone(PIN_BUZZER, freq);
    delay(time);
    noTone(PIN_BUZZER);
}
