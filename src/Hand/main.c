#include "config.h"
#include "string.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void system_init()
{ 

    HardwareInit();
 InitVar();
    
        //中断配置
	//按键中断设定
	P2DIR&=0XC0;
	P2OUT|=0X3F;
	//P2IES|=0X3f;
        P2IES&=0XC0;   //1从高到低，0从低到高
	P2IE|=0X3F;
	//加速度传感器中断P1.0
	P1DIR&=0XFD;
	P1IES&=0XFD; 
	P2OUT|=0X03;
	P1IE|=0X03;
        //无线模块中断设定
	//P1DIR &= ~BIT4;
	//P1IE |= BIT4;    
	//P1IES |=BIT4; 
	
	
	
	
	Reset_DS1302();
	//Set_DS1302(wdata);
	I2C_Init();
	WirelessInit();
	LCD_Initial();
 
	P4DIR|=BIT7;
	OSLightControl(0);

       
    
      
#if DEBUG_EN==0
	
	TACTL|=MC1;
        
#endif
	
}
u8 counter=0;
u8 fuck1,fuck2;
void OS_funcn()            //赋值函数，可直接调用
{
	OS_func=myTaskPCB[OS_index_data].function;
	OS_func(); 
}
void  main(void)
{
	
	
        system_init();
 
        
        SystemOpenGUI();
	BoxGUI("X-MOVE动作感应系统");
       
	
	//PassWordCheck();   

        _EINT();
	
   
           OS_funcn() ;
	while(1)
	{
		if(OS_index_ago==OS_index_data)
		{      
			OS_func();
#if  SIM_OR_ITAG==1                  
			LPM3;
#endif 
			
		}
		else
		{   
			
			OS_index_ago=OS_index_data;
			
			OS_func_state=0;
			OS_funcn();
			
#if  SIM_OR_ITAG==1                  
			LPM3;
#endif 
		}   
	}
}
#pragma vector=USART1RX_VECTOR
__interrupt void usart1_rx (void)
{  
  
}
#pragma vector=USART0RX_VECTOR
__interrupt void usart0_rx (void)
{

}


/*******************************************
函数名称：PORT1_ISR 
功    能：p1端口的中断服务函数
参    数：无
返回值  ：无
********************************************/
#pragma vector=PORT1_VECTOR
__interrupt void  PORT1_ISR(void)
{
	switch(P1IFG)
	{
	case 0x10:  //来自无线模块的中断
               
               
		break;
	case 0x02:
		break;
		
		
	}
        P1IFG = 0;
}
/*******************************************
函数名称：PORT2_ISR 
功    能：p2端口的中断服务函数
参    数：无
返回值  ：无
********************************************/
#pragma vector=PORT2_VECTOR
__interrupt void  PORT2_ISR(void)
{
   
  
    if( GetCurrentKey(&InputPortState,&key_data,0))
    {
           OSFuncKeyInputProcess();
            LPM3_EXIT;
            back_light=back_light_set;
	BackLightSet(OSBackLight);
    
        OSLightControl(0);
    }
        P2IES=InputPortState;          
	
	P2IFG = 0;
	
	
}



