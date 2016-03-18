
void UartInit();
void Send1Char(unsigned char sendchar);
void PutString(unsigned char *ptr);

void PutString_C(unsigned char *ptr) ;
void  SendSensorData(unsigned char *ptr);
__interrupt void usart1_rx (void);