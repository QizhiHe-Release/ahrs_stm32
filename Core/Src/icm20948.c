#include "main.h"
#include "i2c.h"
#include "icm20948.h"

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

    if (HAL_I2C_IsDeviceReady(&hi2c3, I2C_ADDRESS, 100, HAL_MAX_DELAY) == HAL_OK)
    {
		Data = REG_BANK_0;
        HAL_I2C_Mem_Write(&hi2c3, I2C_ADDRESS, REG_BANK_SEL, 1, &Data, 1, HAL_MAX_DELAY);
        HAL_I2C_Mem_Read(&hi2c3, I2C_ADDRESS, WHO_AM_I, 1, &check, 1, HAL_MAX_DELAY);

        if (check == 0xEA)
        {
			Data = DEVICE_RESET;
			HAL_I2C_Mem_Write(&hi2c3, I2C_ADDRESS, PWR_MGMT_1, 1, &Data, 1, HAL_MAX_DELAY);	
			HAL_Delay(10);

			Data = CLKSEL;
			HAL_I2C_Mem_Write(&hi2c3, I2C_ADDRESS, PWR_MGMT_1, 1, &Data, 1, HAL_MAX_DELAY);
			Data = REG_BANK_2;
			HAL_I2C_Mem_Write(&hi2c3, I2C_ADDRESS, REG_BANK_SEL, 1, &Data, 1, HAL_MAX_DELAY);
			Data = 0x04; 
			HAL_I2C_Mem_Write(&hi2c3, I2C_ADDRESS, GYRO_SMPLRT_DIV, 1, &Data, 1, HAL_MAX_DELAY);
			Data = 0x05;
			HAL_I2C_Mem_Write(&hi2c3, I2C_ADDRESS, GYRO_CONFIG_1, 1, &Data, 1, HAL_MAX_DELAY);
			Data = 0x04;
			HAL_I2C_Mem_Write(&hi2c3, I2C_ADDRESS, ACCEL_SMPLRT_DIV_2, 1, &Data, 1, HAL_MAX_DELAY);
			Data = 0x01;
			HAL_I2C_Mem_Write(&hi2c3, I2C_ADDRESS, ACCEL_CONFIG, 1, &Data, 1, HAL_MAX_DELAY);
			Data = REG_BANK_0;
			HAL_I2C_Mem_Write(&hi2c3, I2C_ADDRESS, REG_BANK_SEL, 1, &Data, 1, HAL_MAX_DELAY);
			HAL_Delay(100);
        }
    }
}

// TODO: using DMA
void ICM20948_Read_Accel(void)
{
	uint8_t Rec_Data[6];

	HAL_I2C_Mem_Read(&hi2c3, I2C_ADDRESS, ACCEL_XOUT_H, 1, Rec_Data, 6, 1000);

	Accel_X_RAW = (int16_t)(Rec_Data[0] << 8 | Rec_Data [1]);
	Accel_Y_RAW = (int16_t)(Rec_Data[2] << 8 | Rec_Data [3]);
	Accel_Z_RAW = (int16_t)(Rec_Data[4] << 8 | Rec_Data [5]);

	Ax = Accel_X_RAW/16384.0;
	Ay = Accel_Y_RAW/16384.0;
	Az = Accel_Z_RAW/16384.0;
}

// TODO: using DMA
void ICM20948_Read_Gyro(void)
{
	uint8_t Rec_Data[6];

	HAL_I2C_Mem_Read (&hi2c3, I2C_ADDRESS, GYRO_XOUT_H, 1, Rec_Data, 6, 1000);

	Gyro_X_RAW = (int16_t)(Rec_Data[0] << 8 | Rec_Data [1]);
	Gyro_Y_RAW = (int16_t)(Rec_Data[2] << 8 | Rec_Data [3]);
	Gyro_Z_RAW = (int16_t)(Rec_Data[4] << 8 | Rec_Data [5]);

	Gx = Gyro_X_RAW/32.8;
	Gy = Gyro_Y_RAW/32.8;
	Gz = Gyro_Z_RAW/32.8;
}

// TODO: read IMU DMP data
