/********************************************************************
created:	2011/12/28
created:	28:12:2011   18:55
filename: 	C:\Users\zhaoyiming\Desktop\常用软件\temp.cpp
file path:	C:\Users\zhaoyiming\Desktop\常用软件
file base:	temp
file ext:	cpp
author:		赵一鸣


purpose:	时间相关的硬件驱动
*********************************************************************/
#include "config.h"


u8 CPUFrequene; 

/***************************延时函数*******************************/
/*******************************************
函数名称：delay_Nus
功    能：延时N个us的时间
参    数：n--延时长度
返回值  ：无
********************************************/
void delay_us(unsigned int n)
{
  

  while(n>0)
  {

     
      n--;
  }
} 
/*******************************************
函数名称：delay_1ms
功    能：延时约1ms的时间
参    数：无
返回值  ：无
********************************************/
void delay_1ms(void)
{
	unsigned int i;
	for(i = 1000;i > 0;i--)	; delay_us(1);
}  
/*******************************************
函数名称：delay_Nms
功    能：延时N个ms的时间
参    数：无
返回值  ：无
********************************************/  
void delay_ms(unsigned int n)
{
	unsigned int i = 0;

	for(i = n;i > 0;i--)
		delay_1ms();
}
/*******************************************
函数名称：SetCPUSpeed
功    能：设置CPU速度
参    数：分为16,8,1, （单位MHZ）
返回值  ：无
********************************************/  
void SetCPUSpeed(u8 FreNum)
{
  DCOCTL = DCO0 + DCO1 + DCO2;              // Max DCO
	BCSCTL1 = RSEL0 + RSEL1 + RSEL2;          // XT2on, max RSEL
	BCSCTL2 |= SELS;                          // SMCLK = XT2     
  

}
void TimerInit()
{
  
  CCTL0 = CCIE;                             // CCR0 interrupt enabled
  CCR0 = 6400;
  TACTL = TASSEL_2 + MC_2;                  // SMCLK, contmode
}
	
//定时器计数器
u16 TimerCounter=0;


// Timer A0 interrupt service routine
#pragma vector=TIMERA0_VECTOR
__interrupt void Timer_A (void)
{
 
  TimerCounter++;                    // Toggle P1.0
  LPM0_EXIT;
}

