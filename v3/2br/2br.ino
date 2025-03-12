#include "driver_motor.hpp"

void setup() {
    Serial.begin(9600);
    initMotor();
}

void loop() {
    testMotor();
}
