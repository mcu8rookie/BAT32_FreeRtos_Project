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
#include "dac.h"
#include "pga.h"
#include "adc.h"
#include "sci.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
volatile uint32_t g_ticks;
void delayMS(uint32_t n)
{
		g_ticks = n;
		while(g_ticks);
}

uint8_t  set_value[4];
uint16_t get_value[16];
uint16_t dmy_value[16];

const uint8_t pga_gain[7][2] = 
{
  //{gain, PGAVG[1:0]}
    { 4,  PGA_GAIN_X4},
    { 8,  PGA_GAIN_X8},
    {10,  PGA_GAIN_X10},
    {12,  PGA_GAIN_X12},
    {14,  PGA_GAIN_X14},
    {16,  PGA_GAIN_X16},
    {32,  PGA_GAIN_X32}
};

int main()
{
	MD_STATUS status;
	uint32_t msCnt; 	// count value of 1ms
	uint32_t i, j;
	
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
// DAC channel 0 output --> PGA0 --> ADC channel input
//-----------------------------------------------------------------------
	ADC_Init();					
	DAC_Init(DAC_CHANNEL_0);
	DAC_Start(DAC_CHANNEL_0);		
	ADC_Start(ADC_CHANNEL_PGA0);
		
	printf("PGA0 Gain Test...\n");
	for(i=0; i<sizeof(pga_gain)/sizeof(pga_gain[0]); i++)
	{
		PGA_Init(PGA_CHANNEL_0, PGA_VSS_REFERENCE_VOLTAGE, (pga_gain_t)pga_gain[i][1]);
		PGA_Start(PGA_CHANNEL_0);
		for(j=1; j<sizeof(set_value); j++)
		{
			set_value[j] = (j*256/pga_gain[i][0]/sizeof(set_value));
			DAC_Set_Value(DAC_CHANNEL_0, set_value[j]);
			delayMS(10);
			get_value[j] = ADC_Converse(ADC_CHANNEL_PGA0, 16, dmy_value);
		}
		//-----------------------------------------------------------------------
		// Print result
		//-----------------------------------------------------------------------
		printf("DAC ----------------- ADC ------------------ PGA(X%d):\n", pga_gain[i][0]);
		for(j=1; j<sizeof(set_value); j++)
		{
			printf("DAC Set Value = 0x%02X, ", set_value[j]);
			printf("ADC Get Value = 0x%03X, ", get_value[j]);
			printf("PGA Gain = %3.1f\n", (double)get_value[j]/(set_value[j] << 4));		
		}
		printf("\n");
	}
	
	ADC_Stop();	
	DAC_Stop(DAC_CHANNEL_0);
	PGA_Stop(PGA_CHANNEL_0);

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

