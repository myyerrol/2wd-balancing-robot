#include "driver_ble.hpp"

BLEServer         *g_ble_server       = NULL;
BLECharacteristic *g_ble_cht_tx;
bool               g_ble_dev_conn     = false;
bool               g_ble_dev_conn_old = false;
uint8_t            g_ble_tx_val       = 0;

class MyServerCallbacks : public BLEServerCallbacks {
    void onConnect(BLEServer *p_ble_server) {
        g_ble_dev_conn = true;
    };
    void onDisconnect(BLEServer *p_ble_server) {
        g_ble_dev_conn = false;
    }
};

class MyCallbacks : public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *p_ble_cht) {
        String t_ble_tx_val = p_ble_cht->getValue();
        if (t_ble_tx_val.length() > 0) {
            for (int i = 0; i < t_ble_tx_val.length(); i++) {
                Serial.print(t_ble_tx_val[i]);
            }
            Serial.println();
        }
    }
};

void initBLE() {
    BLEDevice::init("2BR");

    g_ble_server = BLEDevice::createServer();
    g_ble_server->setCallbacks(new MyServerCallbacks());

    BLEService *t_ble_srv = g_ble_server->createService(BLE_SRV_UUID);
    g_ble_cht_tx = t_ble_srv->createCharacteristic(
        BLE_CHT_UUID_TX,
        BLECharacteristic::PROPERTY_NOTIFY);
    g_ble_cht_tx->addDescriptor(new BLE2902());

    BLECharacteristic *t_ble_cht_rx = t_ble_srv->createCharacteristic(
        BLE_CHT_UUID_RX,
        BLECharacteristic::PROPERTY_WRITE);
    t_ble_cht_rx->setCallbacks(new MyCallbacks());

    t_ble_srv->start();

    g_ble_server->getAdvertising()->start();
}

void testBLE() {
    if (g_ble_dev_conn) {
        g_ble_cht_tx->setValue(&g_ble_tx_val, 1);
        g_ble_cht_tx->notify();
        g_ble_tx_val++;
        delay(10);
    }

    if (!g_ble_dev_conn && g_ble_dev_conn_old) {
        delay(500);
        g_ble_server->startAdvertising();
        g_ble_dev_conn_old = g_ble_dev_conn;
    }
    if (g_ble_dev_conn && !g_ble_dev_conn_old) {
        g_ble_dev_conn_old = g_ble_dev_conn;
    }
}
