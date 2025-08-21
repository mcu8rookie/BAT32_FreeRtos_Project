#ifndef __USR_MAIN_C__
#define __USR_MAIN_C__

#include<stdint.h>
#include <stdio.h>

#include "BAT32A237.h"
#include "userdefine.h"
#include "adc.h"

#include"gpio.h"

#include"Usr_Config.h"
#include"Usr_Main.h"
#include"Usr_GPIO.h"

#include"Usr_Uart.h"
#include "Usr_I2C.h"

#include "tima.h"

#include "Usr_Psf.h"

#include "core_cm0plus.h"
#include "core_cmFunc.h"

#include "flash.h"

#include "Usr_I2CA_Slave.h"

#include "Usr_ADC.h"


#if(defined(DEF_FREEMODBUS_EN)&&(DEF_FREEMODBUS_EN==1))
#include "mb.h"
#include "Usr_Modbus.h"
#endif

#include "Usr_E703.h"
#include "Usr_DataFlash.h"
#include "Usr_Psf.h"
#include "Usr_ALSensor.h"
#include "User_SensorParam.h"

unsigned char MCU_Reset_Flag;

uint8_t Flag_SysTick;
uint32_t Mcu_Timestamp;
uint32_t Mcu_ResetSource;
uint32_t Mcu_Name;
uint32_t Product_Name;
uint32_t Product_Verison;

uint16_t TimeSn_Time;
uint16_t TimeSn_SN;

uint32_t Mcu_Time1s_Cnt;



volatile unsigned int DlyMsCnt = 0;

void Sample_DelayMs(unsigned int ms)
{
    
    DlyMsCnt = ms;
    while(DlyMsCnt > 0)
    {
        
    }
}

#if(defined(DEF_SOFT_ARCH)&&(DEF_SOFT_ARCH == DEF_MAINLOOP))

void Mcu_Init(void)
{
    uint32_t msCnt;
    
    SystemCoreClockUpdate();
    msCnt = SystemCoreClock / 1000;
    SysTick_Config(msCnt); 
    
    SystemCoreClockUpdate();
    
    Mcu_Timestamp = 0;
}

int main(int argc, char *argv[])
{

	Mcu_Init();

	Uart_St_Init_s();

	Usr_GPIO_InitSetup();

	Usr_Uart_InitSetup();

	#if(defined(DEF_FREEMODBUS_EN)&&(DEF_FREEMODBUS_EN==1))
	{
		eMBErrorCode    eStatus;

		//eStatus = eMBInit( MB_RTU, 0x0A, 0, 38400, MB_PAR_EVEN );
		eStatus = eMBInit( MB_RTU, DEF_MB_SLAVE_ADDR, 0, Usr_Uart_Baudrate, MB_PAR_EVEN );

		Modbus_printf("\neStatus = eMBInit(); eStatus = %d. ",eStatus);

		/* Enable the Modbus Protocol Stack. */
		eStatus = eMBEnable(  );

		Modbus_printf("\neStatus = eMBEnable(); eStatus = %d. ",eStatus);

		{
			//Usr_Mb_T3d5_Value = 50*SystemCoreClock/Usr_Uart_Baudrate;
			if(Usr_Uart_Baudrate<19200)
			{
				Usr_Mb_T3d5_Value = 50*(SystemCoreClock/Usr_Uart_Baudrate);
			}
			else
			{
				Usr_Mb_T3d5_Value = 50*(SystemCoreClock/19200);
			}

			if(Usr_Mb_T3d5_Value>65535)
			{
			Usr_Mb_T3d5_Value = 65535;
			}

			TMA0_IntervalTimer(TMA_COUNT_SOURCE_FCLK, Usr_Mb_T3d5_Value);     // 50us;
		}
	}
	#endif

    // Project base information;

	Init_printf(MCU_NAME);

	Init_printf("\nHW Ver:    ");Init_printf("%d-%d-%d.",HW_VERSION_PART0,HW_VERSION_PART1,HW_VERSION_PART2);
	Init_printf("\nSW Ver:    ");Init_printf("%d-%d-%d.",FW_VERSION_PART0,FW_VERSION_PART1,FW_VERSION_PART2);

	Init_printf(MCU_SYSCLK);
	Init_printf("%d.\n",SystemCoreClock);


	#if(defined(DEF_DATAFLASH_EN)&&(DEF_DATAFLASH_EN==1))
	Usr_DF_InitSetup();
	#endif

	initSensorParam();

	#if(defined(DEF_TASK_I2CS_EN)&&(DEF_TASK_I2CS_EN==1))
	Usr_I2CS_InitSetup();
	#endif

	#if((defined(SENSOR_HT_TYPE))&&(SENSOR_HT_TYPE == SENSOR_TYPE_HDC3020))
	ALSensor_TH_MainLoop();
	#endif

	#if(defined(SENSOR_PT_TYPE)&&(SENSOR_PT_TYPE == SENSOR_TYPE_CMP201))
	ALSensor_CMP201_MainLoop();
	#endif

	Usr_I2CA_InitSetup();

	#if(defined(DEF_ADC_EN)&&(DEF_ADC_EN==1))
	Usr_Adc_InitSetup();
	#endif

	#if(defined(DEF_HPC_FUNC_EN)&&(DEF_HPC_FUNC_EN == 1))
	HPC_InitSetup(1);
	#else
	HeatBoard_Cool();
	#endif

	//Mcu_Timestamp = 0;

	if((Sens_CoolTime == 0)||(Sens_CoolTime == 0xFFFF))
	{
		Psf_State = PSF_STATE_INIT;
		Psf_Next_State = PSF_STATE_E703;
		Psf_State_KeepTime = PSF_STATE_E703_KEEPTIME;
	}
	else
	{
		Psf_State = PSF_STATE_INIT;
		Psf_Next_State = PSF_STATE_PREHEAT;

		if(Sens_PreHeatTime == 0xFFFF)
		{
			Psf_State_KeepTime = 0;
		}
		else
		{
			Psf_State_KeepTime = Sens_PreHeatTime;
		}
	}


	Debug_printf("\nMcu_Timestamp,%d,",Mcu_Timestamp);
	Flag_SysTick = 0;

	while(1)
	{
		Usr_I2CA_MainLoop();

		if(((Mcu_Timestamp%1000) == 0)&&(Flag_SysTick == 1))
		{
			if(MCU_Reset_Flag == 1)
			{
				MCU_Reset_Flag = 0;

				//////__set_FAULTMASK(1);

				NVIC_SystemReset();
			}

			Flag_SysTick = 0;
			// Debug_printf("\nMcu_Timestamp,%d,",Mcu_Timestamp);
		}


		#if(defined(DEF_ADC_EN)&&(DEF_ADC_EN==1))
		Usr_Adc_MainLoop();
		#endif

		if(Psf_Next_State != Psf_State)
		{
			switch(Psf_Next_State)
			{
				case PSF_STATE_INIT:
				break;

				case PSF_STATE_PREHEAT:
				{
					PORT_SetBit(Usr_LDOEN_PORT,Usr_LDOEN_PIN);
					Flag_HeatMems = 1;
					Usr_Adc_ValidTime = 0;
					g_AdcIntTaken = 0;

					if(Sens_PreHeatTime == 0xFFFF)
					{
						Psf_State_KeepTime = 0;
					}
					else
					{
						Psf_State_KeepTime = Sens_PreHeatTime;
					}
				}
				break;

				case PSF_STATE_E703:
				break;

				case PSF_STATE_COOL:
				{
					PORT_ClrBit(Usr_LDOEN_PORT,Usr_LDOEN_PIN);
					//PORT_SetBit(Usr_LDOEN_PORT,Usr_LDOEN_PIN);

					Flag_HeatMems = 0;
					Usr_Adc_ValidTime = 0;
					g_AdcIntTaken = 0;

					FilterIndex = 0;
					FilterTotal = 0;

					#if(defined(DEF_HTHH_MODE_EN)&&(DEF_HTHH_MODE_EN==1))
					if(Flag_HighTmprHighHumi == 1)
					{
						Psf_State_KeepTime = 10000;
					}
					else
					#endif
					{
						if((Sens_CoolTime==0)||(Sens_CoolTime==0xFFFF))
						{
							Sens_CoolTime = 0;
						}
						else
						{
							Psf_State_KeepTime = Sens_CoolTime;
						}
					}
				}
				break;

				default:
				break;
			}

			Psf_State = Psf_Next_State;
		}

		switch(Psf_State)
		{
			case PSF_STATE_INIT:
			break;

			case PSF_STATE_PREHEAT:
			{
				if(Psf_State_KeepTime == 0)
				{
					Psf_Next_State = PSF_STATE_E703;
				}
			}
			break;

			case PSF_STATE_E703:
			{
				if((Psf_State_KeepTime == 0)&&Flag_1Ms>2)
				{
					int16_t i16TempVal;


					Usr_E703_ReadData();

					Flag_1Ms = 0;

					#if(defined(DEF_SRAW_FILTER_EN)&&(DEF_SRAW_FILTER_EN==1))
					i16TempVal = Usr_SRaw_Filter(E703_ADC_S);
					#else
					Sens_UpdateFlag = 1;
					#endif

					E703_RegBuff[17] = E703_ADC_TC;
					E703_RegBuff[18] = E703_ADC_T;
					E703_RegBuff[19] = E703_ADC_S;
					E703_RegBuff[21] = E703_DSP_T;
					E703_RegBuff[22] = E703_DSP_S;

					if(Sens_UpdateFlag == 1)
					{   
						int32_t Sens_PPM = 0;
						int32_t i32TempVal = 0;
						float   fTempVal = 0;

						if((g_TCompCoeff.baseTRaw == 0) 
						|| (g_TCompCoeff.baseTRaw == 0xFFFF))
						{
							Tmpr_DltTRaw = 0;
						}
						else
						{
							Tmpr_DltTRaw = ExtSens_Tmpr_Raw - g_TCompCoeff.baseTRaw;
						}

						#if(defined(DEF_SRAW_FILTER_EN)&&(DEF_SRAW_FILTER_EN==1))
						Sens_SRaw = i16TempVal;
						#else
						Sens_SRaw = E703_ADC_S;
						#endif

						Sens_Raw_After_Filter = Sens_SRaw;

						Sens_UpdateFlag = 0;


						#if(defined(DEF_DBG_SRAW_0_EN)&&(DEF_DBG_SRAW_0_EN==1))
						if(Sens_Raw_After_Filter <= 0)
						{
							if(Dbg_SRaw0_Cnt1 < 65530)
							{
								Dbg_SRaw0_Cnt1++;

								DF_Data[DEF_SRAW01_INDEX]   = (uint8_t)Dbg_SRaw0_Cnt1;
								DF_Data[DEF_SRAW01_INDEX+1] = (uint8_t)(Dbg_SRaw0_Cnt1>>8);

								DF_UpdateReal_Flag = 1;
							}
						}
						#endif

						// Temperature compensation
						fTempVal = calcTempCompRawData((float)Tmpr_DltTRaw);
						i16TempVal = (int16_t)fTempVal;
						Sens_Raw_After_TmpComp = Sens_Raw_After_Filter - i16TempVal;

						// Manual compensate raw data
						i16TempVal = 0;
						#if((defined(DEF_DELTA_RAW_EN)) && (DEF_DELTA_RAW_EN == 1))
						if(Usr_Delta_Raw == 0xFFFF)
						{
							i16TempVal = 0;
						}
						else
						{
							i16TempVal = Usr_Delta_Raw;
						}
						#endif
						Sens_Raw_After_All = Sens_Raw_After_TmpComp + i16TempVal;

						// calibration
						calibrateTargetGas(Sens_Raw_After_All, &i32TempVal, Sens_TableX2, Table_32Bit, DEF_TABLE_MAX);
						
						// Get PPM after calibration
						Sens_PPM = i32TempVal;
						Sens_PPM_After_Cali = Sens_PPM;

						// Calulate delta PPM with humidity compensation
						fTempVal = 0.0;
						#if(defined(DEF_HUMCOMP_EN)&&(DEF_HUMCOMP_EN==1))
						{
							float Usr_HumComp_K = 0.0;
							
							Usr_HumComp_K = Usr_HumComp_Calc_K1(ExtSens_Tmpr);

							if(Usr_HumComp_K < 0.0)
							{
								fTempVal = Usr_HumComp_K*ExtSens_RH*100;
							}

							fTempVal += Usr_HumComp_Calc_D(ExtSens_Tmpr);
						}
						#endif

						// Update delta PPM with humidity compensation
						Usr_HumComp_PPMC_INT = (int16_t)fTempVal;

						// Get PPM after humidity compensation
						i32TempVal = fTempVal;
						Sens_PPM  -= i32TempVal;
						
						// Calulate PPM after pressure compensation
						fTempVal = 0.0;
						#if(defined(DEF_PRESCOMP_EN)&&(DEF_PRESCOMP_EN==1))
						fTempVal = Delta_Pressure_Compensation(ExtSens_Prs);
						#endif
						// Update delta PPM with pressure compensation
						dlt_ppm_pressure_int = (int16_t)fTempVal;
						
						// Get PPM with pressure compensation
						i32TempVal = (int)fTempVal;
						Sens_PPM -= i32TempVal;

						// Update PPM after pressure compensation
						Sens_PPM_After_PrsComp = (Sens_PPM/10);

						// Get PPM without offset
						i32TempVal = Sens_DC_Y;
						Sens_PPM -= i32TempVal;
						
						// Get PPM after temperature sensitivity compensation
						#if(defined(DEF_TEMPRATE_EN)&&(DEF_TEMPRATE_EN==1))
						{
							fTempVal = Usr_TmpRate_Comp((float)Sens_PPM);
							Sens_PPM = fTempVal;
						}
						#endif
						
						// Get PPM after Manual compensating PPM
						#if(defined(DEF_DELTA_PPM_EN)&&(DEF_DELTA_PPM_EN==1))
						{
							Sens_PPM += Usr_Delta_PPM1;
						}
						#endif

						// Get PPM after ASC
						#if(defined(DEF_ASC_EN)&&(DEF_ASC_EN==1))
						if((ASC_Func_En == 3)
							&&(ASC_Adjust_Cnt > 0)
							&&(ASC_Adjust_Cnt <= DEF_ASC_ADJUST_VALUE_MAX))
						{
							uint8_t i = 0;
							
							ASC_Adjust_Total = 0;
							for(i=0; i<ASC_Adjust_Cnt; i++)
							{
								ASC_Adjust_Total += ASC_Adjust_Value[i];
							}
						}
						else
						{
							ASC_Adjust_Total = 0;
						}
						Sens_PPM -= ASC_Adjust_Total;
						#endif
						
						#if(defined(DEF_JUDGE_OVER_DEWP_EN)&&(DEF_JUDGE_OVER_DEWP_EN==1))
						if(IsHumidityLargerThanDewRH(ExtSens_Tmpr) == 0)
						#endif
						{
							fTempVal = Sens_PPM;
						
							if((Donot_Alarm_5s > 0) || (ASC_Init_Error > 0))
							{
								fTempVal = 0;
							}
						
							#if(defined(DEF_LFL_EN)&&(DEF_LFL_EN==1))
						
							#if((defined(DEF_GAS_TYPE))&&(DEF_GAS_TYPE == DEF_GAS_R454B))
							fTempVal = fTempVal/115000.0f;		// For R454B;
							#endif
						
							#if((defined(DEF_GAS_TYPE))&&(DEF_GAS_TYPE == DEF_GAS_R32))
							fTempVal = fTempVal/144000.0f;		// For R32;
							#endif
						
							fTempVal *= 1000;
						
							if(fTempVal < 0.0001)
							{
								Sens_LFL_U16 = 0;
							}
							else
							{
								Sens_LFL_U16 = (uint16_t)fTempVal;
							}
							#endif
						
							#if(defined(DEF_CONCEN_THRE_EN)&&(DEF_CONCEN_THRE_EN==1))
							if((Flag_Concen_Threshold_En == 1) && (Donot_Alarm_5s == 0))
							{
								if(Sens_LFL_U16 > Concen_Threshold)
								{
									Flag_Concen_Threshol_Alarm = 1;
									#if(defined(DEF_ALARM5MIN_EN)&&(DEF_ALARM5MIN_EN==1))
									Concentration_Alarm_HoldTime = 5*60;
									#endif
								}
								#if(!(defined(DEF_ALARM5MIN_EN)&&(DEF_ALARM5MIN_EN==1)))
								else
								{
									Flag_Concen_Threshol_Alarm = 0;
								}
								#endif
							}
							else
							{
								Flag_Concen_Threshol_Alarm = 0;
							}
							#endif
						
							#if 0//(defined(DEF_ASC_EN)&&(DEF_ASC_EN==1))
							if((Donot_Alarm_5s == 0) && (ASC_Func_En == 3))
							{
								if(Flag_Concen_Threshold_En == 1)
								{	
									if(Sens_LFL_U16 > Concen_Threshold)
									{
										LFL_LeakSignal_Rt = 1;
									}
									else
									{
										LFL_LeakSignal_Rt = 0;
									}
								}
								else
								{
									if(Sens_LFL_U16 > 100)
									{
										LFL_LeakSignal_Rt = 1;
									}
									else
									{
										LFL_LeakSignal_Rt = 0;
									}
								}
							}
							else
							{
								LFL_LeakSignal_Rt = 0;
							}
							#endif
						#if(defined(DEF_JUDGE_OVER_DEWP_EN)&&(DEF_JUDGE_OVER_DEWP_EN==1))
							Flag_Over_Dewp = 0;
						}
						else
						{
							Sens_LFL_U16 = 0;
							Flag_Over_Dewp = 1;
						#endif
						}

						#if(defined(DEF_ASC_TEST_EN)&&(DEF_ASC_TEST_EN==1))
						Sens_PPM = DEF_ASC_TEST_PPM_VALUE;
						#endif

						Sens_PPM_After_All_I32 = Sens_PPM;

						#if((defined(DEF_OVERRANGE_ALARM_EN))&&(DEF_OVERRANGE_ALARM_EN == 1))
						if(PPM_RangeMax > 0)
						{
							if(Sens_PPM_After_All_I32>=PPM_RangeMax)
							{
								Flag_Overrange_Ppm = 1;
							}
							else
							{
								Flag_Overrange_Ppm = 0;
							}
						}
						else
						{
							Flag_Overrange_Ppm = 0;
						}
						#endif

						#if((defined(DEBUG_HUMI_RATE_EN))&&(DEBUG_HUMI_RATE_EN==1))
						// Update datas to customer; 
						if(Flag_RH_Rate_Exceed == 0)
						{
							Sens_LFL_U16_Cust = Sens_LFL_U16;
							ErrorData1_Cust = ErrorData1;
							Psf_Gas_TypeCode_Cust = Psf_Gas_TypeCode;
							TH_Sensor_Temperature_out_Cust = TH_Sensor_Temperature_out;
							TH_Sensor_Humidity_out_Cust = TH_Sensor_Humidity_out;
						}
						#else
						{
							Sens_LFL_U16_Cust = Sens_LFL_U16;
							ErrorData1_Cust = ErrorData1;
							Psf_Gas_TypeCode_Cust = Psf_Gas_TypeCode;
							TH_Sensor_Temperature_out_Cust = TH_Sensor_Temperature_out;
							TH_Sensor_Humidity_out_Cust = TH_Sensor_Humidity_out;
						}
						#endif

						setSensorParam((uint8_t*)&g_tSensor.TRawData,     ExtSens_Tmpr_Raw);
						setSensorParam((uint8_t*)&g_tSensor.SRawDataNoT,  Sens_Raw_After_Filter);
						setSensorParam((uint8_t*)&g_tSensor.SRawData,     Sens_Raw_After_All);
						setSensorParam((uint8_t*)&g_tSensor.RawPPM,       Sens_PPM_After_Cali);
						setSensorParam((uint8_t*)&g_tSensor.TempPPM,      Sens_PPM_After_PrsComp);
						setSensorParam((uint8_t*)&g_tSensor.FinalPPM_MSB, (uint16_t)(Sens_PPM_After_All_I32>>16));
						setSensorParam((uint8_t*)&g_tSensor.FinalPPM_LSB, (uint16_t)Sens_PPM_After_All_I32);
						setSensorParam((uint8_t*)&g_tSensor.FinalLFL,     Sens_LFL_U16);
						setSensorParam((uint8_t*)&g_tSensor.HumiCompVal,  Usr_HumComp_PPMC_INT);
						setSensorParam((uint8_t*)&g_tSensor.PressCompVal, dlt_ppm_pressure_int);
						setSensorParam((uint8_t*)&g_tSensor.WarningFlag,  Flag_Concen_Threshol_Alarm);

						setSensorParam((uint8_t*)&g_tClientData.FinalLFL, Sens_LFL_U16_Cust);
						setSensorParam((uint8_t*)&g_tClientData.ErrCode,  ErrorData1_Cust);
						setSensorParam((uint8_t*)&g_tClientData.GasType,  Psf_Gas_TypeCode_Cust);
						setSensorParam((uint8_t*)&g_tClientData.T,        TH_Sensor_Temperature_out_Cust);
						setSensorParam((uint8_t*)&g_tClientData.RH,       TH_Sensor_Humidity_out_Cust);
						setSensorParam((uint8_t*)&g_tClientData.ASC_Val,  ASC_Adjust_Total);

						if((Sens_CoolTime != 0)&&(Sens_CoolTime != 0xFFFF))
						{
							Psf_Next_State = PSF_STATE_COOL;
						}
					}
				}
			}
			break;

			case PSF_STATE_COOL:
			{
				if(Psf_State_KeepTime == 0)
				{
					Psf_Next_State = PSF_STATE_PREHEAT;
				}
			}
			break;

			default:
			break;
		}


		#if((defined(SENSOR_HT_TYPE))&&(SENSOR_HT_TYPE > 0))
		ALSensor_TH_MainLoop();

		Debug_printf("\tHDC3020 ExtSens_Tmpr,%f,\tExtSens_RH,%f,",ExtSens_Tmpr,ExtSens_RH);
		#endif

		#if(defined(SENSOR_PT_TYPE)&&(SENSOR_PT_TYPE == SENSOR_TYPE_CMP201))

		//ALSensor_CMP201_Stage = 0;

		ALSensor_CMP201_MainLoop();
		Debug_printf("\tCMP201 ExtSens_Tmpr,%d,\tExtSens_Tmpr2,%f,",ExtSens_Prs,ExtSens_Tmpr2);

		#endif


		#if((defined(DEF_HTHH_MODE_EN))&&(DEF_HTHH_MODE_EN==1))

		if(((ExtSens_Tmpr>DEF_HIGH_TMPR1)&&(ExtSens_RH>DEF_HIGH_HUMI1))
		||((ExtSens_Tmpr>DEF_HIGH_TMPR2)&&(ExtSens_RH>DEF_HIGH_HUMI2)))
		{
			Flag_HighTmprHighHumi = 1;
		}
		else
		{
			Flag_HighTmprHighHumi = 0;
		}

		#endif

		#if(defined(DEF_FREEMODBUS_EN)&&(DEF_FREEMODBUS_EN==1))
		{

			( void )eMBPoll(  );

			/* Here we simply count the number of poll cycles. */
			// usRegInputBuf[0]++;

			#if(defined(DEF_HEAT_BOARD_EN)&&(DEF_HEAT_BOARD_EN == 1))
			if(HeatBoard_ParamFlag == 10)
			{

			if((HeatBoard_Duty == 0) \
			||(HeatBoard_Period == 0) \
			||(HeatBoard_Duty > HeatBoard_Period) \
			||(HeatBoard_Duty == 65535) \
			||(HeatBoard_Period == 65535) \
			||(HeatBoard_PreTime == 65535) \
			)
			{
				HeatBoard_ParamFlag = 0;
			}
			else if(HeatBoard_Duty < HeatBoard_Period)
			{
				HeatBoard_ParamFlag = 1;
			}
			else
			{
				HeatBoard_ParamFlag = 2;
			}

			HeatBoard_Heat();
			HeatBoard_Cnt = 0;
			}
			#endif
		}
		#endif

		if(Mcu_Time1s_Cnt>0)
		{   
			int i;

			Mcu_Time1s_Cnt = 0;

			if(Donot_Alarm_5s>0)
			{
				Donot_Alarm_5s--;
			}

			#if(defined(DEF_CONCEN_THRE_EN)&&(DEF_CONCEN_THRE_EN==1))

			#if(defined(DEF_ALARM5MIN_EN)&&(DEF_ALARM5MIN_EN==1))
			if(Concentration_Alarm_HoldTime>0)
			{
				Concentration_Alarm_HoldTime--;
			}

			if(Concentration_Alarm_HoldTime == 0)
			{
				Flag_Concen_Threshol_Alarm = 0;
				setSensorParam((uint8_t*)&g_tSensor.WarningFlag, 0);
			}
			#endif

			#endif

			#if(defined(DEF_TMPR_RATE_EN)&&(DEF_TMPR_RATE_EN==1))

			if(TR_Data_Cnt<2)
			{
				TR_Tmpr[TR_Data_Cnt] = TH_Sensor_Temperature_out;
				TR_Data_Cnt++;
				TR_Tmpr_Rate = 0;
			}
			else
			{
				for(i=0;i<2-1;i++)
				{
					TR_Tmpr[i] = TR_Tmpr[i+1];
				}
				TR_Tmpr[i] = TH_Sensor_Temperature_out;
			}

			if(TR_Data_Cnt==2)
			{
				TR_Tmpr_Delt = TR_Tmpr[1]-TR_Tmpr[0];

				TR_Tmpr_Rate = TR_Tmpr_Delt*60;
			}
			#endif

			#if(defined(DEF_HUMI_RATE_EN)&&(DEF_HUMI_RATE_EN==1))

			if(HR_Data_Cnt<2)
			{
				HR_Humi[HR_Data_Cnt] = TH_Sensor_Humidity_out;
				HR_Data_Cnt++;
				HR_Humi_Rate = 0;
				setSensorParam((uint8_t*)&g_tSensor.RH_Rate, 0);
			}
			else
			{
				for(i=0;i<2-1;i++)
				{
					HR_Humi[i] = HR_Humi[i+1];
				}
				HR_Humi[i] = TH_Sensor_Humidity_out;
			}

			if(HR_Data_Cnt==2)
			{
				HR_Humi_Delt = HR_Humi[1]-HR_Humi[0];

				HR_Humi_Rate = HR_Humi_Delt*60;
				setSensorParam((uint8_t*)&g_tSensor.RH_Rate, HR_Humi_Rate);
			}

			#endif

			#if(defined(DEF_PRES_RATE_EN)&&(DEF_PRES_RATE_EN==1))

			if(PR_Data_Cnt<2)
			{
				PR_Pres[PR_Data_Cnt] = PSensor_Pressure_10Pa;
				PR_Data_Cnt++;
				PR_Pres_Rate = 0;
			}
			else
			{
				for(i=0;i<2-1;i++)
				{
					PR_Pres[i] = PR_Pres[i+1];
				}
				PR_Pres[i] = PSensor_Pressure_10Pa;
			}

			if(PR_Data_Cnt==2)
			{
				PR_Pres_Delt = PR_Pres[1]-PR_Pres[0];

				PR_Pres_Rate = PR_Pres_Delt*60;
			}

			#endif 


			#if(defined(DEF_HPC_FUNC_EN)&&(DEF_HPC_FUNC_EN==1))
			#if(defined(DEF_HPC_TEST_EN)&&(DEF_HPC_TEST_EN==1))
			HPC_Tmpr = DEF_HPC_TMPR;
			HPC_Humi = DEF_HPC_HUMI;
			HPC_HumiRate = DEF_HPC_HUMIRATE;
			#else
			HPC_Tmpr = TH_Sensor_Temperature_out;
			HPC_Humi = TH_Sensor_Humidity_out;
			HPC_HumiRate = HR_Humi_Rate;
			#endif
			#endif


			if(Donot_Alarm_5s == 0)
			{
				#if(defined(DEF_ASC_EN)&&(DEF_ASC_EN==1))
				Usr_ASC_MainLoop();
				#endif
			}

			if(Donot_Alarm_5s == 0)
			{
				#if(defined(DEF_HPC_FUNC_EN)&&(DEF_HPC_FUNC_EN==1))
				HPC_MainLoop();
				#endif
			}

			if((Donot_Alarm_5s == 0)
				&&(ASC_Init_Error == 0))
			{   // Error process;

				// BIT0;
				if((Flag_TH_Err_Comm == 1))
				{
					ErrorData1 |= 0x0001;
				}
				else
				{
					ErrorData1 &= 0xFFFE;
				}

				// BIT1;
				if((Flag_CMP201_Err_Comm == 1))
				{
					ErrorData1 |= 0x0002;
				}
				else
				{
					ErrorData1 &= 0xFFFD;
				}

				// BIT2;
				ErrorData1 &= 0xFFFB;

				// BIT3;
				ErrorData1 &= 0xFFF7;

				// BIT4;
				if((Flag_TH_Err_TRange == 1))
				{   // 
					ErrorData1 |= 0x0010;
				}
				else
				{   
					ErrorData1 &= 0xFFEF;
				}

				// BIT5;
				#if(defined(DEF_ASC_EN)&&(DEF_ASC_EN==1))
				if(ASC_Func_En == 3)
				{   // Disable ASC function;
					ErrorData1 |= 0x0020;
				}
				else
				#endif
				{   // Enable ASC function;
					ErrorData1 &= 0xFFDF;
				}


				// BIT6;
				#if(defined(DEF_ASC_EN)&&(DEF_ASC_EN==1))
				if((ASC_Func_En == 3)&&(ASC_Adjust_Cnt>=DEF_ASC_ADJUST_VALUE_MAX))
				{
					ErrorData1 |= 0x0040;
				}
				else
				#endif
				{
					ErrorData1 &= 0xFFBF;
				}


				// BIT7;
				if(Flag_Overrange_Ppm==1)
				{   // 
					ErrorData1 |= 0x0080;
				}
				else
				{   
					ErrorData1 &= 0xFF7F;
				}

				// BIT8;
				#if(defined(DEF_JUDGE_OVER_DEWP_EN)&&(DEF_JUDGE_OVER_DEWP_EN==1))
				if(Flag_Over_Dewp == 1)
				{
					ErrorData1 |= 0x0100;
				}
				else
				{
					ErrorData1 &= 0xFEFF;
				}
				#endif

				// BIT9;
				if((Flag_TH_Err_Comm == 1)||(Flag_CMP201_Err_Comm == 1))
				{   // 
					ErrorData1 |= 0x0200;
				}
				else
				{   
					ErrorData1 &= 0xFDFF;
				}

				// BIT10;
				ErrorData1 &= 0xFBFF;

				// BIT11;
				if((Flag_TH_Err_Comm == 1)||(Flag_CMP201_Err_Comm == 1))
				{   // 
					ErrorData1 |= 0x0800;
				}
				else
				{   
					ErrorData1 &= 0xF7FF;
				}

				// BIT12;
				if(Sens_TableLen<=1)
				{   // 
					ErrorData1 |= 0x1000;
				}
				else
				{   
					ErrorData1 &= 0xEFFF;
				}

				// BIT13;
				ErrorData1 &= 0xDFFF;

				// BIT14;
				#if(defined(DEF_ASC_EN)&&(DEF_ASC_EN==1))
				if((ASC_Func_En == 3)&&(ASC_Adjust_Cnt>=DEF_ASC_ADJUST_VALUE_MAX-2))
				{
					ErrorData1 |= 0x4000;
				}
				else
				#endif
				{
					ErrorData1 &= 0xBFFF;
				}

				// BIT15;
				ErrorData1 &= 0x7FFF;

			}
			else
			{
				ErrorData0 = 0;
				ErrorData1 = 0;
				ErrorData2 = 0;
			}
		}

		#if(defined(DEF_DATAFLASH_EN)&&(DEF_DATAFLASH_EN == 1))
		{
			if(DF_UpdateReal_Flag == 1)
			{
				EraseSector(DEF_DF_PARAM_STARTADDR);

				flash_write(DEF_DF_PARAM_STARTADDR, DEF_DF_DATA_LEN, DF_Data);

				DF_UpdateReal_Flag = 0;

				Usr_DFData_To_Variable();
			}
		}
		#endif

		if(E703_Reset_Flag == 1)
		{
			E703_Reset_Flag = 0;

			Usr_Read_All_Reg();
			Usr_Read_All_CM();

			{
				uint16_t crc16 = 0;

				crc16 = Usr_E703_CRC(16,0x8005,0xFFFF,(uint16_t*)Buff_U8,(DEF_CM_DATA_NUM-1)*16);

				Usr_E703_UnlockReg();
				Usr_E703_UnlockCMUsr();

				Usr_E703_WriteCMUsr(0x7E,crc16);

				Usr_E703_LockCMUsr();
				Usr_E703_LockReg();

				E703_CMData_Probe[63].addr = 0x7E;
				E703_CMData_Probe[63].data = crc16;
				E703_CMBuff[63] = crc16;
			}

			Sample_DelayMs(50);

			// E703 Reset;
			{
				// 0xB169: reset;   Performs a reset with complete power up sequence
				uint16_t uint16_tmp1 = 0xB169;
				Usr_E703_WriteReg(DEF_REGADDR_CMD, uint16_tmp1);

				Debug_printf("\nE703_Reset;");

				Usr_E703_LockCMFCT();
				Usr_E703_LockCMUsr();
				Usr_E703_LockReg();
			}

			Sample_DelayMs(50);
			Mcu_Timestamp = 800;
		}
	}
}
#endif




#endif


