#include "timer.h"
#include "led.h"
#include "usart.h"
//////////////////////////////////////////////////////////////////////////////////	 
//±¾³ÌĞòÖ»¹©Ñ§Ï°Ê¹ÓÃ£¬Î´¾­×÷ÕßĞí¿É£¬²»µÃÓÃÓÚÆäËüÈÎºÎÓÃÍ¾
//ALIENTEKÕ½½¢STM32¿ª·¢°å
//¶¨Ê±Æ÷ Çı¶¯´úÂë	   
//ÕıµãÔ­×Ó@ALIENTEK
//¼¼ÊõÂÛÌ³:www.openedv.com
//ĞŞ¸ÄÈÕÆÚ:2012/9/4
//°æ±¾£ºV1.1
//°æÈ¨ËùÓĞ£¬µÁ°æ±Ø¾¿¡£
//Copyright(C) ¹ãÖİÊĞĞÇÒíµç×Ó¿Æ¼¼ÓĞÏŞ¹«Ë¾ 2009-2019
//All rights reserved									  
//********************************************************************************
//V1.1 20120904
//1,Ôö¼ÓTIM3_PWM_Initº¯Êı¡£
//2,Ôö¼ÓLED0_PWM_VALºê¶¨Òå£¬¿ØÖÆTIM3_CH2Âö¿í									  
//////////////////////////////////////////////////////////////////////////////////  
   	  
//Í¨ÓÃ¶¨Ê±Æ÷3ÖĞ¶Ï³õÊ¼»¯
//ÕâÀïÊ±ÖÓÑ¡ÔñÎªAPB1µÄ2±¶£¬¶øAPB1Îª36M
//arr£º×Ô¶¯ÖØ×°Öµ¡£
//psc£ºÊ±ÖÓÔ¤·ÖÆµÊı
//ÕâÀïÊ¹ÓÃµÄÊÇ¶¨Ê±Æ÷3!


void TIM3_Int_Init(u16 arr,u16 psc)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //Ê±ÖÓÊ¹ÄÜ

	TIM_TimeBaseStructure.TIM_Period = arr; //ÉèÖÃÔÚÏÂÒ»¸ö¸üĞÂÊÂ¼ş×°Èë»î¶¯µÄ×Ô¶¯ÖØ×°ÔØ¼Ä´æÆ÷ÖÜÆÚµÄÖµ	 ¼ÆÊıµ½5000Îª500ms
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //ÉèÖÃÓÃÀ´×÷ÎªTIMxÊ±ÖÓÆµÂÊ³ıÊıµÄÔ¤·ÖÆµÖµ  10KhzµÄ¼ÆÊıÆµÂÊ  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //ÉèÖÃÊ±ÖÓ·Ö¸î:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIMÏòÉÏ¼ÆÊıÄ£Ê½
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //¸ù¾İTIM_TimeBaseInitStructÖĞÖ¸¶¨µÄ²ÎÊı³õÊ¼»¯TIMxµÄÊ±¼ä»ùÊıµ¥Î»
 
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE ); //Ê¹ÄÜÖ¸¶¨µÄTIM3ÖĞ¶Ï,ÔÊĞí¸üĞÂÖĞ¶Ï

	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3ÖĞ¶Ï
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //ÏÈÕ¼ÓÅÏÈ¼¶0¼¶
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //´ÓÓÅÏÈ¼¶3¼¶
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQÍ¨µÀ±»Ê¹ÄÜ
	NVIC_Init(&NVIC_InitStructure);  //¸ù¾İNVIC_InitStructÖĞÖ¸¶¨µÄ²ÎÊı³õÊ¼»¯ÍâÉèNVIC¼Ä´æÆ÷

	TIM_Cmd(TIM3, ENABLE);  //Ê¹ÄÜTIMxÍâÉè
							 
}
//¶¨Ê±Æ÷3ÖĞ¶Ï·şÎñ³ÌĞò
//extern u16 force1,force2,force3,force4,force5;
void TIM3_IRQHandler(void)   //TIM3ÖĞ¶Ï
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) //¼ì²éÖ¸¶¨µÄTIMÖĞ¶Ï·¢ÉúÓë·ñ:TIM ÖĞ¶ÏÔ´ 
		{
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //Çå³ıTIMxµÄÖĞ¶Ï´ı´¦ÀíÎ»:TIM ÖĞ¶ÏÔ´ 
		
			/*if(force1>=1000)GPIO_SetBits(GPIOE,GPIO_Pin_0);
			if(force1<=1000)GPIO_ResetBits(GPIOE,GPIO_Pin_0);
			
			if(force2>=1000)GPIO_SetBits(GPIOE,GPIO_Pin_1);
			if(force2<=1000)GPIO_ResetBits(GPIOE,GPIO_Pin_1);
			
			if(force3>=1000)GPIO_SetBits(GPIOE,GPIO_Pin_2);
			if(force3<=1000)GPIO_ResetBits(GPIOE,GPIO_Pin_2);
			
			if(force4>=1000)GPIO_SetBits(GPIOE,GPIO_Pin_3);
			if(force4<=1000)GPIO_ResetBits(GPIOE,GPIO_Pin_3);
			
			if(force5>=1000)GPIO_SetBits(GPIOE,GPIO_Pin_4);
			if(force5<=1000)GPIO_ResetBits(GPIOE,GPIO_Pin_4);*/
			
			
		
			
			
			LED1=!LED1;
		}
}




//TIM3 PWM²¿·Ö³õÊ¼»¯ 
//PWMÊä³ö³õÊ¼»¯
//arr£º×Ô¶¯ÖØ×°Öµ
//psc£ºÊ±ÖÓÔ¤·ÖÆµÊı
void TIM3_PWM_Init(u16 arr,u16 psc)
{  
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	//Ê¹ÄÜ¶¨Ê±Æ÷3Ê±ÖÓ
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //Ê¹ÄÜGPIOÍâÉèºÍAFIO¸´ÓÃ¹¦ÄÜÄ£¿éÊ±ÖÓ
	
	//GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE); //Timer3²¿·ÖÖØÓ³Éä  TIM3_CH2->PB5    
	//GPIO_PinRemapConfig(GPIO_FullRemap_TIM3, ENABLE); //Timer3È«Ó³Éää  TIM3_CH2->PB5    

   //ÉèÖÃ¸ÃÒı½ÅÎª¸´ÓÃÊä³ö¹¦ÄÜ,Êä³öTIM3 CH2µÄPWMÂö³å²¨ĞÎ	GPIOB.5
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6; //TIM_CH2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //¸´ÓÃÍÆÍìÊä³ö
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);//³õÊ¼»¯GPIO
	
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7; //TIM_CH2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //¸´ÓÃÍÆÍìÊä³ö
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);//³õÊ¼»¯GPIO
	
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; //TIM_CH2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //¸´ÓÃÍÆÍìÊä³ö
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);//³õÊ¼»¯GPIO
	
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1; //TIM_CH2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //¸´ÓÃÍÆÍìÊä³ö
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);//³õÊ¼»¯GPIO
 
   //³õÊ¼»¯TIM3
	TIM_TimeBaseStructure.TIM_Period = arr; //ÉèÖÃÔÚÏÂÒ»¸ö¸üĞÂÊÂ¼ş×°Èë»î¶¯µÄ×Ô¶¯ÖØ×°ÔØ¼Ä´æÆ÷ÖÜÆÚµÄÖµ
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //ÉèÖÃÓÃÀ´×÷ÎªTIMxÊ±ÖÓÆµÂÊ³ıÊıµÄÔ¤·ÖÆµÖµ 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //ÉèÖÃÊ±ÖÓ·Ö¸î:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIMÏòÉÏ¼ÆÊıÄ£Ê½
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //¸ù¾İTIM_TimeBaseInitStructÖĞÖ¸¶¨µÄ²ÎÊı³õÊ¼»¯TIMxµÄÊ±¼ä»ùÊıµ¥Î»
	
	//³õÊ¼»¯TIM3 Channel2 PWMÄ£Ê½	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //Ñ¡Ôñ¶¨Ê±Æ÷Ä£Ê½:TIMÂö³å¿í¶Èµ÷ÖÆÄ£Ê½2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //±È½ÏÊä³öÊ¹ÄÜ
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //Êä³ö¼«ĞÔ:TIMÊä³ö±È½Ï¼«ĞÔ¸ß
	TIM_OC1Init(TIM3, &TIM_OCInitStructure);  //¸ù¾İTÖ¸¶¨µÄ²ÎÊı³õÊ¼»¯ÍâÉèTIM3 OC2
	TIM_OC2Init(TIM3, &TIM_OCInitStructure);  //¸ù¾İTÖ¸¶¨µÄ²ÎÊı³õÊ¼»¯ÍâÉèTIM3 OC2
	TIM_OC3Init(TIM3, &TIM_OCInitStructure);  //¸ù¾İTÖ¸¶¨µÄ²ÎÊı³õÊ¼»¯ÍâÉèTIM3 OC2
	TIM_OC4Init(TIM3, &TIM_OCInitStructure);  //¸ù¾İTÖ¸¶¨µÄ²ÎÊı³õÊ¼»¯ÍâÉèTIM3 OC2

	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);  //Ê¹ÄÜTIM3ÔÚCCR2ÉÏµÄÔ¤×°ÔØ¼Ä´æÆ÷
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);  //Ê¹ÄÜTIM3ÔÚCCR2ÉÏµÄÔ¤×°ÔØ¼Ä´æÆ÷
	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);  //Ê¹ÄÜTIM3ÔÚCCR2ÉÏµÄÔ¤×°ÔØ¼Ä´æÆ÷
	TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);  //Ê¹ÄÜTIM3ÔÚCCR2ÉÏµÄÔ¤×°ÔØ¼Ä´æÆ÷

	TIM_Cmd(TIM3, ENABLE);  //Ê¹ÄÜTIM3
	

}

void TIM2_PWM_Init(u16 arr,u16 psc)
{  
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);	//Ê¹ÄÜ¶¨Ê±Æ÷3Ê±ÖÓ
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB   | RCC_APB2Periph_AFIO, ENABLE);  //Ê¹ÄÜGPIOÍâÉèºÍAFIO¸´ÓÃ¹¦ÄÜÄ£¿éÊ±ÖÓ
	

	GPIO_PinRemapConfig(GPIO_PartialRemap2_TIM2, ENABLE); //Timer3²¿·ÖÖØÓ³Éä  TIM3_CH2->PB5    
	//GPIO_PinRemapConfig(GPIO_FullRemap_TIM2, ENABLE); //Timer3²¿·ÖÖØÓ³Éä  TIM3_CH2->PB5    

   //ÉèÖÃ¸ÃÒı½ÅÎª¸´ÓÃÊä³ö¹¦ÄÜ,Êä³öTIM3 CH2µÄPWMÂö³å²¨ĞÎ	GPIOB.5
	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; //TIM_CH2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //¸´ÓÃÍÆÍìÊä³ö
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);//³õÊ¼»¯GPIO
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //TIM_CH2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //¸´ÓÃÍÆÍìÊä³ö
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);//³õÊ¼»¯GPIO
		
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11; //TIM_CH2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //¸´ÓÃÍÆÍìÊä³ö
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);//³õÊ¼»¯GPIO
 
   //³õÊ¼»¯TIM2
	TIM_TimeBaseStructure.TIM_Period = arr; //ÉèÖÃÔÚÏÂÒ»¸ö¸üĞÂÊÂ¼ş×°Èë»î¶¯µÄ×Ô¶¯ÖØ×°ÔØ¼Ä´æÆ÷ÖÜÆÚµÄÖµ
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //ÉèÖÃÓÃÀ´×÷ÎªTIMxÊ±ÖÓÆµÂÊ³ıÊıµÄÔ¤·ÖÆµÖµ 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //ÉèÖÃÊ±ÖÓ·Ö¸î:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIMÏòÉÏ¼ÆÊıÄ£Ê½
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //¸ù¾İTIM_TimeBaseInitStructÖĞÖ¸¶¨µÄ²ÎÊı³õÊ¼»¯TIMxµÄÊ±¼ä»ùÊıµ¥Î»
	
	//³õÊ¼»¯TIM3 Channel2 PWMÄ£Ê½	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //Ñ¡Ôñ¶¨Ê±Æ÷Ä£Ê½:TIMÂö³å¿í¶Èµ÷ÖÆÄ£Ê½2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //±È½ÏÊä³öÊ¹ÄÜ
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //Êä³ö¼«ĞÔ:TIMÊä³ö±È½Ï¼«ĞÔ¸ß
	TIM_OC1Init(TIM2, &TIM_OCInitStructure);  //¸ù¾İTÖ¸¶¨µÄ²ÎÊı³õÊ¼»¯ÍâÉèTIM3 OC2
	TIM_OC2Init(TIM2, &TIM_OCInitStructure);  //¸ù¾İTÖ¸¶¨µÄ²ÎÊı³õÊ¼»¯ÍâÉèTIM3 OC2
	TIM_OC3Init(TIM2, &TIM_OCInitStructure);  //¸ù¾İTÖ¸¶¨µÄ²ÎÊı³õÊ¼»¯ÍâÉèTIM3 OC2
	TIM_OC4Init(TIM2, &TIM_OCInitStructure);  //¸ù¾İTÖ¸¶¨µÄ²ÎÊı³õÊ¼»¯ÍâÉèTIM3 OC2

	TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);  //Ê¹ÄÜTIM3ÔÚCCR2ÉÏµÄÔ¤×°ÔØ¼Ä´æÆ÷
	TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);  //Ê¹ÄÜTIM3ÔÚCCR2ÉÏµÄÔ¤×°ÔØ¼Ä´æÆ÷
	TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);  //Ê¹ÄÜTIM3ÔÚCCR2ÉÏµÄÔ¤×°ÔØ¼Ä´æÆ÷
	TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable);  //Ê¹ÄÜTIM3ÔÚCCR2ÉÏµÄÔ¤×°ÔØ¼Ä´æÆ÷

	TIM_Cmd(TIM2, ENABLE);  //Ê¹ÄÜTIM3
	

}


void TIM1_PWM_Init(u16 arr,u16 psc)
{		 					 
	
 	
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	

	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE); //Ê¹ÄÜTIMxÍâÉè
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE); //Ê¹ÄÜTIMxÍâÉè
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE   | RCC_APB2Periph_AFIO, ENABLE);  //Ê¹ÄÜGPIOAÍâÉèÊ±ÖÓÊ¹ÄÜ???²»È·¶¨Òª²»Òª×¢ÊÍ
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); 
 	GPIO_PinRemapConfig(GPIO_FullRemap_TIM1, ENABLE); //Timer3²¿·ÖÖØÓ³Éä  TIM3_CH2->PB5    

  //ÉèÖÃ¸ÃÒı½ÅÎª¸´ÓÃÊä³ö¹¦ÄÜ,Êä³öTIM1 CH1µÄPWMÂö³å²¨ĞÎ
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //TIM1_CH1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //¸´ÓÃ¹¦ÄÜÊä³ö
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOE, &GPIO_InitStructure); //³õÊ¼»¯GPIO
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11; //TIM1_CH1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //¸´ÓÃ¹¦ÄÜÊä³ö
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOE, &GPIO_InitStructure); //³õÊ¼»¯GPIO
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13; //TIM1_CH1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //¸´ÓÃ¹¦ÄÜÊä³ö
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOE, &GPIO_InitStructure); //³õÊ¼»¯GPIO
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14; //TIM1_CH1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //¸´ÓÃ¹¦ÄÜÊä³ö
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOE, &GPIO_InitStructure); //³õÊ¼»¯GPIO
 
	TIM_TimeBaseStructure.TIM_Period = arr; //ÉèÖÃ×Ô¶¯ÖØ×°ÔØÖÜÆÚÖµ
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //ÉèÖÃÔ¤·ÖÆµÖµ ²»·ÖÆµ
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //ÉèÖÃÊ±ÖÓ·Ö¸î:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIMÏòÉÏ¼ÆÊıÄ£Ê½
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); //¸ù¾İÖ¸¶¨µÄ²ÎÊı³õÊ¼»¯TIMx
	
	 
	 
	 
	 
	 
	 
	 
	 
	 
	 
	 
	 
	 
	 
	 
	 
	 
	 
	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //CH1 PWM2Ä£Ê½	
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //±È½ÏÊä³öÊ¹ÄÜ
	TIM_OCInitStructure.TIM_Pulse = 0; //ÉèÖÃ´ı×°Èë²¶»ñ±È½Ï¼Ä´æÆ÷µÄÂö³åÖµ
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //OC1 µÍµçÆ½ÓĞĞ§ 
	TIM_OC1Init(TIM1, &TIM_OCInitStructure);  //¸ù¾İÖ¸¶¨µÄ²ÎÊı³õÊ¼»¯ÍâÉèTIMx
	TIM_OC2Init(TIM1, &TIM_OCInitStructure);  //¸ù¾İÖ¸¶¨µÄ²ÎÊı³õÊ¼»¯ÍâÉèTIMx
	TIM_OC3Init(TIM1, &TIM_OCInitStructure);  //¸ù¾İÖ¸¶¨µÄ²ÎÊı³õÊ¼»¯ÍâÉèTIMx
	TIM_OC4Init(TIM1, &TIM_OCInitStructure);  //¸ù¾İÖ¸¶¨µÄ²ÎÊı³õÊ¼»¯ÍâÉèTIMx

	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);  //CH1 Ô¤×°ÔØÊ¹ÄÜ
	TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);  //CH1 Ô¤×°ÔØÊ¹ÄÜ
	TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable);  //CH1 Ô¤×°ÔØÊ¹ÄÜ
	TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);  //CH1 Ô¤×°ÔØÊ¹ÄÜ
	
	TIM_ARRPreloadConfig(TIM1, ENABLE); //Ê¹ÄÜTIMxÔÚARRÉÏµÄÔ¤×°ÔØ¼Ä´æÆ÷
	
	TIM_CtrlPWMOutputs(TIM1,ENABLE);	//MOE Ö÷Êä³öÊ¹ÄÜ,¸ß¼¶¶¨Ê±Æ÷±ØĞë¿ªÆôÕâ¸ö 
	
	TIM_Cmd(TIM1, ENABLE);  //Ê¹ÄÜTIMx
	   										  
} 
