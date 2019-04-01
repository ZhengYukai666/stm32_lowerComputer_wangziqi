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
 ALIENTEK 战舰STM32F103开发板实验17
 ADC 实验 
 技术支持：www.openedv.com
 淘宝店铺：http://eboard.taobao.com 
 关注微信公众平台微信号："正点原子"，免费获取STM32资料。
 广州市星翼电子科技有限公司  
 作者：正点原子 @ALIENTEK
************************************************/


#define P 0.5
#define D 0.2
int volt, adcx;
extern int iicData[5];
int thumbVolt;
u8 PID_control(int data, int adcx);
 int main(void)
 {	 

	delay_init();	    	 //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	uart_init(115200);	 	//串口初始化为115200
 	//LED_Init();			     //LED端口初始化
 	//Adc_Init();		  		//ADC初始化
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
