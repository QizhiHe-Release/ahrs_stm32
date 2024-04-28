#ifndef __ICM20948_H__
#define __ICM20948_H__

#ifdef __cplusplus
extern "C" {
#endif

// 0: Polling  1: Interrupt  2: DMA
#define I2C_TRANSMIT_MODE           (2)

// ADD_XXX: address     CMD_XXX: command
#define ADD_I2C_ICM20948            0xD0
#define ADD_REG_BANK_SEL            0x7F
#define CMD_REG_BANK_0              0x00
#define CMD_REG_BANK_1              0x10
#define CMD_REG_BANK_2              0x20
#define CMD_REG_BANK_3              0x30
// Bank 0
#define ADD_WHO_AM_I                0x00
#define ADD_PWR_MGMT_1              0x06
#define ADD_GYRO_SMPLRT_DIV         0x00
#define ADD_GYRO_CONFIG_1           0x01
#define ADD_ACCEL_SMPLRT_DIV_2      0x11
#define ADD_ACCEL_CONFIG            0x14
#define ADD_ACCEL_XOUT_H            0x2D
#define ADD_GYRO_XOUT_H             0x33
#define CMD_DEVICE_RESET            0x80
#define CMD_CLKSEL                  0x01
// Bank 1
// Bank 2
// Bank 3

#define ADD_I2C_SLV0_ADDR_WRITE     0x0C
#define ADD_I2C_SLV0_ADDR_READ      0x8C
#define ADD_CNTL2                   0x31
#define ADD_HXL                     0x11


void ICM20948_Init(void);
void ICM20948_Read_Accel(void);
void ICM20948_Read_Gyro(void);
void ICM20948_Read_Accel_Polling(void);
void ICM20948_Read_Gyro_Polling(void);

#ifdef __cplusplus
}
#endif

#endif
