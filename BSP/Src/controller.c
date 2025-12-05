#include "controller.h"
#include "motor.h"
#include "pid.h"
#include "vofa.h"

extern UART_HandleTypeDef huart1;
extern Motor_t left_motor;

//PID实例
extern PID_t position_pid;
extern PID_t speed_pid;

//滤波参数
static const float filter_a=0.8f;

/**
 * @brief:控制器总初始化
 */
void Controller_Init(void)
{
    //位置环初始化
	PID_Init(&position_pid, 0.05f, 0.0f, 0.03f, 320.0f, -320.0f);
    //速度环初始化
  PID_Init(&speed_pid, 8.5f, 0.75f, 0.012f, 1000.0f, -1000.0f);
}

/**
 * @brief:设置目标位置
 * @param: pos 目标位置
 */
void Controller_Set_Target_Position(int32_t pos)
{
    position_pid.target=(float)pos;
}

/**
 * @brief:中断函数使用
 */
void Controller_Update_Callback(void)
{
    //获取当前位置和当前速度
    Motor_Update_Speed(&left_motor);
    position_pid.current_value=left_motor.total_pulses_count;
    speed_pid.current_value=left_motor.speed_rpm;

    //低通滤波
    speed_pid.filtered_value=filter_a*speed_pid.filtered_value+(1-filter_a)*speed_pid.current_value;

    //串级pid（速度环和位置环）
    float target_speed=PID_Calculate(&position_pid);//位置环计算目标速度
    speed_pid.target=target_speed;
    int16_t pwm_out=(int16_t)PID_Calculate(&speed_pid);

    //改变pwm输出
    Motor_Set_PWM(&left_motor,pwm_out);

    //每50ms发送一次数据
    static int send_sount=0;
    if(++send_sount>=5)
    {
        send_sount=0;
        float data_to_send[]={
														speed_pid.filtered_value,   //滤波速度
														speed_pid.current_value,    //当前速度
                            speed_pid.target,           //目标速度
                            position_pid.current_value, //当前位置
                            position_pid.target};       //目标位置
        VOFA_SendData(data_to_send,4);
    }

}
