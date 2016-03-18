


/**************************变量声明和宏定义*********************/

#define COLOR_Red		0xf800			//红
#define COLOR_Orange	0xfc00			//橙
#define COLOR_Yellow	0xffe0			//黄
#define COLOR_Green		0x07e0			//绿
#define COLOR_Cyan		0x07ff			//青
#define COLOR_Blue		0x001f			//蓝
#define COLOR_Purple	0x8010			//紫
#define COLOR_Black		0x0000			//黑色
#define COLOR_White		0xffff			//白色
#define COLOR_LBlue		0x8618			//淡蓝色
#define COLOR_Chess		0x8A65			//淡蓝色
#define LCD_X_MAX			320-1			//屏幕的X轴的物理宽度
#define LCD_Y_MAX			240-1			//屏幕的Y轴的物理宽度

#define Dis_X_MAX			LCD_X_MAX
#define Dis_Y_MAX			LCD_Y_MAX

#define LCD_INITIAL_COLOR	COLOR_Blue			//定义LCD屏初始化时的背景色





#define SEND_BUFFER_SIZE	128

typedef	unsigned short LCDBYTE;			//重定义有关LCD的,也即LCD当中的数据位宽
typedef unsigned short DOTBYTE;			//重定义有关LCD的,也即LCD的点阵数量
typedef signed short  DISWORD;			//重定义在LCD_Dis.c文件中一些中间处理的数据的宽度


typedef unsigned char  BYTE;
typedef unsigned short WORD;
typedef unsigned long  DWORD;
typedef unsigned int   BOOL;

//LCD 初始化函数
void UART_SendOneByte(unsigned char Dat);
extern void LCD_Initial(void);	//如有必要该函数还会包含端口初始化、复位等操作
//画直线函数，s_x、s_y为起始点，e_x、e_y为结束点
extern void Line(LCDBYTE s_x,LCDBYTE s_y,LCDBYTE e_x,LCDBYTE e_y);
void PutString_Test(unsigned char *ptr);
//绘图模式、当前绘图颜色设置
extern void SetPaintMode(BYTE Mode,LCDBYTE Color);
//选择英文(ASCII 字库),该函数只能选择模块内部的英文字库,具体请参考模块使用手册
extern void FontSet(DOTBYTE Font_NUM,LCDBYTE Color);
//选择英文(ASCII字库),该函数只能选择模块所加载的资源中的英文字库
extern void FontSet_rs(LCDBYTE Font_NUM,LCDBYTE Color);
//选择中文字库,该函数只能选择模块所加载的资源中的中文汉字字库
extern void FontSet_cn(LCDBYTE Font_NUM,LCDBYTE Color);
//显示一个汉字
extern void PutChar_cn(LCDBYTE x,LCDBYTE y,unsigned char  * GB) ;
//显示一个汉字字符串
extern void PutString_cn(LCDBYTE x,LCDBYTE y,unsigned char *p);
//设置字符显示的模式,并设置背景色
extern void FontMode(BYTE Mode,LCDBYTE FontBackColor);
//于x、y的坐标上写入一个标准字符
extern void PutChar(DOTBYTE x,DOTBYTE y,char a);
//于x、y的坐标为起始写入一串标准字符串
extern void PutString(DOTBYTE x,DOTBYTE y,u8 *p);

//于x、y的坐标为中心，绘制一个点
extern void PutPixel(DOTBYTE x,DOTBYTE y);
//于x、y的坐标为中心，绘制一个圆边或实心圆
extern void Circle(DOTBYTE x,DOTBYTE y,DOTBYTE r,BYTE mode);
//绘制一个以left、top和right、bottom为两个对角的矩形框或者实心矩形
extern void Rectangle(DOTBYTE left, DOTBYTE top, DOTBYTE right, DOTBYTE bottom, BYTE Mode);
//直接数字显示
extern void NumberDis(LCDBYTE x,LCDBYTE y,signed long Num,unsigned char len,unsigned char type);
//清屏函数，执行全屏幕清除或填充前景色
extern void ClrScreen(BYTE Mode);
//背光亮度设置
extern void BackLightSet(unsigned short Gra);

//背光亮度设置,并使模块的背光由当前亮度缓变到设置的亮度
extern void BackLightTo(unsigned short Gra);
//设置背光缓变的速度
extern void BackLightStep(unsigned char Step);
//设置模块进入省电模式
extern void LCDSetSleep(void);
//使模块退出省电模式
extern void LCDWakeup(void);
//显示一个模块资源中的位图在指定位置上

extern void PutBitmap(LCDBYTE x,LCDBYTE y,unsigned short Index,LCDBYTE Color);
void BuadRateSet(unsigned long Br);
extern void Lcd_disp(unsigned int x,unsigned int y,unsigned char *p);
void FontSetTotal(LCDBYTE Color);
void Lcd_disp_limlen(unsigned int x,unsigned int y,unsigned char *p,unsigned char Tlength);
void PutString_limit(DOTBYTE x,DOTBYTE y,u8 *p,u8 length);
void WideLine(u16 x,u16 y,u8 Wide);
void BitRateConfig();

extern DOTBYTE X_Witch;							//存下当前所选择的ASCII英文字库的字符点数X轴宽度
extern DOTBYTE Y_Witch;							//存下当前所选择的ASCII英文字库的字符点数Y轴高度
extern DOTBYTE X_Witch_cn;						//存下当前所选择的中文字库的字符点数X轴宽度
extern DOTBYTE Y_Witch_cn;						//存下当前所选择的中文字库的字符点数Y轴高度


