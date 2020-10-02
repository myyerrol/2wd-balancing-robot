void initLED(void) {
    pinMode(PIN_LED, OUTPUT);   //making pin no 13 as a output
    LED_ON;                     // turning ON the LED
    delay(1000);                // delay of 1 secound
    LED_OFF;                    // turning OFF the LED
}
