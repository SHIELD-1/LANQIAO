#ifndef _ALLINIT_H_ //记得在 #ifndef 和 _ALLINIT_H_之间加空格
#define _ALLINIT_H_

#include"STC15F2K60S2.h"

void allinit();
/*===============================================
 指示部分
===================================================*/
void RELAY(bit i); //1 开
//void BUZZ(bit i);  //1 开
void LED1(bit i);  //1 开
void LED2(bit i);  //1 开

#endif
