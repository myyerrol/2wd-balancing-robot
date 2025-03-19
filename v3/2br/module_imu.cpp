#include "module_imu.hpp"

MPU6050 g_imu(Wire);

void initIMU() {
    Wire.begin(IMU_PIN_SDA, IMU_PIN_SCL);
    g_imu.begin();
    g_imu.calcGyroOffsets(true);
}

void getIMUAngle(float *p_angle_x, float *p_angle_y, float *p_angle_z) {
    g_imu.update();
    *p_angle_x = g_imu.getAngleX();
    *p_angle_y = g_imu.getAngleY();
    *p_angle_z = g_imu.getAngleZ();
}

void testIMU() {
    float t_angle_x;
    float t_angle_y;
    float t_angle_z;

    getIMUAngle(&t_angle_x, &t_angle_y, &t_angle_z);
    Serial.print("AngleX: ");
    Serial.print(t_angle_x);
    Serial.print("\t");
    Serial.print("AngleY: ");
    Serial.print(t_angle_y);
    Serial.print("\t");
    Serial.print("AngleZ: ");
    Serial.print(t_angle_z);
    Serial.print("\n");
}
