#include "bsp.h"

extern UART_HandleTypeDef huart1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;

extern Motor_t left_motor;
/**
 * @brief: 各模块初始化
 */
void BSP_Init(void)
{
    //电机初始化
    Motor_Init(&left_motor, &htim3, &htim2, TIM_CHANNEL_1, 
             MOTOR_IN1_GPIO_Port, MOTOR_IN1_Pin, 
             MOTOR_IN2_GPIO_Port, MOTOR_IN2_Pin);
    //VOFA通信初始化
    VOFA_Init(&huart1);
}
