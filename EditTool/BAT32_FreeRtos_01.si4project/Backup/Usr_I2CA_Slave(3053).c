#ifndef __USR_I2CA_SLAVE_C__
#define __USR_I2CA_SLAVE_C__


#include <stdint.h>

#include "Usr_Config.h"
#include "Usr_Debug.h"
#include "Usr_Psf.h"
#include "Usr_DataFlash.h"

#include "userdefine.h"
#include "BAT32A237.h"
#include "iica.h"

#include "Usr_Debug.h"

#include "Usr_I2CA_Slave.h"

#include"Usr_Main.h"

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

uint8_t I2CA_RX_Cnt;
uint8_t I2CA_RX_Buff2[DEF_I2CA_RX_MAX];


uint8_t YearMonthDateSN[12] = 
{
    DEF_YMDSN_YEAR1,
    DEF_YMDSN_YEAR2,
    DEF_YMDSN_CRC1,
    
    DEF_YMDSN_MONTH,
    DEF_YMDSN_DATE,
    DEF_YMDSN_CRC2,
    
    DEF_YMDSN_SN1,
    DEF_YMDSN_SN2,
    DEF_YMDSN_CRC3,
    
    DEF_YMDSN_SN3,
    DEF_YMDSN_SN4,
    DEF_YMDSN_CRC4,
    
};

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
    g_iica0_rx_len = DEF_I2CA_RX_MAX;             /* iica0 receive data length */
    g_iica0_rx_cnt = 0;             /* iica0 receive data count */
    g_iica0_rx_end = 0;             /* iica0 receive data end */
    
    gp_iica0_tx_address = I2CA_TX_Buff;        /* iica0 send buffer address */
    g_iica0_tx_cnt = 0;             /* iica0 send data count */
    g_iica0_tx_end = 0;             /* iica0 send data end */
    
    g_iica0_tx_count = 0;
    
    I2CA_WR_Flag = 0;
    I2CA_Cmd_Flag = 0;
    I2CA_Cmd_Code = 0;
    
    Usr_SnCrc1 = sensirion_common_generate(Usr_Product_Nbr,2);
    Usr_SnCrc2 = sensirion_common_generate(Usr_Product_Nbr+2,2);
    Usr_SnCrc3 = sensirion_common_generate(Usr_Serial_Nbr1,2);
    Usr_SnCrc4 = sensirion_common_generate(Usr_Serial_Nbr1+2,2);
    Usr_SnCrc5 = sensirion_common_generate(Usr_Serial_Nbr1+4,2);
    Usr_SnCrc6 = sensirion_common_generate(Usr_Serial_Nbr1+6,2);
    
    Psf_MeasurementFlag = 1;
}



uint8_t TmSn_Byte[14];

void Usr_I2CA_MainLoop(void)
{   
    uint8_t i;
    uint8_t errcnt;
    uint8_t cal_crc1;
    uint8_t cal_crc2;
    uint16_t val;
    uint8_t *ptr1;
    uint8_t *ptr2;
    
    if(I2CA_WR_Flag == 1)
    {   // I2CA had received finish, should process these datas;
        if(1==0)
        {
            
        }
        #if 1
        else if(Usr_Md_CmdCode1 == 0x1183)
        {   // Write HumComp_M2_S;
            #if 1
            I2CA_printf("\nCmdCode1 = 0x%04X,\tCmdCode2 = 0x%04X,\tLen = %d, ",Usr_Md_CmdCode1,Usr_Md_CmdCode2,I2CA_RX_Cnt);
            for(i=0;i<I2CA_RX_Cnt;i++)
            {
                I2CA_printf("\t0x%02X,",I2CA_RX_Buff2[i]);
            }
            #endif
            
            {
                
                errcnt = 0;
                
                for(i=0;i<DEF_HUMCOMP_PARAM_MAX;i++)
                {
                    
                    cal_crc1 = compute_crc8(I2CA_RX_Buff2+2+6*i,2);
                    cal_crc2 = *(I2CA_RX_Buff2+2+2+6*i);
                    if(cal_crc1 != cal_crc2)
                    {
                        errcnt++;
                        I2CA_printf("\terr crc1.");
                    }
                    
                    cal_crc1 = compute_crc8(I2CA_RX_Buff2+2+3+6*i,2);
                    cal_crc2 = *(I2CA_RX_Buff2+2+3+2+6*i);
                    if(cal_crc1 != cal_crc2)
                    {
                        errcnt++;
                        I2CA_printf("\terr crc1.");
                    }
                }
                
                
                if(errcnt==0)
                {
                    
                    for(i=0;i<DEF_HUMCOMP_PARAM_MAX;i++)
                    {
                        ptr1 = (uint8_t*)(HumComp_M2_S+i);
                        *ptr1 = I2CA_RX_Buff2[6+6*i];
                        ptr1++;
                        DF_Data[DEF_HUMCOMP_PARAM_INDEX+0+i*4] = I2CA_RX_Buff2[6+6*i];
                        *ptr1 = I2CA_RX_Buff2[5+6*i];
                        ptr1++;
                        DF_Data[DEF_HUMCOMP_PARAM_INDEX+1+i*4] = I2CA_RX_Buff2[5+6*i];
                        *ptr1 = I2CA_RX_Buff2[3+6*i];
                        ptr1++;
                        DF_Data[DEF_HUMCOMP_PARAM_INDEX+2+i*4] = I2CA_RX_Buff2[3+6*i];
                        *ptr1 = I2CA_RX_Buff2[2+6*i];
                        ptr1++;
                        DF_Data[DEF_HUMCOMP_PARAM_INDEX+3+i*4] = I2CA_RX_Buff2[2+6*i];
                    }
                    DF_UpdateReal_Flag = 1;
                }
                else
                {
                    
                }
            }
        }
        else if(Usr_Md_CmdCode1 == 0x1184)
        {   // Write HumComp_Flag;
            #if 1
            I2CA_printf("\nCmdCode1 = 0x%04X,\tCmdCode2 = 0x%04X,\tLen = %d, ",Usr_Md_CmdCode1,Usr_Md_CmdCode2,I2CA_RX_Cnt);
            for(i=0;i<I2CA_RX_Cnt;i++)
            {
                I2CA_printf("\t0x%02X,",I2CA_RX_Buff2[i]);
            }
            #endif
            
            {
                
                errcnt = 0;
                
                cal_crc1 = compute_crc8(I2CA_RX_Buff2+2,2);
                cal_crc2 = *(I2CA_RX_Buff2+2+2);
                if(cal_crc1 != cal_crc2)
                {
                    errcnt++;
                    I2CA_printf("\terr crc1.");
                    
                }
                
                if(errcnt==0)
                {
                    
                    DF_Data[DEF_HUMCOMP_FLAG_INDEX] = I2CA_RX_Buff2[3];
                    DF_Data[DEF_HUMCOMP_FLAG_INDEX+1] = I2CA_RX_Buff2[2];
                    
                    val = I2CA_RX_Buff2[2];
                    val <<= 8;
                    val += I2CA_RX_Buff2[3];
                    
                    HumComp_Flag = val;
                    
                    DF_UpdateReal_Flag = 1;
                }
                else
                {
                    
                }
            }
        }
        else if(Usr_Md_CmdCode1 == 0x1185)
        {   // Write PresComp_K;
            #if 1
            I2CA_printf("\nCmdCode1 = 0x%04X,\tCmdCode2 = 0x%04X,\tLen = %d, ",Usr_Md_CmdCode1,Usr_Md_CmdCode2,I2CA_RX_Cnt);
            for(i=0;i<I2CA_RX_Cnt;i++)
            {
                I2CA_printf("\t0x%02X,",I2CA_RX_Buff2[i]);
            }
            #endif
            
            {
                
                errcnt = 0;
                
                for(i=0;i<DEF_PRESCOMP_PARAM_MAX;i++)
                {
                    
                    cal_crc1 = compute_crc8(I2CA_RX_Buff2+2+6*i,2);
                    cal_crc2 = *(I2CA_RX_Buff2+2+2+6*i);
                    if(cal_crc1 != cal_crc2)
                    {
                        errcnt++;
                        I2CA_printf("\terr crc1.");
                    }
                    
                    cal_crc1 = compute_crc8(I2CA_RX_Buff2+2+3+6*i,2);
                    cal_crc2 = *(I2CA_RX_Buff2+2+3+2+6*i);
                    if(cal_crc1 != cal_crc2)
                    {
                        errcnt++;
                        I2CA_printf("\terr crc1.");
                    }
                }
                
                if(errcnt==0)
                {
                    
                    for(i=0;i<DEF_PRESCOMP_PARAM_MAX;i++)
                    {
                        ptr1 = (uint8_t*)(PresComp_K+i);
                        
                        *ptr1 = I2CA_RX_Buff2[6+6*i];
                        ptr1++;
                        DF_Data[DEF_PRESCOMP_PARAM_INDEX+0+i*4] = I2CA_RX_Buff2[6+6*i];
                        *ptr1 = I2CA_RX_Buff2[5+6*i];
                        ptr1++;
                        DF_Data[DEF_PRESCOMP_PARAM_INDEX+1+i*4] = I2CA_RX_Buff2[5+6*i];
                        *ptr1 = I2CA_RX_Buff2[3+6*i];
                        ptr1++;
                        DF_Data[DEF_PRESCOMP_PARAM_INDEX+2+i*4] = I2CA_RX_Buff2[3+6*i];
                        *ptr1 = I2CA_RX_Buff2[2+6*i];
                        ptr1++;
                        DF_Data[DEF_PRESCOMP_PARAM_INDEX+3+i*4] = I2CA_RX_Buff2[2+6*i];
                    }
                    DF_UpdateReal_Flag = 1;
                }
                else
                {
                    
                }
            }
        }
        else if(Usr_Md_CmdCode1 == 0x1186)
        {   // Write PresComp_Flag;
            #if 1
            I2CA_printf("\nCmdCode1 = 0x%04X,\tCmdCode2 = 0x%04X,\tLen = %d, ",Usr_Md_CmdCode1,Usr_Md_CmdCode2,I2CA_RX_Cnt);
            for(i=0;i<I2CA_RX_Cnt;i++)
            {
                I2CA_printf("\t0x%02X,",I2CA_RX_Buff2[i]);
            }
            #endif
            
            {
                
                errcnt = 0;
                
                cal_crc1 = compute_crc8(I2CA_RX_Buff2+2,2);
                cal_crc2 = *(I2CA_RX_Buff2+2+2);
                if(cal_crc1 != cal_crc2)
                {
                    errcnt++;
                    I2CA_printf("\terr crc1.");
                    
                }
                
                if(errcnt==0)
                {
                    
                    DF_Data[DEF_PRESCOMP_FLAG_INDEX] = I2CA_RX_Buff2[3];
                    DF_Data[DEF_PRESCOMP_FLAG_INDEX+1] = I2CA_RX_Buff2[2];
                    
                    val = I2CA_RX_Buff2[2];
                    val <<= 8;
                    val += I2CA_RX_Buff2[3];
                    
                    PresComp_Flag = val;
                    
                    DF_UpdateReal_Flag = 1;
                }
                else
                {
                    
                }
            }
        }
        else if(Usr_Md_CmdCode1==0x1188)
        {   // Write SN;
            #if 1
            I2CA_printf("\nCmdCode1 = 0x%04X,\tCmdCode2 = 0x%04X,\tLen = %d, ",Usr_Md_CmdCode1,Usr_Md_CmdCode2,I2CA_RX_Cnt);
            for(i=0;i<I2CA_RX_Cnt;i++)
            {
                I2CA_printf("\t0x%02X,",I2CA_RX_Buff2[i]);
            }
            #endif
            
            #if 0
            {
                
                errcnt = 0;
                
                cal_crc1 = compute_crc8(I2CA_RX_Buff2+2,2);
                cal_crc2 = *(I2CA_RX_Buff2+2+2);
                if(cal_crc1 != cal_crc2)
                {
                    errcnt++;
                    I2CA_printf("\terr crc1.");
                    
                }
                
                cal_crc1 = compute_crc8(I2CA_RX_Buff2+2+3,2);
                cal_crc2 = *(I2CA_RX_Buff2+2+2+3);
                if(cal_crc1 != cal_crc2)
                {
                    errcnt++;
                    I2CA_printf("\terr crc2.");
                }
                
                cal_crc1 = compute_crc8(I2CA_RX_Buff2+2+3+3,2);
                cal_crc2 = *(I2CA_RX_Buff2+2+2+3+3);
                if(cal_crc1 != cal_crc2)
                {
                    errcnt++;
                    I2CA_printf("\terr crc3.");
                }
                
                cal_crc1 = compute_crc8(I2CA_RX_Buff2+2+3+3+3,2);
                cal_crc2 = *(I2CA_RX_Buff2+2+2+3+3+3);
                if(cal_crc1 != cal_crc2)
                {
                    errcnt++;
                    I2CA_printf("\terr crc4.");
                }
                
                if(errcnt==0)
                {
                    
                    DF_Data[DEF_TIME_SN_INDEX] = I2CA_RX_Buff2[7];
                    DF_Data[DEF_TIME_SN_INDEX+1] = I2CA_RX_Buff2[6];
                    DF_Data[DEF_TIME_SN_INDEX+2] = I2CA_RX_Buff2[10];
                    DF_Data[DEF_TIME_SN_INDEX+3] = I2CA_RX_Buff2[9];
                    
                    val = I2CA_RX_Buff2[6];
                    val <<= 8;
                    val += I2CA_RX_Buff2[7];
                    TimeSn_Time = val;
                    
                    val = I2CA_RX_Buff2[9];
                    val <<= 8;
                    val += I2CA_RX_Buff2[10];
                    TimeSn_SN = val;
                    
                    DF_UpdateReal_Flag = 1;
                }
                else
                {
                    
                }
                
            }
            #endif
            #if 1
            {
                
                errcnt = 0;
                
                cal_crc1 = compute_crc8(I2CA_RX_Buff2+2,2);
                cal_crc2 = *(I2CA_RX_Buff2+2+2);
                if(cal_crc1 != cal_crc2)
                {
                    errcnt++;
                    I2CA_printf("\terr crc1.");
                    
                }
                
                cal_crc1 = compute_crc8(I2CA_RX_Buff2+2+3,2);
                cal_crc2 = *(I2CA_RX_Buff2+2+2+3);
                if(cal_crc1 != cal_crc2)
                {
                    errcnt++;
                    I2CA_printf("\terr crc2.");
                }
                
                if(errcnt==0)
                {
                    
                    DF_Data[DEF_TIME_SN_INDEX] = I2CA_RX_Buff2[3];
                    DF_Data[DEF_TIME_SN_INDEX+1] = I2CA_RX_Buff2[2];
                    DF_Data[DEF_TIME_SN_INDEX+2] = I2CA_RX_Buff2[6];
                    DF_Data[DEF_TIME_SN_INDEX+3] = I2CA_RX_Buff2[5];
                    
                    val = I2CA_RX_Buff2[2];
                    val <<= 8;
                    val += I2CA_RX_Buff2[3];
                    TimeSn_Time = val;
                    
                    val = I2CA_RX_Buff2[5];
                    val <<= 8;
                    val += I2CA_RX_Buff2[6];
                    TimeSn_SN = val;
                    
                    DF_UpdateReal_Flag = 1;
                }
                else
                {
                    
                }
                
            }
            #endif
        }
        else if(Usr_Md_CmdCode1 == 0x1189)
        {   // Write temperature compensation parameters;
            #if 1
            I2CA_printf("\nCmdCode1 = 0x%04X,\tCmdCode2 = 0x%04X,\tLen = %d, ",Usr_Md_CmdCode1,Usr_Md_CmdCode2,I2CA_RX_Cnt);
            for(i=0;i<I2CA_RX_Cnt;i++)
            {
                I2CA_printf("\t0x%02X,",I2CA_RX_Buff2[i]);
            }
            #endif
            
            {
                
                errcnt = 0;
                
                cal_crc1 = compute_crc8(I2CA_RX_Buff2+2+3*0,2);
                cal_crc2 = *(I2CA_RX_Buff2+2+2+3*0);
                if(cal_crc1 != cal_crc2)
                {
                    errcnt++;
                    I2CA_printf("\terr crc1.");
                    
                }
                
                cal_crc1 = compute_crc8(I2CA_RX_Buff2+2+3*1,2);
                cal_crc2 = *(I2CA_RX_Buff2+2+2+3*1);
                if(cal_crc1 != cal_crc2)
                {
                    errcnt++;
                    I2CA_printf("\terr crc2.");
                }
                
                cal_crc1 = compute_crc8(I2CA_RX_Buff2+2+3*2,2);
                cal_crc2 = *(I2CA_RX_Buff2+2+2+3*2);
                if(cal_crc1 != cal_crc2)
                {
                    errcnt++;
                    I2CA_printf("\terr crc3.");
                }
                
                cal_crc1 = compute_crc8(I2CA_RX_Buff2+2+3*3,2);
                cal_crc2 = *(I2CA_RX_Buff2+2+2+3*3);
                if(cal_crc1 != cal_crc2)
                {
                    errcnt++;
                    I2CA_printf("\terr crc4.");
                }
                
                cal_crc1 = compute_crc8(I2CA_RX_Buff2+2+3*4,2);
                cal_crc2 = *(I2CA_RX_Buff2+2+2+3*4);
                if(cal_crc1 != cal_crc2)
                {
                    errcnt++;
                    I2CA_printf("\terr crc5.");
                }
                
                cal_crc1 = compute_crc8(I2CA_RX_Buff2+2+3*5,2);
                cal_crc2 = *(I2CA_RX_Buff2+2+2+3*5);
                if(cal_crc1 != cal_crc2)
                {
                    errcnt++;
                    I2CA_printf("\terr crc6.");
                }
                
                cal_crc1 = compute_crc8(I2CA_RX_Buff2+2+3*6,2);
                cal_crc2 = *(I2CA_RX_Buff2+2+2+3*6);
                if(cal_crc1 != cal_crc2)
                {
                    errcnt++;
                    I2CA_printf("\terr crc7.");
                }
                
                cal_crc1 = compute_crc8(I2CA_RX_Buff2+2+3*7,2);
                cal_crc2 = *(I2CA_RX_Buff2+2+2+3*7);
                if(cal_crc1 != cal_crc2)
                {
                    errcnt++;
                    I2CA_printf("\terr crc8.");
                }
                
                if(errcnt==0)
                {
                    uint32_t tmp0;
                    
                    {// Process P0
                    tmp0 = 0;
                    
                    #if 0
                    val = I2CA_RX_Buff2[2];
                    val <<= 8;
                    val += I2CA_RX_Buff2[3];
                    tmp0 = val;
                    DF_Data[DEF_TCOMP_P0_INDEX+2] = (uint8_t)val;
                    DF_Data[DEF_TCOMP_P0_INDEX+2+1] = (uint8_t)(val>>8);
                    #endif
                    
                    val = I2CA_RX_Buff2[5];
                    val <<= 8;
                    val += I2CA_RX_Buff2[6];
                    //tmp0 <<= 16;
                    //tmp0 += val;
                    
                    tmp0 = (int16_t)val;
                    
                    DF_Data[DEF_TCOMP_P0_INDEX] = (uint8_t)val;
                    DF_Data[DEF_TCOMP_P0_INDEX+1] = (uint8_t)(val>>8);
                    
                    TComp_P0 = tmp0;
                    
                    }
                    
                    {// Process P1
                    tmp0 = 0;
                    
                    #if 0
                    val = I2CA_RX_Buff2[8];
                    val <<= 8;
                    val += I2CA_RX_Buff2[9];
                    tmp0 = val;
                    DF_Data[DEF_TCOMP_P1_INDEX+2] = (uint8_t)val;
                    DF_Data[DEF_TCOMP_P1_INDEX+2+1] = (uint8_t)(val>>8);
                    #endif
                    
                    val = I2CA_RX_Buff2[11];
                    val <<= 8;
                    val += I2CA_RX_Buff2[12];
                    //tmp0 <<= 16;
                    //tmp0 += val;
                    
                    tmp0 = (int16_t)val;
                    
                    DF_Data[DEF_TCOMP_P1_INDEX] = (uint8_t)val;
                    DF_Data[DEF_TCOMP_P1_INDEX+1] = (uint8_t)(val>>8);
                    
                    TComp_P1 = tmp0;
                    
                    }
                    
                    {// Process P2
                    tmp0 = 0;
                    
                    val = I2CA_RX_Buff2[14];
                    val <<= 8;
                    val += I2CA_RX_Buff2[15];
                    tmp0 = val;
                    DF_Data[DEF_TCOMP_P2_INDEX+2] = (uint8_t)val;
                    DF_Data[DEF_TCOMP_P2_INDEX+2+1] = (uint8_t)(val>>8);
                    
                    val = I2CA_RX_Buff2[17];
                    val <<= 8;
                    val += I2CA_RX_Buff2[18];
                    tmp0 <<= 16;
                    tmp0 += val;
                    
                    DF_Data[DEF_TCOMP_P2_INDEX] = (uint8_t)val;
                    DF_Data[DEF_TCOMP_P2_INDEX+1] = (uint8_t)(val>>8);
                    
                    TComp_P2 = tmp0;
                    
                    }
                    
                    {// Process P3
                    tmp0 = 0;
                    
                    val = I2CA_RX_Buff2[20];
                    val <<= 8;
                    val += I2CA_RX_Buff2[21];
                    tmp0 = val;
                    DF_Data[DEF_TCOMP_P3_INDEX+2] = (uint8_t)val;
                    DF_Data[DEF_TCOMP_P3_INDEX+2+1] = (uint8_t)(val>>8);
                    
                    val = I2CA_RX_Buff2[23];
                    val <<= 8;
                    val += I2CA_RX_Buff2[24];
                    tmp0 <<= 16;
                    tmp0 += val;
                    
                    DF_Data[DEF_TCOMP_P3_INDEX] = (uint8_t)val;
                    DF_Data[DEF_TCOMP_P3_INDEX+1] = (uint8_t)(val>>8);
                    
                    TComp_P3 = tmp0;
                    
                    }
                    
                    DF_UpdateReal_Flag = 1;
                }
                
                else
                {
                    
                }
                
            }
        }
        else if(Usr_Md_CmdCode1 == 0x118C)
        {   // Write Sens_TableY;
            #if 1
            I2CA_printf("\nCmdCode1 = 0x%04X,\tCmdCode2 = 0x%04X,\tLen = %d, ",Usr_Md_CmdCode1,Usr_Md_CmdCode2,I2CA_RX_Cnt);
            for(i=0;i<I2CA_RX_Cnt;i++)
            {
                I2CA_printf("\t0x%02X,",I2CA_RX_Buff2[i]);
            }
            #endif
            
            {
                
                
                errcnt = 0;
                
                for(i=0;i<DEF_TABLE_MAX;i++)
                {
                    
                    cal_crc1 = compute_crc8(I2CA_RX_Buff2+2+3*i,2);
                    cal_crc2 = *(I2CA_RX_Buff2+2+2+3*i);
                    if(cal_crc1 != cal_crc2)
                    {
                        errcnt++;
                        I2CA_printf("\terr crc1.");
                    
                    }
                }
                
                
                if(errcnt==0)
                {
                
                    uint32_t tmp0;
                    
                    for(i=0;i<DEF_TABLE_MAX;i++)
                    {
                        
                        tmp0 = 0;
                        
                        val = I2CA_RX_Buff2[2+3*i];
                        val <<= 8;
                        val += I2CA_RX_Buff2[2+3*i+1];
                        tmp0 = val;
                        DF_Data[DEF_TABLEY_INDEX+i*2+0] = (uint8_t)val;
                        DF_Data[DEF_TABLEY_INDEX+i*2+1] = (uint8_t)(val>>8);
                        
                        Sens_TableY[i] = tmp0;
                        
                    }
                    DF_UpdateReal_Flag = 1;
                }
                else
                {
                    
                }
                
            }
        }
        else if(Usr_Md_CmdCode1 == 0x118D)
        {   // Write Sens_TableX;
            #if 1
            I2CA_printf("\nCmdCode1 = 0x%04X,\tCmdCode2 = 0x%04X,\tLen = %d, ",Usr_Md_CmdCode1,Usr_Md_CmdCode2,I2CA_RX_Cnt);
            for(i=0;i<I2CA_RX_Cnt;i++)
            {
                I2CA_printf("\t0x%02X,",I2CA_RX_Buff2[i]);
            }
            #endif
            
            {
                
                
                errcnt = 0;
                
                for(i=0;i<DEF_TABLE_MAX;i++)
                {
                    
                    cal_crc1 = compute_crc8(I2CA_RX_Buff2+2+3*i,2);
                    cal_crc2 = *(I2CA_RX_Buff2+2+2+3*i);
                    if(cal_crc1 != cal_crc2)
                    {
                        errcnt++;
                        I2CA_printf("\terr crc1.");
                    
                    }
                }
                
                
                if(errcnt==0)
                {
                
                    uint32_t tmp0;
                    
                    for(i=0;i<DEF_TABLE_MAX;i++)
                    {
                        
                        tmp0 = 0;
                        
                        val = I2CA_RX_Buff2[2+3*i];
                        val <<= 8;
                        val += I2CA_RX_Buff2[2+3*i+1];
                        tmp0 = val;
                        DF_Data[DEF_TABLEX_INDEX+i*2+0] = (uint8_t)val;
                        DF_Data[DEF_TABLEX_INDEX+i*2+1] = (uint8_t)(val>>8);
                        
                        Sens_TableX[i] = tmp0;
                        Sens_TableX2[i] = tmp0;
                        
                    }
                    DF_UpdateReal_Flag = 1;
                }
                else
                {
                    
                }
                
            }
        }
        
        else if(Usr_Md_CmdCode1 == 0x118E)
        {   // Write Sens_CoolTime;
            #if 1
            I2CA_printf("\nCmdCode1 = 0x%04X,\tCmdCode2 = 0x%04X,\tLen = %d, ",Usr_Md_CmdCode1,Usr_Md_CmdCode2,I2CA_RX_Cnt);
            for(i=0;i<I2CA_RX_Cnt;i++)
            {
                I2CA_printf("\t0x%02X,",I2CA_RX_Buff2[i]);
            }
            #endif
            
            {
                
                errcnt = 0;
                
                cal_crc1 = compute_crc8(I2CA_RX_Buff2+2+3*0,2);
                cal_crc2 = *(I2CA_RX_Buff2+2+2+3*0);
                if(cal_crc1 != cal_crc2)
                {
                    errcnt++;
                    I2CA_printf("\terr crc1.");
                    
                }
                
                if(errcnt==0)
                {
                    uint32_t tmp0;
                    
                    {// Process Sens_CoolTime;
                    tmp0 = 0;
                    
                    val = I2CA_RX_Buff2[2];
                    val <<= 8;
                    val += I2CA_RX_Buff2[3];
                    tmp0 = val;
                    DF_Data[DEF_COOLTIME_INDEX+0] = (uint8_t)val;
                    DF_Data[DEF_COOLTIME_INDEX+1] = (uint8_t)(val>>8);
                    
                    Sens_CoolTime = tmp0;
                    
                    }
                    
                    DF_UpdateReal_Flag = 1;
                }
                else
                {
                    
                }
                
            }
        }
        else if(Usr_Md_CmdCode1 == 0x118F)
        {   // Write TComp_TRawBase;
            #if 1
            I2CA_printf("\nCmdCode1 = 0x%04X,\tCmdCode2 = 0x%04X,\tLen = %d, ",Usr_Md_CmdCode1,Usr_Md_CmdCode2,I2CA_RX_Cnt);
            for(i=0;i<I2CA_RX_Cnt;i++)
            {
                I2CA_printf("\t0x%02X,",I2CA_RX_Buff2[i]);
            }
            #endif
            
            {
                
                errcnt = 0;
                
                cal_crc1 = compute_crc8(I2CA_RX_Buff2+2+3*0,2);
                cal_crc2 = *(I2CA_RX_Buff2+2+2+3*0);
                if(cal_crc1 != cal_crc2)
                {
                    errcnt++;
                    I2CA_printf("\terr crc1.");
                    
                }
                
                if(errcnt==0)
                {
                    uint32_t tmp0;
                    
                    {// Process TComp_TRawBase;
                    tmp0 = 0;
                    
                    val = I2CA_RX_Buff2[2];
                    val <<= 8;
                    val += I2CA_RX_Buff2[3];
                    tmp0 = val;
                    DF_Data[DEF_TRAWBASE_INDEX+0] = (uint8_t)val;
                    DF_Data[DEF_TRAWBASE_INDEX+1] = (uint8_t)(val>>8);
                    
                    TComp_TRawBase = tmp0;
                    
                    }
                    
                    DF_UpdateReal_Flag = 1;
                }
                else
                {
                    
                }
                
            }
        }
        else if(Usr_Md_CmdCode1 == 0x1190)
        {   // Write PresComp_PBase;
            #if 1
            Init_printf("\nCmdCode1 = 0x%04X,\tCmdCode2 = 0x%04X,\tLen = %d, ",Usr_Md_CmdCode1,Usr_Md_CmdCode2,I2CA_RX_Cnt);
            for(i=0;i<I2CA_RX_Cnt;i++)
            {
                Init_printf("\t0x%02X,",I2CA_RX_Buff2[i]);
            }
            #endif
            
            {
                
                errcnt = 0;
                
                cal_crc1 = compute_crc8(I2CA_RX_Buff2+2+3*0,2);
                cal_crc2 = *(I2CA_RX_Buff2+2+2+3*0);
                if(cal_crc1 != cal_crc2)
                {
                    errcnt++;
                    I2CA_printf("\terr crc1.");
                    
                }
                
                if(errcnt==0)
                {
                    uint32_t tmp0;
                    
                    {// Process TComp_TRawBase;
                    tmp0 = 0;
                    
                    val = I2CA_RX_Buff2[2];
                    val <<= 8;
                    val += I2CA_RX_Buff2[3];
                    tmp0 = val;
                    DF_Data[DEF_PRESCOMP_PBASE_INDEX+0] = (uint8_t)val;
                    DF_Data[DEF_PRESCOMP_PBASE_INDEX+1] = (uint8_t)(val>>8);
                    
                    PresComp_PBase = tmp0;
                    
                    }
                    
                    DF_UpdateReal_Flag = 1;
                }
                else
                {
                    
                }
                
            }
        }
        else if(Usr_Md_CmdCode1 == 0x1191)
        {   // Write Sens_DC_Y;
            #if 1
            Init_printf("\nCmdCode1 = 0x%04X,\tCmdCode2 = 0x%04X,\tLen = %d, ",Usr_Md_CmdCode1,Usr_Md_CmdCode2,I2CA_RX_Cnt);
            for(i=0;i<I2CA_RX_Cnt;i++)
            {
                Init_printf("\t0x%02X,",I2CA_RX_Buff2[i]);
            }
            #endif
            
            {
                
                errcnt = 0;
                
                cal_crc1 = compute_crc8(I2CA_RX_Buff2+2+3*0,2);
                cal_crc2 = *(I2CA_RX_Buff2+2+2+3*0);
                if(cal_crc1 != cal_crc2)
                {
                    errcnt++;
                    I2CA_printf("\terr crc1.");
                    
                }
                
                if(errcnt==0)
                {
                    uint32_t tmp0;
                    
                    {// Process Sens_DC_Y;
                    tmp0 = 0;
                    
                    val = I2CA_RX_Buff2[2];
                    val <<= 8;
                    val += I2CA_RX_Buff2[3];
                    tmp0 = val;
                    DF_Data[DEF_DC_Y_INDEX+0] = (uint8_t)val;
                    DF_Data[DEF_DC_Y_INDEX+1] = (uint8_t)(val>>8);
                    
                    Sens_DC_Y = tmp0;
                    
                    }
                    
                    DF_UpdateReal_Flag = 1;
                }
                else
                {
                    
                }
                
            }
        }
        //else if(Usr_Md_CmdCode1 == 0x1293)
        else if(Usr_Md_CmdCode1 == 0x1193)
        {   // Write FilterCnt;
            #if 1
            I2CA_printf("\nCmdCode1 = 0x%04X,\tCmdCode2 = 0x%04X,\tLen = %d, ",Usr_Md_CmdCode1,Usr_Md_CmdCode2,I2CA_RX_Cnt);
            for(i=0;i<I2CA_RX_Cnt;i++)
            {
                I2CA_printf("\t0x%02X,",I2CA_RX_Buff2[i]);
            }
            #endif
            
            {
                
                errcnt = 0;
                
                cal_crc1 = compute_crc8(I2CA_RX_Buff2+2+3*0,2);
                cal_crc2 = *(I2CA_RX_Buff2+2+2+3*0);
                if(cal_crc1 != cal_crc2)
                {
                    errcnt++;
                    I2CA_printf("\terr crc1.");
                    
                }
                
                if(errcnt==0)
                {
                    uint32_t tmp0;
                    
                    {// Process FilterCnt;
                    tmp0 = 0;
                    
                    val = I2CA_RX_Buff2[2];
                    val <<= 8;
                    val += I2CA_RX_Buff2[3];
                    tmp0 = val;
                    DF_Data[DEF_FILTERCNT_INDEX+0] = (uint8_t)val;
                    DF_Data[DEF_FILTERCNT_INDEX+1] = (uint8_t)(val>>8);
                    
                    Sens_FilterCnt = tmp0;
                    
                    }
                    
                    DF_UpdateReal_Flag = 1;
                }
                else
                {
                    
                }
                
            }
        }
        else if(Usr_Md_CmdCode1 == 0x1194)
        {   // Write Sens_PreHeatTime;
            #if 1
            I2CA_printf("\nCmdCode1 = 0x%04X,\tCmdCode2 = 0x%04X,\tLen = %d, ",Usr_Md_CmdCode1,Usr_Md_CmdCode2,I2CA_RX_Cnt);
            for(i=0;i<I2CA_RX_Cnt;i++)
            {
                I2CA_printf("\t0x%02X,",I2CA_RX_Buff2[i]);
            }
            #endif
            
            {
                
                errcnt = 0;
                
                cal_crc1 = compute_crc8(I2CA_RX_Buff2+2+3*0,2);
                cal_crc2 = *(I2CA_RX_Buff2+2+2+3*0);
                if(cal_crc1 != cal_crc2)
                {
                    errcnt++;
                    I2CA_printf("\terr crc1.");
                    
                }
                
                if(errcnt==0)
                {
                    uint32_t tmp0;
                    
                    {// Process Sens_PreHeatTime;
                    tmp0 = 0;
                    
                    val = I2CA_RX_Buff2[2];
                    val <<= 8;
                    val += I2CA_RX_Buff2[3];
                    tmp0 = val;
                    DF_Data[DEF_PREHEATTIME_INDEX+0] = (uint8_t)val;
                    DF_Data[DEF_PREHEATTIME_INDEX+1] = (uint8_t)(val>>8);
                    
                    Sens_PreHeatTime = tmp0;
                    
                    }
                    
                    DF_UpdateReal_Flag = 1;
                }
                else
                {
                    
                }
                
            }
        }
        else if(Usr_Md_CmdCode1 == 0x1195)
        {   // Write TmpRate_P;
            #if 1
            I2CA_printf("\nCmdCode1 = 0x%04X,\tCmdCode2 = 0x%04X,\tLen = %d, ",Usr_Md_CmdCode1,Usr_Md_CmdCode2,I2CA_RX_Cnt);
            for(i=0;i<I2CA_RX_Cnt;i++)
            {
                I2CA_printf("\t0x%02X,",I2CA_RX_Buff2[i]);
            }
            #endif
            
            {
                
                errcnt = 0;
                
                cal_crc1 = compute_crc8(I2CA_RX_Buff2+2+3*0,2);
                cal_crc2 = *(I2CA_RX_Buff2+2+2+3*0);
                if(cal_crc1 != cal_crc2)
                {
                    errcnt++;
                    I2CA_printf("\terr crc1.");
                    
                }
                
                if(errcnt==0)
                {
                    uint32_t tmp0;
                    
                    {// Process Sens_PreHeatTime;
                    tmp0 = 0;
                    
                    val = I2CA_RX_Buff2[2];
                    val <<= 8;
                    val += I2CA_RX_Buff2[3];
                    tmp0 = val;
                    DF_Data[DEF_TMPRATE_P_INDEX+0] = (uint8_t)val;
                    DF_Data[DEF_TMPRATE_P_INDEX+1] = (uint8_t)(val>>8);
                    
                    TmpRate_P = tmp0;
                    
                    }
                    
                    DF_UpdateReal_Flag = 1;
                }
                else
                {
                    
                }
                
            }
        }
        
        #if(defined(DEBUG_HEAT_COMP2_EN)&&(DEBUG_HEAT_COMP2_EN==1))
        else if(Usr_Md_CmdCode1 == 0x11A1)
        {   // Write HtComp_TRaw_Base_2;
            #if 1
            I2CA_printf("\nCmdCode1 = 0x%04X,\tCmdCode2 = 0x%04X,\tLen = %d, ",Usr_Md_CmdCode1,Usr_Md_CmdCode2,I2CA_RX_Cnt);
            for(i=0;i<I2CA_RX_Cnt;i++)
            {
                I2CA_printf("\t0x%02X,",I2CA_RX_Buff2[i]);
            }
            #endif
            
            {
                
                errcnt = 0;
                
                cal_crc1 = compute_crc8(I2CA_RX_Buff2+2+3*0,2);
                cal_crc2 = *(I2CA_RX_Buff2+2+2+3*0);
                if(cal_crc1 != cal_crc2)
                {
                    errcnt++;
                    I2CA_printf("\terr crc1.");
                    
                }
                
                if(errcnt==0)
                {
                    uint32_t tmp0;
                    
                    {// Process HtComp_TRaw_Base_2;
                    tmp0 = 0;
                    
                    val = I2CA_RX_Buff2[2];
                    val <<= 8;
                    val += I2CA_RX_Buff2[3];
                    tmp0 = val;
                    DF_Data[DEF_HTCOMP_TRAWBASE_INDEX+0] = (uint8_t)val;
                    DF_Data[DEF_HTCOMP_TRAWBASE_INDEX+1] = (uint8_t)(val>>8);
                    
                    HtComp_TRaw_Base_2 = tmp0;
                    
                    }
                    
                    DF_UpdateReal_Flag = 1;
                }
                else
                {
                    
                }
                
            }
        }
        else if(Usr_Md_CmdCode1 == 0x11A2)
        {   // Write HtComp_HtRaw_Base_2;
            #if 1
            I2CA_printf("\nCmdCode1 = 0x%04X,\tCmdCode2 = 0x%04X,\tLen = %d, ",Usr_Md_CmdCode1,Usr_Md_CmdCode2,I2CA_RX_Cnt);
            for(i=0;i<I2CA_RX_Cnt;i++)
            {
                I2CA_printf("\t0x%02X,",I2CA_RX_Buff2[i]);
            }
            #endif
            
            {
                
                errcnt = 0;
                
                cal_crc1 = compute_crc8(I2CA_RX_Buff2+2+3*0,2);
                cal_crc2 = *(I2CA_RX_Buff2+2+2+3*0);
                if(cal_crc1 != cal_crc2)
                {
                    errcnt++;
                    I2CA_printf("\terr crc1.");
                    
                }
                
                if(errcnt==0)
                {
                    uint32_t tmp0;
                    
                    {// Process HtComp_TRaw_Base_2;
                    tmp0 = 0;
                    
                    val = I2CA_RX_Buff2[2];
                    val <<= 8;
                    val += I2CA_RX_Buff2[3];
                    tmp0 = val;
                    DF_Data[DEF_HTCOMP_HTRAWBASE_INDEX+0] = (uint8_t)val;
                    DF_Data[DEF_HTCOMP_HTRAWBASE_INDEX+1] = (uint8_t)(val>>8);
                    
                    HtComp_HtRaw_Base_2 = tmp0;
                    
                    }
                    
                    DF_UpdateReal_Flag = 1;
                }
                else
                {
                    
                }
                
            }
        }
        else if(Usr_Md_CmdCode1 == 0x11A3)
        {   // Write HtComp_Kh_2;
            #if 1
            I2CA_printf("\nCmdCode1 = 0x%04X,\tCmdCode2 = 0x%04X,\tLen = %d, ",Usr_Md_CmdCode1,Usr_Md_CmdCode2,I2CA_RX_Cnt);
            for(i=0;i<I2CA_RX_Cnt;i++)
            {
                I2CA_printf("\t0x%02X,",I2CA_RX_Buff2[i]);
            }
            #endif
            
            {
                
                errcnt = 0;
                
                cal_crc1 = compute_crc8(I2CA_RX_Buff2+2+3*0,2);
                cal_crc2 = *(I2CA_RX_Buff2+2+2+3*0);
                if(cal_crc1 != cal_crc2)
                {
                    errcnt++;
                    I2CA_printf("\terr crc1.");
                    
                }
                
                if(errcnt==0)
                {
                    uint32_t tmp0;
                    
                    {// Process HtComp_TRaw_Base_2;
                    tmp0 = 0;
                    
                    val = I2CA_RX_Buff2[2];
                    val <<= 8;
                    val += I2CA_RX_Buff2[3];
                    tmp0 = val;
                    DF_Data[DEF_HTCOMP_KH_INDEX+0] = (uint8_t)val;
                    DF_Data[DEF_HTCOMP_KH_INDEX+1] = (uint8_t)(val>>8);
                    
                    HtComp_Kh_2 = tmp0;
                    
                    }
                    
                    DF_UpdateReal_Flag = 1;
                }
                else
                {
                    
                }
                
            }
        }
        else if(Usr_Md_CmdCode1 == 0x11A4)
        {   // Write HtComp_SP_2;
            #if 1
            I2CA_printf("\nCmdCode1 = 0x%04X,\tCmdCode2 = 0x%04X,\tLen = %d, ",Usr_Md_CmdCode1,Usr_Md_CmdCode2,I2CA_RX_Cnt);
            for(i=0;i<I2CA_RX_Cnt;i++)
            {
                I2CA_printf("\t0x%02X,",I2CA_RX_Buff2[i]);
            }
            #endif
            
            {
                
                errcnt = 0;
                
                cal_crc1 = compute_crc8(I2CA_RX_Buff2+2+3*0,2);
                cal_crc2 = *(I2CA_RX_Buff2+2+2+3*0);
                if(cal_crc1 != cal_crc2)
                {
                    errcnt++;
                    I2CA_printf("\terr crc1.");
                    
                }
                
                if(errcnt==0)
                {
                    uint32_t tmp0;
                    
                    {// Process HtComp_TRaw_Base_2;
                    tmp0 = 0;
                    
                    val = I2CA_RX_Buff2[2];
                    val <<= 8;
                    val += I2CA_RX_Buff2[3];
                    tmp0 = val;
                    DF_Data[DEF_HTCOMP_SP_INDEX+0] = (uint8_t)val;
                    DF_Data[DEF_HTCOMP_SP_INDEX+1] = (uint8_t)(val>>8);
                    
                    HtComp_SP_2 = tmp0;
                    
                    }
                    
                    DF_UpdateReal_Flag = 1;
                }
                else
                {
                    
                }
                
            }
        }
        else if(Usr_Md_CmdCode1 == 0x11A5)
        {   // Write HtComp_Ks_2;
            #if 1
            I2CA_printf("\nCmdCode1 = 0x%04X,\tCmdCode2 = 0x%04X,\tLen = %d, ",Usr_Md_CmdCode1,Usr_Md_CmdCode2,I2CA_RX_Cnt);
            for(i=0;i<I2CA_RX_Cnt;i++)
            {
                I2CA_printf("\t0x%02X,",I2CA_RX_Buff2[i]);
            }
            #endif
            
            {
                
                errcnt = 0;
                
                cal_crc1 = compute_crc8(I2CA_RX_Buff2+2+3*0,2);
                cal_crc2 = *(I2CA_RX_Buff2+2+2+3*0);
                if(cal_crc1 != cal_crc2)
                {
                    errcnt++;
                    I2CA_printf("\terr crc1.");
                    
                }
                
                if(errcnt==0)
                {
                    uint32_t tmp0;
                    
                    {// Process HtComp_TRaw_Base_2;
                    tmp0 = 0;
                    
                    val = I2CA_RX_Buff2[2];
                    val <<= 8;
                    val += I2CA_RX_Buff2[3];
                    tmp0 = val;
                    DF_Data[DEF_HTCOMP_KS_INDEX+0] = (uint8_t)val;
                    DF_Data[DEF_HTCOMP_KS_INDEX+1] = (uint8_t)(val>>8);
                    
                    HtComp_Ks_2 = tmp0;
                    
                    }
                    
                    DF_UpdateReal_Flag = 1;
                }
                else
                {
                    
                }
                
            }
        }
        #endif
        #endif
        #if 1
        else if(Usr_Md_CmdCode1==0x3608)
        {   //Write Gas type;
            I2CA_printf("\nCmdCode1 = 0x%04X,\tCmdCode2 = 0x%04X,\tLen = %d, ",Usr_Md_CmdCode1,Usr_Md_CmdCode2,I2CA_RX_Cnt);
            for(i=0;i<I2CA_RX_Cnt;i++)
            {
                I2CA_printf("\t0x%02X,",I2CA_RX_Buff2[i]);
            }
            
            {
                
                errcnt = 0;
                cal_crc1 = compute_crc8(I2CA_RX_Buff2+2+3*0,2);
                cal_crc2 = *(I2CA_RX_Buff2+2+2+3*0);
                if(cal_crc1 != cal_crc2)
                {
                    errcnt++;
                    I2CA_printf("\terr crc1.");
                    
                }
                
                if((errcnt == 0)&&(I2CA_RX_Buff2[2] == 0))
                {
                    
                    if((I2CA_RX_Buff2[3] == 0x18)||(I2CA_RX_Buff2[3] == 0x19)||(I2CA_RX_Buff2[3] == 0x1B)||(I2CA_RX_Buff2[3] == 0x1C)||(I2CA_RX_Buff2[3] == 0x1D))
                    {
                        Psf_Gas_TypeCode = I2CA_RX_Buff2[3];
                    }
                    else
                    {
                        Psf_Gas_TypeCode = PSF_GASTYPE_DEFAULT;
                    }
                    
                    DF_Data[DEF_GASTYPE_INDEX] = (uint8_t)Psf_Gas_TypeCode;
                    DF_Data[DEF_GASTYPE_INDEX+1] = (uint8_t)(Psf_Gas_TypeCode>>8);
                    
                    DF_UpdateReal_Flag = 1;
                }
                
            }
            
        }
        
        else if(Usr_Md_CmdCode1==0x3603)
        {   // Write cmd, Start Measurement;
            I2CA_printf("\nCmdCode1 = 0x%04X,\tCmdCode2 = 0x%04X,\tLen = %d, ",Usr_Md_CmdCode1,Usr_Md_CmdCode2,I2CA_RX_Cnt);
            for(i=0;i<I2CA_RX_Cnt;i++)
            {
                I2CA_printf("\t0x%02X,",I2CA_RX_Buff2[i]);
            }
            
            
            Psf_MeasurementFlag = 1;
            
        }
        #if(defined(DEF_I2CRST1_EN)&&(DEF_I2CRST1_EN==1))
        else if(Usr_Md_CmdCode1==0x3606)
        {   // Write Cmd, Reset;
            I2CA_printf("\nCmdCode1 = 0x%04X,\tCmdCode2 = 0x%04X,\tLen = %d, ",Usr_Md_CmdCode1,Usr_Md_CmdCode2,I2CA_RX_Cnt);
            for(i=0;i<I2CA_RX_Cnt;i++)
            {
                I2CA_printf("\t0x%02X,",I2CA_RX_Buff2[i]);
            }
            
            MCU_Reset_Flag = 1;
            Mcu_Timestamp = 800;
            
        }
        #endif
        #endif
        else
        {
            
        }
        
        Usr_Md_State = 0;
        Usr_Md_Cmd1 = 0;
        Usr_Md_Cmd1 = 0;
        Usr_Md_CmdCode0 = 0;
        Usr_Md_CmdCode1 = 0;
        Usr_Md_CmdCode2 = 0;
        
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
    
    if((g_iica0_slave_status_flag == 1)&&(g_iica0_rx_end == 1)&&(g_iica0_tx_end == 0))
    {   // Master Write completely;
        
        I2CA_printf("\n\nI2CA Rx ");
        
        I2CA_printf("\ng_iica0_slave_status_flag, %d, g_iica0_rx_end, %d, g_iica0_rx_cnt, %d, g_iica0_rx_len, %d, ",g_iica0_slave_status_flag,g_iica0_rx_end,g_iica0_rx_cnt,g_iica0_rx_len);
        I2CA_printf("\ng_iica0_slave_status_flag, %d, g_iica0_tx_end, %d, g_iica0_tx_cnt, %d, g_iica0_tx_count, %d, ",g_iica0_slave_status_flag,g_iica0_tx_end,g_iica0_tx_cnt,g_iica0_tx_count);
        
        I2CA_printf("\nRxDatas, ");
        for(i=0;i<g_iica0_rx_cnt;i++)
        {
            I2CA_printf("\t0x%02X, ",I2CA_RX_Buff[i]);
        }
        
        if(I2CA_Cmd_Code == 0xD0)
        {
            
            
            
        }
        
        g_iica0_rx_end = 0;
        
        gp_iica0_rx_address = I2CA_RX_Buff;        /* iica0 receive buffer address */
        g_iica0_rx_len = DEF_I2CA_RX_MAX;             /* iica0 receive data length */
        g_iica0_rx_cnt = 0;             /* iica0 receive data count */
        g_iica0_rx_end = 0;             /* iica0 receive data end */
        
        g_iica0_slave_status_flag = 0;
    }
    
    if((g_iica0_slave_status_flag == 1)&&(g_iica0_rx_end == 1)&&(g_iica0_tx_end == 1))
    {   // Mater Read completely; (ReStart;)
        uint32_t tmp1;
        
        tmp1 = (uint32_t)gp_iica0_tx_address-(uint32_t)I2CA_TX_Buff;
        
        I2CA_printf("\n\nI2CA Tx ");
        
        I2CA_printf("\ng_iica0_slave_status_flag, %d, g_iica0_rx_end, %d, g_iica0_rx_cnt, %d, g_iica0_rx_len, %d, ",g_iica0_slave_status_flag,g_iica0_rx_end,g_iica0_rx_cnt,g_iica0_rx_len);
        I2CA_printf("\ng_iica0_slave_status_flag, %d, g_iica0_tx_end, %d, g_iica0_tx_cnt, %d, g_iica0_tx_count, %d, ",g_iica0_slave_status_flag,g_iica0_tx_end,g_iica0_tx_cnt,g_iica0_tx_count);
        
        I2CA_printf("\nTxDatas, ");
        
        
        
        for(i=0;i<tmp1;i++)
        {
            I2CA_printf("\t0x%02X, ",I2CA_TX_Buff[i]);
        }
        
        
        g_iica0_slave_status_flag = 0;  /* iica0 slave flag */
        gp_iica0_tx_address = I2CA_TX_Buff;        /* iica0 send buffer address */
        g_iica0_tx_cnt = DEF_I2CA_RX_MAX;             /* iica0 send data count */
        g_iica0_tx_end = 0;             /* iica0 send data end */
        
        g_iica0_tx_count = 0;
        
        g_iica0_rx_cnt = 0;
        
    }
    
    
}


#if 1   // CRC algorithm from Midea little board project;
#define CRC8_POLYNOMIAL 0x31
#define CRC8_INIT       0xFF

uint8_t sensirion_common_generate(const uint8_t *data,uint16_t count)
{
    uint16_t current_byte;
    uint8_t crc = CRC8_INIT;
    uint8_t crc_bit;
    /* calculates 8-Bit checksum with given polynomial */
    for(current_byte=0; current_byte<count; ++current_byte)
    {
        crc ^= (data[current_byte]);
        for(crc_bit=8; crc_bit>0; --crc_bit)
        {
            if(crc&0x80)
            {
                crc = (crc<<1)^CRC8_POLYNOMIAL;
            }
            else
            {
                crc = (crc<<1);
            }
        }
    }
    return crc;
}

#endif

#if 1   // CRC algorithm from HuangShiliang for Midea little board project;
#if 0   // 
2.CRC校验
本协议采用CRC8校验，校验参数如下：
宽度 WIDTH	8 bits
多项式 POLY	0x31 (X8 + X5 + X4 + 1)
初始值 INIT	0xFF
结果异或值 XOROUT	0x00
输入数据反转 REFIN	FALSE
输出数据反转 REFOUT	FALSE
查表法例程：
// 按照多项式 X^8 + X^5 + X^4 + 1 生成。
#endif
static const uint8_t crc8_table[256] =
{
  0x00, 0x31, 0x62, 0x53, 0xc4, 0xf5, 0xa6, 0x97, 0xb9, 0x88, 0xdb, 0xea, 0x7d, 0x4c, 0x1f, 0x2e, 
  0x43, 0x72, 0x21, 0x10, 0x87, 0xb6, 0xe5, 0xd4, 0xfa, 0xcb, 0x98, 0xa9, 0x3e, 0x0f, 0x5c, 0x6d, 
  0x86, 0xb7, 0xe4, 0xd5, 0x42, 0x73, 0x20, 0x11, 0x3f, 0x0e, 0x5d, 0x6c, 0xfb, 0xca, 0x99, 0xa8, 
  0xc5, 0xf4, 0xa7, 0x96, 0x01, 0x30, 0x63, 0x52, 0x7c, 0x4d, 0x1e, 0x2f, 0xb8, 0x89, 0xda, 0xeb, 
  0x3d, 0x0c, 0x5f, 0x6e, 0xf9, 0xc8, 0x9b, 0xaa, 0x84, 0xb5, 0xe6, 0xd7, 0x40, 0x71, 0x22, 0x13, 
  0x7e, 0x4f, 0x1c, 0x2d, 0xba, 0x8b, 0xd8, 0xe9, 0xc7, 0xf6, 0xa5, 0x94, 0x03, 0x32, 0x61, 0x50, 
  0xbb, 0x8a, 0xd9, 0xe8, 0x7f, 0x4e, 0x1d, 0x2c, 0x02, 0x33, 0x60, 0x51, 0xc6, 0xf7, 0xa4, 0x95, 
  0xf8, 0xc9, 0x9a, 0xab, 0x3c, 0x0d, 0x5e, 0x6f, 0x41, 0x70, 0x23, 0x12, 0x85, 0xb4, 0xe7, 0xd6, 
  0x7a, 0x4b, 0x18, 0x29, 0xbe, 0x8f, 0xdc, 0xed, 0xc3, 0xf2, 0xa1, 0x90, 0x07, 0x36, 0x65, 0x54, 
  0x39, 0x08, 0x5b, 0x6a, 0xfd, 0xcc, 0x9f, 0xae, 0x80, 0xb1, 0xe2, 0xd3, 0x44, 0x75, 0x26, 0x17, 
  0xfc, 0xcd, 0x9e, 0xaf, 0x38, 0x09, 0x5a, 0x6b, 0x45, 0x74, 0x27, 0x16, 0x81, 0xb0, 0xe3, 0xd2, 
  0xbf, 0x8e, 0xdd, 0xec, 0x7b, 0x4a, 0x19, 0x28, 0x06, 0x37, 0x64, 0x55, 0xc2, 0xf3, 0xa0, 0x91, 
  0x47, 0x76, 0x25, 0x14, 0x83, 0xb2, 0xe1, 0xd0, 0xfe, 0xcf, 0x9c, 0xad, 0x3a, 0x0b, 0x58, 0x69, 
  0x04, 0x35, 0x66, 0x57, 0xc0, 0xf1, 0xa2, 0x93, 0xbd, 0x8c, 0xdf, 0xee, 0x79, 0x48, 0x1b, 0x2a, 
  0xc1, 0xf0, 0xa3, 0x92, 0x05, 0x34, 0x67, 0x56, 0x78, 0x49, 0x1a, 0x2b, 0xbc, 0x8d, 0xde, 0xef, 
  0x82, 0xb3, 0xe0, 0xd1, 0x46, 0x77, 0x24, 0x15, 0x3b, 0x0a, 0x59, 0x68, 0xff, 0xce, 0x9d, 0xac
};



// 使用CRC8表计算数据的CRC8值
//static uint8_t compute_crc8(uint8_t *data, uint16_t size) 
uint8_t compute_crc8(uint8_t *data, uint16_t size)
{
    //uint8_t crc = 0x00;  // 初始值设置为0
    uint8_t crc = 0xFF;  // 初始值设置为0
    
    while(size--) 
    {
        crc = crc8_table[crc ^ (*data)];
        data++;
    }
    return crc;
}
#endif



#if(defined(DEF_I2C_TYPE)&&(DEF_I2C_TYPE==DEF_I2C_TYPE_PSF))

#endif

#if(defined(DEF_I2C_TYPE)&&(DEF_I2C_TYPE==DEF_I2C_TYPE_MIDEA))

#if 0
#define DEF_PRODUCT_NBR     (0x12345678)
#define DEF_SERIAL_NBR1     (0x12345678)
#define DEF_SERIAL_NBR2     (0x9ABCDEF0)
#endif

uint8_t Usr_Product_Nbr[4] = 
{
    0x12,
    0x34,
    0x56,
    0x78
};

uint8_t Usr_Serial_Nbr1[8] = 
{
    0x12,
    0x34,
    0x56,
    0x78,
    0x9A,
    0xBC,
    0xDE,
    0xF0
};

uint8_t Usr_SnCrc1;
uint8_t Usr_SnCrc2;
uint8_t Usr_SnCrc3;
uint8_t Usr_SnCrc4;
uint8_t Usr_SnCrc5;
uint8_t Usr_SnCrc6;


uint8_t Usr_Md_Cmd1;
uint8_t Usr_Md_Cmd2;
uint16_t Usr_Md_CmdCode0;
uint16_t Usr_Md_CmdCode1;
uint16_t Usr_Md_CmdCode2;
uint8_t Usr_Md_State;

#endif


#endif



