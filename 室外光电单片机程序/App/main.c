 /*!
 *     COPYRIGHT NOTICE
 *     Copyright (c) 2017,ɽ��Ƽ�
 *     All rights reserved.
 *a     �������ۣ�ɽ����̳ http://www.vcan123.com
 *
 *     ��ע�������⣬�����������ݰ�Ȩ����ɽ��Ƽ����У�δ����������������ҵ��;��
 *     �޸�����ʱ���뱣��ɽ��Ƽ��İ�Ȩ������
 *
 * @file       main.c
 * @brief      ɽ��KEA ƽ̨������
 * @author     ɽ��Ƽ�
 * @version    v6.0
 * @date       2017-12-10
 */

#include "common.h"
#include "include.h"
#include "car_init_all.h"
#include "car_sensor.h"

uint16 str0[6];
extern int32 chuizhi_Mid[5],level_Mid[5],dip_Right[5],dip_Left[5],left_chuizhi[5],left_chuizhi[5],right_chuizhi[5];
extern int stop_flag;
extern int16 pulse_output;  //������ֵ
int count = 0;
void main()
{
    init_all();  //��ʼ�����к���
    
    while(1)
    {
      for(int i = 440 ; i < 1050;i++)
      {
      ftm_pwm_duty(FTM0,FTM_CH0,i);
      DELAY_MS(10);
      }
            for(int i = 1050 ; i >440;i--)
      {
      ftm_pwm_duty(FTM0,FTM_CH0,i);
      DELAY_MS(10);
      }
    }
}

