
#include    "USER_PROGRAM.H" 


u16 keyCounter = 0;		//����ɨ�����

void KeyInit(void)
{

}



u16 readKey(void)
{
	u16 key = 0X0000;



	if(K4_PRESS)
	{
		key |= KEY_K4;
	}

	if(K3_PRESS)
	{
		key |= KEY_K3;
	}

	if(K2_PRESS)
	{
		key |= KEY_K2;
	}

	if(K1_PRESS)
	{
		key |= KEY_K1;
	}

	if(K0_PRESS)
	{
		key |= KEY_K0;
	}
	
	
	

	return key;
}


/************************************************************
@
************************************************************/
u16 KeyDetect(void)
{
  u16 key;
  
  key = readKey();

  if(key == 0X0000) key = NO_KEY;
    
  return key;
}

/*----------------------------------------------------------------------------*/
/**@brief ������⣬ÿ10ms����һ��
@return ��
*/
/*----------------------------------------------------------------------------*/
void KeyScan(void)
{
	static u16 keyValue = 0;

  u16 keyTmp = NO_KEY;
  u16 key_return = NO_KEY;
  keyTmp = KeyDetect();
  if(keyTmp == NO_KEY )
  {
    if (keyCounter >= KEY_LONG_TIMES)  //����̧��
    {
      key_return = keyValue | KEY_LONG_UP;
    }
    else if (keyCounter >= KEY_SCAN_TIMES)   //�̰�̧��
    {
      key_return = keyValue | KEY_SHORT_UP;
    }

    keyValue = keyTmp;
    keyCounter = 0;  
  }
  else if(keyTmp != keyValue)
  {
    keyValue = keyTmp;
    keyCounter = 0;
  }	
  else
  {
    keyCounter++;
    if (keyCounter == KEY_SCAN_TIMES)			//ȥ��
    {
      key_return = keyValue;
    }
    else if (keyCounter == KEY_LONG_TIMES)				//����
    {
      key_return = keyValue | KEY_LONG;
    }
    else if (keyCounter == (KEY_LONG_TIMES + KEY_HOLD_TIMES) )			//����
    {
      key_return = keyValue | KEY_HOLD;
      keyCounter = KEY_LONG_TIMES;
    }
  }
  if (key_return != NO_KEY)
  {
		//key is here
		AppData.keyMsg = key_return;
		//UART_SendByte(key_return);
  }

}


u16 GetKeyMsg(void)
{
	u16 key;
	
	key = AppData.keyMsg;
	
	if(AppData.keyMsg != NO_KEY)
	{
		AppData.keyMsg = NO_KEY;
	}
	
	return key;	
}

