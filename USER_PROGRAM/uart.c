
#include    "USER_PROGRAM.H" 

#if (UART_ENABLE) 

void UART_SendByte(u8 byte)
{
	while(!_txif);
	_txr_rxr = byte;
}



/************************************************************
@
************************************************************/
void putchar(char c)
{
    if (c == '\n')
    {
        UART_SendByte(0x0d);
        UART_SendByte(0x0a);
    }
    else
    {
        UART_SendByte((u8)c);
    }
}

/************************************************************
@
************************************************************/
void get_hex_data(u8 dat)
{
   u8 dat0;
   if(dat<0x0a)
   {
       dat0 = dat+'0';
   }
   else
   {
       dat0 = dat+'A'-10;
   }
   putchar(dat0);
}  
/************************************************************
@
************************************************************/
void printf_u8(u8 dat)
{
    putchar(' ');
    get_hex_data(dat >> 4);
    get_hex_data(dat & 0xf);
    putchar(' ');
}


/************************************************************
@
************************************************************/
void printf_dec_u8(u8 dat)
{
	u8 bai,shi,ge;
	
	bai = dat/100 + '0';
	shi = (dat%100)/10 + '0';
	ge = dat%10 + '0';
	
	UART_SendByte(bai);
	UART_SendByte(shi);
	UART_SendByte(ge);
}

/************************************************************
@
************************************************************/
void printf_dec_u16(u16 dat)
{
#if 0
	u8 wan,qian,bai,shi,ge;
	
//	static volatile u8 wan __attribute__((at(0x488)));
//	static volatile u8 qian __attribute__((at(0x489)));
//	static volatile u8 bai __attribute__((at(0x48a)));
//	static volatile u8 shi __attribute__((at(0x48b)));
//	static volatile u8 ge __attribute__((at(0x48c)));
	
	
	wan = (dat/10000) + '0';
	qian = (dat%10000)/1000 + '0';
	bai = (dat%1000)/100 + '0';
	shi = (dat%100)/10 + '0';
	ge = dat%10 + '0';
	
	
	UART_SendByte(wan);
	UART_SendByte(qian);
	UART_SendByte(bai);
	UART_SendByte(shi);
	UART_SendByte(ge);
#endif
}


/************************************************************
@
************************************************************/
void printf_rtc_time(u16 dat)
{
#if 0
	static volatile u8 shi __attribute__((at(0x488)));
	static volatile u8 ge __attribute__((at(0x489)));
	static volatile u8 hour __attribute__((at(0x48a)));
	static volatile u8 minute __attribute__((at(0x48b)));
	static volatile u8 second __attribute__((at(0x48c)));

	//u8 shi,ge;
	//u8 hour,minute,second;
	
	hour = dat/3600;
	minute = (dat%3600)/60;
	second = dat%60;
	
	shi = (hour%100)/10 + '0';
	ge = hour%10 + '0';
	
	UART_SendByte(shi);
	UART_SendByte(ge);
	UART_SendByte(':');
	
	shi = (minute%100)/10 + '0';
	ge = minute%10 + '0';
	
	UART_SendByte(shi);
	UART_SendByte(ge);
	UART_SendByte(':');
	
	shi = (second%100)/10 + '0';
	ge = second%10 + '0';
	
	UART_SendByte(shi);
	UART_SendByte(ge);
	
	UART_SendByte(' ');
	UART_SendByte(' ');
#endif
}


void DebugString(char *buf)
{
	while(*buf != '\0')
	{
			UART_SendByte((u8)(*buf));
			buf++;
	}	
}

void UartInitial(void)
{
	_ucr2 &=~BIT(5);
	_brg = 25;	//baud 9600
	//_brg = 1;	//baud 125000
	
	
  _uarten = 1;	//UART使能
  _txen = 1;	//TX使能
  
  DebugString("\r\n\r\n\r\nHOLTEK BS82D20 Uart initial done!!!\r\n");
}

#else

void UART_SendByte(u8 byte)
{
	while(!_txif);
	_txr_rxr = byte;
}

void DebugString(char *buf)
{
	while(*buf != '\0')
	{
			UART_SendByte((u8)(*buf));
			buf++;
	}	
}

void UartInitial(void)
{
	_ucr2 &=~BIT(5);
	//_brg = 25;	//baud 9600
	_brg = 1;	//baud 125000
	
	
  _uarten = 1;	//UART使能
  _txen = 1;	//TX使能
  
  DebugString("\r\n\r\n\r\nHOLTEK BS82D20 Uart initial done!!!\r\n");
}

#endif


