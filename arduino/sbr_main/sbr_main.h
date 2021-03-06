#ifndef SBR_MAIN_H
#define SBR_MAIN_H

// 电机定义
#define MOTOR_A               0
#define MOTOR_B               1

// 蜂鸣器
#define NOTE_0                -1
#define NOTE_A1               441
#define NOTE_A2               495
#define NOTE_A3               556
#define NOTE_A4               589
#define NOTE_A5               661
#define NOTE_A6               742
#define NOTE_A7               833
#define NOTE_AL1              221
#define NOTE_AL2              248
#define NOTE_AL3              278
#define NOTE_AL4              294
#define NOTE_AL5              330
#define NOTE_AL6              371
#define NOTE_AL7              416
#define NOTE_AH1              882
#define NOTE_AH2              990
#define NOTE_AH3              1112
#define NOTE_AH4              1178
#define NOTE_AH5              1322
#define NOTE_AH6              1484
#define NOTE_AH7              1665
#define NOTE_B1               495
#define NOTE_B2               556
#define NOTE_B3               589
#define NOTE_B4               661
#define NOTE_B5               742
#define NOTE_B6               833
#define NOTE_B7               935
#define NOTE_BL1              248
#define NOTE_BL2              278
#define NOTE_BL3              294
#define NOTE_BL4              330
#define NOTE_BL5              371
#define NOTE_BL6              416
#define NOTE_BL7              467
#define NOTE_BH1              990
#define NOTE_BH2              1112
#define NOTE_BH3              1178
#define NOTE_BH4              1322
#define NOTE_BH5              1484
#define NOTE_BH6              1665
#define NOTE_BH7              1869
#define NOTE_C1               262
#define NOTE_C2               294
#define NOTE_C3               330
#define NOTE_C4               350
#define NOTE_C5               393
#define NOTE_C6               441
#define NOTE_C7               495
#define NOTE_CL1              131
#define NOTE_CL2              147
#define NOTE_CL3              165
#define NOTE_CL4              175
#define NOTE_CL5              196
#define NOTE_CL6              221
#define NOTE_CL7              248
#define NOTE_CH1              525
#define NOTE_CH2              589
#define NOTE_CH3              661
#define NOTE_CH4              700
#define NOTE_CH5              786
#define NOTE_CH6              882
#define NOTE_CH7              990
#define NOTE_D1               294
#define NOTE_D2               330
#define NOTE_D3               350
#define NOTE_D4               393
#define NOTE_D5               441
#define NOTE_D6               495
#define NOTE_D7               556
#define NOTE_DL1              147
#define NOTE_DL2              165
#define NOTE_DL3              175
#define NOTE_DL4              196
#define NOTE_DL5              221
#define NOTE_DL6              248
#define NOTE_DL7              278
#define NOTE_DH1              589
#define NOTE_DH2              661
#define NOTE_DH3              700
#define NOTE_DH4              786
#define NOTE_DH5              882
#define NOTE_DH6              990
#define NOTE_DH7              1112
#define NOTE_E1               330
#define NOTE_E2               350
#define NOTE_E3               393
#define NOTE_E4               441
#define NOTE_E5               495
#define NOTE_E6               556
#define NOTE_E7               624
#define NOTE_EL1              165
#define NOTE_EL2              175
#define NOTE_EL3              196
#define NOTE_EL4              221
#define NOTE_EL5              248
#define NOTE_EL6              278
#define NOTE_EL7              312
#define NOTE_EH1              661
#define NOTE_EH2              700
#define NOTE_EH3              786
#define NOTE_EH4              882
#define NOTE_EH5              990
#define NOTE_EH6              1112
#define NOTE_EH7              1248
#define NOTE_F1               350
#define NOTE_F2               393
#define NOTE_F3               441
#define NOTE_F4               495
#define NOTE_F5               556
#define NOTE_F6               624
#define NOTE_F7               661
#define NOTE_FL1              175
#define NOTE_FL2              196
#define NOTE_FL3              221
#define NOTE_FL4              234
#define NOTE_FL5              262
#define NOTE_FL6              294
#define NOTE_FL7              330
#define NOTE_FH1              700
#define NOTE_FH2              786
#define NOTE_FH3              882
#define NOTE_FH4              935
#define NOTE_FH5              1049
#define NOTE_FH6              1178
#define NOTE_FH7              1322
#define NOTE_G1               393
#define NOTE_G2               441
#define NOTE_G3               495
#define NOTE_G4               556
#define NOTE_G5               624
#define NOTE_G6               661
#define NOTE_G7               742
#define NOTE_GL1              196
#define NOTE_GL2              221
#define NOTE_GL3              234
#define NOTE_GL4              262
#define NOTE_GL5              294
#define NOTE_GL6              330
#define NOTE_GL7              371
#define NOTE_GH1              786
#define NOTE_GH2              882
#define NOTE_GH3              990
#define NOTE_GH4              1049
#define NOTE_GH5              1178
#define NOTE_GH6              1322
#define NOTE_GH7              1484

#define OLED_WIDTH            128
#define OLED_HEIGHT           64
#define OLED_RESET            -1
#define OLED_LOGO_WIDTH       16
#define OLED_LOGO_HEIGHT      16

#define PIN_LED               13
#define PIN_BUZZER            A0
#define PIN_ECHO              A1
#define PIN_TRIG              A2
#define PIN_IIC_SCL           A5
#define PIN_IIC_SDA           A4
#define PIN_SPI_MOSI          11
#define PIN_SPI_MISO          12
#define PIN_RXD               0
#define PIN_TXD               1
#define PIN_ENCODER_A_C1      2
#define PIN_ENCODER_A_C2      4
#define PIN_ENCODER_B_C1      3
#define PIN_ENCODER_B_C2      A3
#define PIN_MOTOR_IN1         5
#define PIN_MOTOR_IN2         6
#define PIN_MOTOR_IN3         7
#define PIN_MOTOR_IN4         8
#define PIN_MOTOR_ENA         9
#define PIN_MOTOR_ENB         10

#define REG_WHO_AM_I          0x75
#define REG_PWR_MGMT_1        0x6B
#define REG_PWR_MGMT_2        0x6C
#define REG_SIGNAL_PATH_RESET 0x68
#define REG_SMPLRT_DIV        0x19
#define REG_CONFIG            0x1A
#define REG_GYRO_CONFIG       0x1B
#define REG_ACCEL_CONFIG      0x1C
#define REG_ACCEL_CONFIG_2    0x1D

#define STATE_STARTUP         0x0001
#define STATE_TURNING         0x0002
#define STATE_FALLDOWN        0x0004
#define STATE_EC_A_CHANGE     0x0008
#define STATE_EC_B_CHANGE     0x0010
#define STATE_SERIAL_END      0x0020
#define STATE_REMOTE_CONTROL  0x0040

#define TIMEOUT_SONIC         3000
#define TIMEOUT_IIC           1000

#define LED_ON  digitalWrite(PIN_LED, HIGH);
#define LED_OFF digitalWrite(PIN_LED, LOW);

enum MotionState {
    Motion_FRONT,
    Motion_BACK,
    Motion_LEFT,
    Motion_RIGHT,
    Motion_STOP
};

enum MotorState {
    MOTOR_FRONT,
    MOTOR_BACK,
    MOTOR_STOP
};

typedef union EEPROMStruct {
    uint8_t bytes[4];
    double  angle;
} EEPROMStruct;

void analyzeSerialData(void);
void calculateAnglePID(void);
void calculateSpeedPID(void);
void countEncoderA(void);
void countEncoderB(void);
void filterIMUData(void);
void getSerialData(void);
void initBuzzer(void);
void initEEPROM(void);
void initEncoders(void);
void initLED(void);
void initIMU(void);
void initMotors(void);
void initOLED(void);
void initSerial(void);
void initSonic(void);
void runSonic(void);
void setMotorDirection(uint8_t motor, MotorState state);
void setMotorSpeed(uint8_t motor, int16_t speed);
void showSelfCheckingInfo(void);
void playBuzzerAlert(uint8_t num);
void playBuzzerSound(uint8_t freq, uint8_t time);
void playBuzzerMusic(void);
void writeDataToEEPROM(void);
uint8_t readDataFromIIC(uint8_t address, uint8_t *data, uint8_t bytes);
uint8_t writeDataToIIC(uint8_t address, uint8_t data, bool stop_flag);
uint8_t writeDataToIIC(uint8_t address, uint8_t *data, uint8_t length,
                       bool stop_flag);
float getSonicData(void);

#endif // SBR_MAIN_H
