#include "AppLib.h"

_BitAppCon BitAppCon = {0, 0, 0, 0, 0, 0, 0, 0};
u8 nextPage = 0;
u8 requestPage = 0;
u16 CoolIntensity[] = {0, 1700, 1800, 1900, 2000, 2175, 2275, 2375, 2475, 2550, 2625};
u8 ExplainNum = 0;

//Botton press effect
static const Button btnSet = {PIC_MENUS_P, 633, 16, 633+162, 16+55};
static const Button btnEnter  = {PIC_MENUS_P, 0, 0, 799, 599};
static const Button btnChinse = {PIC_LANGUAGE_P, 65, 238, 65+180, 238+124};
static const Button btnEnglish = {PIC_LANGUAGE_P, 310, 238, 310+180, 238+124};
static const Button btnKorean = {PIC_LANGUAGE_P, 555, 238, 555+180, 238+124};
static const Button btnFaceRF = {PIC_MENUS_P, 483, 244, 483+236, 244+82};
static const Button btnBodyRF = {PIC_MENUS_P, 483, 344, 483+236, 344+82};
static const Button btnEyeRF = {PIC_MENUS_P, 483, 151, 483+236, 151+82};
static const Button btnO2 = {PIC_MENUS_P, 483, 443, 483+236, 443+82};
static const Button btnCOOL = {PIC_MENUS_P, 619, 469, 767, 571};
static const Button btnExplain = {PIC_MENUS_P, 644, 6, 776, 63};
static const Button btnStart = {PIC_FUN_BUT_P, 286, 473, 286+65, 473+65};
static const Button btnPause = {PIC_FUN_BUT_P, 418, 473, 418+65, 473+65};
static const Button btnBack = {PIC_FUN_BUT_P, 551, 473, 551+65, 473+65};
static const Button btnTimeDown = {PIC_FUN_BUT_P, 145, 344, 145+55, 344+55};
static const Button btnTimeUp = {PIC_FUN_BUT_P, 378, 344, 378+55, 344+55};
static const Button btnIntensityDown = {PIC_FUN_BUT_P, 468, 344, 468+55, 344+55};
static const Button btnIntensityUp = {PIC_FUN_BUT_P, 701, 344, 701+55, 344+55};
static const Button btnModeDown = {PIC_FUN_BUT_P_O2, 145, 362, 145+55, 362+55};
static const Button btnModeUp = {PIC_FUN_BUT_P_O2, 378, 362, 378+55, 362+55};
static const Button btnTimeDown_O2 = {PIC_FUN_BUT_P_O2, 307, 246, 307+55, 246+55};
static const Button btnTimeUp_O2 = {PIC_FUN_BUT_P_O2, 540, 246, 540+55, 246+55};
static const Button btnIntensityDown_O2 = {PIC_FUN_BUT_P_O2, 468, 361, 468+55, 361+55};
static const Button btnIntensityUp_O2 = {PIC_FUN_BUT_P_O2, 701, 361, 701+55, 361+55};

//Botton original effect
static const Button btnStart_O = {PIC_FUN_BUT, 286, 473, 286+65, 473+65};
static const Button btnPause_O = {PIC_FUN_BUT, 418, 473, 418+65, 473+65};
// static const Button btnBack_O = {PIC_FUN_BUT, 551, 473, 551+65, 473+65};
static const Button btnTimeDown_O = {PIC_FUN_BUT, 145, 344, 145+55, 344+55};
static const Button btnTimeUp_O = {PIC_FUN_BUT, 378, 344, 378+55, 344+55};
static const Button btnIntensityDown_O = {PIC_FUN_BUT, 468, 344, 468+55, 344+55};
static const Button btnIntensityUp_O = {PIC_FUN_BUT, 701, 344, 701+55, 344+55};
static const Button btnModeDown_O = {PIC_FUN_BUT_O2, 145, 362, 145+55, 362+55};
static const Button btnModeUp_O = {PIC_FUN_BUT_O2, 378, 362, 378+55, 362+55};
static const Button btnTimeDown_O_O2 = {PIC_FUN_BUT_O2, 307, 246, 307+55, 246+55};
static const Button btnTimeUp_O_O2 = {PIC_FUN_BUT_O2, 540, 246, 540+55, 246+55};
static const Button btnIntensityDown_O_O2 = {PIC_FUN_BUT_O2, 468, 361, 468+55, 361+55};
static const Button btnIntensityUp_O_O2 = {PIC_FUN_BUT_O2, 701, 361, 701+55, 361+55};
static const Button btnExplainExit_O = {PIC_EXPLAIN, 24, 17, 96, 82};
static const Button btnExplainNext_O = {PIC_EXPLAIN, 358, 510, 444, 589};

u8 CommSendFlag = 0;									  //Send Main Board Buffer or not
_Comm Comm = {FRAME_HEAD, RF_FACE, 1, RF_OFF, FRAME_END}; //Send Main Board Buffer
u16 WorkTime = 0;
u8 WorkIntensity = 0, WorkMode = 0;

/*language select*/
void menuChinsePres(void)
{
	u16 i = 0;

	BitAppCon.menuExit = 1;
	nextPage = FUNCTION_SELECT;
	INLINE_MUSIC_BUTTON();
	//dwDisButton(&btnChinse, 0, btnChinse.xs, btnChinse.ys);
	dwSetLanguage(LANGUAGE_CHINESE);
	STMFLASH_Write(FLASH_SAVE_ADDR, &i, 1); //Write language config
}

void menuEnglishPres(void)
{
	u16 i = 123;

	BitAppCon.menuExit = 1;
	nextPage = FUNCTION_SELECT;
	INLINE_MUSIC_BUTTON();
	//dwDisButton(&btnEnglish, 0, btnEnglish.xs, btnEnglish.ys);
	dwSetLanguage(LANGUAGE_ENGLISH);
	STMFLASH_Write(FLASH_SAVE_ADDR, &i, 1); //Write language config
}

void menuKoreanPres(void)
{
	u16 i = 150;

	BitAppCon.menuExit = 1;
	nextPage = FUNCTION_SELECT;
	INLINE_MUSIC_BUTTON();
	//dwDisButton(&btnEnglish, 0, btnEnglish.xs, btnEnglish.ys);
	dwSetLanguage(LANGUAGE_KOREAN);
	STMFLASH_Write(FLASH_SAVE_ADDR, &i, 1); //Write language config
}

/*Menu select*/
void SetPres(void)
{
	{
		nextPage = FUNCTION_LANGUAGE;
		INLINE_MUSIC_BUTTON();
		dwDisButton(&btnSet, 1, btnSet.xs, btnSet.ys);
	}
}

void menuEyeRFPres(void)
{
	{
		nextPage = FUNCTION_EYE;
		INLINE_MUSIC_BUTTON();
		dwDisButton(&btnEyeRF, 1, btnEyeRF.xs, btnEyeRF.ys);
	}
}

void menuFaceRFPres(void)
{
	{
		nextPage = FUNCTION_FACE;
		INLINE_MUSIC_BUTTON();
		dwDisButton(&btnFaceRF, 1, btnFaceRF.xs, btnFaceRF.ys);
	}
}

void menuBodyRFPres(void)
{
	{
		nextPage = FUNCTION_BODY;
		INLINE_MUSIC_BUTTON();
		dwDisButton(&btnBodyRF, 1, btnBodyRF.xs, btnBodyRF.ys);
	}
}

void menuO2Pres(void)
{
	// if(BitAppCon.WorkFlag)
	// {
	// 	dwPlayMusic(MSC_ERROR, 1);
	// }
	// else
	{
		nextPage = FUNCTION_O2;
		INLINE_MUSIC_BUTTON();
		dwDisButton(&btnO2, 1, btnO2.xs, btnO2.ys);
	}
}

void menuCoolPres(void)
{
	{
		BitAppCon.menuExit = 1;
		nextPage = FUNCTION_COOL;
		INLINE_MUSIC_BUTTON();
		dwDisButton(&btnCOOL, 1, btnCOOL.xs, btnCOOL.ys);
	}
}

void menuExplainPres(void)
{
	BitAppCon.menuExit = 1;
	nextPage = FUNCTION_EXPLAIN;
	INLINE_MUSIC_BUTTON();
	dwDisButton(&btnExplain, 1, btnExplain.xs, btnExplain.ys);
}

/*Start button*/
void StartPres(void)
{
	INLINE_MUSIC_START();
	dwDisButton(&btnStart, 1, btnStart.xs, btnStart.ys);
	dwDisButton(&btnPause_O, 1, btnPause_O.xs, btnPause_O.ys);

	switch (nextPage)
	{
	case FUNCTION_O2:
	{
		BitAppCon.WorkFlag = 1;
		BitAppCon.WorkSecFlag = 1;
		
		if (WorkTime == 0)
		{
			WorkTime = 1800;
		}
		break;
	}
	default:
	{
		CommSendFlag = 1;
		Comm.onoff = RF_ON;
		BitAppCon.WorkFlag = 1;
		if (WorkTime == 0)
		{
			WorkTime = 1800;
		}
		break;
	}
	}
}

void StartFree(void)
{
}

/*Pause button*/
void PausePres(void)
{
	INLINE_MUSIC_BUTTON();
	dwDisButton(&btnStart_O, 1, btnStart_O.xs, btnStart_O.ys);
	dwDisButton(&btnPause, 1, btnPause.xs, btnPause.ys);

	if (nextPage==FUNCTION_O2)
	{
		BitAppCon.WorkFlag = 0;
		BitAppCon.WorkSecFlag = 0;
	}
	else
	{
		Comm.onoff = RF_OFF;
		BitAppCon.WorkFlag = 0;
		BitAppCon.WorkSecFlag = 0;
		CommSendFlag = 1;
	}	
}

void PauseFree(void)
{
}

/*Back button*/
void BackPres(void)
{
	INLINE_MUSIC_BUTTON();
	dwDisButton(&btnBack, 1, btnBack.xs, btnBack.ys);
}

void BackFree(void)
{
	nextPage = FUNCTION_SELECT;
}

/*Time button*/
void TimeUpPres(void)
{
	INLINE_MUSIC_BUTTON();
	if (nextPage==FUNCTION_O2)
		dwDisButton(&btnTimeUp_O2, 1, btnTimeUp_O2.xs, btnTimeUp_O2.ys);
	else
		dwDisButton(&btnTimeUp, 1, btnTimeUp.xs, btnTimeUp.ys);
	if (WorkTime < 3600)
	{
		WorkTime += 60;
	}
	funDisTime(WorkTime);
}

void TimeUpFree(void)
{
	if (nextPage==FUNCTION_O2)
		dwDisButton(&btnTimeUp_O_O2, 1, btnTimeUp_O_O2.xs, btnTimeUp_O_O2.ys);
	else
		dwDisButton(&btnTimeUp_O, 1, btnTimeUp_O.xs, btnTimeUp_O.ys);
}

void TimeDownPres(void)
{
	INLINE_MUSIC_BUTTON();
	if (nextPage==FUNCTION_O2)
		dwDisButton(&btnTimeDown_O2, 1, btnTimeDown_O2.xs, btnTimeDown_O2.ys);
	else
		dwDisButton(&btnTimeDown, 1, btnTimeDown.xs, btnTimeDown.ys);
	if (WorkTime > 60)
	{
		WorkTime -= 60;
	}
	funDisTime(WorkTime);
}

void TimeDownFree(void)
{
	if (nextPage==FUNCTION_O2)
	dwDisButton(&btnTimeDown_O_O2, 1, btnTimeDown_O_O2.xs, btnTimeDown_O_O2.ys);
	else
		dwDisButton(&btnTimeDown_O, 1, btnTimeDown_O.xs, btnTimeDown_O.ys);
}

/*Intensity button*/
void IntensityUpPres(void)
{
	INLINE_MUSIC_BUTTON();

	if (nextPage == FUNCTION_O2)
	{
		if (WorkIntensity < 8)
		{
			WorkIntensity++;
		}
		DisplayIntensity(WorkIntensity);
		dwDisButton(&btnIntensityUp_O2, 1, btnIntensityUp_O2.xs, btnIntensityUp_O2.ys);
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
		DisplayIntensity(WorkIntensity);
		dwDisButton(&btnIntensityUp, 1, btnIntensityUp.xs, btnIntensityUp.ys);
	}
}

void IntensityUpFree(void)
{
	if (nextPage == FUNCTION_O2)
		dwDisButton(&btnIntensityUp_O_O2, 1, btnIntensityUp_O_O2.xs, btnIntensityUp_O_O2.ys);
	else
		dwDisButton(&btnIntensityUp_O, 1, btnIntensityUp_O.xs, btnIntensityUp_O.ys);
}

void IntensityDownPres(void)
{
	INLINE_MUSIC_BUTTON();

	if (nextPage == FUNCTION_O2)
	{
		if (WorkIntensity > 1)
		{
			WorkIntensity--;
		}
		DisplayIntensity(WorkIntensity); 
		dwDisButton(&btnIntensityDown_O2, 1, btnIntensityDown_O2.xs, btnIntensityDown_O2.ys);
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
		DisplayIntensity(WorkIntensity);
		dwDisButton(&btnIntensityDown, 1, btnIntensityDown.xs, btnIntensityDown.ys);
	}
}

void IntensityDownFree(void)
{
	if (nextPage == FUNCTION_O2)
		dwDisButton(&btnIntensityDown_O_O2, 1, btnIntensityDown_O_O2.xs, btnIntensityDown_O_O2.ys);
	else
		dwDisButton(&btnIntensityDown_O, 1, btnIntensityDown_O.xs, btnIntensityDown_O.ys);
}

/*mode button*/
void ModeUpPres(void)
{
	INLINE_MUSIC_BUTTON();
	dwDisButton(&btnModeUp, 1, btnModeUp.xs, btnModeUp.ys);

	if (WorkMode < 4)
	{
		WorkMode++;
	}
	DisplayMode(WorkMode);
}

void ModeUpFree(void)
{
	dwDisButton(&btnModeUp_O, 1, btnModeUp_O.xs, btnModeUp_O.ys);
}

void ModeDownPres(void)
{
	INLINE_MUSIC_BUTTON();
	dwDisButton(&btnModeDown, 1, btnModeDown.xs, btnModeDown.ys);

	if (WorkMode > 1)
	{
		WorkMode--;
	}
	DisplayMode(WorkMode);
}

void ModeDownFree(void)
{
	dwDisButton(&btnModeDown_O, 1, btnModeDown_O.xs, btnModeDown_O.ys);
}

/*Other button*/
void ExplainExitPres(void)
{
	BitAppCon.menuExit = 1;
	nextPage = FUNCTION_SELECT;
	INLINE_MUSIC_BUTTON();
}

void ExplainNextPres(void)
{
	if (++ExplainNum <= 3)
	{
		INLINE_MUSIC_BUTTON();
	}
	else
	{
		ExplainNum = 3;
	}
}

void ExplainNextFree(void)
{
	if (ExplainNum <= 3)
	{
		dwDisPicWithL(ExplainNum + PIC_EXPLAIN);
	}
	else
	{
		ExplainNum = 3;
	}
}

static void EnterPres(void)
{
	BitAppCon.menuExit = 1;
	nextPage = FUNCTION_EYE;
	INLINE_MUSIC_BUTTON();
	//dwDisButton(&btnEnter, 0, btnEnter.xs, btnEnter.ys);
	//dwSetBL(0x40);	//change display light
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
				INLINE_MUSIC_STOP();
				WorkTime = 1800;
				dwDisButton(&btnStart_O, 1, btnStart_O.xs, btnStart_O.ys);
				dwDisButton(&btnPause, 1, btnPause.xs, btnPause.ys);
				BitAppCon.WorkSecFlag = 0;
				BitAppCon.WorkFlag = 0;
				Comm.onoff = RF_OFF;
				CommSendFlag = 1;
			}
			funDisTime(WorkTime);
		}
	}
}

//Power up 
void PageRestartAnimation(void)
{		
	dwDisPicNoL(0);
	BitAppCon.menuExit = 0;
	dwCancelKey();
	dwListenKey(EnterPres, 0, &btnEnter);

	while (!BitAppCon.menuExit)
	{
		dwHandler();
	}
	
	dwWaitRelease();
	dwHandler();
}

void PageLanguage(void)
{
	BitAppCon.menuExit = 0;
	dwDisPicNoL(PIC_LANGUAGE);

	//display version
	dwDisChar(DW_SIZE_12, 2, 585, 'V');
	dwDisChar(DW_SIZE_12, 8, 585, '2');
	dwDisChar(DW_SIZE_12, 14, 585, '.');
	dwDisChar(DW_SIZE_12, 20, 585, '0');

	dwCancelKey();
	dwListenKey(menuChinsePres, 0, &btnChinse);
	dwListenKey(menuEnglishPres, 0, &btnEnglish);
	dwListenKey(menuKoreanPres, 0, &btnKorean);
	while (!BitAppCon.menuExit)
	{
		dwHandler();

		//UART1 time sends datas to main board, avoids data send fail
		if (BitAppCon.ms200)
		{
			BitAppCon.ms200 = 0;
			CommSendFlag = 1;
			MainBoardSend();
		}
	}
	dwWaitRelease();
	dwHandler();
}

void PageMenu(void)
{
	BitAppCon.menuExit = 0;

	dwDisPicWithL(PIC_MENUS);
	dwCancelKey();
	dwListenKey(menuEyeRFPres, 0, &btnEyeRF);
	dwListenKey(menuFaceRFPres, 0, &btnFaceRF);
	dwListenKey(menuBodyRFPres, 0, &btnBodyRF);
	dwListenKey(menuO2Pres, 0, &btnO2);
	dwListenKey(SetPres, 0, &btnSet);
	//	dwListenKey(menuExplainPres, 0, &btnExplain);

	while (!BitAppCon.menuExit)
	{
		dwHandler();

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
	dwHandler();
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

	dwDisPicWithL(PIC_EYE_RF);
	funDisTime(WorkTime);
	DisplayIntensity(WorkIntensity);
	dwDisButton(&btnPause, 1, btnPause.xs, btnPause.ys);

	dwCancelKey();
	// dwListenKey(menuFaceRFPres, 0, &btnFaceRF);
	// dwListenKey(menuBodyRFPres, 0, &btnBodyRF);
	// dwListenKey(menuEyeRFPres, 0, &btnEyeRF);
	// dwListenKey(menuO2Pres, 0, &btnO2);
	dwListenKey(StartPres, 0, &btnStart);
	dwListenKey(PausePres, PauseFree, &btnPause);
	dwListenKey(BackPres, BackFree, &btnBack);
	dwListenKey(TimeUpPres, TimeUpFree, &btnTimeUp);
	dwListenKey(TimeDownPres, TimeDownFree, &btnTimeDown);
	dwListenKey(IntensityUpPres, IntensityUpFree, &btnIntensityUp);
	dwListenKey(IntensityDownPres, IntensityDownFree, &btnIntensityDown);

	while (!BitAppCon.menuExit)
	{
		dwHandler();

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
				INLINE_MUSIC_ERROR();
				dwDisButton(&btnStart_O, 1, btnStart_O.xs, btnStart_O.ys);
				Comm.onoff = RF_OFF;
				BitAppCon.WorkFlag = 0;
				BitAppCon.WorkSecFlag = 0;
				CommSendFlag = 1;
			}
			else if((buff1[0] == 0xA0)&&BitAppCon.WorkFlag) //PRESS
			{
				BitAppCon.WorkSecFlag = 1;
				INLINE_MUSIC_BUTTON();
			}
			else if((buff1[0] == 0xA1)&&BitAppCon.WorkFlag) //RELEASE
			{
				if(BitAppCon.WorkSecFlag)
				{
					BitAppCon.WorkSecFlag = 0;
					INLINE_MUSIC_BUTTON();
				}	
			}
		}
	}
	dwWaitRelease();
	dwHandler();
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

	dwDisPicWithL(PIC_FACE_RF);
	funDisTime(WorkTime);
	DisplayIntensity(WorkIntensity);
	dwDisButton(&btnPause, 1, btnPause.xs, btnPause.ys);

	dwCancelKey();
	// dwListenKey(menuFaceRFPres, 0, &btnFaceRF);
	// dwListenKey(menuBodyRFPres, 0, &btnBodyRF);
	// dwListenKey(menuEyeRFPres, 0, &btnEyeRF);
	// dwListenKey(menuO2Pres, 0, &btnO2);
	dwListenKey(StartPres, 0, &btnStart);
	dwListenKey(PausePres, PauseFree, &btnPause);
	dwListenKey(BackPres, BackFree, &btnBack);
	dwListenKey(TimeUpPres, TimeUpFree, &btnTimeUp);
	dwListenKey(TimeDownPres, TimeDownFree, &btnTimeDown);
	dwListenKey(IntensityUpPres, IntensityUpFree, &btnIntensityUp);
	dwListenKey(IntensityDownPres, IntensityDownFree, &btnIntensityDown);

	while (!BitAppCon.menuExit)
	{
		dwHandler();

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
				INLINE_MUSIC_ERROR();
				dwDisButton(&btnStart_O, 1, btnStart_O.xs, btnStart_O.ys);
				Comm.onoff = RF_OFF;
				BitAppCon.WorkFlag = 0;
				BitAppCon.WorkSecFlag = 0;
				CommSendFlag = 1;
			}
			else if((buff1[0] == 0xA0)&&BitAppCon.WorkFlag) //PRESS
			{
				BitAppCon.WorkSecFlag = 1;
				INLINE_MUSIC_BUTTON();
			}
			else if((buff1[0] == 0xA1)&&BitAppCon.WorkFlag) //RELEASE
			{
				if(BitAppCon.WorkSecFlag)
				{
					BitAppCon.WorkSecFlag = 0;
					INLINE_MUSIC_BUTTON();
				}	
			}
		}
	}
	dwWaitRelease();
	dwHandler();
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

	dwDisPicWithL(PIC_BODY_RF);
	funDisTime(WorkTime);
	DisplayIntensity(WorkIntensity);
	dwDisButton(&btnPause, 1, btnPause.xs, btnPause.ys);

	dwCancelKey();
	// dwListenKey(menuFaceRFPres, 0, &btnFaceRF);
	// dwListenKey(menuBodyRFPres, 0, &btnBodyRF);
	// dwListenKey(menuEyeRFPres, 0, &btnEyeRF);
	// dwListenKey(menuO2Pres, 0, &btnO2);
	dwListenKey(StartPres, 0, &btnStart);
	dwListenKey(PausePres, PauseFree, &btnPause);
	dwListenKey(BackPres, BackFree, &btnBack);
	dwListenKey(TimeUpPres, TimeUpFree, &btnTimeUp);
	dwListenKey(TimeDownPres, TimeDownFree, &btnTimeDown);
	dwListenKey(IntensityUpPres, IntensityUpFree, &btnIntensityUp);
	dwListenKey(IntensityDownPres, IntensityDownFree, &btnIntensityDown);
	
	while (!BitAppCon.menuExit)
	{
		dwHandler();

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
				INLINE_MUSIC_ERROR();
				dwDisButton(&btnStart_O, 1, btnStart_O.xs, btnStart_O.ys);
				Comm.onoff = RF_OFF;
				BitAppCon.WorkFlag = 0;
				BitAppCon.WorkSecFlag = 0;
				CommSendFlag = 1;
			}
			else if((buff1[0] == 0xA0)&&BitAppCon.WorkFlag) //PRESS
			{
				BitAppCon.WorkSecFlag = 1;
				INLINE_MUSIC_BUTTON();
			}
			else if((buff1[0] == 0xA1)&&BitAppCon.WorkFlag) //RELEASE
			{
				if(BitAppCon.WorkSecFlag)
				{
					BitAppCon.WorkSecFlag = 0;
					INLINE_MUSIC_BUTTON();
				}				
			}
		}
	}
	dwWaitRelease();
	dwHandler();
}

//Temperature Process
const u16 TemperatureTable[] = {0, 2700, 2800, 2900, 3000,
								3100, 3300, 3500, 3600};
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
				//COOL_ON_PIN = 0;
				BACK1_PIN = 0;
				INLINE_MUSIC_ERROR();
			}			
		}
	}
	else
	{
		i = 0;
		NtcErrorFlag = 0;
		if(IceTemperature<=TemperatureTable[WorkIntensity]-16)
		{
			//COOL_ON_PIN = 1;
			BACK1_PIN = 1;
		}
		if(IceTemperature>=TemperatureTable[WorkIntensity])
		{
			//COOL_ON_PIN = 0;
			BACK1_PIN = 0;
		}
	}
}

void PageO2(void)
{
	WorkTime = 1800;
	WorkIntensity = 1;
	WorkMode = 1;
	BitAppCon.menuExit = 0;

	dwDisPicWithL(PIC_O2);
	funDisTime(WorkTime);
	DisplayIntensity(WorkIntensity);
	DisplayMode(WorkMode);
	dwDisButton(&btnPause, 1, btnPause.xs, btnPause.ys);

	dwCancelKey();
	// dwListenKey(menuFaceRFPres, 0, &btnFaceRF);
	// dwListenKey(menuBodyRFPres, 0, &btnBodyRF);
	// dwListenKey(menuEyeRFPres, 0, &btnEyeRF);
	// dwListenKey(menuO2Pres, 0, &btnO2);
	dwListenKey(StartPres, 0, &btnStart);
	dwListenKey(PausePres, PauseFree, &btnPause);
	dwListenKey(BackPres, BackFree, &btnBack);
	dwListenKey(TimeUpPres, TimeUpFree, &btnTimeUp_O2);
	dwListenKey(TimeDownPres, TimeDownFree, &btnTimeDown_O2);
	dwListenKey(IntensityUpPres, IntensityUpFree, &btnIntensityUp_O2);
	dwListenKey(IntensityDownPres, IntensityDownFree, &btnIntensityDown_O2);
	dwListenKey(ModeUpPres, ModeUpFree, &btnModeUp);
	dwListenKey(ModeDownPres, ModeDownFree, &btnModeDown);

	while (!BitAppCon.menuExit)
	{
		dwHandler();
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
			//COOL_ON_PIN = 0;	//close hate
			BACK1_PIN = 0;
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
	dwHandler();
}

//O2 PWM
const u16 O2ModPeriod[] = {0, 2000, 4000, 4000, 1000, 5000};
const u16 O2ModCompare[] = {0, 1000, 2000, 3000, 1000, 250};

void O2PWM(u8 i, u8 Work)
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
}

void PageCool(void)
{
	WorkTime = 1800;
	WorkIntensity = 1;
	BitAppCon.menuExit = 0;
	dwSetColor(DW_COL_RED, DW_COL_WHITE);
	dwDisPicWithL(PIC_COOL);
	funDisTime(WorkTime);
	dwDisNum(DW_SIZE_48, 581, 349, WorkIntensity / 10);
	dwDisNum(DW_SIZE_48, 581 + 24, 349, WorkIntensity % 10);
	dwDisButton(&btnPause, 1, btnPause.xs, btnPause.ys);
	dwCancelKey();
	dwListenKey(StartPres, StartFree, &btnStart);
	dwListenKey(PausePres, PauseFree, &btnPause);
	dwListenKey(BackPres, BackFree, &btnBack);
	dwListenKey(TimeUpPres, TimeUpFree, &btnTimeUp);
	dwListenKey(TimeDownPres, TimeDownFree, &btnTimeDown);
	dwListenKey(IntensityUpPres, IntensityUpFree, &btnIntensityUp);
	dwListenKey(IntensityDownPres, IntensityDownFree, &btnIntensityDown);

	while (!BitAppCon.menuExit)
	{
		dwHandler();
		WorkTimeDeal();
		if (BitAppCon.WorkFlag)
		{
			BACK1_PIN = 1;
			COOL_ON_PIN = 1;
			TIM_SetCompare3(TIM4, CoolIntensity[WorkIntensity]);
		}
		else
		{
			BACK1_PIN = 0;
			COOL_ON_PIN = 0;
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
	dwHandler();
}

//Explain Function
void PageExplain(void)
{
	ExplainNum = 0;
	BitAppCon.menuExit = 0;
	dwDisPicWithL(PIC_EXPLAIN);
	dwCancelKey();
	dwListenKey(ExplainExitPres, 0, &btnExplainExit_O);
	dwListenKey(ExplainNextPres, ExplainNextFree, &btnExplainNext_O);
	dwWaitRelease();
	while (!BitAppCon.menuExit)
	{
		dwHandler();
	}
	dwWaitRelease();
	dwHandler();
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
