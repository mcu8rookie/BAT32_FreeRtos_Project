#ifndef __USR_I2CSLAVE_PROC_H__
#define __USR_I2CSLAVE_PROC_H__

#include <stdint.h>

#define MD_RD_SN_CMDCODE1   0x3615
#define MD_RD_SN_CMDCODE2   0xEC05
#define MD_RD_SN_CMDLEN        18

extern uint8_t MD_SN[MD_RD_SN_CMDLEN];

void MD_SN_Update(void);


#define MD_RD_DATA_CMDCODE1   0xEC05
#define MD_RD_DATA_CMDLEN        18

extern uint8_t MD_DATA[MD_RD_SN_CMDLEN];

void MD_DATA_Update(void);


#endif



