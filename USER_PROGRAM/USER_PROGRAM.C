
#include    "USER_PROGRAM.H"  

//==============================================
//**********************************************
//==============================================
//#pragma vector  Interrupt_Extemal        @ 0x04
//void Interrupt_Extemal()
//{
//_nop();	
//	
//}

DEFINE_ISR (Interrupt_Extemal, 0x04)
{
	GCC_NOP();	
}



/*******************************************************************
@CTM0 PÖÐ¶Ï
*******************************************************************/	
DEFINE_ISR (Interrupt_CTM0P, 0x10)
{
	GCC_NOP();	
//	DebugString("p");
}

/*******************************************************************
@CTM0 AÖÐ¶Ï
*******************************************************************/	
DEFINE_ISR (Interrupt_CTM0A, 0x14)
{//5ms
	//static u8 tickCnt = 0;
	//static u16 rtcCnt = 0;
	static volatile u8 tickCnt __attribute__((at(0x480)));
	static volatile u16 rtcCnt __attribute__((at(0x484)));
	static volatile u8 misCnt __attribute__((at(0x488)));
	
	GCC_NOP();	
	_ctma0f = 0;

	if(++rtcCnt >= 200)
	{//1s
		rtcCnt = 0;
		AppData.sysRTC++;
		AppTimerRun();
#if SELF_TEST_EN
		selftest();
		selftest_dec_counter();
#endif
	}
	
	if(++tickCnt >= 20)
	{//100ms
		tickCnt = 0;
		AppData.sysTick++;
		PeripheralSet();
	}
	
	if(++misCnt >= 2)
	{//10ms
		misCnt = 0;
		KeyScan();
		BuzzIsr();
	}
}

DEFINE_ISR (Interrupt_PTM1A, 0x18)
{
	_ptma0f = 0;
}


//==============================================
//**********************************************
//==============================================
void USER_PROGRAM_INITIAL()
{
  _papu=0xff;
  _pac=0;	
  _pa=0;	
  
  _pac4 = 1;
	
  _pcpu=0xff;
  _pcc=0;	
  _pc=0;
  
  _pbpu=0xff;
  _pbc=0;
  _pb=0;
  
  _pdpu=0xff;
  _pdc=0;
  _pd=0;
  //////////////////////
  
#if UART_ENABLE
  UartInitial();
#endif
  AppMainInit();
}

//==============================================
//**********************************************
//==============================================
void USER_PROGRAM()
{
	GET_KEY_BITMAP();
	AppData.keyMap[0] = DATA_BUF[0];
	AppData.keyMap[1] = DATA_BUF[1];
	AppData.keyMap[2] = DATA_BUF[2];
	AppTask();
}



