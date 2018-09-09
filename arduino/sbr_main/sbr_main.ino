#include <EEPROM.h>
#include <Wire.h>

#ifdef ENABLE_OLED
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#endif

#include "sbr_main.h"

// Debug encoders.
// #define DEBUG_ENCODERS
// Debug IMU.
// #define DEBUG_IMU
// Debug motor.
// #define DEBUG_MOTORS
// Debug PID cycle, printing time information after opening.
// #define DEBUG_PID_CYCLE
// Debug PID angle output.
// #define DEBUG_PID_OUTPUT_ANGLE
// Debug PID motor output.
#define DEBUG_PID_OUTPUT_MOTOR
// Debug PID parameter, saving dynamic memory by replacing variable values with
// macros after closing.
#define DEBUG_PID_PARAMETER
// Debug sonic sensor.
// #define DEBUG_SONIC
// Enable delay
#define ENABLE_DELAY
// Enable serial.
// #define ENABLE_SERIAL
// Enable speed loop.
// #define ENABLE_SPEED_LOOP
// Enable sonic sensor.
// #define ENABLE_SONIC
// Enable motor.
#define ENABLE_MOTORS
// Enable OLED.
// #define ENABLE_OLED

/*****************************************************************************/

// OLED Global Variables.
#ifdef ENABLE_OLED
Adafruit_SSD1306 g_oled(-1);
const PROGMEM uint8_t g_info_temp[]  = {"Temperature:"};
const PROGMEM uint8_t g_info_check[] = {};
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
double  g_p_angle = 10, g_i_angle = 0, g_d_angle = 0;
#else
#define g_p_angle 0
#define g_i_angle 0
#define g_d_angle 0
#endif
double  g_angle_setpoint = 0.10, g_angle_output, g_angle_integral;
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

void setup()
{
    initSerial();
    initLED();
    initBuzzer();
    initSonic();
    initMotors();
    initIMU();
    initEncoders();
    initEEPROM();

#ifdef ENABLE_OLED
    initOLED();
    showSelfCheckingInfo();
#endif

    g_robot_state |= STATE_STARTUP;
}

void loop()
{
#ifdef DEBUG_MOTORS
    while (Serial.available() > 0) {
        char byte = Serial.read();
        if (byte == 'w') {
            setMotorDirection(MOTOR_A, MOTOR_FRONT);
            setMotorDirection(MOTOR_B, MOTOR_FRONT);
        }
        else if (byte == 's') {
            setMotorDirection(MOTOR_A, MOTOR_BACK);
            setMotorDirection(MOTOR_B, MOTOR_BACK);
        }
        else if (byte == 'a') {
            setMotorDirection(MOTOR_A, MOTOR_FRONT);
            setMotorDirection(MOTOR_B, MOTOR_BACK);
        }
        else if (byte == 'd') {
            setMotorDirection(MOTOR_A, MOTOR_BACK);
            setMotorDirection(MOTOR_B, MOTOR_FRONT);
        }
        else if (byte == 'x') {
            setMotorDirection(MOTOR_A, MOTOR_STOP);
            setMotorDirection(MOTOR_B, MOTOR_STOP);
        }
        else if (byte == 'q') {
            g_motor_speed++;
            Serial.print("Speed: ");
            Serial.println(g_motor_speed);
        }
        else if (byte == 'e') {
            g_motor_speed--;
            Serial.print("Speed: ");
            Serial.println(g_motor_speed);
        }

        setMotorSpeed(MOTOR_A, g_motor_speed);
        setMotorSpeed(MOTOR_B, g_motor_speed);
    }
#endif

/*****************************************************************************/
    // Judge is falldown.
    if (g_robot_state & STATE_FALLDOWN) {
        setMotorSpeed(MOTOR_A, MOTOR_STOP);
        setMotorSpeed(MOTOR_B, MOTOR_STOP);
    }

#ifdef DEBUG_PID_CYCLE
    Serial.print(" 1.");
    Serial.print(micros());
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
    Serial.print(" 2.");
    Serial.print(micros());
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
    Serial.print(" 3.");
    Serial.print(micros());
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
