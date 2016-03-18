
void WirelessInit();

__interrupt void Port_1(void);


void W_PutString(u8 channelID) ;


void WriteTxBuffPtr(u8 channelID,u8* data)   ;
void WriteTxBuff(u8 channelID)  ;
void W_PutStringPtr() ;

void RxWayConfig(u8 channelID);
void SetStandbyMode();
void SetRFChannel(u8 channelID,u8 ID);  //id  0-7

void ProcessReceivedData();