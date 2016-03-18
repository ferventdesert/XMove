#include "config.h"
u8 myMEMSData[PACKETLENGTH];
u8 sdddd[PACKETLENGTH];
u8 myReceiveBuff[PACKETLENGTH];
float AccX,AccY,AccZ,GyroX,GyroY,GyroZ,ComX,ComY,ComZ;
/*MEMS传感器数据存储定义如下
0:从机ID  1:工作模式 2:动作感应标记 3-9:专用数据  10-15  陀螺仪，16-21 磁场计，22-28:加速度计，28-31气压和温度*/

const unsigned char Rx_Address[3]={104,103,102};   //发送地址，暂时必须通过软件修改该值
const unsigned char Tx_Address[3]={100,101,102};     //本机地址，用于SPI无线模式



u8 isGyroExisted=0; 
u8 isAccExisted=1; 
u8 isComExisted=0; 
u8 isGyroEnable=1;
u8  myNodeFreshSpeed=7;  //刷新速度
u8 myWorkMode=0X40;
 
u8 ChanelID=0; 
const u16 GetCounterByNodeFreshSpeed[]={2000,1000,500,250,125,62,31,15};
u16 GetSendCounter()
{
  return GetCounterByNodeFreshSpeed[myNodeFreshSpeed];
}





