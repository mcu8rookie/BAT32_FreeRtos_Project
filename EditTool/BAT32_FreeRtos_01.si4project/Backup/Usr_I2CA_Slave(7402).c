#ifndef __USR_I2CA_SLAVE_C__
#define __USR_I2CA_SLAVE_C__


#include <stdint.h>

#include "userdefine.h"
#include "BAT32A237.h"
#include "iica.h"

#include "Usr_I2CA_Slave.h"

#if 0
#define I2CA_SLAVE_ADDR_7B  (0x55)
#define I2CA_SLAVE_ADDR_WT  ((I2CA_SLAVE_ADDR_7B>>1)+0)
#define I2CA_SLAVE_ADDR_RD  ((I2CA_SLAVE_ADDR_7B>>1)+1)


#define I2CA_CMD_WT_DATA1   (0x01)
#define I2CA_CMD_WT_DATA2   (0x02)

#define I2CA_CMD_RD_DATA1   (0x11)
#define I2CA_CMD_RD_DATA2   (0x22)

#define DEF_I2CA_WT_FLG     1
#define DEF_I2CA_RD_FLG     2
#endif

uint8_t I2CA_WR_Flag;
uint8_t I2CA_Cmd_Flag;
uint16_t I2CA_Cmd_Code;


void Usr_I2CA_InitSetup(void)
{
    IICA0_Init();
    
    IICA->SVA0 = I2CA_SLAVE_ADDR_WT;
    
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
    
}

#endif



