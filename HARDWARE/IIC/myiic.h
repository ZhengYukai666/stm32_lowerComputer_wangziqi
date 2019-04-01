#ifndef __MYIIC_H
#define __MYIIC_H
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������
//IIC���� ����	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/9
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////

//IO��������
 
#define SDA_IN()  {GPIOB->CRL&=0X0F000000;GPIOB->CRL|=(u32)8<<28;GPIOB->CRL|=(u32)8<<20;GPIOB->CRL|=(u32)8<<16;GPIOB->CRL|=(u32)8<<12;GPIOB->CRL|=(u32)8<<8;GPIOB->CRL|=(u32)8<<4;GPIOB->CRL|=(u32)8;}//gpiob4,5,6,7
#define SDA_OUT() {GPIOB->CRL&=0X0F000000;GPIOB->CRL|=(u32)3<<28;GPIOB->CRL|=(u32)3<<20;GPIOB->CRL|=(u32)3<<16;GPIOB->CRL|=(u32)3<<12;GPIOB->CRL|=(u32)3<<8;GPIOB->CRL|=(u32)3<<4;GPIOB->CRL|=(u32)3;}

//IO��������	 
#define IIC_SCL    PBout(6) //SCL
#define IIC_SDA    PBout(7) //SDA	 
#define READ_SDA   PBin(7)  //����SDA 

#define IIC_SDA2    PBout(5) //SDA	 
#define READ_SDA2   PBin(5)  //����SDA 
#define IIC_SDA3    PBout(1) //SDA	 
#define READ_SDA3   PBin(1)  //����SDA 
#define IIC_SDA4    PBout(0) //SDA	 
#define READ_SDA4   PBin(0)  //����SDA 
#define IIC_SDA5    PBout(2) //SDA	 
#define READ_SDA5   PBin(2)  //����SDA 
	
//IIC���в�������
void IIC_Init(void);                //��ʼ��IIC��IO��				 
void IIC_Start(void);				//����IIC��ʼ�ź�
void IIC_Stop(void);	  			//����IICֹͣ�ź�
void IIC_Send_Byte(u8 txd,u8 txd2,u8 txd3);			//IIC����һ���ֽ�
u8 IIC_Read_Byte(unsigned char ack);//IIC��ȡһ���ֽ�
u8 IIC_Wait_Ack(void); 				//IIC�ȴ�ACK�ź�
void IIC_Ack(void);					//IIC����ACK�ź�
void IIC_NAck(void);				//IIC������ACK�ź�

void IIC_Write_One_Byte(u8 daddr,u8 addr,u8 data);
u8 IIC_Read_One_Byte(u8 daddr,u8 addr);	  
#endif
















