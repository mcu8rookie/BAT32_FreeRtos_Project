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
/* The count value of HOCO(32MHz) clock per 1ms at 25 degrees Celsius*/
/* 25���϶���ÿ����HOCO(32MHz)ʱ�Ӽ���ֵ */
#define HOCOCNT   *((volatile uint16_t *)(0x0050064C))  
/* The frequency of HOCO(Unit:Hz) at 25 degrees Celsius */
/* 25���϶ȵ�HOCOƵ�� */
//#define HOCOFREQ  (HOCOCNT * 1000)  
#define HOCOFREQ  (32768 * 976)  
	
/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "BAT32A237.h"
#include "userdefine.h"
#include "sci.h"
#include "rtc.h"
#include "adc.h"
#include "tim4.h"
#include "clk.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
uint32_t SystemHocoClock = HOCOFREQ;
uint16_t g_bgr_value[166]; /* bgr value of -40~125 degrees Celsius */
double   g_vdd_voltage = 3.094;
double   g_bgr_voltage[166];
uint8_t  g_offset = 40;
int64_t  g_minute_delta;

volatile uint32_t g_ticks;

/***********************************************************************************************************************
* Function Name: SystemHocoClockUpdate
* Description  : Update the frequency of HOCO according to temperature
* Arguments    : None
* Return Value : delta
***********************************************************************************************************************/
int32_t SystemHocoClockUpdate(void)
{
	volatile int32_t temp, delta;
	
	temp = (uint32_t)(0.8 * 8000000 * (g_bgr_voltage[g_temperature + g_offset] - g_bgr_voltage[25 + g_offset]) + HOCOFREQ);
	//delta = temp - SystemHocoClock;
	delta = temp - HOCOFREQ;
	SystemHocoClock = temp;
	printf("HOCO frequency = %dHz\n", SystemHocoClock);
	
	return (delta);
}
/***********************************************************************************************************************
* ��������: double_round
* ��   �� : ˫���ȸ�����ֵȡ������
* ��   �� : ˫���ȸ�����
* ��   �� : ����
***********************************************************************************************************************/
static int double_round(double f) {
    return (f >= 0 ? (int)(f + 0.5) : (int)(f-1));
}

int main()
{
	MD_STATUS status;
	uint32_t i, period;
	uint16_t avg_value, get_value[16];
	
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
// RTC Constant Period Interrupt Demo (1 second)
//-----------------------------------------------------------------------
#if 1
	SystemHocoClockUpdate();
	RTC_Init(RTC_32MHZ);
	//RTC_Set_CorrectionValue((double)(SystemHocoClock)/976, 32768);
	RTC_Start();
	date_time.year  = 0x20;
	date_time.month = 0x04;
	date_time.week  = MONDAY; 
	date_time.day   = 0x13;
	date_time.hour  = 0x19;
	date_time.min   = 0x37;
	date_time.sec   = 0x00;
	RTC_Set_CounterValue(&date_time);
	RTC_Set_ConstPeriodInterruptOn(ONESEC);
#endif

//-----------------------------------------------------------------------
// fCLK frequency measure with TM40 channel 0 pulse interval measure mode 
//----------------------------------------------------------------------- 

  //CLK_SubOsc_Setting(OSC_OSCILLATOR, OSC_LOW_POWER);
	CLKBUZ0_PORT_SETTING(); // P140/CLKBUZ0
  //PCBZ->CKS0  = 0x8F;    	// FSUB/2^7 = 256Hz
	PCBZ->CKS0  = 0x83;    	// FMAIN/2^3
#if 0
	while(1)
	{
	uint32_t tmp;
	tmp = g_rtcIntTaken;
	while(g_rtcIntTaken == tmp)
  period = TM40_Get_PulsePeriod(TM4_CHANNEL_0, TM4_CH0_INPUT_TI00, TM4_PULSE_PERIOD_RISING);
	printf("P10/TI00 pulse period = %d fCLK\n", period);
	printf("HOCO frequency = %dHz, fCLK frequency = %dHz, error = %4.3f%%\n", period * 4 * 256, period * 256, (((float)(period * 256) - SystemCoreClock) / SystemCoreClock * 100));
	//printf("HOCO frequency = %dHz, fCLK frequency = %dHz, error = %4.3f%%\n", period * 4 * 1000, period * 1000, (((float)(period * 1000) - SystemCoreClock) / SystemCoreClock * 100));
	}
#endif	
//-----------------------------------------------------------------------
// Temperature Calibration for HOCO frequency
//-----------------------------------------------------------------------
	ADC_Init();	
	ADC_Set_HardTrigger(0, AD_TRG_RTC);  /* INTRTC trigger with wait */
	ADC_Start(ADC_TEMPERSENSOR0);        /* Channel: Temperature Sensor */
	
	/* initialize bgr voltage array */
	for(i=0; i<sizeof(g_bgr_voltage)/sizeof(g_bgr_voltage[0]); i++)
	{
		g_bgr_voltage[i] = 1.44; 
	}	
	
	while(1)
	{
		while(g_AdcIntTaken == 0);
		g_AdcIntTaken = 0;
		ADC_Converse(ADC_INTERREFVOLT, sizeof(get_value)/sizeof(get_value[0]), get_value);
		avg_value = ADC_MidAvg_Filter(get_value, sizeof(get_value)/sizeof(get_value[0]));
		g_bgr_value[g_temperature + g_offset] = avg_value;
		g_bgr_voltage[g_temperature + g_offset] = (double)double_round(100* g_vdd_voltage * avg_value / 4096) / 100; /* keep 2 decimal places */
		printf("Tj temperature = %d, bgr_value = %04d, bgr_voltage = %4.2fV\n", g_temperature, g_bgr_value[g_temperature + g_offset], g_bgr_voltage[g_temperature + g_offset]);
		if(g_temperature < (20 + 13))
		{
			g_minute_delta += SystemHocoClockUpdate();
			if(g_rtcIntTaken == 60)
			{		
				g_rtcIntTaken = 0;
				RTC_Set_CorrectionValue( ((HOCOFREQ + g_minute_delta) / 976), 32768);
				g_minute_delta = 0;
			}
		}
		else
		{	
			RTC->SUBCUD = 0x87AD; /* 0.2% */
		}
		__WFI();
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

