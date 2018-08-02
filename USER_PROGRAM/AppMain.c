
#include    "USER_PROGRAM.H" 


APPDATA AppData;


void AppMainInit(void)
{
	AppData.state = APP_STATE_INIT;
	AppData.sysTick = 0;
	AppData.isTest = 0;
	AppData.func = 0X00;
	AppData.funcLightHeating = 0X00;
	AppData.sysRTC = 0;
	
	AppData.AirBlowWorkTime = 0;
	AppData.AirChangeWorkTime = 0;	
	AppData.AirHeatingWorkTime = 0;
	AppData.LightHeatingWorkTime = 0;


	AppData.AirBlowWorkDelay = 0;
	AppData.AirChangeWorkDelay = 0;
	AppData.AirHeatingBlowDelay = 0;
	AppData.AirHeatingUnBlowDelay = 0;
	
	
	AppData.ptc_on = 0;
	AppData.ptc_on_t = 1;
	AppData.aChg_on = 0;
	AppData.aChg_on_t = 1;
	AppData.aBlw_on = 0;
	AppData.aBlw_on_t = 1;
	AppData.lHt_on = 0;
	AppData.lHt_on_t = 1;

	LedInit();
	KeyInit();
	TimerInit();
	PTM0AInit();
	
	UartInitial();
	
#if SELF_TEST_EN
	selftest_int();
#endif
	
//#define QDP9016A 	0X00
//#define QDP9016B 	0X01
//#define TKG_18A 	0X02
//#define TKG_18B 	0X03
//#define TKG_18C 	0X04
//#define TKG_18D 	0X05
#if UART_ENABLE			
	DebugString("����: ");
	if(MODLE_TYPE == QDP9016A)
	{
		DebugString("QDP9016A ");
	}
	else if(MODLE_TYPE == QDP9016B)
	{
		DebugString("QDP9016B ");
	}
	else if(MODLE_TYPE == TKG_18A)
	{
		DebugString("TKG_18A ");
	}
	else if(MODLE_TYPE == TKG_18B)
	{
		DebugString("TKG_18B ");
	}
	else if(MODLE_TYPE == TKG_18C)
	{
		DebugString("TKG_18C ");
	}
	else if(MODLE_TYPE == TKG_18D)
	{
		DebugString("TKG_18D ");
	}
	DebugString("\r\n");
	
	DebugString(__DATE__);
	DebugString("    ");
	DebugString(__TIME__);
	DebugString("\r\n");
#endif
}

void PeripheralSetAirBlow(void)
{
	LED_AIR_BLOW_ON();	
	if(AppData.AirBlowWorkDelay == 0)
	{
		JK_AIR_BLOW_ON();
	}
//	LED_AIR_CHANGE_OFF();
//	JK_AIR_CHANGE_OFF();
	
//	LED_AIR_HEATING_OFF();
//	JK_AIR_HEATING_OFF();
	
	LED_STANDBY_OFF();
}

void PeripheralUnsetAirBlow(void)
{
	LED_AIR_BLOW_OFF();
	if(AppData.AirHeatingWorkTime == 0)
	{
		JK_AIR_BLOW_OFF();
	}
}

void PeripheralSetAirHeating(void)
{
	LED_AIR_HEATING_ON();
	JK_AIR_BLOW_ON();
	if(AppData.AirHeatingBlowDelay == 0)
	{
		JK_AIR_HEATING_ON();
	}
//	LED_AIR_BLOW_OFF();
//	JK_AIR_BLOW_OFF();
		
//	LED_AIR_CHANGE_OFF();	
//	JK_AIR_CHANGE_OFF();
	
	LED_STANDBY_OFF();		
}

void PeripheralUnsetAirHeating(void)
{
	LED_AIR_HEATING_OFF();
	JK_AIR_HEATING_OFF();
}


void PeripheralSetAirChange(void)
{
//	LED_AIR_HEATING_OFF();
//	JK_AIR_HEATING_OFF();
	
//	LED_AIR_BLOW_OFF();
//	JK_AIR_BLOW_OFF();
		
	LED_AIR_CHANGE_ON();	
	if(AppData.AirChangeWorkDelay == 0)
	{
		JK_AIR_CHANGE_ON();
	}
	LED_STANDBY_OFF();		
}

void PeripheralUnsetAirChange(void)
{
	LED_AIR_CHANGE_OFF();	
	JK_AIR_CHANGE_OFF();
}

void PeripheralSetLightHeating(void)
{
	LED_LIGHT_HEATING_ON();
	JK_LIGHT_HEATING_ON();
	
	LED_STANDBY_OFF();		
}

void PeripheralUnsetLightHeating(void)
{
	LED_LIGHT_HEATING_OFF();
	JK_LIGHT_HEATING_OFF();
}

void PeripheralSet(void)
{
	if(AppData.isTest) return;
	if(AppData.state != APP_STATE_LOOP) return;

	if(AppData.AirBlowWorkTime)
	{
		AppData.aBlw_on = 1;
	}
	else
	{
		AppData.aBlw_on = 0;
#if SELF_TEST_EN
		selftest_checkAirBlowoff();
#endif
	}
	
	if(AppData.AirChangeWorkTime)
	{
		AppData.aChg_on = 1;
	}
	else
	{
		AppData.aChg_on = 0;
#if SELF_TEST_EN
		selftest_checkAirChangeoff();
#endif
	}
#if 1
	if(AppData.AirHeatingWorkTime)
	{
		AppData.ptc_on = 1; 
	}
	else
	{
		AppData.ptc_on = 0; 
	}
#else
	if(AppData.AirHeatingWorkTime)
	{	
		//AppData.ptc_on = 1; 
		//AppData.aBlw_on = 0;																								//��ů����򿪴���
		if(AppData.AirHeatingWorkTime <= (AIR_HEATING_TIME-AIR_HEATING_BLOW_DELAY)) //1s��ſ�����ů
		{
			AppData.ptc_on = 1; 
		}
		if(AppData.AirHeatingWorkTime <= AIR_HEATING_UNBLOW_DELAY)									//ʣ��30s��������
		{
			AppData.ptc_on = 0; 	
		}
		if(AppData.AirHeatingWorkTime == 1)
		{
			if(AppData.AirBlowWorkTime == 0)
			{
				AppData.aBlw_on = 0;	
#if UART_ENABLE			
				printf_rtc_time(AppData.sysRTC);	
				DebugString("[���� �ر�] \r\n");
#endif
			}
		}
	}
	else
	{
		AppData.ptc_on = 0;	
#if SELF_TEST_EN
		selftest_checkPTCoff();
#endif
	}
#endif

	if(AppData.LightHeatingWorkTime)
	{
		AppData.lHt_on = 1;	
	}
	else
	{
		AppData.lHt_on = 0;	
#if SELF_TEST_EN
		selftest_checkLightHeatingoff();
#endif
	}

	
	if((AppData.AirBlowWorkTime == 0)&&
			(AppData.AirChangeWorkTime == 0)&&
			(AppData.AirHeatingWorkTime == 0)&&
			(AppData.LightHeatingWorkTime == 0))
	{
		LED_STANDBY_ON();
	}
	else
	{
		if(AppData.standbyPressCnt)
		{
			LED_STANDBY_ON();
		}
		else
		{
			LED_STANDBY_OFF();
		}
	}
	
	if(AppData.ptc_on_t != AppData.ptc_on)
	{
		AppData.ptc_on_t = AppData.ptc_on;
		if(AppData.ptc_on)
		{
			PeripheralSetAirHeating();	
		}
		else
		{
			PeripheralUnsetAirHeating();
		}
	}
	
	if(AppData.aChg_on_t != AppData.aChg_on)
	{
		AppData.aChg_on_t = AppData.aChg_on;
		if(AppData.aChg_on)
		{
			PeripheralSetAirChange();	
		}
		else
		{
			PeripheralUnsetAirChange();
		}
	}
	
	
	if(AppData.aBlw_on_t != AppData.aBlw_on)
	{
		AppData.aBlw_on_t = AppData.aBlw_on;
		if(AppData.aBlw_on)
		{
			PeripheralSetAirBlow();	
		}
		else
		{
			PeripheralUnsetAirBlow();
		}
	}
	
	if(AppData.lHt_on_t != AppData.lHt_on)
	{
		AppData.lHt_on_t = AppData.lHt_on;
		if(AppData.lHt_on)
		{
			PeripheralSetLightHeating();	
		}
		else
		{
			PeripheralUnsetLightHeating();
		}
	}
}

//#define FUNC_AIR_BLOW					BIT(0)
//#define FUNC_AIR_CHANGE				BIT(1)
//#define FUNC_AIR_HEATING			BIT(2)
//#define FUNC_LIGHT_HEATING		BIT(3)
//#define FUNC_LIGHT_UP					BIT(4)
//#define FUNC_DRY							BIT(5)
//#define FUNC_NET_JOIN					BIT(6)
void AppTimerRun(void)
{
#if 0
	static u8 s_led = 0;
	if(s_led)
	{
		LED_AIR_BLOW_ON();
		s_led = 0;
	}
	else
	{
		LED_AIR_BLOW_OFF();
		s_led = 1;
	}
	return ;
#endif
	if(AppData.AirBlowWorkTime)
	{
		AppData.AirBlowWorkTime--;	
	}
	if(AppData.AirChangeWorkTime)
	{
		AppData.AirChangeWorkTime--;	
	}
	if(AppData.AirHeatingWorkTime)
	{
		if(--AppData.AirHeatingWorkTime == 0)
		{
			AppData.AirHeatingUnBlowDelay = AIR_HEATING_UNBLOW_DELAY;
		}
	}
	
	if(AppData.LightHeatingWorkTime)
	{
		AppData.LightHeatingWorkTime--;
	}
	
	if(AppData.standbyPressCnt)
	{
		AppData.standbyPressCnt--;	
	}

	if(AppData.AirBlowWorkDelay)
	{
		if(--AppData.AirBlowWorkDelay == 0)
		{
			JK_AIR_BLOW_ON();
		}
	}
	if(AppData.AirChangeWorkDelay)
	{
		if(--AppData.AirChangeWorkDelay == 0)
		{
			JK_AIR_CHANGE_ON();
		}
	}

	if(AppData.AirHeatingBlowDelay)
	{
		if(--AppData.AirHeatingBlowDelay == 0)
		{
			JK_AIR_HEATING_ON();
		}
	}

	if(AppData.AirHeatingUnBlowDelay)
	{
		if(--AppData.AirHeatingUnBlowDelay == 0)
		{
			JK_AIR_BLOW_OFF();
		}
	}
}


void BuzzDeal(u16 key)
{
	switch(key)
	{
		case PR_K0:
		case PR_K1:
		case PR_K2:
		case PR_K3:
		case PR_K4:
			BuzzMs(15);
			break;
			
		default:
			break;		
	}
	
}

void AppTask(void)
{
	u16 key;
	
	switch(AppData.state)
	{
		case 	APP_STATE_INIT:
#if UART_ENABLE			
			DebugString("APP_STATE_INIT \r\n");
#endif
			AppData.state = APP_STATE_START;
			LedAllOn();
			APP_TIMER_Set(&AppData.gTimer);
			BuzzMs(50);
			break;
			
		case 	APP_STATE_START:
			//DebugString("APP_STATE_START \r\n");
#if UART_ENABLE			
			if(K0_PRESS)
			{
				DebugString("0 ");
			}
			if(K1_PRESS)
			{
				DebugString("1 ");
			}
			if(K2_PRESS)
			{
				DebugString("2 ");
			}
			if(K3_PRESS)
			{
				DebugString("3 ");
			}
			if(K4_PRESS)
			{
				DebugString("4 ");
			}
#endif
			if(APP_TIMER_Expired(AppData.gTimer,20))	//�ϵ���2s��ر�
			{
				AppData.state = APP_STATE_CHECK_KEY;	
				LedAllOff();
				APP_TIMER_Set(&AppData.gTimer);
			}
			break;
			
		case 	APP_STATE_CHECK_KEY:
			if(K4_PRESS && K3_PRESS)
			{
				if(APP_TIMER_Expired(AppData.gTimer,20))	//�ϵ���2s��ر�
				{
					AppData.state = APP_STATE_SELF_TEST_START;
					AppData.isTest = 1;
					BuzzMs(50);
#if UART_ENABLE			
					DebugString("APP_STATE_SELF_TEST_START \r\n");
#endif
				}
			}
			else
			{
				AppData.state = APP_STATE_LOOP;
#if UART_ENABLE			
				DebugString("APP_STATE_LOOP \r\n");
#endif
			}
			break;	
			
		case 	APP_STATE_LOOP:
			//if(AppData.sysRTCTemp != AppData.sysRTC)
			{
			//		AppData.sysRTCTemp = AppData.sysRTC;
					//printf_dec_u16(AppData.sysRTC);
					//DebugString("\n");
			}
			if(APP_TIMER_Expired(AppData.gTimer,30))
			{
				APP_TIMER_Set(&AppData.gTimer);
//				UART_SendByte(AppData.func);
//				DebugString("PORT:");
//				printf_u8(AppData.func);
//				DebugString("\n");
			}
			key = GetKeyMsg();
			if(key != NO_KEY)
			{
				//UART_SendByte(key>>8&0X00FF);
				//UART_SendByte(key);
				BuzzDeal(key);
				switch(key)
				{
					case PR_K3:	//吹风
						if(AppData.AirBlowWorkTime)
						{
							AppData.AirBlowWorkTime = 0;
							AppData.AirBlowWorkDelay = 0;
						}
						else
						{
							AppData.standbyPressCnt = 0;
							AppData.AirBlowWorkTime = AIR_BLOW_TIME;

							AppData.AirHeatingBlowDelay = 0;
							AppData.AirHeatingUnBlowDelay = 0;
							AppData.AirHeatingWorkTime = 0;
							if(AppData.AirChangeWorkTime)	//如果换气开着，关闭换气，吹风延时2s
							{
								AppData.AirChangeWorkTime = 0;
								AppData.AirChangeWorkDelay = 0;
								AppData.AirBlowWorkDelay = AIR_BLOW_DELAY;
							}
#if SELF_TEST_EN
							SelfTestAirBlowOn();
#endif	
						}
						break;
						
					case PR_K4:	//换气
						if(AppData.AirChangeWorkTime)
						{
							AppData.AirChangeWorkTime = 0;
							AppData.AirChangeWorkDelay = 0;
						}
						else
						{
							AppData.standbyPressCnt = 0;
							AppData.AirChangeWorkTime = AIR_CHANGE_TIME;
							if(AppData.AirBlowWorkTime)	//如果吹风开着，关闭吹风，换气延时2s
							{
								AppData.AirBlowWorkTime = 0;
								AppData.AirBlowWorkDelay = 0;
								AppData.AirChangeWorkDelay = AIR_CHANGE_DELAY;
							}
							if(AppData.AirHeatingWorkTime)
							{
								if(AppData.AirHeatingBlowDelay)	//如果PTC还没工作
								{
									AppData.AirHeatingBlowDelay = 0;
								}
								AppData.AirHeatingUnBlowDelay = 1;	//关闭吹风
								AppData.AirHeatingWorkTime = 0;//关闭PTC
								AppData.AirChangeWorkDelay = AIR_CHANGE_DELAY;
							}
#if SELF_TEST_EN
							SelfTestAirChangeOn();
#endif	
						}
						break;
					
					case PR_K2: //风暖
						if(AppData.AirHeatingWorkTime)		//如果风暖开着
						{
							if(AppData.AirHeatingBlowDelay)	//如果PTC还没工作
							{
								AppData.AirHeatingBlowDelay = 0;
								
								AppData.AirHeatingUnBlowDelay = 1;	//关闭吹风
							}
							else	//PTC已经工作，则需要开吹风
							{
								AppData.AirHeatingUnBlowDelay = AIR_HEATING_UNBLOW_DELAY;  //延时关闭吹风
							}
							AppData.AirHeatingWorkTime = 0;//关闭风暖
						}
						else
						{
							AppData.standbyPressCnt = 0;
							AppData.AirHeatingWorkTime = AIR_HEATING_TIME;
							if(AppData.AirBlowWorkTime == 0)
							{
								AppData.AirHeatingBlowDelay = AIR_HEATING_BLOW_DELAY; //PTC延时1s启动
							}
							
							AppData.AirBlowWorkTime = 0;
							AppData.AirBlowWorkDelay = 0;
						
							AppData.AirChangeWorkTime = 0;
							AppData.AirChangeWorkDelay = 0;
						}
#if 0
						if(AppData.AirHeatingWorkTime > AIR_HEATING_UNBLOW_DELAY)	//处于打开状态	则关闭
						{
							AppData.AirHeatingWorkTime = AIR_HEATING_UNBLOW_DELAY;
							AppData.AirHeatingWorkDelay = 0;
						}
						else if(AppData.AirHeatingWorkTime > 2)										//处于关闭并且风还吹着状态，则打开
						{
							AppData.AirHeatingWorkTime = AIR_HEATING_TIME-AIR_HEATING_BLOW_DELAY;
						}
						else							//处于关闭并且风已经不吹了，则打开
						{
							AppData.AirHeatingWorkTime = AIR_HEATING_TIME;
							AppData.AirHeatingWorkDelay = AIR_HEATING_BLOW_DELAY;
#if SELF_TEST_EN
							printf_dec_u16(AppData.AirHeatingWorkTime);
							DebugString("\r\n");
							SelfTestPTCOn();
#endif
						}
#endif
						break;
					
					case PR_K1://灯暖
						if(AppData.LightHeatingWorkTime)
						{
							AppData.LightHeatingWorkTime = 0;
						}
						else
						{
							AppData.standbyPressCnt = 0;
							AppData.LightHeatingWorkTime = LIGHT_HEATING_TIME;
#if SELF_TEST_EN
							SelfTestLightHeatingOn();
#endif
						}
						break;
						
						
					case PR_K0://待机
						AppData.AirBlowWorkTime = 0;
						AppData.AirBlowWorkDelay = 0;
						AppData.AirChangeWorkTime = 0;
						AppData.AirChangeWorkDelay = 0;
						if(AppData.AirHeatingWorkTime)
						{
							if(AppData.AirHeatingBlowDelay)//如果PTC还没工作
							{
								AppData.AirHeatingBlowDelay = 0;
								AppData.AirHeatingUnBlowDelay = 1;	//关闭吹风
							}
							else//PTC已经工作，则需要开吹风
							{
								AppData.AirHeatingUnBlowDelay = AIR_HEATING_UNBLOW_DELAY;//延时关闭吹风
							}
						}
						AppData.AirHeatingWorkTime = 0;
						AppData.LightHeatingWorkTime = 0;
						AppData.standbyPressCnt = 2;
						break;
					default:
						break;
				}//////	
			}
			//DebugString("+");
			//UART_SendByte(_ctm0dl);
			break;		//APP_STATE_LOOPbreak
			
			
		case APP_STATE_SELF_TEST_START:
			AppData.state = APP_STATE_SELF_TEST_SHOW_MODLE;
			APP_TIMER_Set(&AppData.gTimer);
#if UART_ENABLE			
			DebugString("APP_STATE_SELF_TEST_SHOW_MODLE \r\n");
#endif		
			break;
			
		case APP_STATE_SELF_TEST_SHOW_MODLE:
			LedShowModle();
			if(APP_TIMER_Expired(AppData.gTimer,20))
			{
				AppData.state = APP_STATE_SELF_TEST_LED_CYCLE;
				APP_TIMER_Set(&AppData.gTimer);
				LedAllOff();
#if UART_ENABLE			
				DebugString("APP_STATE_SELF_TEST_LED_CYCLE \r\n");
#endif
			}
			break;
			
		case APP_STATE_SELF_TEST_LED_CYCLE:
			if(LedShowCycle())
			{
				AppData.state = APP_STATE_SELF_TEST_JK_CYCLE;
				APP_TIMER_Set(&AppData.gTimer);
				LedAllOff();
#if UART_ENABLE			
				DebugString("APP_STATE_SELF_TEST_JK_CYCLE \r\n");
#endif
			}
			break;
			
		case APP_STATE_SELF_TEST_JK_CYCLE:
			if(JKShowCycle())
			{
				AppData.state = APP_STATE_SELF_TEST_KEY_CYCLE;
				APP_TIMER_Set(&AppData.gTimer);
				LedAllOff();
				AppData.func = 0X00;
#if UART_ENABLE			
				DebugString("APP_STATE_SELF_TEST_KEY_CYCLE \r\n");
#endif
			}
			break;
			
		case APP_STATE_SELF_TEST_KEY_CYCLE:
			if(KeyShowCycle())
			{
					AppData.state = APP_STATE_LOOP;
					AppData.func = 0X00;
					AppData.isTest = 0;
#if UART_ENABLE			
					DebugString("APP_STATE_LOOP \r\n");
#endif
			}
			//No manual within 10s then go to APP_STATE_LOOP
			break;
			
		default:
			break;
	}
}

