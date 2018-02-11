#include"STC15F2K60S2.h"
#include"allinit.h"
#include"keypad.h"
#include"smg.h"
#include"onewire.c"

#define uchar unsigned char
#define uint unsigned int

uchar PATTERN=1,TMAX = 30,TMIN = 20; //ģʽ���¶����ޣ��¶�����
bit star; //LED1������˸��־λ,
void main(void)
{
	uint Temperature;
	allinit();
	smg_Timer0init();
	while(1)
	{
		key_down();
		/*----------------------------�¶ȶ�ȡ-------------------------------------------------------------------------*/
		if(flag100ms ==1)
		{
			flag100ms = 0;
			Temperature = Temper_Read();
		}
		/*------------------------------�û�����--------------------------------------------------------------------*/
		if(SetFlag == 1)
		{
			if(TMAXTMIN == 0)
			{
				dspbuff[1] = 16;
				dspbuff[2] = 16;
				dspbuff[6] = 16;
				dspbuff[7] = 16;
			}
			TMAX=(TMAXTMIN / 1000) * 10 + (TMAXTMIN %1000/100);
			TMIN=(TMAXTMIN % 100/10) * 10 + (TMAXTMIN %10);
			if(TMIN > TMAX)
				LED2(1);
			else
				LED2(0);
			dspbuff[0] = 17;
			if(TMAXTMIN != 0) //û��������ֵʱ
			{
				dspbuff[1] = TMAX / 10;
				dspbuff[2] = TMAX % 10;
			}
			dspbuff[3] = 16;
			dspbuff[4] = 16;
			dspbuff[5] = 17;
			if(TMAXTMIN != 0)
			{
				dspbuff[6] = TMIN / 10;
				dspbuff[7] = TMIN % 10;
			}
		}
		/*-----------------------------ģʽʶ��-------------------------------------------------------------------*/
		if(Temperature < TMIN)
		{
			PATTERN = 0;
		}
		else if((Temperature <= TMAX)&&(Temperature >= TMIN))
		{
			PATTERN = 1;
		}
		else if(Temperature > TMAX)
		{
			PATTERN = 2;
		}
		/*-----------------------------�������ʾ------------------------------------------------------------------*/
		if(SetFlag == 0)
		{
			dspbuff[0] = 17;
			dspbuff[1] = PATTERN;
			dspbuff[2] = 17;
			dspbuff[3] = 16;
			dspbuff[4] = 16;
			dspbuff[5] = 16;
			dspbuff[6] = Temperature / 10;
			dspbuff[7] = Temperature % 10;
		}
		/*-------------------------------ִ�л���----------------------------------------------------------------*/
		if(PATTERN == 0)
		{
			RELAY(0);
			if(flag800ms == 1)
			{
				flag800ms = 0;
			  star = ~star;
				LED1(star);
			}
		}
		if(PATTERN == 1)
		{
			RELAY(0);
			if(flag400ms == 1)
			{
				flag400ms = 0;
			  star = ~star;
				LED1(star);
			}
		}
		if(PATTERN == 2)
		{
			RELAY(1);
			if(flag200ms == 1)
			{
				flag200ms = 0;
			  star = ~star;
				LED1(star);
			}
		}
	}	
}