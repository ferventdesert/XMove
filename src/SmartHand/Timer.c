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
注意：延时不一定准确，仅作为一定延时使用
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
	unsigned int i=40*CPUFrequene;;
	while(i>0)
	{
		delay_us(1);
		i--;
	}
}  
/*******************************************
函数名称：delay_Nms
功    能：硬件延时2.5个ms的时间
参    数：无
返回值  ：无
********************************************/  
void HardDelay2Ms()
{
	TA0CCR0 = 2000*CPUFrequene;
	__bis_SR_register(LPM0_bits + GIE);       // Enter LPM0 w/ interrupt

}






/*******************************************
函数名称：delay_Nms
功    能：延时N个ms的时间
参    数：无
返回值  ：无
********************************************/  
void delay_ms(unsigned int n)
{

	if(n<3)  //延时小于2ms,采用软件定时
	{
		unsigned int i = 0;

		for(i = n;i > 0;i--)
			delay_1ms();
	}
	else
	{
		while(n>3)
		{
			HardDelay2Ms();
			n-=2;
		}
	}


}
/*******************************************
函数名称：SetCPUSpeed
功    能：设置CPU速度
参    数：分为16,8,1, （单位MHZ）
返回值  ：无
********************************************/  
void SetCPUSpeed(u8 FreNum)
{
	switch(FreNum)
	{
	case 8:
		if (CALBC1_8MHZ ==0xFF || CALDCO_8MHZ == 0xFF)                                     
		{  
			while(1);                               // If calibration constants erased                             // do not load, trap CPU!!
		}   
		BCSCTL1 = CALBC1_8MHZ;                    // Set DCO to 8MHz
		DCOCTL = CALDCO_8MHZ;
		CPUFrequene=FreNum;
		break;
	case 16:
		if (CALBC1_16MHZ ==0xFF || CALDCO_16MHZ == 0xFF)                                     
		{  
			while(1);                               // If calibration constants erased                             // do not load, trap CPU!!
		}   
		BCSCTL1 = CALBC1_16MHZ;                    // Set DCO to 8MHz
		DCOCTL = CALDCO_16MHZ;
		CPUFrequene=FreNum;
		break;
	case 1:
		if (CALBC1_1MHZ ==0xFF || CALDCO_1MHZ == 0xFF)                                     
		{  
			while(1);                               // If calibration constants erased                             // do not load, trap CPU!!
		}   
		BCSCTL1 = CALBC1_1MHZ;                    // Set DCO to 8MHz
		DCOCTL = CALDCO_1MHZ;
		CPUFrequene=FreNum;
		break;
	}
}
void TimerInit()
{
	TA0CTL = TASSEL_2 + MC_2;                  // SMCLK, contmode
	
	TA0CCTL0 = CCIE;                           // TA0CCR0 interrupt enabled
	TA0CCR0 = 2000*CPUFrequene;
}
//定时器计数器
u16 TimerCounter=0;

#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A0 (void)
{

	LPM0_EXIT;

	
	TimerCounter++;


}

