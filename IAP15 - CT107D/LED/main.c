/*****************************************************
//IO口编程；
//LED灯右移循环
***************************************************/
#include"reg52.h"
#include"intrins.h"

#define uchar unsigned char
#define uint unsigned int

//关闭外设
void cls_buzz(void)
{
	P2 = (P2&0x1F|0xA0);
	P0 = 0x00;
	P2 &= 0x1F;
}
//延时函数
void delay()		//@11.0592MHz
{
	unsigned char i, j, k;
	_nop_();
	_nop_();
	i = 9;
	j = 104;
	k = 139;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

void main()
{
	uchar i;
	cls_buzz();
	while(1)
	{
		for(i=0;i<8;i+=2)
		{
			P2=((P2&0x1f)|0x80);
	    P0=~(0x01<<i);//左移i位;P0^7~P0^1 ==> L8~L1 所以在开发板为右移； 如何能够跳两位？？？  error：i+2  right： i+=2
		  P2&=0x1f;
	   	delay();
		}
	
	}
}
