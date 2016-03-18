
void delay_us(unsigned int n);
 
void delay_ms(unsigned int n);
void SetCPUSpeed(u8 value);
void TimerInit();
extern u16 TimerCounter;
__interrupt void Timer_A0 (void);

#define OneSec 500


#define MAXCounter 4*OneSec

