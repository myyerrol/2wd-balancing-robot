#ifndef MODULE_ENCODER
#define MODULE_ENCODER

#define ENCODER_PIN_L1 6
#define ENCODER_PIN_L2 7
#define ENCODER_PIN_R1 10
#define ENCODER_PIN_R2 11

#include <Arduino.h>
#include "2br.hpp"

void initEncoder();
void readEncoder(int *p_encoder_l, int *p_encoder_r);
void testEncoder();

#endif
