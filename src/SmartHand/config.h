/*
config.h
ELPOS2.0的核心控制文件，涉及头文件的引用和预编译头
Copyright (c) 2010，赵一鸣
buptzym@bupt.edu.cn
All rights reserved.
本程序仅供学习参考，不提供任何可靠性方面的担保；请勿用于商业目的
*/



//基本核心宏定义
#define PCID 2
#define HIDENABLE  0
#define PRESSUREENABLE 0
#define PACKETLENGTH 24

 
//相关调试宏定义
 

#define SIM_JTAG_CHANGE 1  //硬件模式置1，软件仿真置0
#define DEBUG_EN  0

#include "msp430x21x2.h"

#include "mydefine.h"
#include "Timer.h"
#include "Nrf24l01.h"
#include "MemsDriver.h"
#include "math.h"
#include "LEDLight.h"
#include <math.h>

#include "BasicAPI.h"
