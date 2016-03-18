void InitAllSensor();
void StartAllSensor();
void CloseAllSensor();
void GetAllSensorData();

u8 L3G4200DReadData();

u8 L3G4200DShowData();
void CalAllSensorData();
void I2C_Init(void);
u8 ADXL345Init(u8 Mode);
u8 ADXL345ReadData();
u8 ADXL345ShowData(u8 Config );
u8 ITG3200ReadData();
u8 BMP085ReadData(u8 oss,long* p,long* T);//温度、压力采样;

u8 HMC5883LInit() ;
void HMC5883LReadData();
u8 HMC5883LInitConfig(u8 Mode);   //1开始工作，0,为休眠