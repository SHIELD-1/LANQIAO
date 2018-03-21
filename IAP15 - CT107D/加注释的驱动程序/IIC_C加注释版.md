/*
  ����˵��: IIC�����������򣨼�ע�Ͱ棩
  �������: Keil uVision 5
  Ӳ������: CT107��Ƭ���ۺ�ʵѵƽ̨(12MHz)
  ��    ��: 2018-01-24
*/
#include<reg52.h>
#include "iic.h"

//������������	1
void IIC_Start(void)
{
	SDA = 1;
	SCL = 1;
	somenop;
	SDA = 0;
	somenop;
	SCL = 0;
}

//����ֹͣ����	2
void IIC_Stop(void)
{
	SDA = 0;
	SCL = 1;
	somenop;
	SDA = 1;
}

//����Ӧ��λ���� 3
/*�������Ķ��Ǳ�̿��ƣ��ӻ����Ķ����������ƣ�Ҳ����˵��Ӳ�����ƣ���������Ӧ���ź��Ǳ�̿��ƣ�
  ���Ǵӻ���Ӧ���ź���Ӳ�����ƣ�����ֻ��Ҫ�� WaitAck() �м��SCLΪ�ߵ�ƽ�ڼ䣬SDA���ֵ͵�ƽһ
  Щʱ�䣬�����ж��ӻ���������Ӧ���źš�
*/
void IIC_Ack(unsigned char ackbit)	 //1�������������
{
	if(ackbit)
	{
		SDA = 0;
	}
	else
	{
		SDA = 1;
	}
	somenop;
	SCL = 1;
	somenop;
	SCL = 0;
	SDA = 1;
	somenop;
}

//�ȴ�Ӧ��	4
bit IIC_WaitAck(void) //����һ����õ�Ӧ��
{
    /*����λ��Ч�ԣ�SCLΪ�ߵ�ƽ�ڼ��ڣ�SDA�����ȱ����ȶ���
	ֻ����ʱ����Ϊ�͵�ƽ�ڼ䣬�����ߵĸߵ�ƽ��͵�ƽ״̬������仯��*/
	SDA = 1;
	somenop;
	SCL = 1;
	somenop;
	if(SDA) //���SDA�������Ƿ����ͣ������ͷ��� 1����ʾӦ�𼴼����������ݣ�
	{
		SCL = 0;
		IIC_Stop();
		return 0;
	}
	else
	{
		SCL = 0;
		return 1;
	}
}

//ͨ��I2C���߷�������	5
void IIC_SendByte(unsigned char byte)
{
	unsigned char i;
	for(i=0;i<8;i++)
	{
		if(byte&0x80) //1000 0000
		{
			SDA = 1;
		}
		else
		{
			SDA = 0;
		}
		somenop;
		SCL = 1;
		somenop;
		SCL = 0;//IIC����д����ʱ��ʱ����SCLҪ���ͣ�������SDA������仯��
		byte <<= 1;//������λ�ɷŵ����
	}
}

//��I2C�����Ͻ�������  6
unsigned char IIC_RecByte(void)
{
	unsigned char date;
	unsigned char i;

	for(i=0;i<8;i++)
	{
		SCL = 1;//IIC��ȡ��ʱ��Ҫ����SCL���������ȶ���
		somenop;
		date <<= 1;
		/* ���������Ϊ�ߵ�ƽ��˵�������ݣ�����0000 0001��ȡdate�����һλ��
		����date����һλ�����λ��*/
		if(SDA)
		date |= 0x01;
		SCL = 0;
		somenop;
	}
	return date;
}

//����Ϊ�Լ���Ҫд�ĳ��򲿷�

//��EEPROM��д�����ݣ���ַ+���ݣ�
void Write_AT24C02(unsigned char add, unsigned char date)
{
    IIC_Start(); //������ʼλ
    IIC_SendByte(0xa0);//  ,���ʹ��豸�ĵ�ַ1010  000�Ͷ�/д0ѡ��λ��
    /*�ͷ����ߣ��ȵ�EEPROM�������߽���Ӧ�����EEPROM���ճɹ��������Ӧ��
    ��û�����ֳɹ����߷��͵����ݴ���ʱEEPROM������Ӧ�𣬴�ʱҪ���ط�������ֹ*/
    IIC_WaitAck();
    IIC_SendByte(add);//������Ҫд����ڲ��Ĵ�����ַ��
    IIC_WaitAck();//EEPROM���䷢��Ӧ��
    IIC_SendByte(date);//��������
    IIC_WaitAck();//EEPROM���䷢��Ӧ��
    IIC_Stop();//����ֹͣλ
    delay10ms();
    /*EEPROM�յ�ֹͣ�źź󣬽��뵽һ���ڲ���д�����ڣ������Ҫ10ms���˼��κβ��������ᱻEEPROM��Ӧ��
    (��������ַ�ʽ������д��֮��Ҫ����һ����ʱ������ᵼ��ʧ��*/
}

//��EEPROM������ݣ���ַ��
unsigned char ReadByte_AT24C02(unsigned char add)
{
    unsigned char date;
    IIC_Start();//������ʼλ��
    IIC_SendByte(0xa0);// 1010  000 0���������д���������ʹӻ���ַ+��1/д0λ
    IIC_WaitAck();
    IIC_SendByte(add);//�����ڲ��Ĵ�����ַ��
    IIC_WaitAck();
    IIC_Start();//���·�����ʼλ����restart��
    IIC_SendByte(0xa1);//1010 000 1�����������,���·��ʹӻ���ַ+��1/д0λ��
    IIC_WaitAck();
    date=IIC_RecByte();//��ȡ����
    /* �����������ڽ��յ����һ���ֽں�Ҳ���ᷢ��ACK�źš�
    ���ǣ��ӻ��������ͷ�SDA�ߣ��������������� stop �źŽ������䡣*/
    IIC_Ack(0);
    IIC_Stop();// ����ֹͣλ?
}
