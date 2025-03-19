#ifndef DRIVER_BLE
#define DRIVER_BLE

#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include "2br.hpp"

#define BLE_SRV_UUID    "a15315c6-a337-4827-b910-736ab86f8fe2"
#define BLE_CHT_UUID_TX "3a06a885-ebb9-4b5c-b041-f7c6f626aeac"
#define BLE_CHT_UUID_RX "4d5a06d0-3b2c-4192-9cad-512902bf4d89"

void initBLE();
void testBLE();
void sendToBLE();
void recvFrBLE();

#endif
