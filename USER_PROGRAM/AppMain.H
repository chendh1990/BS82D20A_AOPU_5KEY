

#define UART_ENABLE 	0 
#define SELF_TEST_EN 	0


//ª•≥‚
#define DisableAirBlow()				AppData.func &= ~FUNC_AIR_BLOW
#define EnableAirBlow()					AppData.func |=  FUNC_AIR_BLOW

#define DisableAirChange()			AppData.func &= ~FUNC_AIR_CHANGE
#define EnableAirChange()				AppData.func |=  FUNC_AIR_CHANGE

#define DisableAirHeating()			AppData.func &= ~FUNC_AIR_HEATING
#define EnableAirHeating()			AppData.func |=  FUNC_AIR_HEATING

//∂¿¡¢
#define DisableLightHeating()		AppData.funcLightHeating &= ~FUNC_LIGHT_HEATING
#define EnableLightHeating()		AppData.funcLightHeating  =  FUNC_LIGHT_HEATING

#define DisableLightUp()				AppData.func &= ~FUNC_LIGHT_UP
#define EnableLightUp()					AppData.func |=  FUNC_LIGHT_UP

#define DisableDry()						AppData.func &= ~FUNC_DRY
#define EnableDry()							AppData.func |=  FUNC_DRY



typedef enum
{
	APP_STATE_INIT,
	APP_STATE_START,
	APP_STATE_CHECK_KEY,
	APP_STATE_LOOP,
	APP_STATE_SELF_TEST_START,
	APP_STATE_SELF_TEST_SHOW_MODLE,
	APP_STATE_SELF_TEST_LED_CYCLE,
	APP_STATE_SELF_TEST_JK_CYCLE,
	APP_STATE_SELF_TEST_KEY_CYCLE,
}APPSTATE;

typedef struct 
{
	u8 state;
	u16 keyMsg;
	u8 keyMap[3];
	u16 sysTick;
	u16 gTimer;
	
	u16 AirBlowWorkTime;
	u8 AirBlowWorkDelay;
	
	u16 AirChangeWorkTime;
	u8 AirChangeWorkDelay;
	
	u16 AirHeatingWorkTime;
	
	u8 AirHeatingBlowDelay;
	u8 AirHeatingUnBlowDelay;
	
	u16 LightHeatingWorkTime;
	
	u8 sysRTC;
	//u16 sysRTCTemp;
	
	u8 standbyPressCnt;
	u8 func;
	u8 funcLightHeating;
	u8 isTest;
	u8 buzzMs;
	u8 ptc_on 	: 1;
	u8 ptc_on_t : 1;
	u8 aChg_on 	: 1;
	u8 aChg_on_t : 1;
	u8 aBlw_on 	: 1;
	u8 aBlw_on_t : 1;
	u8 lHt_on 	: 1;
	u8 lHt_on_t : 1;
	
}APPDATA;


extern APPDATA AppData;



//////////////////////////////////////////////////
void AppTask(void);
void AppMainInit(void);

void AppTimerRun(void);
void PeripheralSet(void);






