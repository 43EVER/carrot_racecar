#ifndef __INITIALL_H__
#define __INITIALL_H__

#include "common.h"
#include "include.h"



#define CAR_A
#define sensor_num   (6)                 //�����еĸ���


#define ADC_chuizhi_mid     (ADC0_SE0)     //�м䴹ֱ���A0
#define ADC_dip_left        (ADC0_SE1)     //���б���A1
#define ADC_dip_right       (ADC0_SE2)     //�ұ�б���A6
#define ADC_level_mid       (ADC0_SE4 )      //�м�ˮƽ���B0
#define ADC_left_chuizhi    (ADC0_SE8)        //��ֱ
#define ADC_right_chuizhi   (ADC0_SE9)        //�Ҵ�ֱ

extern  void init_all(void);


#endif