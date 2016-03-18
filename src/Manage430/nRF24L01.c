#include "config.h"
/////妈妈的，本来不想用这么多宏定义的，无所谓了
#define nRF24L01_CE BIT0//P4.0
#define nRF24L01_CSN BIT1//P4.1
#define nRF24L01_SCK BIT3//P3.3
#define nRF24L01_MOSI BIT1//P3.1
#define nRF24L01_MISO BIT2//P3.2
#define nRF24L01_IRQ BIT4//P1.4
//
//
#define nRF24L01_CE_DIR P4DIR
#define nRF24L01_CSN_DIR P4DIR
#define nRF24L01_SCK_DIR P3DIR
#define nRF24L01_MOSI_DIR P3DIR
#define nRF24L01_MISO_DIR P3DIR
#define nRF24L01_IRQ_DIR P1DIR
//
#define nRF24L01_CE_OutPort P4OUT
#define nRF24L01_CSN_OutPort P4OUT
#define nRF24L01_SCK_OutPort P3OUT
#define nRF24L01_MOSI_OutPort P3OUT
#define nRF24L01_MISO_InPort P3IN
#define nRF24L01_IRQ_InPort P1IN

#define nRF24L01_CE_OutDIR() setbit(nRF24L01_CE_DIR,nRF24L01_CE)

#define nRF24L01_SCK_OutDIR() setbit(nRF24L01_SCK_DIR,nRF24L01_SCK)
#define nRF24L01_MOSI_OutDIR() setbit(nRF24L01_MOSI_DIR,nRF24L01_MOSI)
#define nRF24L01_MISO_InDIR() clrbit(nRF24L01_MISO_DIR,nRF24L01_MISO)
#define nRF24L01_IRQ_InDIR() clrbit(nRF24L01_IRQ_DIR,nRF24L01_IRQ)
//


#define nRF24L01_Set_CE() setbit(nRF24L01_CE_DIR,nRF24L01_CE)
#define nRF24L01_Clear_CE() clrbit(nRF24L01_CE_DIR,nRF24L01_CE)
#define nRF24L01_Set_SCK() setbit(nRF24L01_SCK_OutPort,nRF24L01_SCK)
#define nRF24L01_Clear_SCK() clrbit(nRF24L01_SCK_OutPort,nRF24L01_SCK)
#define nRF24L01_Set_MOSI() setbit(nRF24L01_MOSI_OutPort,nRF24L01_MOSI)
#define nRF24L01_Clear_MOSI() clrbit(nRF24L01_MOSI_OutPort,nRF24L01_MOSI)
//
//SPI Commands
#define nRF24L01_R_REGISTER 0x00
#define nRF24L01_W_REGISTER 0x20
#define nRF24L01_R_RX_PAYLOAD 0x61
#define nRF24L01_W_TX_PAYLOAD 0xA0
#define nRF24L01_FLUSH_TX 0xE1
#define nRF24L01_FLUSH_RX 0xE2
#define nRF24L01_REUSE_TX_PL 0xE3

#define nRF24L01_NOP 0xFF
//
//
//
//
//
//Register Definitions
#define nRF24L01_CONFIG 0x00
#define nRF24L01_EN_AA 0x01
#define nRF24L01_EN_RXADDR 0x02
#define nRF24L01_SETUP_AW 0x03
#define nRF24L01_SETUP_RETR 0x04
#define nRF24L01_RF_CH 0x05
#define nRF24L01_RF_SETUP 0x06
#define nRF24L01_STATUS 0x07
#define nRF24L01_OBSERVE_TX 0x08
#define nRF24L01_CD 0x09
#define nRF24L01_RX_ADDR_P0 0x0A
#define nRF24L01_RX_ADDR_P1 0x0B
#define nRF24L01_RX_ADDR_P2 0x0C
#define nRF24L01_RX_ADDR_P3 0x0D
#define nRF24L01_RX_ADDR_P4 0x0E
#define nRF24L01_RX_ADDR_P5 0x0F
#define nRF24L01_TX_ADDR 0x10
#define nRF24L01_RX_PW_P0 0x11
#define nRF24L01_RX_PW_P1 0x12
#define nRF24L01_RX_PW_P2 0x13
#define nRF24L01_RX_PW_P3 0x14
#define nRF24L01_RX_PW_P4 0x15
#define nRF24L01_RX_PW_P5 0x16
#define nRF24L01_FIFO_STATUS 0x17


void nRF24L01_CSN_OutDIR(u8 ChannelID)
{
   P4DIR|=BIT1;
}


void nRF24L01_Set_CSN(u8 ChannelID) 
{
  P4OUT|=BIT1;
  
}
void nRF24L01_Clear_CSN(u8 ChannelID) 
{
  P4OUT&=~BIT1;
}



void Init_nRF24L01_IO()
{
	nRF24L01_CE_OutDIR();
        for(u8 i=0;i<RFMODULENUM;i++)
        {
	   nRF24L01_CSN_OutDIR(i);
        }
	nRF24L01_SCK_OutDIR();
	nRF24L01_MOSI_OutDIR();
	nRF24L01_MISO_InDIR();
	nRF24L01_IRQ_InDIR();

	//
	nRF24L01_Clear_CE();
         for(u8 i=0;i<RFMODULENUM;i++)
        {
          nRF24L01_Set_CSN(i);
	
        }
	
	nRF24L01_Clear_SCK();
	nRF24L01_Clear_MOSI();
	//   nRF24L01_IRQ_IE|= nRF24L01_IRQ;  //无线中断脚使能
	//  nRF24L01_IRQ_IES|=nRF24L01_IRQ; //下降沿使能
}
//
//
//function SpiWrite();
/******************************************************************************************/
void nRF24L01SpiWrite(unsigned char byte)
{
	unsigned char i;
       
	nRF24L01_Clear_SCK();
	//delay_us(1);
	for (i=0;i<8;i++) // Setup byte circulation bits
	{
		if ((byte&BIT7)==BIT7) // Put DATA_BUF.7 on data line
			nRF24L01_Set_MOSI(); //MOSI=1;

		else
			nRF24L01_Clear_MOSI(); //MOSI=0;
		nRF24L01_Set_SCK(); // Set clock line high
		//delay_us(1);
		byte=byte<<1;
		nRF24L01_Clear_SCK(); // Set clock line low
		//delay_us(1);
	}
	//delay_us(1);
}
//
//
//function SpiRead();
/*****************************************************************************************/
unsigned char nRF24L01SpiRead()
{
	unsigned char i;
	unsigned char temp=0;
	nRF24L01_Clear_SCK();
	//delay_us(1);
	for (i=0;i<8;i++) // Setup byte circulation bits
	{
		nRF24L01_Set_SCK(); // Set clock line high
		//delay_us(1);
		temp=temp<<1; // Right shift DATA_BUF
		if ((nRF24L01_MISO_InPort&nRF24L01_MISO)==nRF24L01_MISO)
		{temp|=1;} // Read data
		nRF24L01_Clear_SCK(); // Set clock line low
		//delay_us(1);
	}
	//delay_us(1);
	return temp; // Return function parameter
}

//
void nRF24L01_Flush_TX_FIFO(u8 channelID)//Clear TX FIFO
{
	nRF24L01_Set_CSN(channelID);
	nRF24L01_Clear_CSN(channelID);
	nRF24L01SpiWrite(nRF24L01_FLUSH_TX);
	nRF24L01_Set_CSN(channelID);
}
//
//
void nRF24L01_Flush_RX_FIFO(u8 channelID)//Clear RX FIFO
{
	nRF24L01_Set_CSN(channelID);
	nRF24L01_Clear_CSN(channelID);
	nRF24L01SpiWrite(nRF24L01_FLUSH_RX);
	nRF24L01_Set_CSN(channelID);
}
//
//
void nRF24L01SpiWriteReg(u8 channelID,unsigned char SpiCommand,unsigned char Content)
{
	nRF24L01_Set_CSN(channelID);
	nRF24L01_Clear_CSN(channelID);
	nRF24L01SpiWrite(SpiCommand);
	nRF24L01SpiWrite(Content);
	nRF24L01_Set_CSN(channelID);
}
//
void nRF24L01_RxWaySet(u8 channelID)//Setup1  RX方向
{
	nRF24L01SpiWriteReg(channelID,nRF24L01_W_REGISTER+nRF24L01_CONFIG,0x3f);//Reflect RX_DR
	//Mask interrupt caused by TX_DS;
	//Mask interrupt caused by MAX_RT;
	//Enable CRC;
	//CRC encoding scheme 2 bytes;
	//POWER UP;
	//PTX;
	delay_us(5);  //给点时间
}
void nRF24L01_TxWaySet(u8 channelID)
{
	nRF24L01SpiWriteReg(channelID,nRF24L01_W_REGISTER+nRF24L01_CONFIG,0x3e);//Reflect RX_DR
	//Mask interrupt caused by TX_DS;
	//Mask interrupt caused by MAX_RT;
	//Enable CRC;
	//CRC encoding scheme 2 bytes;
	//POWER UP;
	//PTX;
	delay_us(5);  //给点时间

}
//
void nRF24L01_Set_Rx_Address(u8 channelID,unsigned char RX_Address_Pipex,const unsigned char *Address,unsigned char Length)
	//Address
{
	unsigned char i=0;
	nRF24L01_Set_CSN(channelID);
	nRF24L01_Clear_CSN(channelID);
	nRF24L01SpiWrite(RX_Address_Pipex);
	for(i=0;i<Length;i++)
	{
		nRF24L01SpiWrite(*Address);
		Address++;
	}
	nRF24L01_Set_CSN(channelID);
}

void nRF24L01_Set_Tx_Address(u8 channelID,unsigned char TX_AddressReg10,const unsigned char *Address,unsigned char Length)//Remote
	//Address
{
	unsigned char i=0;
	nRF24L01_Set_CSN(channelID);
	nRF24L01_Clear_CSN(channelID);
	nRF24L01SpiWrite(TX_AddressReg10);
	for(i=0;i<Length;i++)
	{
		nRF24L01SpiWrite(*Address);
		Address++;
	}
	nRF24L01_Set_CSN(channelID);
}
//
//
void nRF24L01_Read_Rx_Payload(u8 channelID,unsigned char *DataBuff)//Payload Out
{
	unsigned char i=0;
	nRF24L01_Set_CSN(channelID);
	nRF24L01_Clear_CSN(channelID);
	nRF24L01SpiWrite(nRF24L01_R_RX_PAYLOAD);
	for(i=0;i<PACKETLENGTH;i++)
	{
		*DataBuff=nRF24L01SpiRead();

		DataBuff++;
	}
	nRF24L01_Set_CSN(channelID);
}

//  暂时取消最大长度限制void nRF24L01_Write_Tx_Payload(unsigned char *DataByte, unsigned char Length)//Payload IN
void nRF24L01_Write_Tx_Payload(u8 channelID,unsigned char *DataByte)
{


	nRF24L01_Set_CSN(channelID);
	nRF24L01_Clear_CSN(channelID);
	nRF24L01SpiWrite(nRF24L01_W_TX_PAYLOAD);

	for(unsigned char i=0;i<PACKETLENGTH;i++)
	{

		nRF24L01SpiWrite(*DataByte);
		DataByte++;		
	}

	nRF24L01_Set_CSN(channelID);
}

//
//
void nRF24L01_Transmit_Data()//Transmit Pulse
{
	delay_ms(1);
	nRF24L01_Set_CE();
	delay_ms(1);
	nRF24L01_Clear_CE();

}
//
//
void nRF24L01_Reset_Tx_DS(u8 channelID)
{
	nRF24L01SpiWriteReg(channelID,nRF24L01_W_REGISTER+nRF24L01_STATUS,0x2e);///
}
//
//
void nRF24L01_Reset_Rx_DS(u8 channelID)
{
	nRF24L01SpiWriteReg(channelID,nRF24L01_W_REGISTER+nRF24L01_STATUS,0x4e);///
}

void SetRFChannel(u8 channelID,u8 ID)  //id  0-7
{
	nRF24L01SpiWriteReg(channelID,nRF24L01_W_REGISTER+nRF24L01_RF_CH,10*ID+2);//RF Channel.
}

void nRF24L01_Setup2(u8 channelID)//Setup2

{
	nRF24L01SpiWriteReg(channelID,nRF24L01_W_REGISTER+nRF24L01_EN_AA,0x00);////Disable auto_acknowledgment,6 pipes
	nRF24L01SpiWriteReg(channelID,nRF24L01_W_REGISTER+nRF24L01_EN_RXADDR,0x01);//Enabled RX Addresses.Enable data pipe 0
	nRF24L01SpiWriteReg(channelID,nRF24L01_W_REGISTER+nRF24L01_SETUP_AW,0x01);//RX/TX Address field width 3 bytes.
	nRF24L01SpiWriteReg(channelID,nRF24L01_W_REGISTER+nRF24L01_SETUP_RETR,0x00);//Re-Transmit disabled.

	SetRFChannel(channelID,0);  


	nRF24L01SpiWriteReg(channelID,nRF24L01_W_REGISTER+nRF24L01_RF_SETUP,0x06);//Air Data Rate 2Mbps.RF_PWR:0dBm.LNA Gain 0.///00001110


	//2011年5月10日修改到2Mbps
	nRF24L01SpiWriteReg(channelID,nRF24L01_W_REGISTER+nRF24L01_RX_PW_P0,PACKETLENGTH);//Pipe0 3 Bytes Payload.  自己修改为24
	nRF24L01SpiWriteReg(channelID,nRF24L01_W_REGISTER+nRF24L01_RX_PW_P1,0x00);//Pipe1
	nRF24L01SpiWriteReg(channelID,nRF24L01_W_REGISTER+nRF24L01_RX_PW_P2,0x00);//Pipe2
	nRF24L01SpiWriteReg(channelID,nRF24L01_W_REGISTER+nRF24L01_RX_PW_P3,0x00);//Pipe3
	nRF24L01SpiWriteReg(channelID,nRF24L01_W_REGISTER+nRF24L01_RX_PW_P4,0x00);//Pipe4
	nRF24L01SpiWriteReg(channelID,nRF24L01_W_REGISTER+nRF24L01_RX_PW_P5,0x00);//Pipe5
}


void SetStandbyMode()
{
	nRF24L01_Clear_CE();
}

void WirelessInit()
{

	Init_nRF24L01_IO();

        for(u8 channelID=0;channelID<RFMODULENUM;channelID++)
        {
	nRF24L01_Setup2(channelID); 
	nRF24L01_Set_Rx_Address(channelID,nRF24L01_W_REGISTER+nRF24L01_RX_ADDR_P0,Rx_Address,3);//   设定本方地址
	nRF24L01_Set_Tx_Address(channelID,nRF24L01_W_REGISTER+nRF24L01_TX_ADDR,Tx_Address,3);
        }

}
void WriteTxBuff(u8 channelID)   //无线发送数据
{      

	WriteTxBuffPtr(channelID,myMEMSData);

}\
void WriteTxBuffPtr(u8 channelID,u8* data)   //无线发送数据
{      

	Init_nRF24L01_IO();

	nRF24L01_TxWaySet(channelID);
	nRF24L01_Flush_TX_FIFO(channelID);//清空FIFO

	nRF24L01_Write_Tx_Payload(channelID,data);  
	

}

void W_PutStringPtr()   //无线发送数据
{
  for(u8 i=0;i<RFMODULENUM;i++)
  {
        nRF24L01_Transmit_Data();//启动发送，发送完成后进入Standby-I 模式
  }
	delay_us(10);
}
void RxWayConfig(u8 channelID)
{
	Init_nRF24L01_IO();
	nRF24L01_RxWaySet(channelID);
	nRF24L01_Flush_RX_FIFO(channelID);
	nRF24L01_Set_CE();
}



void ProcessReceivedData()
	///进入接收环节

{

	if((nRF24L01_IRQ_InPort&nRF24L01_IRQ)!=nRF24L01_IRQ)//如果有无线数据
	{
		OSLEDControl(2);
		nRF24L01_Reset_Rx_DS(0);//清标志位
		nRF24L01_Read_Rx_Payload(0,myReceiveBuff);//读取数据，数据内容可以在Debug 状态小查看
		nRF24L01_Flush_RX_FIFO(0);

               SendSensorData(myReceiveBuff);

	}






}

