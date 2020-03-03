#include "AppLib.h"
#include "delay.h"

_BitAppCon BitAppCon = {0, 0, 0, 0, 0, 0, 0, 0};
u8 nextPage = 0;
u8 requestPage = 0;

//Botton press effect
static const Button btnStart = {PIC_MENUS_P, 676, 133, 786, 214};
static const Button btnPause = {PIC_MENUS_P, 674, 282, 783, 364};
static const Button btnMute = {1, 714, 10, 773, 69};

//Botton original effect
static const Button btnStart_O = {PIC_MENUS, 676, 133, 786, 214};
static const Button btnPause_O = {PIC_MENUS, 674, 282, 783, 364};
static const Button btnMute_O = {2, 714, 10, 773, 69};

u8 CommSendFlag = 0;									  //Send Main Board Buffer or not
_Comm Comm = {FRAME_HEAD, RF_FACE, 1, RF_OFF, FRAME_END}; //Send Main Board Buffer
u16 WorkTime = 0;
u8 WorkIntensity = 0, WorkMode = 0, muteFlag = 0;
u16 WorkSuckTime = 0, WorkReleaseTime = 0;
u16 TimeX, TimeY, IntensityX, IntensityY, ModeX, ModeY, SuckX, SuckY, ReleaseX, ReleaseY;

/*language select*/
static void menuChinsePres(void)
{
	u16 i = 0;

	BitAppCon.menuExit = 1;
	nextPage = FUNCTION_SELECT;
	dwPlayMusic(MSC_BUTTON, 1);
	dwSetLanguage(LANGUAGE_CHINESE);
	STMFLASH_Write(FLASH_SAVE_ADDR, &i, 1); //Write language config
}

static void menuEnglishPres(void)
{
	u16 i = 123;

	BitAppCon.menuExit = 1;
	nextPage = FUNCTION_SELECT;
	dwPlayMusic(MSC_BUTTON, 1);
	dwSetLanguage(LANGUAGE_ENGLISH);
	STMFLASH_Write(FLASH_SAVE_ADDR, &i, 1); //Write language config
}

/*Menu select*/
static void menuEyeRFPres(void)
{
	// if(BitAppCon.WorkFlag)
	// {
	// 	dwPlayMusic(MSC_ERROR, 1);
	// }
	// else
	{
		nextPage = FUNCTION_EYE;
		dwPlayMusic(MSC_BUTTON, 1);
	}
}

static void menuFaceRFPres(void)
{
	// if(BitAppCon.WorkFlag)
	// {
	// 	dwPlayMusic(MSC_ERROR, 1);
	// }
	// else
	{
		nextPage = FUNCTION_FACE;
		dwPlayMusic(MSC_BUTTON, 1);
	}
}

static void menuBodyRFPres(void)
{
	// if(BitAppCon.WorkFlag)
	// {
	// 	dwPlayMusic(MSC_ERROR, 1);
	// }
	// else
	{
		nextPage = FUNCTION_BODY;
		dwPlayMusic(MSC_BUTTON, 1);
	}
}

static void menuO2Pres(void)
{
	// if(BitAppCon.WorkFlag)
	// {
	// 	dwPlayMusic(MSC_ERROR, 1);
	// }
	// else
	{
		nextPage = FUNCTION_O2;
		dwPlayMusic(MSC_BUTTON, 1);
	}
}

static void menuO2BigPres(void)
{
	// if(BitAppCon.WorkFlag)
	// {
	// 	dwPlayMusic(MSC_ERROR, 1);
	// }
	// else
	{
		nextPage = FUNCTION_O2_BIG;
		dwPlayMusic(MSC_BUTTON, 1);
	}
}

static void menuBIO1Pres(void)
{
	// if(BitAppCon.WorkFlag)
	// {
	// 	dwPlayMusic(MSC_ERROR, 1);
	// }
	// else
	{
		nextPage = FUNCTION_BIO1;
		dwPlayMusic(MSC_BUTTON, 1);
	}
}

/*Back button*/
static void BackPres(void)
{
	// if(BitAppCon.WorkFlag)
	// {
	// 	dwPlayMusic(MSC_ERROR, 1);
	// }
	// else
	{
		dwPlayMusic(MSC_BUTTON, 1);
		nextPage = FUNCTION_LANGUAGE;
	}
}

/*Start button*/
static void StartPres(void)
{
	dwPlayMusic(MSC_START, 1);
	if (nextPage != FUNCTION_FACE && nextPage != FUNCTION_BODY)
	{
		BitAppCon.WorkFlag = 1;
		BitAppCon.WorkSecFlag = 1;
		dwDisButton(&btnStart, 1, btnStart.xs, btnStart.ys);
		dwDisButton(&btnPause_O, 1, btnPause_O.xs, btnPause_O.ys);
		if (WorkTime == 0)
		{
			WorkTime = 1800;
		}
	}
	else
	{
		CommSendFlag = 1;
		Comm.onoff = RF_ON;
		BitAppCon.WorkFlag = 1;
		dwDisButton(&btnStart, 1, btnStart.xs, btnStart.ys);
		dwDisButton(&btnPause_O, 1, btnPause_O.xs, btnPause_O.ys);
		if (WorkTime == 0)
		{
			WorkTime = 1800;
		}
	}
}

/*Pause button*/
static void PausePres(void)
{
	dwPlayMusic(MSC_STOP, 1);
	if (nextPage != FUNCTION_FACE && nextPage != FUNCTION_BODY)
	{
		BitAppCon.WorkFlag = 0;
		BitAppCon.WorkSecFlag = 0;
		dwDisButton(&btnStart_O, 1, btnStart_O.xs, btnStart_O.ys);
		dwDisButton(&btnPause, 1, btnPause.xs, btnPause.ys);
	}
	else
	{
		Comm.onoff = RF_OFF;
		BitAppCon.WorkFlag = 0;
		BitAppCon.WorkSecFlag = 0;
		CommSendFlag = 1;
		dwDisButton(&btnStart_O, 1, btnStart_O.xs, btnStart_O.ys);
		dwDisButton(&btnPause, 1, btnPause.xs, btnPause.ys);
	}
}

/*Time button*/
static void TimeUpPres(void)
{
	dwPlayMusic(MSC_BUTTON, 1);
	if (WorkTime < 3600)
	{
		WorkTime += 60;
	}
	funDisTime(WorkTime, TimeX, TimeY);
}

static void TimeDownPres(void)
{
	dwPlayMusic(MSC_BUTTON, 1);
	if (WorkTime > 60)
	{
		WorkTime -= 60;
	}
	funDisTime(WorkTime, TimeX, TimeY);
}

/*Intensity button*/
static void IntensityUpPres(void)
{
	dwPlayMusic(MSC_BUTTON, 1);
	if (nextPage != FUNCTION_FACE && nextPage != FUNCTION_BODY)
	{
		if (WorkIntensity < 8)
		{
			WorkIntensity++;
		}
	}
	else
	{
		if (WorkIntensity < 15)
		{
			WorkIntensity++;
			if (WorkIntensity <= 10)
				Comm.intensity = WorkIntensity;
			else
				Comm.intensity = WorkIntensity * 2 - 10;
			CommSendFlag = 1;
		}
	}
	DisplayIntensity(WorkIntensity, IntensityX, IntensityY);
}

static void IntensityDownPres(void)
{
	dwPlayMusic(MSC_BUTTON, 1);
	if (nextPage != FUNCTION_FACE && nextPage != FUNCTION_BODY)
	{
		if (WorkIntensity > 1)
		{
			WorkIntensity--;
		}
	}
	else
	{
		if (WorkIntensity > 1)
		{
			WorkIntensity--;
			if (WorkIntensity <= 10)
				Comm.intensity = WorkIntensity;
			else
				Comm.intensity = WorkIntensity * 2 - 10;
			CommSendFlag = 1;
		}
	}
	DisplayIntensity(WorkIntensity, IntensityX, IntensityY);
}

/*SUCK RELEASE TIME BUTTON*/
static void SuckTimeUpPres(void)
{
	dwPlayMusic(MSC_BUTTON, 1);
	if (WorkSuckTime < 3000)
		WorkSuckTime+=100;
	DisplayO2Time(WorkSuckTime, SuckX, SuckY);
}

static void SuckTimeDownPres(void)
{
	dwPlayMusic(MSC_BUTTON, 1);
	if (WorkSuckTime > 100)
		WorkSuckTime-=100;
	DisplayO2Time(WorkSuckTime, SuckX, SuckY);
}

static void ReleaseTimeUpPres(void)
{
	dwPlayMusic(MSC_BUTTON, 1);
	if (WorkReleaseTime < 3000)
		WorkReleaseTime+=100;
	DisplayO2Time(WorkReleaseTime, ReleaseX, ReleaseY);
}

static void ReleaseTimeDownPres(void)
{
	dwPlayMusic(MSC_BUTTON, 1);
	if (WorkReleaseTime > 100)
		WorkReleaseTime-=100;
	DisplayO2Time(WorkReleaseTime, ReleaseX, ReleaseY);
}

/*mode button*/
static void ModeUpPres(void)
{
	dwPlayMusic(MSC_BUTTON, 1);

	if (WorkMode < 4)
	{
		WorkMode++;
	}
	DisplayMode(WorkMode, ModeX, ModeY);
}

static void ModeDownPres(void)
{
	dwPlayMusic(MSC_BUTTON, 1);

	if (WorkMode > 1)
	{
		WorkMode--;
	}
	DisplayMode(WorkMode, ModeX, ModeY);
}

/*Other button*/
static void EnterPres(void)
{
	BitAppCon.menuExit = 1;
	nextPage = FUNCTION_SELECT;
	dwPlayMusic(MSC_BUTTON, 1);
}

static void mutePres(void)
{
	u16 i = 0;
	dwPlayMusic(MSC_BUTTON, 1);
	muteFlag = !muteFlag;
	i = muteFlag;
	STMFLASH_Write(FLASH_SAVE_ADDR+2, &i, 1);
	if(muteFlag)
		dwDisButton(&btnMute_O, 0, btnMute_O.xs, btnMute_O.ys);
	else
		dwDisButton(&btnMute, 0, btnMute.xs, btnMute.ys);
}

/*uart1 send to main board*/
void MainBoardSend(void)
{
	if (CommSendFlag == 1)
	{
		CommSendFlag = 0;
		uasrt1SendByte(Comm.head);
		uasrt1SendByte(Comm.channel);
		uasrt1SendByte(Comm.intensity);
		uasrt1SendByte(Comm.onoff);
		uasrt1SendByte(Comm.end);
	}
}

//Power up 
void PageRestartAnimation(void)
{		
	u8 i = 0;

	dwDisPicNoL(0);
	BitAppCon.menuExit = 0;
	for(i = 51; i<=67; i++)
	{
		dwCutPic(i, 0, 0, 764, 532, 0, 0);
		delay_ms(100);
	}
	dwStopMusic();
	nextPage = FUNCTION_SELECT;
	delay_ms(500);
	dwDisPicWithL(11);
	// dwCancelKey();
	// dwListenButton(EnterPres, 0, ENTER_KEY);

	// while (!BitAppCon.menuExit)
	// {
	// 	dwHandlerButton();
	// }
	
	// dwWaitRelease();
	// dwHandlerButton();
}

void PageLanguage(void)
{
	BitAppCon.menuExit = 0;

	//display version
	dwDisChar(DW_SIZE_12, 2, 585, 'V');
	dwDisChar(DW_SIZE_12, 8, 585, '2');
	dwDisChar(DW_SIZE_12, 14, 585, '.');
	dwDisChar(DW_SIZE_12, 20, 585, '3');

	if(muteFlag)
		dwDisButton(&btnMute_O, 0, btnMute_O.xs, btnMute_O.ys);
	else
		dwDisButton(&btnMute, 0, btnMute.xs, btnMute.ys);

	dwCancelKey();
	dwListenButton(menuChinsePres, 0, CHINESE_KEY);
	dwListenButton(menuEnglishPres, 0, ENGLISH_KEY);
	dwListenButton(mutePres, 0, MUTE_KEY);
	while (!BitAppCon.menuExit)
	{
		dwHandlerButton();

		//UART1 time sends datas to main board, avoids data send fail
		if (BitAppCon.ms200)
		{
			BitAppCon.ms200 = 0;
			CommSendFlag = 1;
			MainBoardSend();
		}
	}
	dwWaitRelease();
	dwHandlerButton();
}

void PageMenu(void)
{
	BitAppCon.menuExit = 0;

	dwCancelKey();
	dwListenButton(menuFaceRFPres, 0, FACE_KEY);
	dwListenButton(menuBodyRFPres, 0, BODY_KEY);
	dwListenButton(menuO2Pres, 0, SUCK_MIDDLE_KEY);
	dwListenButton(menuO2BigPres, 0, SUCK_BIG_KEY);
	dwListenButton(menuBIO1Pres, 0, BIO1_KEY);
	dwListenButton(BackPres, 0, SET_KEY);

	while (!BitAppCon.menuExit)
	{
		dwHandlerButton();

		if (nextPage != FUNCTION_SELECT)
		{
			BitAppCon.menuExit = 1;
		}

		//UART1 times send datas to main board
		if (BitAppCon.ms200)
		{
			BitAppCon.ms200 = 0;
			CommSendFlag = 1;
			MainBoardSend();
		}
	}
	dwWaitRelease();
	dwHandlerButton();
}

void WorkTimeDeal(void)
{
	if (BitAppCon.WorkSecFlag)
	{
		if (BitAppCon.Flag1s)
		{
			BitAppCon.Flag1s = 0;
			if (WorkTime > 0)
			{
				WorkTime--;
			}
			else
			{
				dwPlayMusic(MSC_STOP, 1);
				WorkTime = 1800;
				dwDisButton(&btnStart_O, 1, btnStart_O.xs, btnStart_O.ys);
				dwDisButton(&btnPause, 1, btnPause.xs, btnPause.ys);
				BitAppCon.WorkSecFlag = 0;
				BitAppCon.WorkFlag = 0;
				Comm.onoff = RF_OFF;
				CommSendFlag = 1;
			}
			funDisTime(WorkTime, TimeX, TimeY);
		}
	}
}

void PageEyeRF(void)
{
	CommSendFlag = 0;
	WorkTime = 1800;
	WorkIntensity = 1;
	Comm.channel = RF_FACE;
	Comm.intensity = WorkIntensity;
	Comm.onoff = RF_OFF;
	BitAppCon.menuExit = 0;
	TimeX = 272; 
	TimeY = 258;
	IntensityX = 300;
	IntensityY = 187;

	dwDisButton(&btnPause, 1, btnPause.xs, btnPause.ys);
	funDisTime(WorkTime, TimeX, TimeY);
	DisplayIntensity(WorkIntensity, IntensityX, IntensityY);

	dwCancelKey();
	dwListenButton(menuFaceRFPres, 0, FACE_KEY);
	dwListenButton(menuBodyRFPres, 0, BODY_KEY);
	dwListenButton(menuO2Pres, 0, SUCK_MIDDLE_KEY);
	dwListenButton(menuO2BigPres, 0, SUCK_BIG_KEY);
	dwListenButton(menuBIO1Pres, 0, BIO1_KEY);
	dwListenButton(StartPres, 0, START_KEY);
	dwListenButton(PausePres, 0, STOP_KEY);
	dwListenButton(TimeUpPres, 0, TIME_UP_KEY);
	dwListenButton(TimeDownPres, 0, TIME_DOWN_KEY);
	dwListenButton(IntensityUpPres, 0, INT_UP_KEY);
	dwListenButton(IntensityDownPres, 0, INT_DOWN_KEY);

	while (!BitAppCon.menuExit)
	{
		dwHandlerButton();

		if (nextPage != FUNCTION_EYE)
		{
			CommSendFlag = 1;
			BitAppCon.menuExit = 1;
			Comm.onoff = RF_OFF;
			BitAppCon.WorkFlag = 0;
			BitAppCon.WorkSecFlag = 0;
		}

		WorkTimeDeal();

		//UART1 time sends datas to main board, avoids data send fail
		if (BitAppCon.ms200)
		{
			BitAppCon.ms200 = 0;
			CommSendFlag = 1;
			MainBoardSend();
		}

		//current is over high warning, and pauses
		if (BitAppCon.rx1Flag)
		{
			BitAppCon.rx1Flag = 0;
			if (buff1[0] == 0xEE)
			{
				dwPlayMusic(MSC_ALERT, 1);
				dwDisButton(&btnStart_O, 1, btnStart_O.xs, btnStart_O.ys);
				dwDisButton(&btnPause, 1, btnPause.xs, btnPause.ys);
				Comm.onoff = RF_OFF;
				BitAppCon.WorkFlag = 0;
				BitAppCon.WorkSecFlag = 0;
				CommSendFlag = 1;
			}
			else if((buff1[0] == 0xA0)&&BitAppCon.WorkFlag) //PRESS
			{
				BitAppCon.WorkSecFlag = 1;
				dwPlayMusic(MSC_BUTTON, 1);
			}
			else if((buff1[0] == 0xA1)&&BitAppCon.WorkFlag) //RELEASE
			{
				if(BitAppCon.WorkSecFlag)
				{
					BitAppCon.WorkSecFlag = 0;
					dwPlayMusic(MSC_BUTTON, 1);
				}
			}
		}
	}
	dwWaitRelease();
	dwHandlerButton();
}

void PageFaceRF(void)
{
	CommSendFlag = 0;
	WorkTime = 1800;
	WorkIntensity = 1;
	Comm.channel = RF_FACE;
	Comm.intensity = WorkIntensity;
	Comm.onoff = RF_OFF;
	BitAppCon.menuExit = 0;
	TimeX = 272; 
	TimeY = 258;
	IntensityX = 300;
	IntensityY = 187;

	dwDisButton(&btnPause, 1, btnPause.xs, btnPause.ys);
	funDisTime(WorkTime, TimeX, TimeY);
	DisplayIntensity(WorkIntensity, IntensityX, IntensityY);

	dwCancelKey();
	dwListenButton(menuFaceRFPres, 0, FACE_KEY);
	dwListenButton(menuBodyRFPres, 0, BODY_KEY);
	dwListenButton(menuO2Pres, 0, SUCK_MIDDLE_KEY);
	dwListenButton(menuO2BigPres, 0, SUCK_BIG_KEY);
	dwListenButton(menuBIO1Pres, 0, BIO1_KEY);
	dwListenButton(StartPres, 0, START_KEY);
	dwListenButton(PausePres, 0, STOP_KEY);
	dwListenButton(TimeUpPres, 0, TIME_UP_KEY);
	dwListenButton(TimeDownPres, 0, TIME_DOWN_KEY);
	dwListenButton(IntensityUpPres, 0, INT_UP_KEY);
	dwListenButton(IntensityDownPres, 0, INT_DOWN_KEY);

	while (!BitAppCon.menuExit)
	{
		dwHandlerButton();

		if (nextPage != FUNCTION_FACE)
		{
			CommSendFlag = 1;
			BitAppCon.menuExit = 1;
			Comm.onoff = RF_OFF;
			BitAppCon.WorkFlag = 0;
			BitAppCon.WorkSecFlag = 0;
		}

		WorkTimeDeal();

		//UART1 time sends datas to main board, avoids data send fail
		if (BitAppCon.ms200)
		{
			BitAppCon.ms200 = 0;
			CommSendFlag = 1;
			MainBoardSend();
		}

		//current is over high warning, and pauses
		if (BitAppCon.rx1Flag)
		{
			BitAppCon.rx1Flag = 0;
			if (buff1[0] == 0xEE)
			{
				dwPlayMusic(MSC_ALERT, 1);
				dwDisButton(&btnStart_O, 1, btnStart_O.xs, btnStart_O.ys);
				dwDisButton(&btnPause, 1, btnPause.xs, btnPause.ys);
				Comm.onoff = RF_OFF;
				BitAppCon.WorkFlag = 0;
				BitAppCon.WorkSecFlag = 0;
				CommSendFlag = 1;
			}
			else if((buff1[0] == 0xA0)&&BitAppCon.WorkFlag) //PRESS
			{
				BitAppCon.WorkSecFlag = 1;
				dwPlayMusic(MSC_BUTTON, 1);
			}
			else if((buff1[0] == 0xA1)&&BitAppCon.WorkFlag) //RELEASE
			{
				if(BitAppCon.WorkSecFlag)
				{
					BitAppCon.WorkSecFlag = 0;
					dwPlayMusic(MSC_BUTTON, 1);
				}
			}
		}
	}
	dwWaitRelease();
	dwHandlerButton();
}

void PageBodyRF(void)
{
	CommSendFlag = 0;
	WorkTime = 1800;
	WorkIntensity = 1;
	Comm.channel = RF_BODY;
	Comm.intensity = WorkIntensity;
	Comm.onoff = RF_OFF;
	BitAppCon.menuExit = 0;
	TimeX = 272; 
	TimeY = 258;
	IntensityX = 300;
	IntensityY = 187;

	dwDisButton(&btnPause, 1, btnPause.xs, btnPause.ys);
	funDisTime(WorkTime, TimeX, TimeY);
	DisplayIntensity(WorkIntensity, IntensityX, IntensityY);

	dwCancelKey();
	dwListenButton(menuFaceRFPres, 0, FACE_KEY);
	dwListenButton(menuBodyRFPres, 0, BODY_KEY);
	dwListenButton(menuO2Pres, 0, SUCK_MIDDLE_KEY);
	dwListenButton(menuO2BigPres, 0, SUCK_BIG_KEY);
	dwListenButton(menuBIO1Pres, 0, BIO1_KEY);
	dwListenButton(StartPres, 0, START_KEY);
	dwListenButton(PausePres, 0, STOP_KEY);
	dwListenButton(TimeUpPres, 0, TIME_UP_KEY);
	dwListenButton(TimeDownPres, 0, TIME_DOWN_KEY);
	dwListenButton(IntensityUpPres, 0, INT_UP_KEY);
	dwListenButton(IntensityDownPres, 0, INT_DOWN_KEY);
	
	while (!BitAppCon.menuExit)
	{
		dwHandlerButton();

		if (nextPage != FUNCTION_BODY)
		{
			CommSendFlag = 1;
			BitAppCon.menuExit = 1;
			Comm.onoff = RF_OFF;
			BitAppCon.WorkFlag = 0;
			BitAppCon.WorkSecFlag = 0;
		}

		WorkTimeDeal();

		//UART1 time sends datas to main board, avoids data send fail
		if (BitAppCon.ms200)
		{
			BitAppCon.ms200 = 0;
			CommSendFlag = 1;
			MainBoardSend();
		}

		//current is over high warning, and pauses
		if (BitAppCon.rx1Flag)
		{
			BitAppCon.rx1Flag = 0;
			if (buff1[0] == 0xEE)
			{
				dwPlayMusic(MSC_ALERT, 1);
				dwDisButton(&btnStart_O, 1, btnStart_O.xs, btnStart_O.ys);
				dwDisButton(&btnPause, 1, btnPause.xs, btnPause.ys);
				Comm.onoff = RF_OFF;
				BitAppCon.WorkFlag = 0;
				BitAppCon.WorkSecFlag = 0;
				CommSendFlag = 1;
			}
			else if((buff1[0] == 0xA0)&&BitAppCon.WorkFlag) //PRESS
			{
				BitAppCon.WorkSecFlag = 1;
				dwPlayMusic(MSC_BUTTON, 1);
			}
			else if((buff1[0] == 0xA1)&&BitAppCon.WorkFlag) //RELEASE
			{
				if(BitAppCon.WorkSecFlag)
				{
					BitAppCon.WorkSecFlag = 0;
					dwPlayMusic(MSC_BUTTON, 1);
				}
			}
		}
	}
	dwWaitRelease();
	dwHandlerButton();
}

void PageBIO1(void)
{
	WorkTime = 1800;
	WorkIntensity = 1;
	WorkMode = 1;
	BitAppCon.menuExit = 0;
	TimeX = 272; 
	TimeY = 287;
	IntensityX = 300;
	IntensityY = 142;
	ModeX = 319;
	ModeY = 211;

	dwDisButton(&btnPause, 1, btnPause.xs, btnPause.ys);
	funDisTime(WorkTime, TimeX, TimeY);
	DisplayIntensity(WorkIntensity, IntensityX, IntensityY);
	DisplayMode(WorkMode, ModeX, ModeY);

	dwCancelKey();
	dwListenButton(menuFaceRFPres, 0, FACE_KEY);
	dwListenButton(menuBodyRFPres, 0, BODY_KEY);
	dwListenButton(menuO2Pres, 0, SUCK_MIDDLE_KEY);
	dwListenButton(menuO2BigPres, 0, SUCK_BIG_KEY);
	dwListenButton(menuBIO1Pres, 0, BIO1_KEY);
	dwListenButton(StartPres, 0, START_KEY);
	dwListenButton(PausePres, 0, STOP_KEY);
	dwListenButton(TimeUpPres, 0, TIME_UP_KEY);
	dwListenButton(TimeDownPres, 0, TIME_DOWN_KEY);
	dwListenButton(IntensityUpPres, 0, INT_UP_KEY);
	dwListenButton(IntensityDownPres, 0, INT_DOWN_KEY);
	dwListenButton(ModeUpPres, 0, MODE_UP_KEY);
	dwListenButton(ModeDownPres, 0, MODE_DOWN_KEY);

	while (!BitAppCon.menuExit)
	{
		dwHandlerButton();
		if (nextPage != FUNCTION_BIO1)
		{
			BitAppCon.menuExit = 1;
			BitAppCon.WorkFlag = 0;
			BitAppCon.WorkSecFlag = 0;
		}
		WorkTimeDeal();
		if (BitAppCon.WorkFlag)
		{
		}
		else
		{
			delay_ms(5); //wait BIO1PWM & BIO1Power off
		}

		//UART1 times send datas to main board
		if (BitAppCon.ms200)
		{
			BitAppCon.ms200 = 0;
			// printf("T:%d\n", IceTemperature);
			CommSendFlag = 1;
			MainBoardSend();
		}
	}
	dwWaitRelease();
	dwHandlerButton();
}

//Temperature Process
const u16 TemperatureTable[] = {0, 1396, 1296, 1196, 1096,
								996, 796, 596, 498};
u16 IceTemperature = 0;
static u8 NtcErrorFlag = 0;
void TemperatureProcess(void)
{
	static u16 i = 0;
	
	//NTC ERROR
	if(IceTemperature>=4000||IceTemperature<=100)
	{
		if(++i>=10000)
		{
			i = 10000;
			if(NtcErrorFlag==0)
			{
				NtcErrorFlag = 1;
				HEAT_PIN = 0;
				dwPlayMusic(MSC_ALERT, 1);
			}			
		}
	}
	else
	{
		if (i>=25)
			i -= 25;
		else
			i = 0;
		if(i==0)
			NtcErrorFlag = 0;

		if(IceTemperature>=TemperatureTable[WorkIntensity]+16)
			HEAT_PIN = 1;
		if(IceTemperature<=TemperatureTable[WorkIntensity])
			HEAT_PIN = 0;
	}
}

void PageO2(void)
{
	BACK1_PIN = 0; //change channel
	WorkTime = 1800;
	WorkIntensity = 1;
	WorkMode = 1;
	WorkReleaseTime = 1000;
	WorkSuckTime = 1000;
	BitAppCon.menuExit = 0;
	TimeX = 272; 
	TimeY = 309;
	IntensityX = 300;
	IntensityY = 234;
	ReleaseX = 293;
	ReleaseY = 165;
	SuckX = 293;
	SuckY = 93;

	dwDisButton(&btnPause, 1, btnPause.xs, btnPause.ys);
	funDisTime(WorkTime, TimeX, TimeY);
	DisplayIntensity(WorkIntensity, IntensityX, IntensityY);
	DisplayO2Time(WorkReleaseTime, ReleaseX, ReleaseY);
	DisplayO2Time(WorkSuckTime, SuckX, SuckY);

	dwCancelKey();
	dwListenButton(menuFaceRFPres, 0, FACE_KEY);
	dwListenButton(menuBodyRFPres, 0, BODY_KEY);
	dwListenButton(menuO2Pres, 0, SUCK_MIDDLE_KEY);
	dwListenButton(menuO2BigPres, 0, SUCK_BIG_KEY);
	dwListenButton(menuBIO1Pres, 0, BIO1_KEY);
	dwListenButton(StartPres, 0, START_KEY);
	dwListenButton(PausePres, 0, STOP_KEY);
	dwListenButton(TimeUpPres, 0, TIME_UP_KEY);
	dwListenButton(TimeDownPres, 0, TIME_DOWN_KEY);
	dwListenButton(IntensityUpPres, 0, INT_UP_KEY);
	dwListenButton(IntensityDownPres, 0, INT_DOWN_KEY);
	dwListenButton(ReleaseTimeUpPres, 0, RELEASE_UP_KEY);
	dwListenButton(ReleaseTimeDownPres, 0, RELEASE_DOWN_KEY);
	dwListenButton(SuckTimeUpPres, 0, SUCK_UP_KEY);
	dwListenButton(SuckTimeDownPres, 0, SUCK_DOWN_KEY);

	while (!BitAppCon.menuExit)
	{
		dwHandlerButton();
		if (nextPage != FUNCTION_O2)
		{
			BitAppCon.menuExit = 1;
			BitAppCon.WorkFlag = 0;
			BitAppCon.WorkSecFlag = 0;
		}
		WorkTimeDeal();
		if (BitAppCon.WorkFlag)
		{
			IceTemperature = Get_Adc_Average(ADC_Channel_7,6);	
			TemperatureProcess();
			PUMP_PIN = 1;
		}
		else
		{
			BACK1_PIN = 0;
			HEAT_PIN = 0;
			Valve_PIN = 0;
			PUMP_PIN = 0;
			NtcErrorFlag = 0;
		}

		//UART1 times send datas to main board
		if (BitAppCon.ms200)
		{
			BitAppCon.ms200 = 0;
			// printf("T:%d\n", IceTemperature);
			CommSendFlag = 1;
			MainBoardSend();
		}
	}
	dwWaitRelease();
	dwHandlerButton();
}

void PageO2Big(void)
{
	BACK1_PIN = 1; //change channel
	WorkTime = 1800;
	WorkIntensity = 1;
	WorkMode = 1;
	WorkReleaseTime = 1000;
	WorkSuckTime = 1000;
	BitAppCon.menuExit = 0;
	TimeX = 272; 
	TimeY = 309;
	IntensityX = 300;
	IntensityY = 234;
	ReleaseX = 293;
	ReleaseY = 165;
	SuckX = 293;
	SuckY = 93;

	dwDisButton(&btnPause, 1, btnPause.xs, btnPause.ys);
	funDisTime(WorkTime, TimeX, TimeY);
	DisplayIntensity(WorkIntensity, IntensityX, IntensityY);
	DisplayO2Time(WorkReleaseTime, ReleaseX, ReleaseY);
	DisplayO2Time(WorkSuckTime, SuckX, SuckY);

	dwCancelKey();
	dwListenButton(menuFaceRFPres, 0, FACE_KEY);
	dwListenButton(menuBodyRFPres, 0, BODY_KEY);
	dwListenButton(menuO2Pres, 0, SUCK_MIDDLE_KEY);
	dwListenButton(menuO2BigPres, 0, SUCK_BIG_KEY);
	dwListenButton(menuBIO1Pres, 0, BIO1_KEY);
	dwListenButton(StartPres, 0, START_KEY);
	dwListenButton(PausePres, 0, STOP_KEY);
	dwListenButton(TimeUpPres, 0, TIME_UP_KEY);
	dwListenButton(TimeDownPres, 0, TIME_DOWN_KEY);
	dwListenButton(IntensityUpPres, 0, INT_UP_KEY);
	dwListenButton(IntensityDownPres, 0, INT_DOWN_KEY);
	dwListenButton(ReleaseTimeUpPres, 0, RELEASE_UP_KEY);
	dwListenButton(ReleaseTimeDownPres, 0, RELEASE_DOWN_KEY);
	dwListenButton(SuckTimeUpPres, 0, SUCK_UP_KEY);
	dwListenButton(SuckTimeDownPres, 0, SUCK_DOWN_KEY);

	while (!BitAppCon.menuExit)
	{
		dwHandlerButton();
		if (nextPage != FUNCTION_O2_BIG)
		{
			BitAppCon.menuExit = 1;
			BitAppCon.WorkFlag = 0;
			BitAppCon.WorkSecFlag = 0;
		}
		WorkTimeDeal();
		if (BitAppCon.WorkFlag)
		{
			IceTemperature = Get_Adc_Average(ADC_Channel_7,6);	
			TemperatureProcess();
			PUMP_PIN = 1;
		}
		else
		{
			BACK1_PIN = 0;
			HEAT_PIN = 0;
			Valve_PIN = 0;
			PUMP_PIN = 0;
			NtcErrorFlag = 0;
		}

		//UART1 times send datas to main board
		if (BitAppCon.ms200)
		{
			BitAppCon.ms200 = 0;
			// printf("T:%d\n", IceTemperature);
			CommSendFlag = 1;
			MainBoardSend();
		}
	}
	dwWaitRelease();
	dwHandlerButton();
}

//O2 PWM
const u16 O2ModPeriod[] = {0, 2000, 4000, 4000, 1000, 5000};
const u16 O2ModCompare[] = {0, 1000, 2000, 3000, 1000, 250};

/* void O2PWM(u8 i, u8 Work)
{
	static u16 O2TimeCnt = 0;
	static u8 O2ModRenew = 0;

	if (Work)
	{
		O2ModRenew = i;
		if (++O2TimeCnt >= O2ModPeriod[O2ModRenew])
		{
			O2TimeCnt = 0;
		}
		if ((O2TimeCnt < O2ModCompare[O2ModRenew]))
			Valve_PIN = 0;
		else
			Valve_PIN = 1;
	}
	else
	{
		O2TimeCnt = 0;
		Valve_PIN = 0;
	}
} */

void O2PWM(u16 suck, u16 release, u8 Work)
{
	static u16 O2TimeCnt = 0;

	if (Work)
	{
		if (++O2TimeCnt >= suck+release)
		{
			O2TimeCnt = 0;
		}
		if (O2TimeCnt < suck)
			Valve_PIN = 0;
		else
			Valve_PIN = 1;
	}
	else
	{
		O2TimeCnt = 0;
		Valve_PIN = 0;
	}
}

//BIO1 PWM
const u16 BIO1IntensityTable[] = {0, 36, 38, 40, 42, 44, 46, 48, 50};
const u16 BIO1ModPeriod[] = {0, 11, 330, 400, 500};
const u16 BIO1ModCompare[] = {0, 3, 2, 240, 100};
void BIO1PWM(u8 i, u8 Work)
{
	static u16 BIO1TimeCnt = 0;
	static u8 BIO1ModRenew = 0;

	if (Work)
	{
		if (++BIO1TimeCnt >= BIO1ModPeriod[BIO1ModRenew])
		{
			BIO1TimeCnt = 0;
			BIO1ModRenew = i;
		}
		if ((BIO1TimeCnt < BIO1ModCompare[BIO1ModRenew]))
			BIOS_PIN = 0; //open
		else
			BIOS_PIN = 1; //close
	}
	else
	{
		BIO1TimeCnt = 0;
		BIOS_PIN = 1; //close
	}
}

void BIO1Power(u8 i, u8 Work)
{
	static u16 BIO1TimeCnt = 0;
	static u8 BIO1ModRenew = 0;

	if (Work)
	{
		if (++BIO1TimeCnt >= 75)
		{
			BIO1TimeCnt = 0;
			BIO1ModRenew = i;
		}
		if ((BIO1TimeCnt < BIO1IntensityTable[BIO1ModRenew]))
			BIOA_PIN = 1;
		else
			BIOA_PIN = 0;
	}
	else
	{
		BIO1TimeCnt = 0;
		BIOA_PIN = 0;
	}
}

//Rec and process frame
u8 buff1[5];
void commRx1Handler(u8 byte)
{
	static u8 count = 0;

	if (count == 0)
	{
		if (byte == 0xAA)
		{
			count++;
		}
	}
	else if (count < 2)
	{
		buff1[count - 1] = byte;
		count++;
	}
	else
	{
		count = 0;
		if (byte == 0x55)
		{
			BitAppCon.rx1Flag = 1;
		}
	}
}

/*Bee function*/
const u16 BeeModPeriod[] = {110, 410, 1000, 1010, 3010};
const u16 BeeModCompare[] = {100, 400, 500, 1000, 3000};
u8 BeeMod = 0, BeeTime = 0;
void BeeFunction(void)
{
	static u16 BeeTimeCnt = 0;

	if (BeeTime > 0)
	{
		if (++BeeTimeCnt >= BeeModPeriod[BeeMod])
		{
			BeeTimeCnt = 0;
			BeeTime--;
		}
		else
		{
			if (BeeTimeCnt >= BeeModCompare[BeeMod])
				SOUND_PIN = 0;
			else
				SOUND_PIN = 1;
		}
	}
	else
	{
		BeeTimeCnt = 0;
		SOUND_PIN = 0;
	}
}
////////////////////////////////////////
