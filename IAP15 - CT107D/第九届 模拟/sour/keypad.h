#ifndef _keypad_h_
#define _keypad_h_

#include"includes.h"

#define uchar unsigned char
#define uint unsigned int
#define gpio_key P3   // �������ɨ��˿ڶ��� ע�⣺�˿�ɨ��ʹ�� #define

sbit S7 = P3^0; //������������
sbit S6 = P3^1;
sbit S5 = P3^2;
sbit S4 = P3^3;



void Delay10ms();		//@11.0592MHz
void key_down();

#endif
