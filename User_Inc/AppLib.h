#ifndef _APP_LIB_H
#define _APP_LIB_H

#include "UserBaseLib.h"
#include "dwDriver.h"
#include "usart.h"
#include "adc.h"
#include "stmflash.h"

//Flash function
#define FLASH_SAVE_ADDR  0X0800F800 				//设置FLASH 保存地址(必须为偶数)

//Hardware define
#define SOUND_PIN PAout(4)
#define LED_PIN PAout(6)
#define COOL_ON_PIN PBout(4)
#define PUMP_PIN PBout(3)
#define BACK1_PIN PBout(1)
#define Valve_PIN PBout(0)

//Picture Code
#define PIC_LANGUAGE 6
#define PIC_LANGUAGE_P 5
#define PIC_MENUS 14
#define PIC_MENUS_P 17
#define PIC_EXPLAIN 13
#define PIC_FACE_RF 12
#define PIC_BODY_RF 13
#define PIC_EYE_RF 11
#define PIC_O2 14
#define PIC_COOL 6
#define PIC_FUN_BUT_P 9
#define PIC_FUN_BUT 10
#define PIC_FUN_BUT_P_Cool 12
#define PIC_FUN_BUT_Cool 5
#define PIC_INTENSITY 30

extern u8 nextPage;
extern u8 requestPage;
extern const Button btnChinse;
extern const Button btnEnglish;
extern u8 WorkIntensity, WorkMode;

//music code
#define	MSC_BUTTON  127
#define	MSC_START   2
#define	MSC_STOP    3
#define	MSC_ALERT   4
#define	MSC_ERROR   5

#define FUNCTION_EXPLAIN 0
#define FUNCTION_FACE 1
#define FUNCTION_BODY 2
#define FUNCTION_O2 3
#define FUNCTION_COOL 4
#define FUNCTION_SELECT 5
#define FUNCTION_LANGUAGE 6
#define FUNCTION_EYE 7

//lll
typedef struct
{
  unsigned char menuExit     : 1;
  unsigned char rx1Flag      : 1;
  unsigned char Flag1s       : 1;
  unsigned char WorkFlag     : 1;
  unsigned char ms200        : 1;
  unsigned char ms6       	 : 1;
  unsigned char ms7      	   : 1;
  unsigned char ms8       	 : 1;
}_BitAppCon;

extern _BitAppCon BitAppCon;

void PageLanguage(void);
void PageMenu(void);
void PageFaceRF(void);
void PageBodyRF(void);
void PageCool(void);
void PageO2(void);
void PageExplain(void);
void PageEyeRF(void);

//Main board Communicate
#define RF_OFF 0x00
#define RF_ON 0x01
#define RF_BODY 0x02
#define RF_FACE 0x01
#define FRAME_HEAD    0x55
#define FRAME_END     0xAA
//#define CMD_TYPE	  0xCE
//#define CMD_STATUS	  0xC0
//#define CMD_LED  	  0xC1
//#define CMD_COUNTER	  0xC2
//#define CMD_INC 	  0xC3
//#define CMD_CLERA	  0xC4

typedef struct
{
	u8 head;
	u8 channel;
	u8 intensity;
	u8 onoff;
	u8 end;
}_Comm;
extern _Comm Comm;

extern u8 buff1[5];
void commRx1Handler(u8 byte);
void O2PWM(u8 i, u8 Work);

/****BEE Module******/
extern u8 BeeMod, BeeTime;
void BeeFunction(void);
/* 
static __inline void dwPlayMusic(u8 id, u8 num)
{
	BeeMod = id;
	BeeTime = num;
}

static __inline void dwStopMusic(void)
{
	BeeTime = 0;
}
 */
//#define INLINE_MUSIC_CANNEL()	{BeeTime = 0;}
//#define INLINE_MUSIC_BUTTON() {BeeMod = 0; BeeTime = 1;}
//#define INLINE_MUSIC_START() {BeeMod = 1; BeeTime = 1;}
//#define INLINE_MUSIC_STOP() {BeeMod = 2; BeeTime = 3;}
//#define INLINE_MUSIC_ERROR() {BeeMod = 0; BeeTime = 7;}
//#define INLINE_MUSIC_SCR_ADJ() {BeeMod = 1; BeeTime = 2;}
//////////////////////////

/*****Display Intensity********/
static __inline void DisplayIntensity(u8 i)
{
	dwCutPic(PIC_INTENSITY+i, 448, 143, 687, 384, 448, 143);
	// dwDisNum(DW_SIZE_48, 528,    219,i/10);
	// dwDisNum(DW_SIZE_48, 528+24, 219,i%10);
}

/*****Display Mode********/
static __inline void DisplayMode(u8 i)
{
	dwDisChar(DW_SIZE_32, 537, 537, '@'+i);
}
///////////////////////////////

#endif
