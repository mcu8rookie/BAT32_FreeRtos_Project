/***********************************************************************************************************************
* Copyright (C) All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* @file    can.h
* @brief   This file implements device driver for CAN module.
* @version 1.0.0
* @date    2020/4/4
***********************************************************************************************************************/
#ifndef __CAN_H__
#define __CAN_H__

#include "core_cm0plus.h"                       /*!< ARM Cortex-M0+ processor and core peripherals                             */
#include "system_BAT32A237.h"                   /*!< BAT32A237 System                                                          */

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/
typedef struct {
	uint8_t ClockDivider;//clock divider
	uint8_t BitRatePrescaler;//bit rate prescaler
	uint16_t BitRate;//bit rate
	uint16_t IntEnable;//interrupt
	uint16_t OpMode;//operation mode
	uint32_t Mask1;//Mask1
	uint32_t Mask2;//Mask2
	uint32_t Mask3;//Mask3
	uint32_t Mask4;//Mask4
	
}CAN_InitTypeDef;

typedef struct {
	uint8_t Mode;//MODE
	uint8_t Rtr;//RTR
	uint8_t Ide;//IDE
	uint32_t Id;//ID
	uint8_t Ie;//interrupt
	uint8_t IdMaskNum;//Mask
	uint8_t Dlc;//Data length
	uint8_t Msgbuff[8];//Data
	
}CANMSG_INIT_Type;

typedef struct {
	uint8_t MsgRxStatus;//receive a new message flag
	uint32_t Id;//ID
	uint8_t Dlc;//Data length
	uint8_t Msgbuff[8];//Data
	
}CANMSG_REC_Type;

typedef struct {
	uint8_t MsgTxStatus;//transmit a new message flag
	uint32_t Id;//ID
	uint8_t Dlc;//Data length
	uint8_t Msgbuff[8];//Data
	
}CANMSG_TRX_Type;

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
//==========================================================================================================
//CAN global module clock select register GMCS
#define GMCS_DIV1 0U
#define GMCS_DIV2 1U
#define GMCS_DIV3 2U
#define GMCS_DIV4 3U
#define GMCS_DIV5 4U
#define GMCS_DIV6 5U
#define GMCS_DIV7 6U
#define GMCS_DIV8 7U
#define GMCS_DIV9 8U
#define GMCS_DIV10 9U
#define GMCS_DIV11 10U
#define GMCS_DIV12 11U
#define GMCS_DIV13 12U
#define GMCS_DIV14 13U
#define GMCS_DIV15 14U
#define GMCS_DIV16 15U

//CAN module bit rate prescaler register BRP
#define TQPRS(n) (n-1)

//CAN module bit rate register BTR
#define SJW_1TQ 0U<<12U
#define SJW_2TQ 1U<<12U
#define SJW_3TQ 2U<<12U
#define SJW_4TQ 3U<<12U

#define TSEG2_1TQ 0U<<8U
#define TSEG2_2TQ 1U<<8U
#define TSEG2_3TQ 2U<<8U
#define TSEG2_4TQ 3U<<8U
#define TSEG2_5TQ 4U<<8U
#define TSEG2_6TQ 5U<<8U
#define TSEG2_7TQ 6U<<8U
#define TSEG2_8TQ 7U<<8U

#define TSEG1_2TQ 1U
#define TSEG1_3TQ 2U
#define TSEG1_4TQ 3U
#define TSEG1_5TQ 4U
#define TSEG1_6TQ 5U
#define TSEG1_7TQ 6U
#define TSEG1_8TQ 7U
#define TSEG1_9TQ 8U
#define TSEG1_10TQ 9U
#define TSEG1_11TQ 10U
#define TSEG1_12TQ 11U
#define TSEG1_13TQ 12U
#define TSEG1_14TQ 13U
#define TSEG1_15TQ 14U
#define TSEG1_16TQ 15U


//Format of CAN Module Control Register CTRL
#define CTRL_RSTA_READ 0x0200U
#define CTRL_TSTA_READ 0x0100U
#define CTRL_CCERC_READ 0x0080U
#define CTRL_AL_READ 0x0040U
#define CTRL_VALID_READ 0x0020U
#define CTRL_PSMODE_READ 0x0018U
#define CTRL_OPMODE_READ 0x0007U

#define CTRL_CCERC_CLR 0x0080U
#define CTRL_AL_CLR 0x0040U
#define CTRL_VALID_CLR 0x0020U

#define CTRL_CCERC_SET 0x8000U
#define CTRL_AL_SET 0x4000U

#define PSMODE_IDLE 0x0018U
#define PSMODE_SLEEP 0x0810U//0x0800U
#define PSMODE_STOP 0x1800U

#define OPMODE_IDLE 0x0007U
#define OPMODE_NORMAL 0x0106U//0x0100U
#define OPMODE_NORMAL_ABT 0x0205U//0x0200U
#define OPMODE_ONLY_RX 0x0304U//0x0300U
#define OPMODE_SHOT 0x0403U//0x0400U
#define OPMODE_TEST 0x0502U//0x0500U

//CAN global module control register GMCTRL
#define GMCTRL_MBON_READ 0x8000U
#define GMCTRL_EFSD_READ 0x0002U
#define GMCTRL_GOM_READ 0x0001U

#define GMCTRL_EFSD_SET 0x0200U
#define GMCTRL_GOM_SET 0x0100U
#define GMCTRL_GOM_CLR 0x0001U

//CAN message control register MCTRL
#define MCTRL_MUC_READ 0x2000U
#define MCTRL_MOW_READ 0x0010U
#define MCTRL_IE_READ 0x0008U
#define MCTRL_DN_READ 0x0004U
#define MCTRL_TRQ_READ 0x0002U
#define MCTRL_RDY_READ 0x0001U

#define MCTRL_MOW_CLR 0x0010U

#define MCTRL_IE_SET 0x0800U
#define MCTRL_IE_CLR 0x0008U

#define MCTRL_DN_CLR 0x0004U

#define MCTRL_TRQ_SET 0x0200U
#define MCTRL_TRQ_CLR 0x0002U
#define MCTRL_RDY_SET 0x0100U
#define MCTRL_RDY_CLR 0x0001U

//CAN message configuration register MCONF
#define MCONF_OWS 0x80U
#define MCONF_RTR 0x40U

#define MCONF_MSGBUFF_MSK 0x38U
#define MCONF_TX_MSGBUFF 0x00U
#define MCONF_RX_MSGBUFF_NOMASK 0x08U
#define MCONF_RX_MSGBUFF_MASK1 0x10U
#define MCONF_RX_MSGBUFF_MASK2 0x18U
#define MCONF_RX_MSGBUFF_MASK3 0x20U
#define MCONF_RX_MSGBUFF_MASK4 0x28U


#define MCONF_MA0 0x01U

//CAN module interrupt enable register IE
#define IE_TX_READ 0x0001U
#define IE_RX_READ 0x0002U
#define IE_ERR_READ 0x0004U
#define IE_PERR_READ 0x0008U
#define IE_AL_READ 0x0010U
#define IE_WK_READ 0x0020U


#define IE_TX_SET 0x0100U
#define IE_TX_CLR 0x0001U
#define IE_RX_SET 0x0200U
#define IE_RX_CLR 0x0002U
#define IE_ERR_SET 0x0400U
#define IE_ERR_CLR 0x0004U
#define IE_PERR_SET 0x0800U
#define IE_PERR_CLR 0x0008U
#define IE_AL_SET 0x1000U
#define IE_AL_CLR 0x0010U
#define IE_WK_SET 0x2000U
#define IE_WK_CLR 0x0020U

//CAN module interrupt status register INTS
#define INTS_TX_READ 0x0001U
#define INTS_RX_READ 0x0002U
#define INTS_ERR_READ 0x0004U
#define INTS_PERR_READ 0x0008U
#define INTS_AL_READ 0x0010U
#define INTS_WK_READ 0x0020U


#define INTS_TX_CLR 0x0001U
#define INTS_RX_CLR 0x0002U
#define INTS_ERR_CLR 0x0004U
#define INTS_PERR_CLR 0x0008U
#define INTS_AL_CLR 0x0010U
#define INTS_WK_CLR 0x0020U

//CAN module receive history list register RGPT
#define RGPT_RHPM_READ 0x0002U
#define RGPT_ROVF_READ 0x0001U

#define RGPT_ROVF_CLR 0x0001U

//CAN module transmit history list register TGPT
#define TGPT_THPM_READ 0x0002U
#define TGPT_TOVF_READ 0x0001U

#define TGPT_TOVF_CLR 0x0001U

//CAN module time stamp register TS
#define TS_TSLOCK_READ 0x0004U
#define TS_TSSEL_READ 0x0002U
#define TS_TSEN_READ 0x0001U

#define TS_TSLOCK_SET 0x0400U
#define TS_TSSEL_SET 0x0200U
#define TS_TSEN_SET 0x0100U
#define TS_TSLOCK_CLR 0x0004U
#define TS_TSSEL_CLR 0x0002U
#define TS_TSEN_CLR 0x0001U

//CAN module last error code register LEC
#define LEC_NO_ERR 0U
#define LEC_STUFF_ERR 1U
#define LEC_FORM_ERR 2U
#define LEC_ACK_ERR 3U
#define LEC_RBIT_ERR 4U
#define LEC_DBIT_ERR 5U
#define LEC_CRC_ERR 6U

//CAN module information register INFO
#define INFO_BOFF 0x10U

//CAN global automatic block transmission control register GMABT
#define GMABT_ABTCLR_READ 0x0002U
#define GMABT_ABTTRG_READ 0x0001U

#define GMABT_ABTCLR_SET 0x0200U
#define GMABT_ABTTRG_SET 0x0100U
#define GMABT_ABTTRG_CLR 0x0001U

//CAN global automatic block transmission delay setting register GMABTD
#define GMABTD_ABTD0 0U	//0 DBT
#define GMABTD_ABTD1 1U	//2^5 DBT
#define GMABTD_ABTD2 2U	//2^6 DBT
#define GMABTD_ABTD3 3U	//2^7 DBT
#define GMABTD_ABTD4 4U	//2^8 DBT
#define GMABTD_ABTD5 5U	//2^9 DBT
#define GMABTD_ABTD6 6U	//2^10 DBT
#define GMABTD_ABTD7 7U	//2^11 DBT
#define GMABTD_ABTD8 8U	//2^12 DBT


//=================================================================================================================

#define CAN_RXMODE 0
#define CAN_TXMODE 1

/***********************************************************************************************************************
Global functions
***********************************************************************************************************************/
//=================================================================================================================
void CAN_Init(CAN_Type* pCAN, CAN_InitTypeDef* pCANInit);
void CAN_Start(CAN_Type* pCAN);
void CAN_Start_WithABT(CAN_Type* pCAN);
void CAN_Stop(CAN_Type* pCAN);
void CAN_Sleep(CAN_Type* pCAN);
void CAN_Exit_Sleep(CAN_Type* pCAN);
void MSG_Init(CANMSG_Type* pMSG);

void Config_MSGBuffer(CANMSG_Type* pMSG, CANMSG_INIT_Type* pMSG_Init);
void Transmit_MSGBuffer(CANMSG_Type* pMSG, CANMSG_INIT_Type* pMSG_Init);
void Transmit_MSGBuffer_WithABT(CAN_Type* pCAN, CANMSG_Type* pMSG, CANMSG_INIT_Type* pMSG_Init, uint8_t mCount);
void Msg_Init_Clr(CANMSG_INIT_Type* pMsg_Str);

#endif
