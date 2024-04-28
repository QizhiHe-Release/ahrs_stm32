#include "main.h"
#include "i2c.h"
#include "icm20948.h"

uint8_t imuDataBuffer[12];

int16_t Accel_X_RAW = 0;
int16_t Accel_Y_RAW = 0;
int16_t Accel_Z_RAW = 0;

int16_t Gyro_X_RAW = 0;
int16_t Gyro_Y_RAW = 0;
int16_t Gyro_Z_RAW = 0;

float Ax, Ay, Az, Gx, Gy, Gz;


void ICM20948_Init(void)
{
	uint8_t check;
	uint8_t Data;

	if (HAL_I2C_IsDeviceReady(&hi2c3, ADD_I2C_ADDRESS, 100, HAL_MAX_DELAY) == HAL_OK)
	{
		Data = CMD_REG_BANK_0;
		HAL_I2C_Mem_Write(&hi2c3, ADD_I2C_ADDRESS, ADD_REG_BANK_SEL, 1, &Data, 1, HAL_MAX_DELAY);
		HAL_I2C_Mem_Read(&hi2c3, ADD_I2C_ADDRESS, ADD_WHO_AM_I, 1, &check, 1, HAL_MAX_DELAY);

		if (check == 0xEA)
		{
			Data = CMD_DEVICE_RESET;
			HAL_I2C_Mem_Write(&hi2c3, ADD_I2C_ADDRESS, ADD_PWR_MGMT_1, 1, &Data, 1, HAL_MAX_DELAY);
			HAL_Delay(10);

			Data = CMD_CLKSEL;
			HAL_I2C_Mem_Write(&hi2c3, ADD_I2C_ADDRESS, ADD_PWR_MGMT_1, 1, &Data, 1, HAL_MAX_DELAY);
			Data = CMD_REG_BANK_2;
			HAL_I2C_Mem_Write(&hi2c3, ADD_I2C_ADDRESS, ADD_REG_BANK_SEL, 1, &Data, 1, HAL_MAX_DELAY);
			Data = 0x04;
			HAL_I2C_Mem_Write(&hi2c3, ADD_I2C_ADDRESS, ADD_GYRO_SMPLRT_DIV, 1, &Data, 1, HAL_MAX_DELAY);
			Data = 0x05;
			HAL_I2C_Mem_Write(&hi2c3, ADD_I2C_ADDRESS, ADD_GYRO_CONFIG_1, 1, &Data, 1, HAL_MAX_DELAY);
			Data = 0x04;
			HAL_I2C_Mem_Write(&hi2c3, ADD_I2C_ADDRESS, ADD_ACCEL_SMPLRT_DIV_2, 1, &Data, 1, HAL_MAX_DELAY);
			Data = 0x01;
			HAL_I2C_Mem_Write(&hi2c3, ADD_I2C_ADDRESS, ADD_ACCEL_CONFIG, 1, &Data, 1, HAL_MAX_DELAY);
			Data = CMD_REG_BANK_0;
			HAL_I2C_Mem_Write(&hi2c3, ADD_I2C_ADDRESS, ADD_REG_BANK_SEL, 1, &Data, 1, HAL_MAX_DELAY);
			HAL_Delay(100);
			HAL_I2C_Mem_Read_DMA(&hi2c3, ADD_I2C_ADDRESS, ADD_ACCEL_XOUT_H, I2C_MEMADD_SIZE_8BIT, imuDataBuffer, 12);
			HAL_Delay(100);
		}
	}
}

void HAL_I2C_MemRxCpltCallback(I2C_HandleTypeDef *hi2c)
{
	if (hi2c->Instance == I2C3)
	{
		HAL_I2C_Mem_Read_DMA(hi2c, ADD_I2C_ADDRESS, ADD_ACCEL_XOUT_H, I2C_MEMADD_SIZE_8BIT, imuDataBuffer, 12);
	}
}

void ICM20948_Read_Accel_DMA(void)
{
	Accel_X_RAW = (int16_t)(imuDataBuffer[0] << 8 | imuDataBuffer[1]);
	Accel_Y_RAW = (int16_t)(imuDataBuffer[2] << 8 | imuDataBuffer[3]);
	Accel_Z_RAW = (int16_t)(imuDataBuffer[4] << 8 | imuDataBuffer[5]);

	Ax = Accel_X_RAW / 16384.0;
	Ay = Accel_Y_RAW / 16384.0;
	Az = Accel_Z_RAW / 16384.0;
}

void ICM20948_Read_Gyro_DMA(void)
{
	Gyro_X_RAW = (int16_t)(imuDataBuffer[6] << 8 | imuDataBuffer[7]);
	Gyro_Y_RAW = (int16_t)(imuDataBuffer[8] << 8 | imuDataBuffer[9]);
	Gyro_Z_RAW = (int16_t)(imuDataBuffer[10] << 8 | imuDataBuffer[11]);

	Gx = Gyro_X_RAW / 32.8;
	Gy = Gyro_Y_RAW / 32.8;
	Gz = Gyro_Z_RAW / 32.8;
}


// void ICM20948_Read_Accel(void)
// {
// 	uint8_t Rec_Data[6];

// 	HAL_I2C_Mem_Read(&hi2c3, ADD_I2C_ADDRESS, ADD_ACCEL_XOUT_H, 1, Rec_Data, 6, 100);

// 	Accel_X_RAW = (int16_t)(Rec_Data[0] << 8 | Rec_Data[1]);
// 	Accel_Y_RAW = (int16_t)(Rec_Data[2] << 8 | Rec_Data[3]);
// 	Accel_Z_RAW = (int16_t)(Rec_Data[4] << 8 | Rec_Data[5]);

// 	Ax = Accel_X_RAW / 16384.0;
// 	Ay = Accel_Y_RAW / 16384.0;
// 	Az = Accel_Z_RAW / 16384.0;
// }

// void ICM20948_Read_Gyro(void)
// {
// 	uint8_t Rec_Data[6];

// 	HAL_I2C_Mem_Read(&hi2c3, ADD_I2C_ADDRESS, ADD_GYRO_XOUT_H, 1, Rec_Data, 6, 100);

// 	Gyro_X_RAW = (int16_t)(Rec_Data[0] << 8 | Rec_Data[1]);
// 	Gyro_Y_RAW = (int16_t)(Rec_Data[2] << 8 | Rec_Data[3]);
// 	Gyro_Z_RAW = (int16_t)(Rec_Data[4] << 8 | Rec_Data[5]);

// 	Gx = Gyro_X_RAW / 32.8;
// 	Gy = Gyro_Y_RAW / 32.8;
// 	Gz = Gyro_Z_RAW / 32.8;
// }

// TODO: read IMU DMP data
