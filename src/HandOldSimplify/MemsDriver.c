#include "config.h"
/*
MemsDriver.c
ELPOS2.0��MEMS�����������������ϲ����ã�����ADXL345,ITG3200,BMP085��HMC5883
Copyright (c) 2010����һ��
buptzym@bupt.edu.cn
All rights reserved.
���������ѧϰ�ο������ṩ�κοɿ��Է���ĵ���������������ҵĿ��
*/




#define  L3G4200D  1
#define  HMC5883L 2
#define  ADXL345 3
#define  BMP085  4

#define ITG3200_I2C_ADDR   0X68
#define  HMC5883_I2C_ADDR  0X1E


#define  ADXL345_I2C_ADDR  0X53
#define  BMP085_I2C_ADDR  0X77




//��ADXL345�ڲ��ļĴ�����ַ
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


//����HMC5883L�ڲ��Ĵ�����ַ���ӵ�ַ��
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
//ģ��I2C���ߵ����Ŷ���
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



//***************�ײ�Ӳ��������*****************************************/
/*
������I2C_Init()
���ܣ�I2C���߳�ʼ����ʹ���ߴ��ڿ���״̬
˵������main()�����Ŀ�ʼ����ͨ��Ӧ��Ҫִ��һ�α�����
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
������I2C_Start()
���ܣ�����I2C���ߵ���ʼ״̬
˵����
SCL���ڸߵ�ƽ�ڼ䣬��SDA�����½���ʱ����I2C����
����SDA��SCL����ʲô��ƽ״̬��������������ȷ������ʼ״̬
������Ҳ�������������ظ���ʼ״̬
������ִ�к�I2C���ߴ���æ״̬
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
������I2C_Write()
���ܣ���I2C����д1���ֽڵ�����
������
dat��Ҫд�������ϵ�����
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
������I2C_Read()
���ܣ��Ӵӻ���ȡ1���ֽڵ�����
���أ���ȡ��һ���ֽ�����
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
������I2C_GetAck()
���ܣ���ȡ�ӻ�Ӧ��λ
���أ�
0���ӻ�Ӧ��
1���ӻ���Ӧ��
˵����
�ӻ����յ�ÿ���ֽڵ����ݺ�Ҫ����Ӧ��λ
�ӻ����յ����1���ֽڵ����ݺ�һ��Ҫ������Ӧ��λ
*/
unsigned char  I2C_GetAck()
{
	unsigned char  ack=0;
	I2C_SDA_SET() ;
	//delay_us(1);
	I2C_SCL_SET() ;
	//delay_us(1);
	I2C_SDA_IN();       
	if((P5IN&I2C_SDA)==I2C_SDA)//һ��ע�⣬���޸ĺ궨�壬��˴�һ���޸�
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
������I2C_PutAck()
���ܣ���������Ӧ��λ���Ӧ��λ
������
ack=0����������Ӧ��λ
ack=1������������Ӧ��λ
˵����
�����ڽ�����ÿһ���ֽڵ����ݺ󣬶�Ӧ������Ӧ��λ
�����ڽ��������һ���ֽڵ����ݺ�Ӧ��������Ӧ��λ
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
������I2C_Stop()
���ܣ�����I2C���ߵ�ֹͣ״̬
˵����
SCL���ڸߵ�ƽ�ڼ䣬��SDA����������ʱֹͣI2C����
����SDA��SCL����ʲô��ƽ״̬��������������ȷ����ֹͣ״̬
������ִ�к�I2C���ߴ��ڿ���״̬
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
������I2C_Puts()
���ܣ�I2C�����ۺϷ��ͺ�������ӻ����Ͷ���ֽڵ�����
������
SlaveAddr���ӻ���ַ��7λ����ַ��������дλ��
SubAddr���ӻ����ӵ�ַ
SubMod���ӵ�ַģʽ��0�����ӵ�ַ��1�����ֽ��ӵ�ַ��2��˫�ֽ��ӵ�ַ
*dat��Ҫ���͵�����
Size�����ݵ��ֽ���
���أ�
0�����ͳɹ�
1���ڷ��͹����г����쳣
˵����
�������ܹ��ܺõ���Ӧ���г�����I2C�������������Ƿ����ӵ�ַ
���ӻ�û���ӵ�ַʱ������SubAddr���⣬��SubModӦ��Ϊ0
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
	//������ʱ����
	unsigned char i;
	char a[3];
	//��鳤��
	if ( Size == 0 ) return 0;
	//׼���ӻ���ַ
	a[0] = (SlaveAddr << 1);
	//����ӵ�ַģʽ
	if ( SubMod > 2 ) SubMod = 2;
	//ȷ���ӵ�ַ
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
	//���ʹӻ���ַ�����ŷ����ӵ�ַ��������ӵ�ַ�Ļ���
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
	//��������
	do
	{
		I2C_Write(*dat++);
		if ( I2C_GetAck() ) break;
	} while ( --Size != 0 );
	//������ϣ�ֹͣI2C���ߣ������ؽ��
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
������I2C_Gets()
���ܣ�I2C�����ۺϽ��պ������Ӵӻ����ն���ֽڵ�����
������
SlaveAddr���ӻ���ַ��7λ����ַ��������дλ��
SubAddr���ӻ����ӵ�ַ
SubMod���ӵ�ַģʽ��0�����ӵ�ַ��1�����ֽ��ӵ�ַ��2��˫�ֽ��ӵ�ַ
*dat��������յ�������
Size�����ݵ��ֽ���
���أ�
0�����ճɹ�
1���ڽ��չ����г����쳣
˵����
�������ܹ��ܺõ���Ӧ���г�����I2C�������������Ƿ����ӵ�ַ
���ӻ�û���ӵ�ַʱ������SubAddr���⣬��SubModӦ��Ϊ0
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
	//������ʱ����
	unsigned char i;
	char a[3];
	//��鳤��
	if ( Size == 0 ) return 0;
	//׼���ӻ���ַ
	a[0] = (SlaveAddr << 1);
	//����ӵ�ַģʽ
	if ( SubMod > 2 ) SubMod = 2;
	//��������ӵ�ַ�Ĵӻ�����Ҫ�ȷ��ʹӻ���ַ���ӵ�ַ
	if ( SubMod != 0 )
	{
		//ȷ���ӵ�ַ
		if ( SubMod == 1 )
		{
			a[1] = (unsigned char)(SubAddr);
		}
		else
		{
			a[1] = (unsigned char)(SubAddr >> 8);
			a[2] = (unsigned char)(SubAddr);
		}
		//���ʹӻ���ַ�����ŷ����ӵ�ַ
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
	//�����I2C_Start()�������ӵ�ַ�Ĵӻ����ظ���ʼ״̬
	//�������ӵ�ַ�Ĵӻ�������������ʼ״̬
	I2C_Start();
	//���ʹӻ���ַ
	I2C_Write(a[0]+1);
	if ( I2C_GetAck() )
	{
		I2C_Stop();
		return 1;
	}
	//��������
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
	//������ϣ�ֹͣI2C���ߣ������ؽ��
	I2C_Stop();
	return 0;
}




//***************Ӧ�ò�ӿں���***********************************/
/*
������MEMS_WriteReg()
���ܣ��򴫸�����ĳ���ڲ��Ĵ���д������
������
ICID������������ID
dat��Ҫд�������
RegAddr�������ڲ��Ĵ�����ַ
���أ�
0������
1�����ʴ�����ʱ�����쳣
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
������MEMS_ReadReg()
���ܣ��򴫸�����ĳ���ڲ��Ĵ�����������
������
ICID������������ID
dat��Ҫд�������
RegAddr�������ڲ��Ĵ�����ַ
���أ�
0������
1�����ʴ�����ʱ�����쳣
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




//***********************************�ӿ�ת������**************/



//====================================================
//�������������� ��L3G4200D��
//====================================================

/*
������u8 L3G4200DReadData()
���ܣ���ȡ�����ǵ�����
��������
���أ�1  
ע�⣺�洢λ����myMEMSData��ƫ����L3G4200DDF
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
������u8 L3G4200DSleepActiveChange(u8 Type)
���ܣ������ǵ����ߺ͹����л�����
������TYPE 0������״̬ 1������״̬
���أ�1  
ע�⣺
*/

void L3G4200DInit()
{
	while(MEMS_WriteReg(L3G4200D,0x16,0x07));  //125HZ������	
}

u8 L3G4200DPowerMGR(u8 Mode)
{
	u8 Data,Data2;
	while(MEMS_ReadReg(L3G4200D,0x16,&Data));
	while(MEMS_ReadReg(L3G4200D,0x3E,&Data2));
	if (Mode==1)  //����״̬
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
������float L3G4200DDataProcess(u8 D1,u8 D2)  //d1��λ��D2��λ
���ܣ������ǵ����ݴ����ӿں���
������D1:���ݸ�λ��D2�����ݵ�λ
���أ���õĸ���ֵ
ע�⣺
*/
float L3G4200DDataProcess(u8 D1,u8 D2)  //d1��λ��D2��λ
{
	unsigned int temp=D1;
	temp=temp<<8;
	temp+=D2;
	signed int temp2=(signed int)temp;
	return (float)(temp2)*0.061;



}
/*
������u8 L3G4200DShowData(float* x,float* y,float* z)
���ܣ������ǵ����ݻ�ú���
������float* x,float* y,float* z�ֱ�洢��ǰ��X,Y��Z������ٶ�
���أ�1
ע�⣺
*/
u8 L3G4200DShowData()
{

	GyroX=L3G4200DDataProcess(myMEMSData[L3G4200DDF],myMEMSData[L3G4200DDF+1]);
	GyroY=L3G4200DDataProcess(myMEMSData[L3G4200DDF+2],myMEMSData[L3G4200DDF+3]);
	GyroZ=L3G4200DDataProcess(myMEMSData[L3G4200DDF+4],myMEMSData[L3G4200DDF+5]);
	return 1;
}



//====================================================
//���ٶȴ���������������ADXL345��
//====================================================

/*
������u8 ADXL345Init(u8 Mode) 
���ܣ���ʼ�����ٶȼƵ���������״̬
������Mode������״̬0-3 2G,4G,8G,16G?
���أ�1
ע��:
*/

u8 ADXL345Init(u8 Mode)    //����ģʽ�µĳ�ʼ������
{
	//mode��ʾ��ǰ�Ĺ���״̬��0-3 2G,4G,8G,16G?
	while(MEMS_WriteReg(ADXL345,ADXL345_BW_RATE,0X0A));  //��������ģʽ��100HZ���
	while(MEMS_WriteReg(ADXL345,ADXL345_POWER_CTL,0x28));
	while(MEMS_WriteReg(ADXL345,ADXL345_DATA_FORMAT,0x20+Mode));
        
        
        
        
	return 1;
}


/*
������u8 ADXL345Init(u8 Mode) 
���ܣ���ʼ�����ٶȼƵ��ж�����״̬
������Mode����
���أ�1
ע��:����ϸ������ڲ�����ע��
*/
u8 ADXL345IntConfig()
{
/*	//while (MEMS_WriteReg(ADXL345,ADXL345_THRESH_TAP,20));    //�û���ֵ���62.5mg*20
	//while (MEMS_WriteReg(ADXL345,ADXL345_DUR,3));      //������ֵ�����ʱ��625us��λ
	//while (MEMS_WriteReg(ADXL345,ADXL345_Latent,20));      //�����Ĵ��ʱ��� 1.25mg��λ
	//while (MEMS_WriteReg(ADXL345,ADXL345_Window,80));      //�ڶ����Ĵ�ĵ�ʱ�䴰1.25mg
	while (MEMS_WriteReg(ADXL345,ADXL345_THRESH_ACT,80));      //��⵽�״̬����ֵ1.25mg
	while (MEMS_WriteReg(ADXL345,ADXL345_THRESH_INACT,20));      //��⵽���״̬����ֵ1.25mg
	while (MEMS_WriteReg(ADXL345,ADXL345_TIME_INACT,2));     //��⵽���˶���ʱ��2.0s
	while (MEMS_WriteReg(ADXL345,ADXL345_INACT_CTL,0x17));    //�˶��Ͳ��˶��������00010111
	//while (MEMS_WriteReg(ADXL345,ADXL345_TAP_AXES,0x07));    //�Ĵ��⣬��X,Y,Z�ᶼ��Ч
	while (MEMS_WriteReg(ADXL345,ADXL345_INT_ENABLE,0x18));   //�жϼ�⣬������˫����������Ǽ���ȫ������01111000  0x78    ��ǰֻ��������ͷǼ����ж�
	while (MEMS_WriteReg(ADXL345,ADXL345_INT_MAP,0x18));  //����ܽ��趨,��˫����1pin,����ͷǼ�����2pin  000110008/
  
  */
	
 return 1;
}
/*
������u8 ADXL345DataRevise()  
���ܣ����ٶȼƵ���������
��������
���أ�1
ע��:����ϸ������ڲ�����ע��
*/
u8 ADXL345DataRevise()  //����У������
{
  

        
        
        
	MEMS_WriteReg(ADXL345,0X1F,0X02);  
	//YУ��
	MEMS_WriteReg(ADXL345,0x1E,0X00);    //XУ��

	MEMS_WriteReg(ADXL345,0X20,0X00);  //ZУ��
	return 1;

}

u8 accdata[3];
/*
������u8 ADXL345ReadData()
���ܣ����ٶȼƵĶ�ȡ����
��������
���أ�1
ע��:���ݴ洢��myMEMSData[]��ƫ����ADXL345DF
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
������float ADXL345DataProcess(u8 D1,u8 D2,u8 Config)
���ܣ����ٶȼƵ�����ת������
������D1,D2���ߵ�λ ,���ݴ��ҵ���config������ģʽ���μ�ADXL345Init��mode ����
���أ�1
ע��:���ݴ洢��myMEMSData[]��ƫ����ADXL345DF
*/
float ADXL345DataProcess(u8 D1,u8 D2,u8 Config)
{

	//���鷳�ı��ؼ�����ת���㷨!!!!

	u8 DataSelect[4]={0x1,0x3,0x7,0xf};  //ɸѡ����
	//u16 DataRange[4]={256,512,1024,2048};
	u8 FUCK[4]={1,2,4,8};
	u8 Numflag=0x01<<(Config+1);  //����λ�ı�׼λ��
	unsigned int temp=0;


	if((D1&Numflag)!=Numflag)  //����
	{
		D1&=DataSelect[Config];
		temp=D1<<8;
		temp +=D2;
		return (float)temp/25.6*FUCK[Config];

	}
	else   //����
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
������u8 ADXL345ShowData(float *x,float *y,float *z)
���ܣ����ٶȼƵ�ʵ�����ݺ���
��������õ�ǰx,y,z������ٶ�ֵ
���أ�1
ע��:���ݴ洢��myMEMSData[]��ƫ����ADXL345DF
*/
u8 ADXL345ShowData(u8 Config )
{

	AccX=ADXL345DataProcess(myMEMSData[ADXL345DF+1],myMEMSData[ADXL345DF],Config);
	AccY=ADXL345DataProcess(myMEMSData[ADXL345DF+3],myMEMSData[ADXL345DF+2],Config);
	AccZ=ADXL345DataProcess(myMEMSData[ADXL345DF+5],myMEMSData[ADXL345DF+4],Config);
	return 1;

}	


//====================================================
//�ų�������������HMC5883L��������Ѿ�ĵȵ������ˣ�������
//====================================================
/*
������u8 HMC5883Init(u8 Mode) 
���ܣ���ʼ���ų�����������״̬
������Mode������״̬0-3 2G,4G,8G,16G?
���أ�1
ע��:
*/

void HMC5883LInit()
{
	//mode��ʾ��ǰ�Ĺ���״̬��0-3 2G,4G,8G,16G?
	while(MEMS_WriteReg(HMC5883L,HMC5883L_CfgA,  0x18));      //����bit7Ϊ0��8������,30Hz����ʣ�000��������ģʽ�� 011,101,00   //0704
	while(MEMS_WriteReg(HMC5883L,HMC5883L_CfgB,   0x20));     //����Ĭ�ϴų���Χ��0010000


}
void HMC5883LPowerMGR(u8 Mode)   //1��ʼ������0,Ϊ����
{
	if(Mode)
		while(MEMS_WriteReg(HMC5883L,HMC5883L_Mode,0x00));  //������������ģʽ����ʱÿ��һ����������Ĵ�������ʼһ���µĲ��� 
	else
		while(MEMS_WriteReg(HMC5883L,HMC5883L_Mode,0x11));  //������������ģʽ����ʱÿ��һ����������Ĵ�������ʼһ���µĲ���

}
/*
������u8 HMC5883LReadData()
���ܣ���ȡ�ų��Ƶ�����
��������
���أ�1  
ע�⣺�洢λ����myMEMSData��ƫ����HMC5883DF
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
������float HMC5883LDataProcess(u8 D1,u8 D2)  //d1��λ��D2��λ
���ܣ��ų��Ƶ����ݴ����ӿں���
������D1:���ݸ�λ��D2�����ݵ�λ
���أ���õĸ���ֵ
ע�⣺
*/
float HMC5883LDataProcess(u8 D1,u8 D2)  //d1��λ��D2��λ
{
	float fuck;
	unsigned int temp=D1;
	temp=temp<<8;
	temp+=D2;
	signed int temp2=(signed int)temp;
	fuck= (float)(temp2)*0.00092;  //��˹��1W gause ==1T
	return fuck;
}

/*
������u8 HMC5883L(float* x,float* y,float* z)
����:  �ų��Ƶ����ݻ�ú���
������float* x,float* y,float* z�ֱ�洢��ǰ��X,Y��Z������ٶ�
���أ�1
ע�⣺
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