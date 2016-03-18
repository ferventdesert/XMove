#include "config.h"
void OSLEDControl(u8 Mode)
{
  //0：变暗，1 变亮  2，取反
  switch(Mode)
  {
  case 1:
    P2OUT&=~BIT0;
    break;
  case 0:
    P2OUT|=BIT0;
    break;
  case 2:
     P2OUT^=BIT0;
    break;
  }
}
void OSLEDInit()
{
  P2DIR|=BIT0;
}

void ADCInit()
{
   
   ADC10CTL0 = ADC10SHT_2 + ADC10ON + ADC10IE; // ADC10ON, interrupt enabled
   ADC10AE0 |= 0x02;                         // P2.0 ADC option select
   ADC10CTL1 |=INCH_1;
   

}
void GetVCCValue()
{
    ADC10CTL0 |= ENC + ADC10SC;             // Sampling and conversion start
    
  
    
}

 //ADC10 interrupt service routine
#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR(void)
{
    myMEMSData[VCCFLAG]=(ADC10MEM&0x03FF)>>4;

 
}
