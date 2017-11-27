#include<reg52.h>
#include<intrins.h>
#define uchar unsigned char
#define uint unsigned int

sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;

uchar code duanma[17]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
					0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};//显示0~F的值
uint t;
uchar i=0;
//主函数
void main()
{
	EA=1;
	ET0=1;
	TR0=1;
  TMOD|=0x01; 
	TH0=0XFC;
	TL0=0x18;

	
	while(1)
	{
		
		if(t==1000)
		{
			t=0;
			LSA=1;LSB=1;LSC=1; 
	    P0=duanma[i];//发送段码 	
			if(i<9) i++;
			else  i=0;
		}	
	}
}

void T0_TIME() interrupt 1
{
	TH0=0XFC;
	TL0=0x18;
	t++;
}
