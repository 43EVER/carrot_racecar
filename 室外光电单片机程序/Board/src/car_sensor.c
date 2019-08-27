#include "car_sensor.h"
#include "car_init_all.h"

ADC_info  Senser_ADC;
extern Motor_pid_data     motor;
extern SPEED_STATE   speed;
Servo_pid_info servo;


/**************************ƽ���˲�***************
��4��ͨ������AD�Ĳɼ�������ƽ���˲�
д������ģʽ��ǰ�ڵ��Բ��ù�һ��Ϊnormal  �����ù�һ������  Normalization


****************/

void  ADC_aver_val(ADC_info  *Senser_ADC,debug_two_mode  state)
{
  
uint32 sum=0;  
uint16 i=0,j=0;
uint32 senser[sensor_num][20]={0};
  for(i=0;i<20;i++)      //һ��ͨ��ȡ20��ֵ
  {
  senser[0][i]=adc_once(ADC_chuizhi_mid,ADC_8bit);
  
  senser[1][i]=adc_once(ADC_dip_left, ADC_8bit); 
  senser[2][i]=adc_once(ADC_dip_right, ADC_8bit);
  senser[3][i]=adc_once(ADC_level_mid,ADC_8bit);
  senser[4][i]=adc_once(ADC_left_chuizhi,ADC_8bit);
  senser[5][i]=adc_once(ADC_right_chuizhi,ADC_8bit);
  }

  for(i=0;i<6;i++)             //��ÿһ����������ADֵ�Ӵ�С��������
  {
       bubble((uint32*)&senser[i],20);    //senser[i]�Ƕ�ά���鵥���������Ԫ��
  
  }
  
  for(i=0;i<sensor_num;i++)      //sensor_numΪ4��ͨ���ĸ���
  {  sum=0;
    
     for(j=1;j<19;j++)   //ȥ��1�����ֵ����Сֵ
     {
         sum+=senser[i][j];           
     }
     
     if(state==normal)                                  //normalΪһ���������ܳ�ģʽ,�ýṹ�嶨��
        
 Senser_ADC->ad_act_val[i][0] = sum / 18;    //��ƽ��ֵ��ֵ������ṹ��������
     
       
     
                                                //��1ms�ж������ƽ���˲����ֵ��ad_act_val[i][0]
   }
  
  
}




/***********�ж�1ms��ʱ��ִ�е�����*****************************************/

void time_flag_1ms(ADC_info  *Senser_ADC)

{
    
                  //�����˲�֮ǰ�Ȱѣ����������ƶ�����Senser_ADC.ad_act_val[i][0]�ڳ���
    for (uint8 i = 0; i < sensor_num; i++)
    {
      for (int8 j = 9; j >= 0; j--)
      {
         Senser_ADC->ad_act_val[i][j+1] = Senser_ADC->ad_act_val[i][j];
      }
    }
    //Ȼ�����,�˲�
    ADC_aver_val(Senser_ADC,normal);

}

/****************�ж�5msִ�е�����************************************/


void time_flag_5ms(ADC_info  *Senser_ADC,Servo_pid_info *servo)
{
/****    ��ƽ���˲����ֵ�ٽ���һ�λ����˲�            ***/
  for(uint8 i=0;i<sensor_num;i++)
  {
      Senser_ADC->ad_avr_val[i] = Senser_ADC->ad_act_val[i][0] * 0.5 \
                             + Senser_ADC->ad_act_val[i][1] * 0.2 \
                             + Senser_ADC->ad_act_val[i][2] * 0.1 \
                             + Senser_ADC->ad_act_val[i][3] * 0.1 \
                             + Senser_ADC->ad_act_val[i][4] * 0.1 ;
   
  }

 
  
  Servo_identify(Senser_ADC); //��ʶ��
  
 
  
  servo_control(servo);   //�����
  
}










/********************ð������******************

** ƽ���˲���ʱ��Ҫ�õ����Ӵ�С����

** uint32 str[10]; bubble(str, 10);

**************************/

void bubble(uint32 r[], uint32 n)
{    
  int i = n - 1;
  while(i > 0)  //��������£�ѭ�� N - 1��
  {
    int pos = 0;
    for (int j = 0; j < i; j++) //ѭ��i��
    {
      if (r[j] < r[j+1])
      {
        pos = j;   //��һ��ѭ����J�Ǵ� 0 �� i ��
        int tmp = r[j];
        r[j] = r[j+1];
        r[j+1] = tmp;
      } 
    }
    i = pos;  //����˵����ѭ�����Σ������POS˵�����
  }
}











