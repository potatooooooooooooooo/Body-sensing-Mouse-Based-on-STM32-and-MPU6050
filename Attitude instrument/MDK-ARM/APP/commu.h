#ifndef __commu_H
#define __commu_H

#include "stdio.h"
#include "stdint.h"
#include "imu_data.h"
#include "math.h"
#include "stm32f1xx_hal.h"
#include "string.h"
#include "mavlink.h"
#include "imu_data.h"
#include "main.h"

extern UART_HandleTypeDef huart1;

void sent_data();
void data_process();


#endif