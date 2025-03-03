/***********************************************************************************************************************
* Copyright (C) All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* @file    isr.c
* @brief   This file implements device driver for interrupt module.
* @version 1.0.0
* @date    2021/06/03
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "userdefine.h"
#include "BAT32A237.h"


/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/


/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/

/***********************************************************IRQ00_Handler************************************************************/

__WEAK void lvi_interrupt(void)
{
	INTC_ClearPendingIRQ(LVI_IRQn);
}

void IRQ00_Handler(void)
{
		if(INTC_GetPendingIRQ(LVI_IRQn))
		{
			lvi_interrupt();
		}
		
}

/***********************************************************IRQ01_Handler************************************************************/

__WEAK void intp0_interrupt(void)
{
	INTC_ClearPendingIRQ(INTP0_IRQn);
}
__WEAK void intp6_interrupt(void)
{
	INTC_ClearPendingIRQ(INTP6_IRQn);
}

void IRQ01_Handler(void)
{
		if(INTC_GetPendingIRQ(INTP0_IRQn))
		{
			intp0_interrupt();
		}
		
		if(INTC_GetPendingIRQ(INTP6_IRQn))
		{
			intp6_interrupt();
		}
		
}

/***********************************************************IRQ02_Handler************************************************************/

__WEAK void intp1_interrupt(void)
{
	INTC_ClearPendingIRQ(INTP1_IRQn);
}
__WEAK void intp7_interrupt(void)
{
	INTC_ClearPendingIRQ(INTP7_IRQn);
}

void IRQ02_Handler(void)
{
		if(INTC_GetPendingIRQ(INTP1_IRQn))
		{
			intp1_interrupt();
		}
		
		if(INTC_GetPendingIRQ(INTP7_IRQn))
		{
			intp7_interrupt();
		}
		
}

/***********************************************************IRQ03_Handler************************************************************/

__WEAK void intp2_interrupt(void)
{
	INTC_ClearPendingIRQ(INTP2_IRQn);
}
__WEAK void intp8_interrupt(void)
{
	INTC_ClearPendingIRQ(INTP8_IRQn);
}

void IRQ03_Handler(void)
{
		if(INTC_GetPendingIRQ(INTP2_IRQn))
		{
			intp2_interrupt();
		}
		
		if(INTC_GetPendingIRQ(INTP8_IRQn))
		{
			intp8_interrupt();
		}
		
}

/***********************************************************IRQ04_Handler************************************************************/

__WEAK void intp3_interrupt(void)
{
	INTC_ClearPendingIRQ(INTP3_IRQn);
}
__WEAK void intp9_interrupt(void)
{
	INTC_ClearPendingIRQ(INTP9_IRQn);
}

void IRQ04_Handler(void)
{
		if(INTC_GetPendingIRQ(INTP3_IRQn))
		{
			intp3_interrupt();
		}
		
		if(INTC_GetPendingIRQ(INTP9_IRQn))
		{
			intp9_interrupt();
		}
		
}

/***********************************************************IRQ05_Handler************************************************************/

__WEAK void intp4_interrupt(void)
{
	INTC_ClearPendingIRQ(INTP4_IRQn);
}
__WEAK void intp10_interrupt(void)
{
	INTC_ClearPendingIRQ(INTP10_IRQn);
}

void IRQ05_Handler(void)
{
		if(INTC_GetPendingIRQ(INTP4_IRQn))
		{
			intp4_interrupt();
		}
		
		if(INTC_GetPendingIRQ(INTP10_IRQn))
		{
			intp10_interrupt();
		}
		
}
/***********************************************************IRQ06_Handler************************************************************/

__WEAK void intp5_interrupt(void)
{
	INTC_ClearPendingIRQ(INTP5_IRQn);
}
__WEAK void intp11_interrupt(void)
{
	INTC_ClearPendingIRQ(INTP11_IRQn);
}

void IRQ06_Handler(void)
{
		if(INTC_GetPendingIRQ(INTP5_IRQn))
		{
			intp5_interrupt();
		}
		
		if(INTC_GetPendingIRQ(INTP11_IRQn))
		{
			intp11_interrupt();
		}
		
}
/***********************************************************IRQ07_Handler************************************************************/

__WEAK void uart2_interrupt_send(void)
{
	INTC_ClearPendingIRQ(ST2_IRQn);
}
__WEAK void spi20_interrupt(void)
{
	INTC_ClearPendingIRQ(SPI20_IRQn);
}
__WEAK void iic20_interrupt(void)
{
	INTC_ClearPendingIRQ(IIC20_IRQn);
}


void IRQ07_Handler(void)
{
#if defined(USE_SCI_UART2_TX)
		if(INTC_GetPendingIRQ(ST2_IRQn))
		{
			uart2_interrupt_send();
		}
#elif defined(USE_SCI_SPI20)		
		if(INTC_GetPendingIRQ(SPI20_IRQn))
		{
			spi20_interrupt();
		}
#elif defined(USE_SCI_IIC20)		
		if(INTC_GetPendingIRQ(IIC20_IRQn))
		{
			iic20_interrupt();
		}
#endif

}
/***********************************************************IRQ08_Handler************************************************************/

__WEAK void uart2_interrupt_receive(void)
{
	INTC_ClearPendingIRQ(SR2_IRQn);
}
__WEAK void spi21_interrupt(void)
{
	INTC_ClearPendingIRQ(SPI21_IRQn);
}
__WEAK void iic21_interrupt(void)
{
	INTC_ClearPendingIRQ(IIC21_IRQn);
}

void IRQ08_Handler(void)
{
#if defined(USE_SCI_UART2_RX)	
		if(INTC_GetPendingIRQ(SR2_IRQn))
		{
			uart2_interrupt_receive();
		}
#elif defined(USE_SCI_SPI21)		
		if(INTC_GetPendingIRQ(SPI21_IRQn))
		{
			spi21_interrupt();
		}
#elif defined(USE_SCI_IIC21)		
		if(INTC_GetPendingIRQ(IIC21_IRQn))
		{
			iic21_interrupt();
		}
#endif

}
/***********************************************************IRQ09_Handler************************************************************/

__WEAK void sre2_interrupt(void)
{
	INTC_ClearPendingIRQ(SRE2_IRQn);
}
__WEAK void CAN0Err_Interrupt(void)
{
	INTC_ClearPendingIRQ(CAN0ERR_IRQn);
}

void IRQ09_Handler(void)
{
		if(INTC_GetPendingIRQ(SRE2_IRQn))
		{
			sre2_interrupt();
		}
		
		if(INTC_GetPendingIRQ(CAN0ERR_IRQn))
		{
			CAN0Err_Interrupt();
		}
		
}
/***********************************************************IRQ10_Handler************************************************************/

__WEAK void uart0_interrupt_send(void)
{
	INTC_ClearPendingIRQ(ST0_IRQn);
}
__WEAK void spi00_interrupt(void)
{
	INTC_ClearPendingIRQ(SPI00_IRQn);
}
__WEAK void iic00_interrupt(void)
{
	INTC_ClearPendingIRQ(IIC00_IRQn);
}

void IRQ10_Handler(void)
{
#if defined(USE_SCI_UART0_TX)
    if(INTC_GetPendingIRQ(ST0_IRQn))
		{
			uart0_interrupt_send();
		}
#elif defined(USE_SCI_SPI00)		
		if(INTC_GetPendingIRQ(SPI00_IRQn))
		{
			spi00_interrupt();
		}
#elif defined(USE_SCI_IIC00)		
		if(INTC_GetPendingIRQ(IIC00_IRQn))
		{
			iic00_interrupt();
		}
#endif
}
/***********************************************************IRQ11_Handler************************************************************/

__WEAK void uart0_interrupt_receive(void)
{
	INTC_ClearPendingIRQ(SR0_IRQn);
}
__WEAK void spi01_interrupt(void)
{
	INTC_ClearPendingIRQ(SPI01_IRQn);
}
__WEAK void iic01_interrupt(void)
{
	INTC_ClearPendingIRQ(IIC01_IRQn);
}

void IRQ11_Handler(void)
{
#if defined(USE_SCI_UART0_RX)
    if(INTC_GetPendingIRQ(SR0_IRQn))
		{
			uart0_interrupt_receive();
		}
#elif defined(USE_SCI_SPI01)		
		if(INTC_GetPendingIRQ(SPI01_IRQn))
		{
			spi01_interrupt();
		}
#elif defined(USE_SCI_IIC01)		
		if(INTC_GetPendingIRQ(IIC01_IRQn))
		{
			iic01_interrupt();
		}
#endif
}
/***********************************************************IRQ12_Handler************************************************************/

__WEAK void sre0_interrupt(void)
{
	INTC_ClearPendingIRQ(SRE0_IRQn);
}
__WEAK void tm01h_interrupt(void)
{
	INTC_ClearPendingIRQ(TM01H_IRQn);
}

void IRQ12_Handler(void)
{
		if(INTC_GetPendingIRQ(SRE0_IRQn))
		{
			sre0_interrupt();
		}
		
		if(INTC_GetPendingIRQ(TM01H_IRQn))
		{
			tm01h_interrupt();
		}
		
}
/***********************************************************IRQ13_Handler************************************************************/

__WEAK void uart1_interrupt_send(void)
{
	INTC_ClearPendingIRQ(ST1_IRQn);
}
__WEAK void spi10_interrupt(void)
{
	INTC_ClearPendingIRQ(SPI10_IRQn);
}
__WEAK void iic10_interrupt(void)
{
	INTC_ClearPendingIRQ(IIC10_IRQn);
}

void IRQ13_Handler(void)
{
#if defined(USE_SCI_UART1_TX)
    if(INTC_GetPendingIRQ(ST1_IRQn))
		{
			uart1_interrupt_send();
		}
#elif defined(USE_SCI_SPI10)		
		if(INTC_GetPendingIRQ(SPI10_IRQn))
		{
			spi10_interrupt();
		}
#elif defined(USE_SCI_IIC10)		
		if(INTC_GetPendingIRQ(IIC10_IRQn))
		{
			iic10_interrupt();
		}
#endif
}
/***********************************************************IRQ14_Handler************************************************************/

__WEAK void uart1_interrupt_receive(void)
{
	INTC_ClearPendingIRQ(SR1_IRQn);
}
__WEAK void spi11_interrupt(void)
{
	INTC_ClearPendingIRQ(SPI11_IRQn);
}
__WEAK void iic11_interrupt(void)
{
	INTC_ClearPendingIRQ(IIC11_IRQn);
}

void IRQ14_Handler(void)
{
#if defined(USE_SCI_UART1_RX)	
    if(INTC_GetPendingIRQ(SR1_IRQn))
		{
			uart1_interrupt_receive();
		}
#elif defined(USE_SCI_SPI11)		
		if(INTC_GetPendingIRQ(SPI11_IRQn))
		{
			spi11_interrupt();
		}
#elif defined(USE_SCI_IIC11)		
		if(INTC_GetPendingIRQ(IIC11_IRQn))
		{
			iic11_interrupt();
		}
#endif
}
/***********************************************************IRQ15_Handler************************************************************/

__WEAK void sre1_interrupt(void)
{
	INTC_ClearPendingIRQ(SRE1_IRQn);
}
__WEAK void tm03h_interrupt(void)
{
	INTC_ClearPendingIRQ(TM03H_IRQn);
}

void IRQ15_Handler(void)
{
		if(INTC_GetPendingIRQ(SRE1_IRQn))
		{
			sre1_interrupt();
		}
		
		if(INTC_GetPendingIRQ(TM03H_IRQn))
		{
			tm03h_interrupt();
		}
		
}
/***********************************************************IRQ16_Handler************************************************************/

__WEAK void iica0_interrupt(void)
{
	INTC_ClearPendingIRQ(IICA_IRQn);
}
__WEAK void div_interrupt(void)
{
	INTC_ClearPendingIRQ(DIV_IRQn);
}

void IRQ16_Handler(void)
{
		if(INTC_GetPendingIRQ(IICA_IRQn))
		{
			iica0_interrupt();
		}
		
		if(INTC_GetPendingIRQ(DIV_IRQn))
		{
			div_interrupt();
		}
		
}
/***********************************************************IRQ17_Handler************************************************************/

__WEAK void tm40_channel0_interrupt(void)
{
	INTC_ClearPendingIRQ(TM00_IRQn);
}

void IRQ17_Handler(void)
{
		if(INTC_GetPendingIRQ(TM00_IRQn))
		{
			tm40_channel0_interrupt();
		}
		
}
/***********************************************************IRQ18_Handler************************************************************/

__WEAK void tm40_channel1_interrupt(void)
{
	INTC_ClearPendingIRQ(TM01_IRQn);
}

void IRQ18_Handler(void)
{
		if(INTC_GetPendingIRQ(TM01_IRQn))
		{
			tm40_channel1_interrupt();
		}
		
}
/***********************************************************IRQ19_Handler************************************************************/

__WEAK void tm40_channel2_interrupt(void)
{
	INTC_ClearPendingIRQ(TM02_IRQn);
}

void IRQ19_Handler(void)
{
		if(INTC_GetPendingIRQ(TM02_IRQn))
		{
			tm40_channel2_interrupt();
		}
		
}
/***********************************************************IRQ20_Handler************************************************************/

__WEAK void tm40_channel3_interrupt(void)
{
	INTC_ClearPendingIRQ(TM03_IRQn);
}

void IRQ20_Handler(void)
{
		if(INTC_GetPendingIRQ(TM03_IRQn))
		{
			tm40_channel3_interrupt();
		}
		
}
/***********************************************************IRQ21_Handler************************************************************/

__WEAK void adc_interrupt(void)
{
	INTC_ClearPendingIRQ(ADC_IRQn);
}

void IRQ21_Handler(void)
{
		if(INTC_GetPendingIRQ(ADC_IRQn))
		{
			adc_interrupt();
		}
		
}
/***********************************************************IRQ22_Handler************************************************************/

__WEAK void rtc_interrupt(void)
{
	INTC_ClearPendingIRQ(RTC_IRQn);
}
__WEAK void it_interrupt(void)
{
	INTC_ClearPendingIRQ(IT_IRQn);
}

void IRQ22_Handler(void)
{
		if(INTC_GetPendingIRQ(RTC_IRQn))
		{
			rtc_interrupt();
		}
		
		if(INTC_GetPendingIRQ(IT_IRQn))
		{
			it_interrupt();
		}
		
}
/***********************************************************IRQ23_Handler************************************************************/

__WEAK void key_interrupt(void)
{
	INTC_ClearPendingIRQ(KEY_IRQn);
}
__WEAK void CAN0Rec_Interrupt(void)
{
	INTC_ClearPendingIRQ(CAN0REC_IRQn);
}

void IRQ23_Handler(void)
{
		if(INTC_GetPendingIRQ(KEY_IRQn))
		{
			key_interrupt();
		}
		
		if(INTC_GetPendingIRQ(CAN0REC_IRQn))
		{
			CAN0Rec_Interrupt();
		}
		
}
/***********************************************************IRQ24_Handler************************************************************/

__WEAK void cmp0_interrupt(void)
{
	INTC_ClearPendingIRQ(CMP0_IRQn);
}
__WEAK void CAN0Wup_Interrupt(void)
{
	INTC_ClearPendingIRQ(CAN0WUP_IRQn);
}

void IRQ24_Handler(void)
{
		if(INTC_GetPendingIRQ(CMP0_IRQn))
		{
			cmp0_interrupt();
		}
		
		if(INTC_GetPendingIRQ(CAN0WUP_IRQn))
		{
			CAN0Wup_Interrupt();
		}
		
}
/***********************************************************IRQ25_Handler************************************************************/

__WEAK void cmp1_interrupt(void)
{
	INTC_ClearPendingIRQ(CMP1_IRQn);
}
__WEAK void CAN0Trx_Interrupt(void)
{
	INTC_ClearPendingIRQ(CAN0TRX_IRQn);
}

void IRQ25_Handler(void)
{
		if(INTC_GetPendingIRQ(CMP1_IRQn))
		{
			cmp1_interrupt();
		}
		
		if(INTC_GetPendingIRQ(CAN0TRX_IRQn))
		{
			CAN0Trx_Interrupt();
		}
		
}
/***********************************************************IRQ26_Handler************************************************************/

__WEAK void tma0_interrupt(void)
{
	INTC_ClearPendingIRQ(TMA_IRQn);
}

void IRQ26_Handler(void)
{
		if(INTC_GetPendingIRQ(TMA_IRQn))
		{
			tma0_interrupt();
		}
		
		
}
/***********************************************************IRQ27_Handler************************************************************/

__WEAK void tmm0_interrupt(void)
{
	INTC_ClearPendingIRQ(TMM0_IRQn);
}

void IRQ27_Handler(void)
{
		if(INTC_GetPendingIRQ(TMM0_IRQn))
		{
			tmm0_interrupt();
		}
		
}
/***********************************************************IRQ28_Handler************************************************************/

__WEAK void tmm1_interrupt(void)
{
	INTC_ClearPendingIRQ(TMM1_IRQn);
}

void IRQ28_Handler(void)
{
		if(INTC_GetPendingIRQ(TMM1_IRQn))
		{
			tmm1_interrupt();
		}
		
}
/***********************************************************IRQ29_Handler************************************************************/

__WEAK void tmb0_interrupt(void)
{
	INTC_ClearPendingIRQ(TMB_IRQn);
}

void IRQ29_Handler(void)
{
		if(INTC_GetPendingIRQ(TMB_IRQn))
		{
			tmb0_interrupt();
		}
		
}
/***********************************************************IRQ30_Handler************************************************************/

__WEAK void tmc_interrupt(void)
{
	INTC_ClearPendingIRQ(TMC_IRQn);
}

void IRQ30_Handler(void)
{
		if(INTC_GetPendingIRQ(TMC_IRQn))
		{
			tmc_interrupt();
		}
		
}
/***********************************************************IRQ31_Handler************************************************************/

__WEAK void flash_interrupt(void)
{
	INTC_ClearPendingIRQ(FMC_IRQn);
}

void IRQ31_Handler(void)
{
		if(INTC_GetPendingIRQ(FMC_IRQn))
		{
			flash_interrupt();
		}
		
}

