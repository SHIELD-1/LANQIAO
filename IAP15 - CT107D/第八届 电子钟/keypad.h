#ifndef _keypad_h_
#define _keypad_h_

#include"ds1302.h"

#define uchar unsigned char
#define uint unsigned int
//#define gpio_key P3   // �������ɨ��˿ڶ��� ע�⣺�˿�ɨ��ʹ�� #define

sbit S7 = P3^0; //������������
sbit S6 = P3^1;
sbit S5 = P3^2;
sbit S4 = P3^3;



bit SetFlag; //���ð�ť��־λ
bit STAR = 0;
uchar key_value=16; //��ֵ�������壬����ʾ,����������������

uchar setnum7 = 0,setnum6 = 1; //���� S7 S6 �İ�������˳���л� 
bit TIME_NOW_FLAG = 0,TIME_BUZZ_FLAG = 0; //ʱ�����ñ�־λ


uchar Time_DEC = 0; //BCD��ת��Ϊʮ����ʱ�� + 1
uchar Hourbuff,Minbuff,Secbuff;
uchar Hour_Flag,Min_Flag,Sec_Flag; //����ʱ��
uint Temper;

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
//			if(key_value == 13)  //���ڴ˴��ı��־λ������Ӱ�������ڶ�����������־λȡ��Ҫ���ڰ���������
//				SetFlag = ~SetFlag;
//			if(SetFlag == 1) //�������ý��水����Ч
//			{
//				switch(key_value)
//				{
//					case(0): TMAXTMIN = 0 + TMAXTMIN *10;break;
//					case(1): TMAXTMIN = 1 + TMAXTMIN *10;break;
//					case(2): TMAXTMIN = 2 + TMAXTMIN *10;break;
//					case(4): TMAXTMIN = 3 + TMAXTMIN *10;break;
//					case(5): TMAXTMIN = 4 + TMAXTMIN *10;break;
//					case(6): TMAXTMIN = 5 + TMAXTMIN *10;break;
//					case(8): TMAXTMIN = 6 + TMAXTMIN *10;break;
//					case(9): TMAXTMIN = 7 + TMAXTMIN *10;break;
//					case(10): TMAXTMIN = 8 + TMAXTMIN *10;break;
//					case(12): TMAXTMIN = 9 + TMAXTMIN *10;break;
//					case(14): TMAXTMIN = 0;
//				}
//		  }
//			/*���ּ��*/
//			while(gpio_key!=0x0f);
//		}			// ע�����ּ���λ��
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
			if(STAR_Flag == 1)
			{
				LED2(1);
				STAR = 0;
				STAR_Flag = 0;
			}
			TIME_NOW_FLAG = 1; //����S7ʱ���־λ Ϊ 1
			TIME_BUZZ_FLAG = 0;
			setnum7++;
			if(setnum7 == 4 )
				setnum7 = 0;
			if(setnum7 == 0)
			{
				TIME_NOW_FLAG = 0; //�����ʹ��Ĭ����ʾ
		    DS1302_Init();
			}
		}
		while(!S7);
	}
	if(!S6)
	{
		Delay10ms();
		if(!S6)
		{
			key_value = 6;
			if(STAR_Flag == 1)
			{
				LED2(1);
				STAR = 0;
				STAR_Flag = 0;
			}
			TIME_NOW_FLAG = 0;
			TIME_BUZZ_FLAG = 1;
			setnum6++;
			if(setnum6 == 4)
				setnum6 = 0;
			if(setnum6 == 0)
				TIME_BUZZ_FLAG = 0; //�����ʹ��Ĭ����ʾ
		}
		while(!S6);
	}
	if(!S5)  // +
	{
		Delay10ms();
		if(!S5)
		{
			if(STAR_Flag == 1)
			{
				LED2(1);
				STAR = 0;
				STAR_Flag = 0;
			}
			if(TIME_NOW_FLAG == 1 )
			{
				switch(setnum7)
				{
					case(1): 
					{
						Time_DEC = (Hourbuff / 16) * 10 + (Hourbuff % 16);  //����ǰ������BCD��ת��Ϊ10����
						Time_DEC++;   //��ʮ��������ʾ�� 1 ����
						Timeinit[2] = (Time_DEC / 10) * 16 + (Time_DEC % 10); 
					  if(Timeinit[2] == 0x24)  //���ݵı߽�����
					    Timeinit[2] = 0x00; 
						Hourbuff = Timeinit[2]; //�����������ֵ��ʾ
					  break;
					}
					case(2): 
					{
						Time_DEC = (Minbuff / 16) * 10 + (Minbuff % 16); 
						Time_DEC++;
						Timeinit[1] = (Time_DEC / 10) * 16 + (Time_DEC % 10); 
					  if(Timeinit[1] == 0x60) 
					    Timeinit[1] = 0x00; 
						Minbuff = Timeinit[1]; //�����������ֵ��ʾ
					  break;
					}
					case(3): 
					{
						Time_DEC = (Secbuff / 16) * 10 + (Secbuff % 16); 
						Time_DEC++;
						Timeinit[0] = (Time_DEC / 10) * 16 + (Time_DEC % 10); 
					  if(Timeinit[0] == 0x60) 
					    Timeinit[0] = 0x00; 
						Secbuff = Timeinit[0]; //�����������ֵ��ʾ
					  break;
					}
				}
			}
			if(TIME_BUZZ_FLAG == 1 )
			{
				switch(setnum6)
				{
					case(1): 
					{
						Hour_Flag++;   //��ʮ��������ʾ�� 1 ����
					  if(Hour_Flag == 24)  //���ݵı߽�����
					    Hour_Flag = 0; 
						Hourbuff = Hour_Flag; //�����������ֵ��ʾ
					  break;
					}
					case(2): 
					{
						Min_Flag++;
					  if(Min_Flag == 60) 
					    Min_Flag = 0; 
						Minbuff = Min_Flag; //�����������ֵ��ʾ
					  break;
					}
					case(3): 
					{
						Sec_Flag++;
					  if(Sec_Flag == 0x60) 
					    Sec_Flag = 0x00; 
						Secbuff = Sec_Flag; //�����������ֵ��ʾ
					  break;
					}
				}
			}
		}
		while(!S5);
	}
	if(!S4)  // -
	{
		Delay10ms();
		if(!S4)
		{
			key_value = 4;
			if(STAR_Flag == 1)
			{
				LED2(1);
				STAR = 0;
				STAR_Flag = 0;
			}
			if(TIME_NOW_FLAG == 0 && TIME_BUZZ_FLAG == 0)
			{
				dspbuff[0] = 16; 
				dspbuff[1] = 16;
				dspbuff[2] = 16;
				dspbuff[3] = 16;
				dspbuff[4] = 16;
				dspbuff[5] = Temper / 10;
				dspbuff[6] = Temper % 10;
				dspbuff[7] = 12;
			}
			if(TIME_NOW_FLAG == 1 ) 
			{
				switch(setnum7)
				{
					case(1): 
					{
						Time_DEC = (Hourbuff / 16) * 10 + (Hourbuff % 16); 
						Time_DEC--;
						Timeinit[2] = (Time_DEC / 10) * 16 + (Time_DEC % 10); 
					  if(Time_DEC == -1) 
					    Timeinit[2] = 0x23; 
						Hourbuff = Timeinit[2]; //�����������ֵ��ʾ
					  break;
					}
					case(2): 
					{
						Time_DEC = (Minbuff / 16) * 10 + (Minbuff % 16); 
						Time_DEC--;
						Timeinit[1] = (Time_DEC / 10) * 16 + (Time_DEC % 10); 
					  if(Time_DEC == -1) 
					    Timeinit[1] = 0x59; 
						Minbuff = Timeinit[1]; //�����������ֵ��ʾ
					  break;
					}
					case(3): 
					{
						Time_DEC = (Secbuff / 16) * 10 + (Secbuff % 16); 
						Time_DEC--;
						Timeinit[0] = (Time_DEC / 10) * 16 + (Time_DEC % 10); 
					  if(Time_DEC == -1) 
					    Timeinit[0] = 0x59; 
						Secbuff = Timeinit[0]; //�����������ֵ��ʾ
					  break;
					}
				}
			}
			if(TIME_BUZZ_FLAG == 1 ) 
			{
				switch(setnum6)
				{
					case(1): 
					{ 
						Hour_Flag--;
					  if(Hour_Flag == -1) 
					    Hour_Flag = 23; 
						Hourbuff = Hour_Flag; //�����������ֵ��ʾ
					  break;
					}
					case(2): 
					{
						Min_Flag--;
					  if(Min_Flag == -1) 
					    Min_Flag = 59; 
						Minbuff = Min_Flag; //�����������ֵ��ʾ
					  break;
					}
					case(3): 
					{
						Sec_Flag--;
					  if(Sec_Flag == -1) 
					    Sec_Flag = 59; 
						Secbuff = Sec_Flag; //�����������ֵ��ʾ
					  break;
					}
				}
			}
		}
		while(!S4);
	}
}

#endif