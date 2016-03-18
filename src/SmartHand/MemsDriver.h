void InitAllSensor();
void StartAllSensor();
void CloseAllSensor();
void GetAllSensorData();

void I2C_Init(void);

__interrupt void USCIAB0_ISR(void); 
