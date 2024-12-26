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
#include "timm.h"

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
	 
//-----------------------------------------------------------------------
// Pause timer count when program stops during debugging
//-----------------------------------------------------------------------	 	 
	DBG->DBGSTOPCR |= DBG_DBGSTOPCR_FRZEN0_Msk;	
	 
//-----------------------------------------------------------------------
// Systick setting 
//-----------------------------------------------------------------------   
	g_ticks = 1000; 	// 1000ms
	SystemCoreClockUpdate();
	msCnt = SystemCoreClock / 1000;
	SysTick_Config(msCnt); 
	 
//-----------------------------------------------------------------------
// Init UART0 for retarget printf/scanf etc. 
//----------------------------------------------------------------------- 
#if 0
	SystemCoreClockUpdate();
	status = UART0_Init(SystemCoreClock, 19200);
	if(status == MD_ERROR)
	{
		while(1); // The baud rate cannot get at the current system clock frequency.
	}

	printf("Hello, UART\n");
#endif
//-----------------------------------------------------------------------
// Ouptput Compare function
// P17/TMIOA0 output pulse wave
// P14/TMIOB0 output pulse wave
//-----------------------------------------------------------------------
	/*            ^
	 *       FFFFH|
	 *            |
	 *TMGRA0 = m-1|_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	 *            |                    _| |                    _| |
	 *            |                  _|   |                  _|   |
	 *            |                _|     |                _|     |
	 *TMGRC0 = n-1|_ _ _ _ _ _ _ _|_ _ _ _|_ _ _ _ _ _ _ _|_ _ _ _|_ _ _ _
	 *            |            _| |       |            _| |       |
	 *TMGRB0 = p-1|_ _ _ _ _ _|_ _|_ _ _ _|_ _ _ _ _ _|_ _|_ _ _ _|_ _ _ _
	 *            |        _| |   |       |        _| |   |       |        
	 *            |      _|   |   |       |      _|   |   |       |      _  
	 *TMGRD0 = q-1|_ _ _|_ _ _|_ _|_ _ _ _|_ _ _|_ _ _|_ _|_ _ _ _|_ _ _|    
	 *            |  _| |     |   |       |  _| |     |   |       |  _|      
	 *       0000H|_|___|_____|___|_______|_|___|_____|___|_______|_|______
	 *                  |     |   |       |     |     |   |       |
	 *                  |     |   |_______|     |     |   |_______|
	 *     TMIOA0 ______|_____|___|       |_____|_____|___|       |________
	 *                  |     |   |       |__   |     |   |       |__
	 * TMSR0.IMFA ______|_____|___|_______|  |__|_____|___|_______|  |_____
	 *                  |     |   |__________   |     |   |__________
	 * TMSR0.IMFC ______|_____|___|          |__|_____|___|          |_____
	 *                  |     |                 |     |
	 *                  |_____|                 |_____|
	 *     TMIOB0 ______|     |_________________|     |____________________
	 *                  |     |______________   |     |______________
	 * TMSR0.IMFB ______|_____|              |__|_____|              |_____
	 *                  |____________________   |____________________
	 * TMSR0.IMFD ______|                    |__|                    |_____
	 *                                                 
	 */
	TMM0_DoublePulseOutput(TMM_CLOCK_FCLK, 1000, 800, 600, 400);
	delayMS(100);
	
//-----------------------------------------------------------------------
// PWM output function
// P14/TMIOB0 output PWM wave (duty: 80%)
// P16/TMIOC0 output PWM wave (duty: 50%) 
// P15/TMIOD0 output PWM wave (duty: 20%)
//-----------------------------------------------------------------------
	/*            ^
	 *       FFFFH|
	 *            |
	 *TMGRA0 = m-1|_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
	 *            |                    _| |                    _| |
	 *            |                  _|   |                  _|   |
	 *            |                _|     |                _|     |
	 *TMGRB0 = n-1|_ _ _ _ _ _ _ _|_ _ _ _|_ _ _ _ _ _ _ _|_ _ _ _|_ _ _ _
	 *            |            _| |       |            _| |       |
	 *TMGRC0 = p-1|_ _ _ _ _ _|_ _|_ _ _ _|_ _ _ _ _ _|_ _|_ _ _ _|_ _ _ _
	 *            |        _| |   |       |        _| |   |       |
	 *            |      _|   |   |       |      _|   |   |       |      _
	 *TMGRD0 = q-1|_ _ _|_ _ _|_ _|_ _ _ _|_ _ _|_ _ _|_ _|_ _ _ _|_ _ _|
	 *            |  _| |     |   |       |  _| |     |   |       |  _|
	 *       0000H|_|___|_____|___|_______|_|___|_____|___|_______|_|______
	 *                  |     |   |       |     |     |   |       |
	 *            ______|_____|___|       |_____|_____|___|       |________
	 *     TMIOB0       |     |   |_______|     |     |   |_______|
	 *            ______|_____|   |       |_____|_____|   |       |________
	 *     TMIOC0       |     |___|_______|     |     |___|_______|
	 *            ______|     |   |       |_____|     |   |       |________
	 *     TMIOD0       |_____|___|_______|     |_____|___|_______|
	 *                  |     |   |       |     |     |   |       |
	 *                  |     |   |       |__   |     |   |       |__
	 * TMSR0.IMFA ______|_____|___|_______|  |__|_____|___|_______|  |_____
	 *                  |     |   |__________   |     |   |__________
	 * TMSR0.IMFB ______|_____|___|          |__|_____|___|          |_____
	 *                  |     |______________   |     |______________
	 * TMSR0.IMFC ______|_____|              |__|_____|              |_____
	 *                  |____________________   |____________________
	 * TMSR0.IMFD ______|                    |__|                    |_____
	 *
	 */
	PORT->PU13 |= (1 << 6);  // P136/INTP0 pull up enable 
	                         // Don't forced cutoff 
	TMM0_PWM_1Perdod_3Duty(TMM_CLOCK_FCLK, 1000, 800, 500, 200);
	delayMS(100);
}
/***********************************************************************************************************************
* Function Name: SysTick Handler
* Description  : Decreament the g_ticks value
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void SysTick_Handler(void)
{
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

