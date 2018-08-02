


#define QDP9016A 	0X00
#define QDP9016B 	0X01
#define TKG_18A 	0X02
#define TKG_18B 	0X03
#define TKG_18C 	0X04
#define TKG_18D 	0X05


#define MODLE_TYPE	TKG_18C


#define K0_PRESS	(AppData.keyMap[0]&BIT(0))		//待机
#define K1_PRESS	(AppData.keyMap[0]&BIT(1))		//灯暖
#define K2_PRESS	(AppData.keyMap[0]&BIT(2))		//风暖
#define K3_PRESS	(AppData.keyMap[0]&BIT(3))		//吹风
#define K4_PRESS	(AppData.keyMap[2]&BIT(2))		//换气

#define LED0_PORT	_pc0
#define LED1_PORT	_pc1
#define LED2_PORT	_pc2
#define LED3_PORT	_pc3
#define LED4_PORT	_pc4
#define LED5_PORT	_pc5

#define JK0_PORT	_pb6
#define JK1_PORT	_pb7
#define JK2_PORT	_pd3
#define JK3_PORT	_pd2

#define BUZZ_PORT	_pc6


//LED7
#define LED0ON() 	LED0_PORT = 1
#define LED0OFF() LED0_PORT = 0
//LED5
#define LED1ON() 	LED1_PORT = 1
#define LED1OFF() LED1_PORT = 0
//LED3
#define LED2ON() 	LED2_PORT = 1
#define LED2OFF() LED2_PORT = 0
//LED1
#define LED3ON() 	LED3_PORT = 1
#define LED3OFF() LED3_PORT = 0
//LED9
#define LED4ON() 	LED4_PORT = 1
#define LED4OFF() LED4_PORT = 0
//LED10
#define LED5ON() 	LED5_PORT = 0
#define LED5OFF() LED5_PORT = 1

#define JK0ON() 	JK0_PORT = 1
#define JK0OFF() 	JK0_PORT = 0

#define JK1ON() 	JK1_PORT = 1
#define JK1OFF() 	JK1_PORT = 0

#define JK2ON() 	JK2_PORT = 1
#define JK2OFF() 	JK2_PORT = 0

#define JK3ON() 	JK3_PORT = 1
#define JK3OFF() 	JK3_PORT = 0

#define LED_AIR_BLOW_ON()					LED3ON()
#define LED_AIR_BLOW_OFF()				LED3OFF()

#define LED_AIR_CHANGE_ON()				LED2ON()
#define LED_AIR_CHANGE_OFF()			LED2OFF()

#define LED_AIR_HEATING_ON()			LED1ON()
#define LED_AIR_HEATING_OFF()			LED1OFF()

#define LED_LIGHT_HEATING_ON()		LED0ON()
#define LED_LIGHT_HEATING_OFF()		LED0OFF()

#define LED_LIGHT_HEATING_ON()		LED0ON()
#define LED_LIGHT_HEATING_OFF()		LED0OFF()

#define JK_AIR_BLOW_ON()					JK3ON()
#define JK_AIR_BLOW_OFF()					JK3OFF()

#define JK_AIR_CHANGE_ON()				JK2ON()
#define JK_AIR_CHANGE_OFF()				JK2OFF()

#define JK_AIR_HEATING_ON()				JK1ON()
#define JK_AIR_HEATING_OFF()			JK1OFF()

#define JK_LIGHT_HEATING_ON()			JK0ON()
#define JK_LIGHT_HEATING_OFF()		JK0OFF()

//////////////   function define /////////////////
/*换气、吹风暖干燥功能互斥，按最后设定工作*/

#define FUNC_AIR_BLOW					BIT(0)
#define FUNC_AIR_CHANGE				BIT(1)
#define FUNC_AIR_HEATING			BIT(2)
#define FUNC_DRY							BIT(3)
#define FUNC_LIGHT_HEATING		BIT(4)
#define FUNC_LIGHT_UP					BIT(5)
#define FUNC_NET_JOIN					BIT(6)


#if (SELF_TEST_EN)
#define TIME_DIV	10
#else
#define TIME_DIV	1	//缩短10
#endif

#define AIR_BLOW_TIME				(1800/TIME_DIV)	//30分钟 30*60 = 1800
#define AIR_CHANGE_TIME			(1800/TIME_DIV)	//30分钟 30*60 = 1800
#define AIR_HEATING_TIME		((5400)/TIME_DIV)	//90分钟 90*60 = 5400 30秒吹风冷却
#define LIGHT_HEATING_TIME	(5400/TIME_DIV)	//90分钟 90*60 = 5400
#define LIGHT_UP_TIME				(5400/TIME_DIV)	//90分钟 90*60 = 5400
#define DRY_TIME						(7200/TIME_DIV)	//120分钟 120*60 = 7200
#define AIR_HEATING_BLOW_DELAY						2		//1s
#define AIR_HEATING_UNBLOW_DELAY					30		//30s
#define AIR_BLOW_CHANGE_DELAY						2		//2s
#define AIR_BLOW_DELAY								2		//2s
#define AIR_CHANGE_DELAY							2		//2s

