/*******************************************************************************************
ʹ��ʱҪ��������main()д�ϳ�ʼ������ smg_Timerinit();
********************************************************************************************/
#ifndef _SMG_H_
#define _SMG_H_
#define uchar unsigned char
#define uint unsigned int
uint cnt;   //cntΪȫ�ֱ������ŵ���ǰ������ڱ���ļ���ʹ��(������õ���)
//�������������ʾ���룬�߲���������������ָ�������������ӵ�ѹ��
           //     0    1    2    3     4    5    6    7
uchar tab[28]={ 0xc0,0xf9,0xa4,0xb0, 0x99,0x92,0x82,0xf8,
	         //   8    9    A    b     C    d    E    F   ��    -
             	0x80,0x90,0x88,0x83, 0xc6,0xa1,0x86,0x8e,0xff,0xbf,
	         //   0.          1.        2.        3.          4.       5.         6.       7.
	            0xc0&0x7f,0xf9&0x7f,0xa4&0x7f,0xb0&0x7f, 0x99&0x7f,0x92&0x7f,0x82&0x7f,0xf8&0x7f,
	         //      8.       9.
             	0x80&0x7f,0x90&0x7f};

uchar dspbuff[]={16,16,16,16,16,16,16,16};
uchar dspcom=0;

void display()
{
	//���������
	P2=(P2&0x1f)|0xe0;
	P0=0xff;
	P2&=0x1f;
  //λѡ
	P2=(P2&0x1f)|0xc0;
	P0=(1<<dspcom);
	P2&=0x1f;
	//��������
	P2=(P2&0x1f)|0xe0;
	P0=tab[dspbuff[dspcom]];
	P2&=0x1f;
	if(++dspcom==8)
		dspcom=0;
}

void smg_Timerinit()
{
	TMOD|= 0x01;
	TH0 = (65535-2000)/256; //2ms
	TL0 = (65535-2000)%256;
	ET0 = 1;
	TR0 = 1;
	EA = 1;
}

void smg_timer0()interrupt 1 //��ʱ��0��Ӧ interrupt 1
{
	cnt++;
	TH0=(65535-2000)/256;
	TL0=(65535-2000)%256;
	display();
}

#endif
