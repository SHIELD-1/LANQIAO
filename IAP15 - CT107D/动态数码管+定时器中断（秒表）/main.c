#include"STC15F2K60S2.h"
#include"allinit.h"
#include"smg.h"
#define uchar unsigned char
#define uint unsigned int

uint sec=23,min=59,hour=1; //�����cnt�ķ�Χ��Ҫ��0~500�����Բ�����uchar��

void main()
{
	allinit();      
  smg_Timerinit(); //�����������ʾ���� smg.h ���ǵ����������м������ʱ��T0��ʼ��
	//������ʾ 00-00-00
	dspbuff[7]=sec%10;
	dspbuff[6]=sec/10;
	dspbuff[5]=11;
	dspbuff[4]=min%10;
	dspbuff[3]=min/10;
	dspbuff[2]=11;
	dspbuff[1]=hour%10;
	dspbuff[0]=hour/10;
	while(1)
	{
		if(cnt==500) //500*2ms=1 s
		{
			cnt=0; 
			sec++;
			if(sec<60)   //��ʱ1����
			{
			  dspbuff[6]=sec/10;
				dspbuff[7]=sec%10;
			}
			
			if(sec==60)  //1������
			{
				// ��������
				sec=0;
				// ��һ������ʾ 00-01-00
				dspbuff[6]=sec/10;
				dspbuff[7]=sec%10;
				min++;
				dspbuff[3]=min/10;
				dspbuff[4]=min%10;
				if(min==60)
			  {
					dspbuff[3]=0;
					dspbuff[4]=0;
					hour++;
					dspbuff[0]=hour/10;
					dspbuff[1]=hour%10;
					// ����������
					min=0;
			  }
		  }
	  }	
	}		
}
