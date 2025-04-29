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
    {
        /* Get stop condition */
        IICA->IICCTL00 &= ~IICA_IICCTL00_SPIE_Msk; /* SPIE0 = 0: disable */
        if(g_iica0_slave_status_flag & _80_IICA_ADDRESS_COMPLETE)
        {
            if (g_iica0_slave_status_flag & 0x04U)   /* send flag */
            {
                iica0_callback_slave_sendend();
            }
            if (g_iica0_slave_status_flag & 0x02U)   /* receive flag */
            {
                iica0_callback_slave_receiveend();
            }
            
            
            #if(defined(DEF_I2C_TYPE)&&(DEF_I2C_TYPE==DEF_I2C_TYPE_PSF))
            
            #endif
            
            #if(defined(DEF_I2C_TYPE)&&(DEF_I2C_TYPE==DEF_I2C_TYPE_MIDEA))
            if(0 == 1)
            {
                
            }
            else if(Usr_Md_State == 2)
            {   // Write Cmds finished;
                if(1==0)
                {
                    
                }
                #if 1
                #if(defined(DEF_DELTA_RAW_EN)&&(DEF_DELTA_RAW_EN==1))
                else if(Usr_Md_CmdCode1 == 0x1180)
                {   // Write Usr_Delta_Raw;
                    I2CA_RX_Cnt = g_iica0_rx_cnt;
                    
                    for(I2CA_RX_Cnt=0;I2CA_RX_Cnt<g_iica0_rx_cnt;I2CA_RX_Cnt++)
                    {
                        I2CA_RX_Buff2[I2CA_RX_Cnt] = I2CA_RX_Buff[I2CA_RX_Cnt];
                    }
                    
                    I2CA_WR_Flag = 1;
                }
                #endif
                
                #if(defined(DEF_DELTA_PPM_EN)&&(DEF_DELTA_PPM_EN==1))
                else if(Usr_Md_CmdCode1 == 0x1181)
                {   // Write Usr_Delta_PPM1;
                    I2CA_RX_Cnt = g_iica0_rx_cnt;
                    
                    for(I2CA_RX_Cnt=0;I2CA_RX_Cnt<g_iica0_rx_cnt;I2CA_RX_Cnt++)
                    {
                        I2CA_RX_Buff2[I2CA_RX_Cnt] = I2CA_RX_Buff[I2CA_RX_Cnt];
                    }
                    
                    I2CA_WR_Flag = 1;
                }
                #endif
                
                #if(defined(DEF_CONCEN_THRE_EN)&&(DEF_CONCEN_THRE_EN==1))
                else if(Usr_Md_CmdCode1 == 0x1182)
                {   // Write now concentration threshold value;
                    I2CA_RX_Cnt = g_iica0_rx_cnt;
                    
                    for(I2CA_RX_Cnt=0;I2CA_RX_Cnt<g_iica0_rx_cnt;I2CA_RX_Cnt++)
                    {
                        I2CA_RX_Buff2[I2CA_RX_Cnt] = I2CA_RX_Buff[I2CA_RX_Cnt];
                    }
                    
                    I2CA_WR_Flag = 1;
                }
                #endif
                else if(Usr_Md_CmdCode1==0x1183)
                {   // Write HumComp_M2_S;
                    I2CA_RX_Cnt = g_iica0_rx_cnt;
                    
                    for(I2CA_RX_Cnt=0;I2CA_RX_Cnt<g_iica0_rx_cnt;I2CA_RX_Cnt++)
                    {
                        I2CA_RX_Buff2[I2CA_RX_Cnt] = I2CA_RX_Buff[I2CA_RX_Cnt];
                    }
                    
                    I2CA_WR_Flag = 1;
                }
                else if(Usr_Md_CmdCode1==0x1184)
                {   // Write HumComp_Flag;
                    I2CA_RX_Cnt = g_iica0_rx_cnt;
                    
                    for(I2CA_RX_Cnt=0;I2CA_RX_Cnt<g_iica0_rx_cnt;I2CA_RX_Cnt++)
                    {
                        I2CA_RX_Buff2[I2CA_RX_Cnt] = I2CA_RX_Buff[I2CA_RX_Cnt];
                    }
                    
                    I2CA_WR_Flag = 1;
                }
                else if(Usr_Md_CmdCode1==0x1185)
                {   // Write HumComp_K;
                    I2CA_RX_Cnt = g_iica0_rx_cnt;
                    
                    for(I2CA_RX_Cnt=0;I2CA_RX_Cnt<g_iica0_rx_cnt;I2CA_RX_Cnt++)
                    {
                        I2CA_RX_Buff2[I2CA_RX_Cnt] = I2CA_RX_Buff[I2CA_RX_Cnt];
                    }
                    
                    I2CA_WR_Flag = 1;
                }
                else if(Usr_Md_CmdCode1==0x1186)
                {   // Write PresComp_Flag;
                    I2CA_RX_Cnt = g_iica0_rx_cnt;
                    
                    for(I2CA_RX_Cnt=0;I2CA_RX_Cnt<g_iica0_rx_cnt;I2CA_RX_Cnt++)
                    {
                        I2CA_RX_Buff2[I2CA_RX_Cnt] = I2CA_RX_Buff[I2CA_RX_Cnt];
                    }
                    
                    I2CA_WR_Flag = 1;
                }
                else if(Usr_Md_CmdCode1==0x1188)
                {   // Write SN;
                    I2CA_RX_Cnt = g_iica0_rx_cnt;
                    
                    for(I2CA_RX_Cnt=0;I2CA_RX_Cnt<g_iica0_rx_cnt;I2CA_RX_Cnt++)
                    {
                        I2CA_RX_Buff2[I2CA_RX_Cnt] = I2CA_RX_Buff[I2CA_RX_Cnt];
                    }
                    
                    I2CA_WR_Flag = 1;
                }
                else if(Usr_Md_CmdCode1==0x1189)
                {   // Write Temperature compensation parameters;
                    I2CA_RX_Cnt = g_iica0_rx_cnt;
                    
                    for(I2CA_RX_Cnt=0;I2CA_RX_Cnt<g_iica0_rx_cnt;I2CA_RX_Cnt++)
                    {
                        I2CA_RX_Buff2[I2CA_RX_Cnt] = I2CA_RX_Buff[I2CA_RX_Cnt];
                    }
                    
                    I2CA_WR_Flag = 1;
                }
                else if(Usr_Md_CmdCode1 == 0x118C)
                {   // Write Sens_TableY;
                    I2CA_RX_Cnt = g_iica0_rx_cnt;
                    
                    for(I2CA_RX_Cnt=0;I2CA_RX_Cnt<g_iica0_rx_cnt;I2CA_RX_Cnt++)
                    {
                        I2CA_RX_Buff2[I2CA_RX_Cnt] = I2CA_RX_Buff[I2CA_RX_Cnt];
                    }
                    
                    I2CA_WR_Flag = 1;
                }
                else if(Usr_Md_CmdCode1 == 0x118D)
                {   // Write Sens_TableX;
                    I2CA_RX_Cnt = g_iica0_rx_cnt;
                    
                    for(I2CA_RX_Cnt=0;I2CA_RX_Cnt<g_iica0_rx_cnt;I2CA_RX_Cnt++)
                    {
                        I2CA_RX_Buff2[I2CA_RX_Cnt] = I2CA_RX_Buff[I2CA_RX_Cnt];
                    }
                    
                    I2CA_WR_Flag = 1;
                }
                else if(Usr_Md_CmdCode1 == 0x118E)
                {   // Write Sens_CoolTime;
                    I2CA_RX_Cnt = g_iica0_rx_cnt;
                    
                    for(I2CA_RX_Cnt=0;I2CA_RX_Cnt<g_iica0_rx_cnt;I2CA_RX_Cnt++)
                    {
                        I2CA_RX_Buff2[I2CA_RX_Cnt] = I2CA_RX_Buff[I2CA_RX_Cnt];
                    }
                    
                    I2CA_WR_Flag = 1;
                }
                else if(Usr_Md_CmdCode1 == 0x118F)
                {   // Write TComp_TRawBase;
                    I2CA_RX_Cnt = g_iica0_rx_cnt;
                    
                    for(I2CA_RX_Cnt=0;I2CA_RX_Cnt<g_iica0_rx_cnt;I2CA_RX_Cnt++)
                    {
                        I2CA_RX_Buff2[I2CA_RX_Cnt] = I2CA_RX_Buff[I2CA_RX_Cnt];
                    }
                    
                    I2CA_WR_Flag = 1;
                }
                else if(Usr_Md_CmdCode1 == 0x1190)
                {   // Write PresComp_PBase;
                    I2CA_RX_Cnt = g_iica0_rx_cnt;
                    
                    for(I2CA_RX_Cnt=0;I2CA_RX_Cnt<g_iica0_rx_cnt;I2CA_RX_Cnt++)
                    {
                        I2CA_RX_Buff2[I2CA_RX_Cnt] = I2CA_RX_Buff[I2CA_RX_Cnt];
                    }
                    
                    I2CA_WR_Flag = 1;
                }
                else if(Usr_Md_CmdCode1 == 0x1191)
                {   // Write Sens_DC_Y;
                    I2CA_RX_Cnt = g_iica0_rx_cnt;
                    
                    for(I2CA_RX_Cnt=0;I2CA_RX_Cnt<g_iica0_rx_cnt;I2CA_RX_Cnt++)
                    {
                        I2CA_RX_Buff2[I2CA_RX_Cnt] = I2CA_RX_Buff[I2CA_RX_Cnt];
                    }
                    
                    I2CA_WR_Flag = 1;
                }
                //else if(Usr_Md_CmdCode1 == 0x1293)
                else if(Usr_Md_CmdCode1 == 0x1193)
                {   // Write FilterCnt;
                    I2CA_RX_Cnt = g_iica0_rx_cnt;
                    
                    for(I2CA_RX_Cnt=0;I2CA_RX_Cnt<g_iica0_rx_cnt;I2CA_RX_Cnt++)
                    {
                        I2CA_RX_Buff2[I2CA_RX_Cnt] = I2CA_RX_Buff[I2CA_RX_Cnt];
                    }
                    
                    I2CA_WR_Flag = 1;
                }
                else if(Usr_Md_CmdCode1 == 0x1194)
                {   // Write Sens_PreHeatTime;
                    I2CA_RX_Cnt = g_iica0_rx_cnt;
                    
                    for(I2CA_RX_Cnt=0;I2CA_RX_Cnt<g_iica0_rx_cnt;I2CA_RX_Cnt++)
                    {
                        I2CA_RX_Buff2[I2CA_RX_Cnt] = I2CA_RX_Buff[I2CA_RX_Cnt];
                    }
                    
                    I2CA_WR_Flag = 1;
                }
                else if(Usr_Md_CmdCode1 == 0x1195)
                {   // Write TmpRate_P;
                    I2CA_RX_Cnt = g_iica0_rx_cnt;
                    
                    for(I2CA_RX_Cnt=0;I2CA_RX_Cnt<g_iica0_rx_cnt;I2CA_RX_Cnt++)
                    {
                        I2CA_RX_Buff2[I2CA_RX_Cnt] = I2CA_RX_Buff[I2CA_RX_Cnt];
                    }
                    
                    I2CA_WR_Flag = 1;
                }
                #endif
                
                #if(defined(DEF_HEAT_COMP2_EN)&&(DEF_HEAT_COMP2_EN==1))
                else if(Usr_Md_CmdCode1 == 0x11A1)
                {   // Write HtComp_TRaw_Base_2;
                    I2CA_RX_Cnt = g_iica0_rx_cnt;
                    
                    for(I2CA_RX_Cnt=0;I2CA_RX_Cnt<g_iica0_rx_cnt;I2CA_RX_Cnt++)
                    {
                        I2CA_RX_Buff2[I2CA_RX_Cnt] = I2CA_RX_Buff[I2CA_RX_Cnt];
                    }
                    
                    I2CA_WR_Flag = 1;
                }
                else if(Usr_Md_CmdCode1 == 0x11A2)
                {   // Write HtComp_HtRaw_Base_2;
                    I2CA_RX_Cnt = g_iica0_rx_cnt;
                    
                    for(I2CA_RX_Cnt=0;I2CA_RX_Cnt<g_iica0_rx_cnt;I2CA_RX_Cnt++)
                    {
                        I2CA_RX_Buff2[I2CA_RX_Cnt] = I2CA_RX_Buff[I2CA_RX_Cnt];
                    }
                    
                    I2CA_WR_Flag = 1;
                }
                else if(Usr_Md_CmdCode1 == 0x11A3)
                {   // Write HtComp_Kh_2;
                    I2CA_RX_Cnt = g_iica0_rx_cnt;
                    
                    for(I2CA_RX_Cnt=0;I2CA_RX_Cnt<g_iica0_rx_cnt;I2CA_RX_Cnt++)
                    {
                        I2CA_RX_Buff2[I2CA_RX_Cnt] = I2CA_RX_Buff[I2CA_RX_Cnt];
                    }
                    
                    I2CA_WR_Flag = 1;
                }
                else if(Usr_Md_CmdCode1 == 0x11A4)
                {   // Write HtComp_SP_2;
                    I2CA_RX_Cnt = g_iica0_rx_cnt;
                    
                    for(I2CA_RX_Cnt=0;I2CA_RX_Cnt<g_iica0_rx_cnt;I2CA_RX_Cnt++)
                    {
                        I2CA_RX_Buff2[I2CA_RX_Cnt] = I2CA_RX_Buff[I2CA_RX_Cnt];
                    }
                    
                    I2CA_WR_Flag = 1;
                }
                else if(Usr_Md_CmdCode1 == 0x11A5)
                {   // Write HtComp_Ks_2;
                    I2CA_RX_Cnt = g_iica0_rx_cnt;
                    
                    for(I2CA_RX_Cnt=0;I2CA_RX_Cnt<g_iica0_rx_cnt;I2CA_RX_Cnt++)
                    {
                        I2CA_RX_Buff2[I2CA_RX_Cnt] = I2CA_RX_Buff[I2CA_RX_Cnt];
                    }
                    
                    I2CA_WR_Flag = 1;
                }
                #endif
                else if(Usr_Md_CmdCode1 == 0x11B0)
                {   // Write ErrorData1;
                    I2CA_RX_Cnt = g_iica0_rx_cnt;
                    
                    for(I2CA_RX_Cnt=0;I2CA_RX_Cnt<g_iica0_rx_cnt;I2CA_RX_Cnt++)
                    {
                        I2CA_RX_Buff2[I2CA_RX_Cnt] = I2CA_RX_Buff[I2CA_RX_Cnt];
                    }
                    
                    I2CA_WR_Flag = 1;
                }
                
                #if(defined(DEF_ASC_EN)&&(DEF_ASC_EN==1))
                else if(Usr_Md_CmdCode1 == 0x11C0)
                {   // Write ASC_Func_En;
                    I2CA_RX_Cnt = g_iica0_rx_cnt;
                    
                    for(I2CA_RX_Cnt=0;I2CA_RX_Cnt<g_iica0_rx_cnt;I2CA_RX_Cnt++)
                    {
                        I2CA_RX_Buff2[I2CA_RX_Cnt] = I2CA_RX_Buff[I2CA_RX_Cnt];
                    }
                    
                    I2CA_WR_Flag = 1;
                }
                else if(Usr_Md_CmdCode1 == 0x11C1)
                {   // Write ASC_PPM_HighTh;
                    I2CA_RX_Cnt = g_iica0_rx_cnt;
                    
                    for(I2CA_RX_Cnt=0;I2CA_RX_Cnt<g_iica0_rx_cnt;I2CA_RX_Cnt++)
                    {
                        I2CA_RX_Buff2[I2CA_RX_Cnt] = I2CA_RX_Buff[I2CA_RX_Cnt];
                    }
                    
                    I2CA_WR_Flag = 1;
                }
                else if(Usr_Md_CmdCode1 == 0x11C2)
                {   // Write ASC_PPM_LowTh;
                    I2CA_RX_Cnt = g_iica0_rx_cnt;
                    
                    for(I2CA_RX_Cnt=0;I2CA_RX_Cnt<g_iica0_rx_cnt;I2CA_RX_Cnt++)
                    {
                        I2CA_RX_Buff2[I2CA_RX_Cnt] = I2CA_RX_Buff[I2CA_RX_Cnt];
                    }
                    
                    I2CA_WR_Flag = 1;
                }
                else if(Usr_Md_CmdCode1 == 0x11C3)
                {   // Write ASC_Tmpr_RateTh;
                    I2CA_RX_Cnt = g_iica0_rx_cnt;
                    
                    for(I2CA_RX_Cnt=0;I2CA_RX_Cnt<g_iica0_rx_cnt;I2CA_RX_Cnt++)
                    {
                        I2CA_RX_Buff2[I2CA_RX_Cnt] = I2CA_RX_Buff[I2CA_RX_Cnt];
                    }
                    
                    I2CA_WR_Flag = 1;
                }
                else if(Usr_Md_CmdCode1 == 0x11C4)
                {   // Write ASC_Humi_RateTh;
                    I2CA_RX_Cnt = g_iica0_rx_cnt;
                    
                    for(I2CA_RX_Cnt=0;I2CA_RX_Cnt<g_iica0_rx_cnt;I2CA_RX_Cnt++)
                    {
                        I2CA_RX_Buff2[I2CA_RX_Cnt] = I2CA_RX_Buff[I2CA_RX_Cnt];
                    }
                    
                    I2CA_WR_Flag = 1;
                }
                else if(Usr_Md_CmdCode1 == 0x11C6)
                {   // Write ASC_Adjust_Cnt,ASC_Adjust_Value1,ASC_Adjust_Value2,ASC_Adjust_Value3;
                    I2CA_RX_Cnt = g_iica0_rx_cnt;
                    
                    for(I2CA_RX_Cnt=0;I2CA_RX_Cnt<g_iica0_rx_cnt;I2CA_RX_Cnt++)
                    {
                        I2CA_RX_Buff2[I2CA_RX_Cnt] = I2CA_RX_Buff[I2CA_RX_Cnt];
                    }
                    
                    I2CA_WR_Flag = 1;
                }
                
                #endif
                else if(Usr_Md_CmdCode1==0x3608)
                {   // Write Gas type;
                    I2CA_RX_Cnt = g_iica0_rx_cnt;
                    
                    for(I2CA_RX_Cnt=0;I2CA_RX_Cnt<g_iica0_rx_cnt;I2CA_RX_Cnt++)
                    {
                        I2CA_RX_Buff2[I2CA_RX_Cnt] = I2CA_RX_Buff[I2CA_RX_Cnt];
                    }
                    
                    I2CA_WR_Flag = 1;
                }
                else if(Usr_Md_CmdCode1==0x3603)
                {   // Write Start Measurement Cmd;
                    I2CA_RX_Cnt = g_iica0_rx_cnt;
                    
                    for(I2CA_RX_Cnt=0;I2CA_RX_Cnt<g_iica0_rx_cnt;I2CA_RX_Cnt++)
                    {
                        I2CA_RX_Buff2[I2CA_RX_Cnt] = I2CA_RX_Buff[I2CA_RX_Cnt];
                    }
                    
                    I2CA_WR_Flag = 1;
                }
                #if(defined(DEF_I2CRST1_EN)&&(DEF_I2CRST1_EN==1))
                else if(Usr_Md_CmdCode1==0x3606)
                {   // Write Reset Cmd;
                    I2CA_RX_Cnt = g_iica0_rx_cnt;
                    
                    for(I2CA_RX_Cnt=0;I2CA_RX_Cnt<g_iica0_rx_cnt;I2CA_RX_Cnt++)
                    {
                        I2CA_RX_Buff2[I2CA_RX_Cnt] = I2CA_RX_Buff[I2CA_RX_Cnt];
                    }
                    
                    I2CA_WR_Flag = 1;
                }
                #endif
                
            }
            else if(Usr_Md_State == 3)
            {   // Read data finished;
                
                Usr_Md_State = 0;
                Usr_Md_Cmd1 = 0;
                Usr_Md_Cmd1 = 0;
                Usr_Md_CmdCode0 = 0;
                Usr_Md_CmdCode1 = 0;
                Usr_Md_CmdCode2 = 0;
                
            }
            
            
            {
                
                gp_iica0_rx_address = I2CA_RX_Buff;        /* iica0 receive buffer address */
                g_iica0_rx_len = DEF_I2CA_RX_MAX;             /* iica0 receive data length */
                g_iica0_rx_cnt = 0;             /* iica0 receive data count */
                g_iica0_rx_end = 0;             /* iica0 receive data end */
                
                
                gp_iica0_tx_address = I2CA_TX_Buff;        /* iica0 send buffer address */
                g_iica0_tx_cnt = DEF_I2CA_TX_MAX;             /* iica0 send data count */
                g_iica0_tx_end = 0;             /* iica0 send data end */
                
                g_iica0_tx_count = 0;
                
                g_iica0_slave_status_flag = 0;  /* iica0 slave flag */
                
            }
            #endif
        }
        
        //g_iica0_slave_status_flag = 1U;
    }
    else
    {
        // Read S1;
        if ((g_iica0_slave_status_flag & _80_IICA_ADDRESS_COMPLETE) == 0U)
        {   // Read S2;
            if (IICA->IICS0 & IICA_IICS0_COI_Msk)
            {   // Read S3;
                IICA->IICCTL00 |= IICA_IICCTL00_SPIE_Msk; /* SPIE0 = 1: enable */
                //g_iica0_slave_status_flag |= _80_IICA_ADDRESS_COMPLETE;
                g_iica0_slave_status_flag = _80_IICA_ADDRESS_COMPLETE;
                
                if (IICA->IICS0 & IICA_IICS0_TRC_Msk)  /* TRC0 == 1 */
                {
                    IICA->IICCTL00 |= IICA_IICCTL00_WTIM_Msk;  /* WTIM0 = 1:  interrupt request is generated at the ninth clock's falling edge */
                    
                    #if(defined(DEF_I2C_TYPE)&&(DEF_I2C_TYPE==DEF_I2C_TYPE_MIDEA))
                    {
                        if(Usr_Md_State == 2)
                        {
                            if(1==0)
                            {
                                
                            }
                            #if 1
                            else if(Usr_Md_CmdCode1 == 0x1001)
                            {   // Read Raw;
                                g_iica0_tx_cnt = 9;
                                //Tmpr_TRaw;
                                I2CA_TX_Buff[0] = Tmpr_TRaw>>8;
                                I2CA_TX_Buff[1] = Tmpr_TRaw;
                                //crc_tmp = sensirion_common_generate(I2CA_TX_Buff,2);
                                crc_tmp = compute_crc8(I2CA_TX_Buff,2);
                                I2CA_TX_Buff[2] = crc_tmp;
                                
                                //Sens_SRaw;
                                I2CA_TX_Buff[3] = Sens_Raw_After_Filter>>8;
                                I2CA_TX_Buff[4] = Sens_Raw_After_Filter;
                                //crc_tmp = sensirion_common_generate(I2CA_TX_Buff+3,2);
                                crc_tmp = compute_crc8(I2CA_TX_Buff+3,2);
                                I2CA_TX_Buff[5] = crc_tmp;
                                
                                #if(defined(DEF_DBG_SRAW_0_EN)&&(DEF_DBG_SRAW_0_EN==1))
                                if(Sens_Raw_After_Filter<=0)
                                {
                                    if(Dbg_SRaw0_Cnt2<65530)
                                    {
                                        Dbg_SRaw0_Cnt2++;
                                        
                                        DF_Data[DEF_SRAW02_INDEX] = (uint8_t)Dbg_SRaw0_Cnt2;
                                        DF_Data[DEF_SRAW02_INDEX+1] = (uint8_t)(Dbg_SRaw0_Cnt2>>8);
                                        
                                        DF_UpdateReal_Flag = 1;
                                    }
                                }
                                #endif
                                
                                //Sens_SRawComp;
                                I2CA_TX_Buff[6] = Sens_Raw_After_All>>8;
                                I2CA_TX_Buff[7] = Sens_Raw_After_All;
                                //crc_tmp = sensirion_common_generate(I2CA_TX_Buff+6,2);
                                crc_tmp = compute_crc8(I2CA_TX_Buff+6,2);
                                I2CA_TX_Buff[8] = crc_tmp;
                                
                            }
                            else if(Usr_Md_CmdCode1 == 0x1002)
                            {   // Read Sens_PPM_After_Cali Sens_PPM_After_PrsComp Sens_PPM_After_All Sens_LFL_U16;
                                g_iica0_tx_cnt = 15;
                                //Sens_PPM_After_Cali;
                                I2CA_TX_Buff[0] = Sens_PPM_After_Cali>>8;
                                I2CA_TX_Buff[1] = Sens_PPM_After_Cali;
                                //crc_tmp = sensirion_common_generate(I2CA_TX_Buff,2);
                                crc_tmp = compute_crc8(I2CA_TX_Buff,2);
                                I2CA_TX_Buff[2] = crc_tmp;
                                
                                #if 0
                                //Sens_PPM_After_PrsComp;
                                I2CA_TX_Buff[3] = Sens_PPM_After_PrsComp>>8;
                                I2CA_TX_Buff[4] = Sens_PPM_After_PrsComp;
                                //crc_tmp = sensirion_common_generate(I2CA_TX_Buff+3,2);
                                crc_tmp = compute_crc8(I2CA_TX_Buff+3,2);
                                I2CA_TX_Buff[5] = crc_tmp;
                                #endif
                                
                                #if 1
                                //Sens_PPM_After_PrsComp2;
                                I2CA_TX_Buff[3] = Sens_PPM_After_PrsComp2>>8;
                                I2CA_TX_Buff[4] = Sens_PPM_After_PrsComp2;
                                //crc_tmp = sensirion_common_generate(I2CA_TX_Buff+3,2);
                                crc_tmp = compute_crc8(I2CA_TX_Buff+3,2);
                                I2CA_TX_Buff[5] = crc_tmp;
                                #endif
                                
                                #if 0
                                //Sens_PPM_After_DCY;
                                I2CA_TX_Buff[3] = Sens_PPM_After_DCY>>8;
                                I2CA_TX_Buff[4] = Sens_PPM_After_DCY;
                                //crc_tmp = sensirion_common_generate(I2CA_TX_Buff+3,2);
                                crc_tmp = compute_crc8(I2CA_TX_Buff+3,2);
                                I2CA_TX_Buff[5] = crc_tmp;
                                #endif
                                
                                #if 0
                                //Sens_PPM_After_All;
                                I2CA_TX_Buff[6] = Sens_PPM_After_All>>8;
                                I2CA_TX_Buff[7] = Sens_PPM_After_All;
                                //crc_tmp = sensirion_common_generate(I2CA_TX_Buff+6,2);
                                crc_tmp = compute_crc8(I2CA_TX_Buff+6,2);
                                I2CA_TX_Buff[8] = crc_tmp;
                                #endif
                                
                                #if 1
                                //Sens_PPM_After_All_I32;
                                I2CA_TX_Buff[6] = (Sens_PPM_After_All_I32>>24);
                                I2CA_TX_Buff[7] = (Sens_PPM_After_All_I32>>16);
                                //crc_tmp = sensirion_common_generate(I2CA_TX_Buff+6,2);
                                crc_tmp = compute_crc8(I2CA_TX_Buff+6,2);
                                I2CA_TX_Buff[8] = crc_tmp;
                                
                                I2CA_TX_Buff[9] = (Sens_PPM_After_All_I32>>8);
                                I2CA_TX_Buff[10] = (Sens_PPM_After_All_I32>>0);
                                //crc_tmp = sensirion_common_generate(I2CA_TX_Buff+6,2);
                                crc_tmp = compute_crc8(I2CA_TX_Buff+9,2);
                                I2CA_TX_Buff[11] = crc_tmp;
                                #endif
                                
                                //Sens_LFL_U16;
                                I2CA_TX_Buff[12] = Sens_LFL_U16>>8;
                                I2CA_TX_Buff[13] = Sens_LFL_U16;
                                //crc_tmp = sensirion_common_generate(I2CA_TX_Buff+6,2);
                                crc_tmp = compute_crc8(I2CA_TX_Buff+12,2);
                                I2CA_TX_Buff[14] = crc_tmp;
                            }
                            else if(Usr_Md_CmdCode1 == 0x1003)
                            {   // Read Usr_HumComp_PPMC_INT, dlt_ppm_pressure_int;
                                g_iica0_tx_cnt = 6;
                                
                                #if 1
                                //Usr_HumComp_PPMC_INT;
                                I2CA_TX_Buff[0] = Usr_HumComp_PPMC_INT>>8;
                                I2CA_TX_Buff[1] = Usr_HumComp_PPMC_INT;
                                //crc_tmp = sensirion_common_generate(I2CA_TX_Buff,2);
                                crc_tmp = compute_crc8(I2CA_TX_Buff,2);
                                I2CA_TX_Buff[2] = crc_tmp;
                                
                                //dlt_ppm_pressure_int;
                                I2CA_TX_Buff[3] = dlt_ppm_pressure_int>>8;
                                I2CA_TX_Buff[4] = dlt_ppm_pressure_int;
                                //crc_tmp = sensirion_common_generate(I2CA_TX_Buff+3,2);
                                crc_tmp = compute_crc8(I2CA_TX_Buff+3,2);
                                I2CA_TX_Buff[5] = crc_tmp;
                                #endif
                                
                                #if 0
                                //Usr_HumComp_PPMC_INT;
                                I2CA_TX_Buff[0] = 1;
                                I2CA_TX_Buff[1] = 2;
                                //crc_tmp = sensirion_common_generate(I2CA_TX_Buff,2);
                                crc_tmp = compute_crc8(I2CA_TX_Buff,2);
                                I2CA_TX_Buff[2] = crc_tmp;
                                
                                //dlt_ppm_pressure_int;
                                I2CA_TX_Buff[3] = 3;
                                I2CA_TX_Buff[4] = 4;
                                //crc_tmp = sensirion_common_generate(I2CA_TX_Buff+3,2);
                                crc_tmp = compute_crc8(I2CA_TX_Buff+3,2);
                                I2CA_TX_Buff[5] = crc_tmp;
                                #endif
                            }
                            #if(defined(DEF_CONCEN_THRE_EN)&&(DEF_CONCEN_THRE_EN==1))
                            else if(Usr_Md_CmdCode1 == 0x1004)
                            {   // Read Flag_Concen_Threshol_Alarm
                                g_iica0_tx_cnt = 3;
                                
                                //Usr_HumComp_PPMC_INT;
                                I2CA_TX_Buff[0] = Flag_Concen_Threshol_Alarm>>8;
                                I2CA_TX_Buff[1] = Flag_Concen_Threshol_Alarm;
                                //crc_tmp = sensirion_common_generate(I2CA_TX_Buff,2);
                                crc_tmp = compute_crc8(I2CA_TX_Buff,2);
                                I2CA_TX_Buff[2] = crc_tmp;
                                
                            }
                            #endif
                            
                            #if(defined(DEF_ADC_EN)&&(DEF_ADC_EN == 1))
                            else if(Usr_Md_CmdCode1 == 0x1005)
                            {   // Read Monitor_Raw1
                                g_iica0_tx_cnt = 3;
                                
                                I2CA_TX_Buff[0] = Monitor_Raw1>>8;
                                I2CA_TX_Buff[1] = Monitor_Raw1;
                                //crc_tmp = sensirion_common_generate(I2CA_TX_Buff,2);
                                crc_tmp = compute_crc8(I2CA_TX_Buff,2);
                                I2CA_TX_Buff[2] = crc_tmp;
                                
                            }
                            #endif
                            
                            else if(Usr_Md_CmdCode1 == 0x1006)
                            {   // Read Tmpr Humidity Pressure;
                                
                                g_iica0_tx_cnt = 9;
                                //Tmpr_TRaw;
                                I2CA_TX_Buff[0] = TH_Sensor_Temperature_out>>8;
                                I2CA_TX_Buff[1] = TH_Sensor_Temperature_out;
                                //crc_tmp = sensirion_common_generate(I2CA_TX_Buff,2);
                                crc_tmp = compute_crc8(I2CA_TX_Buff,2);
                                I2CA_TX_Buff[2] = crc_tmp;
                                
                                //Sens_SRaw;
                                I2CA_TX_Buff[3] = TH_Sensor_Humidity_out>>8;
                                I2CA_TX_Buff[4] = TH_Sensor_Humidity_out;
                                //crc_tmp = sensirion_common_generate(I2CA_TX_Buff+3,2);
                                crc_tmp = compute_crc8(I2CA_TX_Buff+3,2);
                                I2CA_TX_Buff[5] = crc_tmp;
                                
                                //Sens_SRawComp;
                                I2CA_TX_Buff[6] = PSensor_Pressure_10Pa>>8;
                                I2CA_TX_Buff[7] = PSensor_Pressure_10Pa;
                                //crc_tmp = sensirion_common_generate(I2CA_TX_Buff+6,2);
                                crc_tmp = compute_crc8(I2CA_TX_Buff+6,2);
                                I2CA_TX_Buff[8] = crc_tmp;
                                
                                
                            }
                            else if(Usr_Md_CmdCode1 == 0x100F)
                            {   // Read FW Version;
                                g_iica0_tx_cnt = 6;
                                //
                                I2CA_TX_Buff[0] = 0;
                                I2CA_TX_Buff[1] = FW_VERSION_PART0;
                                //crc_tmp = sensirion_common_generate(I2CA_TX_Buff,2);
                                crc_tmp = compute_crc8(I2CA_TX_Buff,2);
                                I2CA_TX_Buff[2] = crc_tmp;
                                
                                //
                                I2CA_TX_Buff[3] = FW_VERSION_PART1;
                                I2CA_TX_Buff[4] = FW_VERSION_PART2;
                                //crc_tmp = sensirion_common_generate(I2CA_TX_Buff+3,2);
                                crc_tmp = compute_crc8(I2CA_TX_Buff+3,2);
                                I2CA_TX_Buff[5] = crc_tmp;
                            }
                            
                            #if(defined(DEF_DELTA_RAW_EN)&&(DEF_DELTA_RAW_EN==1))
                            else if(Usr_Md_CmdCode1 == 0x1100)
                            {   // Read Usr_Delta_Raw;
                                g_iica0_tx_cnt = 3;
                                
                                I2CA_TX_Buff[0] = Usr_Delta_Raw>>8;
                                I2CA_TX_Buff[1] = Usr_Delta_Raw;
                                //crc_tmp = sensirion_common_generate(I2CA_TX_Buff,2);
                                crc_tmp = compute_crc8(I2CA_TX_Buff,2);
                                I2CA_TX_Buff[2] = crc_tmp;
                            }
                            #endif
                            
                            #if(defined(DEF_DELTA_PPM_EN)&&(DEF_DELTA_PPM_EN==1))
                            else if(Usr_Md_CmdCode1 == 0x1101)
                            {   // Read Usr_Delta_PPM1;
                                g_iica0_tx_cnt = 3;
                                
                                I2CA_TX_Buff[0] = Usr_Delta_PPM1>>8;
                                I2CA_TX_Buff[1] = Usr_Delta_PPM1;
                                //crc_tmp = sensirion_common_generate(I2CA_TX_Buff,2);
                                crc_tmp = compute_crc8(I2CA_TX_Buff,2);
                                I2CA_TX_Buff[2] = crc_tmp;
                            }
                            #endif
                            
                            #if(defined(DEF_CONCEN_THRE_EN)&&(DEF_CONCEN_THRE_EN==1))
                            else if(Usr_Md_CmdCode1 == 0x1102)
                            {   // Read DAC, Now Concen_Threshold
                                
                                g_iica0_tx_cnt = 3;
                                
                                I2CA_TX_Buff[0] = Concen_Threshold>>8;
                                I2CA_TX_Buff[1] = Concen_Threshold;
                                //crc_tmp = sensirion_common_generate(I2CA_TX_Buff,2);
                                crc_tmp = compute_crc8(I2CA_TX_Buff,2);
                                I2CA_TX_Buff[2] = crc_tmp;
                            }
                            #endif
                            else if(Usr_Md_CmdCode1 == 0x1103)
                            {   // Read HumComp_M2_S[DEF_HUMCOMP_PARAM_MAX];
                                
                                g_iica0_tx_cnt = 48;
                                
                                for(iica0_cnt1=0;iica0_cnt1<DEF_HUMCOMP_PARAM_MAX;iica0_cnt1++)
                                {
                                    iica_cnt2 = *((uint32_t*)(HumComp_M2_S+iica0_cnt1));
                                    
                                    I2CA_TX_Buff[0+6*iica0_cnt1] = iica_cnt2>>24;
                                    I2CA_TX_Buff[1+6*iica0_cnt1] = iica_cnt2>>16;;
                                    //crc_tmp = sensirion_common_generate(I2CA_TX_Buff,2);
                                    crc_tmp = compute_crc8(I2CA_TX_Buff+0+6*iica0_cnt1,2);
                                    I2CA_TX_Buff[2+6*iica0_cnt1] = crc_tmp;
                                    
                                    I2CA_TX_Buff[3+6*iica0_cnt1] = iica_cnt2>>8;
                                    I2CA_TX_Buff[4+6*iica0_cnt1] = iica_cnt2;;
                                    //crc_tmp = sensirion_common_generate(I2CA_TX_Buff,2);
                                    crc_tmp = compute_crc8(I2CA_TX_Buff+3+6*iica0_cnt1,2);
                                    I2CA_TX_Buff[5+6*iica0_cnt1] = crc_tmp;
                                }
                                
                            }
                            else if(Usr_Md_CmdCode1 == 0x1104)
                            {   // Read HumComp_Flag
                                
                                g_iica0_tx_cnt = 3;
                                
                                I2CA_TX_Buff[0] = HumComp_Flag>>8;
                                I2CA_TX_Buff[1] = HumComp_Flag;
                                //crc_tmp = sensirion_common_generate(I2CA_TX_Buff,2);
                                crc_tmp = compute_crc8(I2CA_TX_Buff,2);
                                I2CA_TX_Buff[2] = crc_tmp;
                            }
                            else if(Usr_Md_CmdCode1 == 0x1105)
                            {   // Read PresComp_K[DEF_PRESCOMP_PARAM_MAX];
                                
                                g_iica0_tx_cnt = 18;
                                
                                for(iica0_cnt1=0;iica0_cnt1<DEF_PRESCOMP_PARAM_MAX;iica0_cnt1++)
                                {
                                    iica_cnt2 = *((uint32_t*)(PresComp_K+iica0_cnt1));
                                    
                                    I2CA_TX_Buff[0+6*iica0_cnt1] = iica_cnt2>>24;
                                    I2CA_TX_Buff[1+6*iica0_cnt1] = iica_cnt2>>16;;
                                    //crc_tmp = sensirion_common_generate(I2CA_TX_Buff,2);
                                    crc_tmp = compute_crc8(I2CA_TX_Buff+0+6*iica0_cnt1,2);
                                    I2CA_TX_Buff[2+6*iica0_cnt1] = crc_tmp;
                                    
                                    I2CA_TX_Buff[3+6*iica0_cnt1] = iica_cnt2>>8;
                                    I2CA_TX_Buff[4+6*iica0_cnt1] = iica_cnt2;;
                                    //crc_tmp = sensirion_common_generate(I2CA_TX_Buff,2);
                                    crc_tmp = compute_crc8(I2CA_TX_Buff+3+6*iica0_cnt1,2);
                                    I2CA_TX_Buff[5+6*iica0_cnt1] = crc_tmp;
                                }
                                
                            }
                            else if(Usr_Md_CmdCode1 == 0x1106)
                            {   // Read PresComp_Flag
                                
                                g_iica0_tx_cnt = 3;
                                
                                I2CA_TX_Buff[0] = PresComp_Flag>>8;
                                I2CA_TX_Buff[1] = PresComp_Flag;
                                //crc_tmp = sensirion_common_generate(I2CA_TX_Buff,2);
                                crc_tmp = compute_crc8(I2CA_TX_Buff,2);
                                I2CA_TX_Buff[2] = crc_tmp;
                            }
                            else if(Usr_Md_CmdCode1 == 0x1108)
                            {   // Read SN2;
                                
                                #if 1
                                
                                g_iica0_tx_cnt = 6;
                                
                                I2CA_TX_Buff[0] = TimeSn_Time>>8;
                                I2CA_TX_Buff[1] = TimeSn_Time;
                                //crc_tmp = sensirion_common_generate(I2CA_TX_Buff,2);
                                crc_tmp = compute_crc8(I2CA_TX_Buff,2);
                                I2CA_TX_Buff[2] = crc_tmp;
                                
                                I2CA_TX_Buff[3] = TimeSn_SN>>8;
                                I2CA_TX_Buff[4] = TimeSn_SN;
                                //crc_tmp = sensirion_common_generate(I2CA_TX_Buff+3,2);
                                crc_tmp = compute_crc8(I2CA_TX_Buff+3,2);
                                I2CA_TX_Buff[5] = crc_tmp;
                                
                                #endif
                            }
                            else if(Usr_Md_CmdCode1 == 0x1109)
                            {   // Read Temperature compensation parameters;
                                
                                g_iica0_tx_cnt = 24;
                                
                                //P0 H16b;
                                I2CA_TX_Buff[0] = TComp_P0>>24;
                                I2CA_TX_Buff[1] = TComp_P0>>16;
                                //crc_tmp = sensirion_common_generate(I2CA_TX_Buff,2);
                                crc_tmp = compute_crc8(I2CA_TX_Buff,2);
                                I2CA_TX_Buff[2] = crc_tmp;
                                
                                //P0 L16b;
                                I2CA_TX_Buff[3] = TComp_P0>>8;
                                I2CA_TX_Buff[4] = TComp_P0;
                                //crc_tmp = sensirion_common_generate(I2CA_TX_Buff+3,2);
                                crc_tmp = compute_crc8(I2CA_TX_Buff+3,2);
                                I2CA_TX_Buff[5] = crc_tmp;
                                
                                //P1 H16b;
                                I2CA_TX_Buff[6] = TComp_P1>>24;
                                I2CA_TX_Buff[7] = TComp_P1>>16;
                                //crc_tmp = sensirion_common_generate(I2CA_TX_Buff,2);
                                crc_tmp = compute_crc8(I2CA_TX_Buff+6,2);
                                I2CA_TX_Buff[8] = crc_tmp;
                                
                                //P1 L16b;
                                I2CA_TX_Buff[9] = TComp_P1>>8;
                                I2CA_TX_Buff[10] = TComp_P1;
                                //crc_tmp = sensirion_common_generate(I2CA_TX_Buff+3,2);
                                crc_tmp = compute_crc8(I2CA_TX_Buff+9,2);
                                I2CA_TX_Buff[11] = crc_tmp;
                                
                                //P2 H16b;
                                I2CA_TX_Buff[12] = TComp_P2>>24;
                                I2CA_TX_Buff[13] = TComp_P2>>16;
                                //crc_tmp = sensirion_common_generate(I2CA_TX_Buff,2);
                                crc_tmp = compute_crc8(I2CA_TX_Buff+12,2);
                                I2CA_TX_Buff[14] = crc_tmp;
                                
                                //P2 L16b;
                                I2CA_TX_Buff[15] = TComp_P2>>8;
                                I2CA_TX_Buff[16] = TComp_P2;
                                //crc_tmp = sensirion_common_generate(I2CA_TX_Buff+3,2);
                                crc_tmp = compute_crc8(I2CA_TX_Buff+15,2);
                                I2CA_TX_Buff[17] = crc_tmp;
                                
                                //P3 H16b;
                                I2CA_TX_Buff[18] = TComp_P3>>24;
                                I2CA_TX_Buff[19] = TComp_P3>>16;
                                //crc_tmp = sensirion_common_generate(I2CA_TX_Buff,2);
                                crc_tmp = compute_crc8(I2CA_TX_Buff+18,2);
                                I2CA_TX_Buff[20] = crc_tmp;
                                
                                //P3 L16b;
                                I2CA_TX_Buff[21] = TComp_P3>>8;
                                I2CA_TX_Buff[22] = TComp_P3;
                                //crc_tmp = sensirion_common_generate(I2CA_TX_Buff+3,2);
                                crc_tmp = compute_crc8(I2CA_TX_Buff+21,2);
                                I2CA_TX_Buff[23] = crc_tmp;
                                
                                
                            }
                            else if(Usr_Md_CmdCode1 == 0x110C)
                            {   // Read Sens_TableY;
                                g_iica0_tx_cnt = 3*DEF_TABLE_MAX;
                                
                                for(iica0_cnt1=0;iica0_cnt1<DEF_TABLE_MAX;iica0_cnt1++)
                                {
                                    I2CA_TX_Buff[0+3*iica0_cnt1] = Sens_TableY[iica0_cnt1]>>8;
                                    I2CA_TX_Buff[1+3*iica0_cnt1] = Sens_TableY[iica0_cnt1];
                                    //crc_tmp = sensirion_common_generate(I2CA_TX_Buff,2);
                                    crc_tmp = compute_crc8((I2CA_TX_Buff+3*iica0_cnt1),2);
                                    I2CA_TX_Buff[2+3*iica0_cnt1] = crc_tmp;
                                }
                                
                            }
                            else if(Usr_Md_CmdCode1 == 0x110D)
                            {   // Read Sens_TableX;
                                g_iica0_tx_cnt = 3*DEF_TABLE_MAX;
                                
                                for(iica0_cnt1=0;iica0_cnt1<DEF_TABLE_MAX;iica0_cnt1++)
                                {
                                    I2CA_TX_Buff[0+3*iica0_cnt1] = Sens_TableX[iica0_cnt1]>>8;
                                    I2CA_TX_Buff[1+3*iica0_cnt1] = Sens_TableX[iica0_cnt1];
                                    //crc_tmp = sensirion_common_generate(I2CA_TX_Buff,2);
                                    crc_tmp = compute_crc8((I2CA_TX_Buff+3*iica0_cnt1),2);
                                    I2CA_TX_Buff[2+3*iica0_cnt1] = crc_tmp;
                                }
                                
                            }
                            else if(Usr_Md_CmdCode1 == 0x110E)
                            {   // Read Sens_CoolTime;
                                g_iica0_tx_cnt = 3;
                                
                                I2CA_TX_Buff[0] = Sens_CoolTime>>8;
                                I2CA_TX_Buff[1] = Sens_CoolTime;
                                //crc_tmp = sensirion_common_generate(I2CA_TX_Buff,2);
                                crc_tmp = compute_crc8(I2CA_TX_Buff,2);
                                I2CA_TX_Buff[2] = crc_tmp;
                            }
                            else if(Usr_Md_CmdCode1 == 0x110F)
                            {   // Read TComp_TRawBase;
                                g_iica0_tx_cnt = 3;
                                
                                I2CA_TX_Buff[0] = TComp_TRawBase>>8;
                                I2CA_TX_Buff[1] = TComp_TRawBase;
                                //crc_tmp = sensirion_common_generate(I2CA_TX_Buff,2);
                                crc_tmp = compute_crc8(I2CA_TX_Buff,2);
                                I2CA_TX_Buff[2] = crc_tmp;
                            }
                            else if(Usr_Md_CmdCode1 == 0x1110)
                            {   // Read Usr_PresComp_PBase
                                g_iica0_tx_cnt = 3;
                                
                                I2CA_TX_Buff[0] = PresComp_PBase>>8;
                                I2CA_TX_Buff[1] = PresComp_PBase;
                                //crc_tmp = sensirion_common_generate(I2CA_TX_Buff,2);
                                crc_tmp = compute_crc8(I2CA_TX_Buff,2);
                                I2CA_TX_Buff[2] = crc_tmp;
                            }
                            else if(Usr_Md_CmdCode1 == 0x1111)
                            {   // Read Sens_DC_Y;
                                g_iica0_tx_cnt = 3;
                                
                                I2CA_TX_Buff[0] = Sens_DC_Y>>8;
                                I2CA_TX_Buff[1] = Sens_DC_Y;
                                //crc_tmp = sensirion_common_generate(I2CA_TX_Buff,2);
                                crc_tmp = compute_crc8(I2CA_TX_Buff,2);
                                I2CA_TX_Buff[2] = crc_tmp;
                            }
                            else if(Usr_Md_CmdCode1 == 0x1113)
                            {   // Read FilterCnt;
                                g_iica0_tx_cnt = 3;
                                
                                I2CA_TX_Buff[0] = Sens_FilterCnt>>8;
                                I2CA_TX_Buff[1] = Sens_FilterCnt;
                                //crc_tmp = sensirion_common_generate(I2CA_TX_Buff,2);
                                crc_tmp = compute_crc8(I2CA_TX_Buff,2);
                                I2CA_TX_Buff[2] = crc_tmp;
                            }
                            else if(Usr_Md_CmdCode1 == 0x1114)
                            {   // Read Sens_PreHeatTime;
                                g_iica0_tx_cnt = 3;
                                
                                I2CA_TX_Buff[0] = Sens_PreHeatTime>>8;
                                I2CA_TX_Buff[1] = Sens_PreHeatTime;
                                crc_tmp = compute_crc8(I2CA_TX_Buff,2);
                                I2CA_TX_Buff[2] = crc_tmp;
                            }
                            else if(Usr_Md_CmdCode1 == 0x1115)
                            {   // Read TmpRate_P;
                                g_iica0_tx_cnt = 3;
                                
                                I2CA_TX_Buff[0] = TmpRate_P>>8;
                                I2CA_TX_Buff[1] = TmpRate_P;
                                crc_tmp = compute_crc8(I2CA_TX_Buff,2);
                                I2CA_TX_Buff[2] = crc_tmp;
                            }
                            #if(defined(DEF_HEAT_COMP2_EN)&&(DEF_HEAT_COMP2_EN==1))
                            else if(Usr_Md_CmdCode1 == 0x1121)
                            {   // Read HtComp_TRaw_Base_2;
                                g_iica0_tx_cnt = 3;
                                
                                I2CA_TX_Buff[0] = HtComp_TRaw_Base_2>>8;
                                I2CA_TX_Buff[1] = HtComp_TRaw_Base_2;
                                //crc_tmp = sensirion_common_generate(I2CA_TX_Buff,2);
                                crc_tmp = compute_crc8(I2CA_TX_Buff,2);
                                I2CA_TX_Buff[2] = crc_tmp;
                            }
                            else if(Usr_Md_CmdCode1 == 0x1122)
                            {   // Read HtComp_HtRaw_Base_2;
                                g_iica0_tx_cnt = 3;
                                
                                I2CA_TX_Buff[0] = HtComp_HtRaw_Base_2>>8;
                                I2CA_TX_Buff[1] = HtComp_HtRaw_Base_2;
                                //crc_tmp = sensirion_common_generate(I2CA_TX_Buff,2);
                                crc_tmp = compute_crc8(I2CA_TX_Buff,2);
                                I2CA_TX_Buff[2] = crc_tmp;
                            }
                            else if(Usr_Md_CmdCode1 == 0x1123)
                            {   // Read HtComp_Kh_2;
                                g_iica0_tx_cnt = 3;
                                
                                I2CA_TX_Buff[0] = HtComp_Kh_2>>8;
                                I2CA_TX_Buff[1] = HtComp_Kh_2;
                                //crc_tmp = sensirion_common_generate(I2CA_TX_Buff,2);
                                crc_tmp = compute_crc8(I2CA_TX_Buff,2);
                                I2CA_TX_Buff[2] = crc_tmp;
                            }
                            else if(Usr_Md_CmdCode1 == 0x1124)
                            {   // Read HtComp_SP_2;
                                g_iica0_tx_cnt = 3;
                                
                                I2CA_TX_Buff[0] = HtComp_SP_2>>8;
                                I2CA_TX_Buff[1] = HtComp_SP_2;
                                //crc_tmp = sensirion_common_generate(I2CA_TX_Buff,2);
                                crc_tmp = compute_crc8(I2CA_TX_Buff,2);
                                I2CA_TX_Buff[2] = crc_tmp;
                            }
                            else if(Usr_Md_CmdCode1 == 0x1125)
                            {   // Read HtComp_Ks_2;
                                g_iica0_tx_cnt = 3;
                                
                                I2CA_TX_Buff[0] = HtComp_Ks_2>>8;
                                I2CA_TX_Buff[1] = HtComp_Ks_2;
                                //crc_tmp = sensirion_common_generate(I2CA_TX_Buff,2);
                                crc_tmp = compute_crc8(I2CA_TX_Buff,2);
                                I2CA_TX_Buff[2] = crc_tmp;
                            }
                            else if(Usr_Md_CmdCode1 == 0x112F)
                            {   // Read HtComp function various parameters;
                                g_iica0_tx_cnt = 27;
                                
                                I2CA_TX_Buff[0] = Monitor_Raw1>>8;
                                I2CA_TX_Buff[1] = Monitor_Raw1;
                                //crc_tmp = sensirion_common_generate(I2CA_TX_Buff,2);
                                crc_tmp = compute_crc8(I2CA_TX_Buff+0,2);
                                I2CA_TX_Buff[2] = crc_tmp;
                                
                                I2CA_TX_Buff[3] = ExtSens_Tmpr_Raw>>8;
                                I2CA_TX_Buff[4] = ExtSens_Tmpr_Raw;
                                //crc_tmp = sensirion_common_generate(I2CA_TX_Buff,2);
                                crc_tmp = compute_crc8(I2CA_TX_Buff+3,2);
                                I2CA_TX_Buff[5] = crc_tmp;
                                
                                I2CA_TX_Buff[6] = HtComp_HtRaw_Base_rt_2>>8;
                                I2CA_TX_Buff[7] = HtComp_HtRaw_Base_rt_2;
                                //crc_tmp = sensirion_common_generate(I2CA_TX_Buff,2);
                                crc_tmp = compute_crc8(I2CA_TX_Buff+6,2);
                                I2CA_TX_Buff[8] = crc_tmp;
                                
                                I2CA_TX_Buff[9] = Dlt_P0>>8;
                                I2CA_TX_Buff[10] = Dlt_P0;
                                //crc_tmp = sensirion_common_generate(I2CA_TX_Buff,2);
                                crc_tmp = compute_crc8(I2CA_TX_Buff+9,2);
                                I2CA_TX_Buff[11] = crc_tmp;
                                
                                I2CA_TX_Buff[12] = Dlt_P>>8;
                                I2CA_TX_Buff[13] = Dlt_P;
                                //crc_tmp = sensirion_common_generate(I2CA_TX_Buff,2);
                                crc_tmp = compute_crc8(I2CA_TX_Buff+12,2);
                                I2CA_TX_Buff[14] = crc_tmp;
                                
                                I2CA_TX_Buff[15] = Delta_Ht_Raw_2>>8;
                                I2CA_TX_Buff[16] = Delta_Ht_Raw_2;
                                //crc_tmp = sensirion_common_generate(I2CA_TX_Buff,2);
                                crc_tmp = compute_crc8(I2CA_TX_Buff+15,2);
                                I2CA_TX_Buff[17] = crc_tmp;
                                
                                I2CA_TX_Buff[18] = Sens_Raw_After_TmpComp>>8;
                                I2CA_TX_Buff[19] = Sens_Raw_After_TmpComp;
                                //crc_tmp = sensirion_common_generate(I2CA_TX_Buff,2);
                                crc_tmp = compute_crc8(I2CA_TX_Buff+18,2);
                                I2CA_TX_Buff[20] = crc_tmp;
                                
                                I2CA_TX_Buff[21] = HtComp_CompTotal_2>>8;
                                I2CA_TX_Buff[22] = HtComp_CompTotal_2;
                                //crc_tmp = sensirion_common_generate(I2CA_TX_Buff,2);
                                crc_tmp = compute_crc8(I2CA_TX_Buff+21,2);
                                I2CA_TX_Buff[23] = crc_tmp;
                                
                                I2CA_TX_Buff[24] = Sens_Raw_After_HtComp>>8;
                                I2CA_TX_Buff[25] = Sens_Raw_After_HtComp;
                                //crc_tmp = sensirion_common_generate(I2CA_TX_Buff,2);
                                crc_tmp = compute_crc8(I2CA_TX_Buff+24,2);
                                I2CA_TX_Buff[26] = crc_tmp;
                            }
                            #endif
                            
                            else if(Usr_Md_CmdCode1 == 0x1130)
                            {   // Read ErrorData1;
                                g_iica0_tx_cnt = 3;
                                
                                I2CA_TX_Buff[0] = ErrorData1>>8;
                                I2CA_TX_Buff[1] = ErrorData1;
                                //crc_tmp = sensirion_common_generate(I2CA_TX_Buff,2);
                                crc_tmp = compute_crc8(I2CA_TX_Buff,2);
                                I2CA_TX_Buff[2] = crc_tmp;
                            }
                            
                            
                            #if(defined(DEF_ASC_EN)&&(DEF_ASC_EN==1))
                            else if(Usr_Md_CmdCode1 == 0x1140)
                            {   // Read ASC_Func_En;
                                g_iica0_tx_cnt = 3;
                                
                                I2CA_TX_Buff[0] = ASC_Func_En>>8;
                                I2CA_TX_Buff[1] = ASC_Func_En;
                                //crc_tmp = sensirion_common_generate(I2CA_TX_Buff,2);
                                crc_tmp = compute_crc8(I2CA_TX_Buff,2);
                                I2CA_TX_Buff[2] = crc_tmp;
                            }
                            else if(Usr_Md_CmdCode1 == 0x1141)
                            {   // Read ASC_PPM_HighTh;
                                g_iica0_tx_cnt = 3;
                                
                                I2CA_TX_Buff[0] = ASC_PPM_HighTh>>8;
                                I2CA_TX_Buff[1] = ASC_PPM_HighTh;
                                //crc_tmp = sensirion_common_generate(I2CA_TX_Buff,2);
                                crc_tmp = compute_crc8(I2CA_TX_Buff,2);
                                I2CA_TX_Buff[2] = crc_tmp;
                            }
                            else if(Usr_Md_CmdCode1 == 0x1142)
                            {   // Read ASC_PPM_LowTh;
                                g_iica0_tx_cnt = 3;
                                
                                I2CA_TX_Buff[0] = ASC_PPM_LowTh>>8;
                                I2CA_TX_Buff[1] = ASC_PPM_LowTh;
                                //crc_tmp = sensirion_common_generate(I2CA_TX_Buff,2);
                                crc_tmp = compute_crc8(I2CA_TX_Buff,2);
                                I2CA_TX_Buff[2] = crc_tmp;
                            }
                            else if(Usr_Md_CmdCode1 == 0x1143)
                            {   // Read ASC_Tmpr_RateTh;
                                g_iica0_tx_cnt = 3;
                                
                                I2CA_TX_Buff[0] = ASC_Tmpr_RateTh>>8;
                                I2CA_TX_Buff[1] = ASC_Tmpr_RateTh;
                                //crc_tmp = sensirion_common_generate(I2CA_TX_Buff,2);
                                crc_tmp = compute_crc8(I2CA_TX_Buff,2);
                                I2CA_TX_Buff[2] = crc_tmp;
                            }
                            else if(Usr_Md_CmdCode1 == 0x1144)
                            {   // Read ASC_Humi_RateTh;
                                g_iica0_tx_cnt = 3;
                                
                                I2CA_TX_Buff[0] = ASC_Humi_RateTh>>8;
                                I2CA_TX_Buff[1] = ASC_Humi_RateTh;
                                //crc_tmp = sensirion_common_generate(I2CA_TX_Buff,2);
                                crc_tmp = compute_crc8(I2CA_TX_Buff,2);
                                I2CA_TX_Buff[2] = crc_tmp;
                            }
                            else if(Usr_Md_CmdCode1 == 0x1145)
                            {   // Read ASC_Tmpr_Rt,ASC_Humi_Rt,ASC_Tmpr_RateMax30M,ASC_Humi_RateMax30M;
                                g_iica0_tx_cnt = 18;
                                
                                #if 0
                                if((ASC_Tmpr_Rt==0)||(ASC_Humi_Rt==1))
                                {
                                    PORT_ToggleBit(Usr_DBGIO4_PORT,Usr_DBGIO4_PIN);
                                }
                                #endif
                                
                                I2CA_TX_Buff[0] = ASC_Tmpr_Rt>>8;
                                I2CA_TX_Buff[1] = ASC_Tmpr_Rt;
                                //crc_tmp = sensirion_common_generate(I2CA_TX_Buff,2);
                                crc_tmp = compute_crc8(I2CA_TX_Buff+0*3,2);
                                I2CA_TX_Buff[2] = crc_tmp;
                                
                                I2CA_TX_Buff[3] = ASC_Humi_Rt>>8;
                                I2CA_TX_Buff[4] = ASC_Humi_Rt;
                                //crc_tmp = sensirion_common_generate(I2CA_TX_Buff,2);
                                crc_tmp = compute_crc8(I2CA_TX_Buff+1*3,2);
                                I2CA_TX_Buff[5] = crc_tmp;
                                
                                I2CA_TX_Buff[6] = ASC_Tmpr_RateMax30M>>8;
                                I2CA_TX_Buff[7] = ASC_Tmpr_RateMax30M;
                                //crc_tmp = sensirion_common_generate(I2CA_TX_Buff,2);
                                crc_tmp = compute_crc8(I2CA_TX_Buff+2*3,2);
                                I2CA_TX_Buff[8] = crc_tmp;
                                
                                I2CA_TX_Buff[9] = ASC_Humi_RateMax30M>>8;
                                I2CA_TX_Buff[10] = ASC_Humi_RateMax30M;
                                //crc_tmp = sensirion_common_generate(I2CA_TX_Buff,2);
                                crc_tmp = compute_crc8(I2CA_TX_Buff+3*3,2);
                                I2CA_TX_Buff[11] = crc_tmp;
                                
                                
                                I2CA_TX_Buff[12] = ASC_Tmpr_Rate>>8;
                                I2CA_TX_Buff[13] = ASC_Tmpr_Rate;
                                //crc_tmp = sensirion_common_generate(I2CA_TX_Buff,2);
                                crc_tmp = compute_crc8(I2CA_TX_Buff+3*4,2);
                                I2CA_TX_Buff[14] = crc_tmp;
                                
                                I2CA_TX_Buff[15] = ASC_Humi_Rate>>8;
                                I2CA_TX_Buff[16] = ASC_Humi_Rate;
                                //crc_tmp = sensirion_common_generate(I2CA_TX_Buff,2);
                                crc_tmp = compute_crc8(I2CA_TX_Buff+3*5,2);
                                I2CA_TX_Buff[17] = crc_tmp;
                                
                            }
                            else if(Usr_Md_CmdCode1 == 0x1146)
                            {   // Read ASC_Adjust_Cnt,ASC_Adjust_Value1,ASC_Adjust_Value2,ASC_Adjust_Value3;
                                g_iica0_tx_cnt = 12;
                                
                                I2CA_TX_Buff[0] = ASC_Adjust_Cnt>>8;
                                I2CA_TX_Buff[1] = ASC_Adjust_Cnt;
                                //crc_tmp = sensirion_common_generate(I2CA_TX_Buff,2);
                                crc_tmp = compute_crc8(I2CA_TX_Buff+0*3,2);
                                I2CA_TX_Buff[2] = crc_tmp;
                                
                                I2CA_TX_Buff[3] = (ASC_Adjust_Value[0])>>8;
                                I2CA_TX_Buff[4] = (ASC_Adjust_Value[0]);
                                //crc_tmp = sensirion_common_generate(I2CA_TX_Buff,2);
                                crc_tmp = compute_crc8(I2CA_TX_Buff+1*3,2);
                                I2CA_TX_Buff[5] = crc_tmp;
                                
                                I2CA_TX_Buff[6] = (ASC_Adjust_Value[1])>>8;
                                I2CA_TX_Buff[7] = (ASC_Adjust_Value[1]);
                                //crc_tmp = sensirion_common_generate(I2CA_TX_Buff,2);
                                crc_tmp = compute_crc8(I2CA_TX_Buff+2*3,2);
                                I2CA_TX_Buff[8] = crc_tmp;
                                
                                I2CA_TX_Buff[9] = (ASC_Adjust_Value[2])>>8;
                                I2CA_TX_Buff[10] = (ASC_Adjust_Value[2]);
                                //crc_tmp = sensirion_common_generate(I2CA_TX_Buff,2);
                                crc_tmp = compute_crc8(I2CA_TX_Buff+3*3,2);
                                I2CA_TX_Buff[11] = crc_tmp;
                                
                            }
                            #endif
                            
                            #endif
                            #if 1
                            else if((Usr_Md_CmdCode1 == 0x3615)&&(Usr_Md_CmdCode2 == 0xEC05))
                            {   // Read Product SN;
                                g_iica0_tx_cnt = 18;
                                
                                #if 0
                                I2CA_TX_Buff[0] = Usr_Product_Nbr[0];
                                
                                I2CA_TX_Buff[1] = Usr_Product_Nbr[1];
                                //crc_tmp = sensirion_common_generate(I2CA_TX_Buff,2);
                                crc_tmp = compute_crc8(I2CA_TX_Buff+0,2);
                                I2CA_TX_Buff[2] = crc_tmp;
                                
                                I2CA_TX_Buff[3] = Usr_Product_Nbr[2];
                                I2CA_TX_Buff[4] = Usr_Product_Nbr[3];
                                //crc_tmp = sensirion_common_generate(I2CA_TX_Buff,2);
                                crc_tmp = compute_crc8(I2CA_TX_Buff+3,2);
                                I2CA_TX_Buff[5] = crc_tmp;
                                #endif
                                
                                #if 1
                                I2CA_TX_Buff[0] = 0;
                                I2CA_TX_Buff[1] = FW_VERSION_PART0;
                                //crc_tmp = sensirion_common_generate(I2CA_TX_Buff,2);
                                crc_tmp = compute_crc8(I2CA_TX_Buff,2);
                                I2CA_TX_Buff[2] = crc_tmp;
                                
                                //
                                I2CA_TX_Buff[3] = FW_VERSION_PART1;
                                I2CA_TX_Buff[4] = FW_VERSION_PART2;
                                //crc_tmp = sensirion_common_generate(I2CA_TX_Buff+3,2);
                                crc_tmp = compute_crc8(I2CA_TX_Buff+3,2);
                                I2CA_TX_Buff[5] = crc_tmp;
                                #endif
                                
                                #if 0
                                I2CA_TX_Buff[6] = Usr_Serial_Nbr1[0];
                                I2CA_TX_Buff[7] = Usr_Serial_Nbr1[1];
                                //crc_tmp = sensirion_common_generate(I2CA_TX_Buff,2);
                                crc_tmp = compute_crc8(I2CA_TX_Buff+6,2);
                                I2CA_TX_Buff[8] = crc_tmp;
                                
                                I2CA_TX_Buff[9] = Usr_Serial_Nbr1[2];
                                I2CA_TX_Buff[10] = Usr_Serial_Nbr1[3];
                                //crc_tmp = sensirion_common_generate(I2CA_TX_Buff,2);
                                crc_tmp = compute_crc8(I2CA_TX_Buff+9,2);
                                I2CA_TX_Buff[11] = crc_tmp;
                                
                                I2CA_TX_Buff[12] = Usr_Serial_Nbr1[4];
                                I2CA_TX_Buff[13] = Usr_Serial_Nbr1[5];
                                //crc_tmp = sensirion_common_generate(I2CA_TX_Buff,2);
                                crc_tmp = compute_crc8(I2CA_TX_Buff+12,2);
                                I2CA_TX_Buff[14] = crc_tmp;
                                
                                I2CA_TX_Buff[15] = Usr_Serial_Nbr1[6];
                                I2CA_TX_Buff[16] = Usr_Serial_Nbr1[7];
                                //crc_tmp = sensirion_common_generate(I2CA_TX_Buff,2);
                                crc_tmp = compute_crc8(I2CA_TX_Buff+15,2);
                                I2CA_TX_Buff[17] = crc_tmp;
                                #endif
                                
                                
                                #if 1
                                I2CA_TX_Buff[6] = 0;
                                I2CA_TX_Buff[7] = 0;
                                //crc_tmp = sensirion_common_generate(I2CA_TX_Buff,2);
                                crc_tmp = compute_crc8(I2CA_TX_Buff+6,2);
                                I2CA_TX_Buff[8] = crc_tmp;
                                
                                I2CA_TX_Buff[9] = 0;
                                I2CA_TX_Buff[10] = 0;
                                //crc_tmp = sensirion_common_generate(I2CA_TX_Buff,2);
                                crc_tmp = compute_crc8(I2CA_TX_Buff+9,2);
                                I2CA_TX_Buff[11] = crc_tmp;
                                
                                I2CA_TX_Buff[12] = TimeSn_Time>>8;
                                I2CA_TX_Buff[13] = TimeSn_Time;
                                //crc_tmp = sensirion_common_generate(I2CA_TX_Buff,2);
                                crc_tmp = compute_crc8(I2CA_TX_Buff+12,2);
                                I2CA_TX_Buff[14] = crc_tmp;
                                
                                I2CA_TX_Buff[15] = TimeSn_SN>>8;
                                I2CA_TX_Buff[16] = TimeSn_SN;
                                //crc_tmp = sensirion_common_generate(I2CA_TX_Buff,2);
                                crc_tmp = compute_crc8(I2CA_TX_Buff+15,2);
                                I2CA_TX_Buff[17] = crc_tmp;
                                #endif
                                
                                
                            }
                            else if(Usr_Md_CmdCode1 == 0xEC05)
                            {   // Read Datas;
                                g_iica0_tx_cnt = 18;
                                
                                #if 0
                                I2CA_TX_Buff[0] = Sens_PPM_After_All>>8;
                                I2CA_TX_Buff[1] = Sens_PPM_After_All;
                                //crc_tmp = sensirion_common_generate(I2CA_TX_Buff,2);
                                crc_tmp = compute_crc8(I2CA_TX_Buff+0,2);
                                I2CA_TX_Buff[2] = crc_tmp;
                                #endif
                                
                                #if 1
                                I2CA_TX_Buff[0] = Sens_LFL_U16_Cust>>8;
                                I2CA_TX_Buff[1] = Sens_LFL_U16_Cust;
                                //crc_tmp = sensirion_common_generate(I2CA_TX_Buff,2);
                                crc_tmp = compute_crc8(I2CA_TX_Buff+0,2);
                                I2CA_TX_Buff[2] = crc_tmp;
                                #endif
                                
                                I2CA_TX_Buff[3] = ErrorData1_Cust>>8;
                                I2CA_TX_Buff[4] = ErrorData1_Cust;
                                //crc_tmp = sensirion_common_generate(I2CA_TX_Buff,2);
                                crc_tmp = compute_crc8(I2CA_TX_Buff+3,2);
                                I2CA_TX_Buff[5] = crc_tmp;
                                
                                I2CA_TX_Buff[6] = Psf_Gas_TypeCode_Cust>>8;
                                I2CA_TX_Buff[7] = Psf_Gas_TypeCode_Cust;
                                //crc_tmp = sensirion_common_generate(I2CA_TX_Buff,2);
                                crc_tmp = compute_crc8(I2CA_TX_Buff+6,2);
                                I2CA_TX_Buff[8] = crc_tmp;
                                
                                I2CA_TX_Buff[9] = TH_Sensor_Temperature_out_Cust>>8;
                                I2CA_TX_Buff[10] = TH_Sensor_Temperature_out_Cust;
                                //crc_tmp = sensirion_common_generate(I2CA_TX_Buff,2);
                                crc_tmp = compute_crc8(I2CA_TX_Buff+9,2);
                                I2CA_TX_Buff[11] = crc_tmp;
                                
                                I2CA_TX_Buff[12] = TH_Sensor_Humidity_out_Cust>>8;
                                I2CA_TX_Buff[13] = TH_Sensor_Humidity_out_Cust;
                                //crc_tmp = sensirion_common_generate(I2CA_TX_Buff,2);
                                crc_tmp = compute_crc8(I2CA_TX_Buff+12,2);
                                I2CA_TX_Buff[14] = crc_tmp;
                                
                                #if(defined(DEF_ASC_EN)&&(DEF_ASC_EN==1))
                                I2CA_TX_Buff[15] = ASC_Adjust_Total>>8;
                                I2CA_TX_Buff[16] = ASC_Adjust_Total;
                                //crc_tmp = sensirion_common_generate(I2CA_TX_Buff,2);
                                crc_tmp = compute_crc8(I2CA_TX_Buff+15,2);
                                I2CA_TX_Buff[17] = crc_tmp;
                                #else
                                I2CA_TX_Buff[15] = 0>>8;
                                I2CA_TX_Buff[16] = 0;
                                //crc_tmp = sensirion_common_generate(I2CA_TX_Buff,2);
                                crc_tmp = compute_crc8(I2CA_TX_Buff+15,2);
                                I2CA_TX_Buff[17] = crc_tmp;
                                #endif
                            }
                            #endif
                            else
                            {
                                
                            }
                            
                            Usr_Md_State = 3;
                        }
                        else
                        {
                            
                        }
                    }
                    #endif
                    if (g_iica0_tx_cnt > 0U)
                    {
                        IICA->IICA0 = *gp_iica0_tx_address;
                        gp_iica0_tx_address++;
                        g_iica0_tx_cnt--;
                        
                        g_iica0_tx_count++;
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
                if ((0U == (IICA->IICS0 & IICA_IICS0_ACKD_Msk)) && (g_iica0_tx_cnt != 0U))
                {
                    iica0_callback_slave_error(MD_NACK);
                }
                else
                {
                    if (g_iica0_tx_cnt > 0U)
                    {
                        IICA->IICA0 = *gp_iica0_tx_address;
                        gp_iica0_tx_address++;
                        g_iica0_tx_cnt--;
                        
                        g_iica0_tx_count++;
                    }
                    else
                    {
                        iica0_callback_slave_sendend();
                        IICA->IICCTL00 |= IICA_IICCTL00_WREL_Msk;  /* WREL0 = 1U: cancel wait */
                    }
                }
            }
            else
            {   // Read S5;
                g_iica0_slave_status_flag |= 2U;  /* receive flag */
                if (g_iica0_rx_cnt < g_iica0_rx_len)
                {
                    *gp_iica0_rx_address = IICA->IICA0;
                    gp_iica0_rx_address++;
                    g_iica0_rx_cnt++;
                    
                    #if(defined(DEF_I2C_TYPE)&&(DEF_I2C_TYPE==DEF_I2C_TYPE_PSF))
                    {   // Received datas;
                        if(g_iica0_rx_cnt == 1)
                        {
                            I2CA_Cmd_Code = gp_iica0_rx_address[-1];
                            
                            if(I2CA_Cmd_Code == 0xD0)
                            {
                                g_iica0_rx_len = 1;
                                
                                {
                                    I2CA_TX_Buff[0] = I2CA_TX_Buff[0]+1;
                                    I2CA_TX_Buff[1] = I2CA_TX_Buff[0]+1;
                                    I2CA_TX_Buff[2] = I2CA_TX_Buff[0]+2;
                                    I2CA_TX_Buff[3] = I2CA_TX_Buff[0]+3;
                                    I2CA_TX_Buff[4] = I2CA_TX_Buff[0]+4;
                                    I2CA_TX_Buff[5] = I2CA_TX_Buff[0]+5;
                                }
                            }
                            else if(I2CA_Cmd_Code == 0xE2)
                            {
                                g_iica0_rx_len = 1;
                                
                                {
                                    I2CA_TX_Buff[0] = 1;
                                    I2CA_TX_Buff[1] = TH_Sensor_Temperature_out>>8;
                                    I2CA_TX_Buff[2] = TH_Sensor_Temperature_out;
                                    I2CA_TX_Buff[3] = 3;
                                    I2CA_TX_Buff[4] = TH_Sensor_Temperature_out;
                                    I2CA_TX_Buff[5] = TH_Sensor_Temperature_out>>8;
                                    
                                }
                            }
                            else if(I2CA_Cmd_Code == 0xE3)
                            {
                                g_iica0_rx_len = 1;
                                
                                {
                                    I2CA_TX_Buff[0] = 1;
                                    I2CA_TX_Buff[1] = TH_Sensor_Humidity_out>>8;
                                    I2CA_TX_Buff[2] = TH_Sensor_Humidity_out;
                                    I2CA_TX_Buff[3] = 3;
                                    I2CA_TX_Buff[4] = TH_Sensor_Humidity_out;
                                    I2CA_TX_Buff[5] = TH_Sensor_Humidity_out>>8;
                                }
                            }
                            else
                            {
                                g_iica0_rx_len = DEF_I2CA_RX_MAX;
                            }
                        }
                    }
                    #endif
                    
                    
                    #if(defined(DEF_I2C_TYPE)&&(DEF_I2C_TYPE==DEF_I2C_TYPE_MIDEA))
                    if(g_iica0_rx_cnt == 1)
                    {
                        Usr_Md_Cmd1 = gp_iica0_rx_address[-1];
                        
                    }
                    else if(g_iica0_rx_cnt == 2)
                    {
                        Usr_Md_Cmd2 = gp_iica0_rx_address[-1];
                        Usr_Md_CmdCode0 = Usr_Md_Cmd1;
                        Usr_Md_CmdCode0 <<= 8;
                        Usr_Md_CmdCode0 += Usr_Md_Cmd2;
                        
                        if(Usr_Md_State == 0)
                        {   
                            if(1==0)
                            {
                                
                            }
                            #if 1
                            else if(Usr_Md_CmdCode0 == 0x1001)
                            {   // Read Raw;
                                Usr_Md_State = 2;
                                g_iica0_rx_len = 2;
                                Usr_Md_CmdCode1 = Usr_Md_CmdCode0;
                            }
                            else if(Usr_Md_CmdCode0 == 0x1002)
                            {   // Read Sens_PPM_After_Cali Sens_PPM_After_PrsComp Sens_PPM_After_All Sens_LFL_U16;
                                Usr_Md_State = 2;
                                g_iica0_rx_len = 2;
                                Usr_Md_CmdCode1 = Usr_Md_CmdCode0;
                            }
                            else if(Usr_Md_CmdCode0 == 0x1003)
                            {   // Read Usr_HumComp_PPMC_INT, dlt_ppm_pressure_int;
                                Usr_Md_State = 2;
                                g_iica0_rx_len = 2;
                                Usr_Md_CmdCode1 = Usr_Md_CmdCode0;
                            }
                            #if(defined(DEF_CONCEN_THRE_EN)&&(DEF_CONCEN_THRE_EN==1))
                            else if(Usr_Md_CmdCode0 == 0x1004)
                            {   // Read Flag_Concen_Threshol_Alarm;
                                Usr_Md_State = 2;
                                g_iica0_rx_len = 2;
                                Usr_Md_CmdCode1 = Usr_Md_CmdCode0;
                            }
                            #endif
                            
                            #if(defined(DEF_ADC_EN)&&(DEF_ADC_EN == 1))
                            else if(Usr_Md_CmdCode0 == 0x1005)
                            {   // Read Monitor_Raw1
                                Usr_Md_State = 2;
                                g_iica0_rx_len = 2;
                                Usr_Md_CmdCode1 = Usr_Md_CmdCode0;
                            }
                            #endif
                            else if(Usr_Md_CmdCode0 == 0x1006)
                            {   // Read Tmpr Humidity Pressure;
                                Usr_Md_State = 2;
                                g_iica0_rx_len = 2;
                                Usr_Md_CmdCode1 = Usr_Md_CmdCode0;
                            }
                            else if(Usr_Md_CmdCode0 == 0x100F)
                            {   // Read FW version;
                                Usr_Md_State = 2;
                                g_iica0_rx_len = 2;
                                Usr_Md_CmdCode1 = Usr_Md_CmdCode0;
                            }
                            
                            #if(defined(DEF_DELTA_RAW_EN)&&(DEF_DELTA_RAW_EN==1))
                            else if(Usr_Md_CmdCode0 == 0x1100)
                            {   // Read Usr_Delta_Raw;
                                Usr_Md_State = 2;
                                g_iica0_rx_len = 2;
                                Usr_Md_CmdCode1 = Usr_Md_CmdCode0;
                            }
                            #endif
                            
                            #if(defined(DEF_DELTA_PPM_EN)&&(DEF_DELTA_PPM_EN==1))
                            else if(Usr_Md_CmdCode0 == 0x1101)
                            {   // Read Usr_Delta_Raw;
                                Usr_Md_State = 2;
                                g_iica0_rx_len = 2;
                                Usr_Md_CmdCode1 = Usr_Md_CmdCode0;
                            }
                            #endif
                            
                            #if(defined(DEF_CONCEN_THRE_EN)&&(DEF_CONCEN_THRE_EN==1))
                            else if(Usr_Md_CmdCode0 == 0x1102)
                            {   // Read DAC; now concentration threshold value;
                                Usr_Md_State = 2;
                                g_iica0_rx_len = 2;
                                Usr_Md_CmdCode1 = Usr_Md_CmdCode0;
                            }
                            #endif
                            
                            else if(Usr_Md_CmdCode0 == 0x1103)
                            {   // Read HumComp_M1_S;
                                Usr_Md_State = 2;
                                g_iica0_rx_len = 2;
                                Usr_Md_CmdCode1 = Usr_Md_CmdCode0;
                            }
                            else if(Usr_Md_CmdCode0 == 0x1104)
                            {   // Read HumComp_Flag;
                                Usr_Md_State = 2;
                                g_iica0_rx_len = 2;
                                Usr_Md_CmdCode1 = Usr_Md_CmdCode0;
                            }
                            else if(Usr_Md_CmdCode0 == 0x1105)
                            {   // Read HumComp_K;
                                Usr_Md_State = 2;
                                g_iica0_rx_len = 2;
                                Usr_Md_CmdCode1 = Usr_Md_CmdCode0;
                            }
                            else if(Usr_Md_CmdCode0 == 0x1106)
                            {   // Read PresComp_Flag;
                                Usr_Md_State = 2;
                                g_iica0_rx_len = 2;
                                Usr_Md_CmdCode1 = Usr_Md_CmdCode0;
                            }
                            else if(Usr_Md_CmdCode0 == 0x1108)
                            {   // Read SN .
                                Usr_Md_State = 2;
                                g_iica0_rx_len = 2;
                                Usr_Md_CmdCode1 = Usr_Md_CmdCode0;
                            }
                            else if(Usr_Md_CmdCode0 == 0x1109)
                            {   // Read Temperature compensation parameters;
                                Usr_Md_State = 2;
                                g_iica0_rx_len = 2;
                                Usr_Md_CmdCode1 = Usr_Md_CmdCode0;
                            }
                            else if(Usr_Md_CmdCode0 == 0x110C)
                            {   // Read Sens_TableY;
                                Usr_Md_State = 2;
                                g_iica0_rx_len = 2;
                                Usr_Md_CmdCode1 = Usr_Md_CmdCode0;
                            }
                            else if(Usr_Md_CmdCode0 == 0x110D)
                            {   // Read Sens_TableX;
                                Usr_Md_State = 2;
                                g_iica0_rx_len = 2;
                                Usr_Md_CmdCode1 = Usr_Md_CmdCode0;
                            }
                            else if(Usr_Md_CmdCode0 == 0x110E)
                            {   // Read Sens_CoolTime;
                                Usr_Md_State = 2;
                                g_iica0_rx_len = 2;
                                Usr_Md_CmdCode1 = Usr_Md_CmdCode0;
                            }
                            else if(Usr_Md_CmdCode0 == 0x110F)
                            {   // Read TComp_TRawBase;
                                Usr_Md_State = 2;
                                g_iica0_rx_len = 2;
                                Usr_Md_CmdCode1 = Usr_Md_CmdCode0;
                            }
                            else if(Usr_Md_CmdCode0 == 0x1110)
                            {   // Read PresComp_PBase;
                                Usr_Md_State = 2;
                                g_iica0_rx_len = 2;
                                Usr_Md_CmdCode1 = Usr_Md_CmdCode0;
                            }
                            else if(Usr_Md_CmdCode0 == 0x1111)
                            {   // Read Sens_DC_Y;
                                Usr_Md_State = 2;
                                g_iica0_rx_len = 2;
                                Usr_Md_CmdCode1 = Usr_Md_CmdCode0;
                            }
                            else if(Usr_Md_CmdCode0 == 0x1113)
                            {   // Read FilterCnt;
                                Usr_Md_State = 2;
                                g_iica0_rx_len = 2;
                                Usr_Md_CmdCode1 = Usr_Md_CmdCode0;
                            }
                            else if(Usr_Md_CmdCode0 == 0x1114)
                            {   // Read Sens_PreHeatTime;
                                Usr_Md_State = 2;
                                g_iica0_rx_len = 2;
                                Usr_Md_CmdCode1 = Usr_Md_CmdCode0;
                            }
                            else if(Usr_Md_CmdCode0 == 0x1115)
                            {   // Read TmpRate_P;
                                Usr_Md_State = 2;
                                g_iica0_rx_len = 2;
                                Usr_Md_CmdCode1 = Usr_Md_CmdCode0;
                            }
                            
                            #if(defined(DEF_HEAT_COMP2_EN)&&(DEF_HEAT_COMP2_EN==1))
                            else if(Usr_Md_CmdCode0 == 0x1121)
                            {   // Read HtComp_TRaw_Base_2;
                                Usr_Md_State = 2;
                                g_iica0_rx_len = 2;
                                Usr_Md_CmdCode1 = Usr_Md_CmdCode0;
                            }
                            else if(Usr_Md_CmdCode0 == 0x1122)
                            {   // Read HtComp_HtRaw_Base_2;
                                Usr_Md_State = 2;
                                g_iica0_rx_len = 2;
                                Usr_Md_CmdCode1 = Usr_Md_CmdCode0;
                            }
                            else if(Usr_Md_CmdCode0 == 0x1123)
                            {   // Read HtComp_Kh_2;
                                Usr_Md_State = 2;
                                g_iica0_rx_len = 2;
                                Usr_Md_CmdCode1 = Usr_Md_CmdCode0;
                            }
                            else if(Usr_Md_CmdCode0 == 0x1124)
                            {   // Read HtComp_SP_2;
                                Usr_Md_State = 2;
                                g_iica0_rx_len = 2;
                                Usr_Md_CmdCode1 = Usr_Md_CmdCode0;
                            }
                            else if(Usr_Md_CmdCode0 == 0x1125)
                            {   // Read HtComp_Ks_2;
                                Usr_Md_State = 2;
                                g_iica0_rx_len = 2;
                                Usr_Md_CmdCode1 = Usr_Md_CmdCode0;
                            }
                            else if(Usr_Md_CmdCode0 == 0x112F)
                            {   // Read HtComp function various parameters;
                                Usr_Md_State = 2;
                                g_iica0_rx_len = 2;
                                Usr_Md_CmdCode1 = Usr_Md_CmdCode0;
                            }
                            #endif
                            
                            else if(Usr_Md_CmdCode0 == 0x1130)
                            {   // Read ErrorData1;
                                Usr_Md_State = 2;
                                g_iica0_rx_len = 2;
                                Usr_Md_CmdCode1 = Usr_Md_CmdCode0;
                            }
                            
                            #if(defined(DEF_ASC_EN)&&(DEF_ASC_EN==1))
                            else if(Usr_Md_CmdCode0 == 0x1140)
                            {   // Read ASC_Func_En;
                                Usr_Md_State = 2;
                                g_iica0_rx_len = 2;
                                Usr_Md_CmdCode1 = Usr_Md_CmdCode0;
                            }
                            else if(Usr_Md_CmdCode0 == 0x1141)
                            {   // Read ASC_PPM_HighTh;
                                Usr_Md_State = 2;
                                g_iica0_rx_len = 2;
                                Usr_Md_CmdCode1 = Usr_Md_CmdCode0;
                            }
                            else if(Usr_Md_CmdCode0 == 0x1142)
                            {   // Read ASC_PPM_LowTh;
                                Usr_Md_State = 2;
                                g_iica0_rx_len = 2;
                                Usr_Md_CmdCode1 = Usr_Md_CmdCode0;
                            }
                            else if(Usr_Md_CmdCode0 == 0x1143)
                            {   // Read ASC_Tmpr_RateTh;
                                Usr_Md_State = 2;
                                g_iica0_rx_len = 2;
                                Usr_Md_CmdCode1 = Usr_Md_CmdCode0;
                            }
                            else if(Usr_Md_CmdCode0 == 0x1144)
                            {   // Read ASC_Humi_RateTh;
                                Usr_Md_State = 2;
                                g_iica0_rx_len = 2;
                                Usr_Md_CmdCode1 = Usr_Md_CmdCode0;
                            }
                            else if(Usr_Md_CmdCode0 == 0x1145)
                            {   // Read ASC_Tmpr_Rt,ASC_Humi_Rt,ASC_Tmpr_RateMax30M,ASC_Humi_RateMax30M;
                                Usr_Md_State = 2;
                                g_iica0_rx_len = 2;
                                Usr_Md_CmdCode1 = Usr_Md_CmdCode0;
                            }
                            else if(Usr_Md_CmdCode0 == 0x1146)
                            {   // Read ASC_Adjust_Cnt,ASC_Adjust_Value1,ASC_Adjust_Value2,ASC_Adjust_Value3;
                                Usr_Md_State = 2;
                                g_iica0_rx_len = 2;
                                Usr_Md_CmdCode1 = Usr_Md_CmdCode0;
                            }
                            #endif
                            
                            #if(defined(DEF_DELTA_RAW_EN)&&(DEF_DELTA_RAW_EN==1))
                            else if(Usr_Md_CmdCode0 == 0x1180)
                            {   // Write Usr_Delta_Raw;
                                Usr_Md_State = 2;
                                g_iica0_rx_len = 5;
                                Usr_Md_CmdCode1 = Usr_Md_CmdCode0;
                            }
                            #endif
                            
                            #if(defined(DEF_DELTA_PPM_EN)&&(DEF_DELTA_PPM_EN==1))
                            else if(Usr_Md_CmdCode0 == 0x1181)
                            {   // Write Usr_Delta_PPM1;
                                Usr_Md_State = 2;
                                g_iica0_rx_len = 5;
                                Usr_Md_CmdCode1 = Usr_Md_CmdCode0;
                            }
                            #endif
                            
                            #if(defined(DEF_CONCEN_THRE_EN)&&(DEF_CONCEN_THRE_EN==1))
                            else if(Usr_Md_CmdCode0 == 0x1182)
                            {   // Write now concentration threshold value;
                                Usr_Md_State = 2;
                                g_iica0_rx_len = 5;
                                Usr_Md_CmdCode1 = Usr_Md_CmdCode0;
                            }
                            #endif
                            else if(Usr_Md_CmdCode0 == 0x1183)
                            {   // Write HumComp_M2_S.
                                Usr_Md_State = 2;
                                g_iica0_rx_len = 50;
                                Usr_Md_CmdCode1 = Usr_Md_CmdCode0;
                            }
                            else if(Usr_Md_CmdCode0 == 0x1184)
                            {   // Write HumComp_Flag.
                                Usr_Md_State = 2;
                                g_iica0_rx_len = 5;
                                Usr_Md_CmdCode1 = Usr_Md_CmdCode0;
                            }
                            else if(Usr_Md_CmdCode0 == 0x1185)
                            {   // Write HumComp_K.
                                Usr_Md_State = 2;
                                g_iica0_rx_len = 20;
                                Usr_Md_CmdCode1 = Usr_Md_CmdCode0;
                            }
                            else if(Usr_Md_CmdCode0 == 0x1186)
                            {   // Write PresComp_Flag.
                                Usr_Md_State = 2;
                                g_iica0_rx_len = 5;
                                Usr_Md_CmdCode1 = Usr_Md_CmdCode0;
                            }
                            else if(Usr_Md_CmdCode0 == 0x1188)
                            {   // Write SN .
                                Usr_Md_State = 2;
                                g_iica0_rx_len = 8;
                                Usr_Md_CmdCode1 = Usr_Md_CmdCode0;
                            }
                            else if(Usr_Md_CmdCode0 == 0x1189)
                            {   // Write temperature compensation parameters;
                                Usr_Md_State = 2;
                                g_iica0_rx_len = 26;
                                Usr_Md_CmdCode1 = Usr_Md_CmdCode0;
                            }
                            else if(Usr_Md_CmdCode0 == 0x118C)
                            {   // Write Sens_TableY;
                                Usr_Md_State = 2;
                                g_iica0_rx_len = 35;
                                Usr_Md_CmdCode1 = Usr_Md_CmdCode0;
                            }
                            else if(Usr_Md_CmdCode0 == 0x118D)
                            {   // Write Sens_TableX;
                                Usr_Md_State = 2;
                                g_iica0_rx_len = 35;
                                Usr_Md_CmdCode1 = Usr_Md_CmdCode0;
                            }
                            else if(Usr_Md_CmdCode0 == 0x118E)
                            {   // Write Sens_CoolTime;
                                Usr_Md_State = 2;
                                g_iica0_rx_len = 5;
                                Usr_Md_CmdCode1 = Usr_Md_CmdCode0;
                            }
                            else if(Usr_Md_CmdCode0 == 0x118F)
                            {   // Write TComp_TRawBase;
                                Usr_Md_State = 2;
                                g_iica0_rx_len = 5;
                                Usr_Md_CmdCode1 = Usr_Md_CmdCode0;
                            }
                            else if(Usr_Md_CmdCode0 == 0x1190)
                            {   // Write PresComp_PBase;
                                Usr_Md_State = 2;
                                g_iica0_rx_len = 5;
                                Usr_Md_CmdCode1 = Usr_Md_CmdCode0;
                            }
                            else if(Usr_Md_CmdCode0 == 0x1191)
                            {   // Write Sens_DC_Y;
                                Usr_Md_State = 2;
                                g_iica0_rx_len = 5;
                                Usr_Md_CmdCode1 = Usr_Md_CmdCode0;
                            }
                            //else if(Usr_Md_CmdCode0 == 0x1293)
                            else if(Usr_Md_CmdCode0 == 0x1193)
                            {   // Write FilterCnt;
                                Usr_Md_State = 2;
                                g_iica0_rx_len = 5;
                                Usr_Md_CmdCode1 = Usr_Md_CmdCode0;
                            }
                            else if(Usr_Md_CmdCode0 == 0x1194)
                            {   // Write Sens_PreHeatTime;
                                Usr_Md_State = 2;
                                g_iica0_rx_len = 5;
                                Usr_Md_CmdCode1 = Usr_Md_CmdCode0;
                            }
                            else if(Usr_Md_CmdCode0 == 0x1195)
                            {   // Write TmpRate_P;
                                Usr_Md_State = 2;
                                g_iica0_rx_len = 5;
                                Usr_Md_CmdCode1 = Usr_Md_CmdCode0;
                            }
                            #endif
                            
                            #if(defined(DEF_HEAT_COMP2_EN)&&(DEF_HEAT_COMP2_EN==1))
                            else if(Usr_Md_CmdCode0 == 0x11A1)
                            {   // Write HtComp_TRaw_Base_2;
                                Usr_Md_State = 2;
                                g_iica0_rx_len = 5;
                                Usr_Md_CmdCode1 = Usr_Md_CmdCode0;
                            }
                            else if(Usr_Md_CmdCode0 == 0x11A2)
                            {   // Write HtComp_HtRaw_Base_2;
                                Usr_Md_State = 2;
                                g_iica0_rx_len = 5;
                                Usr_Md_CmdCode1 = Usr_Md_CmdCode0;
                            }
                            else if(Usr_Md_CmdCode0 == 0x11A3)
                            {   // Write HtComp_Kh_2;
                                Usr_Md_State = 2;
                                g_iica0_rx_len = 5;
                                Usr_Md_CmdCode1 = Usr_Md_CmdCode0;
                            }
                            else if(Usr_Md_CmdCode0 == 0x11A4)
                            {   // Write HtComp_SP_2;
                                Usr_Md_State = 2;
                                g_iica0_rx_len = 5;
                                Usr_Md_CmdCode1 = Usr_Md_CmdCode0;
                            }
                            else if(Usr_Md_CmdCode0 == 0x11A5)
                            {   // Write HtComp_Ks_2;
                                Usr_Md_State = 2;
                                g_iica0_rx_len = 5;
                                Usr_Md_CmdCode1 = Usr_Md_CmdCode0;
                            }
                            #endif
                            
                            else if(Usr_Md_CmdCode0 == 0x11B0)
                            {   // Write HtComp_Ks_2;
                                Usr_Md_State = 2;
                                g_iica0_rx_len = 5;
                                Usr_Md_CmdCode1 = Usr_Md_CmdCode0;
                            }
                            
                            #if(defined(DEF_ASC_EN)&&(DEF_ASC_EN==1))
                            else if(Usr_Md_CmdCode0 == 0x11C0)
                            {   // Write ASC_Func_En;
                                Usr_Md_State = 2;
                                g_iica0_rx_len = 5;
                                Usr_Md_CmdCode1 = Usr_Md_CmdCode0;
                            }
                            else if(Usr_Md_CmdCode0 == 0x11C1)
                            {   // Write ASC_PPM_HighTh;
                                Usr_Md_State = 2;
                                g_iica0_rx_len = 5;
                                Usr_Md_CmdCode1 = Usr_Md_CmdCode0;
                            }
                            else if(Usr_Md_CmdCode0 == 0x11C2)
                            {   // Write ASC_PPM_LowTh;
                                Usr_Md_State = 2;
                                g_iica0_rx_len = 5;
                                Usr_Md_CmdCode1 = Usr_Md_CmdCode0;
                            }
                            else if(Usr_Md_CmdCode0 == 0x11C3)
                            {   // Write ASC_Tmpr_RateTh;
                                Usr_Md_State = 2;
                                g_iica0_rx_len = 5;
                                Usr_Md_CmdCode1 = Usr_Md_CmdCode0;
                            }
                            else if(Usr_Md_CmdCode0 == 0x11C4)
                            {   // Write ASC_Humi_RateTh;
                                Usr_Md_State = 2;
                                g_iica0_rx_len = 5;
                                Usr_Md_CmdCode1 = Usr_Md_CmdCode0;
                            }
                            else if(Usr_Md_CmdCode0 == 0x11C6)
                            {   // Write ASC_Adjust_Cnt,ASC_Adjust_Value1,ASC_Adjust_Value2,ASC_Adjust_Value3;
                                Usr_Md_State = 2;
                                g_iica0_rx_len = 14;
                                Usr_Md_CmdCode1 = Usr_Md_CmdCode0;
                            }
                            #endif
                            
                            // 
                            else if(Usr_Md_CmdCode0 == 0x3615)
                            {   // Read SN Cmd1;
                                Usr_Md_State = 1;
                                g_iica0_rx_len = 2;
                                Usr_Md_CmdCode1 = Usr_Md_CmdCode0;
                            }
                            else if(Usr_Md_CmdCode0 == 0x3608)
                            {   // Write Gas Type;
                                Usr_Md_State = 2;
                                g_iica0_rx_len = 5;
                                Usr_Md_CmdCode1 = Usr_Md_CmdCode0;
                            }
                            else if(Usr_Md_CmdCode0 == 0x3603)
                            {   // Write Start Meaurement;
                                Usr_Md_State = 2;
                                g_iica0_rx_len = 2;
                                Usr_Md_CmdCode1 = Usr_Md_CmdCode0;
                            }
                            
                            #if(defined(DEF_I2CRST1_EN)&&(DEF_I2CRST1_EN==1))
                            else if(Usr_Md_CmdCode0==0x3606)
                            {   // Write Reset Cmd;
                                Usr_Md_State = 2;
                                g_iica0_rx_len = 2;
                                Usr_Md_CmdCode1 = Usr_Md_CmdCode0;
                            }
                            #endif
                            else if(Usr_Md_CmdCode0 == 0xEC05)
                            {   // Read Datas;
                                Usr_Md_State = 2;
                                g_iica0_rx_len = 2;
                                Usr_Md_CmdCode1 = Usr_Md_CmdCode0;
                            }
                            else
                            {
                                Usr_Md_State = 0;
                                g_iica0_rx_len = DEF_I2CA_RX_MAX;
                            }
                        }
                        else if(Usr_Md_State == 1)
                        {
                            if(Usr_Md_CmdCode0 == 0xEC05)
                            {
                                Usr_Md_State = 2;
                                //g_iica0_rx_len = 20;
                                g_iica0_rx_len = 2;
                                Usr_Md_CmdCode2 = Usr_Md_CmdCode0;
                            }
                        }
                        else
                        {
                            
                        }
                    }
                    else
                    {
                        
                    }
                    
                    #endif
                    
                    #if(defined(DEF_I2C_TYPE)&&(DEF_I2C_TYPE==DEF_I2C_TYPE_PSF))
                    
                    #endif
                    
                    if (g_iica0_rx_cnt == g_iica0_rx_len)
                    {
                        IICA->IICCTL00 |= IICA_IICCTL00_WTIM_Msk;   /* WTIM0 = 1:  interrupt request is generated at the ninth clock's falling edge */
                        IICA->IICCTL00 |= IICA_IICCTL00_WREL_Msk;   /* WREL0 = 1U: cancel wait */
                        iica0_callback_slave_receiveend();
                        
                    }
                    else
                    {
                        IICA->IICCTL00 |=  IICA_IICCTL00_WREL_Msk;   /* WREL0 = 1U: cancel wait */
                    }
                }
                else
                {
                    IICA->IICCTL00 |=  IICA_IICCTL00_WREL_Msk;   /* WREL0 = 1U: cancel wait */
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
