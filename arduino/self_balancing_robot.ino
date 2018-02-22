#include <Wire.h>
// #include <Adafruit_GFX.h>
// #include <Adafruit_SSD1306.h>

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
#define PIN_ENCODER_LEFT_C1  2
#define PIN_ENCODER_LEFT_C2  4
#define PIN_ENCODER_RIGHT_C1 3
#define PIN_ENCODER_RIGHT_C2 A3
#define PIN_MOTOR_IN1        5
#define PIN_MOTOR_IN2        6
#define PIN_MOTOR_IN3        7
#define PIN_MOTOR_IN4        8
#define PIN_MOTOR_ENA        9
#define PIN_MOTOR_ENB        10
#define MOTOR_A              0
#define MOTOR_B              1
#define TIMEOUT_SONIC        30000
#define TIMEOUT_IIC          1000

enum MotorState
{
    MOTOR_FRONT,
    MOTOR_BACK,
    MOTOR_STOP
};

enum RobotState
{
    ROBOT_FRONT,
    ROBOT_BACK,
    ROBOT_LEFT,
    ROBOT_RIGHT,
    ROBOT_STOP
};

// Adafruit_SSD1306 g_oled(-1);

// IMU Variables.
const uint8_t IMU_ADDRESS = 0x70;
double g_acc_x, g_acc_y, g_acc_z;
double g_gyro_y, g_gyro_z;
double g_comp_y_angle, g_gyro_y_angle;
int16_t g_temp;
uint32_t g_imu_timer;
static uint8_t g_iic_buffer[8];

void initMotors(void);
void initIMU(void);
void initOLED(void);
void setMotorDirection(uint8_t motor, MotorState state);
void setMotorSpeed(uint8_t motor, uint8_t speed);
void playBuzzerSound(uint8_t freq, uint8_t time);
uint8_t readDataFromIIC(uint8_t address, uint8_t *data, uint8_t bytes);
uint8_t writeDataToIIC(uint8_t address, uint8_t data, bool stop_flag);
uint8_t writeDataToIIC(uint8_t address, uint8_t *data, uint8_t length,
                       bool stop_flag);
float getUltrasonicDistance(void);

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
    g_iic_buffer[0] = 7;
    g_iic_buffer[1] = 0x00;
    g_iic_buffer[2] = 0x00; // Set Gyroscope Full Scale Range to ±250deg/s.
    g_iic_buffer[3] = 0x00; // Set Accelerometer Full Scale Range to ±2g.

    // Write to all four registers at once.
    while (writeDataToIIC(0x19, g_iic_buffer, 4, false));
    // PLL with X axis gyroscope reference.
    while (writeDataToIIC(0x6B, 0x01, true));
    while (readDataFromIIC(0x75, g_iic_buffer, 1));

    if (g_iic_buffer[0] != 0x70) {
        while (1);
    }

    delay(1000);

    while (readDataFromIIC(0x3B, g_iic_buffer, 6));
    g_acc_x = (g_iic_buffer[0] << 8) | g_iic_buffer[1];
    g_acc_y = (g_iic_buffer[2] << 8) | g_iic_buffer[3];
    g_acc_z = (g_iic_buffer[4] << 8) | g_iic_buffer[5];
    g_temp  = (g_iic_buffer[6] << 8) | g_iic_buffer[7];

    double pitch = atan(-g_acc_x / sqrt(g_acc_y * g_acc_y + g_acc_z * g_acc_z))
        * RAD_TO_DEG;

    g_gyro_y_angle = pitch;
    g_comp_y_angle = pitch;

    g_imu_timer = micros();
}

// void initOLED(void)
// {
//     g_oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
//     g_oled.clearDisplay();
//     g_oled.setTextSize(4);
//     g_oled.setTextColor(WHITE);
//     g_oled.setCursor(30, 20);
//     g_oled.print("SBR");
//     g_oled.display();
// }

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
        int pwm = map(speed, 0, 100, 0, 255);
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

    playBuzzerSound(50, 500);

    initMotors();
    // initOLED();

    Wire.begin();
    Serial.begin(115200);
}

void loop()
{
    if (Serial.available() > 0) {
        float distance = getUltrasonicDistance();
        Serial.print("Distance: ");
        Serial.print(distance);
        Serial.println("cm");

        if (distance == 0) {
            return ;
        }
        if (distance > 0 && distance <= 5) {
            digitalWrite(PIN_LED, HIGH);
        }
        else
        {
            digitalWrite(PIN_LED, LOW);
        }
    }
}

