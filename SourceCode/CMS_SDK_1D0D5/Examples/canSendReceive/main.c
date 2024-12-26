/***********************************************************************************************************************
* Copyright (C) . All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name    : main.c
* Version      :  
* Device(s)    : BAT32A237
* Tool-Chain   : MDK(armcc)
* Description  : This file is a template.
* Creation Date: 2020/11/02
***********************************************************************************************************************/

/***********************************************************************************************************************
Macro Definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include <stdio.h>
#include "BAT32A237.h"
#include "userdefine.h"
#include "sci.h"
#include "can.h"
#include "adc.h"
#include "clk.h"
#include "gpio.h"
#include "iica.h"
#include "intp.h"
#include "rtc.h"
#include "key.h"
#include "wdt.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
volatile uint32_t g_ticks;
CAN_InitTypeDef CANInitStruct;
CANMSG_INIT_Type Msg_Init;
CANMSG_INIT_Type Msg_Init_buff[8];

uint16_t Tempbuf[4];
extern uint16_t gTemp;

#if defined(CAN0_USE)
extern uint8_t gCanerror0flag;
extern CANMSG_REC_Type can0MsgRec[16];
#endif

extern void MsgRec_Clr(CANMSG_REC_Type* pMsg_Rec);

//-----------------------------------------------------------------------	
//GPIO Initialize
//-----------------------------------------------------------------------	
void GPIO_Init(void)
{
	//PORT->P1 = 0x00;
	PORT->P6 = 0xff;
	PORT->P7 = 0xff;
	
	PORT->PM0 = 0x00;
	PORT->PM1 = 0x00;
	PORT->PM2 = 0x00;
	PORT->PM3 = 0x00;
	PORT->PM4 = 0x01;//P40-> SWDDAT
	PORT->PM5 = 0x00;
	PORT->PM6 = 0x00;
	PORT->PM7 = 0x00;
	PORT->PM12 = 0x00;
	PORT->PM13 = 0x80;//P137-> SWDCLK
	PORT->PM14 = 0x00;
	
	PORT->PMC0 = 0x00;	/*config digital IO*/
	PORT->PMC1 = 0x00;
	PORT->PMC2 = 0x00;
	PORT->PMC12 = 0x00;
	PORT->PMC14 = 0x00;
	
#if defined(CAN1_USE)
	PORT_Init(PORT13,PIN0,OUTPUT);//P130 output mode
	//PORT_SetBit(PORT12,PIN0);
	PORT_ClrBit(PORT13,PIN0);
#endif

#if defined(CAN0_USE)
	PORT_Init(PORT12,PIN0,OUTPUT);//P120 output mode
	//PORT_SetBit(PORT12,PIN0);
	PORT_ClrBit(PORT12,PIN0);
#endif	
	
}

//-----------------------------------------------------------------------	
//APPCODE Remap
//-----------------------------------------------------------------------
void APPCODE_Remap(uint32_t vector_addr)
{
	__disable_irq();
	SCB->VTOR = vector_addr;/*vector address*/
	__DMB();	
	__enable_irq();

}

void cpu_delay_xms(uint32_t xms)
{
	uint32_t i;
	do
	{
		i = 12*1000;
		do
		{
			
		}while(--i);
	}while(--xms);
}

//***********************************************************************************************************************
//CAN0 Initialize
//***********************************************************************************************************************
#ifdef CAN0_USE
void CAN0_Init(void)
{
	uint32_t i;
	CANMSG_Type* pCANmsg;

	CANInitStruct.ClockDivider = GMCS_DIV1;//12M/1
	CANInitStruct.BitRatePrescaler = TQPRS(3);//fcanmod/3  
	CANInitStruct.BitRate = SJW_1TQ|TSEG2_2TQ|TSEG1_5TQ;//500Kbps	Baud = Fclk/8/(C0GMCS+1)/(C0BRP+1)
	CANInitStruct.IntEnable = IE_RX_SET|IE_ERR_SET|IE_PERR_SET|IE_AL_SET|IE_TX_SET|IE_WK_SET;//config CAN interrupt
	CANInitStruct.Mask1 = CAN_REC_MASK1;
	CANInitStruct.Mask2 = CAN_REC_MASK2;
	CANInitStruct.Mask3 = CAN_REC_MASK3;
	CANInitStruct.Mask4 = CAN_REC_MASK4;
	
	CAN_Init(CAN0,&CANInitStruct);
	CAN_Start(CAN0);

//-----------------------------------------------------------------------	
//CAN msg Initialize
//-----------------------------------------------------------------------

	pCANmsg = CAN0MSG00;
	for(i=0;i<16;i++)//Initialize Message buffer0-15
	{
		MSG_Init(pCANmsg++);
	}

//-----------------------------------------------------------------------	
//CAN Receive Message buffer initialize
//-----------------------------------------------------------------------	
	MsgRec_Clr(can0MsgRec);
	
	Msg_Init_Clr(&Msg_Init);
	Msg_Init.Mode = CAN_RXMODE;
	Msg_Init.Ie = 1;//enable receive interrupt
	Msg_Init.Id = 0x231;//standard ID
	Msg_Init.IdMaskNum = MCONF_RX_MSGBUFF_NOMASK;//no mask
	
	Config_MSGBuffer(CAN0MSG08,&Msg_Init);//config Receive Message buffer8
	
	Msg_Init_Clr(&Msg_Init);
	Msg_Init.Mode = CAN_RXMODE;
	Msg_Init.Ie = 1;//enable receive interrupt
	Msg_Init.Id = 0x12319AF8;//ID
	Msg_Init.Ide = 1;//extended ID
	Msg_Init.IdMaskNum = MCONF_RX_MSGBUFF_MASK1;//mask 1
	
	Config_MSGBuffer(CAN0MSG09,&Msg_Init);//config Receive Message buffer9
	
	Msg_Init_Clr(&Msg_Init);
	Msg_Init.Mode = CAN_RXMODE;
	Msg_Init.Ie = 1;//enable receive interrupt
	Msg_Init.Id = 0x12319AF8;//ID
	Msg_Init.Ide = 1;//extended ID
	Msg_Init.IdMaskNum = MCONF_RX_MSGBUFF_MASK2;//mask 2
		
	Config_MSGBuffer(CAN0MSG10,&Msg_Init);//config Receive Message buffer10
	
	Msg_Init_Clr(&Msg_Init);
	Msg_Init.Mode = CAN_RXMODE;
	Msg_Init.Ie = 1;//enable receive interrupt
	Msg_Init.Id = 0x75A;//ID
	Msg_Init.Ide = 0;//standard ID
	Msg_Init.IdMaskNum = MCONF_RX_MSGBUFF_MASK3;//mask 3
		
	Config_MSGBuffer(CAN0MSG11,&Msg_Init);//config Receive Message buffer11
	
	Msg_Init_Clr(&Msg_Init);
	Msg_Init.Mode = CAN_RXMODE;
	Msg_Init.Ie = 1;//enable receive interrupt
	Msg_Init.Id = 0x12319A77;//ID
	Msg_Init.Ide = 1;//extended ID
	Msg_Init.IdMaskNum = MCONF_RX_MSGBUFF_MASK4;//mask 4
		
	Config_MSGBuffer(CAN0MSG12,&Msg_Init);//config Receive Message buffer12
	
	Msg_Init_Clr(&Msg_Init);
	Msg_Init.Mode = CAN_RXMODE;
	Msg_Init.Ie = 1;//enable receive interrupt
	Msg_Init.Id = 0x12319A10;//ID
	Msg_Init.Ide = 1;//extended ID
	Msg_Init.IdMaskNum = MCONF_RX_MSGBUFF_MASK1;//mask 1
		
	Config_MSGBuffer(CAN0MSG13,&Msg_Init);//config Receive Message buffer13
	
	Msg_Init_Clr(&Msg_Init);
	Msg_Init.Mode = CAN_RXMODE;
	Msg_Init.Ie = 1;//enable receive interrupt
	Msg_Init.Id = 0x12319A23;//ID
	Msg_Init.Ide = 1;//extended ID
	Msg_Init.IdMaskNum = MCONF_RX_MSGBUFF_MASK2;//mask 2
	
	Config_MSGBuffer(CAN0MSG14,&Msg_Init);//config Receive Message buffer14
	
	Msg_Init_Clr(&Msg_Init);
	Msg_Init.Mode = CAN_RXMODE;
	Msg_Init.Ie = 1;//enable receive interrupt
	Msg_Init.Id = 0x12319A20;//ID
	Msg_Init.Ide = 1;//extended ID
	Msg_Init.IdMaskNum = MCONF_RX_MSGBUFF_MASK3;//mask 3
		
	Config_MSGBuffer(CAN0MSG15,&Msg_Init);//config Receive Message buffer15
	
//-----------------------------------------------------------------------	
//CAN Transmit Message buffer initialize
//-----------------------------------------------------------------------	
	
	Msg_Init_Clr(&Msg_Init);
	Msg_Init.Mode = CAN_TXMODE;
	Msg_Init.Ie = 1;//enable transmit interrupt
	Msg_Init.Id = 0x731;//ID
	Msg_Init.Dlc = 8;//Data Length
	Msg_Init.Msgbuff[0] = 0x12;
	Msg_Init.Msgbuff[1] = 0x23;
	Msg_Init.Msgbuff[2] = 0x45;
	Msg_Init.Msgbuff[3] = 0x67;
	Msg_Init.Msgbuff[4] = 0x89;
	Msg_Init.Msgbuff[5] = 0x55;
	Msg_Init.Msgbuff[6] = 0xaa;
	Msg_Init.Msgbuff[7] = 0x0f;
		
	Config_MSGBuffer(CAN0MSG00,&Msg_Init);//config Transmit Message buffer0
	
//Remote frame Receiver
//	Msg_Init_Clr(&Msg_Init);
//	Msg_Init.Mode = CAN_TXMODE;
//	Msg_Init.Rtr = 1;//enable remote frame
//	Msg_Init.Ie = 1;//enable transmit interrupt
//	Msg_Init.Id = 0x431;//ID
//	Msg_Init.Dlc = 0;//Data Length
//	Msg_Init.Msgbuff[0] = 0x12;
//	Msg_Init.Msgbuff[1] = 0x23;
//	Msg_Init.Msgbuff[2] = 0x45;
//	Msg_Init.Msgbuff[3] = 0x67;
//	Msg_Init.Msgbuff[4] = 0x89;
//	Msg_Init.Msgbuff[5] = 0x55;
//	Msg_Init.Msgbuff[6] = 0xaa;
//	Msg_Init.Msgbuff[7] = 0x0f;
//	
//	Config_MSGBuffer(CAN0MSG01,&Msg_Init);//config Transmit Message buffer1

}
#endif

//***********************************************************************************************************************
int main()
{
//	uint32_t msCnt; 	// count value of 1ms
//	uint32_t err;
	
	MD_STATUS status;
//	uint32_t txcount;
	rtc_alarm_value_t alarm_val;
	
//-----------------------------------------------------------------------
// APP code address Remap 
//-----------------------------------------------------------------------   
//	APPCODE_Remap(0x00001000);//bootloader rom: 4K size
	
//-----------------------------------------------------------------------
// Clock setting 
//-----------------------------------------------------------------------	
	CLK_Osc_Setting(OSC_OSCILLATOR, OSC_OSCILLATOR); /* MainOSC/SubOSC enable */
	CLK_Fclk_Select(MAINCLK_FMX);//select FMX 12MHz
	while((CGC->CKC & CGC_CKC_MCS_Msk) == 0);

//-----------------------------------------------------------------------
// Systick setting 
//-----------------------------------------------------------------------   
	
	SystemCoreClock = CPU_CLOCK_FREQ;
	SysTick_Config(SystemCoreClock/1000);//1ms
	
//-----------------------------------------------------------------------	
//GPIO Initialize
//-----------------------------------------------------------------------	
	GPIO_Init();
//-----------------------------------------------------------------------	
//ADC Initialize
//-----------------------------------------------------------------------	
	
//	ADC_Init();	
//-----------------------------------------------------------------------
// Init UART0 for retarget printf/scanf etc. 
//----------------------------------------------------------------------- 
	status = UART0_Init(SystemCoreClock, 38400);//38400bps
	if(status == MD_ERROR)
	{
		while(1); // The baud rate cannot get at the current system clock frequency.
	}
	
	printf("Hello, BAT32A237 CAN Test!\n");

//-----------------------------------------------------------------------	
//RTC Initialize
//-----------------------------------------------------------------------
	
	
	if(!(CGC->PER0  & CGC_PER0_RTCEN_Msk))     /* RTC clock is enable? */
	{
		RTC_Init(RTC_FSUB);
		RTC_Start();
		date_time.year  = 0x20;
		date_time.month = 0x11;
		date_time.week  = MONDAY; 
		date_time.day   = 0x02;
		date_time.hour  = 0x08;
		date_time.min   = 0x30;
		date_time.sec   = 0x00;
		RTC_Set_CounterValue(&date_time);
		
		alarm_val.alarmwm = 0x31;
		alarm_val.alarmwh = 0x08;
		alarm_val.alarmww = 0x7f;
		RTC_Set_AlarmValue(alarm_val);
		RTC_Set_AlarmOn();
		
	}
	
//-----------------------------------------------------------------------	
//CAN Initialize
//-----------------------------------------------------------------------
#ifdef CAN0_USE	
	CAN0_Init();
#endif

/***********************************************************************************************************************/
	while(1)
	{
		WDT_Restart();
//		if(txcount)
//		{
//			RTC_Get_CounterValue(&date_time);
//			
//			Msg_Init_Clr(&Msg_Init);
//			Msg_Init.Mode = CAN_TXMODE;
//			Msg_Init.Ie = 0;//disable transmit interrupt
//			Msg_Init.Id = 0x731;//ID
//			Msg_Init.Dlc = 8;//Data Length
//			Msg_Init.Msgbuff[0] = date_time.year;
//			Msg_Init.Msgbuff[1] = date_time.month;
//			Msg_Init.Msgbuff[2] = date_time.day;
//			Msg_Init.Msgbuff[3] = date_time.week;
//			Msg_Init.Msgbuff[4] = date_time.hour;
//			Msg_Init.Msgbuff[5] = date_time.min;
//			Msg_Init.Msgbuff[6] = date_time.sec;
//			Msg_Init.Msgbuff[7] = 'T';
//			
//			Transmit_MSGBuffer(CANMSG00,&Msg_Init);//Transmit Message buffer0
//			txcount--;
//		}
		
		if(g_ticks >= 200)//500ms
		{
			
			g_ticks = 0;
			
			RTC_Get_CounterValue(&date_time);
			
//			gTemp = ADC_Converse(ADC_TEMPERSENSOR0, sizeof(Tempbuf)/2, Tempbuf);
			
#ifdef CAN0_USE			
			if(gCanerror0flag)
			{
				gCanerror0flag = 0;
				CAN0_Init();
				
			}
#endif			
	
						
			Msg_Init_Clr(&Msg_Init_buff[0]);
			Msg_Init_buff[0].Mode = CAN_TXMODE;
			Msg_Init_buff[0].Ie = 0;//disable transmit interrupt
			Msg_Init_buff[0].Id = 0x731;//ID
			Msg_Init_buff[0].Dlc = 8;//Data Length
			Msg_Init_buff[0].Msgbuff[0] = date_time.year;
			Msg_Init_buff[0].Msgbuff[1] = date_time.month;
			Msg_Init_buff[0].Msgbuff[2] = date_time.day;
			Msg_Init_buff[0].Msgbuff[3] = date_time.week;
			Msg_Init_buff[0].Msgbuff[4] = date_time.hour;
			Msg_Init_buff[0].Msgbuff[5] = date_time.min;
			Msg_Init_buff[0].Msgbuff[6] = date_time.sec;
			
			#ifdef CAN0_USE
			Msg_Init_buff[0].Msgbuff[7] = 'A';
			Transmit_MSGBuffer(CAN0MSG00,&Msg_Init_buff[0]);//Transmit Message buffer0
			#endif
			
			//enter deep sleep mode
//			printf("Power down!\n");
			//GPIO Init
//			ADC_Stop();
//			ADC_Set_OperationOff();
//			
//			CAN_Sleep();
//			
//			KR_Init();
//			
//			PORT_SetBit(PORT12,PIN0);//CAN tranceiver standby
//			PORT->P7 = 0x06;
//			WDT_Restart();
//			
//			__STOP();
//			
//			g_ticks = 0;
//			txcount = 1;
//			
//			PORT_ClrBit(PORT12,PIN0);//CAN tranceiver enable
//			
////			printf("Wake up!\n");
//			CAN_Exit_Sleep();
//			PORT->P7 = 0x00;
//			ADC_Init();
//			CAN_Init();
//			CAN_Start();
		}
	}

}

/***********************************************************************************************************************
* Function Name: SysTick Handler
* Description  : Decreament the g_ticks value
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void SysTick_Handler(void)
{
	g_ticks++;
}


