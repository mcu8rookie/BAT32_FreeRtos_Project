#ifndef __USR_MODBUS_H__
#define __USR_MODBUS_H__


#define DEF_MB_SLAVE_ADDR   0x0A

/* ----------------------- Defines ------------------------------------------*/
#define REG_INPUT_START 1000
#define REG_INPUT_NREGS 4

/* ----------------------- Static variables ---------------------------------*/
extern uint16_t   usRegInputStart;
extern uint16_t   usRegInputBuf[REG_INPUT_NREGS];

extern uint8_t Usr_Mb_En;

extern uint8_t Usr_Mb_Timer_En;
extern uint8_t Usr_Mb_Timer_Cnt;

extern uint8_t Usr_Mb_Comm_Tx_En;
extern uint8_t Usr_Mb_Comm_Rx_En;


#if 1
#define REG_HOLDING_START 0
#define REG_HOLDING_NREGS 64

extern unsigned short   usRegHoldingStart;
extern unsigned short   usRegHoldingBuf[REG_HOLDING_NREGS];
#endif

uint8_t Usr_MbToE703_Addr(uint16_t mi,uint8_t *ei);

uint8_t Usr_E703RegToMb_Addr(uint8_t ei,uint16_t *mi);

uint8_t Usr_E703CMToMb_Addr(uint8_t ei,uint16_t *mi);



#endif


