#include "USB.h"

/*buffer[0]表示按键状态 buffer[1]和buffer[2]分别表示X轴和Y轴移动量 buffer[3]鼠标滚动量*/
uint8_t buffer[4] = {0x00, 0x00, 0x00, 0x00};
uint8_t last_BUTTON=0;
uint32_t last_click_time_M = 0;


void Click_L()
{
		memset(buffer, 0, 4);
		buffer[0] = 1;
}

void Click_R()
{
		memset(buffer, 0, 4);
		buffer[0] = 2;
}

void Click_M()
{
		memset(buffer, 0, 4);
		buffer[0] = 4;
}

void Scroll(int8_t x)
{
	buffer[3] = x;
	USBD_HID_SendReport(&hUsbDeviceFS,buffer,4);//鼠标滚动
}

void Move(int8_t x,int8_t y)
{
  //memset(buffer, 0, 4);
	buffer[1]=x;
	buffer[2]=y;
	USBD_HID_SendReport(&hUsbDeviceFS,buffer,4);//鼠标移动
	HAL_Delay(10);
}

int8_t x_step;
int8_t y_step;
// 运动函数，根据UART接收到的数据移动
void MoveAccordingToBuffer(uint8_t *data) 
{
		int8_t max_step = 3;  
		uint8_t left_step = data[0];
		uint8_t right_step = data[1];
		uint8_t up_step = data[2];
		uint8_t down_step = data[3];
    // 计算x轴和y轴的移动步长
    x_step = max_step * (int8_t)((int16_t)right_step - left_step); // 向右为正，向左为负
    y_step = max_step * (int8_t)((int16_t)down_step - up_step);    // 向下为正，向上为负
	
    // 调用Move函数进行移动
    Move(x_step, y_step);
}
void key_callback(uint8_t *data)
{
	uint8_t key=data[4];
	switch(key)
	{
		case 1:
				Click_L();	
			break;
		case 2:
				Click_M();
				break;
		case 4:
				Click_R();	
			break;
		case 0:
				buffer[0] = 0;
			break;
	}
//	if(key == 2)//按住中键
//	{
//		Scroll(y_step/3);
//	}
	last_BUTTON = key;

}
