#include "config.h"


void InitVar()
{
	myMEMSData[IDDF]=PCID;
        myMEMSData[NODETYPEDF]= NODEGENE<<5;
        myMEMSData[NODETYPEDF]  +=GENEID; 
}





void HardwareInit()
{
	WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
	OSLEDInit();
          InitVar();
        OSLEDControl(1);
	SetCPUSpeed(16);
        
       TimerInit();
        UartInit();
        _EINT();

	 
	WirelessInit();
         
      
         
         
     
      
      
       
       
        
       
}

///当收到反馈数据的处理方法
void ProcessCallBackData()
{
      
 

}

