void initIMU(void) {
    // Read data from "WHO_AM_I" register.
    while (readDataFromIIC(REG_WHO_AM_I, g_iic_buffer, 1));
    if (g_iic_buffer[0] != 0x70) {
        while (1);
    }

    // Reset internal registers and restore default settings.
    while (writeDataToIIC(REG_PWR_MGMT_1, 0x80, true));
    delay(100);
    while (writeDataToIIC(REG_SIGNAL_PATH_RESET, 0x07, true));
    delay(100);

    // If PLL is ready, select the most reliable clock source automatically,
    // otherwise use an internal crystal oscillator.
    while (writeDataToIIC(REG_PWR_MGMT_1, 0x01, true));
    // Enable accelerometer and gyroscope.
    while (writeDataToIIC(REG_PWR_MGMT_2, 0x00, true));

    // The internal register: REG_SMPLRT_DIV.
    // Set the sampling frequency to 1000Hz: 1KHz / (1 + 0) = 1000Hz.
    g_iic_buffer[0] = 0x00;
    // The internal register: REG_CONFIG.
    // Set FIFO mode to 0, disable FSYNC and set gyroscope filter mode (184Hz
    // bandwidth, 2.9ms latency, 1KHz frame synchronization).
    g_iic_buffer[1] = 0x01;
    // The internal register: REG_GYRO_CONFIG.
    // Set the gyroscope full scale range to ±250deg/s.
    g_iic_buffer[2] = 0x00;
    // The internal register: REG_ACCEL_CONFIG.
    // Set the accelerometer full scale range to ±2g.
    g_iic_buffer[3] = 0x00;
    // The internal register: REG_ACCEL_CONFIG_2.
    // Set the accelerometer filtering mode (460Hz bandwidth, 1.94ms latency,
    // 1KHz frame synchronization).
    g_iic_buffer[4] = 0x00;
    // Write configuration information to the registers.
    while (writeDataToIIC(REG_SMPLRT_DIV, g_iic_buffer, 5, true));

    // Wait for the sensor initialization to complete.
    delay(100);

    // Read the acceleration and temperature values of the sensor.
    while (readDataFromIIC(0x3B, g_iic_buffer, 8));
    g_acc_x = (g_iic_buffer[0] << 8) | g_iic_buffer[1];
    g_acc_y = (g_iic_buffer[2] << 8) | g_iic_buffer[3];
    g_acc_z = (g_iic_buffer[4] << 8) | g_iic_buffer[5];
    g_temp  = (g_iic_buffer[6] << 8) | g_iic_buffer[7];

    // Calculate the initial pitch angle.
    double pitch = atan(-g_acc_x / sqrt(g_acc_y * g_acc_y + g_acc_z * g_acc_z))
        * RAD_TO_DEG;

    // Calculate the rotation angle around the Y-axis.
    g_gyro_y_angle = pitch;
    g_calc_y_angle = pitch;

    g_timer_imu = micros();
}

void filterIMUData(void) {
#ifdef ENABLE_DELAY
    delay(10);
#endif

    // Read acceleration, temperature, and gyroscope values from sensors.
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

    // Calculate the initial pitch angle.
    double pitch = atan(-g_acc_x / sqrt(g_acc_y * g_acc_y + g_acc_z * g_acc_z))
        * RAD_TO_DEG;
    double gyro_y_rate = g_gyro_y / 131.0;

    calculateAnglePID();

    // Calculate the rotation angle around the Y-axis.
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
