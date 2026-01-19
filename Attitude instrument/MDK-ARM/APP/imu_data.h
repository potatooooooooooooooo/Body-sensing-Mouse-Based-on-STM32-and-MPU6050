#ifndef __IMU_DATA_H
#define __IMU_DATA_H

#include "stm32f1xx_hal.h"
#include "filters.h"
#include "MPU6050driver.h" 

#define DEG2SEC 0.0174532925f
#define SEC2DEG 57.295779578f

typedef struct acc_raw_data_t {
    short x;
    short y;
    short z;
} acc_raw_data_t;

typedef struct gyro_raw_data_t {
    short roll;
    short pitch;
    short yaw;
} gyro_raw_data_t;

typedef struct imu_data_t {
    float gx;
		float gy;
	  float gz;
	  float ax;
	  float ay;
		float az;
} imu_data_t;

void navi_prepare_imu_data(void);
void navi_glory_sum_offset(void);
void Filter_init(void);

extern acc_raw_data_t  acc_data;
extern gyro_raw_data_t gyro_data;
extern imu_data_t imu_data;
extern float attitude_roll,attitude_pitch,attitude_yaw;	

extern uint8_t imu_init_flag;
extern uint8_t imu_offset_flag;	

#endif
