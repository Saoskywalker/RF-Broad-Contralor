/**********************************************************************
Name: Internal Lipolysis Instrument(display contral)
Version: v1.0 Released(changed from BJ-ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½v1.0)
Editor: Aysi
Function: 3 channel strength RF
History:2018.8.3: Debug completed
		2018.12.26: change version to vertical RF
		add NTC(PA4 AIN4), sound pin became pump pin(delay_us 500)
		 develop success
		 2019.2.25: NTC error dithering elimination
		 2019.3.13; NTC changed PA7, PA4 use to sound pin
		 2019.4.9: Add WorkSecFlag use for RF(2 WorkFlag)
		 2019.4.15: RF work way changed
**********************************************************************/

//#define DEBUG
#include "stm32f10x.h"
#include "led.h"
#include "delay.h"
//#include "key.h"
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
	nextPage = FUNCTION_RESTART;
	dwSetColor(DW_COL_RED, DW_COL_WHITE);
	dwStopMusic();

	STMFLASH_Read(FLASH_SAVE_ADDR, &i, 1); //read language config ago
	if (i)
		dwSetLanguage(LANGUAGE_ENGLISH);
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
		dwSendByte(0x00);  // ·¢ËÍÎÕÊÖÖ¸Áî
		dwSendOver();
		delay_ms(5);
		if (dwQueryCmd() == 0x74)
		{ // ÎÕÊÖ³É¹¦
			i = 0xFF;
			break;
		}
		delay_ms(200);
	}
	if (i != 0xFF)
	{ // Ê§°Ü
		while (1)
		{
			SOUND_PIN = ~SOUND_PIN;
			delay_ms(500);
		}
	}
}
