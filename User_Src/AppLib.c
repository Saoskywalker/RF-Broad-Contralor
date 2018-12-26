#include "AppLib.h"

_BitAppCon BitAppCon = {0, 0, 0, 0, 0, 0, 0, 0};
u8 nextPage = 0;
u8 requestPage = 0;
u16 CoolIntensity[] = {0, 1700, 1800, 1900, 2000, 2175, 2275, 2375, 2475, 2550, 2625};
u8 ExplainNum = 0;

//Botton press effect
const Button btnChinse = {PIC_LANGUAGE_P, 181, 223, 343, 325};
const Button btnEnglish = {PIC_LANGUAGE_P, 455, 223, 620, 325};
const Button btnFaceRF = {PIC_MENUS_P, 444, 7, 543, 55};
const Button btnBodyRF = {PIC_MENUS_P, 565, 7, 664, 55};
const Button btnEyeRF = {PIC_MENUS_P, 320, 7, 420, 55};
const Button btnO2 = {PIC_MENUS_P, 689, 7, 788, 55};
const Button btnCOOL = {PIC_MENUS_P, 619, 469, 767, 571};
const Button btnExplain = {PIC_MENUS_P, 644, 6, 776, 63};
const Button btnStart = {PIC_MENUS_P, 696, 523, 754, 580};
const Button btnPause = {PIC_MENUS_P, 523, 511, 583, 568};
const Button btnBack = {PIC_MENUS_P, 17, 13, 60, 55};
const Button btnTimeUp = {PIC_MENUS_P, 116, 532, 159, 577};
const Button btnTimeDown = {PIC_MENUS_P, 290, 532, 334, 577};
const Button btnIntensityUp = {PIC_MENUS_P, 446, 438, 516, 504};
const Button btnIntensityDown = {PIC_MENUS_P, 619, 438, 689, 504};
const Button btnModeUp = {PIC_MENUS_P, 434, 534, 475, 576};
const Button btnModeDown = {PIC_MENUS_P, 610, 534, 651, 575};
//const Button btnIntensityUp_FaceRF    = {PIC_MENUS_P,  405,421,474,489};
//const Button btnIntensityDown_FaceRF    = {PIC_MENUS_P,  633,420,705,489};
//const Button btnIntensityUp_BodyRF    = {PIC_MENUS_P,  405,421,474,489};
//const Button btnIntensityDown_BodyRF    = {PIC_MENUS_P,  633,420,705,489};
//const Button btnIntensityUp_EyeRF    = {PIC_MENUS_P,  405,421,474,489};
//const Button btnIntensityDown_EyeRF    = {PIC_MENUS_P,  633,420,705,489};
const Button btnTimeUp_Cool = {PIC_FUN_BUT_P_Cool, 701, 277, 752, 328};
const Button btnTimeDown_Cool = {PIC_FUN_BUT_P_Cool, 462, 276, 513, 329};

//Botton original effect
const Button btnFaceRF_O = {PIC_MENUS, 444, 7, 543, 55};
const Button btnBodyRF_O = {PIC_MENUS, 565, 7, 664, 55};
const Button btnEyeRF_O = {PIC_MENUS, 320, 7, 420, 55};
const Button btnO2_O = {PIC_MENUS, 689, 7, 788, 55};
const Button btnStart_O = {PIC_MENUS, 696, 523, 754, 580};
const Button btnPause_O = {PIC_MENUS, 523, 511, 583, 568};
const Button btnBack_O = {PIC_MENUS, 17, 13, 60, 55};
const Button btnTimeUp_O = {PIC_MENUS, 116, 532, 159, 577};
const Button btnTimeDown_O = {PIC_MENUS, 290, 532, 334, 577};
//const Button btnIntensityUp_FaceRF_O    = {PIC_MENUS,  405,421,474,489};
//const Button btnIntensityDown_FaceRF_O    = {PIC_MENUS,  633,420,705,489};
//const Button btnIntensityUp_BodyRF_O    = {PIC_MENUS,  405,421,474,489};
//const Button btnIntensityDown_BodyRF_O    = {PIC_MENUS,  633,420,705,489};
//const Button btnIntensityUp_EyeRF_O    = {PIC_MENUS,  405,421,474,489};
//const Button btnIntensityDown_EyeRF_O    = {PIC_MENUS,  633,420,705,489};
const Button btnIntensityUp_O = {PIC_MENUS, 446, 438, 516, 504};
const Button btnIntensityDown_O = {PIC_MENUS, 619, 438, 689, 504};
const Button btnModeUp_O = {PIC_MENUS, 434, 534, 475, 576};
const Button btnModeDown_O = {PIC_MENUS, 610, 534, 651, 575};
const Button btnTimeUp_O_Cool = {PIC_FUN_BUT_Cool, 701, 277, 752, 328};
const Button btnTimeDown_O_Cool = {PIC_FUN_BUT_Cool, 462, 276, 513, 329};
const Button btnExplainExit_O = {PIC_EXPLAIN, 24, 17, 96, 82};
const Button btnExplainNext_O = {PIC_EXPLAIN, 358, 510, 444, 589};

u8 CommSendFlag = 0;									  //Send Main Board Buffer or not
_Comm Comm = {FRAME_HEAD, RF_FACE, 1, RF_OFF, FRAME_END}; //Send Main Board Buffer
u16 WorkTime = 0;
u8 WorkIntensity = 0;

/*language select*/
void menuChinsePres(void)
{
	u16 i = 0;

	BitAppCon.menuExit = 1;
	nextPage = FUNCTION_EYE;
	dwPlayMusic(MSC_BUTTON, 1);
	dwDisButton(&btnChinse, 0, btnChinse.xs, btnChinse.ys);
	dwSetLanguage(LANGUAGE_CHINESE);
	STMFLASH_Write(FLASH_SAVE_ADDR, &i, 1);		//Write language config
}

void menuEnglishPres(void)
{
	u16 i = 123;

	BitAppCon.menuExit = 1;
	nextPage = FUNCTION_EYE;
	dwPlayMusic(MSC_BUTTON, 1);
	dwDisButton(&btnEnglish, 0, btnEnglish.xs, btnEnglish.ys);
	dwSetLanguage(LANGUAGE_ENGLISH);
	STMFLASH_Write(FLASH_SAVE_ADDR, &i, 1);		//Write language config
}

/*Menu select*/
void menuEyeRFPres(void)
{
	nextPage = FUNCTION_EYE;
	dwPlayMusic(MSC_BUTTON, 1);
	dwDisButton(&btnEyeRF, 1, btnEyeRF.xs, btnEyeRF.ys);
}

void menuFaceRFPres(void)
{
	nextPage = FUNCTION_FACE;
	dwPlayMusic(MSC_BUTTON, 1);
	dwDisButton(&btnFaceRF, 1, btnFaceRF.xs, btnFaceRF.ys);
}

void menuBodyRFPres(void)
{
	nextPage = FUNCTION_BODY;
	dwPlayMusic(MSC_BUTTON, 1);
	dwDisButton(&btnBodyRF, 1, btnBodyRF.xs, btnBodyRF.ys);
}

void menuO2Pres(void)
{
	nextPage = FUNCTION_O2;
	dwPlayMusic(MSC_BUTTON, 1);
	dwDisButton(&btnO2, 1, btnO2.xs, btnO2.ys);
}

void menuCoolPres(void)
{
	BitAppCon.menuExit = 1;
	nextPage = FUNCTION_COOL;
	dwPlayMusic(MSC_BUTTON, 1);
	dwDisButton(&btnCOOL, 1, btnCOOL.xs, btnCOOL.ys);
}

void menuExplainPres(void)
{
	BitAppCon.menuExit = 1;
	nextPage = FUNCTION_EXPLAIN;
	dwPlayMusic(MSC_BUTTON, 1);
	dwDisButton(&btnExplain, 1, btnExplain.xs, btnExplain.ys);
}

/*Start button*/
void StartPres(void)
{
	dwPlayMusic(MSC_BUTTON, 1);
	switch (nextPage)
	{
	case FUNCTION_O2:
	{
		if(BitAppCon.WorkFlag)
		{
			BitAppCon.WorkFlag = 0;
			dwDisButton(&btnStart_O, 1, btnStart_O.xs, btnStart_O.ys);
		}
		else
		{
			BitAppCon.WorkFlag = 1;
			dwDisButton(&btnStart, 1, btnStart.xs, btnStart.ys);
			if (WorkTime == 0)
			{
				WorkTime = 1800;
			}
		}
		break;
	}
	default:
	{
		if(BitAppCon.WorkFlag)
		{
			Comm.onoff = RF_OFF;
			BitAppCon.WorkFlag = 0;
			CommSendFlag = 1;
			dwDisButton(&btnStart_O, 1, btnStart_O.xs, btnStart_O.ys);
		}
		else
		{
			CommSendFlag = 1;
			Comm.onoff = RF_ON;
			BitAppCon.WorkFlag = 1;
			dwDisButton(&btnStart, 1, btnStart.xs, btnStart.ys);
			if (WorkTime == 0)
			{
				WorkTime = 1800;
			}
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
	dwPlayMusic(MSC_BUTTON, 1);
	dwDisButton(&btnStart_O, 1, btnStart_O.xs, btnStart_O.ys);
	dwDisButton(&btnPause, 1, btnPause.xs, btnPause.ys);
}

void PauseFree(void)
{
	//	Comm.onoff = RF_OFF;
	BitAppCon.WorkFlag = 0;
	//	CommSendFlag = 1;
}

/*Back button*/
void BackPres(void)
{
	dwPlayMusic(MSC_BUTTON, 1);
	dwDisButton(&btnBack, 1, btnBack.xs, btnBack.ys);
}

void BackFree(void)
{
	nextPage = FUNCTION_LANGUAGE;
}

/*Time button*/
void TimeUpPres(void)
{
	dwPlayMusic(MSC_BUTTON, 1);
	dwDisButton(&btnTimeUp, 1, btnTimeUp.xs, btnTimeUp.ys);
	if (WorkTime < 3600)
	{
		WorkTime += 60;
	}
	funDisTime(WorkTime);
}

void TimeUpFree(void)
{
	dwDisButton(&btnTimeUp_O, 1, btnTimeUp_O.xs, btnTimeUp_O.ys);
}

void TimeDownPres(void)
{
	dwPlayMusic(MSC_BUTTON, 1);
	dwDisButton(&btnTimeDown, 1, btnTimeDown.xs, btnTimeDown.ys);
	if (WorkTime > 60)
	{
		WorkTime -= 60;
	}
	funDisTime(WorkTime);
}

void TimeDownFree(void)
{
	dwDisButton(&btnTimeDown_O, 1, btnTimeDown_O.xs, btnTimeDown_O.ys);
}

/*Intensity button*/
void IntensityUpPres(void)
{
	dwPlayMusic(MSC_BUTTON, 1);
	dwDisButton(&btnIntensityUp, 1, btnIntensityUp.xs, btnIntensityUp.ys);

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
}

void IntensityUpFree(void)
{
	dwDisButton(&btnIntensityUp_O, 1, btnIntensityUp_O.xs, btnIntensityUp_O.ys);
}

void IntensityDownPres(void)
{
	dwPlayMusic(MSC_BUTTON, 1);
	dwDisButton(&btnIntensityDown, 1, btnIntensityDown.xs, btnIntensityDown.ys);
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
}

void IntensityDownFree(void)
{
	dwDisButton(&btnIntensityDown_O, 1, btnIntensityDown_O.xs, btnIntensityDown_O.ys);
}

void IntensityUpPres_O2(void)
{
	dwPlayMusic(MSC_BUTTON, 1);
	dwDisButton(&btnIntensityUp, 1, btnIntensityUp.xs, btnIntensityUp.ys);
	if (WorkIntensity < 4)
	{
		WorkIntensity++;
		//		Comm.intensity = WorkIntensity;
		//		CommSendFlag = 1;
	}
	dwDisChar(DW_SIZE_48, 581 + 12, 349, WorkIntensity + '@');
	//	dwDisNum(DW_SIZE_48, 581,    349,WorkIntensity/10);
	//	dwDisNum(DW_SIZE_48, 581+24, 349,WorkIntensity%10);
}

void IntensityUpFree_O2(void)
{
	dwDisButton(&btnIntensityUp_O, 1, btnIntensityUp_O.xs, btnIntensityUp_O.ys);
}

void IntensityDownPres_O2(void)
{
	dwPlayMusic(MSC_BUTTON, 1);
	dwDisButton(&btnIntensityDown, 1, btnIntensityDown.xs, btnIntensityDown.ys);
	if (WorkIntensity > 1)
	{
		WorkIntensity--;
		//		Comm.intensity = WorkIntensity;
		//		CommSendFlag = 1;
	}
	dwDisChar(DW_SIZE_48, 581 + 12, 349, WorkIntensity + '@');
	//	dwDisNum(DW_SIZE_48, 581,    349,WorkIntensity/10);
	//	dwDisNum(DW_SIZE_48, 581+24, 349,WorkIntensity%10);
}

void IntensityDownFree_O2(void)
{
	dwDisButton(&btnIntensityDown_O, 1, btnIntensityDown_O.xs, btnIntensityDown_O.ys);
}

void IntensityUpPres(void)
{
	dwPlayMusic(MSC_BUTTON, 1);
	dwDisButton(&btnIntensityUp, 1, btnIntensityUp.xs, btnIntensityUp.ys);
	if (WorkIntensity < 10)
	{
		WorkIntensity++;
		//		Comm.intensity = WorkIntensity;
		//		CommSendFlag = 1;
	}
	dwDisNum(DW_SIZE_48, 581, 349, WorkIntensity / 10);
	dwDisNum(DW_SIZE_48, 581 + 24, 349, WorkIntensity % 10);
}

void IntensityUpFree(void)
{
	dwDisButton(&btnIntensityUp_O, 1, btnIntensityUp_O.xs, btnIntensityUp_O.ys);
}

void IntensityDownPres(void)
{
	dwPlayMusic(MSC_BUTTON, 1);
	dwDisButton(&btnIntensityDown, 1, btnIntensityDown.xs, btnIntensityDown.ys);
	if (WorkIntensity > 1)
	{
		WorkIntensity--;
		//		Comm.intensity = WorkIntensity;
		//		CommSendFlag = 1;
	}
	dwDisNum(DW_SIZE_48, 581, 349, WorkIntensity / 10);
	dwDisNum(DW_SIZE_48, 581 + 24, 349, WorkIntensity % 10);
}

void IntensityDownFree(void)
{
	dwDisButton(&btnIntensityDown_O, 1, btnIntensityDown_O.xs, btnIntensityDown_O.ys);
}

/*Other button*/
void ExplainExitPres(void)
{
	BitAppCon.menuExit = 1;
	nextPage = FUNCTION_SELECT;
	dwPlayMusic(MSC_BUTTON, 1);
}

void ExplainNextPres(void)
{
	if (++ExplainNum <= 3)
	{
		dwPlayMusic(MSC_BUTTON, 1);
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

void PageLanguage(void)
{
	BitAppCon.menuExit = 0;
	dwDisPicNoL(PIC_LANGUAGE);

	dwCancelKey();
	dwListenKey(menuChinsePres, 0, &btnChinse);
	dwListenKey(menuEnglishPres, 0, &btnEnglish);
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
	dwListenKey(menuFaceRFPres, 0, &btnFaceRF);
	dwListenKey(menuBodyRFPres, 0, &btnBodyRF);
	dwListenKey(menuO2Pres, 0, &btnO2);
	dwListenKey(menuCoolPres, 0, &btnCOOL);
	//	dwListenKey(menuExplainPres, 0, &btnExplain);
	dwWaitRelease();
	while (!BitAppCon.menuExit)
	{
		dwHandler();

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

void WorkTimeDeal(void)
{
	if (BitAppCon.WorkFlag)
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
				BitAppCon.WorkFlag = 0;
				Comm.onoff = RF_OFF;
				CommSendFlag = 1;
			}
			funDisTime(WorkTime);
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

	funDisTime(WorkTime);
	DisplayIntensity(WorkIntensity);
	dwDisPicWithL(PIC_EYE_RF);

	dwCancelKey();
	dwListenKey(menuFaceRFPres, 0, &btnFaceRF);
	dwListenKey(menuBodyRFPres, 0, &btnBodyRF);
	dwListenKey(menuEyeRFPres, 0, &btnEyeRF);
	dwListenKey(menuO2Pres, 0, &btnO2);
	dwListenKey(StartPres, 0, &btnStart);
	//dwListenKey(PausePres, PauseFree, &btnPause);
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
				CommSendFlag = 1;
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
	dwSetColor(DW_COL_RED, DW_COL_WHITE);
	funDisTime(WorkTime);
	DisplayIntensity(WorkIntensity);
	dwDisButton(&btnFaceRF, 1, btnFaceRF.xs, btnFaceRF.ys);
	dwDisButton(&btnPause, 1, btnPause.xs, btnPause.ys);
	dwCancelKey();
	dwListenKey(menuFaceRFPres, 0, &btnFaceRF);
	dwListenKey(menuBodyRFPres, 0, &btnBodyRF);
	dwListenKey(menuEyeRFPres, 0, &btnEyeRF);
	dwListenKey(StartPres_FaceRF, StartFree_FaceRF, &btnStart);
	dwListenKey(PausePres_FaceRF, PauseFree_FaceRF, &btnPause);
	dwListenKey(BackPres_FaceRF, BackFree_FaceRF, &btnBack);
	dwListenKey(TimeUpPres, TimeUpFree, &btnTimeUp);
	dwListenKey(TimeDownPres, TimeDownFree, &btnTimeDown);
	dwListenKey(IntensityUpPres_FaceRF, IntensityUpFree_FaceRF, &btnIntensityUp);
	dwListenKey(IntensityDownPres_FaceRF, IntensityDownFree_FaceRF, &btnIntensityDown);
	dwWaitRelease();
	while (!BitAppCon.menuExit)
	{
		dwHandler();

		if (nextPage != FUNCTION_FACE)
		{
			CommSendFlag = 1;
			BitAppCon.menuExit = 1;
			Comm.onoff = RF_OFF;
			BitAppCon.WorkFlag = 0;
			dwDisButton(&btnStart_O, 1, btnStart_O.xs, btnStart_O.ys);
			dwDisButton(&btnFaceRF_O, 1, btnFaceRF_O.xs, btnFaceRF_O.ys);
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
				CommSendFlag = 1;
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
	dwSetColor(DW_COL_RED, DW_COL_WHITE);
	funDisTime(WorkTime);
	DisplayIntensity(WorkIntensity);
	dwDisButton(&btnBodyRF, 1, btnBodyRF.xs, btnBodyRF.ys);
	dwDisButton(&btnPause, 1, btnPause.xs, btnPause.ys);
	dwCancelKey();
	dwListenKey(menuFaceRFPres, 0, &btnFaceRF);
	dwListenKey(menuBodyRFPres, 0, &btnBodyRF);
	dwListenKey(menuEyeRFPres, 0, &btnEyeRF);
	dwListenKey(StartPres_BodyRF, StartFree_BodyRF, &btnStart);
	dwListenKey(PausePres_BodyRF, PauseFree_BodyRF, &btnPause);
	dwListenKey(BackPres_BodyRF, BackFree_BodyRF, &btnBack);
	dwListenKey(TimeUpPres, TimeUpFree, &btnTimeUp);
	dwListenKey(TimeDownPres, TimeDownFree, &btnTimeDown);
	dwListenKey(IntensityUpPres_BodyRF, IntensityUpFree_BodyRF, &btnIntensityUp);
	dwListenKey(IntensityDownPres_BodyRF, IntensityDownFree_BodyRF, &btnIntensityDown);
	dwWaitRelease();
	while (!BitAppCon.menuExit)
	{
		dwHandler();

		if (nextPage != FUNCTION_BODY)
		{
			CommSendFlag = 1;
			BitAppCon.menuExit = 1;
			Comm.onoff = RF_OFF;
			BitAppCon.WorkFlag = 0;
			dwDisButton(&btnStart_O, 1, btnStart_O.xs, btnStart_O.ys);
			dwDisButton(&btnBodyRF_O, 1, btnBodyRF_O.xs, btnBodyRF_O.ys);
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
				CommSendFlag = 1;
			}
		}
	}
	dwWaitRelease();
	dwHandler();
}

void PageO2(void)
{
	WorkTime = 1800;
	WorkIntensity = 1;
	BitAppCon.menuExit = 0;
	dwSetColor(DW_COL_RED, DW_COL_WHITE);
	dwDisPicWithL(PIC_O2);
	funDisTime(WorkTime);
	dwDisChar(DW_SIZE_48, 581 + 12, 349, WorkIntensity + '@');
	//	dwDisNum(DW_SIZE_48, 581,    349,WorkIntensity/10);
	//	dwDisNum(DW_SIZE_48, 581+24, 349,WorkIntensity%10);
	dwDisButton(&btnPause, 1, btnPause.xs, btnPause.ys);
	dwCancelKey();
	dwListenKey(StartPres, StartFree, &btnStart);
	dwListenKey(PausePres, PauseFree, &btnPause);
	dwListenKey(BackPres, BackFree, &btnBack);
	dwListenKey(TimeUpPres, TimeUpFree, &btnTimeUp);
	dwListenKey(TimeDownPres, TimeDownFree, &btnTimeDown);
	dwListenKey(IntensityUpPres_O2, IntensityUpFree_O2, &btnIntensityUp);
	dwListenKey(IntensityDownPres_O2, IntensityDownFree_O2, &btnIntensityDown);
	dwWaitRelease();
	while (!BitAppCon.menuExit)
	{
		dwHandler();
		WorkTimeDeal();
		if (BitAppCon.WorkFlag)
		{
			LED_PIN = 1;
			PUMP_PIN = 1;
		}
		else
		{
			LED_PIN = 0;
			Valve_PIN = 0;
			PUMP_PIN = 0;
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
	dwWaitRelease();
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
