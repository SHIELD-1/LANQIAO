//#ifndef _PWM_H_
//#define _PWM_H_

#include<intrins.h>

#ifndef uchar
#define uchar unsigned char
#endif

#ifndef uint
#define uint unsigned int
#endif

#define LED       P0               //����LED�ӿ�
#define LED_ON()  {LED = 0x00;}        //����LED��
#define LED_OFF() {LED = 0xff;}		//����LED��

#define PWM_LIMIT_MAX 99
#define PWM_LIMIT_MIN 0



static uchar TimerConter = 0; //��ʱ���жϴ���
static uchar PWMConter = 0;   //ռ�ձ�
static signed char PWMDirection = 0;         //ռ�ձȱ仯����


//void Delay100ms()		//@11.0592MHz
//{
//	unsigned char i, j, k;

//	_nop_();
//	_nop_();
//	i = 5;
//	j = 52;
//	k = 195;
//	do
//	{
//		do
//		{
//			while (--k);
//		} while (--j);
//	} while (--i);
//}


//void LED(uchar i)
//{
//	if(i)
//	{
//		P2 = (P2&0x1f)|0x80;
//		P0= 0x00;
//		P2 &= 0x1f;	
//	}
//	else
//	{
//		P2 = (P2&0x1f)|0x80;
//		P0 = 0xff;
//		P2 &= 0x1f;	
//	}
//}

void Timer0_Init()//200΢��@11.0592MHz
{
	TMOD &= 0xf0;		//���ö�ʱ��ģʽ
	TMOD |= 0x01;		//���ö�ʱ��ģʽ
	TL0 = 0x47;		//���ö�ʱ��ֵ
	TH0 = 0xff;		//���ö�ʱ��ֵ
	TR0 = 1;		//��ʱ��0��ʼ��ʱ
	ET0  = 1;
}



void Timer0(void) interrupt 1
{
	static  signed char PWMConter_NOW = 0;
	TL0 = 0x47;		//���ö�ʱ��ֵ
	TH0 = 0xff;		//���ö�ʱ��ֵ
//	LED(0);
//	Delay100ms();
//	LED(1);
  if(++TimerConter >= 100)
	{
		TimerConter = 0;
		if((PWMConter <= PWM_LIMIT_MAX) && (0 ==PWMDirection ))
		{
			PWMConter++;
			if(PWMConter > PWM_LIMIT_MAX)
			{
				PWMDirection = 1;
				PWMConter = PWM_LIMIT_MAX;
			}
		}
		if((PWMConter >= PWM_LIMIT_MIN) && (1 == PWMDirection))
		{
			PWMConter--;
			if(PWMConter < PWM_LIMIT_MIN)
			{
				PWMDirection = 0;
				PWMConter = PWM_LIMIT_MIN;
			}
		}
		PWMConter_NOW = PWMConter;
	}
  
  if(PWMConter_NOW > 0)
 	{
		LED_ON();
		PWMConter_NOW--;
	}
  else
	{
		LED_OFF();
	}		
}


