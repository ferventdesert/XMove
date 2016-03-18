
#include "config.h"



void main(void)
{

  u8 LastPort,CurrentKey;
   
     HardwareInit();
   
 
	StartAllSensor();
    
       SetRFChannel(0); 
 
	while(1)
	{
          
            if(	GetCurrentKey(&LastPort,&CurrentKey) )
                  {
                  }
                  else
                  {
                         OSLEDControl(2);
			GetAllSensorData();
			//CalAllSensorData();
			W_PutString();
			
                  }
            
            
             delay_ms(50);
/*
		if(TimerCounter==MAXCounter)  
			TimerCounter=0;  //归零



		u8 counter=GetSendCounter();
		if(TimerCounter%counter==0)  //达到测量周期
		{

			StartAllSensor();
		}
		if(TimerCounter%OneSec==0)  //达到测量周期，实现测量电压

		{
			GetVCCValue();     //测定电压
                      //  OSLEDControl(1);
                         RxWayConfig() ;    //   在十分之一时隙内建立接收通信
			
		}
		if(TimerCounter%OneSec==100)  //
		{
                         // OSLEDControl(0);
		        SetStandbyMode();
		}
                
		if(TimerCounter%counter==5)  //完成测量和发送周期
		{
		  if(	GetCurrentKey(&LastPort,&CurrentKey) )
                  {
                  }
                  else
                  {
                         OSLEDControl(2);
			GetAllSensorData();
			CalAllSensorData();
			W_PutString();
			CloseAllSensor();
                  }
               

		}
		LPM0;*/
	}
}


