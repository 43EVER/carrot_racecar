#ifndef __CAR_STRUCT_H__
#define __CAR_STRUCT_H__

/*********************������ز����Ľṹ��***********************/
#include "common.h"




//ADC
typedef struct
{

  uint32 ad_mid_val[10]; //AD������ֵ
  uint32 ad_add_val[10]; //AD������ֵ��
  int32 ad_avr_val[6]; //AD����ƽ��ֵ
  uint32 ad_max_val[10]; //AD���ֵ
  uint32 ad_min_val[10]; //AD��Сֵ

 
  uint32 ad_act_val[6][15]; //adʵ��ֵ��

}ADC_info;




/*

typedef enum
{
 // Ring, //Բ��
  Straight,   //ֱ��
 // Curve,     //���
  Ramp,    //ʮ��
  //Cross,     //�µ�
}TRACK_TYPE;
*/
typedef enum
{
  Normal,
  Loseline,
  OUT,
}CAR_STATE;

typedef enum
{
  left_lock,
  right_lock,
  freedom,
}SERVO_STATE;





//���������
typedef  struct
{
  float kp_1;
  float kp_2;
  float kd;
  float ki;
  float servo_nI;
  int16 pos;  //λ����������
 // int16  output;
  uint16 pulse_middle;   //�����ֵ
  uint16 pulse_left;    //�����ֵ
  uint16 pulse_right;    //�����ֵ
  int16 pulse_output;  //������ֵ
  int8 flag_right_left , flag_old ; //����1��ת��־λ,����3��ת��־λ������2�м�ת��
  int8 flag_cuandao ;  //�ܵ���־

}Servo_pid_info;  //���������Ʋ���




typedef struct
{ 
  
  uint32 pluse_average[1][10];
  
  float Integral_MAX;
  float Integral_MIN;
  float kp;
  float ki;
  
  int32 count;
  int32 output;
  
  int32 set_speed;
  
  int speed_error;
  
  float spe_nP;   //��������
  float spe_nI;  //���ֿ���

}Motor_pid_data;


typedef struct
{
  int32 Stop_speed;   //ɲ��
  int32 L_Low_speed;  //�͵���
  int32 Low_speed;    //���٣����ߵ�ʱ����
  int32 M_Low_speed;  //�е���
  int32 Middle_speed; //���٣������ʱ����
  int32 M_High_speed; //�и���
  int32 High_speed;  //���٣�ֱ����ʱ����
}SPEED_STATE;



extern Servo_pid_info   servo;
extern Motor_pid_data     motor;
extern ADC_info     Senser_ADC;
extern SPEED_STATE   speed;

#endif