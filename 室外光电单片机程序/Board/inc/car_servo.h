#ifndef  __CAR_SERVO_H__
#define  __CAR_SERVO_H__

#define turn_km   (0.025)        //��ͱȵķ�ĸ���ϵ��,Խ�����Ƶ�Խ����025
 


#include "common.h"
#include "include.h"
#include  "car_struct.h"            //���п����õ��Ľṹ�������
#include "car_init_all.h"

int32 square_mid = 0,SUM_dip = 0 ;
int32 chuizhi_Mid[5] = {0},level_Mid[5] = {0},dip_Left[5] = {0},dip_Right[5] = {0},left_chuizhi[5] = {0},right_chuizhi[5] = {0};  //����4��������鷽�㿴
int32  servo_error[10] = {0};
int32 servo_error_rate = 0,servo_error_rate1 = 0;
int32 SUM_LRL;  //����ˮƽ��к�
int32 Left_rate;
int32 Right_rate;//���ҵ�б仯��
int32 CHA_LR=0;
int32 cha_lr=0;
int32 level_minus=0;
int32 chuizhi_rate=0;
int32 chuizhi_minus=0;


//void Cross_deal();     //ʮ�ִ���
//void Ring_deal();     //Բ������
//void Curve_deal();    //�������
//int Ramp_distinguish();//�µ�ʶ��
//int Cross_distinguish();//ʮ��ʶ��
//int  Ring_distinguish();//Բ��ʶ��
//int Curve_distinguish();//���ʶ��
//int Straight_distinguish();//ֱ��ʶ��

void Straight_deal();  //ֱ������
void RING();
void Cross_deal();


void lose_line();
void search_line();

void Servo_identify(ADC_info  *Senser_ADC);
void servo_control(Servo_pid_info *servo);
void manjiasu();

extern SERVO_STATE servo_state ;  //���״̬����
extern CAR_STATE   car_state ;   //����С����״̬



#endif