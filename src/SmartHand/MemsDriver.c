#include "config.h"
/*
MemsDriver.c
ELPOS2.0的MEMS传感器驱动函数和上层运用，器件ADXL345,ITG3200,BMP085和HMC5883
Copyright (c) 2010，赵一鸣
buptzym@bupt.edu.cn
All rights reserved.
本程序仅供学习参考，不提供任何可靠性方面的担保；请勿用于商业目的
*/



#define L3G4200D 0
#define  HMC5883L 1
#define  ADXL345 2


#define L3G4200D_I2C_ADDR   0X68
#define  HMC5883L_I2C_ADDR  0X1E
#define  ADXL345_I2C_ADDR  0X53


//定ADXL345内部的寄存器地址
#define ADXL345_BW_RATE   0X2C
#define ADXL345_POWER_CTL  0X2D
#define ADXL345_DATA_FORMAT 0X31
#define ADXL345_THRESH_TAP  0X1D
#define ADXL345_DUR 0X21
#define ADXL345_Latent 0x22
#define ADXL345_Window 0x23
#define ADXL345_THRESH_ACT  0X24
#define ADXL345_THRESH_INACT  0X25
#define ADXL345_TIME_INACT  0X26
#define ADXL345_INACT_CTL  0X27
#define ADXL345_THRESH_FF  0X28
#define ADXL345_TIME_FF  0X29
#define ADXL345_TAP_AXES 0X2A
#define ADXL345_ACT_TAP_STATUS 0X2B
#define ADXL345_INT_ENABLE 0X2E
#define ADXL345_INT_MAP 0X2F
#define ADXL345_INT_SOURCE 0X30


//定义HMC5883L内部寄存器地址（子地址）
#define HMC5883L_CfgA  0X00
#define HMC5883L_CfgB   0X01
#define HMC5883L_Mode 0X02
#define HMC5883L_XMSB  0X03
#define HMC5883L_XLSB  0X04
#define HMC5883L_YMSB  0X05
#define HMC5883L_YLSB  0X06
#define HMC5883L_ZMSB   0X07
#define HMC5883L_ZLSB    0X08
#define HMC5883L_StaReg 0x09


struct str_TWI         					//TWI数据结构
{
	volatile u8 STATUS;    	   //TWI_操作状态
	u8  R_W;
	u8  SLA;      					//从设备的器件地址
	u16 ADDR;      					//从设备的数据地址
	u8  DUB_OR_SIN;               //从设备数据地址的字节数
	u8 *pBUF;      					//数据缓冲区指针
	u8 DATALEN;     				//数据长度
	u8 STATE;      					//TWI读写操作步骤
	u8 FAILCNT;     					//失败重试次数
}strTWI;
/**********************************************************
函数名称：I2C读写多字节程序												
函数出口：无																
函数入口：R_W  --0写操作。1读操作											
sla  --器件地址																												
addr --器件子地址	
dub_sin --器件子地址字节数，0为单字节，1为双字节
*ptr --读写数据缓冲区												
len  -- 读写数据长度		
备注：I2C器件有些子器件的子地址是两字节，有的是一个字节，发送
子器件子地址时需注意。
***********************************************************/
u8 TWI_RW(u8 R_W,u8 sla,u16 addr,u8 dub_sin,u8 *ptr,u8 len)
{
	u8 i;

	//i=(addr>>8)<<1;
	//i&=0x06;         //考虑了24C04/08的EEPROM地址高位放在SLA里面
	strTWI.R_W        = R_W;
	strTWI.SLA        = sla;//+i;
	strTWI.ADDR       = addr;
	strTWI.DUB_OR_SIN = dub_sin;
	strTWI.pBUF       = ptr;
	strTWI.DATALEN    = len;
	strTWI.STATE      = 0;
	strTWI.FAILCNT    = 0;

	UCB0I2CSA      = strTWI.SLA;
	if(0 == strTWI.R_W)                           //写操作
	{
		while(UCB0CTL1 & UCTXSTP);                //总线是否空闲
		UCB0CTL1  |= UCTXSTT + UCTR;              //启动I2C，发送

		if(1 == strTWI.DUB_OR_SIN)             //子器件地址是否为双字节
		{
			UCB0TXBUF  = (u8)(strTWI.ADDR>>8);  //发送器件子地址高8位
			while(!(IFG2 & UCB0TXIFG))             //判断是否发送完毕 
			{
				if((UCB0STAT & UCNACKIFG) == 1)    //从设备无应答则返回
					return 1;
			}
			UCB0TXBUF  = (u8)strTWI.ADDR;       //发送器件子地址低8位 
			while(!(IFG2 & UCB0TXIFG))
			{
				if((UCB0STAT & UCNACKIFG) == 1)     //从设备无应答则返回
					return 1;
			} 
		}
		else   
		{
			UCB0TXBUF  = (u8)strTWI.ADDR;       //单字节发送器件子地址 
			 while(!(IFG2 & UCB0TXIFG))   
			{
				if((UCB0STAT & UCNACKIFG) == 1)      //从设备无应答则返回
					return 1;
			} 
		}

		for(i=0; i<strTWI.DATALEN; i++)            //发送数据
		{
			UCB0TXBUF = *strTWI.pBUF++;
			while((IFG2 & UCB0TXIFG) == 0)
			{
				if((UCB0STAT & UCNACKIFG) == 1)     //从设备无应答则返回
					return 1;
			}
		}
		UCB0CTL1 |= UCTXSTP;                       //发送停止位
		while(UCB0CTL1 & UCTXSTP);                 //总线是否空闲
	}
	else if(1 == strTWI.R_W)                       //读操作
	{
		while(UCB0CTL1 & UCTXSTP);                 //总线是否空闲
		UCB0CTL1  |= UCTXSTT + UCTR;               //启动I2C，发送 

		if(1 == strTWI.DUB_OR_SIN)              //子器件地址是否为双字节
		{
			UCB0TXBUF  = (u8)(strTWI.ADDR>>8); //发送器件子地址高8位
			while((IFG2 & UCB0TXIFG) == 0)        //判断是否发送完毕 
			{
				if((UCB0STAT & UCNACKIFG) == 1)  //从设备无应答则返回
					return 1;
			}
			UCB0TXBUF  = (u8)strTWI.ADDR;      //发送器件子地址低8位 
			while((IFG2 & UCB0TXIFG) == 0)
			{
				if((UCB0STAT & UCNACKIFG) == 1)  //从设备无应答则返回
					return 1;
			}
		}
		else
		{
			UCB0TXBUF  = (u8)strTWI.ADDR;      //单字节发送器件子地址
			while((IFG2 & UCB0TXIFG) == 0)
			{
				if((UCB0STAT & UCNACKIFG) == 1)  //从设备无应答则返回
					return 1;
			}
		}
		UCB0CTL1  &= ~UCTR;                        //确定为接收 
		//while (UCB0CTL1 & UCTXSTP);               //判断总线是否被释放 
		UCB0CTL1  |= UCTXSTT;                      //重新发送起始位 
		//while((UCB0CTL1 & UCTXSTT) == 1);         //判断起始位是否发送成功 

	}
	delay_ms(4);
	return 0;
}
/*********************************************************
函数名称：I2C_Init()
函数功能：I2C初始化
入口参数：无
出口参数：无
备注：
**********************************************************/
void I2C_Init(void)
{

	P3SEL |= BIT1 + BIT2;                     //P3.2(SCK),P3.1(SDA)
	UCB0CTL1 |= UCSWRST;                      //Ready for configurating I2C register  
	UCB0CTL0 |= UCMST+UCMODE_3 +UCSYNC;    //I2C、 主机、同步模式
	//================= Starting Of I2C FUNCTION CONFIGURATION========================//

	UCB0CTL1 = UCSSEL_2 + UCSWRST;            //时钟源ACLK
	UCB0BR0  =40;                          //100KHz，16MHz
	UCB0BR1  = 0;
	UCB0CTL1 &= ~UCSWRST;
	IE2      |= UCB0RXIE;                     //使能接收中断
	//================= End Of I2C FUNCTION CONFIGURATION========================// 

}


/*********************************************************
函数名称：USCIAB0_ISR()
函数功能：I2C接收中断
入口参数：无
出口参数：无
备注：
**********************************************************/
#pragma vector=USCIAB0TX_VECTOR 
__interrupt void USCIAB0_ISR(void) 
{ 
	if(IFG2  & UCB0RXIFG)                       // 接收中断 
	{ 
		//Sendbyte(UCB0RXBUF);
		if(strTWI.DATALEN > 1)
		{
			*strTWI.pBUF++ = UCB0RXBUF;
		}
		else if(1 == strTWI.DATALEN)
		{

			*strTWI.pBUF++ = UCB0RXBUF;
			UCB0CTL1 |= UCTXSTP + UCTXNACK;        // 发送停止位和NACK位

		}
		--strTWI.DATALEN;                         // 接收数据长度自减          
	} 
}


//***************应用层接口函数***********************************/
/*
函数：MEMS_WriteReg()
功能：向传感器的某个内部寄存器写入数据
参数：
ICID：传感器器件ID
dat：要写入的数据
RegAddr：器件内部寄存器地址
返回：
0：正常
1：访问传感器时出现异常
*/
unsigned char MEMS_WriteReg(unsigned char ICID,unsigned char RegAddr, unsigned char dat)
{
	unsigned char  b;
	switch(ICID)
	{
	case L3G4200D:
		b=   TWI_RW(0,L3G4200D_I2C_ADDR,RegAddr,0,&dat,1);		
		break;
	case HMC5883L:
		b=   TWI_RW(0,HMC5883L_I2C_ADDR,RegAddr,0,&dat,1);	
		break;

	case ADXL345:
		b=   TWI_RW(0,ADXL345_I2C_ADDR,RegAddr,0,&dat,1);	
		break;

	}
	return b;
}

/*
函数：MEMS_ReadReg()
功能：向传感器的某个内部寄存器读出数据
参数：
ICID：传感器器件ID
dat：要写入的数据
RegAddr：器件内部寄存器地址
返回：
0：正常
1：访问传感器时出现异常
*/
unsigned char  MEMS_ReadReg(unsigned char ICID,unsigned char RegAddr, unsigned char *dat)
{
	unsigned char b;
	switch(ICID)
	{
	case L3G4200D:
		b=   TWI_RW(1,L3G4200D_I2C_ADDR,RegAddr,0,dat,1);	
		break;
	case HMC5883L:
		b=   TWI_RW(1,HMC5883L_I2C_ADDR,RegAddr,0,dat,1);	
		break;

	case ADXL345:
		b=   TWI_RW(1,ADXL345_I2C_ADDR,RegAddr,0,dat,1);	
		break;

	}
	return b;
}




//***********************************接口转换函数**************/



//====================================================
//陀螺仪驱动函数 （L3G4200D）
//====================================================

/*
函数：u8 L3G4200DReadData()
功能：读取陀螺仪的数据
参数：无
返回：1  
注意：存储位置在myMEMSData，偏移量L3G4200DDF
*/
u8 L3G4200DReadData()
{
	for (u8 i=0;i<6;i++)
	{
		MEMS_ReadReg(L3G4200D,29+i,myMEMSData+L3G4200DDF+i);
	}


	return 1;

}
/*
函数：u8 L3G4200DSleepActiveChange(u8 Type)
功能：陀螺仪的休眠和工作切换函数
参数：TYPE 0：休眠状态 1：工作状态
返回：1  
注意：
*/

void L3G4200DInit()
{
	while(MEMS_WriteReg(L3G4200D,0x16,0x07));  //125HZ采样率	
}

u8 L3G4200DPowerMGR(u8 Mode)
{
    u8 Data,Data2;
     while(MEMS_ReadReg(L3G4200D,0x16,&Data));
	while(MEMS_ReadReg(L3G4200D,0x3E,&Data2));
	if (Mode==1)  //激活状态
	{
		setbit(Data,6);
		clrbit(Data2,6);
	}
	else
	{
		clrbit(Data,6);
		setbit(Data2,6);


	}
	while(MEMS_WriteReg(L3G4200D,0x16,Data));
	while(MEMS_WriteReg(L3G4200D,0x3E,Data2));
	return 1;
}
                    
/*
函数：float L3G4200DDataProcess(u8 D1,u8 D2)  //d1高位，D2低位
功能：陀螺仪的数据处理接口函数
参数：D1:数据高位，D2：数据低位
返回：获得的浮点值
注意：
*/
float L3G4200DDataProcess(u8 D1,u8 D2)  //d1高位，D2低位
{
	unsigned int temp=D1;
	temp=temp<<8;
	temp+=D2;
	signed int temp2=(signed int)temp;
	return (float)(temp2)*0.061;



}
/*
函数：u8 L3G4200DShowData(float* x,float* y,float* z)
功能：陀螺仪的数据获得函数
参数：float* x,float* y,float* z分别存储当前的X,Y，Z三轴角速度
返回：1
注意：
*/
u8 L3G4200DShowData()
{

	GyroX=L3G4200DDataProcess(myMEMSData[L3G4200DDF],myMEMSData[L3G4200DDF+1]);
	GyroY=L3G4200DDataProcess(myMEMSData[L3G4200DDF+2],myMEMSData[L3G4200DDF+3]);
	GyroZ=L3G4200DDataProcess(myMEMSData[L3G4200DDF+4],myMEMSData[L3G4200DDF+5]);
	return 1;
}



//====================================================
//加速度传感器驱动函数（ADXL345）
//====================================================

/*
函数：u8 ADXL345Init(u8 Mode) 
功能：初始化加速度计到正常工作状态
参数：Mode：工作状态0-3 2G,4G,8G,16G?
返回：1
注意:
*/

u8 ADXL345Init(u8 Mode)    //测量模式下的初始化函数
{
	//mode表示当前的工作状态，0-3 2G,4G,8G,16G?
	while(MEMS_WriteReg(ADXL345,ADXL345_BW_RATE,0X0A));  //正常工作模式，100HZ输出
	while(MEMS_WriteReg(ADXL345,ADXL345_POWER_CTL,0x28));
	while(MEMS_WriteReg(ADXL345,ADXL345_DATA_FORMAT,0x20+Mode));
	return 1;
}


/*
函数：u8 ADXL345Init(u8 Mode) 
功能：初始化加速度计到中端配置状态
参数：Mode：无
返回：1
注意:具体细节详见内部代码注释
*/
u8 ADXL345IntConfig()
{
	//while (MEMS_WriteReg(ADXL345,ADXL345_THRESH_TAP,20));    //敲击阈值检测62.5mg*20
	//while (MEMS_WriteReg(ADXL345,ADXL345_DUR,3));      //在门限值上面的时间625us单位
	//while (MEMS_WriteReg(ADXL345,ADXL345_Latent,20));      //两次拍打的时间差 1.25mg单位
	//while (MEMS_WriteReg(ADXL345,ADXL345_Window,80));      //第二次拍打的的时间窗1.25mg
	while (MEMS_WriteReg(ADXL345,ADXL345_THRESH_ACT,80));      //检测到活动状态的阈值1.25mg
	while (MEMS_WriteReg(ADXL345,ADXL345_THRESH_INACT,20));      //检测到不活动状态的阈值1.25mg
	while (MEMS_WriteReg(ADXL345,ADXL345_TIME_INACT,2));     //检测到不运动的时间2.0s
	while (MEMS_WriteReg(ADXL345,ADXL345_INACT_CTL,0x17));    //运动和不运动检测配置00010111
	//while (MEMS_WriteReg(ADXL345,ADXL345_TAP_AXES,0x07));    //拍打检测，对X,Y,Z轴都有效
	while (MEMS_WriteReg(ADXL345,ADXL345_INT_ENABLE,0x18));   //中断检测，单击，双击，激活与非激活全部开启01111000  0x78    当前只开启激活和非激活中断
	while (MEMS_WriteReg(ADXL345,ADXL345_INT_MAP,0x18));  //输出管脚设定,单双击在1pin,激活和非激活在2pin  00011000
	return 1;
}
/*
函数：u8 ADXL345DataRevise()  
功能：加速度计的数据修正
参数：无
返回：1
注意:具体细节详见内部代码注释
*/
u8 ADXL345DataRevise()  //数据校正函数
{
	MEMS_WriteReg(ADXL345,0X1F,0X02);  
	//Y校正
	MEMS_WriteReg(ADXL345,0x1E,0X00);    //X校正

	MEMS_WriteReg(ADXL345,0X20,0X00);  //Z校正
	return 1;

}
/*
函数：u8 ADXL345ReadData()
功能：加速度计的读取数据
参数：无
返回：1
注意:数据存储在myMEMSData[]，偏移量ADXL345DF
*/
u8 ADXL345ReadData()
{

	for (u8 i=0;i<6;i++)
	{
		MEMS_ReadReg(ADXL345,0x32+i,myMEMSData+ADXL345DF+i);
	}

	return 1;
}
/*
函数：float ADXL345DataProcess(u8 D1,u8 D2,u8 Config)
功能：加速度计的数据转换函数
参数：D1,D2：高低位 ,数据从右到左。config：工作模式，参见ADXL345Init的mode 定义
返回：1
注意:数据存储在myMEMSData[]，偏移量ADXL345DF
*/
float ADXL345DataProcess(u8 D1,u8 D2,u8 Config)
{

	//超麻烦的比特级数据转换算法!!!!

	u8 DataSelect[4]={0x1,0x3,0x7,0xf};  //筛选数据
	//u16 DataRange[4]={256,512,1024,2048};
	u8 FUCK[4]={1,2,4,8};
	u8 Numflag=0x01<<(Config+1);  //符号位的标准位置
	unsigned int temp=0;


	if((D1&Numflag)!=Numflag)  //正数
	{
		D1&=DataSelect[Config];
		temp=D1<<8;
		temp +=D2;
		return (float)temp/25.6*FUCK[Config];

	}
	else   //负数
	{
		D1=~D1;
		D2=~D2;
		D1&=DataSelect[Config];
		temp=D1<<8;
		temp+=(D2+1);

		return  -(float)temp/25.6*FUCK[Config];
	}

}
/*
函数：u8 ADXL345ShowData(float *x,float *y,float *z)
功能：加速度计的实用数据函数
参数：获得当前x,y,z三轴加速度值
返回：1
注意:数据存储在myMEMSData[]，偏移量ADXL345DF
*/
u8 ADXL345ShowData(u8 Config )
{

	AccX=ADXL345DataProcess(myMEMSData[ADXL345DF+1],myMEMSData[ADXL345DF],Config);
	AccY=ADXL345DataProcess(myMEMSData[ADXL345DF+3],myMEMSData[ADXL345DF+2],Config);
	AccZ=ADXL345DataProcess(myMEMSData[ADXL345DF+5],myMEMSData[ADXL345DF+4],Config);
	return 1;

}	


//====================================================
//磁场计驱动函数（HMC5883L）（总算丫的等到今天了！！！）
//====================================================
/*
函数：u8 HMC5883Init(u8 Mode) 
功能：初始化磁场计正常工作状态
参数：Mode：工作状态0-3 2G,4G,8G,16G?
返回：1
注意:
*/

void HMC5883LInit()
{
	//mode表示当前的工作状态，0-3 2G,4G,8G,16G?
	while(MEMS_WriteReg(HMC5883L,HMC5883L_CfgA,  0x18));      //设置bit7为0，8采样率,30Hz输出率，000正常测量模式， 011,101,00   //0704
	while(MEMS_WriteReg(HMC5883L,HMC5883L_CfgB,   0x20));     //设置默认磁场范围，0010000
	
	
}
void HMC5883LPowerMGR(u8 Mode)   //1开始工作，0,为休眠
{
  if(Mode)
       while(MEMS_WriteReg(HMC5883L,HMC5883L_Mode,0x00));  //设置连续测量模式，此时每读一次数据输出寄存器，开始一次新的测量 
  else
       while(MEMS_WriteReg(HMC5883L,HMC5883L_Mode,0x11));  //设置连续测量模式，此时每读一次数据输出寄存器，开始一次新的测量

}
/*
函数：u8 HMC5883LReadData()
功能：读取磁场计的数据
参数：无
返回：1  
注意：存储位置在myMEMSData，偏移量HMC5883DF
*/
void HMC5883LReadData()
{
	for (u8 i=0;i<6;i++)
	{
		MEMS_ReadReg(HMC5883L,HMC5883L_XMSB+i,myMEMSData+HMC5883DF+i);

	}


	

}

/*
函数：float HMC5883LDataProcess(u8 D1,u8 D2)  //d1高位，D2低位
功能：磁场计的数据处理接口函数
参数：D1:数据高位，D2：数据低位
返回：获得的浮点值
注意：
*/
float HMC5883LDataProcess(u8 D1,u8 D2)  //d1高位，D2低位
{
	float fuck;
	unsigned int temp=D1;
	temp=temp<<8;
	temp+=D2;
	signed int temp2=(signed int)temp;
	fuck= (float)(temp2)*0.00092;  //高斯量1W gause ==1T
	return fuck;
}

/*
函数：u8 HMC5883L(float* x,float* y,float* z)
功能:  磁场计的数据获得函数
参数：float* x,float* y,float* z分别存储当前的X,Y，Z三轴角速度
返回：1
注意：
*/
u8 HMC5883LShowData()
{
	ComX=HMC5883LDataProcess(myMEMSData[HMC5883DF],myMEMSData[HMC5883DF+1]);
	ComZ=HMC5883LDataProcess(myMEMSData[HMC5883DF+2],myMEMSData[HMC5883DF+3]);
	ComY=HMC5883LDataProcess(myMEMSData[HMC5883DF+4],myMEMSData[HMC5883DF+5])+0.136;
	return 1;
}
void InitAllSensor()
{ 
  L3G4200DInit();
  ADXL345Init(3);
  HMC5883LInit();

}
void StartAllSensor()
{
  
  
  HMC5883LPowerMGR(1);
  L3G4200DPowerMGR(1);
}
void CloseAllSensor()
{
    HMC5883LPowerMGR(0);
  L3G4200DPowerMGR(0);
}
                   
void GetAllSensorData()
{
      
      ADXL345ReadData();
      L3G4200DReadData();
      HMC5883LReadData();
}