#ifndef __PID_H
#define __PID_H

typedef struct
{
    //可调参数
    float Kp;
    float Ki;
    float Kd;

    //目标值
    float target;

    //输出限幅
    float output_max;
    float output_min;

    //内部变量
    float error;
    float last_error;
		float current_value;
		float filtered_value;
    float integral;
    float pwm_v;
}PID_t;

/**
 * @brief:PID参数初始化
 * @param:
 */
void PID_Init(PID_t*pid,float Kp,float Ki,float Kd,float out_max,float out_min);

/**
 * @brief:PID输出
 */
float PID_Calculate(PID_t*pid);
#endif
