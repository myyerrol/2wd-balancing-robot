#ifndef DRIVER_BTH
#define DRIVER_BTH

#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include "2br.hpp"

#define BLE_SRV_UUID    "a15315c6-a337-4827-b910-736ab86f8fe2"
#define BLE_CHT_UUID_TX "3a06a885-ebb9-4b5c-b041-f7c6f626aeac"
#define BLE_CHT_UUID_RX "4d5a06d0-3b2c-4192-9cad-512902bf4d89"

class MyServerCallbacks : public BLEServerCallbacks {
    void onConnect(BLEServer *pServer) {
        deviceConnected = true;
    };

    void onDisconnect(BLEServer *pServer) {
        deviceConnected = false;
    }
};

class MyCallbacks : public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic) {
        String rxValue = pCharacteristic->getValue();

        if (rxValue.length() > 0) {
            Serial.println("*********");
            Serial.print("Received Value: ");
            for (int i = 0; i < rxValue.length(); i++) {
                Serial.print(rxValue[i]);
            }
            Serial.println();
            Serial.println("*********");
        }
    }
};

void initBLE();
void testBLE();

#endif
