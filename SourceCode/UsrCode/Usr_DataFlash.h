#ifndef __USR_DATAFLASH_H__
#define __USR_DATAFLASH_H__

#include "Usr_Config.h"



#define DEF_DATAFLASH_EN            1

#define DEF_DF_PARAM_STARTADDR      (0x00500000)
#define DEF_DF_PARAM_OVERADDR       (0x00500100)
#define DEF_DF_DATA_LEN             (DEF_DF_PARAM_OVERADDR-DEF_DF_PARAM_STARTADDR)


#define DEF_TIME_SN_INDEX           4       // 0x04
#define DEF_TIME_SN_ADDRSTART       (DEF_DF_PARAM_STARTADDR+DEF_TIME_SN_INDEX)

#define DEF_TRAWBASE_INDEX          10     // 0x0A
#define DEF_TRAWBASE_ADDRSTART      (DEF_DF_PARAM_STARTADDR+DEF_TIME_SN_INDEX)

#define DEF_TCOMP_P0_INDEX          12      // 0x0C
#define DEF_TCOMP_P0_ADDRSTART      (DEF_DF_PARAM_STARTADDR+DEF_TIME_SN_INDEX)

#define DEF_TCOMP_P1_INDEX          16      // 0x10
#define DEF_TCOMP_P1_ADDRSTART      (DEF_DF_PARAM_STARTADDR+DEF_TIME_SN_INDEX)

#define DEF_TCOMP_P2_INDEX          20      // 0x14
#define DEF_TCOMP_P2_ADDRSTART      (DEF_DF_PARAM_STARTADDR+DEF_TIME_SN_INDEX)

#define DEF_TCOMP_P3_INDEX          24      // 0x18
#define DEF_TCOMP_P3_ADDRSTART      (DEF_DF_PARAM_STARTADDR+DEF_TIME_SN_INDEX)



#define DEF_PREHEATTIME_INDEX       32
#define DEF_PREHEATTIME_ADDRSTART   (DEF_DF_PARAM_STARTADDR+DEF_PREHEATTIME_INDEX)

#define DEF_COOLTIME_INDEX          34
#define DEF_COOLTIME_ADDRSTART      (DEF_DF_PARAM_STARTADDR+DEF_COOLTIME_INDEX)

#define DEF_FILTERCNT_INDEX         36
#define DEF_FILTERCNT_ADDRSTART     (DEF_DF_PARAM_STARTADDR+DEF_FILTERCNT_INDEX)



extern uint32_t DF_StartAddress;
extern unsigned char DF_Rst;
extern unsigned char DF_UpdateInit_Flag;
extern unsigned char DF_UpdateReal_Flag;


extern uint8_t DF_Data[256];
extern uint8_t DF_DefaultData[256];



unsigned char Usr_DF_InitSetup(void);


void Usr_DFData_To_Variable(void);

void Usr_DFData_To_DataFlash(void);



#endif







