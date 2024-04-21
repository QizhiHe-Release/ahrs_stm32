#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

#include <cstdint>

    typedef enum
    {
        IMU_EN_SENSOR_TYPE_NULL = 0,
        IMU_EN_SENSOR_TYPE_ICM20948,
        IMU_EN_SENSOR_TYPE_BMP280,
        IMU_EN_SENSOR_TYPE_MAX
    } IMU_EN_SENSOR_TYPE;

    typedef struct imu_st_angles_data_tag
    {
        float fYaw;
        float fPitch;
        float fRoll;
    } IMU_ST_ANGLES_DATA;

    typedef struct imu_st_sensor_data_tag
    {
        int16_t s16X;
        int16_t s16Y;
        int16_t s16Z;
    } IMU_ST_SENSOR_DATA;

    typedef struct icm20948_st_avg_data_tag
    {
        uint8_t u8Index;
        int16_t s16AvgBuffer[8];
    } ICM20948_ST_AVG_DATA;

    typedef struct
    {
        uint16_t T1;    /*<calibration T1 data*/
        int16_t T2;     /*<calibration T2 data*/
        int16_t T3;     /*<calibration T3 data*/
        uint16_t P1;    /*<calibration P1 data*/
        int16_t P2;     /*<calibration P2 data*/
        int16_t P3;     /*<calibration P3 data*/
        int16_t P4;     /*<calibration P4 data*/
        int16_t P5;     /*<calibration P5 data*/
        int16_t P6;     /*<calibration P6 data*/
        int16_t P7;     /*<calibration P7 data*/
        int16_t P8;     /*<calibration P8 data*/
        int16_t P9;     /*<calibration P9 data*/
        int32_t T_fine; /*<calibration t_fine data*/
    } BMP280_HandleTypeDef;

    typedef struct
    {
        uint8_t Index;
        int32_t AvgBuffer[8];
    } BMP280_AvgTypeDef;

    typedef struct
    {
        float gyro[3];
        float accl[3];
        float magn[3];
    } IMU_DATA;

    class ICM20948_BMP280
    {
    public:
        // icm-20948
        constexpr static uint8_t I2C_ADD_ICM20948 = 0xD0;
        constexpr static uint8_t I2C_ADD_ICM20948_AK09916 = 0x0C;
        constexpr static uint8_t I2C_ADD_ICM20948_AK09916_READ = 0x80;
        constexpr static uint8_t I2C_ADD_ICM20948_AK09916_WRITE = 0x00;
        constexpr static uint8_t REG_ADD_WIA = 0x00;
        constexpr static uint8_t REG_VAL_WIA = 0xEA;
        constexpr static uint8_t REG_ADD_USER_CTRL = 0x03;
        constexpr static uint8_t REG_VAL_BIT_DMP_EN = 0x80;
        constexpr static uint8_t REG_VAL_BIT_FIFO_EN = 0x40;
        constexpr static uint8_t REG_VAL_BIT_I2C_MST_EN = 0x20;
        constexpr static uint8_t REG_VAL_BIT_I2C_IF_DIS = 0x10;
        constexpr static uint8_t REG_VAL_BIT_DMP_RST = 0x08;
        constexpr static uint8_t REG_VAL_BIT_DIAMOND_DMP_RST = 0x04;
        constexpr static uint8_t REG_ADD_PWR_MIGMT_1 = 0x06;
        constexpr static uint8_t REG_VAL_ALL_RGE_RESET = 0x80;
        constexpr static uint8_t REG_VAL_RUN_MODE = 0x01;
        constexpr static uint8_t REG_ADD_LP_CONFIG = 0x05;
        constexpr static uint8_t REG_ADD_PWR_MGMT_1 = 0x06;
        constexpr static uint8_t REG_ADD_PWR_MGMT_2 = 0x07;
        constexpr static uint8_t REG_ADD_ACCEL_XOUT_H = 0x2D;
        constexpr static uint8_t REG_ADD_ACCEL_XOUT_L = 0x2E;
        constexpr static uint8_t REG_ADD_ACCEL_YOUT_H = 0x2F;
        constexpr static uint8_t REG_ADD_ACCEL_YOUT_L = 0x30;
        constexpr static uint8_t REG_ADD_ACCEL_ZOUT_H = 0x31;
        constexpr static uint8_t REG_ADD_ACCEL_ZOUT_L = 0x32;
        constexpr static uint8_t REG_ADD_GYRO_XOUT_H = 0x33;
        constexpr static uint8_t REG_ADD_GYRO_XOUT_L = 0x34;
        constexpr static uint8_t REG_ADD_GYRO_YOUT_H = 0x35;
        constexpr static uint8_t REG_ADD_GYRO_YOUT_L = 0x36;
        constexpr static uint8_t REG_ADD_GYRO_ZOUT_H = 0x37;
        constexpr static uint8_t REG_ADD_GYRO_ZOUT_L = 0x38;
        constexpr static uint8_t REG_ADD_EXT_SENS_DATA_00 = 0x3B;
        constexpr static uint8_t REG_ADD_REG_BANK_SEL = 0x7F;
        constexpr static uint8_t REG_VAL_REG_BANK_0 = 0x00;
        constexpr static uint8_t REG_VAL_REG_BANK_1 = 0x10;
        constexpr static uint8_t REG_VAL_REG_BANK_2 = 0x20;
        constexpr static uint8_t REG_VAL_REG_BANK_3 = 0x30;
        constexpr static uint8_t REG_ADD_GYRO_SMPLRT_DIV = 0x00;
        constexpr static uint8_t REG_ADD_GYRO_CONFIG_1 = 0x01;
        constexpr static uint8_t REG_VAL_BIT_GYRO_DLPCFG_2 = 0x10;
        constexpr static uint8_t REG_VAL_BIT_GYRO_DLPCFG_4 = 0x20;
        constexpr static uint8_t REG_VAL_BIT_GYRO_DLPCFG_6 = 0x30;
        constexpr static uint8_t REG_VAL_BIT_GYRO_FS_250DPS = 0x00;
        constexpr static uint8_t REG_VAL_BIT_GYRO_FS_500DPS = 0x02;
        constexpr static uint8_t REG_VAL_BIT_GYRO_FS_1000DPS = 0x04;
        constexpr static uint8_t REG_VAL_BIT_GYRO_FS_2000DPS = 0x06;
        constexpr static uint8_t REG_VAL_BIT_GYRO_DLPF = 0x01;
        constexpr static uint8_t REG_ADD_ACCEL_SMPLRT_DIV_2 = 0x11;
        constexpr static uint8_t REG_ADD_ACCEL_CONFIG = 0x14;
        constexpr static uint8_t REG_VAL_BIT_ACCEL_DLPCFG_2 = 0x10;
        constexpr static uint8_t REG_VAL_BIT_ACCEL_DLPCFG_4 = 0x20;
        constexpr static uint8_t REG_VAL_BIT_ACCEL_DLPCFG_6 = 0x30;
        constexpr static uint8_t REG_VAL_BIT_ACCEL_FS_2g = 0x00;
        constexpr static uint8_t REG_VAL_BIT_ACCEL_FS_4g = 0x02;
        constexpr static uint8_t REG_VAL_BIT_ACCEL_FS_8g = 0x04;
        constexpr static uint8_t REG_VAL_BIT_ACCEL_FS_16g = 0x06;
        constexpr static uint8_t REG_VAL_BIT_ACCEL_DLPF = 0x01;
        constexpr static uint8_t REG_ADD_I2C_SLV0_ADDR = 0x03;
        constexpr static uint8_t REG_ADD_I2C_SLV0_REG = 0x04;
        constexpr static uint8_t REG_ADD_I2C_SLV0_CTRL = 0x05;
        constexpr static uint8_t REG_VAL_BIT_SLV0_EN = 0x80;
        constexpr static uint8_t REG_VAL_BIT_MASK_LEN = 0x07;
        constexpr static uint8_t REG_ADD_I2C_SLV0_DO = 0x06;
        constexpr static uint8_t REG_ADD_I2C_SLV1_ADDR = 0x07;
        constexpr static uint8_t REG_ADD_I2C_SLV1_REG = 0x08;
        constexpr static uint8_t REG_ADD_I2C_SLV1_CTRL = 0x09;
        constexpr static uint8_t REG_ADD_I2C_SLV1_DO = 0x0A;
        constexpr static uint8_t REG_ADD_MAG_WIA1 = 0x00;
        constexpr static uint8_t REG_VAL_MAG_WIA1 = 0x48;
        constexpr static uint8_t REG_ADD_MAG_WIA2 = 0x01;
        constexpr static uint8_t REG_VAL_MAG_WIA2 = 0x09;
        constexpr static uint8_t REG_ADD_MAG_ST2 = 0x10;
        constexpr static uint8_t REG_ADD_MAG_DATA = 0x11;
        constexpr static uint8_t REG_ADD_MAG_CNTL2 = 0x31;
        constexpr static uint8_t REG_VAL_MAG_MODE_PD = 0x00;
        constexpr static uint8_t REG_VAL_MAG_MODE_SM = 0x01;
        constexpr static uint8_t REG_VAL_MAG_MODE_10HZ = 0x02;
        constexpr static uint8_t REG_VAL_MAG_MODE_20HZ = 0x04;
        constexpr static uint8_t REG_VAL_MAG_MODE_50HZ = 0x05;
        constexpr static uint8_t REG_VAL_MAG_MODE_100HZ = 0x08;
        constexpr static uint8_t REG_VAL_MAG_MODE_ST = 0x10;
        // bmp280
        constexpr static uint8_t BMP280_AD0_LOW = 0xEC;
        constexpr static uint8_t BMP280_AD0_HIGH = 0xEE;
        constexpr static uint8_t BMP280_ADDR = 0xEE;
        constexpr static uint8_t BMP280_REGISTER_DIG_T1 = 0x88;
        constexpr static uint8_t BMP280_REGISTER_DIG_T2 = 0x8A;
        constexpr static uint8_t BMP280_REGISTER_DIG_T3 = 0x8C;
        constexpr static uint8_t BMP280_REGISTER_DIG_P1 = 0x8E;
        constexpr static uint8_t BMP280_REGISTER_DIG_P2 = 0x90;
        constexpr static uint8_t BMP280_REGISTER_DIG_P3 = 0x92;
        constexpr static uint8_t BMP280_REGISTER_DIG_P4 = 0x94;
        constexpr static uint8_t BMP280_REGISTER_DIG_P5 = 0x96;
        constexpr static uint8_t BMP280_REGISTER_DIG_P6 = 0x98;
        constexpr static uint8_t BMP280_REGISTER_DIG_P7 = 0x9A;
        constexpr static uint8_t BMP280_REGISTER_DIG_P8 = 0x9C;
        constexpr static uint8_t BMP280_REGISTER_DIG_P9 = 0x9E;
        constexpr static uint8_t BMP280_REGISTER_CHIPID = 0xD0;
        constexpr static uint8_t BMP280_REGISTER_VERSION = 0xD1;
        constexpr static uint8_t BMP280_REGISTER_SOFTRESET = 0xE0;
        constexpr static uint8_t BMP280_REGISTER_STATUS = 0xF3;
        constexpr static uint8_t BMP280_REGISTER_CONTROL = 0xF4;
        constexpr static uint8_t BMP280_REGISTER_CONFIG = 0xF5;
        constexpr static uint8_t BMP280_TEMP_XLSB_REG = 0xFC;
        constexpr static uint8_t BMP280_TEMP_LSB_REG = 0xFB;
        constexpr static uint8_t BMP280_TEMP_MSB_REG = 0xFA;
        constexpr static uint8_t BMP280_PRESS_XLSB_REG = 0xF9;
        constexpr static uint8_t BMP280_PRESS_LSB_REG = 0xF8;
        constexpr static uint8_t BMP280_PRESS_MSB_REG = 0xF7;
        constexpr static uint8_t BMP280_DIG_T1_LSB_REG = 0x88;
        constexpr static uint8_t BMP280_DIG_T1_MSB_REG = 0x89;
        constexpr static uint8_t BMP280_DIG_T2_LSB_REG = 0x8A;
        constexpr static uint8_t BMP280_DIG_T2_MSB_REG = 0x8B;
        constexpr static uint8_t BMP280_DIG_T3_LSB_REG = 0x8C;
        constexpr static uint8_t BMP280_DIG_T3_MSB_REG = 0x8D;
        constexpr static uint8_t BMP280_DIG_P1_LSB_REG = 0x8E;
        constexpr static uint8_t BMP280_DIG_P1_MSB_REG = 0x8F;
        constexpr static uint8_t BMP280_DIG_P2_LSB_REG = 0x90;
        constexpr static uint8_t BMP280_DIG_P2_MSB_REG = 0x91;
        constexpr static uint8_t BMP280_DIG_P3_LSB_REG = 0x92;
        constexpr static uint8_t BMP280_DIG_P3_MSB_REG = 0x93;
        constexpr static uint8_t BMP280_DIG_P4_LSB_REG = 0x94;
        constexpr static uint8_t BMP280_DIG_P4_MSB_REG = 0x95;
        constexpr static uint8_t BMP280_DIG_P5_LSB_REG = 0x96;
        constexpr static uint8_t BMP280_DIG_P5_MSB_REG = 0x97;
        constexpr static uint8_t BMP280_DIG_P6_LSB_REG = 0x98;
        constexpr static uint8_t BMP280_DIG_P6_MSB_REG = 0x99;
        constexpr static uint8_t BMP280_DIG_P7_LSB_REG = 0x9A;
        constexpr static uint8_t BMP280_DIG_P7_MSB_REG = 0x9B;
        constexpr static uint8_t BMP280_DIG_P8_LSB_REG = 0x9C;
        constexpr static uint8_t BMP280_DIG_P8_MSB_REG = 0x9D;
        constexpr static uint8_t BMP280_DIG_P9_LSB_REG = 0x9E;
        constexpr static uint8_t BMP280_DIG_P9_MSB_REG = 0x9F;

        // icm20948
        void imuInit(IMU_EN_SENSOR_TYPE *penMotionSensorType, IMU_EN_SENSOR_TYPE *penPressureType);
        void imuDataGet(IMU_ST_ANGLES_DATA *pstAngles,
                        IMU_ST_SENSOR_DATA *pstGyroRawData,
                        IMU_ST_SENSOR_DATA *pstAccelRawData,
                        IMU_ST_SENSOR_DATA *pstMagnRawData);
        // bmp280
        void pressSensorDataGet(int32_t *ps32Temperature, int32_t *ps32Pressure, int32_t *ps32Altitude);

    private:
        // i2c
        uint8_t I2C_ReadOneByte(uint8_t DevAddr, uint8_t RegAddr);
        void I2C_WriteOneByte(uint8_t DevAddr, uint8_t RegAddr, uint8_t value);

        // icm20948
        void icm20948init(void);
        bool icm20948Check(void);
        bool icm20948MagCheck(void);
        void icm20948GyroRead(int16_t *ps16X, int16_t *ps16Y, int16_t *ps16Z);
        void icm20948AccelRead(int16_t *ps16X, int16_t *ps16Y, int16_t *ps16Z);
        void icm20948MagRead(int16_t *ps16X, int16_t *ps16Y, int16_t *ps16Z);
        void icm20948ReadSecondary(uint8_t u8I2CAddr, uint8_t u8RegAddr, uint8_t u8Len, uint8_t *pu8data);
        void icm20948WriteSecondary(uint8_t u8I2CAddr, uint8_t u8RegAddr, uint8_t u8data);
        void icm20948GyroOffset(void);
        void icm20948CalAvgValue(uint8_t *pIndex, int16_t *pAvgBuffer, int16_t InVal, int32_t *pOutVal);
        void imuAHRSupdate(float gx, float gy, float gz, float ax, float ay, float az, float mx, float my, float mz);
        float invSqrt(float x);

        // bmp280
        void bmp280Init(void);
        bool bmp280Check(void);
        void bmp280ReadCalibration(void);
        void bmp280TandPGet(float *temperature, float *pressure);
        void bmp280CalAvgValue(uint8_t *pIndex, int32_t *pAvgBuffer, int32_t InVal, int32_t *pOutVal);
        void bmp280CalculateAbsoluteAltitude(int32_t *pAltitude, int32_t PressureVal);
        float bmp280CompensateTemperature(int32_t adc_T);
        float bmp280CompensatePressure(int32_t adc_P);
    };

#ifdef __cplusplus
}
#endif
