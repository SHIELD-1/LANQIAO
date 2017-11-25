#include "reg52.h"

#define LED       P2                //定义LED接口
#define LED_ON()  LED = 0x00;        //所有LED亮
#define LED_OFF() LED = 0xff;		//所有LED灭

#define LED_PWM_LIMIT_MAX 99
#define LED_PWM_LIMIT_MIN 0

static unsigned char TimerCounter  = 0;   //中断计数
static unsigned char LedDirection = 0;    //LED方向控制 0：渐亮  1：渐灭
static signed char LedPwmCounter  = 0;     //LED占空比
void Timer0_Init()//200微秒@11.0592MHz
{
	TMOD &= 0xf0;		//设置定时器模式
	TMOD |= 0x01;		//设置定时器模式
	TL0 = 0x47;		//设置定时初值
	TH0 = 0xff;		//设置定时初值
	TR0 = 1;		//定时器0开始计时
	ET0  = 1;
}
void Timer0() interrupt 1
{
	static signed char PwmCounter = 0;
	TL0 = 0x47;		//设置定时初值
	TH0 = 0xff;		//设置定时初值
	if(++TimerCounter >= 100)   //每20MS调整一下LED的占空比
	{
		TimerCounter = 0;
		if((LedPwmCounter <= LED_PWM_LIMIT_MAX) && (0 == LedDirection))
		{
			LedPwmCounter++;
			if(LedPwmCounter> LED_PWM_LIMIT_MAX)
			{
				LedDirection = 1;
				LedPwmCounter = LED_PWM_LIMIT_MAX;
			}
		}
		
		if((LedPwmCounter >= LED_PWM_LIMIT_MIN) && (1 == LedDirection))
		{
			LedPwmCounter--;
			if(LedPwmCounter < LED_PWM_LIMIT_MIN)
			{
				LedDirection = 0;
				LedPwmCounter = LED_PWM_LIMIT_MIN;
			}
		}
		PwmCounter = LedPwmCounter; //获取LED的占空比
	}
	
	if(PwmCounter > 0) //占空比大于0,则点亮LED,否则熄灭LED
	{
		LED_ON();
		PwmCounter--;
	}
	else
	{
		LED_OFF();
	}	
}
