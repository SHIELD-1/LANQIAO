#include"STC15F2K60S2.h"
#include"iic.c"
#include"ds1302.c"
#include"keypad.h"
#include"allinit.h"
#include"smg.h"

#define uchar unsigned char
#define uint unsigned int

sbit S7Switch = P3^0;
sbit S6 = P3^1;
sbit S5 = P3^2;
sbit S4 = P3^3;

uchar HUMIDITY_HOPE = 50,HUMIDITY_NOW; //ʪ����ֵ��ʪ�ȵ�ǰֵ��

bit AT=1;//�Զ�ģʽ��־
bit RELAY_Flag,BUZZ_Flag; //�̵�����־����������־



void ManualS();
void AutoS();

/*===============================================
 ָʾ����
===================================================*/
void RELAY(uchar i)  //1 ��
{
	if(i)
	{
	  P2 = (P2&0x1f)|0xA0;
    P0 = 0x10;
	  P2 &=0x1f;
	}
	else
	{
		P2 = (P2&0x1f)|0xA0;
    P0 = 0x00;
	  P2 &=0x1f;
	}
}

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
    P0 = 0xfe;
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
    P0 = 0xfd;
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



void main(void)
{
	uint ADC_Value;
	uchar hour,min;
	allinit();
	smg_Timer0init();
	DS1302_Init();
	HUMIDITY_HOPE=ReadByte_AT24C02(0x02);
	ADC_Read(0x03,&ADC_Value);
	while(1)
	{
		/*-----------------------------------------------------------*/
		//�Զ�ģʽ AT=1 / �ֶ�ģʽ�л� AT=0
		/*-------------------------------------------------------------**/
		if(!S7Switch && !SetFlag)
		{
			Delay10ms();
			if(!S7Switch)
			{
				AT = ~AT;
			}
			while(!S7Switch);
		}
		if(ReadTime == 1)
		{
			ReadTime = 0;
			hour = Ds1302_Single_Byte_Read(ds1302_hr_addr);
		  dspbuff[0]=hour / 16;
		  dspbuff[1]=hour % 16;
			dspbuff[2]=17;
		  min = Ds1302_Single_Byte_Read(ds1302_min_addr);
		  dspbuff[3]=min / 16;
		  dspbuff[4]=min % 16;
		}
		if(ReadHum == 1)
		{
			ReadHum = 0;
			//��ȡͨ��3 AD ģ��ת����ֵ����������
		  ADC_Read(0x03,&ADC_Value);
		  //��0~255ת��Ϊʪ�� 0~99
		  HUMIDITY_NOW =fun(ADC_Value);
		
		  dspbuff[6] = HUMIDITY_NOW % 100 / 10;
		  dspbuff[7] = HUMIDITY_NOW % 100 % 10;
			if(AT == 1)  //�ж��Ƿ����� �Զ�ģʽ
			{
				AutoS();
			}
			else
			{
				ManualS();
			}
		}
		
		/*-------------------------------------------------------------*/
		if(AT == 0) //�ֶ�ģʽ��������
		{
			if(!S6)
		 	{
		 		Delay10ms();
				if(!S6)
				{
				   BUZZ_Flag = ~BUZZ_Flag;
				}
				while(!S6);
		 	}
			if(!S5)
			{
				Delay10ms();
				if(!S5)
				{
					RELAY_Flag  = 1;
				}
				while(!S5);
			}
			if(!S4)
			{
				Delay10ms();
				if(!S4)
				{
					RELAY_Flag  = 0;
				}
				while(!S4);
			}
		}
		else  //�Զ�ģʽ��������
		{
			if(!S6)
			{
				Delay10ms();
				if(!S6)
				{
					SetFlag = ~SetFlag;
					if(SetFlag)
					{
						dspbuff[2] = 16;
						dspbuff[3] = 16;
						dspbuff[4] = 16;
						dspbuff[5] = 16;	
					}
					else
					{
					  Write_AT24C02(0x02,HUMIDITY_HOPE);//����ʪ����ֵ��EEPROM	
					}
				}
				while(!S6);
			}
			/*******************************ʪ����ֵ����*************************************/
			if(SetFlag)      //������ֵ����ģʽ
			{
				if(!S5)
				{
					Delay10ms();
					if(!S5)
					{
						HUMIDITY_HOPE++;	
					}
					while(!S5);
				}
				if(!S4)
				{
					Delay10ms();
					if(!S4)
					{
						HUMIDITY_HOPE--;	
					}
					while(!S4);
				}
				dspbuff[0] = 17;
				dspbuff[1] = 17;
				dspbuff[6] = HUMIDITY_HOPE/10;
				dspbuff[7] = HUMIDITY_HOPE%10;
			}        //��ֵ����ģʽ
		}     //�Զ�ģʽ����
	}
}

//		Delay100ms();

void Autos()
{
	LED1(1);
	if(HUMIDITY_NOW < HUMIDITY_HOPE)
		RELAY(1); 
	else 
		RELAY(0);
}

void ManualS()
{
	LED2(1);
	if((HUMIDITY_NOW < HUMIDITY_HOPE) && (BUZZ_Flag == 1))
	{
		if(RELAY_Flag == 1)
		{
			RELAY(1);
			BUZZ(1);
		}
		else
		{
			BUZZ(1);
		}
	}
	else
	{
		if(RELAY_Flag == 1)
		{
			RELAY(1);
		}
		else
		{
			RELAY(0);
			BUZZ(0);
		}
	}		
}