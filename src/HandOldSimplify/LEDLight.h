void OSLEDControl(u8 Mode);
void OSLEDInit();
void GetVCCValue();
void ADCInit();
__interrupt void ADC10_ISR(void);
u8 GetCurrentKey(u8 *PortStatus1,u8* KeyValue)  ;
void KeyboardInit();