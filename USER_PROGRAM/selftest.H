



typedef enum
{
	SELF_TEST_STATE_INIT,
	SELF_TEST_STATE_AIR_HEATING,
	SELF_TEST_STATE_AIR_BLOW,
	SELF_TEST_STATE_AIR_CHANGE,
	SELF_TEST_STATE_LIGHT_HEATING,
}SELFTESTSTATE;



typedef struct 
{
	u8 state;
	u16 worktime;
	u8 airHeatingOn;
	u8 airBlowOn;
	u8 airChangeOn;
	u8 lightHeatingOn;
}SELFTEST_DATA;




void selftest_int(void);


void selftest_dec_counter(void);

void selftest_debug(u16 dat);

void selftest(void);


void selftest_checkPTCoff(void);

void selftest_checkAirChangeoff(void);

void selftest_checkAirBlowoff(void);

void selftest_checkLightHeatingoff(void);

void SelfTestPTCOn(void);


void SelfTestAirBlowOn(void);


void SelfTestAirChangeOn(void);


void SelfTestLightHeatingOn(void);
