#include "includes.h"

bit  Send_Flag,Rec_Flag;
char RxdByte = 0x55,ch;

void UartInit(void)		//9600bps@11.0592MHz
{
	SCON = 0x50;		//8λ����,�ɱ䲨����
	AUXR |= 0x40;		//��ʱ��1ʱ��ΪFosc,��1T
	AUXR &= 0xFE;		//����1ѡ��ʱ��1Ϊ�����ʷ�����
	TMOD &= 0x0F;		//�趨��ʱ��1Ϊ16λ�Զ���װ��ʽ
	TL1 = 0xE0;		//�趨��ʱ��ֵ
	TH1 = 0xFE;		//�趨��ʱ��ֵ
	ET1 = 0;		//��ֹ��ʱ��1�ж�
	TR1 = 1;		//������ʱ��1
	ES = 1;
	EA = 1;
}

//void SendData(unsigned char ch)		   //����һ���ֽ� //��Ƭ������Է���
//{
//	SBUF = ch;   //�������͵����ݷŵ����ͻ�������
//	while(!TI);  //�ȴ�������ϣ�δ������ʱ TI Ϊ 0��������֮�� TI Ϊ 1��
//	TI = 0 ;     // ��ȻӲ���� 1 �ˣ��Ǿͱ����������
//}
//void SendString(unsigned char *s)		//����һ���ַ���
//{
//	while(*s)  // ����Ƿ�����ϣ����������ε� \0��
//	{
//		SendData(*s++); // ���ú���һ���ֽ�һ���ֽڷ���
//	}
//}

////��Ƭ�����ڷ���
//void Uart_TX(char ch)
//{
//	 SBUF = ch; //���͵�����
//	 Send_Flag = 0;         //��־�������ͣ����
//}

//�����жϷ�����
void Usart_Routnie(void) interrupt 4 
{
	  if (RI)        //����ǽ����ж� ��Ƭ������
    {
			 RI = 0;  //�ֶ���������жϱ�־λ
			 RxdByte = SBUF;
    }
    else if (TI)  //�ֽڷ������
    {
    	TI = 0;  //�ֶ����㷢���жϱ�־λ
    }
}
