uint8_t writeDataToIIC(uint8_t address, uint8_t data, bool stop_flag)
{
    return writeDataToIIC(address, &data, 1, stop_flag);
}

uint8_t writeDataToIIC(uint8_t address, uint8_t *data, uint8_t length,
                       bool stop_flag)
{
    Wire.beginTransmission(IMU_ADDRESS);
    Wire.write(address);
    Wire.write(data, length);

    uint8_t result = Wire.endTransmission(stop_flag);

    if (result) {
        Serial.print(F("Error, writeDataToIIC() failed: "));
        Serial.println(result);
    }

    return result;
}

uint8_t readDataFromIIC(uint8_t address, uint8_t *data, uint8_t bytes)
{
    uint32_t timeout_timer;

    Wire.beginTransmission(IMU_ADDRESS);
    Wire.write(address);

    uint8_t result = Wire.endTransmission(false);

    if (result) {
      Serial.print(F("Error, readDataFromIIC() failed: "));
      Serial.println(result);
      return result;
    }

    Wire.requestFrom(IMU_ADDRESS, bytes, (uint8_t)true);

    for (uint8_t i = 0; i < bytes; i++) {
        if (Wire.available()) {
            data[i] = Wire.read();
        }
        else {
            timeout_timer = micros();
            while (((micros() - timeout_timer) < TIMEOUT_IIC) &&
                   !Wire.available());
            if (Wire.available()) {
                data[i] = Wire.read();
            }
            else {
                Serial.println(F("Error, readDataFromIIC() timeout!"));
                return 5;
            }
        }
    }

    return 0;
}
