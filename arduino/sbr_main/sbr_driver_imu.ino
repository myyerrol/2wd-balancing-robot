void initIMU(void)
{
    // Read "WHO_AM_I" Register.
    while (readDataFromIIC(0x75, g_iic_buffer, 1));

    if (g_iic_buffer[0] != 0x70) {
        Serial.print(F("Error, reading imu data failed!"));
        while (1);
    }

    // Reset device, this resets all internal registers to their default values.
    while (writeDataToIIC(0x6B, 0x80, true));

    do {
        while (readDataFromIIC(0x6B, g_iic_buffer, 1));
    } while (g_iic_buffer[0] & 0x80);

    delay(5);

    // PLL with X axis gyroscope reference.
    while (writeDataToIIC(0x6B, 0x01, true));

    // Set the sample rate to 1000Hz - 8kHz/(7+1) = 1000Hz
    g_iic_buffer[0] = 7;
    // Disable FSYNC and set 260 Hz Acc filtering, 256 Hz Gyro filtering,
    // 8 KHz sampling.
    g_iic_buffer[1] = 0x00;
    // Set Gyroscope Full Scale Range to ±250deg/s.
    g_iic_buffer[2] = 0x00;
    // Set Accelerometer Full Scale Range to ±2g.
    g_iic_buffer[3] = 0x00;
    // Write to all four registers at once.
    while (writeDataToIIC(0x19, g_iic_buffer, 4, true));

    // Wait for the sensor to get ready.
    delay(100);

    while (readDataFromIIC(0x3B, g_iic_buffer, 8));
    g_acc_x = (g_iic_buffer[0] << 8) | g_iic_buffer[1];
    g_acc_y = (g_iic_buffer[2] << 8) | g_iic_buffer[3];
    g_acc_z = (g_iic_buffer[4] << 8) | g_iic_buffer[5];
    g_temp  = (g_iic_buffer[6] << 8) | g_iic_buffer[7];

    double pitch = atan(-g_acc_x / sqrt(g_acc_y * g_acc_y + g_acc_z * g_acc_z))
        * RAD_TO_DEG;

    g_gyro_y_angle = pitch;
    g_calc_y_angle = pitch;

    g_timer_imu = micros();
}

void filterIMUData(void)
{
#ifdef ENABLE_DELAY
    delay(1);
#endif

    while (readDataFromIIC(0x3B, g_iic_buffer, 14));
    g_acc_x  = (g_iic_buffer[0]  << 8) | g_iic_buffer[1];
    g_acc_y  = (g_iic_buffer[2]  << 8) | g_iic_buffer[3];
    g_acc_z  = (g_iic_buffer[4]  << 8) | g_iic_buffer[5];
    g_temp   = (g_iic_buffer[6]  << 8) | g_iic_buffer[7];
    g_gyro_y = (g_iic_buffer[10] << 8) | g_iic_buffer[11];
    g_gyro_z = (g_iic_buffer[12] << 8) | g_iic_buffer[13];

    calculateAnglePID();

    double dt = (double)(micros() - g_timer_imu) / 1000000;
    g_timer_imu = micros();

    double pitch = atan(-g_acc_x / sqrt(g_acc_y * g_acc_y + g_acc_z * g_acc_z))
        * RAD_TO_DEG;
    double gyro_y_rate = g_gyro_y / 131.0;

    calculateAnglePID();

    g_gyro_y_angle += gyro_y_rate * dt;
    g_calc_y_angle  = 0.93 * (g_calc_y_angle + gyro_y_rate * dt) + 0.07 * pitch;

    if (abs(g_calc_y_angle - g_eeprom.angle) > 15) {
        g_robot_state |= STATE_FALLDOWN;
    }

#ifdef DEBUG_IMU
    Serial.print("Angle y: ");
    Serial.println(g_calc_y_angle);
#endif
}
