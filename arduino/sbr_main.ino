#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "sbr_main.h"

// PID cycle debug, printing time information after opening.
#define DEBUG_PID_CYCLE
// PID parameter debug, saving dynamic memory by replacing variable values with
// macros after closing.
#define DEBUG_PID_PARAMETER
// Speed Loop Enable.
#define ENABLE_SPEED_LOOP
// Sonic Sensor Enable.
#define ENABLE_SONIC
// Motor Enable.
#define ENABLE_MOTOR
// Output IMU Data.
#define OUTPUT_IMU
// Output Sonic Sensor Data.
#define OUTPUT_SONIC

/*****************************************************************************/

// OLED Global Variables.
// Adafruit_SSD1306 g_oled(-1);
// const uint8_t PROGMEM g_info_temp[]  = {"Temperature:"};
// const uint8_t PROGMEM g_info_check[] = {};

// IMU Global Variables.
const uint8_t IMU_ADDRESS = 0x68;
double g_acc_x, g_acc_y, g_acc_z;
double g_gyro_y, g_gyro_z;
double g_calc_y_angle, g_gyro_y_angle;
int16_t g_temp;
uint32_t g_timer_imu;
static uint8_t g_iic_buffer[8];

// Encoder Global Variables.
volatile int32_t  g_count_encoder_a = 0, g_count_encoder_b = 0;
volatile uint32_t g_timer_encoder_a, g_timer_encoder_b;

// PID Global Variables.
// Angle Loop Variables.
#ifdef DEBUG_PID_PARAMETER
double  g_p_angle = 0, g_i_angle = 0, g_d_angle = 0;
#else
#define g_p_angle 0
#define g_i_angle 0
#define g_d_angle 0
#endif
double  g_angle_setpoint = 0, g_angle_output, g_angle_integral;
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
uint32_t g_robot_state;
uint32_t g_timer_sonic;
uint8_t  g_serial_buffer[20], g_serial_count;
float g_joy_x, g_joy_y;

void setup()
{
    initSerial();
    initLED();
    initBuzzer();
    initSonic();
    initMotors();
    // initOLED();
    initIMU();
    initEncoders();

    // showSelfCheckingInfo();

    g_robot_state |= STATE_STARTUP;
}

void loop()
{
    // if (Serial.available() > 0) {
    //     float distance = getUltrasonicDistance();
    //     Serial.print("Distance: ");
    //     Serial.print(distance);
    //     Serial.println("cm");

    //     if (distance == 0) {
    //         return ;
    //     }
    //     if (distance > 0 && distance <= 5) {
    //         digitalWrite(PIN_LED, HIGH);
    //     }
    //     else
    //     {
    //         digitalWrite(PIN_LED, LOW);
    //     }
    // }
//     if (g_robot_state == ROBOT_FALLDOWN) {
//         setMotorSpeed(MOTOR_A, MOTOR_STOP);
//         setMotorSpeed(MOTOR_B, MOTOR_STOP);
//     }

// #ifdef DEBUG_PID_CYCLE
//     Serial.print(" 1.");
//     Serial.print(micros());
// #endif

// #ifdef ENABLE_SPEED_LOOP
//     calculateSpeedPID();
// #endif
//     filterIMUData();
//     calculateAnglePID();

// #ifdef ENABLE_SONIC
//     if (micros() - g_timer_sonic > 100000) {

//     }
// #endif

// #ifdef DEBUG_PID_CYCLE
//     Serial.print(" 2.");
//     Serial.print(micros());
// #endif

// #ifdef DEBUG_PID_CYCLE
//     Serial.print(F("V,"));
//     Serial.print(atan2(g_acc_x, g_acc_z) * RAD_TO_DEG + 180.0);
//     Serial.print(F(","));
//     Serial.print(g_gyro_y / 131.0 + 180.0);
//     Serial.print(F(","));
//     Serial.print("0");
//     Serial.print("\n");
// #endif

//     getSerialData();
//     analyzeSerialData();

// #ifdef DEBUG_PID_CYCLE
//     Serial.print(" 3.");
//     Serial.print(micros());
// #endif

// #ifdef ENABLE_SPEED_LOOP
//     calculateSpeedPID();
// #endif
//     calculateAnglePID();
}
