#include "imu_data.h"

acc_raw_data_t  acc_data;
gyro_raw_data_t gyro_data;
imu_data_t imu_data;
double pitch_offset = 0.0, roll_offset = 0.0, yaw_offset = 0.0;
double  roll_offset_sum = 0.0, pitch_offset_sum = 0.0, yaw_offset_sum = 0.0;
float attitude_roll,attitude_pitch,attitude_yaw;

uint8_t imu_init_flag = 0;
uint8_t imu_offset_flag = 0;

//IIR滤波器参数变量定义
IIR_coeff_Typedef Filter_Param_Gx;
IIR_coeff_Typedef *pFilter_Param_Gx = &Filter_Param_Gx;
IIR_coeff_Typedef Filter_Param_Gy;
IIR_coeff_Typedef *pFilter_Param_Gy = &Filter_Param_Gy;
IIR_coeff_Typedef Filter_Param_Gz;
IIR_coeff_Typedef *pFilter_Param_Gz = &Filter_Param_Gz;
IIR_coeff_Typedef Filter_Param_Ax;
IIR_coeff_Typedef *pFilter_Param_Ax = &Filter_Param_Ax;
IIR_coeff_Typedef Filter_Param_Ay;
IIR_coeff_Typedef *pFilter_Param_Ay = &Filter_Param_Ay;
IIR_coeff_Typedef Filter_Param_Az;
IIR_coeff_Typedef *pFilter_Param_Az = &Filter_Param_Az;

/* IIR滤波器初始化  计算滤波器参数 */
void Filter_init(void)
{
	cal_iir_coeff(pFilter_Param_Gx, 200, 30);
  cal_iir_coeff(pFilter_Param_Gy, 200, 30);
  cal_iir_coeff(pFilter_Param_Gz, 200, 30);
	
	cal_iir_coeff(pFilter_Param_Ax, 200, 30);
  cal_iir_coeff(pFilter_Param_Ay, 200, 30);
  cal_iir_coeff(pFilter_Param_Az, 200, 30);
}

/*计算得到陀螺仪三轴零偏*/	
void navi_glory_sum_offset(void)
{
	static int i = 0;
	if(i >= 10)
	{
		roll_offset_sum += imu_data.gx;
		pitch_offset_sum+= imu_data.gy;
		yaw_offset_sum  += imu_data.gz;
	}
	i++;
	if(i>260)
	{
		roll_offset = roll_offset_sum/250;
		pitch_offset = pitch_offset_sum/250;
		yaw_offset = yaw_offset_sum/250;
		
		imu_offset_flag = 1;
	}
	
//		roll_offset = -0.1954662310928;
//		pitch_offset = -0.0006342781623825;
//		yaw_offset = -0.004137707221322;	
//	
//		imu_offset_flag = 1;
}

/*	更新陀螺仪与加速度计数据	*/	
/*	单位：rad/s	, m/s^2		*/
void navi_prepare_imu_data(void)
{
	
	MPU_Get_Gyroscope(&gyro_data.roll,&gyro_data.pitch,&gyro_data.yaw);
	MPU_Get_Accelerometer(&acc_data.x,&acc_data.y,&acc_data.z);
	
	if(!imu_offset_flag)
	{
		imu_data.gx = gyro_data.roll/16.4 * DEG2SEC;
		imu_data.gy = gyro_data.pitch/16.4 * DEG2SEC;
		imu_data.gz = gyro_data.yaw/16.4 * DEG2SEC;
	}
	else
	{
		imu_data.gx = gyro_data.roll/16.4 * DEG2SEC - roll_offset;
		imu_data.gy = gyro_data.pitch/16.4 * DEG2SEC - pitch_offset;
		imu_data.gz = gyro_data.yaw/16.4 * DEG2SEC - yaw_offset;
	}
	
//	imu_data.ax = acc_data.x/16384.f * 9.8;
//	imu_data.ay = acc_data.y/16384.f * 9.8;
//	imu_data.az = acc_data.z/16384.f * 9.8;
	
	imu_data.gx = get_iir_output(pFilter_Param_Gx, imu_data.gx);
	imu_data.gy = get_iir_output(pFilter_Param_Gy, imu_data.gy);
	imu_data.gz = get_iir_output(pFilter_Param_Gz, imu_data.gz);
	
	imu_data.ax = get_iir_output(pFilter_Param_Ax, acc_data.x/16384.f * 9.8);
	imu_data.ay = get_iir_output(pFilter_Param_Ay, acc_data.y/16384.f * 9.8);
	imu_data.az = get_iir_output(pFilter_Param_Az, acc_data.z/16384.f * 9.8);

/*a =

   0.102605618801820  -0.019464202711045   0.102433077074544   0.001205039356768   0.100548233953812   0.076944704800304
*/
	/* 加速度计六面校准 */
	//printf("%6f %6f %6f \r\n ",imu_data.ax,imu_data.ay,imu_data.az);
	const float acc_param_k[3] = {0.102575860494020 ,  0.102445129322964 ,  0.100383091010694};
	const float acc_param_a[3] = {-0.020134820730671 ,  0.000982454422219  , 0.071959665650744};
	imu_data.ax = acc_param_k[0] * imu_data.ax + acc_param_a[0];
	imu_data.ay = acc_param_k[1] * imu_data.ay + acc_param_a[1];
	imu_data.az = acc_param_k[2] * imu_data.az + acc_param_a[2];

}
