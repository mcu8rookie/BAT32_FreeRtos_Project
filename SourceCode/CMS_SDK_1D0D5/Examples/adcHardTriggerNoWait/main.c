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
#include "gpio.h"
#include "tim4.h"
#include "dac.h"
#include "adc.h"
#include "dma.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
volatile uint32_t g_ticks;
uint8_t set_value[16];
uint16_t get_value[16];

int main()
{
	MD_STATUS status;
	uint32_t i;
	
//-----------------------------------------------------------------------
// Init UART0 for retarget printf/scanf etc. 
//----------------------------------------------------------------------- 
#if 1
	SystemCoreClockUpdate();
	status = UART0_Init(SystemCoreClock, 19200);
	if(status == MD_ERROR)
	{
		while(1);
	}
	
	printf("Hello, UART\n");
#endif

//-----------------------------------------------------------------------
// Initial set value for DAC
//-----------------------------------------------------------------------
	for(i=1; i<16; i++)
	{
		set_value[i-1] = (i*256/16);	
	}
//-----------------------------------------------------------------------
// P23: DAC channel 1 output --> ADC channel 3 input
// TM4 channel 0 trigger DAC set value with DMA
// TM4 channel 1 trigger ADC conversion
// ADC conversion end interrupt trigger ADC get value with DMA
//-----------------------------------------------------------------------
	ADC_Init();					
	ADC_Set_HardTrigger(0, AD_TRG_TM01);
	DAC_Init(DAC_CHANNEL_1);
	DAC_Start(DAC_CHANNEL_1);
	ADC_Start(ADC_CHANNEL_3);
	DMA_Start(DMA_VECTOR_TM4_CH0, CTRL_DATA_DAC, DMA_MODE_NORMAL, 
		        DMA_SIZE_BYTE, 15, set_value, (void *)&DAC->DACS1);
	DMA_Start(DMA_VECTOR_ADC, CTRL_DATA_ADC, DMA_MODE_NORMAL, 
		        DMA_SIZE_HALF, 15, (void *)&ADC->ADCR, get_value);
	TM40_PWM_1Period_1Duty(1000, 250);
	
	__WFI();	// Sleep mode
	
	ADC_Stop();	
	DAC_Stop(DAC_CHANNEL_1);
	TM40_Channel_Stop(TM4_CHANNEL_0 | TM4_CHANNEL_1);

//-----------------------------------------------------------------------
// Print ADC result
//-----------------------------------------------------------------------	
	printf("DAC(ch1) --> ADC(triggered by INTTM01)\n");	
	for(i=0; i<15; i++)
	{
		printf("DAC Set Value = 0x%02X, ", set_value[i]);
		printf("ADC Get Value = 0x%03X\n", get_value[i]);
	}

    while(1){
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
	
	printf ("[Hard fault handler]\n");
	printf ("R0 = %x\n", stacked_r0);
	printf ("R1 = %x\n", stacked_r1);
	printf ("R2 = %x\n", stacked_r2);
	printf ("R3 = %x\n", stacked_r3);
	printf ("R12 = %x\n", stacked_r12);
	printf ("Stacked LR = %x\n", stacked_lr);
	printf ("Stacked PC = %x\n", stacked_pc);
	printf ("Stacked PSR = %x\n", stacked_psr);
	printf ("Current LR = %x\n", lr_value);
	
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

