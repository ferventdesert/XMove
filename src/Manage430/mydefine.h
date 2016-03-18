typedef unsigned int uint;
typedef unsigned char uchar;
typedef unsigned char u8;
typedef unsigned int u16;
/****************SPI结构无线模块宏定义************/

#define clrbit(reg,bit) reg &= ~(bit) /*清寄存器的某1 比特位*/
#define bitclr(reg,bit) reg &= ~(bit) /*清寄存器的某1 比特位*/
#define setbit(reg,bit) reg |= (bit) /*设置寄存器的某1 比特位*/
#define bitset(reg,bit) reg |= (bit) /*设置寄存器的某1 比特位*/
#define cplbit(reg,bit) reg ^= (bit) /*对寄存器的某1 比特位取反*/
#define bitcpl(reg,bit) reg ^= (bit) /*对寄存器的某1 比特位取反*/




extern unsigned char myMEMSData[];
extern unsigned char myReceiveBuff[];

extern const unsigned char Rx_Address[];   //发送地址，暂时必须通过软件修改该值
extern const unsigned char Tx_Address[];   //本机地址，用于SPI无线模式
extern u8 Uart_RxFlag;
extern u8 Uart_ExMood; 
extern u8 UartReceiveFlag;


//数组存储偏移量宏定义
#define L3G4200DDF  6
#define HMC5883DF  18
#define ADXL345DF 12

#define KEYDF  4




#define IDDF  0  
#define WORKMODEDF  3
#define NODETYPEDF 1
#define NODEABILITYDF 2
#define VCCFLAG 4

