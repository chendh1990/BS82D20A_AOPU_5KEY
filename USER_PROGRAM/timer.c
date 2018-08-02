
#include    "USER_PROGRAM.H" 


void TimerInit(void)
{
#if 0
	/*
	fSUB 32k
	一个时钟周期0.03125ms
	TIMER_RELOAD = 320,那么一个计时周期就是10ms
	
Bit 6~4 CT0CK2~CT0CK0：选择CTM0 计数时钟位
000：fSYS/4
001：fSYS
010：fH/16
011：fH/64
100：fSUB
101：fSUB
110：CTCK0 上升沿时钟
111：CTCK0 下降沿时钟
	*/
	_tmpc = 0;
	
	_ctm0c0 = 0X40;	//0100 0000
	
	_ctm0c1 = 0XC0;	//1100 0000
	
	_ctm0al = (TIMER_RELOAD>>0)&0x00ff;
	_ctm0ah = (TIMER_RELOAD>>8)&0x00ff;

	_ct0cclr = 1;
	
	_ctma0e = 1;
	_emi = 1;
	
	_ct0dpx = 1;
	
	_ct0pau = 0;
	_ct0on = 1;
#else
	/*
	Fh 8M
	Fh/64 = 125k
	一个时钟周期0.008ms
	TIMER_RELOAD = 625,那么一个计时周期就是5ms
	
Bit 6~4 CT0CK2~CT0CK0：选择CTM0 计数时钟位
000：fSYS/4
001：fSYS
010：fH/16
011：fH/64
100：fSUB
101：fSUB
110：CTCK0 上升沿时钟
111：CTCK0 下降沿时钟
	*/
	_tmpc = 0;
	
	_ctm0c0 = 0x30;	//0100 0000
	
	_ctm0c1 = 0xc0;	//1100 0000
	
	_ctm0al = (TIMER_RELOAD>>0)&0x00ff;
	_ctm0ah = (TIMER_RELOAD>>8)&0x00ff;

	_ct0cclr = 1;
	
	_ctma0e = 1;
	_emi = 1;
	
	_ct0dpx = 1;
	
	_ct0pau = 0;
	_ct0on = 1;
#endif
}


void PTM0AInit(void)
{
	/*
	fSYS/4
	一个时钟周期0.5us
	TIMER_RELOAD = 1000,那么一个计时周期就是500us
	
Bit 6~4 CT0CK2~CT0CK0：选择CTM0 计数时钟位
000：fSYS/4
001：fSYS
010：fH/16
011：fH/64
100：fSUB
101：fSUB
110：CTCK0 上升沿时钟
111：CTCK0 下降沿时钟
	*/
	_tmpc = BIT(3);
	
	_ptm0c0 = 0X00;	//0000 0000
	
	_ptm0c1 = 0X30;	//0011 0000
	
	_ptm0al = (PTM0A_RELOAD>>0)&0x00ff;
	_ptm0ah = (PTM0A_RELOAD>>8)&0x00ff;

	_pt0cclr = 1;
	_pt0pol = 1;
//	_ptma0e = 1;

	_pt0pau = 0;
	_pt0on = 0;
}

void PTM0A_Start(void)
{
	_pt0on = 1;
}

void PTM0A_Stop(void)
{
	_pt0on = 0;
}

u8 APP_TIMER_Expired(u16 timer, u16 seconds)
{
    if((AppData.sysTick - timer) > (seconds))
    {
        return true;
    }
    else
    {
        return false;
    }
    return false;
}

void APP_TIMER_Set(u16 *timer)
{
    *timer = AppData.sysTick;
}


