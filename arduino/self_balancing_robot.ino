#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "self_balancing_robot.h"

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
Adafruit_SSD1306 g_oled(-1);
const uint8_t PROGMEM g_info_temp[]  = {"Temperature:"};
const uint8_t PROGMEM g_info_check[] = {};

// IMU Global Variables.
const uint8_t IMU_ADDRESS = 0x70;
double g_acc_x, g_acc_y, g_acc_z;
double g_gyro_y, g_gyro_z;
double g_calc_y_angle, g_gyro_y_angle;
int16_t g_temp;
uint32_t g_timer_imu;
static uint8_t g_iic_buffer[8];

// Encoder Global Variables.
volatile int32_t  g_count_encoder_a, g_count_encoder_b;
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
RobotState g_robot_state;
uint32_t g_timer_sonic;

/*****************************************************************************/

void calculateAnglePID(void)
{
    double output_a, output_b;

    if (micros() - g_timer_angle_pid > 10000) {
#ifdef DEBUG_PID_CYCLE
        Serial.print("A.");
        Serial.print(millis());
#endif
        // Calculate angle.
        double angle_error = g_calc_y_angle - g_angle_setpoint;
        g_angle_integral += angle_error;
        g_angle_output = g_p_angle * angle_error + g_i_angle * g_angle_integral;

        // Calculate turn.
        if ()
    }
}

void calculateSpeedPID(void)
{

}

void countEncoderA(void)
{
    if (digitalRead(PIN_ENCODER_A_C2) == HIGH) {
        g_count_encoder_a++;
    }
    else if (digitalRead(PIN_ENCODER_A_C2 == LOW)) {
        g_count_encoder_a--;
    }
    else {
        return;
    }
}

void countEncoderB(void)
{
    if (digitalRead(PIN_ENCODER_B_C2) == HIGH) {
        g_count_encoder_b++;
    }
    else if (digitalRead(PIN_ENCODER_B_C2 == LOW)) {
        g_count_encoder_b--;
    }
    else {
        return;
    }
}

void initEncoders(void)
{
    pinMode(PIN_ENCODER_A_C1, INPUT);
    pinMode(PIN_ENCODER_A_C2, INPUT);
    pinMode(PIN_ENCODER_B_C1, INPUT);
    pinMode(PIN_ENCODER_B_C2, INPUT);

    attachInterrupt(digitalPinToInterrupt(2), countEncoderA, FALLING);
    attachInterrupt(digitalPinToInterrupt(3), countEncoderB, FALLING);
}

void initMotors(void)
{
    pinMode(PIN_MOTOR_IN1, OUTPUT);
    pinMode(PIN_MOTOR_IN2, OUTPUT);
    pinMode(PIN_MOTOR_IN3, OUTPUT);
    pinMode(PIN_MOTOR_IN4, OUTPUT);
    pinMode(PIN_MOTOR_ENA, OUTPUT);
    pinMode(PIN_MOTOR_ENB, OUTPUT);

    setMotorDirection(MOTOR_A, MOTOR_STOP);
    setMotorDirection(MOTOR_B, MOTOR_STOP);
}

void initIMU(void)
{
    // Read "WHO_AM_I" Register.
    while (readDataFromIIC(0x75, g_iic_buffer, 1));
    if (g_iic_buffer[0] != 0x70) {
        Serial.print(F("Error Reading IMU Data!"));
        while (1);
    }

    // Reset device, this resets all internal registers to their default values.
    while (writeDataToIIC(0x6B, 0x80, true));
    do {
        while (readDataFromIIC(0x6B, g_iic_buffer, 1));
    } while (g_iic_buffer[0] & 0x80);

    // PLL with X axis gyroscope reference.
    while (writeDataToIIC(0x6B, 0x01, true));

    // Set the sample rate to 1000Hz - 8kHz/(7+1) = 1000Hz
    g_iic_buffer[0] = 7;
    // Disable FSYNC and set 260 Hz Acc filtering, 256 Hz Gyro filtering,
    // 8 KHz sampling.
    g_iic_buffer[1] = 0x00;
    // Set Gyroscope Full Scale Range to ±250deg/s.
    g_iic_buffer[2] = 0x00;
    // Set Accelerometer Full Scale Range to ±2g.
    g_iic_buffer[3] = 0x00;
    // Write to all four registers at once.
    while (writeDataToIIC(0x19, g_iic_buffer, 4, false));

    // Wait for the sensor to get ready.
    delay(100);

    while (readDataFromIIC(0x3B, g_iic_buffer, 8));
    g_acc_x = (g_iic_buffer[0] << 8) | g_iic_buffer[1];
    g_acc_y = (g_iic_buffer[2] << 8) | g_iic_buffer[3];
    g_acc_z = (g_iic_buffer[4] << 8) | g_iic_buffer[5];
    g_temp  = (g_iic_buffer[6] << 8) | g_iic_buffer[7];

    double pitch = atan(-g_acc_x / sqrt(g_acc_y * g_acc_y + g_acc_z * g_acc_z))
        * RAD_TO_DEG;

    g_gyro_y_angle = pitch;
    g_calc_y_angle = pitch;

    g_timer_imu = micros();
}

void initOLED(void)
{
    g_oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    g_oled.clearDisplay();
    g_oled.setTextSize(4);
    g_oled.setTextColor(WHITE);
    g_oled.setCursor(30, 20);
    g_oled.print("SBR");
    g_oled.display();
}

void setMotorDirection(uint8_t motor, MotorState state)
{
    if (state == MOTOR_FRONT) {
        if (motor == MOTOR_A) {
            digitalWrite(PIN_MOTOR_IN1, HIGH);
            digitalWrite(PIN_MOTOR_IN2, LOW);
        }
        else if (motor == MOTOR_B) {
            digitalWrite(PIN_MOTOR_IN3, LOW);
            digitalWrite(PIN_MOTOR_IN4, HIGH);
        }
        else {
            return;
        }
    }
    else if (state == MOTOR_BACK) {
        if (motor == MOTOR_A) {
            digitalWrite(PIN_MOTOR_IN1, LOW);
            digitalWrite(PIN_MOTOR_IN2, HIGH);
        }
        else if (motor == MOTOR_B) {
            digitalWrite(PIN_MOTOR_IN3, HIGH);
            digitalWrite(PIN_MOTOR_IN4, LOW);
        }
        else {
            return;
        }
    }
    else if (state == MOTOR_STOP) {
        if (motor == MOTOR_A) {
            digitalWrite(PIN_MOTOR_IN1, LOW);
            digitalWrite(PIN_MOTOR_IN2, LOW);
        }
        else if (motor == MOTOR_B) {
            digitalWrite(PIN_MOTOR_IN3, LOW);
            digitalWrite(PIN_MOTOR_IN4, LOW);
        }
        else {
            return;
        }
    }
    else {
        return;
    }
}

void setMotorSpeed(uint8_t motor, uint8_t speed)
{
    if (speed >= 0 && speed <= 100) {
        uint8_t pwm = map(speed, 0, 100, 0, 255);
        if (motor == MOTOR_A) {
            analogWrite(PIN_MOTOR_ENA, pwm);
        }
        else {
            analogWrite(PIN_MOTOR_ENB, pwm);
        }
    }
    else {
        return;
    }
}

void showSelfCheckingInfo(void)
{
    g_oled.clearDisplay();
    g_oled.setTextSize(1);
    g_oled.setCursor(0, 0);

    for (uint8_t i = 0; i < strlen(g_info_check); i++)
    {
        uint8_t byte =  pgm_read_byte_near(g_info_check + i);
        g_oled.print(byte);
    }
    for (uint8_t i = 0; i < strlen(g_info_temp); i++)
    {
        uint8_t byte =  pgm_read_byte_near(g_info_temp + i);
        g_oled.print(byte);
    }

    g_oled.print((double)g_temp / 340.0 + 31.53);
    g_oled.display();
}

void playBuzzerSound(uint8_t freq, uint8_t time)
{
    tone(PIN_BUZZER, freq);
    delay(time);
    noTone(PIN_BUZZER);
}

uint8_t writeDataToIIC(uint8_t address, uint8_t data, bool stop_flag)
{
    return writeDataToIIC(address, &data, 1, stop_flag);
}

uint8_t writeDataToIIC(uint8_t address, uint8_t *data, uint8_t length,
                       bool stop_flag)
{
    Wire.beginTransmission(IMU_ADDRESS);
    Wire.write(address);
    Wire.write(data, length);

    uint8_t result = Wire.endTransmission(stop_flag);

    if (result) {
        Serial.print(F("writeDataToIIC() failed: "));
        Serial.println(result);
    }

    return result;
}

uint8_t readDataFromIIC(uint8_t address, uint8_t *data, uint8_t bytes)
{
    uint32_t timeout_timer;

    Wire.beginTransmission(IMU_ADDRESS);
    Wire.write(address);

    uint8_t result = Wire.endTransmission(false);

    if (result) {
      Serial.print(F("readDataFromIIC() failed: "));
      Serial.println(result);
      return result;
    }

    Wire.requestFrom(IMU_ADDRESS, bytes, (uint8_t)true);

    for (uint8_t i = 0; i < bytes; i++)
    {
        if (Wire.available()) {
            data[i] = Wire.read();
        }
        else {
            timeout_timer = micros();
            while (((micros() - timeout_timer) < TIMEOUT_IIC) &&
                   !Wire.available());
            if (Wire.available()) {
                data[i] = Wire.read();
            }
            else {
                Serial.println(F("readDataFromIIC() timeout!"));
                return 5;
            }
        }
    }
    return 0;
}

float getUltrasonicDistance(void)
{
    float duration = 0.0;
    float distance = 0.0;

    digitalWrite(PIN_TRIG, LOW);
    delayMicroseconds(10);
    digitalWrite(PIN_TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(PIN_TRIG, LOW);

    duration = pulseIn(PIN_ECHO, HIGH, TIMEOUT_SONIC);

    if (duration == 0.0) {
        return 0.0;
    }
    else {
        distance = duration * 0.017;
        return distance;
    }
}

void setup()
{
    pinMode(PIN_LED, OUTPUT);
    pinMode(PIN_BUZZER, OUTPUT);
    pinMode(PIN_TRIG, OUTPUT);
    pinMode(PIN_ECHO, INPUT);

    Wire.begin();
    Serial.begin(115200);

    initMotors();
    playBuzzerSound(50, 500);

    initOLED();
    playBuzzerSound(50, 500);

    initIMU();
    playBuzzerSound(50, 500);

    initEncoders();
    playBuzzerSound(50, 500);

    showSelfCheckingInfo();

    g_robot_state = ROBOT_STARTUP;
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
    if (g_robot_state == ROBOT_FALLDOWN) {
        setMotorSpeed(MOTOR_A, MOTOR_STOP);
        setMotorSpeed(MOTOR_B, MOTOR_STOP);
    }

#ifdef DEBUG_PID_CYCLE
    Serial.print("1.");
    Serial.print(micros());
#endif

#ifdef ENABLE_SPEED_LOOP
    calculateSpeedPID();
#endif
    filterIMUData();
    calculateAnglePID();

#ifdef ENABLE_SONIC
    if (micros() - g_timer_sonic > 100000) {

    }
#endif

#ifdef DEBUG_PID_CYCLE
    Serial.print("2.");
    Serial.print(micros());
#endif

#ifdef DEBUG_PID_CYCLE
    Serial.print(F("V,"));
    Serial.print(atan2(g_acc_x, g_acc_z) * RAD_TO_DEG + 180.0);
    Serial.print(F(","));
    Serial.print(g_gyro_y / 131.0 + 180.0);
    Serial.print(F(","));
    Serial.print("0");
    Serial.print("\n");
#endif

    getSerialData();
    analyzeSerialData();

#ifdef DEBUG_PID_CYCLE
    Serial.print("3.");
    Serial.print(micros());
#endif

#ifdef ENABLE_SPEED_LOOP
    calculateSpeedPID();
#endif
    calculateAnglePID();
}

