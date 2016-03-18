/*
config.h
ELPOS2.0的核心控制文件，涉及头文件的引用和预编译头
Copyright (c) 2010，赵一鸣
buptzym@bupt.edu.cn
All rights reserved.
本程序仅供学习参考，不提供任何可靠性方面的担保；请勿用于商业目的




*/
//基本核心宏定义
#define PCID 1
#define HIDENABLE  0
#define PRESSUREENABLE 0
#define PACKETLENGTH 24
#define NODEGENE 3   //XMOVE的代数
#define GENEID 0   //代数ID




#define SIM_JTAG_CHANGE 1  //硬件模式置1，软件仿真置0
#define INPUT_CONTROL_EN  0



#define DEBUG_EN  0


#define  GAME_CONTROL_EN 1



#include <msp430x14x.h>

#include "mydefine.h"
#include "Timer.h"
#include "Nrf24l01.h"
#include "LCDDriver.h"

#include "GUIPack.h"
#include "MemsDriver.h"
#include "ds1302.h"
#include "OS_func.h"
#include "myfunc_game.h"
#include "uart.h"
#include "myfunc_input.h"


#include "BasicAPI.h"

#define UART_SPI_MOOD 1

#define CHSORENG  0  // 0中文，1英文

#define KEY_WirelessReply  1

#include "math.h"
#include "stdlib.h"
#include "string.h"
#include <math.h>
#include <stdio.h>




