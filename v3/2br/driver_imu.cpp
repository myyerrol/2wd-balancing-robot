#include "driver_imu.hpp"

/**mpu6050.cpp + mpu6050.h
 * 功能：模块初始化，直接读取mpu6050角度
 * 说明：基于MPU6050_tockn库，仅进行了简单封装
 *
 */


MPU6050 mpu6050(Wire);

/******************** mpu6050初始化 ***************************/
/**
  * 函数功能: mpu6050初始化
  * 输入参数: 无
  * 返 回 值: 无
  * 说    明: 初始化时需要静止3s左右，矫正零点
  */
void mpu6050_init()//mpu6050初始化
{
  Wire.begin(13,12);// (sda,scl)Set I2C frequency to 400kHz
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);
}



/******************** mpu6050获取角度值 ***************************/
/**
  * 函数功能: mpu6050获取角度值
  * 输入参数: 角度数值的变量指针，方向（X,Y,Z）
  * 返 回 值: 无
  * 说    明: 此函数用于更新mpu6050并且获取数值
  */
void mpu6050_get_angel(double* getAngel,char Axis)
{
  mpu6050.update();
  switch(Axis)
  {
    case 'X': *getAngel=mpu6050.getAngleX();break;
    case 'Y': *getAngel=mpu6050.getAngleY();break;
    case 'Z': *getAngel=mpu6050.getAngleZ();break;
    default:break;
  }
}
