#include "config.h"
void OSLEDControl(u8 Mode)
{
  //0：变暗，1 变亮  2，取反
  switch(Mode)
  {
  case 0:
    P4OUT&=~BIT7;
    break;
  case 1:
    P4OUT|=BIT7;
    break;
  case 2:
     P4OUT^=BIT7;
    break;
  }
}
void OSLEDInit()
{
  P4DIR|=BIT7;
}

void ADCInit()
{
 //  ADC10CTL0 = ADC10SHT_2 + ADC10ON + ADC10IE; // ADC10ON, interrupt enabled
  // ADC10AE0 |= 0x01;                         // P2.0 ADC option select
   

}
void GetVCCValue()
{
    //ADC10CTL0 |= ENC + ADC10SC;             // Sampling and conversion start
    
  
    
}

u8 GetCurrentKey(u8 *PortStatus1,u8* KeyValue)  //第一个参数为上次端口状态值，第二个为返回的键值
{
	u8 PortStatus2,ReturnValue=0;
	u8 KeyFlag;

	 
        PortStatus2=P2IN;
	for (u8 i=0;i<6;i++)
	{   KeyFlag=1<<i;
		if ((*PortStatus1&KeyFlag)>(PortStatus2&KeyFlag))  // 按下
		{
			*KeyValue=2*i+1;
                        myMEMSData[KEYDF]=*KeyValue;
			W_PutString();
			ReturnValue=1;
		} 
		else if((*PortStatus1&KeyFlag)<(PortStatus2&KeyFlag))  //弹起
		{
		                *KeyValue=2*i+2;
                                 myMEMSData[KEYDF]=*KeyValue;
			 	 W_PutString();
				ReturnValue=1;
		}
		
	}
        *PortStatus1=PortStatus2;
         myMEMSData[KEYDF]=0;
         _EINT();
     
	
return ReturnValue;
}

void KeyboardInit()
{
  P2DIR=0;
}


/*
 ADC10 interrupt service routine
#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR(void)
{
   // myMEMSData[VCCFLAG]=(ADC10MEM&0x0300)>>8;
   // myMEMSData[VCCFLAG+1]=ADC10MEM&0XFF ;
 
}
*/