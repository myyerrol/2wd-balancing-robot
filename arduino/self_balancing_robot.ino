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
#define PIN_MOTOR_ENB       10
#define TIMEOUT             30000

void playBuzzerSound(uint8_t freq, uint8_t time);
float getUltrasonicDistance(void);

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

    digitalWrite(PIN_LED, HIGH);

    delay(1000);

    digitalWrite(PIN_LED, LOW);

    playBuzzerSound(50, 500);

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
            //playBuzzerSound(100, 500);
        }
        else
        {
            digitalWrite(PIN_LED, LOW);
        }
    }
}

