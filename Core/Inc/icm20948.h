#ifndef __ICM20948_H__
#define __ICM20948_H__

#ifdef __cplusplus
extern "C" {
#endif

#define I2C_ADDRESS 0xD0
#define REG_BANK_SEL 0x7F
#define REG_BANK_0 0x00
#define REG_BANK_1 0x10
#define REG_BANK_2 0x20
#define REG_BANK_3 0x30
// Bank 0
#define WHO_AM_I 0x00
#define PWR_MGMT_1 0x06
#define DEVICE_RESET 0x80
#define CLKSEL 0x01
#define GYRO_SMPLRT_DIV 0x00
#define GYRO_CONFIG_1 0x01
#define ACCEL_SMPLRT_DIV_2 0x11
#define ACCEL_CONFIG 0x14
#define ACCEL_XOUT_H 0x2D
#define GYRO_XOUT_H 0x33
// Bank 1
// Bank 2
// Bank 3

void ICM20948_Init(void);
void ICM20948_Read_Accel(void);
void ICM20948_Read_Gyro(void);

#ifdef __cplusplus
}
#endif

#endif
