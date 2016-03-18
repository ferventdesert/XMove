//第二套键盘扫描码
#include "config.h"





u8 myMEMSData[PACKETLENGTH];
u8 myReceiveBuff[UARTPACKETLENGTH];
u8 UartReceiveFlag;

u8 Uart_ExMood=0;  //串口状态机
u8 Uart_RxFlag;
const unsigned char Tx_Address[3]={104,103,102};   //发送地址，暂时必须通过软件修改该值
const unsigned char Rx_Address[3]={100,101,102};     //本机地址，用于SPI无线模式