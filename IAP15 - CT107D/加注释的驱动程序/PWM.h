/*---------------------------------------------------------------------------------
ʹ��ʱҪ���������Լ�ʱ��1���г�ʼ��
-------------------------------------------------------------------------------------*/
#ifndef _PWM_H_
#define _PWM_H_

#include"STC15F2K60S2.h"
#include<intrins.h>

#ifndef uchar
#define uchar unsigned char
#endif

#ifndef uint
#define uint unsigned int
#endif

#define LED       P0               //����LED�ӿ�
#define LED_ON()  LED = 0x00;      //����LED��   /* ���Զ����������ܽ� */
#define LED_OFF() LED = 0xff;		//����LED��

#define PWM_LIMIT_MAX  99      //0~99�ȷ�����µ�ռ�ձ�������
#define PWM_LIMIT_MIN  0



static uchar TimerConter = 0;      //��ʱ���жϴ���
static uchar PWMDirection = 0;     //ռ�ձȱ仯����  1 �� ռ�ձȼ���  0�� ռ�ձ�����
static signed char PWMConter = 0;  //ռ�ձ�


void Timer1_Init();/200΢��@11.0592MHz

#endif



