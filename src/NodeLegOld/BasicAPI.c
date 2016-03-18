#include "config.h"


void InitVar()
{
	myMEMSData[IDDF]=PCID;
        myMEMSData[WORKMODEDF] = myWorkMode;  
   
        myMEMSData[NODETYPEDF]= NODEGENE<<5;
        myMEMSData[NODETYPEDF]  +=GENEID; 
        
}



void HardwareInit()
{
	WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
        SetCPUSpeed(16);
	
       
        _EINT();
    
	I2C_Init();
	WirelessInit();
        ADCInit();
      
              
      
        InitVar();
      
        
       
        TimerInit();
        OSLEDInit();
        OSLEDControl(1);
          InitAllSensor();

}

///当收到反馈数据的处理方法
void ProcessCallBackData()
{
      
     for(u8 i=2;i<PACKETLENGTH-2; i+=2)
     {
        if( myReceiveBuff[i]==PCID)
        {
         myWorkMode=myReceiveBuff[i+1];  //获得当前工作模式
            myNodeFreshSpeed= (myWorkMode&0xE0)>>5;  //确定刷新速率
     isGyroEnable= (myWorkMode&0x10)>>4;  
     ChanelID= myWorkMode&0x7;  
     
     SetRFChannel(ChanelID);

     
     
     return;
        }
     }
      
  
}

