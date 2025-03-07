void initEEPROM(void) {
    for (uint8_t i = 0; i < 4; i++) {
        g_eeprom.bytes[i] = 0;
    }
}

void readDataFromEEPROM(void) {
    for (uint8_t i = 0; i < 4; i++) {
        g_eeprom.bytes[i] = EEPROM.read(i);
    }
}

void writeDataToEEPROM(void) {
    uint8_t *ptr = g_eeprom.bytes;

    for (uint8_t i = 0; i < 4; i++) {
        EEPROM.write(i, *ptr);
        ptr++;
    }
}
