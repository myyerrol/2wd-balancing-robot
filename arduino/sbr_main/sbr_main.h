#ifndef SBR_MAIN_H
#define SBR_MAIN_H

#define PIN_LED              13
#define PIN_BUZZER           A0
#define PIN_ECHO             A1
#define PIN_TRIG             A2
#define PIN_IIC_SCL          A5
#define PIN_IIC_SDA          A4
#define PIN_SPI_MOSI         11
#define PIN_SPI_MISO         12
#define PIN_RXD              0
#define PIN_TXD              1
#define PIN_ENCODER_A_C1     2
#define PIN_ENCODER_A_C2     4
#define PIN_ENCODER_B_C1     3
#define PIN_ENCODER_B_C2     A3
#define PIN_MOTOR_IN1        5
#define PIN_MOTOR_IN2        6
#define PIN_MOTOR_IN3        7
#define PIN_MOTOR_IN4        8
#define PIN_MOTOR_ENA        9
#define PIN_MOTOR_ENB        10
#define MOTOR_A              0
#define MOTOR_B              1
#define TIMEOUT_SONIC        3000
#define TIMEOUT_IIC          1000
#define STATE_STARTUP        0x0001
#define STATE_TURNING        0x0002
#define STATE_FALLDOWN       0x0004
#define STATE_EC_A_CHANGE    0x0008
#define STATE_EC_B_CHANGE    0x0010
#define STATE_SERIAL_END     0x0020
#define STATE_REMOTE_CONTROL 0x0040

#define LED_ON  digitalWrite(PIN_LED, HIGH);
#define LED_OFF digitalWrite(PIN_LED, LOW);

enum MotorState {
    MOTOR_FRONT,
    MOTOR_BACK,
    MOTOR_STOP
};

enum MotionState {
    Motion_FRONT,
    Motion_BACK,
    Motion_LEFT,
    Motion_RIGHT,
    Motion_STOP
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
void initEncoders(void);
void initLED(void);
void initIMU(void);
void initMotors(void);
void initOLED(void);
void initSerial(void);
void initSonic(void);
void runSonic(void);
void setMotorDirection(uint8_t motor, MotorState state);
void setMotorSpeed(uint8_t motor, uint8_t speed);
void showSelfCheckingInfo(void);
void playBuzzerSound(uint8_t freq, uint8_t time);
void writeDataToEEPROM(void);
uint8_t readDataFromIIC(uint8_t address, uint8_t *data, uint8_t bytes);
uint8_t writeDataToIIC(uint8_t address, uint8_t data, bool stop_flag);
uint8_t writeDataToIIC(uint8_t address, uint8_t *data, uint8_t length,
                       bool stop_flag);
float getSonicData(void);

#endif // SBR_MAIN_H
