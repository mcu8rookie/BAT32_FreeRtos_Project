#ifndef __USR_I2CA_SLAVE_H__
#define __USR_I2CA_SLAVE_H__

#if 1
//#define I2CA_SLAVE_ADDR_7B  (0x98>>1)
#define I2CA_SLAVE_ADDR_7B  (0x13)

#define I2CA_SLAVE_ADDR_WT  ((I2CA_SLAVE_ADDR_7B<<1)+0)
#define I2CA_SLAVE_ADDR_RD  ((I2CA_SLAVE_ADDR_7B<<1)+1)


#define I2CA_CMD_WT_DATA1   (0x01)
#define I2CA_CMD_WT_DATA2   (0x02)

#define I2CA_CMD_RD_DATA1   (0x11)
#define I2CA_CMD_RD_DATA2   (0x22)

#define DEF_I2CA_WT_FLG     (1)
#define DEF_I2CA_RD_FLG     (2)

#define DEF_I2CA_TX_MAX     (64)
#define DEF_I2CA_RX_MAX     (64)
#endif




extern uint8_t I2CA_WR_Flag;
extern uint8_t I2CA_Cmd_Flag;
extern uint16_t I2CA_Cmd_Code;

void Usr_I2CA_InitSetup(void);

void Usr_I2CA_MainLoop(void);

#endif



