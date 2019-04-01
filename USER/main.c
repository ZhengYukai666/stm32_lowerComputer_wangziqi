#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "lcd.h"
#include "usart.h"	 
#include "adc.h"
#include "myiic.h"
 #include "dac.h"
/************************************************
 ALIENTEK ս��STM32F103������ʵ��17
 ADC ʵ�� 
 ����֧�֣�www.openedv.com
 �Ա����̣�http://eboard.taobao.com 
 ��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡSTM32���ϡ�
 ������������ӿƼ����޹�˾  
 ���ߣ�����ԭ�� @ALIENTEK
************************************************/


#define P 0.5
#define D 0.2
int volt, adcx;
extern int iicData[5];
int thumbVolt;
u8 PID_control(int data, int adcx);
 int main(void)
 {	 

	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 	//���ڳ�ʼ��Ϊ115200
 	//LED_Init();			     //LED�˿ڳ�ʼ��
 	//Adc_Init();		  		//ADC��ʼ��
	//Dac1_Init();				//DAC???
	printf("********************NOTE*********************\r\n");
	printf("Send any float number from 0 to 3.3, like 1.0");
   
	 IIC_Init();
  IIC_Start();
		IIC_Send_Byte(0x90,0x90,0x90);
	if(IIC_Wait_Ack()) printf("error1");
	 IIC_Send_Byte(0x40,0x40,0x40);
	if(IIC_Wait_Ack()) printf("error2");
	 
	
	while(1)
	{
		/*adcx=Get_Adc_Average(ADC_Channel_1,10);
		volt = PID_control(data,adcx);
		printf("adcx = %d",adcx);
		printf("volt = %d",volt);*/
//		thumbVolt = iicData[1]*16;
//		DAC_SetChannel1Data(DAC_Align_12b_R, thumbVolt);//thumbVolt
		
		
		IIC_Send_Byte(iicData[0],iicData[1],iicData[2]);
	if(IIC_Wait_Ack()) printf("error3");
		//printf("success \r\n");
		//delay_ms(100);
 }
}
 







u8 PID_control(int data, int adcx){
	int ret;
	static float deltaLast,delta;
	deltaLast = delta;
	delta = (float)data/1000 - (float)adcx/4096*3.3;
	ret = (u8)(volt+((delta)*P+(deltaLast-delta)*D)/3.3*256);
	return ret;
}
