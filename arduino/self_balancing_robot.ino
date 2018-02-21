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
#define TIMEOUT              30000

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

void initMotors(void);
void initOLED(void);
void setMotorDirection(uint8_t motor, MotorState state);
void setMotorSpeed(uint8_t motor, uint8_t speed);
void playBuzzerSound(uint8_t freq, uint8_t time);
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

float getUltrasonicDistance(void)
{
    float duration = 0.0;
    float distance = 0.0;

    digitalWrite(PIN_TRIG, LOW);
    delayMicroseconds(10);
    digitalWrite(PIN_TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(PIN_TRIG, LOW);

    duration = pulseIn(PIN_ECHO, HIGH, TIMEOUT);

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

