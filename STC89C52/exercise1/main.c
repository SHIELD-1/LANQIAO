#include<reg52.h>
#include<intrins.h>
#define uchar unsigned char
#define uint unsigned int
sbit k1=P3^0;
sbit k2=P3^1;
sbit k3=P3^2;

sbit led=P2^0;

sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;


uchar KeyValue;
uchar code smgduan[17]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,
0x7c,0x39,0x5e,0x79,0x71};//段码表2
/*****************************************************
* 延时函数
******************************************************/
void delay(uint t)
{
  while(t--);
}

void DigDisplay7()
{
	LSA=1;LSB=1;LSC=1;
	P0=smgduan[7];
	delay(50000);
}
void DigDisplay6()
{
	LSA=1;LSB=1;LSC=1;
	P0=smgduan[6];
	delay(50000);
}
void DigDisplay5()
{
	uchar i;
	LSA=1;LSB=1;LSC=1;
	for(i=0;i<10;i++)
	{
	 P0=smgduan[i];
	 delay(50000);
	 P0=0x00;
	}
}


void keypros()
{
	if(k1==0)
	{
		delay(1000);
		if(k1==0)
		{
			DigDisplay7();
		}
		while(!k1);
	}	
	else if(k2==0)
	{
		delay(1000);
		if(k2==0)
		{
		  DigDisplay6();
		}
		while(!k1);
	}	
	else if(k3==0)
	{
		delay(1000);
		if(k3==0)
		{
			DigDisplay5();
		}
		while(!k1);
	}	
}
void main()
{
	P0=0x00;
	P2=0xff;
	while(1)
	{
		keypros();
	}		
}
