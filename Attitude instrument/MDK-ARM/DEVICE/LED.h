#ifndef __LED_H
#define __LED_H

#include "main.h"
#include "stdio.h"
#include "stdint.h"
#include "tim.h"

void LED_Callback(int max_duty);
uint8_t KEY_Scan(uint8_t mode);

#endif
