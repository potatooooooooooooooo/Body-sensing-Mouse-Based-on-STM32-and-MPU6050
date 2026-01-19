#include "ahrs.h"
#include <stdbool.h>
#include <stdio.h>

#define SAMPLE_PERIOD (0.005f) // replace this with actual sample period

FusionAhrs ahrs;

void navi_calculate()
{
	navi_prepare_imu_data();
	if(!imu_offset_flag)/* º∆À„Õ”¬›“«¡„∆Æ */
	{
		navi_glory_sum_offset();
		return;
	}
	else
	{
		const FusionVector gyroscope = {imu_data.gx*SEC2DEG, imu_data.gy*SEC2DEG, imu_data.gz*SEC2DEG}; // replace this with actual gyroscope data in degrees/s
		const FusionVector accelerometer = {imu_data.ax/9.8, imu_data.ay/9.8, imu_data.az/9.8}; // replace this with actual accelerometer data in g

		FusionAhrsUpdateNoMagnetometer(&ahrs, gyroscope, accelerometer, SAMPLE_PERIOD);

		const FusionEuler euler = FusionQuaternionToEuler(FusionAhrsGetQuaternion(&ahrs));

		attitude_roll = euler.angle.roll;
		attitude_pitch = euler.angle.pitch;
		attitude_yaw = euler.angle.yaw;
	}
}
