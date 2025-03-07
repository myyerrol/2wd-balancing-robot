void initIMU(void) {
    // 读取【WHO_AM_I】寄存器数据
    while (readDataFromIIC(REG_WHO_AM_I, g_iic_buffer, 1));
    if (g_iic_buffer[0] != 0x70) {
        while (1);
    }

    // 重设内部寄存器组并恢复默认设置
    while (writeDataToIIC(REG_PWR_MGMT_1, 0x80, true));
    delay(100);
    while (writeDataToIIC(REG_SIGNAL_PATH_RESET, 0x07, true));
    delay(100);

    // 如果PLL准备就绪则自动选择最可靠的时钟源，否则使用内部晶振
    while (writeDataToIIC(REG_PWR_MGMT_1, 0x01, true));
    // 使能加速度计和陀螺仪
    while (writeDataToIIC(REG_PWR_MGMT_2, 0x00, true));

    // 内部寄存器为：REG_SMPLRT_DIV
    // 设置采样频率为1000Hz: 1kHz/(1+0) = 1000Hz
    g_iic_buffer[0] = 0x00;
    // 内部寄存器为：REG_CONFIG
    // 设置FIFO模式为0、禁用FSYNC并设置陀螺仪滤波模式（184Hz带宽、2.9ms延迟、1kHz帧同步）
    g_iic_buffer[1] = 0x01;
    // 内部寄存器为：REG_GYRO_CONFIG
    // 设置陀螺仪满标度范围为±250deg/s
    g_iic_buffer[2] = 0x00;
    // 内部寄存器为：REG_ACCEL_CONFIG
    // 设置加速度计满标度范围为±2g
    g_iic_buffer[3] = 0x00;
    // 内部寄存器为：REG_ACCEL_CONFIG_2
    // 设置加速度计滤波模式（460Hz带宽、1.94ms延迟、1kHz帧同步）
    g_iic_buffer[4] = 0x00;
    // 将配置信息写入到寄存器组中
    while (writeDataToIIC(REG_SMPLRT_DIV, g_iic_buffer, 5, true));

    // 等待传感器初始化完成
    delay(100);

    // 获取传感器的加速度和温度数值
    while (readDataFromIIC(0x3B, g_iic_buffer, 8));
    g_acc_x = (g_iic_buffer[0] << 8) | g_iic_buffer[1];
    g_acc_y = (g_iic_buffer[2] << 8) | g_iic_buffer[3];
    g_acc_z = (g_iic_buffer[4] << 8) | g_iic_buffer[5];
    g_temp  = (g_iic_buffer[6] << 8) | g_iic_buffer[7];

    // 计算得到初始俯仰角
    double pitch = atan(-g_acc_x / sqrt(g_acc_y * g_acc_y + g_acc_z * g_acc_z))
        * RAD_TO_DEG;

    // 计算得到绕Y轴旋转角
    g_gyro_y_angle = pitch;
    g_calc_y_angle = pitch;

    g_timer_imu = micros();
}

void filterIMUData(void) {
#ifdef ENABLE_DELAY
    delay(10);
#endif

    // 获取传感器的加速度、温度和陀螺仪数值
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

    // 计算得到当前俯仰角
    double pitch = atan(-g_acc_x / sqrt(g_acc_y * g_acc_y + g_acc_z * g_acc_z))
        * RAD_TO_DEG;
    double gyro_y_rate = g_gyro_y / 131.0;

    calculateAnglePID();

    // 计算得到绕Y轴旋转角
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
