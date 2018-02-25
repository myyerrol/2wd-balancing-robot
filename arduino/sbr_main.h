#ifndef SBR_MAIN_H
#define SBR_MAIN_H

#define PIN_LED          13
#define PIN_BUZZER       A0
#define PIN_ECHO         A1
#define PIN_TRIG         A2
#define PIN_IIC_SCL      A5
#define PIN_IIC_SDA      A4
#define PIN_SPI_MOSI     11
#define PIN_SPI_MISO     12
#define PIN_RXD          0
#define PIN_TXD          1
#define PIN_ENCODER_A_C1 2
#define PIN_ENCODER_A_C2 4
#define PIN_ENCODER_B_C1 3
#define PIN_ENCODER_B_C2 A3
#define PIN_MOTOR_IN1    5
#define PIN_MOTOR_IN2    6
#define PIN_MOTOR_IN3    7
#define PIN_MOTOR_IN4    8
#define PIN_MOTOR_ENA    9
#define PIN_MOTOR_ENB    10
#define MOTOR_A          0
#define MOTOR_B          1
#define TIMEOUT_SONIC    30000
#define TIMEOUT_IIC      1000

#define LED_ON  digitalWrite(PIN_LED, HIGH);
#define LED_OFF digitalWrite(PIN_LED, LOW);

enum MotorState
{
    MOTOR_FRONT,
    MOTOR_BACK,
    MOTOR_STOP
};

enum MotionState
{
    Motion_FRONT,
    Motion_BACK,
    Motion_LEFT,
    Motion_RIGHT,
    Motion_STOP
};

enum RobotState
{
    ROBOT_STARTUP,
    ROBOT_TURNING,
    ROBOT_FALLDOWN,
    ROBOT_ENCODER_A,
    ROBOT_ENCODER_B,
    ROBOT_CMD_DONE,
    ROBOT_REMOTE_CONTROL
};

void calculateAnglePID(void);
void calculateSpeedPID(void);
void countEncoderA(void);
void countEncoderB(void);
void initBuzzer(void);
void initEncoders(void);
void initLED(void);
void initIMU(void);
void initMotors(void);
void initOLED(void);
void initSerial(void);
void initSonic(void);
void setMotorDirection(uint8_t motor, MotorState state);
void setMotorSpeed(uint8_t motor, uint8_t speed);
void showSelfCheckingInfo(void);
void playBuzzerSound(uint8_t freq, uint8_t time);
uint8_t readDataFromIIC(uint8_t address, uint8_t *data, uint8_t bytes);
uint8_t writeDataToIIC(uint8_t address, uint8_t data, bool stop_flag);
uint8_t writeDataToIIC(uint8_t address, uint8_t *data, uint8_t length,
                       bool stop_flag);
float getUltrasonicDistance(void);

#endif // SBR_MAIN_H
