#include "config.h"
/*
MemsDriver.c
ELPOS2.0的MEMS传感器驱动函数和上层运用，器件ADXL345,ITG3200,BMP085和HMC5883
Copyright (c) 2010，赵一鸣
buptzym@bupt.edu.cn
All rights reserved.
本程序仅供学习参考，不提供任何可靠性方面的担保；请勿用于商业目的
*/




#define  L3G4200D  1
#define  HMC5883L 2
#define  ADXL345 3
#define  BMP085  4

#define ITG3200_I2C_ADDR   0X68
#define  HMC5883_I2C_ADDR  0X1E


#define  ADXL345_I2C_ADDR  0X53
#define  BMP085_I2C_ADDR  0X77




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




//////////////////////////////////////////////
//模拟I2C总线的引脚定义
#define   I2C_SCL  BIT1
#define   I2C_SDA  BIT0
#define  I2C_SCL_SET()            P5OUT |= I2C_SCL
#define  I2C_SCL_CLR()             P5OUT &=~ I2C_SCL
#define  I2C_SDA_SET()            P5OUT |= I2C_SDA
#define  I2C_SDA_CLR()             P5OUT &=~ I2C_SDA
#define  I2C_SDA_IN()             P5DIR &=~ I2C_SDA
#define  I2C_SDA_OUT()            P5DIR |= I2C_SDA
#define I2C_SCL_OUT()               P5DIR |= I2C_SCL
#define  I2C_SCL_IN()             P5DIR &=~ I2C_SCL



//***************底层硬件驱动层*****************************************/
/*
函数：I2C_Init()
功能：I2C总线初始化，使总线处于空闲状态
说明：在main()函数的开始处，通常应当要执行一次本函数
*/
void I2C_Init()
{
	
	
	I2C_SDA_OUT();
	I2C_SCL_OUT() ;
	I2C_SCL_SET() ;
	delay_ms(4);
	I2C_SDA_SET() ;
	delay_ms(4);
}

/*
函数：I2C_Start()
功能：产生I2C总线的起始状态
说明：
SCL处于高电平期间，当SDA出现下降沿时启动I2C总线
不论SDA和SCL处于什么电平状态，本函数总能正确产生起始状态
本函数也可以用来产生重复起始状态
本函数执行后，I2C总线处于忙状态
*/
void I2C_Start()
{
	I2C_SDA_SET() ;
	//delay_us(1);
	I2C_SCL_SET() ;
	//delay_us(1);
	I2C_SDA_CLR() ;
	//delay_us(1);
	I2C_SCL_CLR() ;
	//delay_us(1);
}

/*
函数：I2C_Write()
功能：向I2C总线写1个字节的数据
参数：
dat：要写到总线上的数据
*/
void I2C_Write(unsigned char dat)
{
	
	
	//////////////
	unsigned char i;
	for (i=0; i<8; i++)
	{
		I2C_SCL_CLR() ;
		//delay_us(1);
		if (((dat >> 7) & 0x01) == 0x01)
		{
			I2C_SDA_SET() ;
		}
		else
		{
			I2C_SDA_CLR() ;
		}
		//delay_us(1);
		I2C_SCL_SET() ;
		dat = dat << 1;
		//delay_us(1);
	}
	I2C_SCL_CLR() ;
	// delay_us(1);
	I2C_SDA_SET() ;
	//delay_us(1);
	
}

/*
函数：I2C_Read()
功能：从从机读取1个字节的数据
返回：读取的一个字节数据
*/
unsigned char I2C_Read()
{
	unsigned char i;
	unsigned char TempBit  = 0;
	unsigned char TempData = 0;
	I2C_SCL_CLR() ;
	//delay_us(1);
	I2C_SDA_SET() ;
	for (i=0; i<8; i++)
	{
		//delay_us(1);
		I2C_SCL_SET() ;
		//delay_us(1);
		I2C_SDA_IN() ; 
		if (((P5IN&I2C_SDA)==I2C_SDA))
		{
			TempBit = 1;
			
		}
		else
		{
			TempBit = 0;
		}
		I2C_SDA_OUT() ; 
		//delay_us(1);
		TempData = (TempData << 1) | TempBit;
		
		I2C_SCL_CLR() ;
		// delay_us(1);
	}
	//delay_us(1);
	return(TempData);
}

/*
函数：I2C_GetAck()
功能：读取从机应答位
返回：
0：从机应答
1：从机非应答
说明：
从机在收到每个字节的数据后，要产生应答位
从机在收到最后1个字节的数据后，一般要产生非应答位
*/
unsigned char  I2C_GetAck()
{
	unsigned char  ack=0;
	I2C_SDA_SET() ;
	//delay_us(1);
	I2C_SCL_SET() ;
	//delay_us(1);
	I2C_SDA_IN();       
	if((P5IN&I2C_SDA)==I2C_SDA)//一定注意，若修改宏定义，则此处一定修改
		ack=1;
	else 
		ack=0;
	// delay_us(1);
	I2C_SDA_OUT();   
	//  delay_us(1);
	I2C_SCL_CLR() ;
	//delay_us(1);
	return ack;
}

/*
函数：I2C_PutAck()
功能：主机产生应答位或非应答位
参数：
ack=0：主机产生应答位
ack=1：主机产生非应答位
说明：
主机在接收完每一个字节的数据后，都应当产生应答位
主机在接收完最后一个字节的数据后，应当产生非应答位
*/
void I2C_PutAck(unsigned char  ack)
{
	if( ack==1)
		
		I2C_SDA_SET();
	else 
		I2C_SDA_CLR() ;
	
	//delay_us(1);
	I2C_SCL_SET() ;
	//delay_us(1);
	I2C_SCL_CLR() ;
	//delay_us(1);
}

/*
函数：I2C_Stop()
功能：产生I2C总线的停止状态
说明：
SCL处于高电平期间，当SDA出现上升沿时停止I2C总线
不论SDA和SCL处于什么电平状态，本函数总能正确产生停止状态
本函数执行后，I2C总线处于空闲状态
*/
void I2C_Stop()
{
	//unsigned int t = I2C_STOP_WAIT_VALUE;
	I2C_SDA_CLR() ;
	//delay_us(1);
	I2C_SCL_SET() ;
	//delay_us(1);
	I2C_SDA_SET() ;
	delay_us(2);
	
}

/*
函数：I2C_Puts()
功能：I2C总线综合发送函数，向从机发送多个字节的数据
参数：
SlaveAddr：从机地址（7位纯地址，不含读写位）
SubAddr：从机的子地址
SubMod：子地址模式，0－无子地址，1－单字节子地址，2－双字节子地址
*dat：要发送的数据
Size：数据的字节数
返回：
0：发送成功
1：在发送过程中出现异常
说明：
本函数能够很好地适应所有常见的I2C器件，不论其是否有子地址
当从机没有子地址时，参数SubAddr任意，而SubMod应当为0
*/
unsigned char  I2C_Puts
(
 unsigned char SlaveAddr,
 unsigned int SubAddr,
 unsigned char SubMod,
 unsigned char *dat,
 unsigned int Size
 )
{
	//定义临时变量
	unsigned char i;
	char a[3];
	//检查长度
	if ( Size == 0 ) return 0;
	//准备从机地址
	a[0] = (SlaveAddr << 1);
	//检查子地址模式
	if ( SubMod > 2 ) SubMod = 2;
	//确定子地址
	switch ( SubMod )
	{
	case 0:
		break;
	case 1:
		a[1] = (unsigned char)(SubAddr);
		break;
	case 2:
		a[1] = (unsigned char)(SubAddr >> 8);
		a[2] = (unsigned char)(SubAddr);
		break;
	default:
		break;
	}
	//发送从机地址，接着发送子地址（如果有子地址的话）
	SubMod++;
	I2C_Start();
	for ( i=0; i<SubMod; i++ )
	{
		I2C_Write(a[i]);
		if ( I2C_GetAck() )
		{
			I2C_Stop();
			return 1;
		}
	}
	//发送数据
	do
	{
		I2C_Write(*dat++);
		if ( I2C_GetAck() ) break;
	} while ( --Size != 0 );
	//发送完毕，停止I2C总线，并返回结果
	I2C_Stop();
	if ( Size == 0 )
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

/*
函数：I2C_Gets()
功能：I2C总线综合接收函数，从从机接收多个字节的数据
参数：
SlaveAddr：从机地址（7位纯地址，不含读写位）
SubAddr：从机的子地址
SubMod：子地址模式，0－无子地址，1－单字节子地址，2－双字节子地址
*dat：保存接收到的数据
Size：数据的字节数
返回：
0：接收成功
1：在接收过程中出现异常
说明：
本函数能够很好地适应所有常见的I2C器件，不论其是否有子地址
当从机没有子地址时，参数SubAddr任意，而SubMod应当为0
*/
unsigned char  I2C_Gets
(
 unsigned char SlaveAddr,
 unsigned int SubAddr,
 unsigned char SubMod,
 unsigned char *dat,
 unsigned int Size
 )
{
	//定义临时变量
	unsigned char i;
	char a[3];
	//检查长度
	if ( Size == 0 ) return 0;
	//准备从机地址
	a[0] = (SlaveAddr << 1);
	//检查子地址模式
	if ( SubMod > 2 ) SubMod = 2;
	//如果是有子地址的从机，则要先发送从机地址和子地址
	if ( SubMod != 0 )
	{
		//确定子地址
		if ( SubMod == 1 )
		{
			a[1] = (unsigned char)(SubAddr);
		}
		else
		{
			a[1] = (unsigned char)(SubAddr >> 8);
			a[2] = (unsigned char)(SubAddr);
		}
		//发送从机地址，接着发送子地址
		SubMod++;
		I2C_Start();
		for ( i=0; i<SubMod; i++ )
		{
			I2C_Write(a[i]);
			if ( I2C_GetAck() )
			{
				I2C_Stop();
				return 1;
			}
		}
	}
	//这里的I2C_Start()对于有子地址的从机是重复起始状态
	//对于无子地址的从机则是正常的起始状态
	I2C_Start();
	//发送从机地址
	I2C_Write(a[0]+1);
	if ( I2C_GetAck() )
	{
		I2C_Stop();
		return 1;
	}
	//接收数据
	for (;;)
	{
		*dat++ = I2C_Read();
		if ( --Size == 0 )
		{
			I2C_PutAck(1);
			break;
		}
		I2C_PutAck(0);
	}
	//接收完毕，停止I2C总线，并返回结果
	I2C_Stop();
	return 0;
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
		//b = I2C_Puts(ITG3200_I2C_ADDR,RegAddr,1,&dat,1);
        break;
	case HMC5883L:
		//b = I2C_Puts(HMC5883_I2C_ADDR,RegAddr,1,&dat,1);
		break;
		
	case ADXL345:
		b = I2C_Puts(ADXL345_I2C_ADDR,RegAddr,1,&dat,1);
		break;
	case    BMP085:
		//b = I2C_Puts(BMP085_I2C_ADDR,RegAddr,1,&dat,1);
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
	unsigned char b;
	switch(ICID)
	{
	case L3G4200D:
		//b = I2C_Gets(ITG3200_I2C_ADDR,RegAddr,1,dat,1);
        break;
	case HMC5883L:
		//b = I2C_Gets(HMC5883_I2C_ADDR,RegAddr,1,dat,1);
		break;
		
	case ADXL345:
		b = I2C_Gets(ADXL345_I2C_ADDR,RegAddr,1,dat,1);
		break;
	case    BMP085:
		//b = I2C_Gets(BMP085_I2C_ADDR,RegAddr,1,dat,1);
		break;
	}
	return 0;
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
  u8 i=0;
	for ( i=0;i<6;i++)
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
/*	//while (MEMS_WriteReg(ADXL345,ADXL345_THRESH_TAP,20));    //敲击阈值检测62.5mg*20
	//while (MEMS_WriteReg(ADXL345,ADXL345_DUR,3));      //在门限值上面的时间625us单位
	//while (MEMS_WriteReg(ADXL345,ADXL345_Latent,20));      //两次拍打的时间差 1.25mg单位
	//while (MEMS_WriteReg(ADXL345,ADXL345_Window,80));      //第二次拍打的的时间窗1.25mg
	while (MEMS_WriteReg(ADXL345,ADXL345_THRESH_ACT,80));      //检测到活动状态的阈值1.25mg
	while (MEMS_WriteReg(ADXL345,ADXL345_THRESH_INACT,20));      //检测到不活动状态的阈值1.25mg
	while (MEMS_WriteReg(ADXL345,ADXL345_TIME_INACT,2));     //检测到不运动的时间2.0s
	while (MEMS_WriteReg(ADXL345,ADXL345_INACT_CTL,0x17));    //运动和不运动检测配置00010111
	//while (MEMS_WriteReg(ADXL345,ADXL345_TAP_AXES,0x07));    //拍打检测，对X,Y,Z轴都有效
	while (MEMS_WriteReg(ADXL345,ADXL345_INT_ENABLE,0x18));   //中断检测，单击，双击，激活与非激活全部开启01111000  0x78    当前只开启激活和非激活中断
	while (MEMS_WriteReg(ADXL345,ADXL345_INT_MAP,0x18));  //输出管脚设定,单双击在1pin,激活和非激活在2pin  000110008/
  
  */
	
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

u8 accdata[3];
/*
函数：u8 ADXL345ReadData()
功能：加速度计的读取数据
参数：无
返回：1
注意:数据存储在myMEMSData[]，偏移量ADXL345DF
*/
u8 ADXL345ReadData()
{
  u8 i;

	for ( i=0;i<6;)
	{
		MEMS_ReadReg(ADXL345,0x32+i,myMEMSData+ADXL345DF+i);
              
                i++;
	}
  accdata[0]=myMEMSData[ADXL345DF];
    accdata[1]=myMEMSData[ADXL345DF];
     
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
		D1=~D1;  //0x00
		D2=~D2;   //0x21
		D1&=DataSelect[Config];  //0X00
		temp=D1<<8;  //0
		temp+=(D2+1);   //34

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
  u8 i=0;
	for ( i=0;i<6;i++)
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
	ADXL345Init(1);
	HMC5883LInit();
	L3G4200DInit();
	isGyroExisted=0;
	isAccExisted=1;
	isComExisted=0;
	clrbit(myMEMSData[NODEABILITYDF],BIT6);  //GYRO
	clrbit(myMEMSData[NODEABILITYDF],BIT5);  //COM
	setbit(myMEMSData[NODEABILITYDF],BIT4);  //ACC
	if(HIDENABLE)
	{
		setbit(myMEMSData[NODEABILITYDF],BIT7);// HID
	}
	if(PRESSUREENABLE)
	{
		setbit(myMEMSData[NODEABILITYDF],BIT3);// pressure
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
        
        
       myMEMSData[ADXL345DF]= accdata[0];
   myMEMSData[ADXL345DF]= accdata[1];
}
void CalAllSensorData()
{
   HMC5883LShowData();
     ADXL345ShowData(1);
   L3G4200DShowData();
}