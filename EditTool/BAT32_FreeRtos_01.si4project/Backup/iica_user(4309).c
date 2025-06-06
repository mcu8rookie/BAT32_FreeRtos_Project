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
    
    PORT_ToggleBit(Usr_DBGIO4_PORT,Usr_DBGIO4_PIN);
    
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
                #endif
                else if(Usr_Md_CmdCode1==0x3608)
                {
                    I2CA_RX_Cnt = g_iica0_rx_cnt;
                    
                    for(I2CA_RX_Cnt=0;I2CA_RX_Cnt<g_iica0_rx_cnt;I2CA_RX_Cnt++)
                    {
                        I2CA_RX_Buff2[I2CA_RX_Cnt] = I2CA_RX_Buff[I2CA_RX_Cnt];
                    }
                    
                    I2CA_WR_Flag = 1;
                }
                else if(Usr_Md_CmdCode1==0x3603)
                {
                    I2CA_RX_Cnt = g_iica0_rx_cnt;
                    
                    for(I2CA_RX_Cnt=0;I2CA_RX_Cnt<g_iica0_rx_cnt;I2CA_RX_Cnt++)
                    {
                        I2CA_RX_Buff2[I2CA_RX_Cnt] = I2CA_RX_Buff[I2CA_RX_Cnt];
                    }
                    
                    I2CA_WR_Flag = 1;
                }
                
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
                                I2CA_TX_Buff[3] = Sens_SRaw>>8;
                                I2CA_TX_Buff[4] = Sens_SRaw;
                                //crc_tmp = sensirion_common_generate(I2CA_TX_Buff+3,2);
                                crc_tmp = compute_crc8(I2CA_TX_Buff+3,2);
                                I2CA_TX_Buff[5] = crc_tmp;
                                
                                //Sens_SRawComp;
                                I2CA_TX_Buff[6] = Sens_SRawComp>>8;
                                I2CA_TX_Buff[7] = Sens_SRawComp;
                                //crc_tmp = sensirion_common_generate(I2CA_TX_Buff+6,2);
                                crc_tmp = compute_crc8(I2CA_TX_Buff+6,2);
                                I2CA_TX_Buff[8] = crc_tmp;
                                
                                
                            }
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
                            else if(Usr_Md_CmdCode1 == 0x1108)
                            {   // Read SN2;
                                g_iica0_tx_cnt = 12;
                                
                                I2CA_TX_Buff[0] = YearMonthDateSN[0];
                                I2CA_TX_Buff[1] = YearMonthDateSN[1];
                                //crc_tmp = sensirion_common_generate(I2CA_TX_Buff,2);
                                crc_tmp = compute_crc8(I2CA_TX_Buff,2);
                                I2CA_TX_Buff[2] = crc_tmp;
                                
                                I2CA_TX_Buff[3] = YearMonthDateSN[3];
                                I2CA_TX_Buff[4] = YearMonthDateSN[4];
                                //crc_tmp = sensirion_common_generate(I2CA_TX_Buff+3,2);
                                crc_tmp = compute_crc8(I2CA_TX_Buff+3,2);
                                I2CA_TX_Buff[5] = crc_tmp;
                                
                                I2CA_TX_Buff[6] = YearMonthDateSN[6];
                                I2CA_TX_Buff[7] = YearMonthDateSN[7];
                                //crc_tmp = sensirion_common_generate(I2CA_TX_Buff+6,2);
                                crc_tmp = compute_crc8(I2CA_TX_Buff+6,2);
                                I2CA_TX_Buff[8] = crc_tmp;
                                
                                I2CA_TX_Buff[9] = YearMonthDateSN[9];
                                I2CA_TX_Buff[10] = YearMonthDateSN[10];
                                //crc_tmp = sensirion_common_generate(I2CA_TX_Buff+9,2);
                                crc_tmp = compute_crc8(I2CA_TX_Buff+9,2);
                                I2CA_TX_Buff[11] = crc_tmp;
                                
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
                            else if(Usr_Md_CmdCode1 == 0x1113)
                            {   // Read FilterCnt;
                                g_iica0_tx_cnt = 3;
                                
                                I2CA_TX_Buff[0] = Sens_FilterCnt>>8;
                                I2CA_TX_Buff[1] = Sens_FilterCnt;
                                //crc_tmp = sensirion_common_generate(I2CA_TX_Buff,2);
                                crc_tmp = compute_crc8(I2CA_TX_Buff,2);
                                I2CA_TX_Buff[2] = crc_tmp;
                            }
                            #endif
                            #if 1
                            else if((Usr_Md_CmdCode1 == 0x3615)&&(Usr_Md_CmdCode2 == 0xEC05))
                            {
                                g_iica0_tx_cnt = 18;
                                
                                I2CA_TX_Buff[0] = Usr_Product_Nbr[0];
                                I2CA_TX_Buff[1] = Usr_Product_Nbr[1];
                                I2CA_TX_Buff[2] = Usr_SnCrc1;
                                I2CA_TX_Buff[3] = Usr_Product_Nbr[2];
                                I2CA_TX_Buff[4] = Usr_Product_Nbr[3];
                                I2CA_TX_Buff[5] = Usr_SnCrc2;
                                I2CA_TX_Buff[6] = Usr_Serial_Nbr1[0];
                                I2CA_TX_Buff[7] = Usr_Serial_Nbr1[1];
                                I2CA_TX_Buff[8] = Usr_SnCrc3;
                                I2CA_TX_Buff[9] = Usr_Serial_Nbr1[2];
                                I2CA_TX_Buff[10] = Usr_Serial_Nbr1[3];
                                I2CA_TX_Buff[11] = Usr_SnCrc4;
                                I2CA_TX_Buff[12] = Usr_Serial_Nbr2[0];
                                I2CA_TX_Buff[13] = Usr_Serial_Nbr2[1];
                                I2CA_TX_Buff[14] = Usr_SnCrc5;
                                I2CA_TX_Buff[15] = Usr_Serial_Nbr2[2];
                                I2CA_TX_Buff[16] = Usr_Serial_Nbr2[3];
                                I2CA_TX_Buff[17] = Usr_SnCrc6;
                                
                            }
                            else if(Usr_Md_CmdCode1 == 0xEC05)
                            {
                                g_iica0_tx_cnt = 18;
                                
                                I2CA_TX_Buff[0] = Mcu_Time1s_Cnt;
                                I2CA_TX_Buff[1] = Mcu_Time1s_Cnt;
                                crc_tmp = sensirion_common_generate(I2CA_TX_Buff,2);
                                I2CA_TX_Buff[2] = crc_tmp;
                                I2CA_TX_Buff[3] = Mcu_Time1s_Cnt;
                                I2CA_TX_Buff[4] = Mcu_Time1s_Cnt;
                                crc_tmp = sensirion_common_generate(I2CA_TX_Buff+3,2);
                                I2CA_TX_Buff[5] = crc_tmp;
                                I2CA_TX_Buff[6] = Psf_Gas_TypeCode>>8;
                                I2CA_TX_Buff[7] = Psf_Gas_TypeCode;
                                crc_tmp = sensirion_common_generate(I2CA_TX_Buff+6,2);
                                I2CA_TX_Buff[8] = crc_tmp;
                                I2CA_TX_Buff[9] = Mcu_Time1s_Cnt;
                                I2CA_TX_Buff[10] = Mcu_Time1s_Cnt;
                                crc_tmp = sensirion_common_generate(I2CA_TX_Buff+9,2);
                                I2CA_TX_Buff[11] = crc_tmp;
                                I2CA_TX_Buff[12] = Mcu_Time1s_Cnt;
                                I2CA_TX_Buff[13] = Mcu_Time1s_Cnt;
                                crc_tmp = sensirion_common_generate(I2CA_TX_Buff+12,2);
                                I2CA_TX_Buff[14] = crc_tmp;
                                I2CA_TX_Buff[15] = Mcu_Time1s_Cnt;
                                I2CA_TX_Buff[16] = Mcu_Time1s_Cnt;
                                crc_tmp = sensirion_common_generate(I2CA_TX_Buff+15,2);
                                I2CA_TX_Buff[17] = crc_tmp;
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
                            else if(Usr_Md_CmdCode0 == 0x1006)
                            {   // Read Tmpr Humidity Pressure;
                                Usr_Md_State = 2;
                                g_iica0_rx_len = 2;
                                Usr_Md_CmdCode1 = Usr_Md_CmdCode0;
                            }
                            else if(Usr_Md_CmdCode0 == 0x1108)
                            {   // Read SN Cmd1. CmdCode = 0x1108.
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
                            else if(Usr_Md_CmdCode0 == 0x1113)
                            {   // Read FilterCnt;
                                Usr_Md_State = 2;
                                g_iica0_rx_len = 2;
                                Usr_Md_CmdCode1 = Usr_Md_CmdCode0;
                            }
                            else if(Usr_Md_CmdCode0 == 0x1188)
                            {   // Write SN Cmd1. CmdCode = 0x1188.
                                Usr_Md_State = 2;
                                g_iica0_rx_len = 14;
                                Usr_Md_CmdCode1 = Usr_Md_CmdCode0;
                            }
                            else if(Usr_Md_CmdCode0 == 0x1189)
                            {   // Write temperature compensation parameters;
                                Usr_Md_State = 2;
                                g_iica0_rx_len = 26;
                                Usr_Md_CmdCode1 = Usr_Md_CmdCode0;
                            }
                            //else if(Usr_Md_CmdCode0 == 0x1293)
                            else if(Usr_Md_CmdCode0 == 0x1193)
                            {   // Write FilterCnt;
                                Usr_Md_State = 2;
                                g_iica0_rx_len = 5;
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
