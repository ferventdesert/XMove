typedef unsigned int uint;
typedef unsigned char uchar;
typedef unsigned char u8;
typedef unsigned int u16;
typedef signed char s8;





#define clrbit(reg,bit) reg &= ~(bit) /*清寄存器的某1 比特位*/
#define bitclr(reg,bit) reg &= ~(bit) /*清寄存器的某1 比特位*/
#define setbit(reg,bit) reg |= (bit) /*设置寄存器的某1 比特位*/
#define bitset(reg,bit) reg |= (bit) /*设置寄存器的某1 比特位*/
#define cplbit(reg,bit) reg ^= (bit) /*对寄存器的某1 比特位取反*/
#define bitcpl(reg,bit) reg ^= (bit) /*对寄存器的某1 比特位取反*/





extern unsigned char    OS_index_data,key_data,OS_count,OS_func_state,WirelessProcessFlag,MenuType,
              OS_index_ago,GyroControlEN,AccControlEN,TickControlEN,WirelessEN,UserID,InputPortState,GyroMenuEN,InnerFuncState,KeyRepeatEN;
extern u16 OSBackLight,back_light,back_light_set,OSColor;

extern long mPassWord;
long  strlenExt(const unsigned char *pucSrc);
void InputControl();
uchar uart_key_transform(uchar temp);
void input_command(uchar key_data_temp);
u8 OSFuncKeyInputProcess();
u8 KeyPressDownConfirm(u8 Time);
void FloatToChar(float OriData,u8* Result);
/**************宏定义***************/






extern float AccX,AccY,AccZ,GyroX,GyroY,GyroZ,ComX,ComY,ComZ;

//数组存储偏移量宏定义
#define L3G4200DDF  6
#define HMC5883DF  18
#define ADXL345DF 12
#define BMP085DF 26
#define KEYDF  4
#define PRODF 2

#define IDDF  0  
#define WORKMODEDF  3
 
#define NODETYPEDF 1
 

#define MOVEFLAG 5
 





#define  SIZE_OF_Task 40

struct TaskPCB                     //菜单结构
{
    
	unsigned char *Name;
        u8  (* function)(); 
         unsigned char *Detail;
         u8 PicIndex;
         u8 SubTaskList[10];
      
      
};
struct HeightInfo 
{
	u16 OriginFloor;   //原始楼层数
	u16 FloorStep;     //标准楼距
	long OriginPressure,T;  //默认下的大气压数值
};
extern struct HeightInfo  myHeightInfo;


extern u8 myMEMSData[];
extern u8 myReceiveBuff[];

extern u8 myWorkMode;
extern u8 isGyroEnable;
extern u8 ChanelID; 
extern u8  myNodeFreshSpeed; 



extern u8 isGyroExisted; 
extern u8 isAccExisted; 
extern u8 isComExisted; ; 








const extern struct TaskPCB  myTaskPCB[];
const extern  u8  FullKeyBoardData[];
const extern u8 NumKeyBoardData[];
u8 SendWirelessData();
extern u8 (* OS_func)();  
uint random(uint x,uint y);
u8 GetCurrentKey(u8 *PortStatus1,u8* KeyValue,u8 ThisOrNet) ;
void OSTaskClose();
u8   NetProEnterConfirm();
u8   NetProCloseConfirm(u8 CurrentKey);
void OSLightControl(u8 Mode);
u8 DecToHexFunc(u16 Dec);
extern const unsigned char Rx_Address[];     //本机地址，用于SPI无线模式
extern const unsigned char Tx_Address[];   //发送地址，暂时必须通过软件修改该值
extern float AccX,AccY,AccZ,GyroX,GyroY,GyroZ,ComX,ComY,ComZ;
extern unsigned char uart_txbuff[];
extern unsigned char uart_rxbuff[]; 

extern unsigned char wdata[];
extern unsigned char rdata[];


extern u8 myMEMSData[];
//0:从机ID  1:工作模式 2:动作感应标记 3-9:专用数据  10-15  陀螺仪，16-21 磁场计，22-28:加速度计，28-32气压和温度*/
//

/************拼音输入法宏定义******************/
#define   T9BD        0x00	  //标点输入
#define   T9DX        0x01	  //大写英文
#define   T9XX        0x02	  //小写英文
#define   T9PY        0x03	  //T9拼音输入
#define   T9SZ        0x04	  //T9数字输入

#define   T9NULL      0x00    //查询结果为空





#define KEYUP_UP  2
#define KEYUP_DOWN 1 
#define KEYDOWN_UP  12
#define KEYDOWN_DOWN   11
#define KEYLEFT_UP    4
#define KEYLEFT_DOWN  3
#define KEYRIGHT_UP  8
#define KEYRIGHT_DOWN   7
#define KEYSPECIAL  88
#define KEYENTER_DOWN  5
#define KEYENTER_UP   6
#define KEYCANCEL_UP    10 
#define KEYCANCEL_DOWN  9
#define KEYNULL  0


#define VKNUM    13
#define VKFULL  12
