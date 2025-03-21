#ifndef DRIVER_WIFI
#define DRIVER_WIFI

#include <Arduino.h>
#include <WiFi.h>

void initWIFI();
void testWIFI();
void sendDataToWIFI(char *p_data);
void recvDataFrWIFI(char *p_data);

#endif
