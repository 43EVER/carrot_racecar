#ifndef  __CAR_MOTOR_H__
#define  __CAR_MOTOR_H__

#include "common.h"
#include "include.h"
#include  "car_struct.h"            //���п����õ��Ľṹ�������



void  motor_control(Motor_pid_data *motor,SPEED_STATE *speed);  //�������
//void pluse_bubble(uint32 r[], uint32 n);
void average_wave_filtering(Motor_pid_data *motor);
//void moving_average_wave_filtering(Motor_pid_data *motor);
void motor_init();

#endif