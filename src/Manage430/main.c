
#include "config.h"






u8 SendingTime=0;
void  main(void)
{

  
	HardwareInit();
	SetRFChannel(0,0);  //设定基础频段
        
	RxWayConfig(0);
        delay_ms(1000);
	while(1) 
	{  

		ProcessReceivedData();
                
                if(TimerCounter==MAXCounter) 
                {
                    SendSensorData(myMEMSData);
                 
			TimerCounter=0;  //归零
                }

               
                if(UartReceiveFlag==1)  //处理串口输入的数据
                {

                    if(myReceiveBuff[0]!=PCID)
                      continue;
                    if(myReceiveBuff[1]==1)  //配置节点状态
                    {
                       while(SendingTime<100)
                       {
                          W_PutStringPtr(0,myReceiveBuff);
                          SendingTime++;
                       }
                       SendingTime=0;

                    }
                    
                    else if(myReceiveBuff[1]==2) //配置信道状态
                      
                    {
                      
                    }
                    else
                    {
                      
                    }
                }
           
                UartReceiveFlag=0;
	}
        

}
