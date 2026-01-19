#ifndef __MAHONY_H
#define __MAHONY_H

#include "stm32f1xx_hal.h"
#include "imu_data.h"
#include "MPU6050driver.h" 
#include "math.h"

#define sq(x) ((x)*(x))
#define DEGREES_TO_RADIANS(angle) ((angle) * 0.0174532925f)

static void imuComputeRotationMatrix(void);
void imuInit(void);
static float invSqrt(float x);

static void imuMahonyAHRSupdate(float dt, float gx, float gy, float gz,
                                uint8_t useAcc, float ax, float ay, float az,
                                uint8_t useMag, float mx, float my, float mz,
                                uint8_t useYaw, float yawError);
static void imuUpdateEulerAngles(void);
void imuCalculateEstimatedAttitude(void);
		
extern float rMat[3][3];																	

#endif
