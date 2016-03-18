void MMA7455SpiWrite(unsigned char byte);
unsigned char MMA7455SpiRead(void);
void MMA7455SpiWriteReg(unsigned char SpiCommand,unsigned char Content);
void Init_MMA7455_IO(void);
u8 MMA7455SpiReadReg(unsigned char Reg);//Payload Out