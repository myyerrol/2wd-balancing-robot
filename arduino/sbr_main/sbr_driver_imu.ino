void initIMU(void)
{
    // Read "WHO_AM_I" Register.
    while (readDataFromIIC(REG_WHO_AM_I, g_iic_buffer, 1));

    if (g_iic_buffer[0] != 0x70) {
        while (1);
    }

    // Reset the internal registers and restores the default settings.
    while (writeDataToIIC(REG_PWR_MGMT_1, 0x80, true));
    delay(100);

    while (writeDataToIIC(REG_SIGNAL_PATH_RESET, 0x07, true));
    delay(100);

    // Auto selects the best available clock source – PLL if ready, else use
    // the Internal oscillator.
    while (writeDataToIIC(REG_PWR_MGMT_1, 0x01, true));
    // Enable Accelerometer and Gyroscope.
    while (writeDataToIIC(REG_PWR_MGMT_2, 0x00, true));

    // REG_SMPLRT_DIV
    // Set the sample rate to 1000Hz: 1kHz/(1+0) = 1000Hz
    g_iic_buffer[0] = 0x00;
    // REG_CONFIG
    // Set FIFO MODE to 0, disable FSYNC and set Gyroscope filtering(184Hz
    // Bandwidth, 2.9ms Delay, 1kHz Fs).
    g_iic_buffer[1] = 0x01;
    // REG_GYRO_CONFIG
    // Set Gyroscope Full Scale Range to ±250deg/s.
    g_iic_buffer[2] = 0x00;
    // REG_ACCEL_CONFIG
    // Set Accelerometer Full Scale Range to ±2g.
    g_iic_buffer[3] = 0x00;
    // REG_ACCEL_CONFIG_2
    // Set Accelerometer filtering(460Hz Bandwidth, 1.94ms Delay, 1kHz Fs);
    g_iic_buffer[4] = 0x00;
    // Write to all four registers at once.
    while (writeDataToIIC(REG_SMPLRT_DIV, g_iic_buffer, 5, true));

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

    if (abs(g_calc_y_angle - g_eeprom.angle) > 60) {
        g_robot_state |= STATE_FALLDOWN;
    }
    else {
        g_robot_state &= ~STATE_FALLDOWN;
    }

#ifdef DEBUG_IMU
    Serial.print("Angle y: ");
    Serial.println(g_calc_y_angle);
#endif
}
