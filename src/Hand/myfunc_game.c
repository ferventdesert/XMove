#include "config.h"
#if  GAME_CONTROL_EN==1
#include <math.h>

#define u8 unsigned char 
const unsigned char  BoxShape[19][9]=
{    
	
	{ 1,0,0,1,1,1,2,1,1  },   
	{ 1,0,1,1,2,1,1,2,2  },   
	{ 0,0,1,0,2,0,1,1,3  },   
	{ 1,0,0,1,1,1,1,2,0  },   
	
	{ 1,0,2,0,1,1,1,2,5  },   
	{ 0,0,1,0,2,0,2,1,6  },   
	{ 2,0,2,1,2,2,1,2,7  },   
	{ 0,0,0,1,1,1,2,1,4  },   
	
	{ 1,0,2,0,2,1,2,2,9  },   
	{ 2,0,0,1,1,1,2,1,10 },   
	{ 1,0,1,1,1,2,2,2,11 },   
	{ 0,0,1,0,2,0,0,1,8  },   
	
	{ 0,0,0,1,1,1,1,2,13 },   
	{ 1,0,2,0,0,1,1,1,12 },   
	
	{ 2,0,1,1,2,1,1,2,15 },   
	{ 0,0,1,0,1,1,2,1,14 },   
	
	{ 1,0,1,1,1,2,1,3,17 },   
	{ 0,1,1,1,2,1,3,1,16 },   
	
	{ 1,0,2,0,1,1,2,1,18 } 
}; 

void TerisBrickInit(u8  Data[][22],u8 i,u8 j)
{
	
	u8  a,b;
	for(b=0;b<i;b++)
	{
		for(a=0;a<j;a++)
			Data[b][a]=0;
	}
	for(b=0;b<j;b++)
	{
		Data[0][b]=1;
		Data[11][b]=1;
	}
	for(a=0;a<i;a++)
	{
		Data[a][0]=1;
		Data[a][21]=1;
	}
	
	
}
void GenerateBox(u8 *XAxi ,u8 *YAxi,u8 *Type,u8 Data[][22],u8 *FailFlag)
{
	u8 fuck;
	*XAxi=5;
	*YAxi=2;
	*Type=random(0,18);
	
	for(fuck=2;fuck<10;fuck++)
	{
		if(Data[fuck][2]==1)
			*FailFlag=2;
	}	
	
}
void  ControlBox(u8 x,u8 y,u8 mood,u8 dir)
{
	//dir指出方向，0,为横版，1为竖版
	if(mood==1)
	{       SetPaintMode(0,COLOR_Black);
	if(dir==1) 
		Rectangle(22+10*y,22+10*x,32+10*y,32+10*x,1);
	else 
		
        Rectangle(22+8*x,22+8*y,30+8*x,30+8*y,1);
	SetPaintMode(0,COLOR_Red);
	if(dir==1) 
		Rectangle(23+10*y,23+10*x,31+10*y,31+10*x,1);
	else
        Rectangle(23+8*x,23+8*y,29+8*x,29+8*y,1);
	}
	
	else
	{
		SetPaintMode(1,COLOR_Black);
		if(dir==1) 
			
			Rectangle(22+10*y,22+10*x,32+10*y,32+10*x,1);
		else
			Rectangle(22+8*x,22+8*y,30+8*x,30+8*y,1);
		
	}
	
}
void TotalRefreshLCD(u8  Data[][22],u8 dir)
{
	u8 t,s;
	SetPaintMode(1,COLOR_Black);
	if(dir==0)
		
		Rectangle(30,22,110,190,1);
	
	
	else
		Rectangle(22,32,232,132,1);  
	
	
	for(t=1;t<11;t++)
	{
		for(s=2;s<21;s++)
		{
			if(Data[t][s]==1)
				ControlBox(t,s,1,dir);
		}
	}
	
}
void CheckMark(u8 *mark ,u8  Data[][22],u8 dir)
{
	u8 m,t,s;
	u8 tMark=0;
	
	for(m=20;m>2;m--)
	{
		tMark=0;
		for(t=1;t<11;t++)
		{
			if(Data[t][m]==1)
				tMark++;
		}
		if(tMark==10)
		{
			for(t=m;t>2;t--)
			{
				for(s=1;s<11;s++)
				{
					Data[s][t]= Data[s][t-1];
				}
			}
			m++;
			TotalRefreshLCD(Data,dir);
			delay_ms(200);
			(*mark)++;
		}          
	}
}

void ShowBoxGUI(u8 x_axi,u8 y_axi,u8 type,u8 mood,u8 dir)
{
	u8 i;
	for(i=0;i<4;i++)
	{
		ControlBox(x_axi+BoxShape[type][i*2],y_axi+BoxShape[type][i*2+1],mood , dir);	
	}
}
u8 Bottom_Anti(u8 XAxi ,u8 YAxi,u8  Data[][22],u8 Type)
{
	u8 i;
	u8 Value=1;
	for(i=0;i<4;i++)   
	{   
		if(Data[XAxi+BoxShape[Type][2*i]][YAxi+BoxShape[Type][2*i+1]+1]==1)   
			Value=0;
	}  
	return Value;	 
}
u8 Right_Anti(u8 XAxi ,u8 YAxi,u8  Data[][22],u8 Type)
{
	u8 i;
	u8 Value=1; 
	
	for(i=0;i<4;i++)   
	{   
		if(Data[XAxi+BoxShape[Type][2*i]+1][YAxi+BoxShape[Type][2*i+1]]==1)   
			Value=0;
	}                 
	return Value;	 
	
}
u8 Lift_Anti(u8 XAxi ,u8 YAxi,u8  Data[][22],u8 Type)
{
	u8 i;
	u8 Value=1; 
	
	for(i=0;i<4;i++)   
	{   
		if(Data[XAxi+BoxShape[Type][2*i]-1][YAxi+BoxShape[Type][2*i+1]]==1)   
			Value=0;
	}                 
	return Value;	
	
}
u8 Change_Anti(u8 XAxi ,u8 YAxi,u8  Data[][22],u8 *Type)
{
	u8 i;
	u8 Value=1; 
	for(i=0;i<4;i++)   
	{   
		if(Data[XAxi+BoxShape[BoxShape[*Type][8]][2*i]][YAxi+BoxShape[BoxShape[*Type][8]][2*i+1]]==1)   
			Value=0; //???????????    
	}   
	return Value;   
	
}




u8 TerisBrick()
{
	u8 grade=0,mark=0;
	u8 GameGUIData[12][22];
	u8 KeyTemp;
	u8 XAxi,YAxi,Type,OriGrade=0;

        TickControlEN=1;
	u8* temp[2];
	u8 dir=0;
	
	temp[0]="竖版游戏模式";
	temp[1]="横版游戏模式";
         if(AccControlEN==1)
                        {
                          
                            ADXL345Init(0);
                        }
      
	
	
	while(OS_func_state<10)
	{
		switch(OS_func_state)
		{
		case 0:
			GUI_GameOpen("俄罗斯方块",&grade);
			
			OriGrade=grade;
			dir=ListGUI(temp,"选择游戏方向",2);  //dir 表征运动方向，0：横版，1竖版
			dir--;
			Clear_Screen();
			OS_func_state=1;
			
			break;
		case 1:
			
			TerisBrickInit(GameGUIData,12,22);
			_EINT();
			SetPaintMode(1,COLOR_Black);
			if(dir==0)
			{
				Rectangle(30,22,110,190,1);
				
			}
			else
				Rectangle(22,32,232,132,1);  
			PutString(275,70,"grade");
			PutString(275,110,"mark");
			Lcd_disp(2,200,"左右方向键移动，下键加速，上改变形状");  
			while(OS_func_state==1)
			{ 
                          back_light=back_light_set;
                          FontSetTotal(COLOR_Black);
			
			NumberDis(275,90,grade,3,1);
			NumberDis(275,130,mark,3,1);
			GenerateBox(&XAxi,&YAxi,&Type,GameGUIData,&OS_func_state);
			while(Bottom_Anti(XAxi,YAxi,GameGUIData,Type))
			{       key_data=KEYNULL;
			ShowBoxGUI(XAxi,YAxi,Type,1,dir);	
                        if(AccControlEN==1)
                        {
                          ADXL345ReadData();
                          ADXL345ShowData(0);
                          L3G4200DReadData();
                          L3G4200DShowData();
                        }
			if(KeyTemp==KEYDOWN_DOWN)
				delay_ms(150);
			else 
				delay_ms(500-70*grade);
			
			ShowBoxGUI(XAxi,YAxi,Type,0,dir);	
			YAxi++;
			if(AccControlEN==1)
                        {
                              if(dir==0)  //横版
                          {
                            if(AccX>3)
                              key_data=KEYLEFT_UP    ;
                             else if(AccX<-3)
                              key_data=KEYRIGHT_UP  ;
                             if(GyroY>400||GyroY<-400)
                             {
                               key_data=KEYUP_UP  ;
                                 delay_ms(200);
                             }
                               
                          }
                          else
                          {
                             if(AccY>3)
                              key_data=KEYLEFT_UP    ;
                             else if(AccY<-3)
                              key_data=KEYRIGHT_UP  ;
                               if(GyroX>400||GyroX<-400)
                               {
                               key_data=KEYUP_UP  ;
                               delay_ms(200);
                               }
                            
                          }
                        }
			switch(key_data)
			{
			case KEYLEFT_UP    :
				if(Lift_Anti(XAxi,YAxi,GameGUIData,Type)!=0)
					XAxi--;
				break;	
			case KEYRIGHT_UP  :
				
				if(Right_Anti(XAxi,YAxi,GameGUIData,Type)!=0)
					XAxi++;
				
				break;
			case KEYUP_UP  :
				if(Change_Anti(XAxi,YAxi,GameGUIData,&Type)!=0)
					Type=BoxShape[Type][8];
				break;
			case KEYDOWN_UP  :
				
				if(Bottom_Anti(XAxi,YAxi,GameGUIData,Type))
					YAxi++;
				break;
				
			case KEYCANCEL_UP    :
				if(MessageGui("提示信息","是否跳出?",1)==1)
				{
                                         TickControlEN=1;
					OS_func_state=2;
					return 1;
				}
				else
					TotalRefreshLCD(GameGUIData,dir);
				break;
				
			}
			KeyTemp=key_data;
                        key_data=KEYNULL;
			}
			
			for(u8 t=0;t<4;t++)
			{
				GameGUIData[XAxi+BoxShape[Type][2*t]][YAxi+BoxShape[Type][2*t+1]]=1;
			}
			ShowBoxGUI(XAxi,YAxi,Type,1,dir);	
			CheckMark(&mark,GameGUIData,dir);
			grade=OriGrade+mark/10;
			
			} 
			
			break;
		case 2:
			if(mark==0)
				MessageGui("超级菜鸟","学习下游戏规则",0);
			else if(mark>0&&mark<10)
				MessageGui("初学者","你还要加油哦",0);
			else if(mark>9&&mark<20)
				MessageGui("中级水平","哥们你很牛逼",0);
			else if(mark>19&&mark<30)
				MessageGui("高级水平","无敌哥！膜拜",0);
			else
				MessageGui("超级无敌","不是一般人！！",0);
			if( MessageGui("提示信息","是否继续",1)==1)
				OS_func_state=0;
			else 
			{
                          TickControlEN=1;
				OSTaskClose();
				
			}
			break;
			
		}
        }
		
		return 1;
		
		
		
}
void GUI_GameOpen(unsigned char *Name,unsigned char *grade)
{
	
	TaskBoxGUI("X-MOVE游戏系统启动");
	FontSet_cn(2,COLOR_Red);
	PutString_cn(35,76,Name);
	FontSet_cn(1,COLOR_Black);
	PutString_cn(80,110,"赵一鸣制作");
	PutString(100,130,"COPYRIGHT2010");
	delay_ms(2000);
	
	
	
	
}



void GUI_Gameclose(unsigned char mark)
{
	
	
	TaskBoxGUI("抱歉，您失败了");
	if(MessageGui("提示信息","是否继续？",1)==1)
		OS_func_state=0;
	else
		OS_func_state=4;
	
}

/*****************************五子棋算法部分*************************************/

//x,y是横纵坐标，Data是数组
//返回0：无子，1 ：黑子，2：白子
u8 ReadData(u8 x,u8 y,u16  Data[29])
{
	u8 t=y+x*15;
	u16 temp=0x03;
	temp=temp<<2*(t%8);
	return ((Data[t/8]&temp)>>(2*(t%8)));
}

//x,y是横纵坐标，Data是数组
// dat 0：无子，1 ：黑子，2：白子
void WriteData(u8 x,u8 y,u16 Data[29],u8 dat)
{
	u8 t=y+x*15;
	u16 Dat=dat;
	u16 temp=0x03;
	temp=temp<<2*(t%8);
	temp=0xffff-temp;
	Dat=Dat<<2*(t%8);
	Data[t/8]=(Data[t/8]&temp)|Dat;
}
void DrawDesk()
{
	u8 m;
	Clear_Screen();
	SetPaintMode(0,COLOR_Black);
	Rectangle(23,28,205,210,1);
	SetPaintMode(0,COLOR_Yellow);
	Rectangle(20,25,202,207,1);
	SetPaintMode(0,COLOR_Black);
	for(m=0;m<15;m++)
		Line(20,25+13*m,200,25+13*m);
	for(m=0;m<15;m++)
		Line(20+13*m,25,20+13*m,207);
	//Lcd_disp(240,12,"五子棋");
	//Lcd_disp(65,36,"赵一鸣之作");
}
void Drawchess(u8 x,u8 y, u8 mood)
{
	
	if(mood==2)//黑方
	{ 
		SetPaintMode(0,COLOR_Black);
		Circle(20+13*x,25+y*13,5,1);
	}
	//Rectangle(2+x*4,1+y*4,4+x*4,3+y*4,1);
	
	else if(mood==1)
	{
		
		SetPaintMode(0,COLOR_White);
		Circle(20+13*x,25+y*13,5,1);
		SetPaintMode(0,COLOR_Black);
		Circle(20+13*x,25+y*13,5,0);
	}
}

void PushChess(u8 x,u8 y,u16  Data[29],u8 mood)
{
	Drawchess(x,y,mood);
	WriteData(x,y,Data,mood);
	
	
	
}
u8 DrawKuang(u8 *x,u8 *y,u16  Data[29])
{
	
	u8 func_state=0;
     u8 GyroKey,myKey;
	while(func_state==0)
	{   
		SetPaintMode(0,COLOR_Black);
		Rectangle(14+*x*13,19+*y*13,26+*x*13,31+*y*13,0);
           if(GyroControlEN==1&&back_light>1&&GyroMenuEN)
		{
                     
                       delay_ms(200);
			L3G4200DReadData();
			L3G4200DShowData();
			
			delay_ms(200);
		}
       
        else
	        InputControl(); 
             
                GyroKey=GyroKeyBoardInputMethod(0,0,300,300);
        
        if(GyroKey!=KEYNULL)
            myKey=GyroKey;
        else
             myKey=key_data;
               GyroKey=KEYNULL;
       
		SetPaintMode(0,COLOR_Yellow);
		Rectangle(14+*x*13,19+*y*13,26+*x*13,31+*y*13,0);
		SetPaintMode(0,COLOR_Black);
		
		PutPixel(20+(*x)*13,19+(*y)*13);
		PutPixel(20+(*x)*13,(*y)*13+31);
		PutPixel(14+(*x)*13,(*y)*13+25);
		PutPixel(26+(*x)*13,(*y)*13+25);
		switch(myKey)
		{
		
		case KEYENTER_UP   :
			if(ReadData(*x,*y,Data)==0)
				func_state=1;
			break;
		case KEYCANCEL_UP    :
			return 0;
                default:
                    FourDirectionInputMethod(myKey,1,1,1,1,0,14,0,14,0,0, x,y);
		}
                myKey=KEYNULL;
             
	}
	return 1;
}
u8 ResultCheck(u16  Data[29],u8 color)  //成功测试 返回值：0：不成功，1 白方， 2黑方
{
	int x, y;
	// 判断横向
	for ( y = 0; y < 15; y++ )
	{
		for ( x = 0; x < 11; x++ )
		{
			if ( color ==ReadData(x,y,Data)  &&
				color == ReadData(x+1,y,Data) &&
				color == ReadData(x+2,y,Data)  &&
				color == ReadData(x+3,y,Data)  &&
				color == ReadData(x+4,y,Data)  )
				
				return color;
			
		}
	}
	// 判断纵向
	for ( y = 0; y < 11; y++ )
	{
		for ( x = 0; x < 15; x++ )
		{
			if ( color ==ReadData(x,y,Data) &&
				color ==ReadData(x,y+1,Data) &&
				color == ReadData(x,y+2,Data) &&
				color ==ReadData(x,y+3,Data) &&
				color == ReadData(x,y+4,Data) )
				
				return color;
			
		}
	}
	// 判断"\"方向
	for ( y = 0; y < 11; y++ )
	{
		for ( x = 0; x < 11; x++ )
		{
			if ( color == ReadData(x,y,Data)&&
				color == ReadData(x+1,y+1,Data) &&
				color ==ReadData(x+2,y+2,Data)&&
				color ==ReadData(x+3,y+3,Data)&&
				color == ReadData(x+4,y+4,Data) )
				
				return color;
			
		}
	}
	// 判断"/"方向
	for ( y = 0; y < 11; y++ )
	{
		for ( x = 4; x < 15; x++ )
		{
			if ( color ==  ReadData(x,y,Data) &&
				color ==  ReadData(x-1,y+1,Data) &&
				color ==  ReadData(x-2,y+2,Data) &&
				color ==  ReadData(x-3,y+3,Data) &&
				color ==  ReadData(x-4,y+4,Data) )
				
				return color;
			
		}
	}
	// 不满足胜利条件
	return 0;
	
	
	
}
void CalGameSatus(u16 Data[][29],u16 TotalCheseData[29],u8 mood)  //mood=2黑方判断，mood=1；白方判断
{
	u8 a,b,c,d;
	for(a=0;a<15;a++)
	{
		for(b=0;b<15;b++)
		{
			if(ReadData(a,b,TotalCheseData)==0)
			{
				d=0;
				for(c=1;c<5;c++)
				{
					if(ReadData(a-c,b,TotalCheseData)!=mood||a-c==0)   //左边
						break;
					else
						d++;
				}
				for(c=1;c<5;c++)
				{
					if(ReadData(a+c,b,TotalCheseData)!=mood||a-c==14)  //右边
						break;
					else
						d++;
				}
				
				WriteData(a,b,Data[0],d%4);    //写入横向数据
				WriteData(a,b,Data[1],d/4);  
				d=0;
				for(c=1;c<5;c++)
				{
					if(ReadData(a,b-c,TotalCheseData)!=mood||b-c==0)  //上边
						break;
					else
						d++;
				}
				for(c=1;c<5;c++)
				{
					if(ReadData(a,b+c,TotalCheseData)!=mood||b+c==14)
						break;
					else
						d++;
				}
				WriteData(a,b,Data[2],d%4);   //纵向数据
				WriteData(a,b,Data[3],d/4);   //纵向数据
				d=0;
				for(c=1;c<5;c++)
				{
					if(ReadData(a-c,b-c,TotalCheseData)!=mood||b-c==0||a-c==0)  //左上
						break;
					else
						d++;
				}
				for(c=1;c<5;c++)
				{
					if(ReadData(a+c,b+c,TotalCheseData)!=mood||b+c==14||a+c==14)
						break;
					else
						d++;
				}
				WriteData(a,b,Data[4],d%4);   //左斜数据
				WriteData(a,b,Data[5],d/4); 
				d=0;
				for(c=1;c<5;c++)
				{
					if(ReadData(a-c,b+c,TotalCheseData)!=mood||a-c==0||b+c==14)  //左下
						break;
					else
						d++;
				}
				for(c=1;c<5;c++)
				{
					if(ReadData(a+c,b-c,TotalCheseData)!=mood||a+c==14||b-c==0)  //右下
						break;
					else
						d++;
				}
				WriteData(a,b,Data[6],d%4);   //右斜数据
				WriteData(a,b,Data[7],d/4); 
			}
		}
	}
}
void  GameSatusInit(u16 Data1[][29])
{
	u8 m,n;
	for(m=0;m<8;m++)
	{
		for(n=0;n<29;n++)
		{
			Data1[m][n]=0;
		}
	}
}

void  CalPushPosition(u8 *X, u8 *Y,u16 Data1[][29],u16 Data2[][29],u16 TotalCheseData[29])
{
	long TotalMark,MaxMark=0;
	
	long MarkTransform[5]={0,100,400,2000,10000};
	u8 m,n,p,Mark;
	CalGameSatus(Data1,TotalCheseData,1);
	for(m=0;m<15;m++)
	{
		for(n=0;n<15;n++)
		{
			TotalMark=0;
			for(p=0;p<4;p++)
			{
				Mark=ReadData(m,n,Data1[2*p])+4*ReadData(m,n,Data1[2*p+1]);
				TotalMark+=  MarkTransform[Mark];
			}
			
			if(TotalMark>MaxMark)
			{
				*X=m,*Y=n;
				MaxMark=TotalMark;
			}
		}
	}
	CalGameSatus(Data2,TotalCheseData,2);
	for(m=0;m<15;m++)
	{
		for(n=0;n<15;n++)
		{
			TotalMark=0;
			for(p=0;p<4;p++)
			{
				Mark=  ReadData(m,n,Data2[2*p])+4*ReadData(m,n,Data2[2*p+1]);
				TotalMark+=MarkTransform[Mark];         
			}
			if(TotalMark>MaxMark)
			{
				*X=m,*Y=n;
				MaxMark=TotalMark;
			}
		}
	}  
	
	
	
}
/*void CalForcastPushPosition(u8 *X, u8 *Y,u16 Data1[][29],u16 Data2[][29],u16 TotalCheseData[29])
{
u8 X1,Y1; //第一步的坐标点
CalPushPosition( &X1,  &Y1, Data1[][29], Data2[][29],u16 TotalCheseData[29]);

  
}*/
void SendFiveMessage(u8 x,u8 y,u8 mood)
{
	u8 Message[5]="wb12";
	switch(mood)
		
	{
	case 0:   //握手
		if(PCID==0)
			W_PutString("wa1"); 
		
		else
			W_PutString("wa2");  
		break; 
		
	case 2:  //下棋
		Message[2]='0'+x;
		Message[3]='0'+y;
		W_PutString(Message);
		break;
	case 3:   //强退或认输
		W_PutString("wc");
		break;
		
	}
	
	
}
u8 ReceiveFiveMessage(u8 *x,u8 *y,u8 mood)
{
	
	u8 Count=0;
	while(WirelessProcessFlag==0&&Count<31)
	{
		delay_ms(1000);
		Count++;
	}
	if(Count==31)
	{
		MessageGui("抱歉","通信超时！",0);
		return 0;
	}
	else
	{       
		//PutString_C(uart_rxbuff);
		switch(mood)
		{
		case 0:
			if(uart_rxbuff[1]=='a')
			{      SendFiveMessage(0,0,0);
			MessageGui("恭喜成功","进入游戏",0);
			
			return 1;
			}
			else
			{
				//MessageGui("抱歉","通信有误！",0);
				return 1;
			}
			
		case 1:
			if(uart_rxbuff[1]=='b')
			{
				*x=uart_rxbuff[2]-0x30;
				*y=uart_rxbuff[3]-0x30;
				return 1;
			}
			else if(uart_rxbuff[1]=='c')
			{
				MessageGui("日死他","对方强行退出",0);
				return 0;
			}
			else
			{
				MessageGui("抱歉","通信有误！",0);
				return 0;
				
			}
			
			
		}
	}
	return 0;
	
}
u8 Five()
{
	u16 TotalCheseData[29];
	u16 myGameSatus[8][29];
	u16 itGameSatus[8][29];
	u8 func_state=0,choose;
	u8 XAxi,YAxi;
	u8* temp[5];
        TickControlEN=0;
	while(OS_func_state<11)
	{
		switch(OS_func_state)
		{
		case 0:
			TaskBoxGUI("超级五子棋");
                        
			func_state=0;
			temp[0]="人机对弈-我黑方";
			temp[1]="人机对弈-我白方";
			temp[2]="无线网络对战"; 
			temp[3]="自我挑战模式"; 
			temp[4]="机器对战演示"; 
			choose=ListGUI(temp,"选择游戏模式",5);
			if(choose==0)
			{
				OS_func_state=10;
				return 0;
			}
			
			else if(choose==5)
				OS_func_state=6;
			else
				
				OS_func_state= choose;
			if(choose==2)
				func_state=1;
			for(u8 t=0;t<29;t++)
			{
				TotalCheseData[t]=0;
			}
			XAxi=8,YAxi=8;
			DrawDesk();
			//func_state=1;
			break;
		case 1:   //黑方下棋
		case 2:
			
			
			if(func_state==0)   //我方下棋
			{
				if(DrawKuang(&XAxi,&YAxi,TotalCheseData))
					PushChess(XAxi,YAxi,TotalCheseData,2);
				else
				{
					OS_func_state=10;
				}
				if(ResultCheck(TotalCheseData,2)==2)  //胜利，跳出到成功界面
				{
					OS_func_state=5;  
				}
				else
					func_state=1;  //让给对方下棋
			}
			else   //对方下棋
			{
				GameSatusInit(myGameSatus);
				GameSatusInit(itGameSatus);
				CalPushPosition(&XAxi,&YAxi,myGameSatus,itGameSatus,TotalCheseData);
				PushChess(XAxi,YAxi,TotalCheseData,1);
				if(ResultCheck(TotalCheseData,1)==1)       
				{
					OS_func_state=5;
				}
				else
					func_state=0;   
				
			}
			break;
			
		case 4:
			if(func_state==0)
			{
				if(DrawKuang(&XAxi,&YAxi,TotalCheseData))
					PushChess(XAxi,YAxi,TotalCheseData,2);
				else
				{
					OS_func_state=10;
				}
				if(ResultCheck(TotalCheseData,2)==2)
				{
					OS_func_state=5;
				}
				else
					func_state=1;
			}
			else
			{
				if(DrawKuang(&XAxi,&YAxi,TotalCheseData))
					PushChess(XAxi,YAxi,TotalCheseData,1);
				else
				{
					OS_func_state=10;
				}
				if(ResultCheck(TotalCheseData,1)==1)
				{
					OS_func_state=5;
				}
				else
					func_state=0;
			}
			break;
		case 6:
			if(func_state==0)
			{
				GameSatusInit(myGameSatus);
				GameSatusInit(itGameSatus);
				CalPushPosition(&XAxi,&YAxi,myGameSatus,itGameSatus,TotalCheseData);
				PushChess(XAxi,YAxi,TotalCheseData,1);
				if(ResultCheck(TotalCheseData,1)==1)
				{
					OS_func_state=5;
				}
				else
					func_state=1;
				
			}
			else
			{
				GameSatusInit(myGameSatus);
				GameSatusInit(itGameSatus);
				CalPushPosition(&XAxi,&YAxi,myGameSatus,itGameSatus,TotalCheseData);
				PushChess(XAxi,YAxi,TotalCheseData,2);
				if(ResultCheck(TotalCheseData,2)==2)
				{
					OS_func_state=5;
				}
				else
					func_state=0;
				
			}
			break;
		case 3:
			switch(func_state)
			{
			case 0:     //申请态
				WirelessProcessFlag=0;
#if PCID==0
				
				if(   MessageGui("对方需入五子棋","发出申请？",1)==1)
				{      // delay_ms(3000);
					SendFiveMessage(0,0,func_state);
					BoxGUI("申请已发送");
					if(ReceiveFiveMessage(&XAxi,&YAxi,0))
					{
						func_state=1;
						DrawDesk();
						// SendFiveMessage(0,0,0);
					}
					else
						func_state=3;
					
				}
				else
					func_state=3;
#else                           
				BoxGUI("等待申请中");
				if(ReceiveFiveMessage(&XAxi,&YAxi,0))
				{
					
					func_state=1;
					
					DrawDesk();
				}
				else
					func_state=3;
#endif
				break;
			case 1:
				if(PCID==0)
				{
					
					if(DrawKuang(&XAxi,&YAxi,TotalCheseData))
					{
						PushChess(XAxi,YAxi,TotalCheseData,2);
						SendFiveMessage(XAxi,YAxi,2);
					}
					else
					{
						SendFiveMessage(0,0,3);
						func_state=3;
						
					}
					
					if(ResultCheck(TotalCheseData,2)==2)
					{
						
						OS_func_state=5;
						func_state=0;
						break;
					}
					
					WirelessProcessFlag=0;
					if(ReceiveFiveMessage(&XAxi,&YAxi,1)==1)
					{
						PushChess(XAxi,YAxi,TotalCheseData,1);
					}
					
					else
					{
						func_state=3;
						SendFiveMessage(0,0,3);
					}
					if(ResultCheck(TotalCheseData,1)==1)
					{
						
						OS_func_state=5;
						func_state=1;
						break;
					}
					
					
				}
				else
				{       WirelessProcessFlag=0;
				if(ReceiveFiveMessage(&XAxi,&YAxi,1)==1)
				{
					PushChess(XAxi,YAxi,TotalCheseData,2);
					
				}
				
				else
				{
					func_state=3;
					SendFiveMessage(0,0,3);
				}
				if(ResultCheck(TotalCheseData,2)==2)
				{
					
					OS_func_state=5;
					func_state=1;
					break;
				}
				if(DrawKuang(&XAxi,&YAxi,TotalCheseData))
				{
					PushChess(XAxi,YAxi,TotalCheseData,1);
					SendFiveMessage(XAxi,YAxi,2);
				}
				else
				{
					func_state=3;
					SendFiveMessage(0,0,3);
				}
				
				if(ResultCheck(TotalCheseData,1)==1)
				{
					
					OS_func_state=5;
					func_state=0;
					break;
				}
				
				}
				break;
			case 3:
				MessageGui("通信失败","游戏结束",0);
				
				OS_func_state=10;
				break;
				
				
			}
			
			
			
			
			break;
			
		case 5:
			if(func_state==0)
			{
				if(MessageGui("黑方胜利","是否继续？",1)==1)
					OS_func_state=0;
				else OS_func_state=10;
			}
			else
			{
				if(MessageGui("白方胜利","是否继续？",1)==1)
					OS_func_state=0;
				else
					OS_func_state=10;
			}
			
			break;
		case 10:
			if(MessageGui("提示信息","是否跳出游戏？",1)==1)
                          
			{ TickControlEN=1;
                    
                          OSTaskClose();
			return 1;
			
			}
			else
				OS_func_state=0;
			
			
			
			
		}
	}
	return 1;
	
	
}
#else

u8 TerisBrick()
{return 1;}
u8 Five(){return 1;}
void SendFiveMessage(u8 x,u8 y,u8 mood){}
#endif
