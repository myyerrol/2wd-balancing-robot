#include "driver_motor.hpp"

void setup() {
    Serial.begin(9600);
    // pinMode(0, OUTPUT);
    // pinMode(1, OUTPUT);
    initMotor();
}

void loop() {
    // Serial.println("Hello World!");
    // delay(1000);
    // digitalWrite(0, LOW);
    // digitalWrite(1, LOW);
    // delay(1000);
    // digitalWrite(0, LOW);
    // digitalWrite(1, HIGH);
    // delay(1000);
    // digitalWrite(0, HIGH);
    // digitalWrite(1, LOW);
    // delay(1000);
    // digitalWrite(0, HIGH);
    // digitalWrite(1, HIGH);
    testMotor();
}
