#include "ds1302.h"
/*！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
调用此模块时记得在main() 里调用初始化函数 DS1302_Init()；

！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！*/
/********************************************************************/
//------------------------------------------------------------------
//函数名称：Write_Ds1302_Byte(unsigned char dat)
//函数功能：向DS1302写入一个字节
//输入参数：date  将要写入的数据
//返回值：无
//时序原理：在控制指令字输入后的下一个SCLK时钟的上升沿时数据被写入DS1302，数据输入从第0位开始
//------------------------------------------------------------------

/*发送一个字节到 DS1302 通信总线上*/
void Write_Ds1302_Byte(unsigned char dat)
{
	unsigned char i;
	SCK = 0;                //拉低SCLK，为脉冲上升沿写入数据做好准备
	for (i=0;i<8;i++)
	{
		if (dat & 0x01) 	// 首先取出dat的第0位(低位)数据写入1302
		{
			SDA_SET;		//#define SDA_SET SDA=1 /*电平置高*/
		}
		else
		{
			SDA_CLR;		//#define SDA_CLR SDA=0 /*电平置低*/
		}
		SCK_SET;            //然后拉高时钟，上升沿写入数据
		SCK_CLR;		    //再拉低时钟，形成脉冲，完成一个位的操作
		dat = dat >> 1; //将 data的各数据位右移1位，准备写入下一个数据位(高位)
	}
}
/********************************************************************/
//------------------------------------------------------------------
//函数名称：Read_Ds1302_Byte(void)
//函数功能：从DS1302读取一个字节
//输入参数：无
//返回值：读取的数据
//时序原理：在紧跟8位的控制指令字后的下一个SCLK时钟的下降沿时读出DS1302的数据，读出数据时从低位0位到高位7
//注意：DS1302中所存放的数据是BCD码，在读写时要注意转换
//例如：00011000，当把它视为二进制数时，其值为24；但作为2位BCD码时，其值为18。
//------------------------------------------------------------------

/* 由 DS1302 通信总线上读取一个字节 */
unsigned char Read_Ds1302_Byte(void)
{
	unsigned char i, dat=0;
	for (i=0;i<8;i++)
	{
		dat = dat >> 1;
		/*首先读取此时的 IO 引脚，并设置 date 中的对应位*/
		if (SDA_R) 	  //等价于if(SDA_R==1)    #define SDA_R SDA
		{
			dat |= 0x80; // xxxx xxxx | 1000 0000 = 1xxx xxxx/*写 1*/
		}
		else //可不写？
		{
			dat &= 0x7F; // xxxx xxxx & 0111 1111 = 0xxx xxxx/*写 0*/
		}
		SCK_SET;    //然后拉高时钟，为脉冲下降沿读出数据做准备
		SCK_CLR;    //再拉低时钟，时钟下降沿读出，完成一个位的动作
	}
	return dat;  //最后返回读到的字节数据
}

/********************************************************************/
/*用单次写操作向某一寄存器写入一个字节，addr-寄存器地址，data-待写入字节 */
void Ds1302_Single_Byte_Write(unsigned char addr, unsigned char dat)
{

	RST_CLR;			/*RST脚置低，实现DS1302的初始化*/
	SCK_CLR;			/*SCK脚置低，实现DS1302的初始化*/

	RST_SET;			//使能片选信号  /*启动DS1302总线,RST=1电平置高 */
	addr = addr & 0xFE;	  /*保证是写操作,写之前将最低位置零*/
	Write_Ds1302_Byte(addr); /*写入目标地址：addr*/
	Write_Ds1302_Byte(dat);	 /*写入数据：dat*/
	RST_CLR;				 //除能片选信号 /*停止DS1302总线*/
}

/********************************************************************/
//------------------------------------------------------------------
//函数名称：Ds1302_Single_Byte_Read(unsigned char addr)
//函数功能：从DS1302的指定寄存器读数据
//输入参数：addr 为读寄存器的地址
//返回值：data 读取的数据
//命令字：也即读寄存器的地址 最高位位7必须为1，位6如果为0表示存取日历数据，位5至位1表示操作单元的地址，位0为1表示读操作
//------------------------------------------------------------------

/*用单次读操作从某一寄存器读取一个字节，addr-寄存器地址，返回值-读到的字节 */
unsigned char Ds1302_Single_Byte_Read(unsigned char addr)
{
	unsigned char dat;
	RST_CLR;			/*RST脚置低，实现DS1302的初始化*/
	SCK_CLR;			/*SCK脚置低，实现DS1302的初始化*/

	RST_SET;	//使能片选信号 /*启动DS1302总线,RST=1电平置高 */
	addr = addr | 0x01;	  /* 保证是写操作,写之前将最低位置高*/
	Write_Ds1302_Byte(addr); /*写入目标地址：addr*/
	dat=Read_Ds1302_Byte(); /*从DS1302中读出一个字节的数据*/
	RST_CLR;	//除能片选信号 /*停止DS1302总线*/
    SDA_CLR;//已经修改 释放IO引脚
	return dat;
}

/**************************************************************************/
//自己写的程序
void DS1302_Init()
{
    Ds1302_Single_Byte_Write(0x8e,0x00); //关掉写保护

    Ds1302_Single_Byte_Write(ds1302_sec_addr,0x00);  //秒
    Ds1302_Single_Byte_Write(ds1302_min_addr,0x30);  //分 27
    Ds1302_Single_Byte_Write(ds1302_hr_addr,0x08);  //时  09 
    Ds1302_Single_Byte_Write(ds1302_date_addr,0x25);  //日 
    Ds1302_Single_Byte_Write(ds1302_month_addr,0x01);  //月
    Ds1302_Single_Byte_Write(ds1302_day_addr,0x06);  //星期
    Ds1302_Single_Byte_Write(ds1302_year_addr,0x18);  //年

    Ds1302_Single_Byte_Write(0x8e,0x80); //关掉写保护
}

