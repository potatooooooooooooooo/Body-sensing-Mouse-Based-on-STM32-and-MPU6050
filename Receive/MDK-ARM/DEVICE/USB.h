#ifndef __USB_H
#define __USB_H

#include "usbd_hid.h"
#include <stdint.h>
#include <stdbool.h>
#include "main.h"

#define DOUBLE_CLICK_TIME 250 //双击最大间隔 单位：ms

extern USBD_HandleTypeDef hUsbDeviceFS;

bool is_double_click_L(void);
bool is_double_click_R(void);
unsigned char is_double_click_M(unsigned char currentkeynum);
void Click_L(void);
void Click_R(void);
void Click_M(void);
void Scroll(int8_t x);
void Move(int8_t x,int8_t y);
void MoveAccordingToBuffer(uint8_t *data);
void key_callback(uint8_t *data);

#endif
