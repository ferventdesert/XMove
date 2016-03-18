#include "config.h"
void OSLEDControl(u8 Mode)
{
  //0：变暗，1 变亮  2，取反
  switch(Mode)
  {
  case 0:
    P3OUT&=~BIT7;
    break;
  case 1:
    P3OUT|=BIT7;
    break;
  case 2:
     P3OUT^=BIT7;
    break;
  }
}
void OSLEDInit()
{
  P3DIR|=BIT7;
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
/*
 ADC10 interrupt service routine
#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR(void)
{
   // myMEMSData[VCCFLAG]=(ADC10MEM&0x0300)>>8;
   // myMEMSData[VCCFLAG+1]=ADC10MEM&0XFF ;
 
}
*/