
#include    "USER_PROGRAM.H"
 
//#define LED_STANDBY_ON()					LED4ON();LED5OFF()
//#define LED_STANDBY_OFF()					LED4OFF();LED5ON()

void LedInit(void)
{

}

void LED_STANDBY_ON(void)
{
	LED4OFF();
	LED5ON();
}

void LED_STANDBY_OFF(void)
{
	LED4ON();
	LED5OFF();
}

void LedAllOn(void)
{
	LED0ON();
	LED1ON();
	LED2ON();
	LED3ON();
	LED4ON();
	LED5ON();
}

void LedAllOff(void)
{
	LED0OFF();
	LED1OFF();
	LED2OFF();
	LED3OFF();
	LED4OFF();
	LED5OFF();
}

////LED7
//#define LED0ON() 	LED0_PORT = 1
//#define LED0OFF() LED0_PORT = 0
////LED5
//#define LED1ON() 	LED1_PORT = 1
//#define LED1OFF() LED1_PORT = 0
////LED3
//#define LED2ON() 	LED2_PORT = 1
//#define LED2OFF() LED2_PORT = 0
////LED1
//#define LED3ON() 	LED3_PORT = 1
//#define LED3OFF() LED3_PORT = 0
////LED9
//#define LED4ON() 	LED4_PORT = 1
//#define LED4OFF() LED4_PORT = 0
//#define QDP9016A 	0X00
//#define QDP9016B 	0X01
//#define TKG_18A 	0X02
//#define TKG_18B 	0X03
//#define TKG_18C 	0X04
//#define TKG_18D 	0X05
void LedShowModle(void)
{
	GetKeyMsg();
	
	LED5OFF();
#if (MODLE_TYPE==QDP9016A)
	LED4ON();
	LED3OFF();
	LED2OFF();
	LED1OFF();
	LED0OFF();
#endif

#if (MODLE_TYPE==QDP9016B)
	LED4ON();
	LED0ON();
	LED3OFF();
	LED2OFF();
	LED1OFF();
#endif

#if (MODLE_TYPE==TKG_18A)
	LED2ON();
	LED0ON();
	LED3OFF();
	LED4OFF();
	LED1OFF();
#endif


#if (MODLE_TYPE==TKG_18B)
	LED2ON();
	LED0ON();
	LED3ON();
	LED4OFF();
	LED1OFF();
#endif

#if (MODLE_TYPE==TKG_18C)
	LED2ON();
	LED3ON();
	LED0ON();
	LED1ON();
	LED4ON();
#endif

#if (MODLE_TYPE==TKG_18D)

#endif

}

u8 LedShowCycle(void)
{
	static u8 led_state = 0;
	
	GetKeyMsg();
	if(APP_TIMER_Expired(AppData.gTimer,5))
	{
		APP_TIMER_Set(&AppData.gTimer);
		
		if(led_state == 0)
		{
			LedAllOff();
			LED5ON();
		}
		else if(led_state == 1)
		{
			LedAllOff();
			LED4ON();
		}
		else if(led_state == 2)
		{
			LedAllOff();
		}
		else if(led_state == 3)
		{
			LedAllOff();
			LED0ON();
		}
		else if(led_state == 4)
		{
			LedAllOff();
		}
		else if(led_state == 5)
		{
			LedAllOff();
			LED1ON();
		}
		else if(led_state == 6)
		{
			LedAllOff();
		}
		else if(led_state == 7)
		{
			LedAllOff();
			LED2ON();
		}
		else if(led_state == 8)
		{
			LedAllOff();
		}
		else if(led_state == 9)
		{
			LedAllOff();
			LED3ON();
		}
		else if(led_state == 10)
		{
			LedAllOff();
		}
		else if(led_state == 11)
		{
			return 1;
		}
		led_state++;
	}	
	
	return 0;
}

u8 JKShowCycle(void)
{
	static u8 led_state = 0;
	
	GetKeyMsg();
	if(APP_TIMER_Expired(AppData.gTimer,20))
	{
		APP_TIMER_Set(&AppData.gTimer);
		
		LED_STANDBY_OFF();
		
		if(led_state == 0)
		{
			LED_LIGHT_HEATING_OFF();
			JK_LIGHT_HEATING_OFF();
			
			LED_AIR_CHANGE_OFF();
			JK_AIR_CHANGE_OFF();
			
			LED_AIR_HEATING_OFF();
			JK_AIR_HEATING_OFF();
			
			LED_AIR_BLOW_ON();
			JK_AIR_BLOW_ON();
		}
		else if(led_state == 1)
		{
			LED_LIGHT_HEATING_OFF();
			JK_LIGHT_HEATING_OFF();
			
			LED_AIR_CHANGE_OFF();
			JK_AIR_CHANGE_OFF();
			
			LED_AIR_HEATING_ON();
			JK_AIR_HEATING_ON();
			
			LED_AIR_BLOW_ON();
			JK_AIR_BLOW_ON();
		}
		else if(led_state == 2)
		{
			LED_LIGHT_HEATING_ON();
			JK_LIGHT_HEATING_ON();
			
			LED_AIR_CHANGE_OFF();
			JK_AIR_CHANGE_OFF();
			
			LED_AIR_HEATING_OFF();
			JK_AIR_HEATING_OFF();
			
			LED_AIR_BLOW_ON();
			JK_AIR_BLOW_ON();
		}
		else if(led_state == 3)
		{
			LED_LIGHT_HEATING_OFF();
			JK_LIGHT_HEATING_OFF();
			
			LED_AIR_CHANGE_OFF();
			JK_AIR_CHANGE_OFF();
			
			LED_AIR_HEATING_OFF();
			JK_AIR_HEATING_OFF();
			
			LED_AIR_BLOW_OFF();
			JK_AIR_BLOW_OFF();
		}
		else if(led_state == 4)
		{
			LED_LIGHT_HEATING_OFF();
			JK_LIGHT_HEATING_OFF();
			
			LED_AIR_CHANGE_ON();
			JK_AIR_CHANGE_ON();
			
			LED_AIR_HEATING_OFF();
			JK_AIR_HEATING_OFF();
			
			LED_AIR_BLOW_OFF();
			JK_AIR_BLOW_OFF();
		}
		else if(led_state == 5)
		{
			LED_LIGHT_HEATING_OFF();
			JK_LIGHT_HEATING_OFF();
			
			LED_AIR_CHANGE_OFF();
			JK_AIR_CHANGE_OFF();
			
			LED_AIR_HEATING_OFF();
			JK_AIR_HEATING_OFF();
			
			LED_AIR_BLOW_OFF();
			JK_AIR_BLOW_OFF();
			return 1;
		}

		led_state++;
	}	
	
	return 0;
}


u8 KeyShowCycle(void)
{
	u16 key;
	static u8  standby = 0;

	if(APP_TIMER_Expired(AppData.gTimer,100))
	{
		APP_TIMER_Set(&AppData.gTimer);
		return 1;
	}
	
	key = GetKeyMsg();
	if(key != NO_KEY)
	{
		APP_TIMER_Set(&AppData.gTimer);
		switch(key)
		{
			
			case PS_K3:
				if(!(AppData.func&FUNC_AIR_BLOW))
				{
					EnableAirBlow();
					LED_AIR_BLOW_ON();
				}
				else
				{
					DisableAirBlow();
					LED_AIR_BLOW_OFF();
				}
				break;
				
			case PS_K4:
				if(!(AppData.func&FUNC_AIR_CHANGE))
				{
					EnableAirChange();
					LED_AIR_CHANGE_ON();
				}
				else
				{
					DisableAirChange();
					LED_AIR_CHANGE_OFF();
				}
				break;
			
			case PS_K2:
				if(!(AppData.func&FUNC_AIR_HEATING))
				{
					EnableAirHeating();
					LED_AIR_HEATING_ON();
				}
				else
				{
					DisableAirHeating();
					LED_AIR_HEATING_OFF();
				}
				break;
			
			case PS_K1:
				if(AppData.funcLightHeating != FUNC_LIGHT_HEATING)
				{
					EnableLightHeating();
					LED_LIGHT_HEATING_ON();
				}
				else
				{
					DisableLightHeating();
					LED_LIGHT_HEATING_OFF();
				}
				break;
				
				
			case PS_K0:	
				if(standby)
				{
					standby = 0;
					LED_STANDBY_OFF();
				}
				else
				{
					standby = 1;
					LED_STANDBY_ON();
				}
				break;			
				
			
			default:
				break;
		}//////end key handle

			
	}
	return 0;
}

void BuzzMs(u8 ms)
{
	AppData.buzzMs = ms;
	PTM0A_Start();
}


void BuzzIsr(void)
{
	if(AppData.buzzMs)
	{
		AppData.buzzMs--;	
		if(AppData.buzzMs == 1)
		{
			PTM0A_Stop();
		}
	}	
}



