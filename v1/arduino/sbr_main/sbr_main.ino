#include <EEPROM.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "sbr_main.h"

// Debug encoders.
// #define DEBUG_ENCODERS
// Debug IMU.
// #define DEBUG_IMU
// Debug motor.
#define DEBUG_MOTORS
// Debug PID cycle, printing time information after opening.
// #define DEBUG_PID_CYCLE
// Debug PID angle output.
// #define DEBUG_PID_ANGLE_OUTPUT
// Debug PID parameter, saving dynamic memory by replacing variable values with
// macros after closing.
// #define DEBUG_PID_PARAMETER
// Debug sonic sensor.
// #define DEBUG_SONIC

// Enable delay
#define ENABLE_DELAY
// Enable serial.
#define ENABLE_SERIAL
// Enable speed loop.
#define ENABLE_SPEED_LOOP
// Enable sonic sensor.
#define ENABLE_SONIC
// Enable motor.
// #define ENABLE_MOTORS
// Enable OLED.
#define ENABLE_OLED

/*****************************************************************************/

// OLED Global Variables.
#ifdef ENABLE_OLED
Adafruit_SSD1306 g_oled(OLED_WIDTH, OLED_HEIGHT, &Wire, OLED_RESET);
const PROGMEM uint8_t g_info_temp[]  = {"Temperature:"};
const PROGMEM uint8_t g_info_check[] = {};
const PROGMEM uint8_t g_logo_bmp[] = {
    B00000000, B11000000,
    B00000001, B11000000,
    B00000001, B11000000,
    B00000011, B11100000,
    B11110011, B11100000,
    B11111110, B11111000,
    B01111110, B11111111,
    B00110011, B10011111,
    B00011111, B11111100,
    B00001101, B01110000,
    B00011011, B10100000,
    B00111111, B11100000,
    B00111111, B11110000,
    B01111100, B11110000,
    B01110000, B01110000,
    B00000000, B00110000
};
#endif

// IMU Global Variables.
const uint8_t IMU_ADDRESS = 0x68;
double g_acc_x, g_acc_y, g_acc_z;
double g_gyro_y, g_gyro_z;
double g_calc_y_angle, g_gyro_y_angle;
int16_t g_temp;
uint32_t g_timer_imu;
static uint8_t g_iic_buffer[14];

// Encoder Global Variables.
volatile int32_t  g_count_encoder_a = 0, g_count_encoder_b = 0;
volatile uint32_t g_timer_encoder_a, g_timer_encoder_b;

// PID Global Variables.
// Angle Loop Variables.
#ifdef DEBUG_PID_PARAMETER
double  g_p_angle = 15, g_i_angle = 0, g_d_angle = 0;
#else
#define g_p_angle 0
#define g_i_angle 0
#define g_d_angle 0
#endif
double  g_angle_setpoint = -1.0, g_angle_output, g_angle_integral;
uint32_t g_timer_angle_pid;

// Speed Loop Variables.
#ifdef DEBUG_PID_PARAMETER
double  g_p_speed = 0, g_i_speed = 0;
#else
#define g_p_speed 0
#define g_i_speed 0
#endif
double  g_speed_setpoint = 0, g_speed_output, g_speed_integral;
uint32_t g_timer_speed_pid;

// Turning Angle Variables.
#ifdef DEBUG_PID_PARAMETER
double  g_p_turn = 0, g_i_turn = 0;
#else
#define g_p_turn 0
#define g_i_turn 0
#endif
double  g_turn_integral = 0, g_turn_output;

// Other Global Variables.
uint8_t  g_serial_buffer[20], g_serial_count;
int16_t  g_motor_speed = 100;
uint32_t g_robot_state;
uint32_t g_timer_sonic;
float g_joy_x, g_joy_y;
EEPROMStruct g_eeprom;


#define MUSIC_RYD

#ifndef MUSIC_HLH
#ifndef MUSIC_RYD
// 《欢乐颂》曲谱
int g_buzzer_tune[] = {
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
float g_buzzer_durt[] = {
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
int g_buzzer_speed = 500;
#endif
#endif

#ifdef MUSIC_HLH
// 《紅蓮華》曲谱
int g_buzzer_tune[] = {
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
float g_buzzer_durt[] = {
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
int g_buzzer_speed = 380;
#endif

#ifdef MUSIC_RYD
// 《Rage Your Dream》曲谱
int g_buzzer_tune[] = {
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
float g_buzzer_durt[] = {
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
int g_buzzer_speed = 450;
#endif





void setup()
{
    initSerial();
    initLED();
    initBuzzer();
    initSonic();
    initMotors();
    initIMU();
    initEncoders();
//    initEEPROM();

#ifdef ENABLE_OLED
    initOLED();
    // showSelfCheckingInfo();
#endif

    g_robot_state |= STATE_STARTUP;
}

void loop()
{
#ifdef DEBUG_MOTORS
    if (Serial.available() > 0) {
        char ch = Serial.read();
        Serial.print("command: ");
        Serial.println(ch);
        if (ch == 'w') {
            setMotorDirection(MOTOR_A, MOTOR_FRONT);
            setMotorDirection(MOTOR_B, MOTOR_FRONT);
        }
        else if (ch == 's') {
            setMotorDirection(MOTOR_A, MOTOR_BACK);
            setMotorDirection(MOTOR_B, MOTOR_BACK);
        }
        else if (ch == 'a') {
            setMotorDirection(MOTOR_A, MOTOR_FRONT);
            setMotorDirection(MOTOR_B, MOTOR_BACK);
        }
        else if (ch == 'd') {
            setMotorDirection(MOTOR_A, MOTOR_BACK);
            setMotorDirection(MOTOR_B, MOTOR_FRONT);
        }
        else if (ch == 'x') {
            setMotorDirection(MOTOR_A, MOTOR_STOP);
            setMotorDirection(MOTOR_B, MOTOR_STOP);
        }
        else if (ch == 'q') {
            g_motor_speed++;
            Serial.print("Speed: ");
            Serial.println(g_motor_speed);
        }
        else if (ch == 'e') {
            g_motor_speed--;
            Serial.print("Speed: ");
            Serial.println(g_motor_speed);
        }

        setMotorSpeed(MOTOR_A, g_motor_speed);
        setMotorSpeed(MOTOR_B, g_motor_speed);
    }
#endif

//    while (Serial.available() > 0) {
//        char ch = char(Serial.read());
//        Serial.print(ch);
//    }

/*****************************************************************************/
    // Judge is falldown.
    if (g_robot_state & STATE_FALLDOWN) {
        setMotorDirection(MOTOR_A, MOTOR_STOP);
        setMotorDirection(MOTOR_B, MOTOR_STOP);
    }

#ifdef DEBUG_PID_CYCLE
    Serial.print("Time 1: ");
    Serial.print(micros() + "us");
#endif

/*****************************************************************************/
// Calculate PID.
#ifdef ENABLE_SPEED_LOOP
    calculateSpeedPID();
#endif

#ifndef DEBUG_MOTORS
    filterIMUData();
    calculateAnglePID();
#endif

/*****************************************************************************/
// Get sonic sensor data.
#ifdef ENABLE_SONIC
    if (micros() - g_timer_sonic > 100000) {
        runSonic();
    }
#endif

#ifdef DEBUG_PID_CYCLE
    Serial.print("Time 2: ");
    Serial.print(micros() + "us");
#endif

/*****************************************************************************/
// Print serial data.
#ifdef DEBUG_PID_CYCLE
    Serial.print(F("V,"));
    Serial.print(atan2(g_acc_x, g_acc_z) * RAD_TO_DEG + 180.0);
    Serial.print(F(","));
    Serial.print(g_gyro_y / 131.0 + 180.0);
    Serial.print(F(","));
    Serial.print("0");
    Serial.print("\n");
#endif

/*****************************************************************************/
// Get serial data.
#ifdef ENABLE_SERIAL
    getSerialData();
    analyzeSerialData();
#endif

#ifdef DEBUG_PID_CYCLE
    Serial.print("Time 3: ");
    Serial.print(micros() + "us");
#endif

/*****************************************************************************/
// Calculate PID.
#ifdef ENABLE_SPEED_LOOP
    calculateSpeedPID();
#endif

#ifndef DEBUG_MOTORS
    calculateAnglePID();
#endif
}
