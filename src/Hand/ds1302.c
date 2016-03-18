
#include "config.h"
/*
config.h
ELPOS2.0的实时时钟驱动函数，器件:DS1302
Copyright (c) 2010，赵一鸣
buptzym@bupt.edu.cn
All rights reserved.
本程序仅供学习参考，不提供任何可靠性方面的担保；请勿用于商业目的
*/


/***************DS1302宏定义*********************/
#define DS_RST  BIT7        //DS_RST = P2.7 
#define DS_SCL  BIT3        //DS_SCL = P3.3 
#define DS_SDA  BIT6        //DS_SDA = P2.6
#define DS_RST_IN P2DIR &= ~DS_RST
#define DS_RST_OUT P2DIR |= DS_RST
#define DS_RST0 P2OUT &= ~DS_RST
#define DS_RST1 P2OUT |= DS_RST
#define DS_SCL_IN P3DIR &= ~DS_SCL
#define DS_SCL_OUT P3DIR |= DS_SCL
#define DS_SCL0 P3OUT &= ~DS_SCL
#define DS_SCL1 P3OUT |= DS_SCL
#define DS_SDA_IN P2DIR &= ~DS_SDA
#define DS_SDA_OUT P2DIR |= DS_SDA
#define DS_SDA0 P2OUT &= ~DS_SDA
#define DS_SDA1 P2OUT |= DS_SDA
#define DS_SDA_BIT P2IN & DS_SDA
/************系统核心定义******************/



/*******************************************
函数名称：Reset_DS1302
功    能：对DS1302进行复位操作
参    数：无
返回值  ：无
********************************************/
void Reset_DS1302(void)
{
	DS_RST_OUT;  //RST对应的IO设置为输出状态
	DS_SCL_OUT;  //SCLK对应的IO设置为输出状态
	DS_SCL0;     //SCLK=0
	DS_RST0;     //RST=0
	delay_us(100);
	DS_SCL1;    //SCLK=1
}
/*******************************************
函数名称：Write1Byte
功    能：对DS1302写入1个字节的数据
参    数：wdata--写入的数据
返回值  ：无
********************************************/
void Write1Byte(uchar wdata) 
{ 
	uchar i;

	DS_SDA_OUT;     //SDA对应的IO设置为输出状态
	DS_RST1;        //REST=1;

	for(i = 8; i > 0; i--) 
	{
		if(wdata&0x01)  DS_SDA1;
		else            DS_SDA0;
		DS_SCL0;
		delay_us(10); 
		DS_SCL1;
		delay_us(10); 
		wdata >>= 1; 
	} 
}
/*******************************************
函数名称：Read1Byte
功    能：从DS1302读出1个字节的数据
参    数：无
返回值  ：读出的一个字节数据
********************************************/
uchar Read1Byte(void) 
{ 
	uchar i;
	uchar rdata = 0X00;

	DS_SDA_IN;  //SDA对应的IO设置为输入状态
	DS_RST1;    //REST=1;

	for(i = 8; i > 0; i--)
	{
		DS_SCL1;
		delay_us(10);
		DS_SCL0;
		delay_us(10);
		rdata >>= 1;
		if(DS_SDA_BIT)  rdata |= 0x80;
	} 

	return(rdata); 
}
/*******************************************
函数名称：W_Data
功    能：向某个寄存器写入一个字节数据
参    数：addr--寄存器地址
wdata--写入的数据
返回值  ：无
********************************************/
void W_Data(uchar addr, uchar wdata)
{
	DS_RST0; 
	DS_SCL0;   
	_NOP();
	DS_RST1;
	Write1Byte(addr);   //写入地址
	Write1Byte(wdata);  //写入数据
	DS_SCL1;
	DS_RST0;
} 
/*******************************************
函数名称：R_Data
功    能：从某个寄存器读出一个字节数据
参    数：addr--寄存器地址
返回值  ：读出的数据
********************************************/
uchar R_Data(uchar addr)
{
	uchar rdata;

	DS_RST0; 
	DS_SCL0; 
	_NOP();
	DS_RST1;
	Write1Byte(addr);    //写入地址
	rdata = Read1Byte();  //读出数据 
	DS_SCL1;
	DS_RST0;

	return(rdata);
}

/*******************************************
函数名称：Set_DS1302
功    能：设置DS1302内部的时间
参    数：ptr--指向存放数据地址的指针
返回值  ：无
说明    ：写入数据的格式：
秒 分 时 日 月 星期 年  【共7个字节】
********************************************/
void Set_DS1302(uchar *ptr) 
{
	uchar i;
	uchar addr = 0x80; 

	W_Data(0x8e,0x00);    //允许写入

	for(i = 7;i > 0;i--)
	{ 
		W_Data(addr,*ptr++); 
		addr += 2;
	}
	W_Data(0x8e,0x80);      //禁止
}
/******************************************************************** 
*
* 名称: Get_DS1302
* 说明: 
* 功能: 读取DS1302当前时间
* 调用: R_Data(uchar addr) 
* 输入: ucCurtime: 保存当前时间地址。当前时间格式为: 秒 分 时 日 月 星期 年 
* 7Byte (BCD码) 1B 1B 1B 1B 1B 1B 1B
* 返回值: 无
***********************************************************************/
/*******************************************
函数名称：Get_DS1302
功    能：读取DS1302内部的时间
参    数：ptr--指向数据存放地址的指针
返回值  ：无
说明    ：读出数据的格式：
秒 分 时 日 月 星期 年  【共7个字节】
********************************************/
void Get_DS1302(uchar *ptr) 
{
	uchar i;
	uchar addr = 0x81;

	for(i = 0;i < 7;i++)
	{
		ptr[i] = R_Data(addr);
		addr += 2;
	}
}
