#ifndef __USR_I2C_H__
#define __USR_I2C_H__



#if 1
// E703,
#define DEF_E703_I2C_ADDR_7B    0x6C
#define DEF_E703_I2C_ADDR_WT    0xD8
#define DEF_E703_I2C_ADDR_RD    0xD9

#define DEF_HDC3020_I2C_ADD_7B  0x44
#define DEF_HDC3020_I2C_ADD_WT  0x88
#define DEF_HDC3020_I2C_ADD_RD  0x89
#endif





extern unsigned char   i2c_cmdbuf[1];
extern unsigned char   i2c_wtbuf[32];
extern unsigned char   i2c_rdbuf[32];

extern unsigned char   i2c20_cmdbuf[1];
extern unsigned char   i2c20_wtbuf[32];
extern unsigned char   i2c20_rdbuf[32];

extern unsigned char   i2c00_cmdbuf[1];
extern unsigned char   i2c00_wtbuf[32];
extern unsigned char   i2c00_rdbuf[32];

extern unsigned char   i2c01_cmdbuf[1];
extern unsigned char   i2c01_wtbuf[32];
extern unsigned char   i2c01_rdbuf[32];




unsigned char Usr_I2C_InitSetup(void);

unsigned char Usr_I2C_MainLoop(void);

unsigned char Usr_I2C_AccessCmdData(unsigned char *cmdbuf,unsigned char cmdlen,unsigned char *rxbuff,unsigned char rxlen);

unsigned char Usr_Read_ChipVersion(void);



#endif


