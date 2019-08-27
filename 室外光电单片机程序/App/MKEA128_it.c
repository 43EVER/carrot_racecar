/*!
 *     COPYRIGHT NOTICE
 *     Copyright (c) 2017,ɽ��Ƽ�
 *     All rights reserved.
 *     �������ۣ�ɽ����̳ http://www.vcan123.com
 *
 *     ��ע�������⣬�����������ݰ�Ȩ����ɽ��Ƽ����У�δ����������������ҵ��;��
 *     �޸�����ʱ���뱣��ɽ��Ƽ��İ�Ȩ������
 *
 * @file       KEA128_it.c
 * @brief      ɽ��KEA ƽ̨������
 * @author     ɽ��Ƽ�
 * @version    v6.0
 * @date       2017-12-10
 */

 
#include "common.h"
#include "include.h"
#include  "MKEA128_it.h"
#include "car_time_sign.h"
#include "car_sensor.h"
#include "car_motor.h"
#include "mydata.h"
/*
#define  pluse_ratio  (0.128083438)//0.001090803       0.007839294
*/
const double pluse_ratio = 0.128083438; 

//�Ա�������ֵ���л�����Ȩ�˲�
double filter_encoder(double now_speed);   
//�ٶȻ�pi
int pid_speed(double set_speed,double now_speed);


int adrc_tmp = 0.0;
int watch_dog = 50; //0.5s û�����ݾ�ֹͣ���
int tmp = 0;
double actual_speed = 0.0,actual_speed_last=0.0,set_speed = 0.0;
int out_pwm = 4500;
int turn = 745;

RINGBUF madata;
char round_data[100];
void turn_deal(void);
/*************************�жϷ����������еĿ��ƶ������ж���ִ�У�******************************/
void pit0_irq(void)
{
  PIT_Flag_Clear(PIT0); 
  produce_time_sign();  //����ʱ���־
  
     if( ms_10flag)
     {
      gpio_turn(PTB1);
        ms_10flag=0;      
        average_wave_filtering(&motor);  //����ɼ�
        if(gpio_get(PTF5))
           motor.count = -motor.count;     
        
        //����������������Ϣת��Ϊ�ٶ���Ϣ,�����л����˲�         
        actual_speed = filter_encoder(motor.count * pluse_ratio);
        actual_speed = 0.23*actual_speed + 0.77*actual_speed_last;
        actual_speed_last = actual_speed;
        
        motor.count = actual_speed / pluse_ratio;
        uart_putchar(UART0,(char)(motor.count/127));
        uart_putchar(UART0,(char)(motor.count%127)); 
        
        out_pwm = pid_speed(set_speed,actual_speed);
        out_pwm += 4550;
  
        if(watch_dog > 0){
        watch_dog --;
        }else{
          if(watch_dog <= 0){
            out_pwm = 4500;
            turn = 745;
            uart_init(UART0,115200);
            uart_rx_irq_en(UART0);
          }
        }
       // watch_dog = 50;
        turn_deal();
        ftm_pwm_duty(FTM1,FTM_CH0,out_pwm);  
        
     }
}

float DOB_(float speed,int U)
{
  static float speed_last = 0.0;
  static float  Deq_0=0.0,Deq_1=0.0,Deq_2=0.0;
  Deq_0 = 1.06*Deq_1 - 0.0625*Deq_2 + 503*speed - 487.2*speed_last;
  Deq_0 -= 0.13*U + 0.87*Deq_1;
  Deq_2 = Deq_1; Deq_1 = Deq_0;
  return Deq_0;
}
char data[5]={0};
void turn_deal(void)
{

  if(madata.fill_cnt >= 5)//���ж϶����Ƿ�Ϊ��
  {
      RINGBUF_Get(&madata,data,5);
      set_speed = data[0]*127+data[1];
      turn = data[2]*127+data[3];
      if(data[4] == 0x00)
        set_speed = -set_speed;

      set_speed = (set_speed)/1000.0;
          
      if(set_speed >= 6.0) //���趨�ٶ�Ҳ�������ƣ�������6m/s
        set_speed = 6.0;
      else if(set_speed <= -6.0)
        set_speed = -6.0;
          
        
      if(turn <= 440)
        turn = 440;
      else if (turn >= 1050)
        turn = 1050;
 
  }
   ftm_pwm_duty(FTM0,FTM_CH0,turn);//ֱ�ӽ����ڷ��ķ��򸶸���� turn ( 440- 745 - 1050)
}  
char data1[5] = {0};
void uart0_irq(void)
{
  char ch = 0xff;
  static int index = 0,canread = 0;

  watch_dog = 50;
  uart_getchar(UART0,&ch);
  
  if (canread) 
  {
   // RINGBUF_Put(&madata,ch);
   // index++;
    data1[index++] = ch;
    
    if (index == 5) 
    {
      canread = 0;
      for(int i = 0;i < 5 ; i++)
      {
          
          RINGBUF_Put(&madata,data1[i]);
      
      }
      
//    set_speed = data[0]*127+data[1];
//     turn = data[2]*127+data[3];
 //     if(data[4] == 0x00)
 //       set_speed = -set_speed;
      
      index = 0;
      
 //     set_speed = (set_speed)/1000.0;
      
   //   if(set_speed >= 6.0) //���趨�ٶ�Ҳ�������ƣ�������6m/s
  //       set_speed = 6.0;
  //    else if(set_speed <= -6.0)
  //       set_speed = -6.0;
      
 //     
  //    if(turn <= 440)
 //        turn = 440;
  //    else if (turn >= 1050)
  //       turn = 1050;
  //     ftm_pwm_duty(FTM0,FTM_CH0,turn);//ֱ�ӽ����ڷ��ķ��򸶸���� turn ( 440- 745 - 1050)
   
    }
  }
 
  if (ch == 0x80) {
      canread = 1;
      index = 0;
  }
  
}

double myfabs(double tmp)
{
  return (tmp>0.0)?tmp:(0-tmp);
}

//�ٶȻ��� λ��ʽpi
//����ֵ�� PWM�ź�
//double kp_max = 300; //400
double kd = 0;
double ki = 0.03;//0.03
double kp = 0.95;//0.95

//double kd_max = 3000;
//double kd = 1000;
int pid_speed(double set_speed,double now_speed)
{ 
  int out_pwm;
  static double U_o=0.0,U_o_last=0.0;
  static int start_motor_cnt = 0;
  static double set_speed_last;
  static double error ;
  static double error_last = 0;
  static double error_sum = 0;
  static double diffrence=0.0,diffrence_last=0.0;
  static double Up = 0.0,Ui = 0.0;
  
  //�����һ��
  set_speed = (set_speed)/(5.0 - 0.0);
  now_speed = (now_speed)/(5.0 - 0.0);
  
  set_speed = 0.1*set_speed + 0.9*set_speed_last;
  error = set_speed - now_speed;
  
  
  set_speed_last = set_speed;
  
  
   //ƫ��С���趨ֵ��1/2ʱ��ſ�ʼ���� 
  //if(myfabs(error_sum) < 0.6 )//&& myfabs(error) < myfabs(set_speed)*0.8)
        //* (2/(1+fabs(error)));
  Up = error * kp;
  Ui = Ui + Up*ki;
  
  /*diffrence = error - error_last;
  diffrence = 0.6*diffrence + 0.4*diffrence_last;
  diffrence_last = diffrence;
  error_last = error;*/
  
  
  if(Ui >= 0.35)
    Ui = 0.35;
  else if(Ui <= -0.35)
    Ui = -0.35;
  
  //kd = kd*0.1;
  
 
 
  
  U_o = (double)(Up + Ui);
  
        
  //U_o += kd*diffrence;
  
  
  
  
  /*
  if(U_o >= 1.0)
    U_o = 1.0;
  else if(U_o <= -1.0)
    U_o = -1.0;
  else 
    U_o = U_o;
  */
  
  U_o = 0.8*U_o + 0.2*U_o_last;
  U_o_last = U_o;
  
  out_pwm = U_o*700;
  
  //out_pwm += set_speed * 20; //ǰ��
  
  if(out_pwm >= 700)
     out_pwm = 700;
  else if(out_pwm <= -700)
     out_pwm = -700;
  else
     out_pwm = out_pwm;
  return out_pwm;     
} 


//�Ա��������ٵ��źŽ��л�����Ȩ�˲�
double filter_encoder(double now_speed)
{
    static double  encoder_speed[10];
    static int flag_start = 1;
    double ret_speed=0.0;
    int i=0;
    
    if(flag_start){
        flag_start = 0;
        for(int i=0; i<10; i++)
            encoder_speed[i] = now_speed;
    }
    
    for( i=0; i<10-1; i++)
        encoder_speed[i] = encoder_speed[i+1];

    encoder_speed[10-1] = now_speed;
    
    ret_speed = encoder_speed[9]*0.2 + encoder_speed[8]*0.2 + encoder_speed[7]*0.1 
                + encoder_speed[6]*0.1 + encoder_speed[5]*0.1 + encoder_speed[4]*0.1 
                + encoder_speed[3]*0.05 + encoder_speed[2]*0.05 + encoder_speed[1]*0.05 
                + encoder_speed[0]*0.05 ;
    
    return ret_speed;
}