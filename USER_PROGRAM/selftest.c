
#include    "USER_PROGRAM.H" 

#if (SELF_TEST_EN)
SELFTEST_DATA SelfTestData;

void selftest_int(void)
{
	SelfTestData.state = SELF_TEST_STATE_INIT;
	SelfTestData.worktime = 0;
	
	SelfTestData.airHeatingOn = 0;
	SelfTestData.airBlowOn = 0;
	SelfTestData.airChangeOn = 0;
	SelfTestData.lightHeatingOn = 0;
}


void selftest(void)
{
	switch(SelfTestData.state)
	{
		case 	SELF_TEST_STATE_INIT:
			if(AppData.state == APP_STATE_LOOP)
			{
				SelfTestData.state = SELF_TEST_STATE_AIR_HEATING;
				SelfTestData.worktime = AIR_HEATING_TIME+5;
				AppData.keyMsg = PS_K2;
			}
			break;
			
		case 	SELF_TEST_STATE_AIR_HEATING:
			if(SelfTestData.worktime == 0)
			{
				SelfTestData.state = SELF_TEST_STATE_AIR_BLOW;
				SelfTestData.worktime = AIR_BLOW_TIME+5;
				AppData.keyMsg = PS_K3;
			}
			break;
			
		case 	SELF_TEST_STATE_AIR_BLOW:
			if(SelfTestData.worktime == 0)
			{
				SelfTestData.state = SELF_TEST_STATE_AIR_CHANGE;
				SelfTestData.worktime = AIR_CHANGE_TIME+5;
				AppData.keyMsg = PS_K4;
			}
			break;	
			
		case 	SELF_TEST_STATE_AIR_CHANGE:
			if(SelfTestData.worktime == 0)
			{
				SelfTestData.state = SELF_TEST_STATE_LIGHT_HEATING;
				SelfTestData.worktime = LIGHT_HEATING_TIME+5;
				AppData.keyMsg = PS_K1;
			}
			break;	
			
			
		default:
		
			break;		
			
	}
}


void selftest_dec_counter(void)
{
	if(SelfTestData.worktime)
	{
		SelfTestData.worktime--;
	}
}


void selftest_debug(u16 dat)
{
	printf_rtc_time(dat);	
}


void selftest_checkPTCoff(void)
{
	if(SelfTestData.airHeatingOn)
	{
		SelfTestData.airHeatingOn = 0;
		printf_rtc_time(AppData.sysRTC);	
		DebugString("[风暖 关闭]\r\n");
	}	
	

}

void selftest_checkAirBlowoff(void)
{
	if(SelfTestData.airBlowOn)
	{
		SelfTestData.airBlowOn = 0;
		printf_rtc_time(AppData.sysRTC);	
		DebugString("[吹风 关闭] \r\n");
	}	
}


void selftest_checkAirChangeoff(void)
{
	
	if(SelfTestData.airChangeOn)
	{
		SelfTestData.airChangeOn = 0;
		printf_rtc_time(AppData.sysRTC);	
		DebugString("换气 关闭] \r\n");
	}	
}


void selftest_checkLightHeatingoff(void)
{

	if(SelfTestData.lightHeatingOn)
	{
		SelfTestData.lightHeatingOn = 0;
		printf_rtc_time(AppData.sysRTC);	
		DebugString("[灯暖 关闭] \r\n");
	}	
}


void SelfTestPTCOn(void)
{
	SelfTestData.airHeatingOn = 1;
	printf_rtc_time(AppData.sysRTC);
	DebugString("[风暖 开启] \r\n");
}

void SelfTestAirBlowOn(void)
{
	SelfTestData.airBlowOn = 1;
	printf_rtc_time(AppData.sysRTC);
	DebugString("[吹风 开启] \r\n");
}

void SelfTestAirChangeOn(void)
{
	SelfTestData.airChangeOn = 1;
	printf_rtc_time(AppData.sysRTC);
	DebugString("[换气 开启] \r\n");
}

void SelfTestLightHeatingOn(void)
{
	SelfTestData.lightHeatingOn = 1;
	printf_rtc_time(AppData.sysRTC);
	DebugString("[灯暖 开启] \r\n");
}

#endif