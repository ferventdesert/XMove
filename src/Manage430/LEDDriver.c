#include "config.h"
void OSLEDControl(u8 Mode)
{
  //0：变暗，1 变亮  2，取反
  switch(Mode)
  {
  case 0:
    P2OUT&=~BIT0;
    break;
  case 1:
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

