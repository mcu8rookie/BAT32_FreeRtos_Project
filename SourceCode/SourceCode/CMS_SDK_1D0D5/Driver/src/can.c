/***********************************************************************************************************************
* Copyright (C) All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* @file    can.c
* @brief   This file implements device driver for CAN module.
* @version 1.0.0  
* @date    2022/2/25
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "BAT32A237.h"
#include "userdefine.h"
#include "can.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
//----------------------------------------------------------------------------------------------------------------------


/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/


/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: MSG_Init
* @brief  This function initializes the message buffer m.
* @param  pMSG - the pointer of Message
* @return None
***********************************************************************************************************************/
void MSG_Init(CANMSG_Type* pMSG)
{
	
	while(pMSG->CMCTRL&MCTRL_RDY_READ)
	{
		pMSG->CMCTRL = MCTRL_RDY_CLR;
	}
	
	pMSG->CMCONF &= ~MCONF_MA0;
	pMSG->CMCONF &= ~MCONF_MSGBUFF_MSK;
	
	pMSG->CMCTRL = MCTRL_DN_CLR;
	pMSG->CMCTRL = MCTRL_TRQ_CLR;
	pMSG->CMCTRL = MCTRL_RDY_CLR;
}
/***********************************************************************************************************************
* Function Name: Config_MSGBuffer
* @brief  This function config the message buffer m.
* @param  pMSG - the pointer of Message
* @param  pMSG_Init - the pointer of Message Init struct
* @return None
***********************************************************************************************************************/
void Config_MSGBuffer(CANMSG_Type* pMSG, CANMSG_INIT_Type* pMSG_Init)
{
	
	while(pMSG->CMCTRL&MCTRL_RDY_READ)
	{
		pMSG->CMCTRL = MCTRL_RDY_CLR;
	}
	
	pMSG->CMCONF = MCONF_MA0;
	
	pMSG->CMCONF &= ~MCONF_MSGBUFF_MSK;
	if(pMSG_Init->Mode==CAN_TXMODE)//transmit message
	{
		
		if(pMSG_Init->Ide==1)
		{
			pMSG->CMIDL = pMSG_Init->Id&0xffff;
			pMSG->CMIDH = ((pMSG_Init->Id>>16U)&0xffff)|0x8000;
			
		}
		else
		{
			pMSG->CMIDL = 0;
			pMSG->CMIDH = (pMSG_Init->Id<<2U)&0x1ffc;
		}
		
		if(pMSG_Init->Rtr==1)
		{
			pMSG->CMCONF |= MCONF_RTR;
		}
		else
		{
			pMSG->CMCONF &= ~MCONF_RTR;
		}
		
		pMSG->CMDLC = pMSG_Init->Dlc;
		
		pMSG->CMDB0 = pMSG_Init->Msgbuff[0];
		pMSG->CMDB1 = pMSG_Init->Msgbuff[1];
		pMSG->CMDB2 = pMSG_Init->Msgbuff[2];
		pMSG->CMDB3 = pMSG_Init->Msgbuff[3];
		pMSG->CMDB4 = pMSG_Init->Msgbuff[4];
		pMSG->CMDB5 = pMSG_Init->Msgbuff[5];
		pMSG->CMDB6 = pMSG_Init->Msgbuff[6];
		pMSG->CMDB7 = pMSG_Init->Msgbuff[7];
	}
	else// Receive message
	{
		
		if(pMSG_Init->Ide==1)
		{
			pMSG->CMIDL = pMSG_Init->Id&0xffff;
			pMSG->CMIDH = ((pMSG_Init->Id>>16U)&0xffff)|0x8000;
			
		}
		else
		{
			pMSG->CMIDL = 0;
			pMSG->CMIDH = (pMSG_Init->Id<<2U)&0x1ffc;
		}
		
//		if(pMSG_Init->Rtr==1)
//		{
//			pMSG->CMCONF |= MCONF_RTR;
//		}
//		else
		{
			pMSG->CMCONF &= ~MCONF_RTR;
		}
		
		pMSG->CMCONF |= pMSG_Init->IdMaskNum;//config Message mask
		
	}
	
	if(pMSG_Init->Ie)//Message interrupt
	{
		pMSG->CMCTRL = MCTRL_IE_SET;
	}
	else
	{
		pMSG->CMCTRL = MCTRL_IE_CLR;
	}
	
	pMSG->CMCTRL = MCTRL_RDY_SET;
	
	if(pMSG_Init->Mode==CAN_TXMODE)
	{
		pMSG->CMCTRL = MCTRL_TRQ_SET;
	}
	
	
}
/***********************************************************************************************************************
* Function Name: Transmit_MSGBuffer
* @brief  This function transmit the message buffer m.
* @param  pMSG - the pointer of Message
* @param  pMSG_Init - the pointer of Message Init struct
* @return None
***********************************************************************************************************************/
void Transmit_MSGBuffer(CANMSG_Type* pMSG, CANMSG_INIT_Type* pMSG_Init)
{
	
	while(pMSG->CMCTRL&MCTRL_TRQ_READ);
	
	while(pMSG->CMCTRL&MCTRL_RDY_READ)
	{
		pMSG->CMCTRL = MCTRL_RDY_CLR;
	}
	
	pMSG->CMCONF = MCONF_MA0;
	
	pMSG->CMCONF &= ~MCONF_MSGBUFF_MSK;
	if(pMSG_Init->Mode==CAN_TXMODE)//transmit message
	{
		
		if(pMSG_Init->Ide==1)
		{
			pMSG->CMIDL = pMSG_Init->Id&0xffff;
			pMSG->CMIDH = ((pMSG_Init->Id>>16U)&0xffff)|0x8000;
			
		}
		else
		{
			pMSG->CMIDL = 0;
			pMSG->CMIDH = (pMSG_Init->Id<<2U)&0x1ffc;
		}
		
		if(pMSG_Init->Rtr==1)
		{
			pMSG->CMCONF |= MCONF_RTR;
		}
		else
		{
			pMSG->CMCONF &= ~MCONF_RTR;
		}
		
		pMSG->CMDLC = pMSG_Init->Dlc;
		
		pMSG->CMDB0 = pMSG_Init->Msgbuff[0];
		pMSG->CMDB1 = pMSG_Init->Msgbuff[1];
		pMSG->CMDB2 = pMSG_Init->Msgbuff[2];
		pMSG->CMDB3 = pMSG_Init->Msgbuff[3];
		pMSG->CMDB4 = pMSG_Init->Msgbuff[4];
		pMSG->CMDB5 = pMSG_Init->Msgbuff[5];
		pMSG->CMDB6 = pMSG_Init->Msgbuff[6];
		pMSG->CMDB7 = pMSG_Init->Msgbuff[7];
	}
	
	if(pMSG_Init->Ie)//Message interrupt
	{
		pMSG->CMCTRL = MCTRL_IE_SET;
	}
	else
	{
		pMSG->CMCTRL = MCTRL_IE_CLR;
	}
	
	pMSG->CMCTRL = MCTRL_RDY_SET;
	
	if(pMSG_Init->Mode==CAN_TXMODE)
	{
		pMSG->CMCTRL = MCTRL_TRQ_SET;
	}
	
	
}
/***********************************************************************************************************************
* Function Name: Transmit_MSGBuffer_WithABT
* @brief  This function transmit the message buffers with ABT.
* @param  pCAN Pointer to a CAN
* @param  pMSG - the pointer of Message
* @param  pMSG_Init - the pointer of Message Init struct
* @return None
***********************************************************************************************************************/
void Transmit_MSGBuffer_WithABT(CAN_Type* pCAN, CANMSG_Type* pMSG, CANMSG_INIT_Type* pMSG_Init, uint8_t mCount)
{
	uint8_t i;
	
	while(pCAN->CGMABT&GMABT_ABTTRG_READ);
	
	for(i=0;i<mCount;i++)
	{
		while(pMSG->CMCTRL&MCTRL_RDY_READ)
		{
			pMSG->CMCTRL = MCTRL_RDY_CLR;
		}
		
		pMSG->CMCONF = MCONF_MA0;
		
		pMSG->CMCONF &= ~MCONF_MSGBUFF_MSK;
//		if(pMSG_Init->Mode==CAN_TXMODE)//transmit message
		{
			
			if(pMSG_Init->Ide==1)
			{
				pMSG->CMIDL = pMSG_Init->Id&0xffff;
				pMSG->CMIDH = ((pMSG_Init->Id>>16U)&0xffff)|0x8000;
				
			}
			else
			{
				pMSG->CMIDL = 0;
				pMSG->CMIDH = (pMSG_Init->Id<<2U)&0x1ffc;
			}
			
	//		if(pMSG_Init->Rtr==1)
	//		{
	//			pMSG->CMCONF |= MCONF_RTR;
	//		}
	//		else
			{
				pMSG->CMCONF &= ~MCONF_RTR;
			}
			
			pMSG->CMDLC = pMSG_Init->Dlc;
			
			pMSG->CMDB0 = pMSG_Init->Msgbuff[0];
			pMSG->CMDB1 = pMSG_Init->Msgbuff[1];
			pMSG->CMDB2 = pMSG_Init->Msgbuff[2];
			pMSG->CMDB3 = pMSG_Init->Msgbuff[3];
			pMSG->CMDB4 = pMSG_Init->Msgbuff[4];
			pMSG->CMDB5 = pMSG_Init->Msgbuff[5];
			pMSG->CMDB6 = pMSG_Init->Msgbuff[6];
			pMSG->CMDB7 = pMSG_Init->Msgbuff[7];
		}
		
//		if(pMSG_Init->Ie)//Message interrupt
//		{
//			pMSG->CMCTRL = MCTRL_IE_SET;
//		}
//		else
//		{
//			pMSG->CMCTRL = MCTRL_IE_CLR;
//		}
		
		pMSG->CMCTRL = MCTRL_RDY_SET;
		
		pMSG_Init++;
		pMSG++;
	}
	
	while(pCAN->CCTRL&CTRL_TSTA_READ);
	
	pCAN->CGMABT = GMABT_ABTTRG_SET;
	
}
/***********************************************************************************************************************
* Function Name: Msg_Init_Clr
* @brief  This function Clear the Message initialize struct.
* @param  pMsg_Str - the pointer of Message
* @return None
***********************************************************************************************************************/
void Msg_Init_Clr(CANMSG_INIT_Type* pMsg_Str)
{
	uint32_t i;
	uint8_t* pMsgDat;
	
	pMsgDat = (uint8_t*)pMsg_Str;
	for(i=0;i<sizeof(CANMSG_INIT_Type);i++)
	{
		pMsgDat[i] = 0;
	}
}
/***********************************************************************************************************************
* Function Name: CAN_Init
* @brief  This function initializes the CAN.
* @param  pCAN Pointer to a CAN
* @param  pCANInit Pointer to a CAN_InitTypeDef structure
* @return None
***********************************************************************************************************************/

void CAN_Init(CAN_Type* pCAN, CAN_InitTypeDef* pCANInit)
{
	if(CAN0 == pCAN)
	{
		CGC->PER0 |= CGC_PER0_CAN0EN_Msk;    /* enables input clock supply */
	}
	
	pCAN->CGMCS = pCANInit->ClockDivider;//clock divider
	pCAN->CGMCTRL = GMCTRL_GOM_SET;//set GOM
	pCAN->CBRP = pCANInit->BitRatePrescaler;//bit rate prescaler  
	pCAN->CBTR = pCANInit->BitRate;//bit rate
	pCAN->CIE = pCANInit->IntEnable;//config CAN interrupt
	pCAN->CMASK1L = pCANInit->Mask1&0xffff;//Mask 1
	pCAN->CMASK1H = (pCANInit->Mask1>>16)&0x1fff;
	pCAN->CMASK2L = pCANInit->Mask2&0xffff;//Mask 2
	pCAN->CMASK2H = (pCANInit->Mask2>>16)&0x1fff;
	pCAN->CMASK3L = pCANInit->Mask3&0xffff;//Mask 3
	pCAN->CMASK3H = (pCANInit->Mask3>>16)&0x1fff;
	pCAN->CMASK4L = pCANInit->Mask4&0xffff;//Mask 4
	pCAN->CMASK4H = (pCANInit->Mask4>>16)&0x1fff;
	
	pCAN->CCTRL = CTRL_CCERC_CLR|CTRL_AL_CLR|CTRL_VALID_CLR|PSMODE_IDLE|OPMODE_IDLE;
	
	if(CAN0 == pCAN)
	{
    /* Set CAN0TXD pin */
    CTXD0_PORT_SETTING();
    /* Set CAN0RXD pin */
    CRXD0_PORT_SETTING();
	}
  
}

/***********************************************************************************************************************
* Function Name: CAN_Start
* @brief  This function starts the CAN.
* @param  pCAN Pointer to a CAN
* @return None
***********************************************************************************************************************/
void CAN_Start(CAN_Type* pCAN)
{
  pCAN->CCTRL = OPMODE_NORMAL;
	if(CAN0 == pCAN)
	{
		INTC_ClearPendingIRQ(CAN0REC_IRQn);    /* clear CAN0REC interrupt flag */
		INTC_EnableIRQ(CAN0REC_IRQn);          /* enable CAN0REC interrupt */
		INTC_ClearPendingIRQ(CAN0TRX_IRQn);    /* clear CAN0TRX interrupt flag */
//	INTC_EnableIRQ(CAN0TRX_IRQn);          /* enable CAN0TRX interrupt */
//	__NVIC_SetPriority(CAN0TRX_IRQn%32, 0);

		INTC_ClearPendingIRQ(CAN0ERR_IRQn);    /* clear CAN0ERR interrupt flag */
		INTC_EnableIRQ(CAN0ERR_IRQn);          /* enable CAN0ERR interrupt */
	}
	
}
/***********************************************************************************************************************
* Function Name: CAN_Start_WithABT
* @brief  This function starts the CAN with ABT.
* @param  pCAN Pointer to a CAN
* @return None
***********************************************************************************************************************/
void CAN_Start_WithABT(CAN_Type* pCAN)
{
  pCAN->CCTRL = OPMODE_NORMAL_ABT;
	if(CAN0 == pCAN)
	{	
		INTC_ClearPendingIRQ(CAN0REC_IRQn);    /* clear CAN0REC interrupt flag */
		INTC_EnableIRQ(CAN0REC_IRQn);          /* enable CAN0REC interrupt */
		INTC_ClearPendingIRQ(CAN0TRX_IRQn);    /* clear CAN0TRX interrupt flag */
		INTC_EnableIRQ(CAN0TRX_IRQn);          /* enable CAN0TRX interrupt */
		INTC_ClearPendingIRQ(CAN0ERR_IRQn);    /* clear CAN0ERR interrupt flag */
		INTC_EnableIRQ(CAN0ERR_IRQn);          /* enable CAN0ERR interrupt */
	}
	
}
/***********************************************************************************************************************
* Function Name: CAN_Stop
* @brief  This function stops the CAN.
* @param  pCAN Pointer to a CAN
* @return None
***********************************************************************************************************************/
void CAN_Stop(CAN_Type* pCAN)
{
   
  pCAN->CCTRL = CTRL_CCERC_CLR|CTRL_AL_CLR|CTRL_VALID_CLR|PSMODE_IDLE|OPMODE_IDLE; 
	if(CAN0 == pCAN)
	{
		INTC_DisableIRQ(CAN0REC_IRQn);         /* disable CAN0REC interrupt */
		INTC_ClearPendingIRQ(CAN0REC_IRQn);    /* clear CAN0REC interrupt flag */
		CGC->PER0 &= ~CGC_PER0_CAN0EN_Msk;    /* disable input clock supply */
		
	}
	
		
}
/***********************************************************************************************************************
* Function Name: CAN_Sleep
* @brief  This function let the CAN enter sleep.
* @param  pCAN Pointer to a CAN
* @return None
***********************************************************************************************************************/
void CAN_Sleep(CAN_Type* pCAN)
{
//    CAN->CCTRL = CTRL_CCERC_CLR|CTRL_AL_CLR|CTRL_VALID_CLR|PSMODE_IDLE|OPMODE_IDLE; 
//	INTC_DisableIRQ(CAN0REC_IRQn);         /* disable CAN0REC interrupt */
//	INTC_ClearPendingIRQ(CAN0REC_IRQn);    /* clear CAN0REC interrupt flag */
	pCAN->CCTRL = PSMODE_SLEEP;	/*enter sleep mode*/
	if(CAN0 == pCAN)
	{
		INTC_ClearPendingIRQ(CAN0WUP_IRQn);    /* clear CAN0WUp interrupt flag */
		INTC_EnableIRQ(CAN0WUP_IRQn);         /* enable CAN0WUp interrupt */
	}
	
}
/***********************************************************************************************************************
* Function Name: CAN_Exit_Sleep
* @brief  This function let the CAN exit sleep.
* @param  pCAN Pointer to a CAN
* @return None
***********************************************************************************************************************/
void CAN_Exit_Sleep(CAN_Type* pCAN)
{

	pCAN->CCTRL = PSMODE_IDLE;	/*exit sleep mode*/
	if(CAN0 == pCAN)
	{
		INTC_ClearPendingIRQ(CAN0WUP_IRQn);    /* clear CAN0WUp interrupt flag */
		INTC_DisableIRQ(CAN0WUP_IRQn);         /* disable CAN0WUp interrupt */
	}
	
}
/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
