#ifndef __CONTROLLER_H
#define __CONTROLLER_H
#include "stm32f1xx_hal.h"

//控制器总初始化
void Controller_Init(void);

//设置目标位置
void Controller_Set_Target_Position(int32_t pos);

//中断函数使用
void Controller_Update_Callback(void);

#endif
