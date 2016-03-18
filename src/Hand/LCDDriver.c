#include "config.h"
/*
LCDDriver.c
ELPOS2.0的彩屏驱动函数，器件:MZTH
Copyright (c) 2010，赵一鸣
buptzym@bupt.edu.cn
All rights reserved.
本程序仅供学习参考，不提供任何可靠性方面的担保；请勿用于商业目的
*/



DOTBYTE X_Witch=8;							//存下当前所选择的ASCII英文字库的字符点数X轴宽度
DOTBYTE Y_Witch=16;							//存下当前所选择的ASCII英文字库的字符点数Y轴高度
DOTBYTE X_Witch_cn=16;						//存下当前所选择的中文字库的字符点数X轴宽度
DOTBYTE Y_Witch_cn=16;						//存下当前所选择的中文字库的字符点数Y轴高度

 

unsigned char Send_Buffer[SEND_BUFFER_SIZE];
/******************************硬件驱动层******************************************/
//========================================================================
// 函数: void LCD_Initial(void)
// 描述: LCD模块初始化,在此初始化MCU用于控制模块的UART接口，以及一些用于控制
//			模块所必需要端口或其它硬件
// 参数: 无
// 返回: 无
// 备注: 模块上电后默认的波特率为9600
// 版本:
//      2010/03/04      First version
//========================================================================

void LCD_Initial(void)
{
	P5DIR |= BIT4;				//控制模块复位
	P5OUT&=~BIT4;
	delay_ms(600);
	P5OUT|=BIT4;
	delay_ms(100);
	
	
}

/****************************底层运用驱动**************************/
void UART_SendOneByte(unsigned char Dat)
{
	while (!(IFG1 & UTXIFG0));    //等待发送寄存器为空         
	TXBUF0 = Dat; 
}
void PutString_Test(unsigned char *ptr)
{
	while(*ptr != '\0')
	{
		UART_SendOneByte(*ptr++);                     // 发送数据
	}
      
}
void UART_SendPacked(unsigned char Command,unsigned char * p,unsigned char num)
{
	//unsigned char Index=0;
	unsigned char check=0;
	
	
	/*UART_TX_Buffer[Index++] = 0x55;
	UART_TX_Buffer[Index++] = num+1;
	UART_TX_Buffer[Index++] = Command;
	check = Command;
	while(num--)
	{
	UART_TX_Buffer[Index++] = *p;
	check += *p++;
	}
	UART_TX_Buffer[Index++] = check;
	UART_TX_Buffer[Index++] = 0xaa;*/
	UART_SendOneByte(0x55);
	UART_SendOneByte(num+1);
	UART_SendOneByte(Command);
	check = Command;
	while(num--)
	{
		UART_SendOneByte(*p);
		check += *p++;
	}
	UART_SendOneByte(check);
	UART_SendOneByte(0xaa);
	
	
}

//========================================================================
// 文件名: LCD_Dis.c
// 作  者: Xinqiang Zhang(email: Xinqiang@Mzdesign.com.cn)
//			www.Mzdesign.com.cn
// 日  期: 2010/03/04
// 描  述: 通用版LCD用户接口层程序集
//
// 参  考: 请参考具体显示器的硬件描述说明书或者是DataSheet,并以此来编写加速
//			版接口程序;本程序适用于STM32系列MCU，对应的显示模块为MzTH24 V10
// 版  本:
//      2010/03/04      First version    Mz Design
//========================================================================

/*
LCDBYTE BMP_Color;
LCDBYTE Char_Color;

  BYTE	Font_type;
  BYTE	Font_Cover;								//
LCDBYTE	Char_BackColor;						 */






//========================================================================
// 函数: void FontSet_cn(LCDBYTE Font_NUM,LCDBYTE Color)
// 描述: 汉字库选择
// 参数: Font_NUM 	汉字字库的资源序列号（请参考具体使用时，资源中的汉字库序号）
//		 Color  	文本颜色,作用于汉字显示以及英文字符显示等字符显示的操作 
// 返回: 无
// 备注: 
// 版本:
//      2010/03/04      First version
//========================================================================
void FontSet_cn(LCDBYTE Font_NUM,LCDBYTE Color)
{
	Send_Buffer[0] = Font_NUM>>8;
	Send_Buffer[1] = (unsigned char) Font_NUM;
	Send_Buffer[2] = Color>>8;
	Send_Buffer[3] = (unsigned char) Color;
	UART_SendPacked(0x83,Send_Buffer,4);
	switch(Font_NUM)
	{
	case 0:					//选择模块所加载资源中的中文字库第1号
		X_Witch_cn = 12;
		Y_Witch_cn = 12;
		break;
	case 1:					//选择模块所加载资源中的中文字库第1号
		X_Witch_cn = 16;
		Y_Witch_cn = 16;
		break;
	case 2:					//选择模块所加载资源中的中文字库第1号
		X_Witch_cn = 24;
		Y_Witch_cn = 24;
		break;
	default:break;
	}
}
//========================================================================
// 函数: void BuadRateSet(unsigned int Br) 
// 描述: 设置模块波特率
// 参数: Br 要设置的波特率
// 返回: 无
// 备注: 模块上电后默认的波特率为9600
// 版本:
//      2010/03/04      First version
//========================================================================
void BuadRateSet(unsigned long Br) 
{
	Send_Buffer[0] = (unsigned char)(Br>>24);
	Send_Buffer[1] = (unsigned char)(Br>>16);
	Send_Buffer[2] = (unsigned char)(Br>>8);
	Send_Buffer[3] = (unsigned char) Br;

	UART_SendPacked(0x8B,Send_Buffer,4);
}
//========================================================================
// 函数: void FontSet_rs(int Font_NUM,unsigned int Color)
// 描述: 英文字体设置，该功能为设置模块所加载的资源中的英文字库
// 参数: Font_NUM 	字体选择,模块加载的资源中英文字库所对应的资源序号
//		 Color  	文本颜色,作用于汉字显示以及英文字符显示等字符显示的操作
// 返回: 无
// 备注: 
// 版本:
//      2010/03/04      First version
//========================================================================
void FontSet_rs(LCDBYTE Font_NUM,LCDBYTE Color)
{
	Send_Buffer[0] = Font_NUM>>8;
	Send_Buffer[1] = (unsigned char) Font_NUM;
	Send_Buffer[2] = Color>>8;
	Send_Buffer[3] = (unsigned char) Color;
	UART_SendPacked(0x82,Send_Buffer,4);
	switch(Font_NUM)
	{
	case 3:					//选择模块所加载资源中的ASCII英文字库第0号
		X_Witch = 8;
		Y_Witch = 16;
		break;
	case 4:					//选择模块所加载资源中的ASCII英文字库第0号
		X_Witch = 20;
		Y_Witch = 40;
		break;
	default:break;
	}
}

//========================================================================
// 函数: void FontSet(int Font_NUM,unsigned int Color)
// 描述: 英文字体设置  选择模块中固件所包含的英文字库
// 参数: Font_NUM 	字体选择,以模块固件的字库为准
//		 Color  	文本颜色,作用于汉字显示以及英文字符显示等字符显示的操作  
// 返回: 无
// 备注: 
// 版本:
//      2010/03/04      First version
//========================================================================
void FontSet(LCDBYTE Font_NUM,LCDBYTE Color)
{
	Send_Buffer[0] = 0x00;//Font_NUM>>8;
	Send_Buffer[1] = (unsigned char) Font_NUM;
	Send_Buffer[2] = Color>>8;
	Send_Buffer[3] = (unsigned char) Color;
	UART_SendPacked(0x81,Send_Buffer,4);
	switch(Font_NUM)
	{
	case 0:					//选择模块固件自带ASCII英文字库第0号
		X_Witch = 6;
		Y_Witch = 10;
		break;
	case 1:					//选择模块固件自带ASCII英文字库第1号
		X_Witch = 8;
		Y_Witch = 16;
		break;
	case 2:					//选择模块固件自带ASCII英文字库第2号
		X_Witch = 10;
		Y_Witch = 20;
		break;
	case 3:					//选择模块固件自带ASCII英文字库第3号
		X_Witch = 16;
		Y_Witch = 32;
		break;
	default:break;
	}
}

//========================================================================
// 函数: void NumberDis(LCDBYTE x,LCDBYTE y,signed int Num,unsigned char len,unsigned char type)  
// 描述: 直接数字显示
// 参数: x	要显示的数字的左上角x轴起始位置
//		 y	要显示的数字的左上角y轴起始位置
//		 Num	要显示的数字
//		 len	要显示的数字的十进制位的个数
//		 type	显示模式
//			0: 全显示
//			1：靠左显示
//			2：靠右显示
// 返回: 无
// 备注: 使用当前设置的英文字体，并受字符覆盖模式控制
// 版本:
//      2010/03/04      First version
//========================================================================
void NumberDis(LCDBYTE x,LCDBYTE y,signed long Num,unsigned char len,unsigned char type) 
{
	unsigned char *temp;
	Send_Buffer[0] = x>>8;
	Send_Buffer[1] = (unsigned char) x;
	Send_Buffer[2] = y>>8;
	Send_Buffer[3] = (unsigned char) y;
	temp = (unsigned char*)&Num;
	Send_Buffer[7] = *temp++;
	Send_Buffer[6] = *temp++;
	Send_Buffer[5] = *temp++;
	Send_Buffer[4] = *temp;
	Send_Buffer[8] = len;
	Send_Buffer[9] = type;
	
	UART_SendPacked(0x0a,Send_Buffer,10);
}

//========================================================================
// 函数: void PutBitmap(LCDBYTE x,LCDBYTE y,unsigned short Index,LCDBYTE Color)  
// 描述: 显示一个模块资源中的位图在指定位置上
// 参数: x  X轴坐标     y  Y轴坐标
//		 Index  位图资源在资源当中的序列号 
//		 Color	位图显示时的效果
//			0x0000：正常显示位图
//			非零:	按指定的色彩使位图偏色显示 
// 返回: 无
// 备注: 
// 版本:
//      2010/03/04      First version
//========================================================================
void PutBitmap(LCDBYTE x,LCDBYTE y,unsigned short Index,LCDBYTE Color) 
{
	Send_Buffer[0] = x>>8;
	Send_Buffer[1] = (unsigned char) x;
	Send_Buffer[2] = y>>8;
	Send_Buffer[3] = (unsigned char) y;
	Send_Buffer[4] = Index>>8;
	Send_Buffer[5] = (unsigned char) Index;
	if(Color==0)
		UART_SendPacked(0x09,Send_Buffer,6);
	else
	{
		Send_Buffer[6] = Color>>8;
		Send_Buffer[7] = (unsigned char)Color;
		UART_SendPacked(0x0d,Send_Buffer,8);
	}
     
}
//========================================================================
// 函数: void PutChar_cn(unsigned char x,unsigned char y,unsigned short * GB) 
// 描述: 写入一个二级汉字库汉字
// 参数: x  X轴坐标     y  Y轴坐标
//		 a  GB码  
// 返回: 无
// 备注: 请注意MCU的大小端
// 版本:
//      2010/03/04      First version
//========================================================================

void PutChar_cn(LCDBYTE x,LCDBYTE y,unsigned char * GB) 
{
	Send_Buffer[0] = x>>8;
	Send_Buffer[1] = (unsigned char) x;
	Send_Buffer[2] = y>>8;
	Send_Buffer[3] = (unsigned char) y;
	Send_Buffer[4] = *(GB++);		//传送二级字库中汉字GB码的高八位值
	Send_Buffer[5] = *GB;	//传送二级字库中汉字GB码的低八位值
	UART_SendPacked(0x08,Send_Buffer,6);
}

//========================================================================
// 函数: void PutString_cn(unsigned char x,unsigned char y,unsigned short *p)
// 描述: 在x、y为起始坐标处写入一串汉字字符
// 参数: x  X轴坐标     y  Y轴坐标
//		 p  要显示的字符串  
// 返回: 无
// 备注: 同PutChar_cn中的解释
// 版本:
//      2010/03/04      First version
//========================================================================



//========================================================================
void PutString_cn(LCDBYTE x,LCDBYTE y,unsigned char *p)
{
	unsigned char Index;
	Send_Buffer[0] = x>>8;
	Send_Buffer[1] = (unsigned char) x;
	Send_Buffer[2] = y>>8;
	Send_Buffer[3] = (unsigned char) y;
	Index = 4;
	while(*p!='\0'&&Index<68)
	{
		Send_Buffer[Index++] = *p++;
		//Send_Buffer[Index++] = (unsigned char)((*p++)>>8);
	}
	UART_SendPacked(0x0c,Send_Buffer,Index);
}
//========================================================================
// 函数: void FontMode(BYTE Mode,LCDBYTE FontBackColor) 
// 描述: 设置字符显示的模式,并设置背景色
// 参数: Mode	0: 字符显示时仅对字符的有效点进行显示操作,也就是不作背景覆盖
//					为叠加模式
//				1: 覆盖模式
//		FontBackColor	设置覆盖模式时,字符的背景色 
// 返回: 无
// 备注: 仅对字符显示有效
// 版本:
//      2010/03/04      First version
//========================================================================
void FontMode(BYTE Mode,LCDBYTE FontBackColor)
{
	Send_Buffer[0] = Mode;//>>8;
	//	Send_Buffer[1] = (unsigned char) Font_NUM;
	Send_Buffer[1] = FontBackColor>>8;
	Send_Buffer[2] = (unsigned char) FontBackColor;
	UART_SendPacked(0x85,Send_Buffer,3);
}
//========================================================================
// 函数: void PutChar(DOTBYTE x,DOTBYTE y,char a) 
// 描述: 写入一个标准字符
// 参数: x  X轴坐标     y  Y轴坐标
//		 a  要显示的字符在字库中的偏移量  
// 返回: 无
// 备注: ASCII字符可直接输入ASCII码即可
// 版本:
//      2010/03/04      First version
//========================================================================
void PutChar(DOTBYTE x,DOTBYTE y,char a)       
{
	Send_Buffer[0] = x>>8;
	Send_Buffer[1] = (unsigned char) x;
	Send_Buffer[2] = y>>8;
	Send_Buffer[3] = (unsigned char) y;
	Send_Buffer[4] = (unsigned char) a;
	UART_SendPacked(0x07,Send_Buffer,5);
}

//========================================================================
// 函数: void PutString(DOTBYTE x,DOTBYTE y,char *p)
// 描述: 在x、y为起始坐标处写入一串标准字符
// 参数: x  X轴坐标     y  Y轴坐标
//		 p  要显示的字符串  
// 返回: 无
// 备注: 仅能用于自带的ASCII字符串显示
// 版本:
//      2010/03/04      First version
//========================================================================
void PutString(DOTBYTE x,DOTBYTE y,u8 *p)
{
	unsigned char Index;
	Send_Buffer[0] = x>>8;
	Send_Buffer[1] = (unsigned char) x;
	Send_Buffer[2] = y>>8;
	Send_Buffer[3] = (unsigned char) y;
	Index = 4;
	while(*p&&Index<68)
	{
		Send_Buffer[Index++] = *p++;
	}
	UART_SendPacked(0x0b,Send_Buffer,Index);
}
//========================================================================
// 函数: void SetPaintMode(BYTE Mode,LCDBYTE Color)
// 描述: 绘图模式设置
// 参数: Mode 绘图模式    Color  像素点的颜色,相当于前景色  
// 返回: 无
// 备注: Mode无效
// 版本:
//      2010/03/04      First version
//========================================================================
void SetPaintMode(BYTE Mode,LCDBYTE Color)
{
	//	LCDBYTE temp;
	//	temp = BMP_Color;
	Mode = Mode;//Plot_Mode = Mode;		//仅仅是为了保持与其它驱动的一至性，绘图模式在该版驱动中未用
	//	BMP_Color = Color;
	Send_Buffer[0] = Color>>8;
	Send_Buffer[1] = (unsigned char) Color;
	UART_SendPacked(0x84,Send_Buffer,2);
	
}
//========================================================================
// 函数: void PutPixel(DOTBYTE x,DOTBYTE y)
// 描述: 在x、y点上绘制一个前景色的点
// 参数: x  X轴坐标     y  Y轴坐标
// 返回: 无
// 备注: 使用前景色
// 版本:
//      2010/03/04      First version
//========================================================================
void PutPixel(DOTBYTE x,DOTBYTE y)
{
	Send_Buffer[0] = x>>8;
	Send_Buffer[1] = (unsigned char) x;
	Send_Buffer[2] = y>>8;
	Send_Buffer[3] = (unsigned char) y;
	UART_SendPacked(0x01,Send_Buffer,4); 	
}
//========================================================================
// 函数: void Line(LCDBYTE s_x,LCDBYTE s_y,LCDBYTE e_x,LCDBYTE e_y)
// 描述: 在s_x、s_y为起始坐标，e_x、e_y为结束坐标绘制一条直线
// 参数: x  X轴坐标     y  Y轴坐标
// 返回: 无
// 备注: 使用前景色
// 版本:
//      2010/03/04      First version
//========================================================================
void Line(LCDBYTE s_x,LCDBYTE s_y,LCDBYTE e_x,LCDBYTE e_y)
{  
	Send_Buffer[0] = s_x>>8;
	Send_Buffer[1] = (unsigned char) s_x;
	Send_Buffer[2] = s_y>>8;
	Send_Buffer[3] = (unsigned char) s_y;
	Send_Buffer[4] = e_x>>8;
	Send_Buffer[5] = (unsigned char) e_x;
	Send_Buffer[6] = e_y>>8;
	Send_Buffer[7] = (unsigned char) e_y;
	UART_SendPacked(0x02,Send_Buffer,8);   
}
//========================================================================
// 函数: void Circle(DOTBYTE x,DOTBYTE y,DOTBYTE r,BYTE Mode)
// 描述: 以x,y为圆心R为半径画一个圆(mode = 0) or 圆面(mode = 1)
// 参数: 
// 返回: 无
// 备注: 画圆函数执行较慢，如果MCU有看门狗，请作好清狗的操作
// 版本:
//      2010/03/04      First version
//========================================================================
void Circle(DOTBYTE x,DOTBYTE y,DOTBYTE r,BYTE Mode)
{
	Send_Buffer[0] = x>>8;
	Send_Buffer[1] = (unsigned char) x;
	Send_Buffer[2] = y>>8;
	Send_Buffer[3] = (unsigned char) y;
	Send_Buffer[4] = r>>8;
	Send_Buffer[5] = (unsigned char) r;
	if(Mode==0)
		UART_SendPacked(0x05,Send_Buffer,6);
	else
        {
		UART_SendPacked(0x06,Send_Buffer,6);
            //    delay_ms(10);
        }
        
}	

//========================================================================
// 函数: void Rectangle(DOTBYTE left, DOTBYTE top, DOTBYTE right, 
//						DOTBYTE bottom, BYTE Mode)
// 描述: 以x,y为圆心R为半径画一个圆(mode = 0) or 圆面(mode = 1)
// 参数: left - 矩形的左上角横坐标，范围0到118
//		 top - 矩形的左上角纵坐标，范围0到50
//		 right - 矩形的右下角横坐标，范围1到119
//		 bottom - 矩形的右下角纵坐标，范围1到51
//		 Mode - 绘制模式，可以是下列数值之一：
//				0:	矩形框（空心矩形）
//				1:	矩形面（实心矩形）
// 返回: 无
// 备注: 
// 版本:
//      2010/03/04      First version
//========================================================================
void Rectangle(DOTBYTE left, DOTBYTE top, DOTBYTE right, DOTBYTE bottom, BYTE Mode)
{
	Send_Buffer[0] = left>>8;
	Send_Buffer[1] = (unsigned char) left;
	Send_Buffer[2] = top>>8;
	Send_Buffer[3] = (unsigned char) top;
	Send_Buffer[4] = right>>8;
	Send_Buffer[5] = (unsigned char) right;
	Send_Buffer[6] = bottom>>8;
	Send_Buffer[7] = (unsigned char) bottom;
	if(Mode==0)
		UART_SendPacked(0x03,Send_Buffer,8);
	else
		UART_SendPacked(0x04,Send_Buffer,8);
     
}
//========================================================================
// 函数: void ClrScreen(BYTE Mode)
// 描述: 清屏函数，执行全屏幕清除或填充前景色
// 参数: Mode   0:全屏除屏
//				1:全屏填充前景色
// 返回: 无
// 备注: 
// 版本:
//      2010/03/04      First version
//========================================================================
void ClrScreen(BYTE Mode)
{
	if(Mode==0)
		Send_Buffer[0] = 0xaa;
	else Send_Buffer[0] = 0x55;
	UART_SendPacked(0x80,Send_Buffer,1);
}

//========================================================================
// 函数: void BackLightSet(unsigned short Gra)
// 描述: 设置当前背光亮度等级
// 参数: Gra   0~500
// 返回: 无
// 备注: 
// 版本:
//      2010/03/04      First version
//========================================================================
void BackLightSet(unsigned short Gra)
{
	Send_Buffer[0] = Gra>>8;
	Send_Buffer[1] = (unsigned char) Gra;
	UART_SendPacked(0x8A,Send_Buffer,2);	
   
}

//========================================================================
// 函数: void BackLightTo(unsigned short Gra)
// 描述: 设置背光亮度，并使模块由当前的背光亮度渐变到所设定的值
// 参数: Gra   0~500
// 返回: 无
// 备注: 
// 版本:
//      2010/03/04      First version
//========================================================================
void BackLightTo(unsigned short Gra)
{
	Send_Buffer[0] = Gra>>8;
	Send_Buffer[1] = (unsigned char) Gra;
	UART_SendPacked(0x89,Send_Buffer,2);	
        delay_ms(50);
}

//========================================================================
// 函数: void BackLightStep(unsigned char Step)
// 描述: 背光缓亮/暗的速度设置
// 参数: Step   5~100   数值越小，缓变的速度越快
// 返回: 无
// 备注: 
// 版本:
//      2010/03/04      First version
//========================================================================
void BackLightStep(unsigned char Step)
{
	Send_Buffer[0] = Step;
	UART_SendPacked(0x88,Send_Buffer,1);	
}

//========================================================================
// 函数: void LCDSetSleep(void)
// 描述: 设置模块进入省电模式
// 参数: 
// 返回: 无
// 备注: 
// 版本:
//      2010/03/04      First version
//========================================================================
void LCDSetSleep(void)
{
	Send_Buffer[0] = 0x5a;
	UART_SendPacked(0x8c,Send_Buffer,1);	
         delay_ms(100);
}
//========================================================================
// 函数: void LCDWakeup(void)
// 描述: 将模块从省电模式中唤醒
// 参数: 无
// 返回: 无
// 备注: 模块被唤醒后，最好等10ms左右再对模块进行操作
// 版本:
//      2010/03/04      First version
//========================================================================
void LCDWakeup(void)
{
	UART_SendOneByte(0x00);	
}


void Lcd_disp(unsigned int x,unsigned int y,unsigned char *p)
{
	
	unsigned char Index;
	u8 flag=0,s=1,b=0;
      
	u8 length=strlenExt(p);
	while(flag<length)
	{
		Send_Buffer[0] = x>>8;
		Send_Buffer[1] = (unsigned char) x;
		Send_Buffer[2] = y>>8;
		Send_Buffer[3] = (unsigned char) y;
		Index = 4;
                
	        while(flag<length&&*(p+flag)<0x80&&s==1)
		{
			Send_Buffer[Index++] = *(p+flag); 
			flag++;
			x += X_Witch;
                        if((x + X_Witch) >Dis_X_MAX)
			{
				x = 0;
				if((Dis_Y_MAX - y) < Y_Witch) break;
				else y += Y_Witch_cn;
                                s=0;
                              
			}
                          b=1;
			
		}
		if(b==1)
		{
			
			UART_SendPacked(0x0b,Send_Buffer,Index);
		}
		b=0,s=1;
                Send_Buffer[0] = x>>8;
		Send_Buffer[1] = (unsigned char) x;
		Send_Buffer[2] = y>>8;
		Send_Buffer[3] = (unsigned char) y;
		Index = 4;
		while(flag<length&&*(p+flag)>0x80&&s==1)
		{
			Send_Buffer[Index++] = *(p+flag); 
			Send_Buffer[Index++] = *(p+flag+1); 
			flag+=2;
			x += X_Witch_cn;
                        if((x + X_Witch_cn) >Dis_X_MAX)
			{
				x = 0;
                                s=0;
				if((Dis_Y_MAX - y) < Y_Witch_cn) break;
				else y += Y_Witch_cn;
			}
			
          
                        b=2;
		}
		if(b==2)
		{
			
			UART_SendPacked(0x0c,Send_Buffer,Index);
		}
	}
	
    
	
	
	
}

void FontSetTotal(LCDBYTE Color)
{
	FontSet( 1, Color);
	//选择中文字库,该函数只能选择模块所加载的资源中的中文汉字字库
	FontSet_cn( 1, Color);
}
void Lcd_disp_limlen(unsigned int x,unsigned int y,unsigned char *p,unsigned char Tlength)
{
  unsigned char Index;
	u8 flag=0,s=1,b=0;
       
	u8 length=strlenExt(p);
        if(Tlength<length)
          length=Tlength;
	while(flag<length)
	{
		Send_Buffer[0] = x>>8;
		Send_Buffer[1] = (unsigned char) x;
		Send_Buffer[2] = y>>8;
		Send_Buffer[3] = (unsigned char) y;
		Index = 4;
                
	        while(flag<length&&*(p+flag)<0x80&&s==1)
		{
			Send_Buffer[Index++] = *(p+flag); 
			flag++;
			x += X_Witch;
                        if((x + X_Witch) >Dis_X_MAX)
			{
				x = 0;
				if((Dis_Y_MAX - y) < Y_Witch) break;
				else y += Y_Witch_cn;
                                s=0;
                              
			}
                          b=1;
			
		}
		if(b==1)
		{
			
			UART_SendPacked(0x0b,Send_Buffer,Index);
		}
		b=0,s=1;
                Send_Buffer[0] = x>>8;
		Send_Buffer[1] = (unsigned char) x;
		Send_Buffer[2] = y>>8;
		Send_Buffer[3] = (unsigned char) y;
		Index = 4;
		while(flag<length&&*(p+flag)>0x80&&s==1)
		{
			Send_Buffer[Index++] = *(p+flag); 
			Send_Buffer[Index++] = *(p+flag+1); 
			flag+=2;
			x += X_Witch_cn;
                        if((x + X_Witch_cn) >Dis_X_MAX)
			{
				x = 0;
                                s=0;
				if((Dis_Y_MAX - y) < Y_Witch_cn) break;
				else y += Y_Witch_cn;
			}
			
          
                        b=2;
		}
		if(b==2)
		{
			
			UART_SendPacked(0x0c,Send_Buffer,Index);
		}
	}
	
  
}


void PutString_limit(DOTBYTE x,DOTBYTE y,u8 *p,u8 length)
{
	unsigned char Index,i=0;
	Send_Buffer[0] = x>>8;
	Send_Buffer[1] = (unsigned char) x;
	Send_Buffer[2] = y>>8;
	Send_Buffer[3] = (unsigned char) y;
	Index = 4;
	while(*p&&Index<68&&i<length)
	{
		Send_Buffer[Index++] = *p++;
                i++;
	}
	UART_SendPacked(0x0b,Send_Buffer,Index);
}
void BitRateConfig()
{
       BuadRateSet(115200);
        delay_ms(50);
     
  UTCTL0 |= SSEL1;                          // UCLK = SMCLK
  UBR00 = 0x45;                             // 8Mhz/115200 - 69.44
  UBR10 = 0x00;                             //
  UMCTL0 = 0x4A;                            // modulation
   
  delay_ms(40);
  
  
}
