#include "LED.h"

void LED_Callback(int max_duty1)
{
	
	static int cur_duty = 10;
	static int finish_flag = 1;
	static int flag = 0;	//0：变亮阶段	1：变暗阶段
	static int LED_ID = 0;
	int max_duty = max_duty1;
	int delta_duty = (int)max_duty/50.f;
	
	printf("%5d %5d %5d %d %d\r\n ",max_duty1,cur_duty,delta_duty,finish_flag,LED_ID);
	
	if(finish_flag == 1)//一个灯已灭,准备下个呼吸灯的参数
	{
		 max_duty = max_duty1;
		 delta_duty = max_duty/50;//保证亮：500ms，灭：500ms
		 finish_flag = 0;//新一个灯开始呼吸，即改变了maxduty后只有在下个灯才会有效
	}
	if(finish_flag == 0)
	{
			switch(LED_ID)
			{
				case 1:
					__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,cur_duty);
					__HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_3,0);
					__HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_4,0);
					break;
				case 2:
					__HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_3,cur_duty);
					__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,0);
					__HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_4,0);
					break;
				case 3:
					__HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_4,cur_duty);
					__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,0);
					__HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_3,0);
					break;
			}
			if(max_duty < 50)
			{
					__HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_4,0);
					__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,0);
					__HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_3,0);
			}				
			
			/* 更新状态 */
			if(cur_duty >= max_duty)
			{
				cur_duty = max_duty;
				flag = 1;
			}
			if(cur_duty <= 0)
			{
				cur_duty = 0;
				flag = 0;
				finish_flag = 1;
				LED_ID++;//下一个灯亮
			}
			if(LED_ID>3) LED_ID = 1;
			
			
			if(flag == 0)
			{
				cur_duty += delta_duty;
			}
			else
			{
				cur_duty -= delta_duty;
			}


	}
	
}

//按键处理函数
//返回按键值
//mode:0,不支持连续按;1,支持连续按;
//0，没有任何按键按下
//1，WKUP按下 WK_UP
//注意此函数有响应优先级,KEY0>KEY1>WK_UP!!
uint8_t KEY_Scan(uint8_t mode)
{
    static uint8_t key_up=1;     //按键松开标志
    if(mode==1)key_up=1;    //支持连按
		int i, j, k;
		i=j=k=0;
    if(key_up&&
		(HAL_GPIO_ReadPin(KEY1_GPIO_Port, KEY1_Pin)==0||
		 HAL_GPIO_ReadPin(KEY2_GPIO_Port, KEY2_Pin)==0||
	 	 HAL_GPIO_ReadPin(KEY3_GPIO_Port, KEY3_Pin)==0))	
    {
        HAL_Delay(10);
        key_up=0;
        if(HAL_GPIO_ReadPin(KEY1_GPIO_Port, KEY1_Pin)==0)  i=1;
        if(HAL_GPIO_ReadPin(KEY2_GPIO_Port, KEY2_Pin)==0)  j=1;
        if(HAL_GPIO_ReadPin(KEY3_GPIO_Port, KEY3_Pin)==0)  k=1;   
				return i*1 + j*2 + k*4;
    }
		
		else if(HAL_GPIO_ReadPin(KEY1_GPIO_Port, KEY1_Pin)==1&&
						HAL_GPIO_ReadPin(KEY2_GPIO_Port, KEY2_Pin)==1&&
						HAL_GPIO_ReadPin(KEY3_GPIO_Port, KEY3_Pin)==1)
			//(KEY0==1&&KEY1==1&&WK_UP==0)
		{
			key_up=1;
		}
    return 0;   //无按键按下
}