
void delay_us(unsigned int n);
 
void delay_ms(unsigned int n);
void SetCPUSpeed(u8 FreNum);
__interrupt void Timer_A1 (void);
void TimerInit();

extern u8 CPUFrequene;

extern u16 TimerCounter;
#define OneSec 500


#define MAXCounter 4*OneSec
