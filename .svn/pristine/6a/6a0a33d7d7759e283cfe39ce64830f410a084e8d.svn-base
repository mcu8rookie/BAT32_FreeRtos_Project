/***********************************************************************************************************************
* Copyright (C) All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* @file    iica_user.c
* @brief   This file implements device driver for IICA module.
* @version 1.0.0
* @date    2022/2/25
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "userdefine.h"
#include "BAT32A237.h"
#include "iica.h"

#include"Usr_Config.h"
#include"Usr_Main.h"
#include "Usr_Psf.h"

#include "Usr_I2CA_Slave.h"
#include "Usr_ALSensor.h"

#include"gpio.h"
#include"Usr_GPIO.h"

#include "Usr_DataFlash.h"

/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
//void IRQ16_Handler(void) __attribute__((alias("iica0_interrupt")));

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: iica0_interrupt
* @brief  IICA interrupt service routine
* @param  None
* @return None
***********************************************************************************************************************/
void iica0_interrupt(void)
{
    INTC_ClearPendingIRQ(IICA_IRQn);
    IICA0_Clear_Wakeup();
    
    
    #if 0
    PORT_ToggleBit(Usr_DBGIO3_PORT,Usr_DBGIO3_PIN);
    //PORT_ToggleBit(Usr_DBGIO4_PORT,Usr_DBGIO4_PIN);
    #endif
    
    if ((IICA->IICS0 & _80_IICA_MASTER_DEVICE) == 0x80U)
    {
        iica0_masterhandler();
    }
    else
    {
        iica0_slavehandler();
    }
}
/***********************************************************************************************************************
* Function Name: iica0_masterhandler
* @brief  This function is IICA0 master handler.
* @param  None
* @return None
***********************************************************************************************************************/
static void iica0_masterhandler(void)
{
    /* Control for communication */
    if ((0U == (IICA->IICF0 & IICA_IICF0_IICBSY_Msk)) && (g_iica0_tx_cnt != 0U))
    {
        iica0_callback_master_error(MD_SPT);
    }
    /* Control for sended address */
    else
    {
        if ((g_iica0_master_status_flag & _80_IICA_ADDRESS_COMPLETE) == 0U)
        {
            if (IICA->IICS0 & IICA_IICS0_ACKD_Msk)
            {
                g_iica0_master_status_flag |= _80_IICA_ADDRESS_COMPLETE;

                if (IICA->IICS0 & IICA_IICS0_TRC_Msk)
                {
                    IICA->IICCTL00 |= IICA_IICCTL00_WTIM_Msk;     /* interrupt request is generated at the ninth clock's falling edge */

                    if (g_iica0_tx_cnt > 0U)
                    {
                        IICA->IICA0 = *gp_iica0_tx_address;
                        gp_iica0_tx_address++;
                        g_iica0_tx_cnt--;
                    }
                    else
                    {
                        iica0_callback_master_sendend();
                    }
                }
                else
                {
                    IICA->IICCTL00 |= IICA_IICCTL00_ACKE_Msk;     /* enable acknowledgment */
                    IICA->IICCTL00 &= ~IICA_IICCTL00_WTIM_Msk;    /* interrupt request is generated at the eighth clock's falling edge */
                    IICA->IICCTL00 |= IICA_IICCTL00_WREL_Msk;     /* cancel wait */
                }
            }
            else
            {
                iica0_callback_master_error(MD_NACK);
            }
        }
        else
        {
            /* Master send control */
            if (IICA->IICS0 & IICA_IICS0_TRC_Msk)
            {
                if ((0U == (IICA->IICS0 & IICA_IICS0_ACKD_Msk)) && (g_iica0_tx_cnt != 0U))
                {
                    iica0_callback_master_error(MD_NACK);
                }
                else
                {
                    if (g_iica0_tx_cnt > 0U)
                    {
                        IICA->IICA0 = *gp_iica0_tx_address;
                        gp_iica0_tx_address++;
                        g_iica0_tx_cnt--;
                    }
                    else
                    {
                        iica0_callback_master_sendend();
                    }
                }
            }
            /* Master receive control */
            else
            {
                if (g_iica0_rx_cnt < g_iica0_rx_len)
                {
                    *gp_iica0_rx_address = IICA->IICA0;
                    gp_iica0_rx_address++;
                    g_iica0_rx_cnt++;
                    
                    if (g_iica0_rx_cnt == g_iica0_rx_len)
                    {
                        IICA->IICCTL00 &= ~IICA_IICCTL00_ACKE_Msk;   /* disable acknowledgment */
                        IICA->IICCTL00 |= IICA_IICCTL00_WREL_Msk;    /* cancel wait */
                        IICA->IICCTL00 |= IICA_IICCTL00_WTIM_Msk;    /* interrupt request is generated at the eighth clock's falling edge */
                    }
                    else
                    {
                        IICA->IICCTL00 |= IICA_IICCTL00_WREL_Msk;     /* cancel wait */
                    }
                }
                else
                {
                    iica0_callback_master_receiveend();
                }
            }
        }
    }
}
/***********************************************************************************************************************
* Function Name: iica0_callback_master_error
* @brief  This function is a callback function when IICA0 master error occurs.
* @param  None
* @return None
***********************************************************************************************************************/
static void iica0_callback_master_error(MD_STATUS flag)
{
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: iica0_callback_master_receiveend
* @brief  This function is a callback function when IICA0 finishes master reception.
* @param  None
* @return None
***********************************************************************************************************************/
static void iica0_callback_master_receiveend(void)
{
    IICA->IICCTL00 |= IICA_IICCTL00_SPT_Msk;            /* stop condition is generated */
    while(0U == (IICA->IICS0 & IICA_IICS0_SPD_Msk));    /* stop condition is detected */

    /* Start user code. Do not edit comment generated here */
        g_iica0_rx_end = 1;
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: iica0_callback_master_sendend
* @brief  This function is a callback function when IICA0 finishes master transmission.
* @param  None
* @return None
***********************************************************************************************************************/
static void iica0_callback_master_sendend(void)
{
    IICA->IICCTL00 |= IICA_IICCTL00_SPT_Msk;            /* stop condition is generated */
    while(0U == (IICA->IICS0 & IICA_IICS0_SPD_Msk));    /* stop condition is detected */
    /* Start user code. Do not edit comment generated here */
    g_iica0_tx_end = 1;
    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: iica0_slavehandler
* @brief  This function is IICA0 slave handler.
* @param  None
* @return None
***********************************************************************************************************************/
// Read S1;
uint8_t crc_tmp;
uint8_t iica0_cnt1;
uint32_t iica_cnt2;

static void iica0_slavehandler(void)
{
    /* Control for stop condition */
    if (IICA->IICS0 & IICA_IICS0_SPD_Msk)
    {   // meet stop condition;
        /* Get stop condition */
        IICA->IICCTL00 &= ~IICA_IICCTL00_SPIE_Msk; /* SPIE0 = 0: disable */
        if(g_iica0_slave_status_flag & _80_IICA_ADDRESS_COMPLETE)
        {   // had match address;
            if (g_iica0_slave_status_flag & 0x04U)   /* send flag */
            {
                iica0_callback_slave_sendend();
            }
            if (g_iica0_slave_status_flag & 0x02U)   /* receive flag */
            {
                iica0_callback_slave_receiveend();
            }
            g_iica0_slave_status_flag = 1U;
        }
    }
    else
    {
        // Read S1;
        if ((g_iica0_slave_status_flag & _80_IICA_ADDRESS_COMPLETE) == 0U)  // No address
        {   // Read S2;
            // had not match address;
            if (IICA->IICS0 & IICA_IICS0_COI_Msk)  // Right address
            {   // Read S3;
                // meet same address;
                IICA->IICCTL00 |= IICA_IICCTL00_SPIE_Msk; /* SPIE0 = 1: enable */   // enable stop interrupt;
                //g_iica0_slave_status_flag |= _80_IICA_ADDRESS_COMPLETE;
                g_iica0_slave_status_flag = _80_IICA_ADDRESS_COMPLETE;
                
                if (IICA->IICS0 & IICA_IICS0_TRC_Msk)  /* TRC0 == 1 */
                {   // 
                    IICA->IICCTL00 |= IICA_IICCTL00_WTIM_Msk;  /* WTIM0 = 1:  interrupt request is generated at the ninth clock's falling edge */
                    
                    //if (g_iica0_tx_cnt > 0U)
                    if (g_iica0_tx_cnt < g_iica0_tx_len)
                    {
                        IICA->IICA0 = gp_iica0_tx_address[0];
                        g_iica0_tx_cnt = 1;
                    }
                    else
                    {
                        iica0_callback_slave_sendend();
                        IICA->IICCTL00 |= IICA_IICCTL00_WREL_Msk;  /* WREL0 = 1U: cancel wait */
                    }
                }
                else
                {   // Read S4;
                    IICA->IICCTL00 |=  IICA_IICCTL00_ACKE_Msk;   /* ACKE0 = 1U: enable acknowledgment */
                    IICA->IICCTL00 &= ~IICA_IICCTL00_WTIM_Msk;   /* WTIM0 = 0U: interrupt request is generated at the eighth clock's falling edge */
                    IICA->IICCTL00 |=  IICA_IICCTL00_WREL_Msk;   /* WREL0 = 1U: cancel wait */
                }
            }
            else
            {
                iica0_callback_slave_error(MD_ERROR);
            }
        }
        else
        {
            if (IICA->IICS0 & IICA_IICS0_TRC_Msk)  /* TRC0 == 1 */
            {
                g_iica0_slave_status_flag |= 4U;   /* send flag */
                if ((0U == (IICA->IICS0 & IICA_IICS0_ACKD_Msk)) && (g_iica0_tx_len > 0U))
                {
                    g_iica0_tx_cnt = 0;
                    g_iica0_tx_len = 0;
                    iica0_callback_slave_error(MD_NACK);
                }
                else
                {
                    // if (g_iica0_tx_cnt > 0U)
                    if (g_iica0_tx_cnt < g_iica0_tx_len)
                    {
                        IICA->IICA0 = gp_iica0_tx_address[g_iica0_tx_cnt++];
                    }
                    else
                    {
                        g_iica0_tx_cnt = 0;
                        g_iica0_tx_len = 0;
                        
                        iica0_callback_slave_sendend();
                        IICA->IICCTL00 |= IICA_IICCTL00_WREL_Msk;  /* WREL0 = 1U: cancel wait */
                    }
                }
            }
            else
            {   // Read S5;
                
                uint16_t u16CmdCode = 0;
                
                g_iica0_slave_status_flag |= 2U;  /* receive flag */
                
                if(g_u16CurCmdCode == 0xFFFF)
                {
                    g_u8CmdBuf[0] = g_u8CmdBuf[1];
                    g_u8CmdBuf[1] = IICA->IICA0;
                    u16CmdCode = (g_u8CmdBuf[0]<<8) | g_u8CmdBuf[1];
                    
                    IICA->IICCTL00 |=  IICA_IICCTL00_WREL_Msk;	 /* WREL0 = 1U: cancel wait */
                    
                    if(Usr_I2CA_isCmdCodeOK(u16CmdCode))
                    {
                        gp_iica0_rx_address[0] = g_u8CmdBuf[0];
                        gp_iica0_rx_address[1] = g_u8CmdBuf[1];
                        g_iica0_rx_cnt = 2;
                        
                        if(Usr_I2CA_isReadingCmd(u16CmdCode))  // reading command
                        {
                            gp_iica0_tx_address = Usr_I2CA_getBuffAddr(u16CmdCode);
                            g_iica0_tx_len = Usr_I2CA_getRdCmdDataLen(u16CmdCode);
                            g_iica0_tx_cnt = 0;
                            
                            g_iica0_rx_cnt = 0;
                            g_iica0_rx_len = DEF_I2CA_RX_MAX;
                            g_u16CurCmdCode = 0xFFFF;
                        }
                        else if((u16CmdCode == 0x3603)
                            || (u16CmdCode == 0x3606)
                            || (u16CmdCode == 0x3615))
                        {
                            g_u8CmdEC05Type = 1;
                            g_iica0_rx_cnt = 0;
                            g_iica0_rx_len = DEF_I2CA_RX_MAX;
                            g_u16CurCmdCode = 0xFFFF;
                        }
                        else
                        {
                            g_u16CurCmdCode = u16CmdCode;
                            g_iica0_rx_len = Usr_I2CA_getWrCmdDataLen(u16CmdCode);
                        }
                        
                        if(g_u16CurCmdCode == 0xFFFF)
                        {
                            g_iica0_slave_status_flag |= 1U;
                            IICA->IICCTL00 |= IICA_IICCTL00_SPIE_Msk; /* SPIE0 = 1: enable */
                            IICA->IICCTL00 |=  IICA_IICCTL00_ACKE_Msk;	 /* ACKE0 = 1U: enable acknowledgment */
                            IICA->IICCTL00 &= ~IICA_IICCTL00_WTIM_Msk;	 /* WTIM0 = 0U: interrupt request is generated at the eighth clock's falling edge */
                            IICA->IICCTL00 |=  IICA_IICCTL00_WREL_Msk;	 /* WREL0 = 1U: cancel wait */
                            iica0_callback_slave_receiveend();
                        }
                    }
                    else
                    {
                        g_iica0_rx_cnt = 0;
                        g_iica0_rx_len = DEF_I2CA_RX_MAX;
                        
                        //g_iica0_slave_status_flag |= 1U;
                        //IICA->IICCTL00 |= IICA_IICCTL00_SPIE_Msk; /* SPIE0 = 1: enable */
                        
                        IICA->IICCTL00 |=  IICA_IICCTL00_ACKE_Msk;	 /* ACKE0 = 1U: enable acknowledgment */
                        IICA->IICCTL00 &= ~IICA_IICCTL00_WTIM_Msk;	 /* WTIM0 = 0U: interrupt request is generated at the eighth clock's falling edge */
                        IICA->IICCTL00 |=  IICA_IICCTL00_WREL_Msk;	 /* WREL0 = 1U: cancel wait */
                        iica0_callback_slave_receiveend();
                    }
                }
                else
                {
                    if(g_iica0_rx_cnt < g_iica0_rx_len)
                    {
                        gp_iica0_rx_address[g_iica0_rx_cnt++] = IICA->IICA0;
                        
                        if(g_iica0_rx_cnt == g_iica0_rx_len)
                    {
                        IICA->IICCTL00 |=  IICA_IICCTL00_ACKE_Msk;	 /* ACKE0 = 1U: enable acknowledgment */
                        IICA->IICCTL00 &= ~IICA_IICCTL00_WTIM_Msk;	 /* WTIM0 = 0U: interrupt request is generated at the eighth clock's falling edge */
                        IICA->IICCTL00 |= IICA_IICCTL00_WREL_Msk;   /* WREL0 = 1U: cancel wait */
                        iica0_callback_slave_receiveend();
                        
                        //g_iica0_slave_status_flag |= 1U;
                        //IICA->IICCTL00 |= IICA_IICCTL00_SPIE_Msk; /* SPIE0 = 1: enable */
                        
                        if(Usr_I2CA_isReadingCmd(g_u16CurCmdCode) == 0)
                        {
                            g_u8CmdOK = 1;
                        }
                        
                        g_u16CurCmdCode = 0xFFFF;
                        g_u16CurCmdLen  = g_iica0_rx_cnt;
                        g_iica0_rx_cnt = 0;
                        g_iica0_rx_len = DEF_I2CA_RX_MAX;
                    }
                    else
                    {
                        IICA->IICCTL00 |=  IICA_IICCTL00_WREL_Msk;   /* WREL0 = 1U: cancel wait */
                    }
                }
                else
                {
                    g_iica0_slave_status_flag |= 1U;
                    IICA->IICCTL00 |= IICA_IICCTL00_SPIE_Msk; /* SPIE0 = 1: enable */
                    IICA->IICCTL00 |=  IICA_IICCTL00_WREL_Msk;   /* WREL0 = 1U: cancel wait */
                }
            }
        }
    }
}
}



/***********************************************************************************************************************
* Function Name: iica0_callback_slave_error
* @brief  This function is a callback function when IICA0 slave error occurs.
* @param  None
* @return None
***********************************************************************************************************************/
static void iica0_callback_slave_error(MD_STATUS flag)
{
    /* Start user code. Do not edit comment generated here */
    IICA->IICCTL00 |=  IICA_IICCTL00_WREL_Msk;   /* WREL0 = 1U: cancel wait */   
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: iica0_callback_slave_receiveend
* @brief  This function is a callback function when IICA0 finishes slave reception.
* @param  None
* @return None
***********************************************************************************************************************/
static void iica0_callback_slave_receiveend(void)
{
    /* Start user code. Do not edit comment generated here */
    g_iica0_rx_end = 1;
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: iica0_callback_slave_sendend
* @brief  This function is a callback function when IICA0 finishes slave transmission.
* @param  None
* @return None
***********************************************************************************************************************/
static void iica0_callback_slave_sendend(void)
{
    /* Start user code. Do not edit comment generated here */
    g_iica0_tx_end = 1;
    /* End user code. Do not edit comment generated here */
}

/* Start user code for adding. Do not edit comment generated here */

/* End user code. Do not edit comment generated here */
