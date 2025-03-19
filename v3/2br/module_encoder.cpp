#include "module_encoder.hpp"

volatile int g_encoder_l_cnt = 0;
volatile int g_encoder_r_cnt = 0;

static void handleEncoderLPhaseA() {
    if (digitalRead(ENCODER_PIN_L2) == HIGH) {
        g_encoder_l_cnt++;
    }
    else {
        g_encoder_l_cnt--;
    }
}

static void handleEncoderLPhaseB() {
    if (digitalRead(ENCODER_PIN_L1) == LOW) {
        g_encoder_l_cnt++;
    }
    else {
        g_encoder_l_cnt--;
    }
}

static void handleEncoderRPhaseA() {
    if (digitalRead(ENCODER_PIN_R2) == LOW) {
        g_encoder_r_cnt++;
    }
    else {
        g_encoder_r_cnt--;
    }
}

static void handleEncoderRPhaseB() {
    if (digitalRead(ENCODER_PIN_R1) == HIGH) {
        g_encoder_r_cnt++;
    }
    else {
        g_encoder_r_cnt--;
    }
}

void initEncoder() {
    pinMode(ENCODER_PIN_L1, INPUT);
    pinMode(ENCODER_PIN_L2, INPUT);
    pinMode(ENCODER_PIN_R1, INPUT);
    pinMode(ENCODER_PIN_R2, INPUT);

    attachInterrupt(ENCODER_PIN_L1, handleEncoderLPhaseA, RISING);
    attachInterrupt(ENCODER_PIN_L2, handleEncoderLPhaseB, RISING);
    attachInterrupt(ENCODER_PIN_R1, handleEncoderRPhaseA, RISING);
    attachInterrupt(ENCODER_PIN_R2, handleEncoderRPhaseB, RISING);
    interrupts();

    g_encoder_r_cnt = 0;
    g_encoder_l_cnt = 0;
}

void readEncoder(int *p_encoder_l, int *p_encoder_r) {
    *p_encoder_l = g_encoder_l_cnt;
    *p_encoder_r = g_encoder_r_cnt;

#ifndef DEBUG_ENCODER
    g_encoder_r_cnt = 0;
    g_encoder_l_cnt = 0;
#endif
}

void testEncoder() {
    int t_encoder_l;
    int t_encoder_r;
    readEncoder(&t_encoder_l, &t_encoder_r);
    Serial.print("Encoder L: ");
    Serial.print(t_encoder_l);
    Serial.print(" ");
    Serial.print("Encoder R: ");
    Serial.print(t_encoder_r);
    Serial.print("\n");
}
