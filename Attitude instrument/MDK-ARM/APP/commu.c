#include "commu.h"
#include "NRF24L01.h"

#define max_step 5
uint8_t BUF[5]={0};//四位分别代表 左(-) 右(+) 上(-) 下(+) 第五位：1：左键 2：中键 3：右键
int LR,UN;

uint8_t system_id = 1;
uint8_t component_id = 1;
mavlink_message_t msg1;

extern UART_HandleTypeDef huart1;
uint8_t tmp_buf[33];
uint16_t len=0;

void data_process()
{
	//pitch:左负右正，-90~90
	//roll：上正下负
	LR = (int)attitude_pitch / 5;
	UN = (int)attitude_roll / 5;
	if(LR>0)
	{
		BUF[1] = abs(LR);
		BUF[0] = 0;
	}
	else
	{
		BUF[0] = abs(LR);
		BUF[1] = 0;
	}
	if(UN>0)
	{
		BUF[2] = abs(UN);
		BUF[3] = 0;
	}
	else
	{
		BUF[3] = abs(UN);
		BUF[2] = 0;
	}

}

extern uint8_t key;
void sent_data()
{
	data_process();
	/* 用串口通过mavlink协议发 */
//	mavlink_msg_rc_channels_pack(system_id, component_id, &msg1,
//												 0, 8, BUF[0], BUF[1], BUF[2], BUF[3], 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 254);
//	len = mavlink_msg_to_send_buffer(buf,&msg1);
//	HAL_UART_Transmit(&huart1, buf, len, 0xffff);
	
//	printf("%6f %6f %6f %6f %6f %6f\r\n ",imu_data.ax,imu_data.ay,imu_data.az,imu_data.gx,imu_data.gy,imu_data.gz);
	tmp_buf[0]=BUF[0];
	tmp_buf[1]=BUF[1];
	tmp_buf[2]=BUF[2];
	tmp_buf[3]=BUF[3];
	tmp_buf[4]=key;
	
	//printf("NRF24L01发送数据：%s\r\n",tmp_buf);
	NRF24L01_TxPacket(tmp_buf);
	HAL_GPIO_TogglePin(LED4_GPIO_Port, LED4_Pin);
	
}
