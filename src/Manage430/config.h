
 
 
#include <msp430x14x.h>
#include "mydefine.h"
#include "Timer.h"
#include "uart.h"
#include "nRF24L01.h"
#include "LEDDriver.h"
#include "BasicAPI.h"
 

//基本核心宏定义
#define PCID 1
#define HIDENABLE  0
#define PRESSUREENABLE 0
#define PACKETLENGTH 24
#define UARTPACKETLENGTH 24

#define RFMODULENUM 1
 



#define NODEGENE 3   //XMOVE的代数
#define GENEID 2   //代数ID



//相关调试宏定义
 

#define SIM_JTAG_CHANGE 1  //硬件模式置1，软件仿真置0
#define DEBUG_EN  0


