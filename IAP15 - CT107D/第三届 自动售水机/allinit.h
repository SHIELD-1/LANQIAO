#ifndef _ALLINIT_H_ //�ǵ��� #ifndef �� _ALLINIT_H_֮��ӿո�
#define _ALLINIT_H_
void allinit()
{
	P2=(P2&0x1f)|0x80;
	P0=0xff;
	P2&=0x1f;
	
	P2=(P2&0x1f)|0xA0;
	P04=0;
	P06=0;
	P2&=0x1f;
	
	P2=(P2&0x1f)|0xc0;
	P0=0xff;
	P2&=0x1f;
	P2=(P2&0x1f)|0xe0;
	P0=0xFF;
	P2&=0x1f;
}
/*===============================================
 ָʾ����
===================================================*/
void RELAY(bit i)  //1 ��
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

//void BUZZ(bit i)  //1 ��
//{
//	if(i)
//	{
//	  P2 = (P2&0x1f)|0xA0;
//    P0 = 0x40;
//	  P2 &=0x1f;
//	}
//	else
//	{
//		P2 = (P2&0x1f)|0xA0;
//    P0 = 0x00;
//	  P2 &=0x1f;
//	}
//}

void LED1(bit i)  //1 ��
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

//void LED2(bit i)  //1 ��
//{
//	if(i)
//	{
//	  P2 = (P2&0x1f)|0x80;
//    P0 = 0xfd;
//	  P2 &=0x1f;
//	}
//	else
//	{
//	  P2 = (P2&0x1f)|0x80;
//    P0 = 0xff;
//	  P2 &=0x1f;
//	}
//}
#endif