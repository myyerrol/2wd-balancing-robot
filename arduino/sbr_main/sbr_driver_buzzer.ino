#define NOTE_0  -1

#define NOTE_A1  441
#define NOTE_A2  495
#define NOTE_A3  556
#define NOTE_A4  589
#define NOTE_A5  661
#define NOTE_A6  742
#define NOTE_A7  833
#define NOTE_AL1 221
#define NOTE_AL2 248
#define NOTE_AL3 278
#define NOTE_AL4 294
#define NOTE_AL5 330
#define NOTE_AL6 371
#define NOTE_AL7 416
#define NOTE_AH1 882
#define NOTE_AH2 990
#define NOTE_AH3 1112
#define NOTE_AH4 1178
#define NOTE_AH5 1322
#define NOTE_AH6 1484
#define NOTE_AH7 1665

#define NOTE_B1  495
#define NOTE_B2  556
#define NOTE_B3  589
#define NOTE_B4  661
#define NOTE_B5  742
#define NOTE_B6  833
#define NOTE_B7  935
#define NOTE_BL1 248
#define NOTE_BL2 278
#define NOTE_BL3 294
#define NOTE_BL4 330
#define NOTE_BL5 371
#define NOTE_BL6 416
#define NOTE_BL7 467
#define NOTE_BH1 990
#define NOTE_BH2 1112
#define NOTE_BH3 1178
#define NOTE_BH4 1322
#define NOTE_BH5 1484
#define NOTE_BH6 1665
#define NOTE_BH7 1869

#define NOTE_C1  262
#define NOTE_C2  294
#define NOTE_C3  330
#define NOTE_C4  350
#define NOTE_C5  393
#define NOTE_C6  441
#define NOTE_C7  495
#define NOTE_CL1 131
#define NOTE_CL2 147
#define NOTE_CL3 165
#define NOTE_CL4 175
#define NOTE_CL5 196
#define NOTE_CL6 221
#define NOTE_CL7 248
#define NOTE_CH1 525
#define NOTE_CH2 589
#define NOTE_CH3 661
#define NOTE_CH4 700
#define NOTE_CH5 786
#define NOTE_CH6 882
#define NOTE_CH7 990

#define NOTE_D1  294
#define NOTE_D2  330
#define NOTE_D3  350
#define NOTE_D4  393
#define NOTE_D5  441
#define NOTE_D6  495
#define NOTE_D7  556
#define NOTE_DL1 147
#define NOTE_DL2 165
#define NOTE_DL3 175
#define NOTE_DL4 196
#define NOTE_DL5 221
#define NOTE_DL6 248
#define NOTE_DL7 278
#define NOTE_DH1 589
#define NOTE_DH2 661
#define NOTE_DH3 700
#define NOTE_DH4 786
#define NOTE_DH5 882
#define NOTE_DH6 990
#define NOTE_DH7 1112

#define NOTE_E1  330
#define NOTE_E2  350
#define NOTE_E3  393
#define NOTE_E4  441
#define NOTE_E5  495
#define NOTE_E6  556
#define NOTE_E7  624
#define NOTE_EL1 165
#define NOTE_EL2 175
#define NOTE_EL3 196
#define NOTE_EL4 221
#define NOTE_EL5 248
#define NOTE_EL6 278
#define NOTE_EL7 312
#define NOTE_EH1 661
#define NOTE_EH2 700
#define NOTE_EH3 786
#define NOTE_EH4 882
#define NOTE_EH5 990
#define NOTE_EH6 1112
#define NOTE_EH7 1248

#define NOTE_F1  350
#define NOTE_F2  393
#define NOTE_F3  441
#define NOTE_F4  495
#define NOTE_F5  556
#define NOTE_F6  624
#define NOTE_F7  661
#define NOTE_FL1 175
#define NOTE_FL2 196
#define NOTE_FL3 221
#define NOTE_FL4 234
#define NOTE_FL5 262
#define NOTE_FL6 294
#define NOTE_FL7 330
#define NOTE_FH1 700
#define NOTE_FH2 786
#define NOTE_FH3 882
#define NOTE_FH4 935
#define NOTE_FH5 1049
#define NOTE_FH6 1178
#define NOTE_FH7 1322

#define NOTE_G1  393
#define NOTE_G2  441
#define NOTE_G3  495
#define NOTE_G4  556
#define NOTE_G5  624
#define NOTE_G6  661
#define NOTE_G7  742
#define NOTE_GL1 196
#define NOTE_GL2 221
#define NOTE_GL3 234
#define NOTE_GL4 262
#define NOTE_GL5 294
#define NOTE_GL6 330
#define NOTE_GL7 371
#define NOTE_GH1 786
#define NOTE_GH2 882
#define NOTE_GH3 990
#define NOTE_GH4 1049
#define NOTE_GH5 1178
#define NOTE_GH6 1322
#define NOTE_GH7 1484

#define MUSIC_RYD

#ifndef MUSIC_HLH
#ifndef MUSIC_RYD
// 《欢乐颂》曲谱
int tune[] = {
    NOTE_D3, NOTE_D3, NOTE_D4,  NOTE_D5,
    NOTE_D5, NOTE_D4, NOTE_D3,  NOTE_D2,
    NOTE_D1, NOTE_D1, NOTE_D2,  NOTE_D3,
    NOTE_D3, NOTE_D2, NOTE_D2,
    NOTE_D3, NOTE_D3, NOTE_D4,  NOTE_D5,
    NOTE_D5, NOTE_D4, NOTE_D3,  NOTE_D2,
    NOTE_D1, NOTE_D1, NOTE_D2,  NOTE_D3,
    NOTE_D2, NOTE_D1, NOTE_D1,
    NOTE_D2, NOTE_D2, NOTE_D3,  NOTE_D1,
    NOTE_D2, NOTE_D3, NOTE_D4,  NOTE_D3, NOTE_D1,
    NOTE_D2, NOTE_D3, NOTE_D4,  NOTE_D3, NOTE_D2,
    NOTE_D1, NOTE_D2, NOTE_DL5, NOTE_0,
    NOTE_D3, NOTE_D3, NOTE_D4,  NOTE_D5,
    NOTE_D5, NOTE_D4, NOTE_D3,  NOTE_D4, NOTE_D2,
    NOTE_D1, NOTE_D1, NOTE_D2,  NOTE_D3,
    NOTE_D2, NOTE_D1, NOTE_D1
};
float durt[] = {
    1, 1, 1, 1,
    1, 1, 1, 1,
    1, 1, 1, 1,
    1+0.5, 0.5, 1+1,
    1, 1, 1, 1,
    1, 1, 1, 1,
    1, 1, 1, 1,
    1+0.5, 0.5, 1+1,
    1, 1, 1, 1,
    1, 0.5, 0.5, 1, 1,
    1, 0.5, 0.5, 1, 1,
    1, 1, 1, 1,
    1, 1, 1, 1,
    1, 1, 1, 0.5, 0.5,
    1, 1, 1, 1,
    1+0.5, 0.5, 1+1,
};
int speed = 500;
#endif
#endif

#ifdef MUSIC_HLH
// 《紅蓮華》曲谱
int tune[] = {
    NOTE_G6, NOTE_GH1, NOTE_G7, NOTE_G5, NOTE_G5, NOTE_G6, NOTE_G5,

    NOTE_0, NOTE_G2, NOTE_G1, NOTE_G1, NOTE_G2, NOTE_G4,
    NOTE_G3, NOTE_GL6, NOTE_0, NOTE_0,
    NOTE_0, NOTE_GL6, NOTE_G1, NOTE_G2, NOTE_G3, NOTE_G2, NOTE_G3, NOTE_G5,
    NOTE_G6, NOTE_GH1, NOTE_G7, NOTE_G5, NOTE_G6, NOTE_G5,

    NOTE_G5, NOTE_G5, NOTE_GH3, NOTE_GH2, NOTE_GH3, NOTE_GH2, NOTE_GH3, NOTE_GH4, NOTE_GH3,
    NOTE_GH1, NOTE_0, NOTE_0, NOTE_0, NOTE_GH1,
    NOTE_G7, NOTE_G7, NOTE_GH1, NOTE_GH2, NOTE_0, NOTE_GH1,
    NOTE_GH2, NOTE_GH1, NOTE_G6, NOTE_GH1, NOTE_GH3, NOTE_GH2,

    NOTE_G2, NOTE_G2, NOTE_G2, NOTE_G2, NOTE_G2, NOTE_G3, NOTE_GH1,
    NOTE_GH2, NOTE_GH1, NOTE_G6, NOTE_GH1, NOTE_GH5,
    NOTE_G2, NOTE_G2, NOTE_G1, NOTE_G2, NOTE_GL7, NOTE_GH1,
    NOTE_GH2, NOTE_GH1, NOTE_G6, NOTE_GH1, NOTE_GH3, NOTE_GH2,

    NOTE_0, NOTE_GH2, NOTE_GH3, NOTE_GH2, NOTE_GH3, NOTE_GH5, NOTE_GH3,
    NOTE_GH2, NOTE_GH1, NOTE_GL6, NOTE_GL7, NOTE_G1, NOTE_G2, NOTE_G3, NOTE_G5, NOTE_GH1,
    NOTE_G7, NOTE_G7, NOTE_GH1, NOTE_GH2, NOTE_0,
    NOTE_GH1, NOTE_G7, NOTE_GH1,

    NOTE_GH1, NOTE_G7, NOTE_GH1, NOTE_0, NOTE_G5,
    NOTE_GH1, NOTE_G7, NOTE_G6, NOTE_G5,
    NOTE_0, NOTE_G3, NOTE_G5,
    NOTE_G6, NOTE_0, NOTE_G6, NOTE_GH1,

    NOTE_GH2, NOTE_0, NOTE_GH1, NOTE_GH2,
    NOTE_GH3, NOTE_G2, NOTE_G3, NOTE_G5, NOTE_G6, NOTE_G7, NOTE_GH1, NOTE_G7,
    NOTE_0, NOTE_G5, NOTE_G5, NOTE_GH3,
    NOTE_GH2, NOTE_GH3, NOTE_GH5, NOTE_GH3, NOTE_GH2, NOTE_GH3, NOTE_GH3, NOTE_0, NOTE_GH1,

    NOTE_GH2, NOTE_GH3, NOTE_GH5, NOTE_GH3, NOTE_GH2, NOTE_GH3, NOTE_GH3, NOTE_0, NOTE_GL5,
    NOTE_GL5, NOTE_G1, NOTE_G1, NOTE_GL5, NOTE_GL5, NOTE_G1, NOTE_G2, NOTE_G1,
    NOTE_G5, NOTE_G4, NOTE_G3, NOTE_G2, NOTE_G1,
    NOTE_G1, NOTE_0, NOTE_GH1, NOTE_GH2, NOTE_GH3, NOTE_GH2,

    NOTE_0, NOTE_G5, NOTE_GH2, NOTE_GH3, NOTE_GH5, NOTE_GH3,
    NOTE_GL6, NOTE_GL5, NOTE_GL6, NOTE_GL5, NOTE_G6, NOTE_G6, NOTE_G6, NOTE_G6,
    NOTE_GL3, NOTE_GL2, NOTE_G5, NOTE_G5, NOTE_GH3,
    NOTE_GH2, NOTE_GH3, NOTE_GH5, NOTE_GH3, NOTE_GH2, NOTE_GH3, NOTE_GH3, NOTE_0, NOTE_GH1, NOTE_GH1,

    NOTE_GH2, NOTE_GH3, NOTE_GH5, NOTE_GH3, NOTE_GH2, NOTE_GH3, NOTE_GH1, NOTE_0, NOTE_GH1,
    NOTE_GH1, NOTE_GH2, NOTE_GH3, NOTE_GH3, NOTE_0, NOTE_GH7,
    NOTE_GH5, NOTE_GH3, NOTE_GH2, NOTE_GH2, NOTE_GH1,

    NOTE_GH1, NOTE_0, NOTE_GH1, NOTE_GH2, NOTE_GH3, NOTE_GH2,
    NOTE_0, NOTE_0, NOTE_GH2, NOTE_GH2, NOTE_GH2,
    NOTE_GH3, NOTE_G5, NOTE_G6, NOTE_G5, NOTE_G6, NOTE_G6
};
float durt[] = {
    0.5+0.25, 0.25+0.5, 0.5, 0.5, 0.5, 0.5+0.25, 0.25 + 1,

    1, 0.5, 0.25, 0.25, 0.5, 0.5,
    0.5, 1+0.5, 1, 1,
    0.5, 0.5, 0.25, 0.5, 0.25+0.5, 0.5, 0.5, 0.5,
    0.5+0.25, 0.25+0.5, 0.5+0.5, 0.5, 0.5+0.25, 0.25+1,

    0.5, 0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.5, 0.25, 0.25+0.25,
    0.5+0.25, 1, 1, 0.5, 0.5,
    0.5+0.25, 0.25+0.5, 0.5, 1, 0.5, 0.5,
    0.5+0.25, 0.25+0.5, 0.5+0.25, 0.5+0.25, 0.5+0.25, 0.25+0.5,

    0.5, 0.5, 0.5, 0.25, 0.5, 0.25+0.5, 0.5,
    0.5+0.25, 0.25+0.5, 0.5+0.5, 0.5, 1+0.5,
    0.5, 0.5, 0.5, 0.5+0.25, 0.25+0.5, 0.5,
    0.5+0.25, 0.25+0.5, 0.5+0.5, 0.5, 0.5+0.25, 0.25+0.5,

    0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5,
    0.5+0.25, 0.25+0.5, 0.5+0.25, 0.25, 0.25, 0.25, 0.25, 0.25, 0.5,
    0.5+0.25, 0.25+0.5, 0.5, 1, 1,
    0.5+0.25, 0.25+0.5, 0.5+1+1,

    0.5+0.25, 0.25+0.5, 0.5+1, 0.5, 0.5,
    0.5+0.25, 0.25+0.5, 0.5+1+0.5, 0.5+1+1,
    0.5, 1, 0.5,
    1+1, 0.5, 1, 0.5,

    1+1, 0.5, 1, 0.5,
    0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5,
    1, 1, 1, 1,
    0.5, 0.5, 0.5, 0.5, 0.5, 0.25, 0.25, 0.5, 0.5,

    0.5, 0.5, 0.5, 0.5, 0.5, 0.25, 0.25, 0.5, 0.5,
    0.5, 0.25, 0.25+0.5, 0.5, 0.5, 0.5, 0.5, 0.5,
    1, 1, 0.5+0.25, 0.25+0.5, 0.5,
    1, 0.5, 0.5+0.5, 0.5, 0.5, 0.5,

    1, 0.5, 0.5+0.5, 0.5, 0.5, 0.5,
    0.5+0.25, 0.25+0.5, 0.5+0.25, 0.5+0.25, 0.25, 0.25, 0.25, 0.25,
    0.5+0.25, 0.25, 1, 1, 1,
    0.5, 0.5, 0.5, 0.5, 0.5, 0.25, 0.25, 0.5, 0.25, 0.25,

    0.5, 0.5, 0.5, 0.5, 0.5, 0.25, 0.25, 0.5, 0.5,
    1, 0.5, 0.5+0.5, 0.5, 0.5, 0.5+1,
    1, 0.5+0.25, 0.25, 0.5, 0.5,

    1, 0.5, 0.5+0.5, 0.5, 0.5, 0.5,
    1, 0.5, 0.5, 1, 1,
    0.5+0.25, 0.25+0.5, 0.5+0.25, 0.5+0.25, 0.5, 0.5
};
int speed = 380;
#endif

#ifdef MUSIC_RYD
// 《Rage Your Dream》曲谱
int tune[] = {
    NOTE_E3, NOTE_E5,
    NOTE_E6, NOTE_E6, NOTE_EH1, NOTE_E6, NOTE_EH1,
    NOTE_E7, NOTE_E5, NOTE_E3, NOTE_E5, NOTE_E4, NOTE_E5,
    NOTE_E6, NOTE_E1, NOTE_E6, NOTE_E2, NOTE_E1, NOTE_E2,

    NOTE_E3, NOTE_E7, NOTE_E5, NOTE_E5, NOTE_E3, NOTE_E5,
    NOTE_E6, NOTE_E6, NOTE_EH1, NOTE_E6, NOTE_EH1,
    NOTE_E7, NOTE_E5, NOTE_E5, NOTE_E3, NOTE_E5, NOTE_E3,
    NOTE_E4, NOTE_E4, NOTE_E5, NOTE_E5,

    NOTE_EH1, NOTE_EH1, NOTE_EH1
};
float durt[] = {
    0.5, 0.5,
    1, 0.5, 0.5, 1+0.5, 0.5,
    1, 0.5, 0.5, 1, 0.5, 0.5,
    1, 0.5, 0.5, 1, 0.5, 0.5,

    1, 0.5, 0.5, 1, 0.5, 0.5,
    1, 0.5, 0.5, 1+0.5, 0.5,
    0.5, 0.5, 0.5, 0.5, 1, 1,
    1+0.5, 0.5, 1, 1,
    1+0.5, 0.5, 1+1
};
int speed = 450;
#endif

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
    for(uint8_t i = 0; i < sizeof(tune) / sizeof(tune[0]); i++) {
        tone(PIN_BUZZER, tune[i]);
        delay(speed * durt[i]);
        noTone(PIN_BUZZER);
    }
}

void playBuzzerSound(uint8_t freq, uint8_t time) {
    tone(PIN_BUZZER, freq);
    delay(time);
    noTone(PIN_BUZZER);
}
