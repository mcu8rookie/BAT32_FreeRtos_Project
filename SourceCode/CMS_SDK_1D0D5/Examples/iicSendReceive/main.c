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

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
volatile uint32_t g_ticks;
uint32_t width;
uint32_t freq[16];
uint8_t tx_buf[3];
uint8_t rx_buf[3];


int main()
 {
	MD_STATUS status;
	uint32_t err;
	uint32_t i;

//-----------------------------------------------------------------------
// Init UART0 for retarget printf/scanf etc. 
//----------------------------------------------------------------------- 
#if 1
	SystemCoreClockUpdate();
	status = UART0_Init(SystemCoreClock, 19200);
	if(status == MD_ERROR)
	{
		while(1);	// The baud rate cannot get at the current system clock frequency.
	}
	
	printf("Hello, UART\n");
#endif

//-----------------------------------------------------------------------
// IIC20 transmission/reception
//-----------------------------------------------------------------------
	printf("\n");	
	printf("Please connect No.41 pin(P15/SCL20) to SCL on partner board\n");
	printf("Please connect No.42 pin(P14/SDA20) to SDA on partner board\n");
	printf("Press any key to continue\n");
	//getchar();
	printf("\n");	
	
	IIC20_Init();
	tx_buf[0] = 0xAA;
	tx_buf[1] = 0x55;
	tx_buf[2] = 0x5A;
	
	g_iic20_tx_end = 0;
	IIC20_MasterSend(SLVADDR, tx_buf, 3);
	while(g_iic20_tx_end == 0);
	
	g_iic20_rx_end = 0;
	IIC20_MasterReceive(SLVADDR, rx_buf, 3);
	while(g_iic20_rx_end == 0);
	
	/***********************************************************************
	*  Compare the reveived value with sent value
	*  tx_buf[0] == rx_buf[0]
	*  tx_buf[1] == rx_buf[1]
	*  tx_buf[2] == rx_buf[2]
	***********************************************************************/
	err = 0;
	for(i=0; i<sizeof(tx_buf); i++)
	{
		if(tx_buf[i] != rx_buf[i])
		{
			err = 1;
		}
	}
	if(err)
	{
		printf("IIC20 Send and Receive NG\n");
	}
	else 
	{
		printf("IIC20 Send and Receive OK\n");
	}

//-----------------------------------------------------------------------
// IIC21 transmission/reception
//-----------------------------------------------------------------------
	printf("\n");	
	printf("Please connect No.29 pin(P70/SCL21) to SCL on partner board\n");
	printf("Please connect No.28 pin(P71/SDA21) to SDA on partner board\n");
	printf("Press any key to continue\n");
	getchar();
	printf("\n");	
	
	IIC21_Init();
	tx_buf[0] = 0xAA;
	tx_buf[1] = 0x55;
	tx_buf[2] = 0x5A;
	
	g_iic21_tx_end = 0;
	IIC21_MasterSend(SLVADDR, tx_buf, 3);
	while(g_iic21_tx_end == 0);
	
	g_iic21_rx_end = 0;
	IIC21_MasterReceive(SLVADDR, rx_buf, 3);
	while(g_iic21_rx_end == 0);
	
	/***********************************************************************
	*  Compare the reveived value with sent value
	*  tx_buf[0] == rx_buf[0]
	*  tx_buf[1] == rx_buf[1]
	*  tx_buf[2] == rx_buf[2]
	***********************************************************************/
	err = 0;
	for(i=0; i<sizeof(tx_buf); i++)
	{
		if(tx_buf[i] != rx_buf[i])
		{
			err = 1;
		}
	}
	if(err)
	{
		printf("IIC21 Send and Receive NG\n");
	}
	else
	{
		printf("IIC21 Send and Receive OK\n");
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

