#ifndef __USR_I2CA_SLAVE_C__
#define __USR_I2CA_SLAVE_C__


#include <stdint.h>

#include "userdefine.h"
#include "BAT32A237.h"
#include "iica.h"

#include "Usr_I2CA_Slave.h"

#if 0
//#define I2CA_SLAVE_ADDR_7B  (0x98>>1)
#define I2CA_SLAVE_ADDR_7B  (0x13)

#define I2CA_SLAVE_ADDR_WT  ((I2CA_SLAVE_ADDR_7B>>1)+0)
#define I2CA_SLAVE_ADDR_RD  ((I2CA_SLAVE_ADDR_7B>>1)+1)


#define I2CA_CMD_WT_DATA1   (0x01)
#define I2CA_CMD_WT_DATA2   (0x02)

#define I2CA_CMD_RD_DATA1   (0x11)
#define I2CA_CMD_RD_DATA2   (0x22)

#define DEF_I2CA_WT_FLG     (1)
#define DEF_I2CA_RD_FLG     (2)

#define DEF_I2CA_TX_MAX     (64)
#define DEF_I2CA_RX_MAX     (64)
#endif

uint8_t I2CA_WR_Flag;
uint8_t I2CA_Cmd_Flag;
uint16_t I2CA_Cmd_Code;

uint8_t I2CA_RX_Buff[DEF_I2CA_RX_MAX];
uint8_t I2CA_TX_Buff[DEF_I2CA_TX_MAX];


void Usr_I2CA_InitSetup(void)
{
    IICA0_Init();
    
    //IICA->SVA0 = I2CA_SLAVE_ADDR_WT;
    
    #if 0
    //void IICA0_SlaveSend(uint8_t adr, uint8_t * const tx_buf, uint16_t tx_num)
    {
    g_iica0_tx_cnt = tx_num;
    gp_iica0_tx_address = tx_buf;
    g_iica0_tx_end = 0;
    g_iica0_slave_status_flag = 0U;
    IICA->SVA0 = adr; /* slave address */
    }
    
    //void IICA0_SlaveReceive(uint8_t adr, uint8_t * const rx_buf, uint16_t rx_num)
    {
    g_iica0_rx_len = rx_num;
    g_iica0_rx_cnt = 0U;
    gp_iica0_rx_address = rx_buf;
    g_iica0_rx_end = 0;
    g_iica0_slave_status_flag  = 0U;
    IICA->SVA0 = adr; /* slave address */
    }
    #endif
    
    g_iica0_master_status_flag = 0; /* iica0 master flag */
    
    g_iica0_slave_status_flag = 0;  /* iica0 slave flag */
    
    gp_iica0_rx_address = I2CA_RX_Buff;        /* iica0 receive buffer address */
    g_iica0_rx_len = 0;             /* iica0 receive data length */
    g_iica0_rx_cnt = 0;             /* iica0 receive data count */
    g_iica0_rx_end = 0;             /* iica0 receive data end */
    
    gp_iica0_tx_address = I2CA_TX_Buff;        /* iica0 send buffer address */
    g_iica0_tx_cnt = 0;             /* iica0 send data count */
    g_iica0_tx_end = 0;             /* iica0 send data end */
    
    I2CA_WR_Flag = 0;
    I2CA_Cmd_Flag = 0;
    I2CA_Cmd_Code = 0;
}

void Usr_I2CA_MainLoop(void)
{
    if(I2CA_WR_Flag == 1)
    {   // Write;
        
        I2CA_WR_Flag = 3;
    }
    else if(I2CA_WR_Flag == 2)
    {   // Read;
        
        I2CA_WR_Flag = 0;
    }
    else
    {
        
    }
    
    #if 0
    IICA0_SlaveReceive(I2CA_SLAVE_ADDR_WT, I2CA_RX_Buff, sizeof(I2CA_RX_Buff));
    IICA0_SlaveSend(I2CA_SLAVE_ADDR_WT, I2CA_TX_Buff, sizeof(I2CA_TX_Buff));
    //IICA0_Set_Wakeup(); /* Entry DeepSleep and waiting wakeup */
    while(g_iica0_rx_end == 0);
    while(g_iica0_tx_end == 0);
    #endif
    
}

#endif



