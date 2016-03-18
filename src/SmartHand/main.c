
#include "config.h"



void main(void)
{

    HardwareInit();
   
 
	//StartAllSensor();
    
 

	while(1)
	{



          
            

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
			RxWayConfig() ;    //   在十分之一时隙内建立接收通信
		}
		if(TimerCounter%OneSec==50)  //
		{
                  OSLEDControl(2);
                  
                  
			SetStandbyMode();
		}



		if(TimerCounter%counter==5)  //完成测量和发送周期
		{
			OSLEDControl(2);

			GetAllSensorData();
			//CalAllSensorData();
			W_PutString();
			CloseAllSensor();

		}
		LPM0;
	}
}

