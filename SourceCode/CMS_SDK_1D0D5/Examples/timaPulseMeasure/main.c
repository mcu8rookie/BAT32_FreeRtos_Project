/***********************************************************************************************************************
* Copyright (C) . All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name    : main.c
* Version      :  
* Device(s)    : BAT32A237
* Tool-Chain   : MDK(armcc)
* Description  : This file is a template.
* Creation Date: 2022/2/25
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
#include "tima.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
volatile uint32_t g_ticks;

void delayMS(uint32_t n)
{
		g_ticks = n;
		while(g_ticks);
}

int main()
 {
	MD_STATUS status;
	uint32_t msCnt; 	// count value of 1ms
	volatile uint32_t width, period;

//-----------------------------------------------------------------------
// Pause timer count when program stops during debugging
//-----------------------------------------------------------------------	 	 
	DBG->DBGSTOPCR |= DBG_DBGSTOPCR_FRZEN0_Msk;	
	 
//-----------------------------------------------------------------------
// Init UART0 for retarget printf/scanf etc. 
//----------------------------------------------------------------------- 
#if 1
	SystemCoreClockUpdate();
	status = UART0_Init(SystemCoreClock, 19200);
	if(status == MD_ERROR)
	{
		while(1); // The baud rate cannot get at the current system clock frequency.
	}
	
	printf("Hello, UART\n");
#endif
	
//-----------------------------------------------------------------------
// Systick setting 
//-----------------------------------------------------------------------   
	g_ticks = 1000; 	// 1000ms
	SystemCoreClockUpdate();
	msCnt = SystemCoreClock / 1000;
	SysTick_Config(msCnt); 
	
//-----------------------------------------------------------------------
// Please connect No.62 pin(P00) to No.61 pin(P01/TAIO) on board
//-----------------------------------------------------------------------
	PORT->P0  &= ~(1 << 0);  /* P00 = L */
	PORT->PM0 &= ~(1 << 0);  /* P00 output mode */
#if 1
	printf("Please connect No.62 pin(P00) to No.61 pin(P01/TAIO) on board\n");
	printf("Press any key to continue\n");
	getchar();
#endif	
//-----------------------------------------------------------------------
// Measure the pulse width of No.61 pin(P01/TAIO)
//-----------------------------------------------------------------------
	while((PORT->P0 & (1 << 0)) != 0);
	PORT->P0 &= ~(1 << 0);  /* P00 = L */
	width = TMA0_Get_PulseWidth(TMA_COUNT_SOURCE_FCLK, TMA_PULSE_WIDTH_HIGH);
	printf("P01/TAIO pulse width  = %d fCLK\n", width);  /* expected value: msCnt */
	while((PORT->P0 & (1 << 0)) == 0);
	PORT->P0 |=  (1 << 0);  /* P00 = H */
	width = TMA0_Get_PulseWidth(TMA_COUNT_SOURCE_FCLK, TMA_PULSE_WIDTH_LOW);
	printf("P01/TAIO pulse width  = %d fCLK\n", width);  /* expected value: msCnt */
	
//-----------------------------------------------------------------------
// Measure the pulse period of No.61 pin(P01/TAIO)
//-----------------------------------------------------------------------
	while((PORT->P0 & (1 << 0)) != 0);
	PORT->P0 &= ~(1 << 0);  /* P00 = L */
  period = TMA0_Get_PulsePeriod(TMA_COUNT_SOURCE_FCLK, TMA_PULSE_PERIOD_RISING);
	printf("P01/TAIO pulse period = %d fCLK\n", period);  /* expected value: msCnt * 2 */
	while((PORT->P0 & (1 << 0)) == 0);
	PORT->P0 |=  (1 << 0);  /* P00 = H */
  period = TMA0_Get_PulsePeriod(TMA_COUNT_SOURCE_FCLK, TMA_PULSE_PERIOD_FALLING);
	printf("P01/TAIO pulse period = %d fCLK\n", period);  /* expected value: msCnt * 2 */
	delayMS(2);
}

/***********************************************************************************************************************
* Function Name: SysTick Handler
* Description  : Decreament the g_ticks value
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void SysTick_Handler(void)
{
	PORT->P0  ^=  (1 << 0);  /* P00 toggle */
	g_ticks--;
}

/***********************************************************************************************************************
* Function Name: HardFault_Handler
* Description  : Hard Fault handler to report stacked register values
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
// Hard Fault handler in C, with stack frame location and LR value
// extracted from the assembly wrapper as input parameters
void hard_fault_handler_c(unsigned int * hardfault_args, unsigned lr_value)
{
	unsigned int stacked_r0;
	unsigned int stacked_r1;
	unsigned int stacked_r2;
	unsigned int stacked_r3;
	unsigned int stacked_r12;
	unsigned int stacked_lr;
	unsigned int stacked_pc;
	unsigned int stacked_psr;
	
	stacked_r0 = ((unsigned long) hardfault_args[0]);
	stacked_r1 = ((unsigned long) hardfault_args[1]);
	stacked_r2 = ((unsigned long) hardfault_args[2]);
	stacked_r3 = ((unsigned long) hardfault_args[3]);
	stacked_r12 = ((unsigned long) hardfault_args[4]);
	stacked_lr = ((unsigned long) hardfault_args[5]);
	stacked_pc = ((unsigned long) hardfault_args[6]);
	stacked_psr = ((unsigned long) hardfault_args[7]);
	
	printf ("[Hard fault handler]\r\n");
	printf ("R0 = %x\r\n", stacked_r0);
	printf ("R1 = %x\r\n", stacked_r1);
	printf ("R2 = %x\r\n", stacked_r2);
	printf ("R3 = %x\r\n", stacked_r3);
	printf ("R12 = %x\r\n", stacked_r12);
	printf ("Stacked LR = %x\r\n", stacked_lr);
	printf ("Stacked PC = %x\r\n", stacked_pc);
	printf ("Stacked PSR = %x\r\n", stacked_psr);
	printf ("Current LR = %x\r\n", lr_value);
	
	while(1); // endless loop
}

/***********************************************************************************************************************
* Function Name: HardFault_Handler
* Description  : Assembly wrapper using Embedded Assembler in Keil MDK
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
// Hard Fault handler wrapper in assembly
// It extracts the location of stack frame and passes it to handler
// in C as a pointer. We also extract the LR value as second
// parameter.
__asm void HardFault_Handler(void)
{
		MOVS 	r0, #4
		MOV 	r1, LR
		TST 	r0, r1
		BEQ 	stacking_used_MSP
		MRS 	R0, PSP ; first parameter - stacking was using PSP
		B 		get_LR_and_branch
stacking_used_MSP
		MRS 	R0, MSP ; first parameter - stacking was using MSP
get_LR_and_branch
		MOV 	R1, LR ; second parameter is LR current value
		LDR 	R2,=__cpp(hard_fault_handler_c)
		BX 		R2
}

