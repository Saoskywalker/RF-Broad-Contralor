/**********************************************************************
Name: Internal Lipolysis Instrument mini(display contral)
Version: v5.0 Released(changed from 脂立瘦立式 v4.1)
Editor: Aysi
Function: 3 channel strength RF + air heat
History:2019.4.30:changed, 3 language, 8 inch display
**********************************************************************/

//#define DEBUG
#include "stm32f10x.h"
#include "led.h"
#include "delay.h"
#include "sys.h"
#include "timer.h"
#include "AppLib.h"

void screenCheck(void);

int main()
{
	u16 i = 0;

	LED_Init();
	NVIC_Configuration(); //nvic set 2:2
	delay_init();
	uart_init(9600);			 //Main Board
	uart2_init(115200);			 //DW Display
	TIM4_PWM_Init(7200, 0);		 //10Khz.
	TIM_SetCompare3(TIM4, 3000); //4.6v
	screenCheck();
	dwPlayVol(0xFF);
	TIM3_Int_Init(999, 70); //1ms
	Adc_Init();

	delay_ms(1000);
	delay_ms(1000);
	delay_ms(250);
	INLINE_MUSIC_START();
	nextPage = FUNCTION_SELECT;
	dwSetColor(DW_COL_RED, DW_COL_WHITE);
	// INLINE_MUSIC_CANNEL();

	STMFLASH_Read(FLASH_SAVE_ADDR, &i, 1); //read language config ago
	if (i==123)
		dwSetLanguage(LANGUAGE_ENGLISH);
	else if(i==150)
		dwSetLanguage(LANGUAGE_KOREAN);
	else 
		dwSetLanguage(LANGUAGE_CHINESE);

	//#ifndef DEBUG
	//	IWDG_Init(4,625);    //psc 64,reload 625,voertime 1s	
	//#endif
	while (1)
	{
		//#ifndef DEBUG
		//		IWDG_ReloadCounter();//feed wdt
		//#endif
		//		printf("kkk");
		//		USART_SendData(USART2, 0XCC);
		//		USART_SendData(USART2, 0XCC);
		//	 GPIO_SetBits(GPIOA,GPIO_Pin_4);
		//		delay_ms(500);
		//		PAout(4) = ~PAout(4);
		//		delay_ms(500);
		switch (nextPage)
		{
		case FUNCTION_RESTART:
		{
			PageRestartAnimation();
			break;
		}
		case FUNCTION_LANGUAGE:
		{
			PageLanguage();
			break;
		}
		case FUNCTION_EXPLAIN:
		{
			PageExplain();
			break;
		}
		case FUNCTION_FACE:
		{
			PageFaceRF();
			break;
		}
		case FUNCTION_BODY:
		{
			PageBodyRF();
			break;
		}
		case FUNCTION_O2:
		{
			PageO2();
			break;
		}
		case FUNCTION_COOL:
		{
			PageCool();
			break;
		}
		case FUNCTION_SELECT:
		{
			PageMenu();
			break;
		}
		case FUNCTION_EYE:
		{
			PageEyeRF();
			break;
		}
		default:
		{
			break;
		}
		}
	}
}

void screenCheck(void)
{
	u8 i;
	//Check communicate with DW Display, continue 2s
	for (i = 0; i < 10; i++)
	{
		dwSendByte(0xAA);
		dwSendByte(0x00);  // 发送握手指令
		dwSendOver();
		delay_ms(5);
		if (dwQueryCmd() == 0x74)
		{ // 握手成功
			i = 0xFF;
			break;
		}
		delay_ms(200);
	}
	if (i != 0xFF)
	{ // 失败
		while (1)
		{
			SOUND_PIN = ~SOUND_PIN;
			delay_ms(500);
		}
	}
}
