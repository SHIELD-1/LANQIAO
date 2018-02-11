#ifndef _keypad_h_
#define _keypad_h_

#define uchar unsigned char
#define uint unsigned int
//#define gpio_key P3   // �������ɨ��˿ڶ��� ע�⣺�˿�ɨ��ʹ�� #define

sbit S7 = P3^0; //������������
sbit S6 = P3^1;
sbit S5 = P3^2;
sbit S4 = P3^3;

bit SetFlag5 = 1,SetFlag7 = 1; //������־
uchar key_value=16; //��ֵ�������壬����ʾ

void Delay10ms()		//@11.0592MHz
{
	uchar i, j;

	i = 108;
	j = 145;
	do
	{
		while (--j);
	} while (--i);
}

//void key_down()
//{
//	//�������¾�֤ 1111 0000
//	P44=0;P42=0;
//	gpio_key=0x0f;
//	if(gpio_key!=0x0f)
//	{
//		Delay10ms();//10ms ����
//		if(gpio_key!=0x0f)
//		{
//			//�з�תɨ���ʼ�� 1111 0000
//			P42=1;P44=1;
//			gpio_key=0x30;
//			//��ɨ���ж�
//			if((gpio_key==0x30)&&(P44==0)&&(P42==1))
//				key_value=0;
//			if((gpio_key==0x30)&&(P44==1)&&(P42==0))
//				key_value=1;
//			if((gpio_key==0x10)&&(P44==1)&&(P42==1))
//				key_value=2;
//			if((gpio_key==0x20)&&(P44==1)&&(P42==1))
//				key_value=3;
//			//�з�תɨ���ʼ�� 0000 1111
//			P42=0;P44=0;
//			gpio_key=0x0f;
//			switch(gpio_key)
//			{
//				case(0x0e) : key_value +=0;break; //0000 1110
//				case(0x0d) : key_value +=4;break; //0000 1101
//				case(0x0b) : key_value +=8;break; //0000 1011
//				case(0x07) : key_value +=12;break; //0000 0111
//			}
//			/*���ּ��*/
//			while(gpio_key!=0x0f); // ע�����ּ���λ��
//		}
//	}
//}

key_down()
{
	if(!S7)
	{
		Delay10ms();
		if(!S7)
		{
			key_value = 7;
			SetFlag7 = ~SetFlag7;
		}
		while(!S7);
	}
	if(!S6)
	{
		Delay10ms();
		if(!S6)
		{
			key_value = 6;
		}
		while(!S6);
	}
	if(!S5)
	{
		Delay10ms();
		if(!S5)
		{
			key_value = 5;
			SetFlag5 = ~SetFlag5;
		}
		while(!S5);
	}
	if(!S4)
	{
		Delay10ms();
		if(!S4)
		{
			key_value = 4;
		}
		while(!S4);
	}
}

#endif