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
//#define RTL_SIMULATION
#define USE_HANDSHAKE
#define TEST_SPI_MODE_0
#define TEST_SPI_MODE_3

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
uint8_t mtx_buf[] = {0xA5, 0x5A, 0xCC, 0x33, 0x3C, 0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01};
uint8_t srx0_buf[13];
uint8_t srx3_buf[13];

void delayMS(uint32_t n)
{
		g_ticks = n;
		while(g_ticks);
}

int main()
{
	MD_STATUS status;
	uint32_t msCnt; 	// count value of 1ms
	uint32_t i, err;

//-----------------------------------------------------------------------
// Systick setting 
//-----------------------------------------------------------------------   
	g_ticks = 1000; 	// 1000ms
	SystemCoreClockUpdate();
	msCnt = SystemCoreClock / 1000;
	SysTick_Config(msCnt);

//-----------------------------------------------------------------------
// Please connect the following pins:
// SCK:  P10/SCK11 --> P30/SCK00
// MOSI: P12/SDO11 --> P50/SDI00
// MISO: P11/SDI11 <-- P51/SDO00
// SS00: P62/SS11  --> P62/SS00
//-----------------------------------------------------------------------
	
//-----------------------------------------------------------------------
// Connect P136 to P136/INTP0 of Master chip
// Output a pulse to inform the master that the slave is ready
// P71/LED indicates the result of data received by mode 0
// P72/LED indicates the result of data received by mode 3
//-----------------------------------------------------------------------
#ifdef USE_HANDSHAKE
	INTP0_PORT_SETTING();
	PORT->PM13 &= ~(1<<6);  // P136 output mode
#endif
	PORT->PM7  &= ~(3<<1);  // P71, P72 output mode
	PORT->P7   |=  (3<<1);  // P71/LED, P72/LED OFF
	
//=======================================================================
// SPI00 MODE 0 Slave transmission/reception
//   Mode 0: CPOL = 0, CPHA = 0; i.e. DAP = 1, CKP = 1
//   Mode 1: CPOL = 0, CPHA = 1; i.e. DAP = 0, CKP = 1
//   Mode 2: CPOL = 1, CPHA = 0; i.e. DAP = 1, CKP = 0
//   Mode 3: CPOL = 1, CPHA = 1; i.e. DAP = 0, CKP = 0
//=======================================================================
#ifdef TEST_SPI_MODE_0
	SPI00_SlaveInit(SPI_MODE_0);
	
//-----------------------------------------------------------------------
// Master Send and Slave Receive
//-----------------------------------------------------------------------
	SPI00_SlaveReceive(srx0_buf, sizeof(srx0_buf));
	
#ifdef USE_HANDSHAKE
	/* P136 output a pulse to flag SPI slave ready */
	PORT->P13 |=  (1 << 6);
	for(i=0; i<10; i++);
	PORT->P13 &= ~(1 << 6);	
#endif

#ifdef SPI00_WITH_DMA
	SysTick->CTRL  &= ~SysTick_CTRL_TICKINT_Msk;    /* Disable SysTick IRQ */
	__WFI();
	SysTick->CTRL  |=  SysTick_CTRL_TICKINT_Msk;    /* Enable SysTick IRQ */
#else
	while(g_spi00_rx_count != 0);
#endif	
	delayMS(1);
	
//-----------------------------------------------------------------------
// Master Receive and Slave Send
//-----------------------------------------------------------------------
	SPI00_SlaveSend(srx0_buf, sizeof(srx0_buf));
	
#ifdef SPI00_WITH_DMA
	SysTick->CTRL  &= ~SysTick_CTRL_TICKINT_Msk;    /* Disable SysTick IRQ */
	__WFI();
	SysTick->CTRL  |=  SysTick_CTRL_TICKINT_Msk;    /* Enable SysTick IRQ */
#else
	while(g_spi00_tx_count != 0);
#endif	
	delayMS(1);
	
//-----------------------------------------------------------------------
// Check Data
//-----------------------------------------------------------------------
	err = 0;
	for(i=0; i<sizeof(srx0_buf); i++) {		
		if(mtx_buf[i] != srx0_buf[i]) 
		{
			err++; 
		}	
	}
	if(err) {
		for(i=0; i<8; i++)
		{
			PORT->P7 ^= (1<<1);
	#ifndef RTL_SIMULATION
			delayMS(250);
	#endif
		}
		PORT->P7 |=  (1 << 1); 	// P71/LED OFF
	}
	else {
		for(i=0; i<8; i++)
		{
			PORT->P7 ^= (1<<1);
	#ifndef RTL_SIMULATION
			delayMS(250);
	#endif
		}
		PORT->P7 &= ~(1 << 1); 	// P71/LED ON
	}
#endif  // end of TEST_SPI_MODE_0
//=======================================================================
// SPI00 MODE 3 Slave transmission/reception
//   Mode 0: CPOL = 0, CPHA = 0; i.e. DAP = 1, CKP = 1
//   Mode 1: CPOL = 0, CPHA = 1; i.e. DAP = 0, CKP = 1
//   Mode 2: CPOL = 1, CPHA = 0; i.e. DAP = 1, CKP = 0
//   Mode 3: CPOL = 1, CPHA = 1; i.e. DAP = 0, CKP = 0
//=======================================================================
#ifdef TEST_SPI_MODE_3
	SPI00_SlaveInit(SPI_MODE_3);

//-----------------------------------------------------------------------
// Master Send and Slave Receive
//-----------------------------------------------------------------------
	SPI00_SlaveReceive(srx3_buf, sizeof(srx3_buf));

#ifdef USE_HANDSHAKE
#ifndef RTL_SIMULATION
	delayMS(50);
#endif
	/* P136 output a pulse to flag SPI slave ready */
	PORT->P13 |=  (1 << 6);
	for(i=0; i<10; i++);
	PORT->P13 &= ~(1 << 6);
#endif

#ifdef SPI00_WITH_DMA
	SysTick->CTRL  &= ~SysTick_CTRL_TICKINT_Msk;    /* Disable SysTick IRQ */
	__WFI();
	SysTick->CTRL  |=  SysTick_CTRL_TICKINT_Msk;    /* Enable SysTick IRQ */
#else
	while(g_spi00_rx_count != 0);
#endif	
	delayMS(1);	
	
//-----------------------------------------------------------------------
// Master Receive and Slave Send
//-----------------------------------------------------------------------
	SPI00_SlaveSend(srx3_buf, sizeof(srx3_buf));

#ifdef SPI00_WITH_DMA
	SysTick->CTRL  &= ~SysTick_CTRL_TICKINT_Msk;    /* Disable SysTick IRQ */
	__WFI();
	SysTick->CTRL  |=  SysTick_CTRL_TICKINT_Msk;    /* Enable SysTick IRQ */
#else
	while(g_spi00_tx_count != 0);
#endif	
	delayMS(1);
	
//-----------------------------------------------------------------------
// Check Data
//-----------------------------------------------------------------------
	err = 0;
	for(i=0; i<sizeof(srx3_buf); i++) {		
		if(mtx_buf[i] != srx3_buf[i]) 
		{
			err++; 
		}	
	}
	if(err) {
		for(i=0; i<8; i++)
		{
			PORT->P7 ^= (1<<2);
	#ifndef RTL_SIMULATION
			delayMS(250);
	#endif
		}
		PORT->P7 |=  (1 << 2); 	// P72/LED OFF
	}
	else {
		for(i=0; i<8; i++)
		{
			PORT->P7 ^= (1<<2);
	#ifndef RTL_SIMULATION
			delayMS(250);
	#endif
		}
		PORT->P7 &= ~(1 << 2); 	// P72/LED ON
	}
	
#endif	// end of TEST_SPI_MODE_3

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

