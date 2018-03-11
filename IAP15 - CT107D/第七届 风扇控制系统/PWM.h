/*---------------------------------------------------------------------------------
ʹ��ʱҪ���������Լ�ʱ��1���г�ʼ��
-------------------------------------------------------------------------------------*/
#ifndef _PWM_H_
#define _PWM_H_

#ifndef uchar
#define uchar unsigned char
#endif

#ifndef uint
#define uint unsigned int
#endif

#define OUTPUT       P34               //����LED�ӿ�
#define OUTPUT_ON()  OUTPUT = 1;      //����LED��   /* ���Զ����������ܽ� */
#define OUTPUT_OFF() OUTPUT = 0;		//����LED��

#define PWM_LIMIT_MAX  99      //0~99�ȷ�����µ�ռ�ձ�������
#define PWM_LIMIT_MIN  0

uchar PWMConter = 20;  //ռ�ձ�
bit PWMflag = 0;

static uchar TimerConter = 0;      //��ʱ���жϴ���
//static uchar PWMDirection = 0;     //ռ�ձȱ仯����  1 �� ռ�ձȼ���  0�� ռ�ձ�����
//static signed char PWMConter = 0;  //ռ�ձ�     


void Timer1_Init()//200΢��@11.0592MHz
{
//	TMOD &= 0x0f;		//���ö�ʱ��ģʽ
//	TMOD |= 0x10;		//���ö�ʱ��ģʽ
//	TL1 = 0x47;		//���ö�ʱ��ֵ
//	TH1 = 0xff;		//���ö�ʱ��ֵ
//	TR1 = 1;		//��ʱ��0��ʼ��ʱ
//	ET1  = 1;
//	EA = 1;
	AUXR &= 0xBF;		//��ʱ��ʱ��12Tģʽ
	TMOD &= 0x0F;		//���ö�ʱ��ģʽ
	TMOD |= 0x10;		//���ö�ʱ��ģʽ
	TL1 = 0xF7;		//���ö�ʱ��ֵ
	TH1 = 0xFF;		//���ö�ʱ��ֵ
	TR1 = 1;		//��ʱ��1��ʼ��ʱ
	ET1 = 1;
	EA = 1;
}


//ÿ200us����һ���ж�,ռ�ձȻ��ڼ���100�ε���ռ�ձȣ�ÿ����������ռ�ձȻ��ڼ�����ͬʱ���μ�һ��������ʣ��ʱ�������֮ǰ�෴�Ļ
void Timer1(void) interrupt 3
{
	static signed char PWMConter_NOW = 0;
	TL1 = 0xF7;		//���ö�ʱ��ֵ
	TH1 = 0xFF;		//���ö�ʱ��ֵ
//	TL1 = 0x47;		//���ö�ʱ��ֵ
//	TH1 = 0xff;		//���ö�ʱ��ֵ

  if(++TimerConter >= 100)  //200us*100 ����һ��ռ�ձ� ռ�ձȵ����ޱ���С�� 100����Ϊÿ������(2ms)��ռ�ձȱ�������һ�ε���ǰ���꣬Ҳ���ǲ��ܳ������������ֵ
	{
		TimerConter = 0;      //��ʱ���жϼ���ֵ����
//		if((PWMConter <= PWM_LIMIT_MAX) && (0 ==PWMDirection ))    // �ж�ռ�ձ��Ƿ�С�����޲��������ӵķ���
//		{
//			PWMConter++;
//			if(PWMConter > PWM_LIMIT_MAX)
//			{
//				PWMDirection = 1;
//				PWMConter = PWM_LIMIT_MAX;
//			}
//		}
//		if((PWMConter >= PWM_LIMIT_MIN) && (1 == PWMDirection))    // �ж�ռ�ձ��Ƿ�������޲����ڼ�С�ķ���
//		{
//			PWMConter--;
//			if(PWMConter < PWM_LIMIT_MIN)
//			{
//				PWMDirection = 0;
//				PWMConter = PWM_LIMIT_MIN;
//			}
//		}
		PWMConter_NOW = PWMConter;
	}
  if(PWMConter_NOW > 0 && PWMflag)  //ÿ�ν����ж϶�������жϲ�ִ��
 	{
		OUTPUT_ON();         //�͵�ƽ   |____
		PWMConter_NOW--;
	}
  else
	{
		OUTPUT_OFF();        //�ߵ�ƽ 
	}		
}

#endif



