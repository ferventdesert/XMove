#include "config.h"

/*
mydefine.c
ELPOS2.0的底层基本函数和全局变量声明
Copyright (c) 2010，赵一鸣
buptzym@bupt.edu.cn
All rights reserved.
本程序仅供学习参考，不提供任何可靠性方面的担保；请勿用于商业目的
*/





unsigned char    OS_index_data,key_data,OS_count=0,OS_func_state=0,WirelessProcessFlag=0,MenuType=2,OS_index_ago=0,
                GyroControlEN=1,AccControlEN=1,TickControlEN=1,WirelessEN=1,UserID=PCID,GyroMenuEN=0,InnerFuncState,
                 KeyRepeatEN=0;

u16 OSBackLight=300,back_light=10,back_light_set=10,OSColor=COLOR_Blue;
long mPassWord=123;



u8 isGyroExisted; 
u8 isAccExisted; 
u8 isComExisted; 
u8 isGyroEnable=1;
u8  myNodeFreshSpeed=2;  //刷新速度
u8 myWorkMode=0X40;
 
u8 ChanelID=0; 
const u16 GetCounterByNodeFreshSpeed[]={2000,1000,500,250,125,62,31,15};
u16 GetSendCounter()
{
  return GetCounterByNodeFreshSpeed[myNodeFreshSpeed];
}









#if CHSORENG==0
const struct  TaskPCB  myTaskPCB[SIZE_OF_Task]= //菜单定义
{
	{"系统主菜单",MenuGUI,"全局功能显示",5,{0,6,14,20,8,33,9,10}},   //0
	{"系统时间",time_show,"查看当前系统的时间",8,{8,0}},    //1
	{"加速度监测",AccShow,"三轴加速度检测",24,{8,0}},   //2
	{"五子棋",Five,"人机和无线对战",23,{9,0}},   //3
	{"俄罗斯方块",TerisBrick,"经典游戏,支持横竖屏",8,{9,0}},   //4
	{"气压和温度",PressureTest,"显示温度和气压状态",24,{8,0}},    //5
	{"动作感应键盘",GyroKeyboard,"感受全新的字符动作输入",17,{14,0}},   //6
	{"通信管理",WirelessControl,"管理通信方式和协议",11,{10,0}},   //7
	{"传感器监测",MenuGUI,"检测当前环境状态",20,{0,6,1,2,5,19,12,16}},   //8
	{"娱乐功能",MenuGUI,"您可使用该系统自带游戏",22,{0,4,3,4,15,28}},   //9
	{"系统管理",MenuGUI,"您可对该系统设置和管理",11,{0,4,7,11,13,17}},   //10
	{"运行配置",OSConfigSet,"对功耗和功能的设置",19,{10,0}},   //11
	{"水准仪",Waterlevel,"水平角度测试仪",18,{8,0}},   //12   暂时无用
	{"界面设定",OSThemeSet,"设置菜单样式和主题等",9,{10,0}},    //13
	{"次世代功能",MenuGUI,"超越时代的九轴动作感应",21,{0,6,18,22,6,27,31,32}},   //14
	{"图片浏览",OSPictureShow,"浏览系统保存的图片",25,{9,0}},   //15
	{"电子指南针",OSCompass,"电子指南针提供方向信息",10,{8,0}},   //16
	{"常用功能统计",OSUsualStatic,"最常用功能统计",23,{10,0}},   //17
	{"空中鼠标！",SkyMouse,"无线动作感应鼠标！",7,{14,0}},   //18
        {"高度检测",HeightTest,"获得当前高度信息",21,{8,0}},   //19
        {"动作感应游戏",MenuGUI,"远程动作控制电脑游戏",25,{0,8,21,36,37,23,25,26,29,30}},   //20
        {"极品飞车",NFS,"风驰电掣的快感",16,{20,0}},   //21
         {"AHRS姿态",AHRS,"实时姿态计算和控制",24,{14,0}},   //22
         {"使命召唤",COD,"双系统的FPS超爽感受！",15,{20,0}},   //23
         {"PC重力感应",Gravity,"可改变电脑屏幕方向",9,{20,0}},   //24
         {"雷电3D版",Thunder,"经典三维空战游戏",7,{20,0}},   //25
         {"几何战争",GeoWar,"双手柄控制游戏",6,{20,0}},   //26
         {"手势识别",HandRecongiton,"",22,{14,0}},   //27
         {"文本输入",TextInput,"",8,{14,0}},   //28
         {"鹰击长空",HAWX,"",14,{20,0}},   //29
         {"四肢健身",BodyFit,"",22,{20,0}},   //30
          {"远程机械控制",RemoteCtl,"动作同步跟踪控制",11,{14,0}},   //31
           {"虚拟实景",Demo,"",21,{14,0}},   //32
           {"PC控制中心",MenuGUI,"快捷控制中心",21,{0,4,24,34,35,38}},   //33
            {"PC图片浏览",Picasa,"",21,{33,0}},   //34
            {"弹珠球",Ball,"",21,{33,0}},   //35
             {"街头霸王",Fighter,"",21,{20,0}},   //36
              {"孤岛危机",Crysis,"",21,{20,0}},   //37
               {"太空探索",Sky,"",9,{33,0}},   //38
	
};

#endif

#if CHSORENG==1
const struct  TaskPCB  myTaskPCB[SIZE_OF_Task]= //菜单定义
{
	{"Main Menu",MenuGUI,"全局功能显示",5,{0,5,14,20,8,9,10}},   //0
	{"System Time",time_show,"查看当前系统的时间",6,{8,0}},    //1
	{"Acc Watch",AccShow,"三轴加速度检测",9,{8,0}},   //2
	{"Go Bang",Five,"欢乐五子棋,人机和无线对战",8,{9,0}},   //3
	{"Terris",TerisBrick,"经典游戏,支持横竖屏",10,{9,0}},   //4
	{"Temp.&Press.",PressureTest,"显示温度和气压状态",11,{10,0}},    //5
	{"Motion Keys",GyroKeyboard,"感受全新的字符动作输入",12,{14,0}},   //6
	{"Wireless Net",WirelessControl,"管理通信方式和协议",13,{10,0}},   //7
	{"EnvirWatch",MenuGUI,"检测当前环境状态",5,{0,3,1,2,5}},   //8
	{"Recreation",MenuGUI,"您可使用该系统自带游戏",6,{0,4,3,4,15,28}},   //9
	{"SysManage",MenuGUI,"您可对该系统设置和管理",8,{0,4,7,11,13,17}},   //10
	{"RunConfig.",OSConfigSet,"对功耗和功能的设置",9,{10,0}},   //11
	{"WaterLevel",Waterlevel,"水平角度测试仪",6,{14,0}},   //12   暂时无用
	{"UI Set",OSThemeSet,"设置菜单样式和主题等",6,{10,0}},    //13
	{"Miracle",MenuGUI,"超越时代的九轴动作感应",8,{0,7,18,6,12,16,19,22,27}},   //14
	{"PictrueView",OSPictureShow,"浏览系统保存的图片",5,{9,0}},   //15
	{"ECompass",OSCompass,"电子指南针提供方向信息",6,{14,0}},   //16
	{"Com.Statics",OSUsualStatic,"最常用功能统计",9,{10,0}},   //17
	{"AirMouse",SkyMouse,"无线动作感应鼠标！",9,{14,0}},   //18
        {"HeightTest",HeightTest,"获得当前所在的楼层！",9,{14,0}},   //19
        {"Motion Games",MenuGUI,"远程动作控制电脑游戏",9,{0,7,21,23,24,25,26,29,30}},   //20
         {"NFS",NFS,"风驰电掣的快感",9,{20,0}},   //21
         {"AHRS",AHRS,"实时姿态计算和控制",9,{14,0}},   //22
         {"COD",COD,"双系统的FPS超爽感受！",9,{20,0}},   //23
         {"PCGravity",Gravity,"可改变电脑屏幕方向",9,{20,0}},   //24
         {"Thunder3D",Thunder,"经典三维空战游戏",9,{20,0}},   //25t
         {"GeoWar",GeoWar,"双手柄控制游戏",9,{20,0}},   //26
         {"HandRecog.",HandRecongiton,"",9,{14,0}},   //27
         {"TextInput",TextInput,"",9,{14,0}},   //28
         {"HAWX",HAWX,"",9,{20,0}},   //29
         {"RehabCenter",BodyFit,"",9,{20,0}},   //30
	

};
#endif
struct HeightInfo  myHeightInfo={1,4,101325};





u8 (* OS_func)();  //全局函数指针


const unsigned char Rx_Address[3]={104,103,102 };   //发送地址，暂时必须通过软件修改该值
const unsigned char Tx_Address[3]={100,101,102};     //本机地址，用于SPI无线模式
u8 InputPortState;

u8 myMEMSData[PACKETLENGTH];
u8 uart_rxbuff[PACKETLENGTH];
float AccX,AccY,AccZ,GyroX,GyroY,GyroZ,ComX,ComY,ComZ;
/*MEMS传感器数据存储定义如下
0:从机ID  1:工作模式 2:动作感应标记 3-9:专用数据  10-15  陀螺仪，16-21 磁场计，22-28:加速度计，28-31气压和温度*/



long  strlenExt(const unsigned char *pucSrc)
{
	long  i = 0;
	
	while(*(pucSrc+i) != '\0')
		i++;
	
	return i;
}
void InputControl()
{

    
#if  SIM_JTAG_CHANGE==1
      if(KeyRepeatEN==1)
      {
        if(key_data%2)
          key_data++;
        delay_ms(200);
      }
      else
      {
          key_data=KEYNULL;
	 delay_ms(3);
	  LPM3;
         delay_ms(3);
      }
	
#else 
	_NOP();
#endif 
        

}

void input_command(uchar key_data_temp)
{
	key_data=key_data_temp;
	
}
uint random(uint x,uint y) 
{ 
	
	Get_DS1302(rdata);
	uint ran=0; 
	srand(rdata[0]); //随机种子 
	ran=rand()%(y-x+1)+x; 
	return ran; 
} 
void OSTaskClose()
{
	OS_index_data=myTaskPCB[OS_index_data].SubTaskList[0];
      //  myMEMSData[PRODF]=0;
        
        SendWirelessData();  //发送无线数据以改变上位机工作方式
	OS_func_state=44;
             _EINT();   
	
}

u8 SendWirelessData()
{
         myMEMSData[IDDF]=UserID;
	
       
        
        if(WirelessEN==1)
	W_PutString(myMEMSData);
        else 
        {
          Uart_PutString(myMEMSData);
        }
	return 0;
	
}

u8 GetCurrentKey(u8 *PortStatus1,u8* KeyValue,u8 ThisOrNet) //第一个参数为上次端口状态值，第二个为返回的键值
{
	u8 PortStatus2,ReturnValue=0;
	u8 KeyFlag;
	_DINT();
	delay_ms(15);
        PortStatus2=P2IN; 
        if(0X2B==PortStatus2&0x3F)  //特殊按键
        {
          *KeyValue=KEYSPECIAL;
          ReturnValue=2;
          return ReturnValue;
        }
	for (u8 i=0;i<6;i++)
	{   KeyFlag=1<<i;
		if ((*PortStatus1&KeyFlag)>(PortStatus2&KeyFlag))  // 按下
		{
			*KeyValue=2*i+1;
                        if(ThisOrNet)
                        {
                        myMEMSData[KEYDF]=*KeyValue;
			SendWirelessData();
                        }
			ReturnValue=1;
		} 
		else if((*PortStatus1&KeyFlag)<(PortStatus2&KeyFlag))  //弹起
		{
		                *KeyValue=2*i+2;
                                if(ThisOrNet)
                                {
                                 myMEMSData[KEYDF]=*KeyValue;
			 	SendWirelessData(); 
                                }
				ReturnValue=1;
		}
		
	}
 
        *PortStatus1=PortStatus2;
         myMEMSData[KEYDF]=0;
     
	
return ReturnValue;
}
//秒，分，时，日，月，星期，年

unsigned char wdata[7]={0x30,0x05,0x17,0x08,0x02,0x02,0x11};
unsigned char rdata[7]={0x30,0x22,0x23,0x26,0x09,0x07,0x10};
const u8 FullKeyBoardData[44]=
{
	'1','2','3','4','5','6','7','8','9','0','!',
		'q','w','e','r','t','y','u','i','o','p','?',
		'a','s','d','f','g','h','j','k','l',':','!',
		'z','x','c','v','b','n','m','.','l',' ',' '
};
const u8 NumKeyBoardData[12]=
{
	'7','8','9',
		'4','5','6',
		'1','2','3',
		' ','0',' '
		
};
void FloatToChar(float OriData,u8* Result)
{
      OriData*=1000;   //统一乘以10K,以减小精度误差
	*Result=(u8)(OriData/256);
	*(Result+1)=(u8)(OriData-*Result*256);
}
void OSLightControl(u8 Mode)
{
  //0：变暗，1 变亮  2，取反
  switch(Mode)
  {
  case 0:
    P4OUT&=~BIT7;
    break;
  case 1:
    P4OUT|=BIT7;
    break;
  case 2:
     P4OUT^=BIT7;
    break;
  }
}

u8 DecToHexFunc(u16 Dec)
{
  return (Dec/10)*16+Dec%10;
}

u8 KeyPressDownConfirm(u8 Time)
{
  while( (!GetCurrentKey(&InputPortState,&key_data,0))&&Time>0)
  {
    delay_ms(50);
    Time--;
  }
  if(Time==0)
    return 1;
  else 
  {
    return 0;
  }
}
  
u8 OSFuncKeyInputProcess()
{
        GyroMenuEN=0;
         KeyRepeatEN=0;
       
	if(key_data==KEYENTER_DOWN)
        {
          if(KeyPressDownConfirm(5))
		GyroMenuEN=1;
           else 
           {
              key_data=KEYENTER_UP;
              
           }
        }
        else
            GyroMenuEN=0;
        if(key_data==KEYUP_DOWN||key_data==KEYDOWN_DOWN||key_data==KEYLEFT_DOWN||key_data==KEYRIGHT_DOWN)
        {
           u8 KeyTemp=key_data;
          if(KeyPressDownConfirm(10))
		KeyRepeatEN=1;
           else 
           {
              key_data=KeyTemp+1;
           }
        }
        else
            KeyRepeatEN=0;
        
	
        return 1;
}   

u8   NetProEnterConfirm()
{
      if(!MessageGui("LCD即将休眠","是否继续？",1))
    { OSTaskClose();
		return 0;
    }
    else
    {
        BackLightTo(0);
	delay_ms(1000);
	LCDSetSleep();
        OS_func_state=1;
        return 1;
    }

}
u8   NetProCloseConfirm(u8 CurrentKey)
{
      if(CurrentKey==KEYSPECIAL)
                {
                 
                       _EINT();
                             OSLightControl(0);
                       if(MessageGui("将退出程序","是否跳出？",1))
                       {
                       OSTaskClose();
                       return 1;  //确认退出
                         }
                       else
                       {
                         BackLightTo(0);
	              delay_ms(1000);
	                  LCDSetSleep();
                          return 0;  // 不退出
                         
                       }
               
                }
      return 0;
      
}