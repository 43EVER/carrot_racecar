#include "car_init_all.h"
#include "mydata.h"

extern char round_data[100];
extern RINGBUF madata;
void init_all(void)
{
    /********************************ADC ��� ��� LED  TCLK2��ʼ��*************************************/
   /*  adc_init (ADC_chuizhi_mid );       //�м䴹ֱ���A0
     adc_init (ADC_dip_left );        //���б��� A1
     adc_init (ADC_dip_right );      //�ұ�б���  A6
     adc_init (ADC_level_mid );     //�м�ˮƽ���  B0
     adc_init (ADC_left_chuizhi);    //C0 
     adc_init (ADC_right_chuizhi);   //C1
     
     motor_init();
      
    ftm_pwm_init(FTM1,FTM_CH1,50,765);//���  PTC5  
    ftm_pwm_duty(FTM1,FTM_CH1,765);

     ftm_pwm_init(FTM0,FTM_CH0,8000,10000);//���   PTB2       B3 �� ��ת  B2�� ��ת

    ftm_pwm_init(FTM0,FTM_CH1,8000,10000);//���   PTB3
   */
    while( !RINGBUF_Init(&madata,round_data,100));
    ftm_pwm_init(FTM0,FTM_CH0,50,1050); //���745
    ftm_pwm_init(FTM1,FTM_CH0,300,4600); //���
    
    
    ftm_pulse_init(FTM2, FTM_PS_1, TCLK2);   //FTM2���������������Ƶ����������Ϊ TCLK2  E7
    gpio_init(PTE1, GPI, 0);
    gpio_init(PTB1, GPO, 0);
    gpio_init(PTC4, GPI, 0);
    gpio_init(PTC5, GPI, 0); 
    
    gpio_init(PTF5, GPI, 0);
    
 //   uart_init(UART0,115200);
 //   uart_rx_irq_en(UART0);
    
   /* led_init (LED0);    //��ʼ�� LED0
    led_init (LED1);    //��ʼ�� LED1
    led_init (LED2);    //��ʼ�� LED2
    led_init (LED3);    //��ʼ�� LED3

    led (LED0,LED_OFF);    //Ϩ�� LED0
    led (LED1,LED_OFF);    //Ϩ�� LED1
    led (LED2,LED_OFF);    //Ϩ�� LED2
    led (LED3,LED_OFF);    //Ϩ�� LED3

    gpio_init(PTF3, GPO, 0);
*/
     
    /******************************�ж�***********/
  //  pit_init_ms(PIT0, 1);                                //  ��ʱ 1ms
  //  enable_irq(PIT_CH0_IRQn);                             // ʹ��PIT_CH0�ж�
  //  EnableInterrupts;   //�����жϣ������õ��жϵģ�����Ҫ�ģ�

}


