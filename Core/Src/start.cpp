#include "start.h"
#include "main.h"
#include "usart.h"
#include "imu.h"
#include <string>
using namespace std;

extern uint8_t time1000ms, time2ms;

// for stm32cube monitor debug
float debug[10] = {0};

void start_up()
{
	ICM20948_BMP280 imu_baro;
	IMU_EN_SENSOR_TYPE enMotionSensorType, enPressureType;
	IMU_ST_ANGLES_DATA stAngles;
	IMU_ST_SENSOR_DATA stGyroRawData;
	IMU_ST_SENSOR_DATA stAccelRawData;
	IMU_ST_SENSOR_DATA stMagnRawData;
	// int32_t s32PressureVal = 0, s32TemperatureVal = 0, s32AltitudeVal = 0;

	imu_baro.imuInit(&enMotionSensorType, &enPressureType);
	if (IMU_EN_SENSOR_TYPE_ICM20948 == enMotionSensorType)
	{
		printf("Motion sersor is ICM-20948\n");
	}
	else
	{
		printf("Motion sersor NULL\n");
	}
	if (IMU_EN_SENSOR_TYPE_BMP280 == enPressureType)
	{
		printf("Pressure sersor is BMP280\n");
	}
	else
	{
		printf("Pressure sersor NULL\n");
	}

	while (1)
	{
		if (time1000ms)
		{
			string str = "Powered By QizhiHe, Wechat: 1210106584\r\n";
			HAL_UART_Transmit(&huart1, (uint8_t *)str.data(), str.size(), 0xff);
			HAL_GPIO_TogglePin(LED_STATE_GPIO_Port, LED_STATE_Pin);

			time1000ms = 0;
		}

		if (time2ms)
		{
			imu_baro.imuDataGet( &stAngles, &stGyroRawData, &stAccelRawData, &stMagnRawData);
			// imu_baro.pressSensorDataGet(&s32TemperatureVal, &s32PressureVal, &s32AltitudeVal);

			{
				debug[0] = stAngles.fPitch;
				debug[1] = stAngles.fRoll;
				debug[2] = stAngles.fYaw;
			}

			time2ms = 0;
		}
	}
}
