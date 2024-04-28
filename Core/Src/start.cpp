#include "start.h"
#include "main.h"
#include "usart.h"
#include "icm20948.h"
#include <string>
using namespace std;

extern uint8_t time1000ms, time5ms;

// for stm32cube monitor debug
float debug[20] = {0};

extern uint8_t imuDataBuffer[12];

extern int16_t Accel_X_RAW;
extern int16_t Accel_Y_RAW;
extern int16_t Accel_Z_RAW;

extern int16_t Gyro_X_RAW;
extern int16_t Gyro_Y_RAW;
extern int16_t Gyro_Z_RAW;

extern float Ax, Ay, Az, Gx, Gy, Gz;

void start_up()
{
	ICM20948_Init();
	// ICM20948 imu;
	// IMU_EN_SENSOR_TYPE enMotionSensorType, enPressureType;
	// IMU_ST_ANGLES_DATA stAngles;
	// IMU_ST_SENSOR_DATA stGyroData;
	// IMU_ST_SENSOR_DATA stAccelData;
	// IMU_ST_SENSOR_DATA stMagnData;
	// // int32_t s32PressureVal = 0, s32TemperatureVal = 0, s32AltitudeVal = 0;

	// imu.imuInit(&enMotionSensorType, &enPressureType);
	// if (IMU_EN_SENSOR_TYPE_ICM20948 == enMotionSensorType)
	// {
	// 	printf("Motion sersor is ICM-20948\n");
	// }
	// else
	// {
	// 	printf("Motion sersor NULL\n");
	// }
	// if (IMU_EN_SENSOR_TYPE_BMP280 == enPressureType)
	// {
	// 	printf("Pressure sersor is BMP280\n");
	// }
	// else
	// {
	// 	printf("Pressure sersor NULL\n");
	// }

	while (1)
	{
		if (time1000ms)
		{
			string str = "Powered By QizhiHe, Wechat: 1210106584\r\n";
			HAL_UART_Transmit(&huart1, (uint8_t *)str.data(), str.size(), 0xff);
			HAL_GPIO_TogglePin(LED_STATE_GPIO_Port, LED_STATE_Pin);

			time1000ms = 0;
		}

		if (time5ms)
		{
			ICM20948_Read_Accel_DMA();
			ICM20948_Read_Gyro_DMA();

			debug[0] = Accel_X_RAW;
			debug[1] = Accel_Y_RAW;
			debug[2] = Accel_Z_RAW;

			debug[3] = Gyro_X_RAW;
			debug[4] = Gyro_Y_RAW;
			debug[5] = Gyro_Z_RAW;

			debug[6] = Ax;
			debug[7] = Ay;
			debug[8] = Az;
			debug[9] = Gx;
			debug[10] = Gy;
			debug[11] = Gz;


			time5ms = 0;
		}
	}
}
