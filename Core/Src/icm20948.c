#include "main.h"
#include "i2c.h"
#include "icm20948.h"

#ifndef I2C_TRANSMIT_MODE
#define I2C_TRANSMIT_MODE (1)
#endif

uint8_t imuDataBuffer[12];
uint8_t magDataBuffer[6];

int16_t Accel_X_RAW = 0;
int16_t Accel_Y_RAW = 0;
int16_t Accel_Z_RAW = 0;

int16_t Gyro_X_RAW = 0;
int16_t Gyro_Y_RAW = 0;
int16_t Gyro_Z_RAW = 0;

int16_t Magn_X_RAW = 0;
int16_t Magn_Y_RAW = 0;
int16_t Magn_Z_RAW = 0;

float Ax, Ay, Az, Gx, Gy, Gz;


void ICM20948_Init(void)
{
	uint8_t check;
	uint8_t Data;

	if (HAL_I2C_IsDeviceReady(&hi2c3, ADD_I2C_ICM20948, HAL_MAX_DELAY, HAL_MAX_DELAY) == HAL_OK)
	{
		Data = CMD_REG_BANK_0;
		HAL_I2C_Mem_Write(&hi2c3, ADD_I2C_ICM20948, ADD_REG_BANK_SEL, 1, &Data, 1, HAL_MAX_DELAY);
		HAL_Delay(10);
		HAL_I2C_Mem_Read(&hi2c3, ADD_I2C_ICM20948, ADD_WHO_AM_I, 1, &check, 1, HAL_MAX_DELAY);
		HAL_Delay(10);
		if (check == 0xEA)
		{
			Data = CMD_DEVICE_RESET;
			HAL_I2C_Mem_Write(&hi2c3, ADD_I2C_ICM20948, ADD_PWR_MGMT_1, 1, &Data, 1, HAL_MAX_DELAY);
			HAL_Delay(10);
			Data = CMD_CLKSEL;
			HAL_I2C_Mem_Write(&hi2c3, ADD_I2C_ICM20948, ADD_PWR_MGMT_1, 1, &Data, 1, HAL_MAX_DELAY);
			HAL_Delay(10);
			Data = CMD_REG_BANK_2;
			HAL_I2C_Mem_Write(&hi2c3, ADD_I2C_ICM20948, ADD_REG_BANK_SEL, 1, &Data, 1, HAL_MAX_DELAY);
			HAL_Delay(10);
			Data = 0x04;
			HAL_I2C_Mem_Write(&hi2c3, ADD_I2C_ICM20948, ADD_GYRO_SMPLRT_DIV, 1, &Data, 1, HAL_MAX_DELAY);
			HAL_Delay(10);
			Data = 0x05;
			HAL_I2C_Mem_Write(&hi2c3, ADD_I2C_ICM20948, ADD_GYRO_CONFIG_1, 1, &Data, 1, HAL_MAX_DELAY);
			HAL_Delay(10);
			Data = 0x04;
			HAL_I2C_Mem_Write(&hi2c3, ADD_I2C_ICM20948, ADD_ACCEL_SMPLRT_DIV_2, 1, &Data, 1, HAL_MAX_DELAY);
			HAL_Delay(10);
			Data = 0x01;
			HAL_I2C_Mem_Write(&hi2c3, ADD_I2C_ICM20948, ADD_ACCEL_CONFIG, 1, &Data, 1, HAL_MAX_DELAY);
			HAL_Delay(10);
			Data = CMD_REG_BANK_0;
			HAL_I2C_Mem_Write(&hi2c3, ADD_I2C_ICM20948, ADD_REG_BANK_SEL, 1, &Data, 1, HAL_MAX_DELAY);
			HAL_Delay(10);
			Data = 0x08;
			HAL_I2C_Mem_Write(&hi2c3, ADD_I2C_SLV0_ADDR_WRITE, ADD_CNTL2, 1, &Data, 1, HAL_MAX_DELAY);
			HAL_Delay(10);

			if (I2C_TRANSMIT_MODE == 1)
			{
				HAL_I2C_Mem_Read_IT(&hi2c3, ADD_I2C_ICM20948, ADD_ACCEL_XOUT_H, I2C_MEMADD_SIZE_8BIT, imuDataBuffer, 12);
			}
			if (I2C_TRANSMIT_MODE == 2)
			{
				HAL_I2C_Mem_Read_DMA(&hi2c3, ADD_I2C_ICM20948, ADD_ACCEL_XOUT_H, I2C_MEMADD_SIZE_8BIT, imuDataBuffer, 12);
			}
		}
	}
}

void HAL_I2C_MemRxCpltCallback(I2C_HandleTypeDef *hi2c)
{
	if (hi2c->Instance == I2C3)
	{
		if (I2C_TRANSMIT_MODE == 1)
		{
			HAL_I2C_Mem_Read_IT(hi2c, ADD_I2C_ICM20948, ADD_ACCEL_XOUT_H, I2C_MEMADD_SIZE_8BIT, imuDataBuffer, 12);
		}

		if (I2C_TRANSMIT_MODE == 2)
		{
			HAL_I2C_Mem_Read_DMA(hi2c, ADD_I2C_ICM20948, ADD_ACCEL_XOUT_H, I2C_MEMADD_SIZE_8BIT, imuDataBuffer, 12);
		}
	}
}

void ICM20948_Read_Accel(void)
{
	Accel_X_RAW = (int16_t)(imuDataBuffer[0] << 8 | imuDataBuffer[1]);
	Accel_Y_RAW = (int16_t)(imuDataBuffer[2] << 8 | imuDataBuffer[3]);
	Accel_Z_RAW = (int16_t)(imuDataBuffer[4] << 8 | imuDataBuffer[5]);

	Ax = Accel_X_RAW / 16384.0;
	Ay = Accel_Y_RAW / 16384.0;
	Az = Accel_Z_RAW / 16384.0;
}

void ICM20948_Read_Gyro(void)
{
	Gyro_X_RAW = (int16_t)(imuDataBuffer[6] << 8 | imuDataBuffer[7]);
	Gyro_Y_RAW = (int16_t)(imuDataBuffer[8] << 8 | imuDataBuffer[9]);
	Gyro_Z_RAW = (int16_t)(imuDataBuffer[10] << 8 | imuDataBuffer[11]);

	Gx = Gyro_X_RAW / 32.8;
	Gy = Gyro_Y_RAW / 32.8;
	Gz = Gyro_Z_RAW / 32.8;
}

void ICM20948_Read_Accel_Polling(void)
{
	HAL_I2C_Mem_Read(&hi2c3, ADD_I2C_ICM20948, ADD_ACCEL_XOUT_H, 1, imuDataBuffer, 6, 100);
	ICM20948_Read_Accel();
}

void ICM20948_Read_Gyro_Polling(void)
{
	HAL_I2C_Mem_Read(&hi2c3, ADD_I2C_ICM20948, ADD_GYRO_XOUT_H, 1, &imuDataBuffer[6], 6, 100);
	ICM20948_Read_Gyro();
}

void ICM20948_Read_Magn_Polling(void)
{
	HAL_I2C_Mem_Read(&hi2c3, ADD_I2C_SLV0_ADDR_READ, ADD_HXL, I2C_MEMADD_SIZE_8BIT, magDataBuffer, 6, HAL_MAX_DELAY);

    Magn_X_RAW = (int16_t)((magDataBuffer[1] << 8) | magDataBuffer[0]);
    Magn_Y_RAW = (int16_t)((magDataBuffer[3] << 8) | magDataBuffer[2]);
    Magn_Z_RAW = (int16_t)((magDataBuffer[5] << 8) | magDataBuffer[4]);
}
