#ifndef DRIVER_ENCODER
#define DRIVER_ENCODER

#define PIN_ENCODER_L1 6
#define PIN_ENCODER_L2 7
#define PIN_ENCODER_R1 10
#define PIN_ENCODER_R2 11

#include <Arduino.h>
#include "2br.hpp"

void initEncoder();
void readEncoder();
void testEncoder();

#endif
