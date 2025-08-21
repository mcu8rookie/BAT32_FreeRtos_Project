#ifndef __USR_ALSENSOR_H__
#define __USR_ALSENSOR_H__


//#include "Usr_Code.h"
#include <stdint.h>

#define ALSENSOR_STAGE_UNINIT   0
#define ALSENSOR_STAGE_KNOCK    1
#define ALSENSOR_STAGE_INIT     2
#define ALSENSOR_STAGE_WAIT1    3
#define ALSENSOR_STAGE_GETDATA  4
#define ALSENSOR_STAGE_PROC     5
#define ALSENSOR_STAGE_WAIT2    6
#define ALSENSOR_STAGE_STOP     7
#define ALSENSOR_STAGE_QUIT     8


extern int16_t TH_Sensor_Temperature_out;

extern uint16_t TH_Sensor_Humidity_out;


extern unsigned char TH_RdBuf[6];

extern volatile unsigned int TH_DelayMs;

extern unsigned char ALSensor_TH_Stage;
extern volatile unsigned int ALSensor_TH_HoleTime;
extern unsigned char ALSensor_TH_RepeatCnt;

extern unsigned int ALSensor_TH_VID;
extern unsigned int ALSensor_TH_PID;

extern unsigned int ALSensor_HDC2010_VID;
extern unsigned int ALSensor_HDC2010_PID;

extern int32_t th_sensor_tmp;

extern unsigned char Flag_TH_Err_Comm;
extern unsigned char Flag_TH_Err_TRange;
extern unsigned char Flag_TH_Err_HRange;

extern float ExtSens_Tmpr;
extern float ExtSens_RH;

extern int ExtSens_Prs;
extern double ExtSens_Tmpr2;

extern unsigned int ExtSens_RH0D1P_U16;

extern uint16_t ExtSens_Tmpr_Raw1;

extern uint16_t ExtSens_Tmpr_Raw;
extern unsigned int ExtSens_RH_Raw;

unsigned char ALSensor_TH_MainLoop(void);



extern uint16_t CPS122_Temperature_0D1C;
extern uint16_t PSensor_Pressure_10Pa;
extern int32_t TPSensor_Temporary;


#if(defined(SENSOR_PT_TYPE)&&(SENSOR_PT_TYPE == SENSOR_TYPE_CMP201))

extern unsigned char ALSensor_CMP201_Stage;

extern volatile unsigned int ALSensor_CMP201_HoleTime;

extern unsigned char Flag_CMP201_Err_Comm;
extern unsigned char Flag_CMP201_Err_TRange;
extern unsigned char Flag_CMP201_Err_PRange;


unsigned char ALSensor_CMP201_InitSetup(void);

unsigned char ALSensor_CMP201_MainLoop(void);


#endif

#endif



