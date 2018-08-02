

#define TIMER_RELOAD	625 	//327
#define PTM0A_RELOAD	500


////////////////////////////////////////////////

void TimerInit(void);
void PTM0AInit(void);
void PTM0A_Start(void);
void PTM0A_Stop(void);


void APP_TIMER_Set(u16 *timer);
u8 APP_TIMER_Expired(u16 timer, u16 seconds);

