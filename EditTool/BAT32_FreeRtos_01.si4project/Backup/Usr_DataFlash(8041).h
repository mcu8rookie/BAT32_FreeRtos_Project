#ifndef __USR_DATAFLASH_H__
#define __USR_DATAFLASH_H__

#include "Usr_Config.h"



#define DEF_DATAFLASH_EN            1

#define DEF_DF_PARAM_STARTADDR      (0x00500000)
#define DEF_DF_PARAM_OVERADDR       (0x00500100)
#define DEF_DF_DATA_LEN             (DEF_DF_PARAM_OVERADDR-DEF_DF_PARAM_STARTADDR)


#define DEF_TIME_SN_INDEX           4
#define DEF_TIME_SN_ADDRSTART       (DEF_DF_PARAM_STARTADDR+DEF_TIME_SN_INDEX)



extern uint32_t DF_StartAddress;
extern unsigned char DF_Rst;
extern unsigned char DF_UpdateInit_Flag;
extern unsigned char DF_UpdateReal_Flag;


extern uint8_t DF_Data[256];
extern uint8_t DF_DefaultData[256];



unsigned char Usr_DF_InitSetup(void);







#endif







