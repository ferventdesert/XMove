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








//自制Sensor的SPI驱动程序，住自己成功！
#define Sensor_CSN BIT7//P2.5

#define  Sensor_SCK BIT0//P2.6
#define Sensor_MOSI BIT1//P3.3
#define  Sensor_MISO BIT2//P3.7

#define Sensor_CSN_DIR P6DIR
#define Sensor_SCK_DIR P1DIR
#define Sensor_MOSI_DIR P1DIR
#define Sensor_MISO_DIR P1DIR


#define Sensor_CSN_OutPort P6OUT
#define  Sensor_SCK_OutPort P1OUT
#define Sensor_MOSI_OutPort P1OUT
#define  Sensor_MISO_InPort P1IN

#define Sensor_CSN_OutDIR() setbit(Sensor_CSN_DIR,Sensor_CSN)
#define Sensor_SCK_OutDIR() setbit(Sensor_SCK_DIR,Sensor_SCK)
#define Sensor_MOSI_OutDIR() setbit(Sensor_MOSI_DIR,Sensor_MOSI)
#define Sensor_MISO_InDIR() clrbit(Sensor_MISO_DIR,Sensor_MISO)

#define Sensor_Set_CE() setbit(Sensor_CE_OutPort,Sensor_CE)
#define Sensor_Clear_CE() clrbit(Sensor_CE_OutPort,Sensor_CE)
#define Sensor_Set_CSN() setbit(Sensor_CSN_OutPort,Sensor_CSN)
#define Sensor_Clear_CSN() clrbit(Sensor_CSN_OutPort,Sensor_CSN)
#define Sensor_Set_SCK() setbit(Sensor_SCK_OutPort,Sensor_SCK)
#define Sensor_Clear_SCK() clrbit(Sensor_SCK_OutPort,Sensor_SCK)
#define Sensor_Set_MOSI() setbit(Sensor_MOSI_OutPort,Sensor_MOSI)
#define Sensor_Clear_MOSI() clrbit(Sensor_MOSI_OutPort,Sensor_MOSI)


void Init_Sensor_IO(void)
{

	Sensor_CSN_OutDIR();
	Sensor_SCK_OutDIR();
	Sensor_MOSI_OutDIR();
	Sensor_MISO_InDIR();
	Sensor_Set_CSN();
	Sensor_Clear_SCK();
	Sensor_Clear_MOSI();
}
void I2C_Init()
{
  Init_Sensor_IO();
}
//
//
//function SpiWrite();
/******************************************************************************************/
void SensorSpiWrite(unsigned char byte)
{
	unsigned char i;

	Sensor_Clear_SCK();
	for (i=0;i<8;i++) // Setup byte circulation bits
	{
		if ((byte&0x80)==0x80) // Put DATA_BUF.7 on data line
			Sensor_Set_MOSI(); //MOSI=1;
		else
			Sensor_Clear_MOSI(); //MOSI=0;
		Sensor_Set_SCK(); // Set clock line high
		byte=byte<<1;
		Sensor_Clear_SCK(); // Set clock line low
	}

}
//
//
//function SpiRead();
/*****************************************************************************************/
unsigned char SensorSpiRead(void)
{
	unsigned char i;
	unsigned char temp=0;
	Sensor_Clear_SCK();
	for (i=0;i<8;i++) // Setup byte circulation bits
	{
		Sensor_Set_SCK(); // Set clock line high
		temp=temp<<1; // Right shift DATA_BUF
		if ((Sensor_MISO_InPort&Sensor_MISO)==Sensor_MISO)
		{temp|=1;} // Read data
		Sensor_Clear_SCK(); // Set clock line low

	}

	return temp; // Return function parameter
}
void SensorSpiWriteReg(unsigned char SpiCommand,unsigned char Content)
{
	SpiCommand=((SpiCommand&0x3f)<<1)|0x80;
	Sensor_Set_CSN();
	Sensor_Clear_CSN();
	SensorSpiWrite(SpiCommand);
	SensorSpiWrite(Content);
	Sensor_Set_CSN();
}

u8 SensorSpiReadReg(unsigned char Reg)//Payload Out
{
	unsigned char DataBuff;
	Reg=((Reg&0x3f))<<1;
	Sensor_Set_CSN();
	Sensor_Clear_CSN();
	SensorSpiWrite(Reg);
	DataBuff=SensorSpiRead();	
	Sensor_Set_CSN();
	return DataBuff;
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
	switch(ICID)
	{
	case L3G4200D:
		//b=   TWI_RW(0,L3G4200D_I2C_ADDR,RegAddr,0,&dat,1);		
		break;
	case HMC5883L:
		//b=   TWI_RW(0,HMC5883L_I2C_ADDR,RegAddr,0,&dat,1);	
		break;

	case ADXL345:
             SensorSpiWriteReg(RegAddr,dat);
		
		break;

	}
	return 0;
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
	
	switch(ICID)
	{
	case L3G4200D:
		//b=   TWI_RW(1,L3G4200D_I2C_ADDR,RegAddr,0,dat,1);	
		break;
	case HMC5883L:
		//b=   TWI_RW(1,HMC5883L_I2C_ADDR,RegAddr,0,dat,1);	
		break;

	case ADXL345:
              *dat = SensorSpiReadReg(RegAddr);
           
	//	b=   TWI_RW(1,ADXL345_I2C_ADDR,RegAddr,0,dat,1);	
		break;

	}
	return 1;
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
        Init_Sensor_IO();
     
     
	ADXL345Init(3);
	HMC5883LInit();
	L3G4200DInit();
	isGyroExisted=0;
	isAccExisted=1;
	isComExisted=0;
	clrbit(myMEMSData[NODETYPEDF],6);  //GYRO
	clrbit(myMEMSData[NODETYPEDF],5);  //COM
	clrbit(myMEMSData[NODETYPEDF],4);  //ACC
	if(HIDENABLE)
	{
		setbit(myMEMSData[NODETYPEDF],7);// HID
	}
	if(PRESSUREENABLE)
	{
		setbit(myMEMSData[NODETYPEDF],3);// pressure
	}
}
void StartAllSensor()
{
	if(isComExisted)
		HMC5883LPowerMGR(1);


	if(isGyroExisted&&isGyroEnable)
		L3G4200DPowerMGR(1);


}
void CloseAllSensor()
{
	if(isComExisted)
		HMC5883LPowerMGR(0);
	if(isGyroExisted)
	{

		L3G4200DPowerMGR(0);
	}
}

void GetAllSensorData()
{
	if(isAccExisted)
		ADXL345ReadData();
	if(isGyroExisted&&isGyroEnable)
		L3G4200DReadData();
	if(isComExisted)
		HMC5883LReadData();
}
void CalAllSensorData()
{
   HMC5883LShowData();
    ADXL345ShowData(3);
   L3G4200DShowData();
}