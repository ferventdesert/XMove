#include "config.h"
u8 time_show()
{
      u8 TotalFreshEN=1;
	
	TaskBoxGUI("时钟和日历显示");
	OS_func_state=1;

	while(OS_func_state==1)
	{

		Get_DS1302(rdata);

		clock_GUI(80,90,60,rdata,TotalFreshEN);
		calendar_GUI(150,3*X_Witch_cn,rdata,TotalFreshEN);
                TotalFreshEN=0;
    
        if(key_data==KEYCANCEL_UP    )
        {
            OSTaskClose();
            return 0;
        }
	}
	
	return 1;
}



u8 AccShow()
{
	u8* temp[4];
	
	u8 AccRange=0;
	u16 flag=0;
	temp[0]="2G高精度模式";
	temp[1]="4G监测";
	temp[2]="8G高范围监测";
	temp[3]="16G超高范围监测";
	u8 mUnit[4]={20,40,80,160};
	AccRange=ListGUI(temp,"请选择量程",4);
	if (AccRange==0)
	{
		OSTaskClose();
		return 0;
	}
	TaskBoxGUI_P(2,X_Witch_cn,307,224,temp[AccRange-1],0);
	ADXL345Init(AccRange-1);
	OS_func_state=1;
	
	while (OS_func_state==1)
	{
		ADXL345ReadData();
		ADXL345ShowData(AccRange-1);
		CurveDraw(20,2*X_Witch_cn,40,200,mUnit[AccRange-1],COLOR_Red,"x轴加速度",AccX,flag);
		CurveDraw(20,2*X_Witch_cn+65,40,200,mUnit[AccRange-1],COLOR_Blue,"y轴加速度",AccY,flag);
		CurveDraw(20,2*X_Witch_cn+130,40,200,mUnit[AccRange-1],COLOR_Yellow,"z轴加速度",AccZ,flag);
		
		delay_ms(100);
		if(flag<185)
			flag++;
		else
			flag=0;
		if(key_data==KEYCANCEL_UP    )
			return 0;
		
	}
	return 1;
	
}




u8 GyroKeyboard()
{
	u8 fuck[30];
	u8 flag=0;
	
	VirtualFullKeyBoard(20,20,fuck,&flag,30);
	OSTaskClose();
	return 1;
	
}



u8 OSThemeSet()
{
	TaskBoxGUI("欢迎使用图形界面配置向导");
	u8 *mOSTheme[2];
	mOSTheme[0]="菜单样式";
	mOSTheme[1]="主题设定";
	u8 choose1=ListGUI(mOSTheme,"配置主选单",2);
	if (choose1==0)
	{
		OSTaskClose();
		return 0;
	}
	u8* mThemeSet[3];
	u8 choose2;
	switch(choose1)
	{
	case 1:
		mThemeSet[0]="详细列表";
		mThemeSet[1]="无图标列表";
		mThemeSet[2]="大图标宫格";
		choose2=ListGUI(mThemeSet,"请选择菜单样式",3);
		if (choose2==0)
		{
			return 1;
		}
		else
			MenuType=choose2-1;
		break;
	case 2:
		mThemeSet[0]="湛蓝天空";
		mThemeSet[1]="超骚红色";
		mThemeSet[2]="黑丝诱惑";
		choose2=ListGUI(mThemeSet,"请选择您想要的主题",3);
		switch(choose2)
		{
		case 0:
			return 1;
		case 1:
			OSColor=COLOR_Blue;
			break;
		case 2:
			OSColor=COLOR_Red;
			break;
		case 3:
			OSColor=COLOR_Black;
			break;
		}
		break;

	}

	BoxGUI("X-MOVE动作感应系统");
	OSTaskClose();
	return 1;
}

u8 OSPictureShow()
{
	PictureShowBox(20,20,"系统图片浏览");
	OSTaskClose();
	return 1;
}
u8 OSCompass()
{       
        TaskBoxGUI("电子指南针(高斯)");
        
 
        float AngleXY=0;
        float XVaule,YValue;   //用于存储当前的要画的水平线的坐标
          HMC5883LInit();   //初始化HMC5883;
      
          CircleShowGUI(80,120,70,COLOR_Green);
          TaskBoxGUI_P(200,3*X_Witch_cn,200+5*Y_Witch_cn,5*X_Witch_cn,"X轴磁强",0);
	TaskBoxGUI_P(200,6*X_Witch_cn,200+5*Y_Witch_cn,8*X_Witch_cn,"Y轴磁强",0);
        TaskBoxGUI_P(200,9*X_Witch_cn,200+5*Y_Witch_cn,11*X_Witch_cn,"Z轴磁强",0);
        OS_func_state=1;
	
	while(OS_func_state==1)
	{
		back_light=back_light_set;
		FontMode(1,COLOR_White);
		XVaule=70*sin(AngleXY);
		YValue=70*cos(AngleXY);
		SetPaintMode(0,COLOR_Red);
		
		Line((u16)(80-XVaule),(u16)(120+YValue),(u16)(80+XVaule),(u16)(120-YValue));
		  delay_ms(100);
		SetPaintMode(0,COLOR_Green);
		
                 HMC5883LReadData();
      
                   HMC5883LShowData();
			AngleXY=atan((float)(ComX/ComY));
			Line((u16)(80-XVaule),(u16)(120+YValue),(u16)(80+XVaule),(u16)(120-YValue));
	               ShowMountGUI(201,4*X_Witch_cn,ComX,7,COLOR_Red,1);
			ShowMountGUI(201,7*X_Witch_cn,ComY,7,COLOR_Red,1);
                        ShowMountGUI(201,10*X_Witch_cn,ComZ,7,COLOR_Red,1);

		if (key_data==KEYCANCEL_UP)
		{
			OS_func_state=0;
                      
			OSTaskClose();
		}
              
		
		
	}
                           
	OSTaskClose();
	return 1;

}
u8 OSUsualStatic()
{
	u8 *fuck[4];
	u16 num[4]={30,80,100,30};
	fuck[0]="陀螺键盘";
	fuck[1]="时间显示";
	fuck[2]="空中鼠标";
	fuck[3]="电子罗盘";
	HistogramGUI(fuck,num,4,"常用软件使用统计（次数）");
	OSTaskClose();
	return 1; 
}
u8 PressureTest()
{
	long mPressure,mTemper;
	u8 flag=0;
	
	u8* temp[2];
	u8 choose=0;
	temp[0]="曲线模式";
	temp[1]="数据直显模式";	
	choose=ListGUI(temp,"选择数据显示模式",2);
        OS_func_state=1;
	if(choose==0)
	{
		OSTaskClose();
		return 0;
	}
	TaskBoxGUI_P(7,27,307,224,"气压和温度状态",0);
	switch(choose)
	{
		
	case 2:
		while(OS_func_state==1)
		{
			BMP085ReadData(3,&mPressure,&mTemper);
			if(!CurveDraw(9,30,60,240,180,COLOR_Red,"气压值帕斯卡",(float)(mPressure)/1000,flag))
                            if(!MessageGui("检查运行参数","是否继续？",1))
                              break;
                              
			if(!CurveDraw(9,120,60,240,60,COLOR_Blue,"温度摄氏度",(float)(mTemper)/10,flag))
                          if(!MessageGui("检查运行参数","是否继续？",1))
                              break;
			delay_ms(700);
			if (flag==240)
			{
				flag=0;
			}
			else
				flag++;
			if (key_data==KEYCANCEL_UP    )
			{
				OSTaskClose();
				return 0;
				
			}
     	
		}
                break;
		
		
	case 1:
		FontSet(3,COLOR_Red);
		FontSet_cn(4,COLOR_Red);
		FontMode(1,COLOR_White);
		Lcd_disp(20,3*X_Witch_cn,"当前气压：单位帕斯卡");
		Lcd_disp(20,7*X_Witch_cn,"当前温度：单位摄氏度");
		while (OS_func_state==1)
		{
			BMP085ReadData(3,&mPressure,&mTemper);
			NumberDis(20,4*X_Witch_cn, mPressure,6,3);
			ShowMountGUI(20,8*X_Witch_cn, mTemper/10,4,COLOR_Red,3);
			delay_ms(700);
			if (key_data==KEYCANCEL_UP    )
			{
				OSTaskClose();
				return 0;
			}
		}
                break;
		
	}
	
	
	return 1;
}
u8 SkyMouse()
{

	u8 CurrentKey,LastPort;
	u8  LeftKeyDelay=0;
        u8 choose;
	u8 *temp[7];
	temp[0]="画图";
	temp[1]="计算器";
	temp[2]="网络浏览器";
	temp[3]="记事本";
	temp[4]="任务管理器";
	temp[5]="文本输入工具";
         temp[6]="幻灯片演示工具";
	
	TaskBoxGUI("空中鼠标模式");
        ADXL345Init(0);
          KeyBoardFuncIntroGUI(0,"左键","右键","滚轮","切换","手势","跳出");
	if(!MessageGui("LCD即将休眠","是否继续？",1))
	{
		OSTaskClose();
		return 0;
	}
	BackLightTo(0);
	
	delay_ms(1000);
	LCDSetSleep();
	OS_func_state=1;
	while (OS_func_state==1)
	{   OSLightControl(2);   
             L3G4200DReadData();
               ADXL345ReadData();
          
             
	if(!GetCurrentKey(&LastPort,&CurrentKey,1)) 
	{
			
	}
	switch(CurrentKey)
	{
        case KEYUP_UP:
          LeftKeyDelay=0;
           CurrentKey=KEYNULL;
          break;
          case KEYLEFT_DOWN:
                   myMEMSData[KEYDF]=KEYLEFT_DOWN;
                 SendWirelessData();
                 delay_ms(10);	
        case KEYUP_DOWN:
             //myMEMSData[KEYDF]=KEYUP_DOWN;
             if(LeftKeyDelay==0)
             {
               delay_ms(200);
               LeftKeyDelay=1;
             }
             else
             {
                 SendWirelessData();
                 delay_ms(10);	
             }
             break;
          case KEYRIGHT_DOWN:
              myMEMSData[KEYDF]=KEYRIGHT_DOWN;
             SendWirelessData();
             delay_ms(800);
             break;
          case KEYENTER_DOWN:
       
                  myMEMSData[KEYDF]=KEYENTER_DOWN;
                   SendWirelessData();
                   delay_ms(10);
                
             break;
      
	
	case  KEYSPECIAL:
		BackLightSet(OSBackLight);
		
                delay_ms(500);
                _EINT();
                 choose=ListGUI(temp,"请选择快捷菜单",7);
		_DINT();
		if (choose==0)
		{
			 OSTaskClose();
			return 0;
		}
		else if (choose==6)  // 文本输入工具
		{	
			u8 flag=0;
                        u8 Buff[20];
			_EINT();
			//myMEMSData[PRODF]=choose;
			while(MessageGui("提示信息","输入字符？",1))
			{
                       
				if(VirtualFullKeyBoard(20,20,Buff,&flag,20))
                                {
                                  for(u8 i=0;i<20;i++)
                                  {
                                     myMEMSData[L3G4200DDF+i] =Buff[i];
                                  }
                                  
				SendWirelessData();
                                }
                               for(u8 i=0;i<20;i++)
                                Buff[i]=0;
                        
                                flag=0;
                        }
            
		}
		else 
		{
			myMEMSData[PRODF]=choose;
                           myMEMSData[KEYDF]=KEYNULL;
			SendWirelessData();
                        delay_ms(1000);
                     
			
		}
               _DINT();
                myMEMSData[PRODF]=0; //一定记得此处清零！
	         myMEMSData[KEYDF]=KEYNULL;
		delay_ms(2000);
		LCDSetSleep();  
                    _EINT();
		break; 
        default:
          SendWirelessData();
	  delay_ms(5);
          break;

	}
        
      
	
	
	}
	return 1;
}

u8 HeightTest()
{
	TaskBoxGUI("楼层和高度检测");
	u8 *temp[3];
	u8 myFloor=0;
	long myPressure;
        long myAveragePressure;
        float myHeight=0;
	long T;
	temp[0]="海拔监测";
        temp[1]="楼层监测";
	temp[2]="参数修正";
	u8 choose=ListGUI(temp, "请选择功能",3);
	OS_func_state=1;
	switch(choose)
	{
	case 0:
		return 0;
        case 1:
                TaskBoxGUI("高度信息,仅供参考");
                   FontMode(3,COLOR_White);
                while (OS_func_state)
		{
                  myAveragePressure=0;
                 for(u8 i=0;i<5;i++)  //求平均，获得更稳定的读值
                 {
                     BMP085ReadData(3,&myPressure,&T);
                      myAveragePressure+=myPressure;
                 }
                 myAveragePressure=myAveragePressure/5;
           
                 myHeight=(float)(101325-myAveragePressure)/10.0;
                 ShowMountGUI(20,4*X_Witch_cn,myHeight,5,COLOR_Red,3);
                 if (key_data==KEYCANCEL_UP    )
			{
				OSTaskClose();
				return 0;
			}
                 delay_ms(1000);
                  
                }
                break;
          
	case 2:
		TaskBoxGUI("当前楼层信息");
		FontSet(3,COLOR_Red);
                FontMode(1,COLOR_White);
		Lcd_disp(20,3*X_Witch_cn,"当前楼层数");
		while (OS_func_state)
		{        
			BMP085ReadData(3,&myPressure,&T);
			myFloor=myHeightInfo.OriginFloor+(myHeightInfo.OriginPressure-myPressure)/(12*myHeightInfo.FloorStep);
			NumberDis(20,4*X_Witch_cn, myFloor,2,3);
			InputControl();
			if (key_data==KEYCANCEL_UP    )
			{
				OSTaskClose();
				return 0;
			}
		}
                break;
	case 3:
		TaskBoxGUI("高程数据修正向导");
		if(!SliderGUI(20,80,160,"楼层间距",2,5,1,&myHeightInfo.FloorStep))
		{
			OSTaskClose();
			return 0;
		}
		if (!SliderGUI(20,80,160,"当前楼层值",1,20,1,&myHeightInfo.OriginFloor))
		{
			OSTaskClose();
			return 0;
		}
		if(MessageGui("提示信息","刷新原始气压？",1))
			BMP085ReadData(3,&myHeightInfo.OriginPressure,&T);
		MessageGui("提示信息","数据刷新完毕",2);
                break;

	}
	return 1;
}
u8 OSConfigSet()
{
	TaskBoxGUI("欢迎使用系统配置向导");
	u8 *temp[6];
	temp[0]="旋转检测";
	temp[1]="加速度检测";
	temp[2]="背光时长";
	temp[3]="背光亮度";
	temp[4]="定时器";
	temp[5]="时间设定";
	u8 choose=ListGUI(temp,"配置选单",6);
	
	switch(choose)
	{
	case 0:
		OSTaskClose();
		return 0;
	case 1:
		GyroControlEN=	MessageGui("配置选项","开启旋转检测？",1);
		break;
	case 2:
		AccControlEN=	MessageGui("配置选项","开启加速度检测？",1);
		break;
	case 3:
		SliderGUI(20,80,150,"背光时长设定",1,60,1,&back_light_set);
		
		break;
	case 4:
		SliderGUI(20,80,150,"背光强度设定",1,500,25,&OSBackLight);
		BackLightTo(OSBackLight);
		break;
	case 5:
		TickControlEN=MessageGui("配置选项","开启定时器？",1);
		break;
	case 6:
          if(TimeSetGUI())
            MessageGui("提示信息","时间设定成功！",0);
          else
                      MessageGui("提示信息","设定已取消",0);
              

                         break;
	
			

	}
	return 1;
}

u8 NFS()
{
	
          KeyBoardFuncIntroGUI(0,"前进","后退","左拐","右拐","确认","跳出");
	
	  return  CommonControl();
               
                  
            
  
}
u8  COD()
{

	u8 LastPort,CurrentKey;
        KeyBoardFuncIntroGUI(0,"前进","后退","功能键","换枪","锁定","跳出");
	if (!MessageGui("第二手柄已就绪否？","否则将无法继续",1))
	{
		OSTaskClose();
		return 0;
	}
          KeyBoardFuncIntroGUI(1,"开枪","瞄准","上膛","卧倒","无","无");
   
        if(!NetProEnterConfirm())
           return 0;
        SendWirelessData();  //提前发送数据
      
       
	
	OS_func_state=1;
	while (OS_func_state)
	{      OSLightControl(2);
              L3G4200DReadData();
               if(!GetCurrentKey(&LastPort,&CurrentKey,1)) 
               {
                  if(CurrentKey!=KEYENTER_DOWN)
                  {
                    L3G4200DShowData();
                    {
                      if(GyroX>20||GyroX<-20||GyroZ>20||GyroZ<-20)
                        SendWirelessData();
                    }
                 
                  }
                    delay_ms(15);
                
               }
              
                 
             if(  NetProCloseConfirm(CurrentKey))
                   return 1;
            
  
         }
         return 1;
    
}

u8 AHRS()
{
    return  CommonControl();
}

u8  Gravity()
{
	
	TaskBoxGUI("PC重力感应屏幕");
	
        if(!NetProEnterConfirm())
           return 0;
	
        key_data=KEYNULL;
        ADXL345Init(0);
	while(OS_func_state==1)
	{
                  OSLightControl(2);
		ADXL345ReadData();
		ADXL345ShowData(0);
		if (AccX>8)
		{
			//myMEMSData[PRODF]=1;   //朝上？
		}
		else if (AccX<-8)
		{
			//myMEMSData[PRODF]=2;  //朝下
		}
		else if (AccY>8)
		{
			//myMEMSData[PRODF]=3;
		}
		else if (AccY<-8)
		{
			//myMEMSData[PRODF]=4;
		}
		//if (myMEMSData[PRODF]!=0)
		{

			MessageGui("提示信息","电脑将屏幕翻转",2);
			TaskBoxGUI("PC重力感应屏幕");
			SendWirelessData();
			
		
		}
                delay_ms(3000);
                myMEMSData[PRODF]=0;

		  if(key_data==KEYCANCEL_UP)
                  {
                    OSTaskClose();
				OSLightControl(0);
				
                   return 1;
                  }
	}
        return 1;
	
	
}

u8 Thunder()
{
	u8 LastPort,CurrentKey;
	u8* temp[3];
	u8 choose;
	temp[0]="菜单模式";
	temp[1]="游戏模式";
	temp[2]="跳出";
	KeyBoardFuncIntroGUI(0,"机枪","导弹","无","菜单","无","跳出");
	   if(!NetProEnterConfirm())
           return 0;
        ADXL345Init(0);
	
	
	myMEMSData[PRODF]=1;
	while (OS_func_state==1)
	{
		OSLightControl(2);
		 GetAllSensorData();
		if (!GetCurrentKey(&LastPort,&CurrentKey,1))
		{
			SendWirelessData();
			delay_ms(15);	
		}
		if(CurrentKey==KEYSPECIAL)
		{
			BackLightSet(OSBackLight);
			_EINT();
			choose=	ListGUI(temp,"请选择工作模式",3);
			if(choose==3&&MessageGui("提示信息","确认跳出吗",1))
			{
				OSTaskClose();
				OSLightControl(0);
				return 1;
			}
			else
				myMEMSData[PRODF]=choose;
			
			_DINT();
			delay_ms(1000);
			LCDSetSleep();  
		}
		
	}
	return 1;
}

u8 BodyFit()
{
   return  HandRecongiton();
  
}

u8 CommonControl()
{
     u8 LastPort,CurrentKey;
	   if(!NetProEnterConfirm())
           return 0;
	   ADXL345Init(0);
        
	   while(OS_func_state==1)
           {
	   OSLightControl(2);
	   if(!GetCurrentKey(&LastPort,&CurrentKey,1))
	   {
		    HMC5883LReadData();
		   ADXL345ReadData();
	           L3G4200DReadData();
		   SendWirelessData();
		   delay_ms(40);
	   }
	   if(  NetProCloseConfirm(CurrentKey))
           {
         
                   return 1;	   
           }
		   
	}
        return 1;
}
u8 GeoWar()
{
           return  CommonControl();
        
}
u8 HAWX()
{
  
	u8 LastPort,CurrentKey;
    u8* temp[3];
	u8 choose;
	temp[0]="菜单模式";
	temp[1]="游戏模式";
	temp[2]="跳出";
       KeyBoardFuncIntroGUI(0,"发射","武器","无","菜单","无","跳出");
     if(!NetProEnterConfirm())
           return 0;
        ADXL345Init(0);
	//myMEMSData[PRODF]=1;
        while (OS_func_state==1)
	{
		OSLightControl(2);
	GetAllSensorData();
		if (!GetCurrentKey(&LastPort,&CurrentKey,1))
		{
			SendWirelessData();
			delay_ms(15);	
		}
		if(CurrentKey==KEYSPECIAL)
		{
			BackLightSet(OSBackLight);
			_EINT();
			choose=	ListGUI(temp,"请选择工作模式",3);
			if(choose==3&&MessageGui("提示信息","确认跳出吗",1))
			{
				OSTaskClose();
				OSLightControl(0);
				return 1;
			}
			else
				myMEMSData[PRODF]=choose;
			
			_DINT();
			delay_ms(1000);
			LCDSetSleep();  
                        CurrentKey=KEYNULL;
		}
	}
        return 1;
}

u8 WirelessControl()
{

    TaskBoxGUI("通信管理设置向导");
	
	u8 *temp[2];
	temp[0]="无线有线方式切换";
	temp[1]="本机号临时切换";
	MessageGui("请谨慎选择","否则可能造成通信失效",0);

	u8 choose=ListGUI(temp,"配置选单",2);
	
	switch(choose)
	{
	case 0:
		OSTaskClose();
		return 0;
	case 1:
		WirelessEN=MessageGui("通信信道切换","是：无线，否：有线",1);
		break;
	case 2:
		SliderGUI(20,80,150,"本机号切换",0,3,1,(u16*)(&UserID));
		break;

	}
	OSTaskClose();
	return 1;
	
}
u8 Waterlevel()
{
	float AngleXY,AngleYZ,AngleZX,AnverageAccX,AnverageAccY,AnverageAccZ;
	TaskBoxGUI("水准仪和倾角测量");
	float XVaule,YValue;   //用于存储当前的要画的水平线的坐标

        
	CircleShowGUI(80,120,70,COLOR_Blue);
	ADXL345Init(0);
	TaskBoxGUI_P(200,3*X_Witch_cn,200+5*Y_Witch_cn,5*X_Witch_cn,"X-Z角度",0);
	TaskBoxGUI_P(200,6*X_Witch_cn,200+5*Y_Witch_cn,8*X_Witch_cn,"Y-Z角度",0);
	OS_func_state=1;
	
	while(OS_func_state==1)
	{
		back_light=back_light_set;
		FontMode(1,COLOR_White);
		XVaule=70*sin(AngleXY);
		YValue=70*cos(AngleXY);
		SetPaintMode(0,COLOR_White);
		
		Line((u16)(80-XVaule),(u16)(120+YValue),(u16)(80+XVaule),(u16)(120-YValue));
		
		SetPaintMode(0,COLOR_Blue);
		for(u8 i=0;i<10;i++)
		{
			ADXL345ReadData();
			ADXL345ShowData(0);
			AnverageAccX+=AccX;
			AnverageAccY+=AccY;
			AnverageAccZ+=AccZ;
			delay_ms(10);
		}
		AnverageAccX/=10;
		AnverageAccY/=10;
		AnverageAccZ/=10;
		if(AnverageAccZ<2&&AnverageAccZ>-2)
		{
 
			AngleXY=atan((float)(AnverageAccY/AnverageAccX));
			Line((u16)(80-XVaule),(u16)(120+YValue),(u16)(80+XVaule),(u16)(120-YValue));
	    
				
		}
		else
		{
                 
			AngleYZ=atan((float)(AnverageAccY/AnverageAccZ));
			AngleZX=atan((float)(AnverageAccX/AnverageAccZ));
			ShowMountGUI(201,4*X_Witch_cn,AngleYZ*57,7,COLOR_Red,1);
			ShowMountGUI(201,7*X_Witch_cn,AngleZX*57,7,COLOR_Red,1);
			delay_ms(500);
			
		}
		
		if (key_data==KEYCANCEL_UP)
		{
			OS_func_state=0;
			OSTaskClose();
		}
		
		
	}
	
	
	return 1;
}

u8 HandRecongiton()
{
	u8 LastPort,CurrentKey;

	TaskBoxGUI("Gesture Recognition");
	
	KeyBoardFuncIntroGUI(0,"无","无","无","无","笔触","跳出");
      
      if(!NetProEnterConfirm())
        return 0;
	
	while(OS_func_state==1)
	{   
         
		
		if (!GetCurrentKey(&LastPort,&CurrentKey,0))
		{
                  
			switch(CurrentKey)
			{
			case KEYENTER_DOWN:
                              OSLightControl(2);
                                 L3G4200DReadData();
                                myMEMSData[KEYDF]=CurrentKey;
                                
				SendWirelessData();
                                delay_ms(10);	
				break;
			case KEYSPECIAL:
				OS_func_state=44;
				break;
                        case KEYENTER_UP: 
                              OSLightControl(0);
                              myMEMSData[KEYDF]=CurrentKey;
                                 
				SendWirelessData();
                                CurrentKey=KEYNULL;
				break;
			}
                        
			
			
		}
               
              
	}
        _EINT();
	if (MessageGui("提示信息","确认跳出吗?",1))
	{
	OSTaskClose();
	return 1;
	}
        return 1;

  
}

u8 TextInput()
{
  u8 Buff[30];
  u8 Buffflag=0;
   if(!T9InputTask( 5, 20, Buff,&Buffflag,30))
   {
#if PCID==3
       MessageGui("提示信息","保存输入吗",1))
#endif 
      OSTaskClose();
   }
   return 1;
}
u8 RemoteCtl()
{
  u8 LastPort,CurrentKey;
	//KeyBoardFuncIntroGUI(0,"机枪","导弹","无","菜单","无","跳出");
	   if(!NetProEnterConfirm())
           return 0;
        ADXL345Init(0);
	
	
	
	while (OS_func_state==1)
	{
		OSLightControl(2);
		ADXL345ReadData();
		L3G4200DReadData();
		if (!GetCurrentKey(&LastPort,&CurrentKey,1))
		{
                      
			
                        switch(CurrentKey)
			{
			case KEYLEFT_DOWN:
                        case KEYRIGHT_DOWN: 
                       case KEYENTER_DOWN: 
                            
                               myMEMSData[KEYDF]=CurrentKey;
				break;
			}
                        SendWirelessData();
			delay_ms(15);
                         if(  NetProCloseConfirm(CurrentKey))
                       {
          
                          return 1;	   
                      }
		}
		
		
	}
        return 1;
         
	
 
}
u8 Demo()
{
  return COD();
}
u8 Picasa()
{
  KeyBoardFuncIntroGUI(0,"前","后","放大","缩小","感应","跳出");
   return  CommonControl();
}
u8 Ball()
{      MessageGui("提示信息","未部署该功能",0);
      OSTaskClose();
  return 1;

  
}

u8 Fighter()
{
       u8 LastPort,CurrentKey;
	   if(!NetProEnterConfirm())
           return 0;
	   ADXL345Init(3);
      
	   while(OS_func_state==1)
           {
	   OSLightControl(2);
	   if(!GetCurrentKey(&LastPort,&CurrentKey,1))
	   {
		     L3G4200DReadData();
                     ADXL345ReadData();
                     L3G4200DShowData();
                        ADXL345ShowData(3);
                      OSLightControl(2);
                     if(AccX>40)
                     {
                          myMEMSData[MOVEFLAG]=1;
                          SendWirelessData();
                           delay_ms(1000);	
                              myMEMSData[MOVEFLAG]=0;
                     }                   
		      switch(CurrentKey)
			{

                         case KEYENTER_DOWN:
                                 
                                myMEMSData[KEYDF]=CurrentKey;
                                
				SendWirelessData();
                                delay_ms(30);	
				break;
                            default:
                            
                              delay_ms(30);	
				break;
                        }
                
	   }
	   if(  NetProCloseConfirm(CurrentKey))
           {
          
                   return 1;	   
           }
		   
	}
        return 1;
}
u8 Crysis()
{
     return  COD();
}
u8 Sky()
{
    u8 LastPort,CurrentKey;
	   if(!NetProEnterConfirm())
           return 0;
	   ADXL345Init(0);
         
	   while(OS_func_state==1)
           {
	   OSLightControl(2);
	   if(!GetCurrentKey(&LastPort,&CurrentKey,1))
	   {
		     L3G4200DReadData();
                      OSLightControl(2);
		switch(CurrentKey)
			{
                    
                           
                         case KEYENTER_DOWN:
                                
                                
                                myMEMSData[KEYDF]=CurrentKey;
                                
				SendWirelessData();
                                delay_ms(30);	
				break;
                            default:
                              SendWirelessData();
                              delay_ms(30);	
				break;
                        }
                
	   }
	   if(  NetProCloseConfirm(CurrentKey))
           {
          
                   return 1;	   
           }
		   
	}
        return 1;
}
