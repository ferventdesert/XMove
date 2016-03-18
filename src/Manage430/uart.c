

#include "config.h"
u8 Count=0;


void UartInit()
{
        P3SEL |= 0xC0;                            // P3.4,5 = USART0 TXD/RXD
	ME2 |= UTXE1 + URXE1;                     // Enable USART0 TXD/RXD
	UCTL1 |= CHAR;                            // 8-bit character
	UTCTL1 |= SSEL1;                          // UCLK = SMCLK
	UBR01 = 0x45;                             // 32k/2400 - 13.65
	UBR11 = 0x00;                             //
	UMCTL1 = 0x4A;                           // Modulation
	UCTL1 &= ~SWRST;                          // Initialize USART state machine
	IE2 |= URXIE1;                            // Enable USART0 RX interrupt     
}
/*******************************************
函数名称：Send1Char
功    能：向PC机发送一个字符
参    数：sendchar--要发送的字符
返回值  ：无
********************************************/
void Send1Char(uchar sendchar)
{
	while (!(IFG2 & UTXIFG1));    //等待发送寄存器为空         
	TXBUF1 = sendchar; 
	
}
/*******************************************
函数名称：PutSting
功    能：向PC机发送字符串
参    数：ptr--指向发送字符串的指针
返回值  ：无
********************************************/
void PutString_C(unsigned char *ptr)     
{
	while(*ptr != '\0')
	{
		Send1Char(*ptr++);                     // 发送数据
	}
	Send1Char(0x0D);
	Send1Char(0x0A); //发送换行指令
}
void PutString(unsigned char *ptr)
{
	while(*ptr != '\0')
	{
		Send1Char(*ptr++);                     // 发送数据
	}
}
void  SendSensorData(unsigned char *ptr)
{
	       u8 i=0;
		Send1Char('#');
		
		while(i<PACKETLENGTH)
	        {
		Send1Char(*ptr++);
                i++;// 发送数据
	        }
		Send1Char('$'); //发送换行指令
}

 


#pragma vector=USART1RX_VECTOR
__interrupt void usart1_rx (void)
{  
  
  if(RXBUF0=='#'&&Uart_ExMood==0)
	{
		Uart_ExMood=1;
                Uart_RxFlag=0;
	}
	
	else if(RXBUF0!='$'&&Uart_ExMood==1)
	{
		if(Uart_RxFlag<UARTPACKETLENGTH)
			myReceiveBuff[Uart_RxFlag++]=RXBUF0;
	}
	else if(RXBUF0=='$'&&Uart_ExMood==1)
	{
          	Uart_ExMood=0;
                UartReceiveFlag=1;
		LPM0_EXIT;
	
	}
  
  
  
  
  
   
}