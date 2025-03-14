#ifndef __USR_ALSENSOR_H__
#define __USR_ALSENSOR_H__


//#include "Usr_Code.h"

#define ALSENSOR_STAGE_UNINIT   0
#define ALSENSOR_STAGE_KNOCK    1
#define ALSENSOR_STAGE_INIT     2
#define ALSENSOR_STAGE_WAIT1    3
#define ALSENSOR_STAGE_GETDATA  4
#define ALSENSOR_STAGE_PROC     5
#define ALSENSOR_STAGE_WAIT2    6
#define ALSENSOR_STAGE_STOP     7
#define ALSENSOR_STAGE_QUIT     8


extern short TH_Sensor_Temperature_out;

extern unsigned short TH_Sensor_Humidity_out;


extern unsigned char TH_RdBuf[6];

extern volatile unsigned int TH_DelayMs;

extern unsigned char ALSensor_TH_Stage;
extern volatile unsigned int ALSensor_TH_HoleTime;
extern unsigned char ALSensor_TH_RepeatCnt;

extern unsigned int ALSensor_HDC2010_VID;
extern unsigned int ALSensor_HDC2010_PID;

extern long th_sensor_tmp;

extern bit Flag_TH_Err_Comm;
extern bit Flag_TH_Err_TRange;
extern bit Flag_TH_Err_HRange;


unsigned char ALSensor_TH_MainLoop(void);



extern unsigned int CPS122_Temperature_0D1C;
extern unsigned int PSensor_Pressure_10Pa;
extern long TPSensor_Temporary;


#if(defined(SENSOR_PT_TYPE)&&(SENSOR_PT_TYPE == SENSOR_TYPE_CMP201))

extern unsigned char ALSensor_CMP201_Stage;

extern volatile unsigned int ALSensor_CMP201_HoleTime;

extern bit Flag_CMP201_Err_Comm;
extern bit Flag_CMP201_Err_TRange;
extern bit Flag_CMP201_Err_PRange;


unsigned char ALSensor_CMP201_InitSetup(void);

unsigned char ALSensor_CMP201_MainLoop(void);


#endif

#endif



