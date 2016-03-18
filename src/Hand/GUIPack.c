

/*
GUIPack.c
LCD图形控件库，针对铭正同创公司彩屏系列的LCD做了优化
Copyright (c) 2010，赵一鸣
buptzym@bupt.edu.cn
All rights reserved.
本程序仅供学习参考，不提供任何可靠性方面的担保；请勿用于商业目的
*/



#include "config.h"
#include "string.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
/*
函数：BoxGUI(unsigned char *title) 
功能：在LCD上产生覆盖屏幕的桌面
参数：无
*/
void BoxGUI(unsigned char *title)    //图形化界面窗口函数
{ 
	SetPaintMode(0,COLOR_Cyan);
	ClrScreen(1);
	SetPaintMode(0,OSColor);
	Rectangle(0,0,319,17,1);
	Rectangle(0,239,319,223,1);
	FontMode(0,1);
	FontSetTotal(COLOR_White);
	Lcd_disp(2,223,title);
	Lcd_disp(2,2,"xOS Super Edition");
        Lcd_disp(240,2,"ID:");
        ShowMountGUI(280,2,PCID,1,COLOR_White,1);
       
        
}
void DrawMovingBackColor(u16 x1,u16 y1,u16 x2,u16 y2,LCDBYTE COLOR,u8 Direction,u8 MoveEN)
{
	SetPaintMode(0,COLOR);
	if(x2-x1+y2-y1>350&&(MoveEN==0))
		Rectangle(x1,y1,x2,y2,1);
	else
	{
		switch(Direction)
		{
		case 1:  //下
			for (u8 i=y1;i<y2;i++)
			{
				Line(x1,i,x2,i);
				delay_ms(5);
			}
			break;
		case 2:  //上
			for (u8 i=y2;i>y1;i--)
			{
				Line(x1,i,x2,i);
			}
			break;
		case 3:  //右
			for (u8 i=x1;i<x2;i++)
			{
				Line(i,y1,i,y2);
			}
			break;
		case 4:  //左
			for (u8 i=x2;i>x1;i--)
			{
				Line(i,y1,i,y2);
			}
			break;
		}
	}
	
}

/*
函数：TaskBoxGUI_P(u16 x1,u16 y1,u16 x2,u16 y2,u8 *title)
功能：在LCD上产生可变大小的任务底框
参数：（x1,y1）左上角坐标，(X2,Y2)右下角坐标,title为窗口标题
*/
void TaskBoxGUI_P(u16 x1,u16 y1,u16 x2,u16 y2,u8 *title,u8 MoveEN)    //图形化界面窗口函数
{
	
	
	DrawMovingBackColor(x1+3,y1+3,x2+3,y2+3,COLOR_Black,1,MoveEN);
	
	
	
	Rectangle(x1,y1,x2,y2,0);
	SetPaintMode(0,OSColor);
	Rectangle(x1,y1+1,x2,y1+16,1);
	
	SetPaintMode(0,COLOR_White);
	
	Rectangle(x1+1,y1+Y_Witch+1,x2-1,y2-1,1);
	
	FontMode(0,COLOR_White);
	FontSetTotal(COLOR_White);
	Lcd_disp(x1,y1,title);
	FontSetTotal(COLOR_Black);
}
/*
函数：ShowMountGUI(u16 x,u16 y,float Mount,u8 Range,u16 Color,u8 Font)
功能：在LCD上显示可变位置的浮点值
参数：（x,y)数字左上角坐标值，mount要显示的浮点数，range对该数显示的长度，从左开始
Color显示颜色，Font字体类型，参见LCD使用说明
*/

void ShowMountGUI(u16 x,u16 y,float Mount,u8 Range,u16 Color,u8 Font)
{
	unsigned char MountTemp[8];
	
	sprintf((char*)MountTemp,"%f", Mount);
	FontSet(Font,Color);
	
	PutString_limit(x,y,MountTemp,Range);
	
	
}
/*
函数：u8  MenuGUI()  
功能：显示不同风格的菜单界面
参数：(全局变量)MenuType指出当前显示的界面风格，参见界面编辑的相关说明
返回值：固定为1
*/

u8  MenuGUI()    //图形化界面窗口函数
{
	switch(MenuType)
	{    
	case 0:
		MainMenuListGUI(1,3,200,64);
		break;
	case 1:
		MainMenuListGUI(1,8,0,25);
		break;
	case 2:
		MainMenuListGUI(3,2,100,90);
		break;
		
	}
	return 1;
}


/*
函数：void TaskBoxGUI(unsigned char *title)  
功能：在LCD上显示固定大小和位置的任务底框
参数：tilte:显示的标题
返回值：无
*/
void TaskBoxGUI(unsigned char *title)   
{ 
	TaskBoxGUI_P(7,27,307,197,title,0);
}

/*
函数：unsigned char myListGUI(u8 x,u8 y,u8 ** list, u8 mount)
功能：在LCD上显示固定大小，可变位置的列表型菜单界面
参数：（x,y）要显示坐标，**list存储列表的指针数组，mount，要显示的列表数量，
注意不能超过数组大小
返回值：0：表示用户强行退出，1-mount：返回当前用户的选择项（注意：从1开始）
*/
unsigned char myListGUI(u8 x,u8 y,u8 ** list,u8 *title, u8 MaxMount,u8 LRMaxMount,u8 UDMaxMount,u8 OneLRLength,u8 OneUDLength)
{
    u8  func_state=0, menu_flag=1,flag=1,UDListMount,TotalFreshEN,FreshEN=1;  //UDListMount实际的列表行数
	
	if(LRMaxMount==1)
		UDListMount=UDMaxMount;
	else
		UDListMount=MaxMount/LRMaxMount+1;
    
	if(func_state==0)
	{
		
		
		TaskBoxGUI_P(x+1,y+1,x+3+LRMaxMount*OneLRLength,y+Y_Witch_cn+UDListMount*OneUDLength+5,title,1);
		
		func_state=1;
	}
	while(func_state==1)
		
	{
		
		if(FreshEN==1)
		{
			SetPaintMode(0,COLOR_White); 
			Rectangle(x+2,y+2+Y_Witch_cn,x+2+LRMaxMount*OneLRLength,y+UDListMount*OneUDLength+11,1);
			SetPaintMode(0,COLOR_Black); 
		}
		
		for (u8 UDflag=0;UDflag<UDMaxMount;UDflag++)
		{
			for(u8 LRflag=0;LRflag<LRMaxMount;LRflag++)
			{
				if (menu_flag-1+UDflag*LRMaxMount+LRflag>=MaxMount)
				{
					break;
				}
				DrawTitle(x+1+LRflag*OneLRLength,y+Y_Witch_cn+4+UDflag*OneUDLength,list[menu_flag-1+UDflag*LRMaxMount+LRflag],LRflag+UDflag*LRMaxMount+1==flag?1:0,0,FreshEN);
			}//
		}
		
		
		
		FontMode(1,COLOR_White);
		FontSetTotal(COLOR_Black);
		switch(UpdownListInputControl(&menu_flag,&flag,MaxMount,LRMaxMount,UDMaxMount,0,&FreshEN,&TotalFreshEN))
		{
		case 0:
			OSTaskClose();
			func_state=2;
			return 0;
			
		case 1:
			func_state=2;
			break;
			
			
		}    
	}		
	return menu_flag+flag-1;
}
/*
函数：unsigned char MessageGui(unsigned char *title,unsigned char *message,unsigned char Type)
功能：在LCD上显示固定大小的是非型选择界面
参数：*title要显示的标题，message：要显示的信息，Type:显示风格 0：仅有确定项，用于提示，1：有是否两个选项，2：不经确认的提示项
返回值：1:用户选择是，0，用户选择否，若Type==0或2，返回值为1
*/
unsigned char MessageGui(unsigned char *title,unsigned char *message,unsigned char Type)
{
	if(Type==2)
	{
		TaskBoxGUI_P(65,70,253,144,title,1);
		
		FontSetTotal(COLOR_Black);
		Lcd_disp(68,86,message);
		delay_ms(400);
		return 1;
	}
	
	u8* temp[2];
	temp[0]="确认";
	temp[1]="取消";
	TaskBoxGUI_P(70,70-Y_Witch_cn,253,144,title,0);
	switch(myListGUI(80,72,temp,message,Type+1,2,1,4*X_Witch_cn,1*Y_Witch_cn))
	{
	case 0:
		return 0;
	case 1:
		return 1;
	case 2:
		return 0;
	}
	return 1;
	
	
}

/*
函数：unsigned char ListGUI(unsigned char** list,unsigned char *title,unsigned char mount)
功能：在LCD上显示固定大小和固定位置（在LCD中央）的列表型菜单界面
参数：参见myListGUI()的函数声明
返回值：参见myListGUI()的函数声明
*/
unsigned char ListGUI(unsigned char** list,unsigned char *title,unsigned char mount)
{
	u8 temp,WidthMax=0,LRMount,UDMount;
	for(u8 t=0;t<mount;t++)
	{
		temp=strlenExt(*(list+t));
		if(temp>WidthMax)
			WidthMax=temp;		
	}
	if(WidthMax>12)
	{
		LRMount=1;
		if(mount<5)
			UDMount=mount;
		else
			UDMount=5;
		
		
	}
	else
	{
		LRMount=2;
		UDMount=mount/2+mount%2;
	}
	
	
	return myListGUI(40,80,list,title,mount,LRMount,UDMount,(WidthMax+4)*X_Witch,24);
	
}
/*
函数：unsigned char  TextGUI(unsigned char *Text,unsigned char *title,unsigned char UpLimit,unsigned char DownLimit,u8 type)
功能：在LCD上显示用于浏览文字的图形界面控件
参数：Text:要显示的文字指针,UpLimit在LCD上显示的最顶层行数位置（以16像素为准）,DownLimit,最底层行数位置，type:指出当前按确认件后是否有特殊功能出现
返回值：1：用户点选确认，自然跳出，2：在特殊功能存在的情况下，用户点击确认 0：非以上两种情况时返回0
*/
unsigned char  TextGUI(unsigned char *Text,unsigned char *title,unsigned char UpLimit,unsigned char DownLimit,u8 type)
{
	//type变量指出当前按确认件后是否有特殊功能出现
	unsigned char page=1;
	unsigned char ReturnValue=0;   //当返回值为1时，应跳出该函数
	unsigned char func_state=0;
	unsigned char Temp;
	unsigned char OS_count=9;
	
	unsigned char Interval=DownLimit-UpLimit+1;  //求出两个界限的间隔 ，界限范围皆为0-4，上界一定小于等于下界
	
	u8   Tpage;
	FontSetTotal(COLOR_Black);
	
	if(func_state==0)
	{  
		//BoxGUI(Title);
		OS_count=strlenExt(Text)/30;  
		Tpage=OS_count/Interval+1;
		func_state=1;
	}
	while(func_state==1)
	{       
		
		SetPaintMode(0,COLOR_Black); 
		
		Rectangle(1,Y_Witch*(UpLimit-1),319,Y_Witch*(DownLimit-1),1);
		SetPaintMode(0,COLOR_White); 
		Rectangle(2,Y_Witch*(UpLimit)+1,318,Y_Witch*(DownLimit-1)-1,1);
		
		FontSetTotal(COLOR_White);
		FontMode(0,COLOR_Black);
		Lcd_disp(2,Y_Witch*(UpLimit-1),"文本阅读--");
		
		Lcd_disp(2+X_Witch_cn*5,Y_Witch*(UpLimit-1),title);
		FontSetTotal(COLOR_Black);    
		if( Tpage>1)
			Lcd_disp_limlen(1,Y_Witch*(UpLimit)+1,*(Text+(page-1)*30)>0x80?Text+(page-1)*30-1:Text+(page-1)*30,Interval*30);
		else 
			Lcd_disp_limlen(1,Y_Witch*(UpLimit)+1,Text,Interval*30);
		//Rectangle(1,1,127,63,0);
		Temp=(unsigned char)(Y_Witch*(UpLimit)+1+(Y_Witch*Interval)*((float)page/(float)OS_count));
		Line(317,Y_Witch*(UpLimit)+1,317,Y_Witch*(DownLimit+1)+2);
		Rectangle(318,Temp,319,Temp+(unsigned char )((Y_Witch*Interval)*(float)page/(float)OS_count),1);
		InputControl();
		switch(key_data)
		{
		case KEYENTER_UP   :
			ReturnValue=1; 
			func_state=2;
			page=1;
			break;
		case KEYCANCEL_UP    :
			if(type==1)
			{
				if(MessageGui("提示信息","进入功能菜单",0))
					ReturnValue=2;    //进入特殊功能
				page=1;
				func_state=2;
			}
			break;
		case KEYUP_UP  :
			if(page>1)
				page--;
			break;
		case KEYUP_DOWN :
			if(page<OS_count&&Tpage>1)
				page++;
			break;
			
			
		}
		
	}
	return ReturnValue;
	
}

/*
函数：void SystemOpenGUI()
功能：在LCD上显示系统初始化界面，并对系统进行配置
参数：无
返回值：无
*/
void SystemOpenGUI()
{    
	BitRateConfig();
	BackLightSet(OSBackLight);
         OSLightControl(2);
	PutBitmap(0,0,5,0);
	delay_ms(2000);
          OSLightControl(2);
	SetPaintMode(0,COLOR_Black);
	ClrScreen(1);
	FontMode(0,1);
	FontSetTotal(COLOR_White);
	PutString(2,2,"ELPOS Enhanced Edition 2.0");
          OSLightControl(2);
	delay_ms(200);
	FontSet(3,COLOR_Red);
          OSLightControl(2);
	PutString(200,50,"ELPOS");
	FontSet(2,OSColor); 
	PutString(200,100,"X-MOVE");
	FontSet(1,COLOR_White);
          OSLightControl(2);
	PutString(2,2+Y_Witch,"System Check...");
          OSLightControl(2);
	delay_ms(200);
	PutString(2,2+3*Y_Witch,"Flash:64KB,RAM:2KB");
          OSLightControl(2);
	delay_ms(200);
         
	PutString(2,2+4*Y_Witch,"CPU:MSP430F149 OC 16MHz");
          OSLightControl(2);
	delay_ms(400);
	PutString(2,2+5*Y_Witch,"DC IN 3.3V INPUT");
	delay_ms(200);
          OSLightControl(2);
	PutString(2,2+6*Y_Witch,"Loading The Data...");
	delay_ms(500);
	PutString(2,2+7*Y_Witch,"Please Wait");
          OSLightControl(0);
	//初始化设置
	myMEMSData[0]=PCID;  //当前的器件地址
#if PCID==1
        MenuType=2;
        OSColor=COLOR_Black;
#endif 
#if PCID==2
          MenuType=0;
        OSColor=COLOR_Blue;
#endif 

   #if PCID==3
          MenuType=2;
        OSColor=COLOR_Blue;
#endif 
        
        
	
}
/*
函数：void Clear_Screen()
功能：LCD清屏函数
参数：COLOR_Cyan（全局变量）当前系统的主题颜色
返回值：无
*/

void Clear_Screen()
{
	SetPaintMode(0,COLOR_Cyan);
	Rectangle(1,1+Y_Witch,LCD_X_MAX,LCD_Y_MAX-Y_Witch,1);
}
/*
函数：void calendar_GUI(u16 x,u16 y,u8 *rdata)
功能：LCD显示日历的控件函数
参数：(x,y)要显示的控件坐标，rdata表示存储时间的全局变量指针
返回值：无
*/
void calendar_GUI(u16 x,u16 y,u8 *rdata,u8 TotalFreshEN)
{
	u8 tTime;
	if(TotalFreshEN==1)
	{
		TaskBoxGUI_P(x,y,x+X_Witch_cn*7,y+3+3*Y_Witch_cn,"日历信息",0);
		
		SetPaintMode(0,COLOR_Black);
		
		Lcd_disp(x,y+1+Y_Witch_cn,"20  年  月  日");
		Line(x,y+2*X_Witch_cn+1,x+X_Witch_cn*7,y+2*X_Witch_cn+1);
		
		tTime=(rdata[6]/16)*10+rdata[6]%16;  //计算年
		NumberDis(x+X_Witch*2,y+X_Witch_cn+1,tTime,2,1);
		tTime=(rdata[4]/16)*10+rdata[4]%16;  //计算月
		NumberDis(x+X_Witch*6,y+X_Witch_cn+1,tTime,2,1);
		tTime=(rdata[3]/16)*10+rdata[3]%16;  //计算日
		NumberDis(x+X_Witch*10,y+X_Witch_cn+1,tTime,2,1);
		tTime=rdata[5]%16;
		switch(tTime)
		{
		case 1:
			PutString_cn(x,y+2+2*Y_Witch_cn,"星期一");
			break;
		case 2:
			PutString_cn(x,y+2+2*Y_Witch_cn,"星期二");
			break;
		case 3:
			PutString_cn(x,y+2+2*Y_Witch_cn,"星期三");
			break;
		case 4:
			PutString_cn(x,y+2+2*Y_Witch_cn,"星期四");
			break;
		case 5:
			PutString_cn(x,y+2+2*Y_Witch_cn,"星期五");
			break;
		case 6:
			PutString_cn(x,y+2+2*Y_Witch_cn,"星期六，周末");
			break;
		case 7:
			PutString_cn(x,y+2+2*Y_Witch_cn,"星期天，周末");
			break;   
		}
	}
}


void DrawClockPoint(u8 r,u8 x,u8 y,u8 hour,u8 min,u8 sec,u8 Color)
{
	if(Color==1)
		SetPaintMode(0,COLOR_Black);
	else
		SetPaintMode(0,COLOR_White);
	Line(x,y,x+(s8)(r*0.4*sin((float)hour*3.14/6.0)),y-(s8)(r*0.4*cos((float)hour*3.14/6.0)));
	Line(x,y,x+(s8)(r*0.6*sin((float)min*3.14/30.0)),y-(s8)(r*0.6*cos((float)min*3.14/30.0)));
	Line(x,y,x+(s8)(r*0.8*sin((float)sec*3.14/30.0)),y-(s8)(r*0.8*cos((float)sec*3.14/30.0)));
	
}
/*
函数：void clock_GUI(u16 x,u16 y,u16 r,u8 *rdata,u8 TotalFreshEN)
功能：LCD显示时间的时钟控件
参数：(x,y)要显示的控件左上角坐标，rdata表示存储时间的全局变量指针，r表示圆面半径，注意不要超过LCD允许范围
返回值：无
*/
void clock_GUI(u16 x,u16 y,u16 r,u8 *rdata,u8 TotalFreshEN)
{  
	unsigned char sec,min,hour;
	
	if(TotalFreshEN==1)
	{
		
		CircleShowGUI(x,y,r,COLOR_White);
		TaskBoxGUI_P(x-r,y+r,x+8*6,y+r+2*Y_Witch,"时间信息",0);
		SetPaintMode(0,COLOR_Black);
		
	}
	
	sec=(rdata[0]/16)*10+rdata[0]%16;
	min=(rdata[1]/16)*10+rdata[1]%16;
	hour=(rdata[2]/16)*10+rdata[2]%16;
	SetPaintMode(0,COLOR_White);
	Rectangle(x-r,y+r+X_Witch_cn,x+8*6,y+r+2*X_Witch_cn,1);
	NumberDis(x-r,y+r+X_Witch_cn,hour,2,1);
	NumberDis(x-r+X_Witch*3,y+r+X_Witch_cn,min,2,1);
	NumberDis(x-r+X_Witch*6,y+r+X_Witch_cn,sec,2,1);
	
	DrawClockPoint(r,x,y,hour,min,sec,1);
	delay_ms(1000);
	DrawClockPoint(r,x,y,hour,min,sec,0)  ;  //刷新表盘
    
}
/*
函数：void CurveDraw(u16 x,u16 y,u16 Wide,u16 Long,u16 unit,u16 Color,u8 *title,float mount,u16 flag)
功能：LCD显示曲线控件的图形函数
参数：(x,y)要显示的控件左上角坐标，Wide表示控件宽度（上下计算，像素），LONG：长度（左右计算，像素），Unit：最大可显示的值，COLOR:要显示的颜色
title:显示的标题，float:显示浮点值，flag:显示的位置标记位，当flag==0的时候，控件全部刷新
返回值：1:显示成功 0.显示失败
*/
u8 CurveDraw(u16 x,u16 y,u16 Wide,u16 Long,u16 unit,u16 Color,u8 *title,float mount,u16 flag)
{
	//x,y左上角坐标，wide 宽度，long 长度，Uint总量程，mode=0初始态
	float t=(float)Wide/2/(float)unit;
	signed int temp=(signed int)(t*mount);
	if(mount>(signed int)unit)
	{
		MessageGui("控件错误","超出最大量程",0);
		return 0;
	}
	
	
	if(flag==0)  //初始态
	{
		FontSetTotal(COLOR_Black);
		Lcd_disp(x,y,title);
		FontSet(0,COLOR_Black);
		y+=15;
		NumberDis(x,y,unit,2,1);
		NumberDis(x,y+Wide/4,unit/2,2,1);
		NumberDis(x,y+Wide/2,0,3,1);   
		NumberDis(x,y+3*Wide/4,unit/2,2,1);
		NumberDis(x,y+Wide,unit,3,1);
		SetPaintMode(0,COLOR_Black);
		y-=5;
		Rectangle(x+15,y+12,x+X_Witch+Long,y+12+Wide,1);
		SetPaintMode(0,COLOR_White);
		Line(x+15,y+12+Wide/2,x+X_Witch+Long,y+12+Wide/2);
		FontMode(1,COLOR_White);
		
		
	}
	else
	{
		//绘图态
		SetPaintMode(0,Color);
		ShowMountGUI(x+X_Witch_cn*8,y,mount,6, COLOR_Black,1);
		u16 fuck=y+12+Wide/2-temp;
		PutPixel(x+15+flag,fuck+10);
	}
	return 1;
}
/*
函数：void DrawTitle(u16 x,u16 y,u8* mTitle,u8 Type,u8 style)
功能：菜单的子功能函数，用于产生反白的字体
参数：(x,y)要显示的控件左上角坐标，Index表示在子菜单列表中的具体位置，TYPE为反白选项0不反白，1反白，mTitle要显示的字符，style特殊风格，默认为0
返回值：无
*/
u8 DrawTitle(u16 x,u16 y,u8* mTitle,u8 Type,u8 style,u8 FreshEN)

{  
	if(FreshEN==0)
		return 0;
	//TYPE用于选择该项是否反白，0不反白，1反白
	if (Type==0)    
	{
		FontMode(0,OSColor);
		FontSetTotal(COLOR_Red);
		
	}
	else
	{
		FontMode(1,OSColor);
		FontSetTotal(COLOR_White);
	}
	switch(style)
	{
	case 0:
		
		Lcd_disp(x,y,mTitle);
		break;
		
		
	}
	return 1;
	
	
	
	
}
/*
函数：void DrawIconAndTitle(u16 x,u16 y,u8 Index, u8 PictSize,u8 Type,u8 TitleOrPict)
功能：主菜单界面的子函数，用于产生单项
参数：(x,y)要显示的控件左上角坐标，Index表示在子菜单列表中的具体位置，PictSize为要显示的图片大小，TYPE为反白选项0不反白，1反白,TitleOrPict控制来写字或画图，这样可以更快
返回值：无
*/
void DrawIconAndTitle(u16 x,u16 y,u8 Index, u8 PictSize,u8 Type,u8 TitleOrPict)

{  
	
	u8* mTitle=myTaskPCB[myTaskPCB[OS_index_data].SubTaskList[Index+2]].Name;
	u8* mDetail=myTaskPCB[myTaskPCB[OS_index_data].SubTaskList[Index+2]].Detail;
	//TYPE用于选择该项是否反白，0不反白，1反白
	if (Type==0)    
	{
		FontMode(1,COLOR_White);
		FontSetTotal(COLOR_Red);
		
	}
	else
	{
		FontMode(1,OSColor);
		FontSetTotal(COLOR_White);
	}
	switch(MenuType)
	{
	case 0:
		if(TitleOrPict==1)
			PutBitmap(x,y,myTaskPCB[myTaskPCB[OS_index_data].SubTaskList[Index+2]].PicIndex,0);
		else
		{
			Lcd_disp(x+PictSize,y,mTitle);
			FontSetTotal(COLOR_Black);
			FontMode(0,COLOR_White);	
			
			Lcd_disp(x+65,y+Y_Witch_cn,mDetail);
		}
		
		
		break;
	case 1:
		if(TitleOrPict==0)
		{
			Lcd_disp(x,y,mTitle);
			
			FontSetTotal(COLOR_Black);	
			FontMode(0,COLOR_White);	
			Lcd_disp(x+7*X_Witch_cn,y,mDetail);
			Line(x,y+Y_Witch_cn,x+18*X_Witch_cn,y+Y_Witch_cn);
		}
		break;
	case 2:
	       
		if(TitleOrPict==1) 
			PutBitmap(x,y,myTaskPCB[myTaskPCB[OS_index_data].SubTaskList[Index+2]].PicIndex,0);
		else 
			Lcd_disp(x,y+65,mTitle);
		break;
	case 3:
		
		Lcd_disp(x,y+PictSize,mTitle);
		break;
		
		
	}
	
	
	
	
}

u8  MenuDataRefreshGUI(u8 MenuFlag,u8 MaxMount,u8 flag,u8 LastFlag,u8 LRMaxMount,u8 UDMaxMount,u8 OneLRLength,u8 OneUDLength,u8 FreshEN,u8 TotalFreshEN)
{
	if(!FreshEN)
		return 0;
	if(TotalFreshEN)
	{
		
		SetPaintMode(0,COLOR_White);
		Rectangle(X_Witch_cn+1,2*Y_Witch_cn,Dis_X_MAX-X_Witch_cn-1,Dis_Y_MAX-Y_Witch_cn-1,1);
		
		//全局菜单（无反白项）显示
		SetPaintMode(0,COLOR_Black);
		
		for(u8 TitleORPictFlag=0;TitleORPictFlag<2;TitleORPictFlag++)
			for (u8 UDflag=0;UDflag<UDMaxMount;UDflag++)
			{
				for(u8 LRflag=0;LRflag<LRMaxMount;LRflag++)
				{
					if (MenuFlag-1+UDflag*LRMaxMount+LRflag>=MaxMount)
					{
						break;
					}
					DrawIconAndTitle(X_Witch_cn+1+LRflag*OneLRLength,2*Y_Witch_cn+UDflag*OneUDLength,MenuFlag-1+UDflag*LRMaxMount+LRflag,OneUDLength,LRflag+UDflag*LRMaxMount+1==flag?1:0,TitleORPictFlag);
					
				}
			}
	}
	else
	{
		u8 UDflag,LRflag;
		for(u8 i=0;i<2;i++)
		{
			
			
			if(i==1)
			{
				UDflag	=(flag-1)/LRMaxMount;
				LRflag=flag-1-UDflag*LRMaxMount;
			}
			else
			{
				UDflag	=(LastFlag-1)/LRMaxMount;
				LRflag=LastFlag-1-UDflag*LRMaxMount;
				
			}
			
			DrawIconAndTitle(X_Witch_cn+1+LRflag*OneLRLength,2*Y_Witch_cn+UDflag*OneUDLength,MenuFlag-1+UDflag*LRMaxMount+LRflag,OneUDLength,i,0);
		}	
	}
	return 1;
}
/*
u8 UpdownListInputControl(u8 *Menuflag,u8 *ThisPageflag,u8 *TotolFlag,u8 *ThisPageMax)
功能：菜单输入控制方法，用于上下类型的菜单
参数：Menuflag，全页面标志计数器，ThisPageflag当前页面标志计数器，TotolFlag总页面条数，ThisPageMax当前页面最大数量,PromptEN：是否提示到目录头或者结尾
返回值：0：退出 1， 确认，2：仅仅选择了移动位置
*/

u8 UpdownListInputControl(u8 *Menuflag,u8 *ThisPageflag,u8 TotolFlag,u8 ThisPageLRMax, u8 ThisPageUDMax,u8 PromptEN,u8 *FreshEN,u8* TotalFreshEN)
{
	u8 LastMenuFlag=*Menuflag;
	u8 PromptFlag=0;
	u8 GyroKey=KEYNULL;
	*FreshEN=0;
	u8 myKey=KEYNULL;
	if(GyroControlEN==1)
		PromptEN=0; //当开启陀螺检测时，关闭提示
	if(GyroControlEN==1&&back_light>1&&GyroMenuEN)
	{
		
		delay_ms(300-20*TotolFlag);
		L3G4200DReadData();
		L3G4200DShowData();
		
		delay_ms(300-20*TotolFlag);
	}
	
	else
		InputControl(); 
	if(GyroMenuEN!=0)
        GyroKey=GyroKeyBoardInputMethod(0,1,300-30*ThisPageLRMax,300-20*ThisPageUDMax);
	
	if(GyroKey!=KEYNULL)
		myKey=GyroKey;
	else
		myKey=key_data;
	GyroKey=KEYNULL;
	
	switch(myKey)
	{  
	case KEYENTER_UP   :
		
		return 1;
		//break;
		
	case KEYUP_UP  :
		if(*ThisPageflag>ThisPageLRMax)
			(*ThisPageflag)-=ThisPageLRMax;
		else
		{if(*Menuflag>ThisPageLRMax)
		(*Menuflag)-=ThisPageLRMax;
		else
			if(*ThisPageflag==1&&PromptEN)
			{
				PromptFlag=1;
				MessageGui("提示信息","已到目录开头",2);
			}
			//else 
			//*ThisPageflag=1;
		}	
		break;
	case KEYDOWN_UP  :
		if(*ThisPageflag<=ThisPageLRMax*(ThisPageUDMax-1)&&*ThisPageflag+ThisPageLRMax<=TotolFlag)
			(*ThisPageflag)+=ThisPageLRMax;
		else
		{if(*Menuflag+*ThisPageflag-1<=TotolFlag-ThisPageLRMax)
		(*Menuflag)+=ThisPageLRMax;
		else
		{
			if(TotolFlag==*ThisPageflag&&PromptEN)
			{
				PromptFlag=1;
				MessageGui("提示信息","已到目录结尾",2);
				
			}
			//else
			//*ThisPageflag= TotolFlag-*Menuflag+1;
		}
		}
		break;
    case  KEYLEFT_UP    :
		if(*ThisPageflag>1)
			(*ThisPageflag)--;
		else
		{if(*Menuflag>1)
		(*Menuflag)--;
		else
			if(PromptEN)
			{
				MessageGui("提示信息","已到目录开头",2);
				PromptFlag=1;
			}
		}
		
		break;
	case KEYRIGHT_UP  :
		if(*ThisPageflag<TotolFlag)
			(*ThisPageflag)++;
		else
		{if(*Menuflag+*ThisPageflag-1<TotolFlag)
		(*Menuflag)++;
		else
			if(PromptEN)
			{
				MessageGui("提示信息","已到目录结尾",2);
				PromptFlag=1;
			}
		}
		break;
		
	case KEYCANCEL_UP    :
		
		return 0;
	} 
	if(key_data!=KEYNULL)
		*FreshEN=1;
	
	if(LastMenuFlag==*Menuflag&&PromptFlag==0)
		*TotalFreshEN=0;
	else
		*TotalFreshEN=1;
	return 2;
	
}

u8  GyroKeyBoardInputMethod(u8 HeadDirectionDefine,u8 CancelEN,float Xthreshold,float Ythreshold)
{
	//HeadDirectionDefine  以设备朝上为准，横屏为0，竖屏为1
	u8 key=KEYNULL;
	if(GyroControlEN==0||back_light<2)
		return KEYNULL;
	if (HeadDirectionDefine==0)
	{
		
		if (GyroX>Xthreshold)
		{
			key=KEYRIGHT_UP  ;
		}
		else if(GyroX<-Xthreshold)
			key=KEYLEFT_UP    ;
		if (GyroY>Ythreshold)
		{
			key=KEYUP_UP  ;
		}
		else if(GyroY<-Ythreshold)
		{
			key=KEYDOWN_UP  ;
		}
		if(CancelEN==1&&GyroZ>1800)
			key=KEYCANCEL_UP  ;
		
	}
	else
	{
		if (GyroY>Ythreshold)
		{
			key=KEYLEFT_UP    ;
		}
		else if(GyroY<-Ythreshold)
		{
			key=KEYRIGHT_UP  ;
		}
		if (GyroX>Xthreshold)
		{
			key=KEYDOWN_UP  ;
		}
		else if(GyroX<-Xthreshold)
			key=KEYUP_UP  ;
		
		
	}
	return key;
	
}
/*
函数：u8  MainMenuListGUI()
功能：主菜单界面的函数，负责绘图和和获得用户选择
参数：无
返回值：固定返回1
*/
u8  MainMenuListGUI(u8 LRMaxMount,u8 UDMaxMount,u8 OneLRLength,u8 OneUDLength)
{
	
	if (myTaskPCB[OS_index_data].function!=MenuGUI)
	{
		return 0;
	}
	
	u8 MaxMount=myTaskPCB[OS_index_data].SubTaskList[1];
	
	u8 func_state=0,menu_flag=1,LastFlag,TotalFreshEN=1,flag=1,FreshEN=1;
	
	if(func_state==0)
	{
		
		
		TaskBoxGUI_P(X_Witch_cn,Y_Witch_cn,Dis_X_MAX-X_Witch_cn,Dis_Y_MAX-Y_Witch_cn-3,(u8 *)myTaskPCB[OS_index_data].Name,0);
		func_state=1;
		
	}
	while(func_state==1)
		
	{     
		
		MenuDataRefreshGUI( menu_flag, MaxMount, flag, LastFlag, LRMaxMount,UDMaxMount, OneLRLength, OneUDLength,FreshEN,TotalFreshEN);
		LastFlag=flag;
		switch(UpdownListInputControl(&menu_flag,&flag,MaxMount,LRMaxMount,UDMaxMount,1,&FreshEN,&TotalFreshEN))
		{
		case 0:
			OSTaskClose();
			func_state=2;
			return 1;
			
		case 1:
			func_state=2;
			break;
			
			
		}
		
		
	}		
	OS_index_data= myTaskPCB[OS_index_data].SubTaskList[menu_flag+flag];
	return 1;	
	
}
/*
函数：u8 SliderGUI(u16 x,u16 y,u16 Length,u8* title,u16 RangeLow,u16 RangeHigh,u8 step,u16* Data)
功能：滑动模式的数值选择控件
参数：(x,y)控件左上角坐标，length，显示的控件长度（从左到右）,RangeLow:数值最低可选值，RangeHigh:数值最高可选值，step：数据选择步进，data:存储数据的指针
返回值：0:控件错误或用户取消选择，1：用户成功使用控件，数据存在data中
*/
u8 SliderGUI(u16 x,u16 y,u16 Length,u8* title,u16 RangeLow,u16 RangeHigh,u8 step,u16* Data)
{ 
	u16 OriginData=*Data; //保存原始的数据信息，跳出时可以恢复
	u8 fuck;
	if (*Data>RangeHigh||*Data<RangeLow)
	{
		MessageGui("提示信息，程序错误","原始值溢出，设置最小",0);
		*Data=RangeLow;
		return 0;
	}
	TaskBoxGUI_P(x,y,x+Length+2*X_Witch,y+4*Y_Witch_cn,title,1);
	FontMode(1,COLOR_White);
	Lcd_disp(x+X_Witch,y+Y_Witch_cn+1,"当前数值");
	delay_ms(5);
	
	NumberDis(x+X_Witch,y+3*Y_Witch_cn,RangeLow,3,2);
	NumberDis(x+Length-2*X_Witch_cn,y+3*Y_Witch_cn,RangeHigh,3,2);
	
	while (1)
	{
		
		NumberDis(x+Length/2,y+Y_Witch_cn+1,*Data,3,2);
		
		SetPaintMode(0,COLOR_Red);
		Rectangle(x+X_Witch,y+2*Y_Witch_cn+X_Witch,x+X_Witch+Length,y+2*Y_Witch_cn+X_Witch+1,1);
		Rectangle(x+X_Witch+Length*(*Data-RangeLow)/(RangeHigh-RangeLow)-2,y+2*Y_Witch_cn+X_Witch-4,x+X_Witch+Length*(*Data-RangeLow)/(RangeHigh-RangeLow)+2,y+2*Y_Witch_cn+X_Witch+4,1);
		
		InputControl();
		SetPaintMode(0,COLOR_White);   //清空原来的方格
		Rectangle(x+X_Witch+Length*(*Data-RangeLow)/(RangeHigh-RangeLow)-2,y+2*Y_Witch_cn+X_Witch-4,x+X_Witch+Length*(*Data-RangeLow)/(RangeHigh-RangeLow)+2,y+2*Y_Witch_cn+X_Witch+4,1);
		switch(key_data)
		{
			
		case KEYENTER_UP   :
			return 1;
		case KEYCANCEL_UP    :
			MessageGui("提示信息","已放弃输入",0);
			*Data=OriginData;
			return 0;
		default:
			FourDirectionInputMethod(key_data,1,0,step,1,RangeLow,RangeHigh,0,3,0,0,(u8*)Data,&fuck);
			break;
		}
		
	}
	
	
}
/*
函数：u8 VirtualFullKeyBoardInput(u16 x,u16 y,u8* KeyX,u8* KeyY,u8 *Key)
功能：虚拟全键盘的输入子函数
参数：(x,y)控件左上角坐标，KeyX,KeyY表示当前在数字键盘上的X,Y坐标位置，范围分别为0-10,0-4，Key为返回的选择项，具体参见FullKeyBoardData[]数组声明
返回值：0:用户跳出或选择特殊功能键，1：用户选择了普通的字符，其用法参见具体代码
*/

u8 VirtualFullKeyBoardInput(u16 x,u16 y,u8* KeyX,u8* KeyY,u8 *Key)
{
	InnerFuncState=1;
	u8 GyroKey;
	
	while(InnerFuncState==1)
	{
		
		key_data=KEYNULL;
		SetPaintMode(0,COLOR_Red);
		Rectangle(x+5+*KeyX*21,y+LCD_Y_MAX-Y_Witch_cn-127+*KeyY*21,x+5+*KeyX*21+21,y+LCD_Y_MAX-Y_Witch_cn-127+*KeyY*21+21,0);
		if(GyroControlEN==1)
		{
			L3G4200DReadData();
			L3G4200DShowData();
			
			delay_ms(150);
		}
		
		else
			
			InputControl();
		
		GyroKey=GyroKeyBoardInputMethod(0,1,100,300);
		if(GyroKey!=KEYNULL)
			key_data=GyroKey;
		GyroKey=KEYNULL;
		
		SetPaintMode(0,COLOR_Black);
		Rectangle(x+5+*KeyX*21,y+LCD_Y_MAX-Y_Witch_cn-127+*KeyY*21,x+5+*KeyX*21+21,y+LCD_Y_MAX-Y_Witch_cn-127+*KeyY*21+21,0);
		
		switch(key_data)
		{
		case  KEYCANCEL_UP   :
			*Key=0;
			return 0;   //退格键
		case  KEYENTER_UP   :
			if (*KeyY*11+*KeyX==43)
			{
				*Key=1;
				return 0;   //退格键
			}
			
			else
				
				*Key=FullKeyBoardData[*KeyY*11+*KeyX];
			return 1;
		default:
			FourDirectionInputMethod(key_data,1,1,1,1,0,10,0,3,1,0,KeyX,KeyY);
			break;
		}
		
	}	
	return 1;
}

/*
u8 VirtualFullKeyBoard(u16 x,u16 y,u8 *Buff,u8 *BuffFlag,u8 Max)
功能：虚拟全键盘的输入函数
参数：(x,y)控件左上角坐标，Buff为存储输入数据的数组，BuffFlag为当前存储的数组长度，Max为数组可得到的最大动态长度
返回值：0:用户跳出1：用户选择了确认
*/

u8 VirtualFullKeyBoard(u16 x,u16 y,u8 *Buff,u8 *BuffFlag,u8 Max)
{
	u8 InputKey;
	
	u8 mkeyx=5,mkey=2;
	//参数检查
	if (x>LCD_X_MAX-240)
	{
		x=LCD_X_MAX-242;
	}
	if (y>LCD_Y_MAX-95)
		
	{
		y=LCD_Y_MAX-97;
	}
	
	TaskBoxGUI_P(x+3,y+Y_Witch_cn+2,x+243,y+LCD_Y_MAX-3*Y_Witch_cn-2,"虚拟全键盘输入",0);
	FontMode(1,COLOR_White);
	FontSetTotal(COLOR_Black);
	PutBitmap(3+x,y+LCD_Y_MAX-3*Y_Witch_cn-97,VKFULL,0);
	SetPaintMode(0,OSColor);
	//开启陀螺功能
	InnerFuncState=1;
	while(InnerFuncState)
	{
		if (	VirtualFullKeyBoardInput(x,y,&mkeyx,&mkey,&InputKey))   //正常输入字符
		{
			*(Buff+*BuffFlag)=InputKey;
			if((*BuffFlag)<Max)
				(*BuffFlag)++;
		}
		else
		{
			switch(InputKey)
			{
				
				
			case 0:
				if(MessageGui("提示信息","完成输入？",1))
					return 1;
				else
					return 0;
				
			case 1:
				if(*BuffFlag>0)
				{
					SetPaintMode(0,COLOR_White);
					Rectangle(x+5+X_Witch*(*BuffFlag),y+3*Y_Witch_cn+3,x+5+X_Witch*(*BuffFlag)+X_Witch,y+4*X_Witch+2,1);
					SetPaintMode(0,OSColor);
					
					(*BuffFlag)--;
				}
				
				break;
			}
			
			
			
		}
		
		Rectangle(x+5+X_Witch*(*BuffFlag),y+3*Y_Witch_cn+3,x+5+X_Witch*(*BuffFlag)+X_Witch,y+4*X_Witch+2,1);
		PutString_limit(x+5,y+2*Y_Witch_cn+3,Buff,*BuffFlag);
		delay_ms(40);
	}
	return 1;
	
}

/*
函数：u8 PictureShowBox(u8 x,u8 y,u8* title)
功能：图片显示控件
参数：(x,y)控件左上角坐标，*titile为显示的标题
返回值：0:跳出该控件，1：其他
注意事项：该函数局限性很大，内部变量Index给出了在LCD缓存中存储的图片位置，但不能超过允许范围，否则会出错
*/
u8 PictureShowBox(u16 x,u16 y,u8* title)
{
	u8 Index=6;
	u8 FUCK;
	//最大的范围只能达到240，160
	TaskBoxGUI_P(x,y,x+240,y+160,title,0);
	
	InnerFuncState=1;
	while(InnerFuncState)
	{
		SetPaintMode(0,COLOR_White);
		Rectangle(x,y+Y_Witch_cn,x+239,y+159,1);
		PutBitmap(x,y+Y_Witch_cn,Index,0);
		if(GyroControlEN==1)
		{
			L3G4200DReadData();
			L3G4200DShowData();
			delay_ms(1000);
		}
		
		else
			InputControl();
		if(GyroControlEN==1)
		{
			if(GyroZ>600)
				key_data=KEYUP_UP  ;
			else if(GyroZ<-600)
				key_data=KEYDOWN_UP  ;
			
		}
		switch(key_data)
		{
            
		case KEYCANCEL_UP    :
			if(MessageGui("提示信息","是否退出图片浏览",1))
			{
				return 0;
			}
			else
				break;
		case KEYENTER_UP   :
			break;
		default:
			FourDirectionInputMethod(key_data,0,1,1,1,6,25,6,25,0,1,&FUCK,&Index);
			break;
		}
		
		key_data=KEYNULL;
	}
	return 1;
	
}
/*
函数：u8 CircleShowGUI(u16 x,u16 y, u8 r,LCDBYTE COLOR)
功能：显示一个圆盘
参数：无
返回值：固定为1
注意事项：磁场计至今未成功调试，该功能不可用
*/

u8 CircleShowGUI(u16 x,u16 y, u8 r,LCDBYTE COLOR)   //指南针图形界面
{ 
	
	SetPaintMode(0,COLOR_Black);
	Circle(x+2,y+2,r,1);
	SetPaintMode(0,COLOR);
	Circle(x,y,r,1);
	SetPaintMode(0,COLOR_Black);
	Circle(x,y,r,0);
	return 1;
	
}
/*
u8 VirtualFullKeyBoard(u16 x,u16 y,u8 *Buff,u8 *BuffFlag,u8 Max)
功能：虚拟数字键盘的子输入函数
参数：(x,y)控件左上角坐标，KeyX,KeyY表示当前在数字键盘上的X,Y坐标位置，范围分别为0-2,0-3，Key为返回的选择项，具体参见NumKeyBoardData[]数组声明
返回值：0:用户跳出或选择特殊功能键，1：用户选择了普通的字符，其用法参见具体代码
*/
u8 VirtualNumKeyBoardInput(u16 x,u16 y,u8* KeyX,u8* KeyY,u8 *Key,u8 FuncEN,u8 HardKeyTransEN)  //Ox,oy 是原始的x,y坐标值
{
	u8 GyroKey;
	while(1)
	{
		key_data=KEYNULL;
		SetPaintMode(0,COLOR_Red);
		Rectangle(x+2+*KeyX*31,y+2*Y_Witch_cn+3+*KeyY*27,x+2+*KeyX*31+31,y+2*Y_Witch_cn+*KeyY*27+30,0);
		if(GyroControlEN==1)
		{
			L3G4200DReadData();
			L3G4200DShowData();
			delay_ms(150);
		}
		
		else
			
			InputControl();
		if(key_data==KEYNULL)
			GyroKey=GyroKeyBoardInputMethod(0,1,300,300);
		else
		{
			if(key_data!=KEYENTER_UP&&key_data!=KEYCANCEL_UP)
			{
				if(HardKeyTransEN&&GyroControlEN)
				{
                                        *Key=key_data;
					return 2;  
				}
			}
		}
		if(GyroKey!=KEYNULL)
			key_data=GyroKey;
		GyroKey=KEYNULL;
		
		
		SetPaintMode(0,COLOR_Black);
		Rectangle(x+2+*KeyX*31,y+2*Y_Witch_cn+3+*KeyY*27,x+2+*KeyX*31+31,y+2*Y_Witch_cn+*KeyY*27+30,0);
		
		switch(key_data)
		{
		case KEYCANCEL_UP    :
			*Key=0;   //跳出态
			return 0;
		case KEYENTER_UP   :
			if(FuncEN==1)
				switch(*KeyX+*KeyY*3)
			{
		case 9:
			
			*Key=1;
			return 0;  //确认态
			
		case 11:
			
			*Key=2;  //删除态
			return 0;
			
		default:
			*Key=NumKeyBoardData[*KeyX+*KeyY*3];
			return 1;
			}
			else
			{
				*Key=*KeyX+*KeyY*3;
				return 1;
			}
			
		default:
			FourDirectionInputMethod(key_data,1,1,1,1,0,2,0,3,0,0, KeyX,  KeyY);
			break;
		}
		
	}
	
	
}
/*
u8 VirtualFullKeyBoard(u16 x,u16 y,u8 *Buff,u8 *BuffFlag,u8 Max)
功能：虚拟数字键盘的输入函数
参数：(x,y)控件左上角坐标，Buff为存储输入数据的数组，BuffFlag为当前存储的数组长度，Max为数组可得到的最大动态长度
返回值：0:用户跳出1：用户选择了确认
*/
u8 VirtualNumKeyBoard(u16 x,u16 y,u8 *Buff,u8 *BuffFlag,u8 Max,u8 *title)

{
	u8 mkeyx=1,mkey=2,InputKey;
	if (x>LCD_X_MAX-100)
	{
		x=LCD_X_MAX-100;
	}
	if (y>50)
	{
		y=50;
	}
	TaskBoxGUI_P(x,y,x+100,y+2*Y_Witch_cn+108,title,0);
	PutBitmap(x,y+2*Y_Witch,VKNUM,0);
	FontMode(1,COLOR_White);
	InnerFuncState=1;
	while (InnerFuncState)
	{
		if (VirtualNumKeyBoardInput(x,y,&mkeyx,&mkey,&InputKey,1,0))
		{
			*(Buff+*BuffFlag)=InputKey;
			if((*BuffFlag)<Max)
				(*BuffFlag)++;
		} 
		else
		{
			switch(InputKey)
			{
			case 0:
				MessageGui("提示信息","已跳出",0);
				return 0;
			case 2:
				if(*BuffFlag>0)
				{
					SetPaintMode(0,COLOR_White);
					Rectangle(x+5+X_Witch*(*BuffFlag),y+Y_Witch_cn,x+5+X_Witch*(*BuffFlag)+X_Witch,y+2*Y_Witch_cn,1);
					SetPaintMode(0,OSColor);
					(*BuffFlag)--;
				}
				break;
			case 1:
				return 1;
			}
		}
		
		Rectangle(x+5+X_Witch*(*BuffFlag),y+Y_Witch_cn,x+5+X_Witch*(*BuffFlag)+X_Witch,y+2*Y_Witch_cn,1);
		PutString_limit(x+5,y+Y_Witch_cn,Buff,*BuffFlag);
	}
	return 1;
	
	
}
/*
函数：u8 InputLongNum(u8* title,long *LData)
功能：输入长整形数字的图形控件
参数：title标题，LData要输入的数据
返回值：0:用户跳出1：用户正常输入了数字
*/
u8 InputLongNum(u8* title,long *LData)
{
	u8 Num[8];
	*LData=0;
	long Ltemp;
	u8 Flag=0,mTemp=0;
	
	if(!VirtualNumKeyBoard(30,80,Num,&Flag,8,title))
		return 0;
	
	mTemp=Flag;
	while(Flag>0)
	{
		Ltemp=(long)pow(10,mTemp-Flag);
		*LData+=(Num[Flag-1]-0X30)*Ltemp;
		Flag--;
		
	}
	return 1;
}
/*
函数：u8 PassWordCheck()
功能：数字检查函数，要求用户输入数字，并与原有的数字比较
参数：无
返回值：0：两数字不同，1：数据相同，
*/
u8 PassWordCheck()
{
	long temp=0;
	while(1)
	{
		if(!	InputLongNum("请输入密码",&temp))
		{
			MessageGui("提示信息","数据格式错误",0);
			
		}
		else
		{
			if (temp==mPassWord)
			{
				MessageGui("恭喜","输入正确",0)	;
				return 1;
			} 
			else
			{	MessageGui("提示信息","重新输入",0);
			}
		}
		
	}
	
}
/*
函数：u8 HistogramGUI(u8** List,u16* Num,u8 num,u8* title)
功能：显示柱状图控件
参数：List,存储不同享标题的数组，Num存储不同项的数值的数组，num要显示的项的数量，title控件标题
返回值：0：两数字不同，1：数据相同，
*/
u8 HistogramGUI(u8** List,u16* Num,u8 num,u8* title)
{
	u16 MaxNum=0;
	
	u16 XStep=270/(num+1);  //X步进
	if (num>4)
	{
		num=4;
	}
	for(u8 i=0;i<num;i++)
	{
		MaxNum=MaxNum>Num[i]?MaxNum:Num[i];
	}
	u16 RangeHigh=(u16)(1.2*MaxNum);
	TaskBoxGUI(title);
	SetPaintMode(0,COLOR_Black);
	Line(15,48,15,170);
	Line(15,170,289,170);
	SetPaintMode(0,COLOR_Red);
	FontSet_cn(0,COLOR_Black);
	for (u8 i=0;i<num;i++)
	{
		Lcd_disp(60+i*XStep-20,172,List[i]);
		Rectangle(50+i*XStep,170-(u16)(((float)Num[i]/(float)MaxNum)*(float)RangeHigh),80+i*XStep,170,1);
		NumberDis(50+i*XStep,190-(u16)(((float)Num[i]/(float)MaxNum)*(float)RangeHigh),Num[i],3,2);
	}
	
	
	InputControl();
	return 1;
	
}

u8 TimeSetGUI()
{
#if PCID==1
	if(!MessageGui("时钟硬件不可用","是否继续？",1))
		return 0;
#endif
	if (!MessageGui("确定修改时间？","是否继续？",1))
		return 0;
	u16 TimeTemp=1;
	
	if(!SliderGUI(20,40,150,"年代",1,60,1,&TimeTemp))
		return 0;
	rdata[6]=DecToHexFunc(TimeTemp);
	TimeTemp=1;
	if(!SliderGUI(20,100,150,"星期",1,7,1,&TimeTemp))
		return 0;
	
	rdata[5]=DecToHexFunc(TimeTemp);
	TimeTemp=1;
	if(!SliderGUI(20,160,150,"月份",1,12,1,&TimeTemp))
		return 0;
	rdata[4]=DecToHexFunc(TimeTemp);
	TimeTemp=1;
	if(!SliderGUI(20,40,150,"日期",1,31,1,&TimeTemp))
		return 0;
	rdata[3]=DecToHexFunc(TimeTemp);
	TimeTemp=1;
	if(!SliderGUI(20,100,150,"小时",1,24,1,&TimeTemp))
		return 0;
	rdata[2]=DecToHexFunc(TimeTemp);
	TimeTemp=1;
	if(!SliderGUI(20,160,150,"分钟",1,60,1,&TimeTemp))
		return 0;
	rdata[1]=DecToHexFunc(TimeTemp);
	rdata[0]=0;
	if(MessageGui("要写入时间信息吗？","是否继续？",1))     
	{
		Set_DS1302(rdata);
		return 1;
	}
	else
	{
		return 0;
	}
	
	
}





u8 KeyBoardFuncIntroGUI(u8 HandleID,u8 *KeyUp,u8 *KeyDown,u8 *KeyLeft,u8 *KeyRight,u8 *KeyEnter,u8* KeyEsc)
{   
  u8  *Title;
switch(HandleID)
{
case 0:
	Title="主控制器键位表";
	break;
case 1:
	Title="从控制器键位表";
	break;
default:
	return 0;
} 
TaskBoxGUI_P(1,LCD_Y_MAX-(5-2*HandleID)*Y_Witch_cn,LCD_X_MAX,LCD_Y_MAX-(3-2*HandleID)*Y_Witch_cn,Title,1);
FontMode(0,OSColor);

Lcd_disp(0,LCD_Y_MAX-(4-2*HandleID)*Y_Witch_cn,KeyUp);
Lcd_disp(3*X_Witch_cn*1,LCD_Y_MAX-(4-2*HandleID)*Y_Witch_cn,KeyDown);

Lcd_disp(3*X_Witch_cn*2,LCD_Y_MAX-(4-2*HandleID)*Y_Witch_cn,KeyLeft);
Lcd_disp(3*X_Witch_cn*3,LCD_Y_MAX-(4-2*HandleID)*Y_Witch_cn,KeyRight);
Lcd_disp(3*X_Witch_cn*4,LCD_Y_MAX-(4-2*HandleID)*Y_Witch_cn,KeyEnter);
Lcd_disp(3*X_Witch_cn*5,LCD_Y_MAX-(4-2*HandleID)*Y_Witch_cn,KeyEsc);

InputControl();
return 1;




}

u8 FourDirectionInputMethod(u8 key,u8 LREN,u8 UDEN,u8 LRStep,u8 UDStep,u8 LRMin,u16 LRMAX,u8 UDMin,u8 UDMax,u8 CircleEN,u8 PromtEN,u8 *KeyX,u8 *KeyY)
{
	
    if(key==KEYRIGHT_UP||key==KEYLEFT_UP)
		if(!LREN)
			return 0;
		if(key==KEYUP_UP||key==KEYDOWN_UP)
			if(!UDEN)
				return 0;
			switch(key)
			{
			case KEYRIGHT_UP  :
				if (*KeyX+LRStep<=LRMAX)
				{
					(*KeyX)+=LRStep;
				} 
				else
				{
					if (CircleEN)
					{
						(*KeyX)=LRMin;
					}
					if(PromtEN)
						MessageGui("提示信息","已到目录最后",2);
					
				}
				break;
			case KEYLEFT_UP :
				if ((*KeyX)-LRStep>=LRMin)
				{
					(*KeyX)-=LRStep;
				} 
				else
				{
					if (CircleEN)
					{
						(*KeyX)=LRMAX;
					}
					if(PromtEN)
						MessageGui("提示信息","已到目录最前",2);
					
					
				}
				break;
			case KEYDOWN_UP:
				if ((*KeyY)+UDStep<=UDMax)
				{
					(*KeyY)+=UDStep;
				} 
				else
				{
					if(CircleEN)
						(*KeyY)=UDMin;
					if(PromtEN)
						MessageGui("提示信息","已到目录最后",2);
					
				}
				break;
			case KEYUP_UP  :
				if ((*KeyY)-UDStep>=UDMin)
				{
					(*KeyY)-=UDStep;
				} 
				else
				{
					if(CircleEN)
						(*KeyY)=UDMax;
					if(PromtEN)
						MessageGui("提示信息","已到目录最前",2);
				}
				break;
				
				
			}
			return 1;
}



