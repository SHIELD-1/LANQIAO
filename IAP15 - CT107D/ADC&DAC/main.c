#include"STC15F2K60S2.h"
#include"allinit.h"
#include"smg.h"
#include"iic.c"


#define  uchar unsigned char 
#define  uint  unsigned int 

/*===============================================
 ָʾ����
===================================================*/
void BUZZ(uchar i)  //1 ��
{
	if(i)
	{
	  P2 = (P2&0x1f)|0xA0;
    P0 = 0x40;
	  P2 &=0x1f;
	}
	else
	{
		P2 = (P2&0x1f)|0xA0;
    P0 = 0x00;
	  P2 &=0x1f;
	}
}

void LED1(uchar i)  //1 ��
{
	if(i)
	{
	  P2 = (P2&0x1f)|0x80;
    P0 = 0x7f;
	  P2 &=0x1f;
	}
	else
	{
	  P2 = (P2&0x1f)|0x80;
    P0 = 0xff;
	  P2 &=0x1f;
	}
}

void LED2(uchar i)  //1 ��
{
	if(i)
	{
	  P2 = (P2&0x1f)|0x80;
    P0 = 0xbf;
	  P2 &=0x1f;
	}
	else
	{
	  P2 = (P2&0x1f)|0x80;
    P0 = 0xff;
	  P2 &=0x1f;
	}
}
/*==================================================*/
void Delay100ms()		//@11.0592MHz
{
	unsigned char i, j, k;

	_nop_();
	_nop_();
	i = 5;
	j = 52;
	k = 195;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}


void main(void)
{
	uint ADC_Value;
	allinit();
	smg_Timerinit();
//	ADC_Init(0x01); //1 Ϊ������ 3  ΪRb2��λ��
	while(1)
	{
		//��ȡͨ��3 AD ģ��ת����ֵ����������
		if(ADC_Read(0x03,&ADC_Value)) LED1(1); else  LED1(0);
		//�� AD ģ��ת���õ�����ֵ���͸�PCF8591 ����DA��ģת��ת��Ϊģ��������ģ��������ڵ�С�� 
		if(DAC_Out(ADC_Value)) LED2(1); else LED2(0);  //Ϊʲô����һ��ע�͵�����һ��С�Ƴ�����
		//��ʾ
		ADC_Value = fun(ADC_Value);
		dspbuff[0]=ADC_Value/100+17;
		dspbuff[1]=ADC_Value%100/10;
		dspbuff[2]=ADC_Value%100%10;
		if(ADC_Value > 150)   BUZZ(1); else BUZZ(0);
		Delay100ms();
	}
	
}