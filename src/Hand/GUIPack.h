void BoxGUI(unsigned char *title);    //图形化界面窗口函数
unsigned char MessageGui(unsigned char *title,unsigned char *message,unsigned char Type);
unsigned char myListGUI(u8 x,u8 y,u8 ** list,u8 *title, u8 MaxMount,u8 LRMaxMount,u8 UDMaxMount,u8 OneLRLength,u8 OneUDLength);
unsigned char ListGUI(unsigned char** list,unsigned char *title,unsigned char mount);
unsigned char  TextGUI(unsigned char *Text,unsigned char *title,unsigned char UpLimit,unsigned char DownLimit,u8 type);
u8 DrawTitle(u16 x,u16 y,u8* mTitle,u8 Type,u8 style,u8 FreshEN);
void ShowMountGUI(u16 x,u16 y,float Mount,u8 Range,u16 Color,u8 Font);
void SystemOpenGUI();
void Clear_Screen();
void TaskBoxGUI_P(u16 x1,u16 y1,u16 x2,u16 y2,u8 *title,u8 MoveEN);
void clock_GUI(u16 x,u16 y,u16 r,u8 *rdata,u8 TotalFreshEN);
u8 CurveDraw(u16 x,u16 y,u16 Wide,u16 Long,u16 unit,u16 Color,u8 *title,float mount,u16 flag);
void TaskBoxGUI(unsigned char *title) ;   //图形化界面窗口函数;
void calendar_GUI(u16 x,u16 y,u8 *rdata,u8 TotalFreshEN);
u8  MenuGUI()  ;    //图形化界面窗口函数
u8  MainMenuListGUI(u8 LRMaxMount,u8 UDMaxMount,u8 OneLRLength,u8 OneUDLength);
u8 SliderGUI(u16 x,u16 y,u16 Length,u8* title,u16 RangeLow,u16 RangeHigh,u8 step,u16* Data);
u8 VirtualFullKeyBoardInput(u16 x,u16 y,u8* KeyX,u8* KeyY,u8 *Key);
u8 VirtualFullKeyBoard(u16 x,u16 y,u8 *Buff,u8 *BuffFlag,u8 Max);
u8 PictureShowBox(u16 x,u16 y,u8* title);
u8 CircleShowGUI(u16 x,u16 y, u8 r,LCDBYTE COLOR)  ;
u8 VirtualNumKeyBoardInput(u16 x,u16 y,u8* KeyX,u8* KeyY,u8 *Key,u8 FuncEN,u8 HardKeyTransEN) ;
u8 VirtualNumKeyBoard(u16 x,u16 y,u8 *Buff,u8 *BuffFlag,u8 Max,u8 *title);
u8 InputLongNum(u8* title,long *LData);
u8 PassWordCheck();
u8 HistogramGUI(u8** List,u16* Num,u8 num,u8* title);
u8 UpdownListInputControl(u8 *Menuflag,u8 *ThisPageflag,u8 TotolFlag,u8 ThisPageLRMax, u8 ThisPageUDMax,u8 PromptEN,u8 *FreshEN,u8* TotalFreshEN);
u8 TimeSetGUI();

u8  MenuDataRefreshGUI(u8 MenuFlag,u8 MaxMount,u8 flag,u8 LastFlag,u8 LRMaxMount,u8 UDMaxMount,u8 OneLRLength,u8 OneUDLength,u8 FreshEN,u8 TotalFreshEN);
u8 KeyBoardFuncIntroGUI(u8 HandleID,u8 *KeyUp,u8 *KeyDown,u8 *KeyLeft,u8 *KeyRight,u8 *KeyEnter,u8* KeyEsc);
u8  GyroKeyBoardInputMethod(u8 HeadDirectionDefine,u8 CancelEN,float Xthreshold,float Ythreshold);
u8 FourDirectionInputMethod(u8 key,u8 LREN,u8 UDEN,u8 LRStep,u8 UDStep,u8 LRMin,u16 LRMAX,u8 UDMin,u8 UDMax,u8 CircleEN,u8 PromtEN,u8 *KeyX,u8 *KeyY);
