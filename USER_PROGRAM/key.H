




#define KEY_SCAN_TIMES		(3)  //按键防抖的扫描次数
#define KEY_SHORT_TIMES		(5)
#define KEY_LONG_TIMES		(200)	//长按键的次数
#define KEY_HOLD_TIMES      (50)    //连按的频率次数


#define NO_KEY          0xffff
							 
#define KEY_LONG				0x1000
#define KEY_HOLD				0x2000
#define KEY_SHORT_UP    0x3000
#define KEY_LONG_UP     0x4000

#define KEY_K2					0X0001

#define PR_K2		KEY_K2
#define PS_K2		(KEY_SHORT_UP|KEY_K2)
#define PL_K2		(KEY_LONG|KEY_K2)
#define PU_K2		(KEY_LONG_UP|KEY_K2)
#define PH_K2		(KEY_HOLD|KEY_K2)

#define KEY_K1			0X0002

#define PR_K1		KEY_K1
#define PS_K1		(KEY_SHORT_UP|KEY_K1)
#define PL_K1		(KEY_LONG|KEY_K1)
#define PU_K1		(KEY_LONG_UP|KEY_K1)
#define PH_K1		(KEY_HOLD|KEY_K1)

#define KEY_K0			0X0004

#define PR_K0		KEY_K0
#define PS_K0		(KEY_SHORT_UP|KEY_K0)
#define PL_K0		(KEY_LONG|KEY_K0)
#define PU_K0		(KEY_LONG_UP|KEY_K0)
#define PH_K0		(KEY_HOLD|KEY_K0)

#define KEY_K3			0X0008

#define PR_K3		KEY_K3
#define PS_K3		(KEY_SHORT_UP|KEY_K3)
#define PL_K3		(KEY_LONG|KEY_K3)
#define PU_K3		(KEY_LONG_UP|KEY_K3)
#define PH_K3		(KEY_HOLD|KEY_K3)


#define KEY_K4			0X0010

#define PR_K4		KEY_K4
#define PS_K4		(KEY_SHORT_UP|KEY_K4)
#define PL_K4		(KEY_LONG|KEY_K4)
#define PU_K4		(KEY_LONG_UP|KEY_K4)
#define PH_K4		(KEY_HOLD|KEY_K4)




void KeyInit(void);
void KeyScan(void);
u16 GetKeyMsg(void);













/////////////////////////////////////////////////////////////////
void KeyInit(void);



