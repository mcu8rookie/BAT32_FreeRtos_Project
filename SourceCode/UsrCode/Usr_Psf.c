#ifndef __USR_PSF_C__
#define __USR_PSF_C__


#include <stdint.h>

#include "Usr_Config.h"
#include "Usr_Psf.h"

#include "Usr_ALSensor.h"
#include "Usr_DataFlash.h"

uint16_t Psf_Gas_Type;
uint16_t Psf_Gas_TypeCode;
uint16_t Psf_MeasurementFlag;

uint8_t Psf_State;
uint8_t Psf_Next_State;
unsigned int Psf_State_KeepTime;


uint8_t Sens_UpdateFlag;
int16_t Sens_SRaw;

uint16_t ErrorData0;
uint16_t ErrorData1;
uint16_t ErrorData2;



uint16_t Sens_DC_Y;

int16_t Sens_Raw_After_Mems;
int16_t Sens_Raw_After_Filter;
int16_t Sens_Raw_After_TmpComp;
int16_t Sens_Raw_After_HtComp;
int16_t Sens_Raw_After_DltRaw;
int16_t Sens_Raw_After_All;


uint16_t Sens_PPM_After_Cali;
uint16_t Sens_PPM_After_PrsComp;
uint16_t Sens_PPM_After_All;
int32_t  Sens_PPM_After_All_I32;

uint16_t Sens_LFL_U16;


#if(defined(DEF_CONCEN_THRE_EN)&&(DEF_CONCEN_THRE_EN==1))
uint16_t Concen_Threshold;
uint8_t Flag_Concen_Threshol_Alarm;
uint8_t Flag_Concen_Threshold_En;
uint16_t Donot_Alarm_5s;
uint16_t Concentration_Alarm_HoldTime;
#endif


int16_t Tmpr_DltTRaw;

uint16_t Sens_CoolTime;
uint16_t Sens_PreHeatTime;
uint16_t Sens_FilterCnt;


uint16_t Sens_TableX[DEF_TABLE_MAX];
uint16_t Sens_TableY[DEF_TABLE_MAX];
int16_t Sens_TableX2[DEF_TABLE_MAX];
uint32_t Table_32Bit[DEF_TABLE_MAX];
uint8_t Sens_TableLen;





float HumComp_M2_S[DEF_HUMCOMP_PARAM_MAX];
uint16_t HumComp_Flag;
uint16_t HumComp_Flag2;


uint16_t Flag_HumiCompParameter;
uint16_t Flag_HumiCompParameter2;


int16_t Usr_HumComp_PPMC_INT;


int16_t Usr_Delta_Raw;
int16_t Usr_Delta_PPM1;

#if(defined(DEF_DBG_SRAW_0_EN)&&(DEF_DBG_SRAW_0_EN==1))
uint16_t Dbg_SRaw0_Cnt1;
uint16_t Dbg_SRaw0_Cnt2;
#endif



#if(defined(DEF_HUMCOMP_EN)&&(DEF_HUMCOMP_EN==1))

float Usr_HumComp_Calc_K1(float T)
{   
	float k = 0.0;

    if((Flag_HumiCompParameter != 0) && (HumComp_Flag != 0))
    {
    	if(T >= 10)
    	{
			float temp = 0.0;
			
			k = HumComp_M2_S[0];
			
			temp = T;
			k += HumComp_M2_S[1]*temp;
			
			temp *= T;
			k += HumComp_M2_S[2]*temp;
			
			temp *= T;
			k += HumComp_M2_S[3]*temp;
		}
    }

    return k;
}

float Usr_HumComp_Calc_D(float T)
{
    float deltaPPM = 0.0;
    
    if((Flag_HumiCompParameter2 != 0) && (HumComp_Flag != 0))
	{
		if(T >= 10)
		{
			float temp = 0;
			
			deltaPPM = HumComp_M2_S[4];

			temp = T;
			deltaPPM += temp*HumComp_M2_S[5];

			temp *= T;
			deltaPPM += temp*HumComp_M2_S[6];

			temp *= T;
			deltaPPM += temp*HumComp_M2_S[7];
		}
	}
    
    return deltaPPM;
}

#endif




#if(defined(DEF_PRESCOMP_EN)&&(DEF_PRESCOMP_EN == 1))

uint16_t PresComp_PBase;

float PresComp_K[DEF_PRESCOMP_PARAM_MAX];

uint16_t PresComp_Flag;

uint16_t Flag_PresCompParameter;

int16_t dlt_ppm_pressure_int;


float Delta_Pressure_Compensation(int prsu)
{   
	float deltaPPM = 0.0;
	
    if((PresComp_Flag != 0)
		&& (Flag_PresCompParameter != 0)
		&& (PresComp_PBase != 0)
		&& (PresComp_PBase != 0xFFFF))
    {   
		float tmp0 = 0;
		float tmp1 = 0;
		
        tmp0 = prsu;                // Real pressure; Unit: 1Pa;
        
        tmp1 = tmp0/10;             // Real pressure; Unit: 10Pa;
        
        tmp1 -= PresComp_PBase;   // Delta pressure; Unit: 10Pa;
        
        tmp0 = tmp1/10000.0;            // Delta pressure; Unit: 100000Pa = 1Bar;
        
		deltaPPM = PresComp_K[0];

		tmp1 = tmp0;
		deltaPPM += PresComp_K[1]*tmp1;

		tmp1 *= tmp0;
		deltaPPM += PresComp_K[2]*tmp1;
    }
    
    return deltaPPM;
}

#endif

#if(defined(DEF_TEMPRATE_EN)&&(DEF_TEMPRATE_EN == 1))

int16_t TmpRate_P;

float Usr_TmpRate_Comp(float arg)
{   
	float finalPPM = 0.0;
	
    if((TmpRate_P != 0) && ((uint16_t)TmpRate_P != 0xFFFF))
    {   
		float tmp0 = 0;
		float tmp1 = 0;
		float tmp2 = 0;
        
        tmp1 = TmpRate_P;
        tmp2 = (float)Tmpr_DltTRaw;
        
        tmp0 = tmp1*tmp2;
        tmp0 /= 1048576;
        tmp0 += 1;
        finalPPM = arg/tmp0;
    }
	else
	{
		finalPPM = arg;
	}
	
	return finalPPM;
}

#endif

#if((defined(DEF_HTHH_MODE_EN))&&(DEF_HTHH_MODE_EN==1))

//#define DEF_HIGH_TMPR1   (80.0f)
//#define DEF_HIGH_HUMI1   (0.7f)

//#define DEF_HIGH_TMPR2   (60.0f)
//#define DEF_HIGH_HUMI2   (0.85f)

//extern double High_Tmpr;
//extern double High_Humi;

uint8_t Flag_HighTmprHighHumi;

#endif

#if(defined(DEF_ADC_EN)&&(DEF_ADC_EN == 1))

uint16_t Monitor_Raw1;

#endif

#if(defined(DEF_HEAT_COMP2_EN)&&(DEF_HEAT_COMP2_EN == 1))

uint8_t Flag_HtComp_2;

uint16_t HtComp_TRaw_Base_2;
uint16_t HtComp_HtRaw_Base_2;
int16_t HtComp_Kh_2;
int16_t HtComp_SP_2;
int16_t HtComp_Ks_2;

int16_t HtComp_Delta_TRaw_2;
uint16_t HtComp_HtRaw_Base_rt_2;
uint16_t HtComp_HtRaw_Base_min_2;
uint16_t HtComp_HtRaw_Base_max_2;

int16_t Delta_Ht_Raw_2;
int16_t Delta_Ht_Comp_2;
int16_t HtComp_CompTotal_2;

int32_t Dlt_P;

int32_t Dlt_P0;

uint16_t HtComp_DP0;

#endif

#if(defined(DEF_JUDGE_OVER_DEWP_EN)&&(DEF_JUDGE_OVER_DEWP_EN==1))

uint8_t Flag_Over_Dewp;

unsigned char IsHumidityLargerThanDewRH(float T)
{
	unsigned char ret = 0;
	
	if(T >= 45)
	{
	// y = 0.03443*x^2 - 6.033921*x + 276.480364
		double dewRH = 0;
		double temp = 0;
	
		dewRH  = T;
		dewRH *= T;
		dewRH *= 0.03443;
	
		temp = -6.033921*T;
	
		dewRH += temp;
		dewRH += 276.480364;
		    
		if(TH_Sensor_Humidity_out/10 >= (unsigned int)dewRH)
		{
			ret = 1;
		}
	}
	
	return ret;
}

#endif





volatile uint16_t Flag_1Ms;

#define DEF_TYPE_BIT    0
#define DEF_TYPE_BOOL   0

#define DEF_TYPE_CHAR       1   //8bit;
#define DEF_TYPE_SCHAR      1   //8bit;
#define DEF_TYPE_UCHAR      2   //16bit;
#define DEF_TYPE_SINT16     3
#define DEF_TYPE_UINT16     4
#define DEF_TYPE_SINT32     7
#define DEF_TYPE_UINT32     8
#define DEF_TYPE_SINT64     9
#define DEF_TYPE_UINT64     10

#define DEF_TYPE_FLT    0
#define DEF_TYPE_DBL    0
#define DEF_TYPE_LDBL   0

#if(defined(DEF_FUN_TCOMP_EN) && (DEF_FUN_TCOMP_EN == 1))

TempCompCoeffType g_TCompCoeff = {0};

float calcTempCompRawData(float nbr)
{   
	float deltaSRaw = 0;
    
    if((g_TCompCoeff.flag != 0)
		&& (g_TCompCoeff.baseTRaw != 0)
		&& (g_TCompCoeff.baseTRaw != 0xFFFF))
	{
		float fTempVal = 0;
		
		deltaSRaw = g_TCompCoeff.P0;
		
		fTempVal = nbr;
		deltaSRaw += g_TCompCoeff.P1*fTempVal;

		fTempVal *= nbr;
		deltaSRaw += g_TCompCoeff.P2*fTempVal;

		fTempVal *= nbr;
		deltaSRaw += g_TCompCoeff.P3*fTempVal;
	    
	    if(deltaSRaw >= 32766.9)
	    {
	        deltaSRaw = 32767;
	    }
	    else if (deltaSRaw <= -32766.9)
	    {
	        deltaSRaw = -32767;
	    }
	}
	return deltaSRaw;
}
#endif


//#define DEF_SRAW_FILTERMAX      64
//#define DEF_SRAW_FILTERCNT      4

int16_t FilterBuff[DEF_SRAW_FILTERMAX];
int8_t FilterIndex = 0;
int32_t FilterTotal = 0;

int16_t Usr_SRaw_Filter(int16_t in)
{
    int8_t i;
    
    //if(FilterIndex<DEF_SRAW_FILTERCNT)
    if(Sens_FilterCnt <= 1)
    {
        Sens_UpdateFlag = 1;
        
        return in;
    }
    
    if(FilterIndex<Sens_FilterCnt)
    {
        FilterBuff[FilterIndex++] = in;
        FilterTotal+=in;
        
        if(FilterIndex == Sens_FilterCnt)
        {
            Sens_UpdateFlag = 1;
        }
    }
    else
    {
        FilterTotal -= FilterBuff[0];
        
        for(i=0;i<Sens_FilterCnt-1;i++)
        {
            FilterBuff[i] = FilterBuff[i+1];
        }
        FilterBuff[i] = in;
        
        FilterTotal+=in;
        
        Sens_UpdateFlag = 1;
    }
    
    return (FilterTotal/FilterIndex);
}



uint8_t calibrateTargetGas(int16_t datain, int32_t *dataout, int16_t * Xcoordinates, uint32_t* Ycoordinates, uint8_t nbr)
{   
	uint8_t k = 0;
	uint8_t ret = 0;
	float f32_tmp = 0;

	if((dataout == 0) || (nbr < 2))
	{   
		ret = 0;
	}
	else
	{   
		for(k=0; k<(nbr-1); k++)
		{   
			if((Xcoordinates[k] == 0xFFFFFFFF)
				|| (Xcoordinates[k] >= Xcoordinates[k+1])
				|| (Ycoordinates[k] == 0xFFFFFFFF)
				|| (Ycoordinates[k] >= Ycoordinates[k+1]))
			{
				*dataout = 0;
				ret = 0;
				break;
			}
			else if(Xcoordinates[k+1] == 0xFFFFFFFF)
			{
				if(k > 0)
				{
					*dataout = Ycoordinates[k];
				}
				else
				{
					*dataout = 0;
				}
				ret = 0;
				break;
			}
			else if(datain <= Xcoordinates[k+1])
			{   
				f32_tmp = ((float)datain - (float)(Xcoordinates[k]))*((float)(Ycoordinates[k+1]) - (float)(Ycoordinates[k]));

				f32_tmp = f32_tmp/((float)(Xcoordinates[k+1]) - (float)(Xcoordinates[k]));

				f32_tmp = (float)Ycoordinates[k] + f32_tmp;

				*dataout = (int32_t)f32_tmp;

				ret = 1;
				break;
			}
		}
	}
    
    return ret;
}

#if((defined(DEF_OVERRANGE_ALARM_EN))&&(DEF_OVERRANGE_ALARM_EN == 1))

#define DEF_TBL_Y_IDLE      (0xFFFF)

uint8_t Flag_Overrange_Ppm;
int32_t PPM_RangeMax;

void Usr_CheckRangeMax(void)
{   
    unsigned char cnt;
    
    Flag_Overrange_Ppm = 0;
    
    for(cnt=0;cnt<DEF_TABLE_MAX;cnt++)
    {
        if(Sens_TableY[cnt] == DEF_TBL_Y_IDLE)
        {
            break;
        }
    }
    
    if(cnt == 0)
    {
        PPM_RangeMax = 0;
    }
    else if(cnt == DEF_TABLE_MAX)
    {
        PPM_RangeMax = Table_32Bit[10]-(uint32_t)Sens_DC_Y;
    }
    else
    {
        PPM_RangeMax = Table_32Bit[cnt]-(uint32_t)Sens_DC_Y;
    }
    
    Sens_TableLen = cnt;
}

#endif



// judge whether is FP32 number;
// ptr: a pointer to number's address; the number is that will judgement;
// return: 0 if not number, or 1 is number;
uint8_t FP32_IsNumerical(uint8_t *ptr)
{   
    uint8_t u8_tmp;
    
    u8_tmp = *(ptr+3);
    if((u8_tmp&0x7F) == 0x7F)
    {
        u8_tmp = *(ptr+2);
        if((u8_tmp&0x80) == 0x80)
        {
            return 0;
        }
    }
    
    return 1;
}


#if(defined(DEF_ASC_EN)&&(DEF_ASC_EN==1))

uint16_t SelfMoni2_DriftFault;

int32_t ASC_Average_Array[ASC_ARRAYLEN];

uint8_t ASC_Average_Index;

uint16_t ASC_TimeCnt;
uint16_t ASC_TimeCnt_Th;

uint8_t LFL_LeakSignal_Rt = 0;

uint16_t LFL_Leakage_Flag;

int32_t ASC_PPM_Total;
int32_t  ASC_PPM_Cnt;
int32_t  ASC_PPM_Average;


#if(defined(DEF_ASC_EN)&&(DEF_ASC_EN==1))

uint16_t ASC_Func_En;

uint16_t ASC_Usr_En;
uint16_t ASC_Param_En;


uint16_t ASC_PPM_HighTh;
uint16_t ASC_PPM_LowTh;

int32_t ASC_PPM_HighTh_S32;
int32_t ASC_PPM_LowTh_S32;

uint16_t ASC_Adjust_Cnt;

int16_t ASC_Adjust_Value[DEF_ASC_ADJUST_VALUE_MAX];
int32_t ASC_Adjust_Total;

#define DEF_TMPR_BUFFLEN    (2)

int16_t ASC_Tmpr_Rt;
int16_t ASC_Tmpr[DEF_TMPR_BUFFLEN];
uint8_t ASC_Tmpr_Index;
int16_t ASC_Tmpr_Min;
int16_t ASC_Tmpr_Max;
int16_t ASC_Tmpr_Min30M;
int16_t ASC_Tmpr_Max30M;
int16_t ASC_Tmpr_Rate;
int16_t ASC_Tmpr_RateTh;
int16_t ASC_Tmpr_RateMax30M;
int16_t ASC_Tmpr_Thre;

#define DEF_HUMI_BUFFLEN    (2)

int16_t ASC_Humi_Rt;
int16_t ASC_Humi[DEF_HUMI_BUFFLEN];
uint8_t ASC_Humi_Index;
int16_t ASC_Humi_Min;
int16_t ASC_Humi_Max;
int16_t ASC_Humi_Min30M;
int16_t ASC_Humi_Max30M;
int16_t ASC_Humi_Rate;
int16_t ASC_Humi_RateTh;
int16_t ASC_Humi_RateMax30M;

uint16_t ASC_DeltDire_Cnt;
int32_t ASC_DeltDire_Buff[DEF_ASC_DELTDIRC_BUFFLEN];

int8_t ASC_Dlt_Direct_Current;
int8_t ASC_Dlt_Direct_Last;

uint16_t ASC_Dlt_SameDire_Cnt;
uint16_t ASC_Dlt_SameDire_Cnt30M;

int32_t ASC_Dlt_ThPos;
int32_t ASC_Dlt_ThNeg;
int32_t ASC_Dlt_Value;


#endif


#if(defined(DEF_ASC_FAST_EN)&&(DEF_ASC_FAST_EN==1))
uint8_t ASC_Stage = 0;
uint16_t ASC_Fast_DataCnt;
uint8_t ASC_Init_Error = 0;
int32_t ASC_Init_Value;

uint8_t ASC_Fast_FailCnt;
uint8_t ASC_Fast_SuccCnt;
uint16_t ASC_Fast_ProcCnt;
int16_t ASC_Fast_Value;
uint8_t ASC_Fast_Rslt;
#endif

void Usr_ASC_MainLoop(void)
{   
    unsigned char loc_cnt;
    
    unsigned char loc_cnt2;
    
    int32_t int32_tmp;
    int32_t int32_tmp1;
    int32_t int32_tmp2;
    
    
    #if(defined(DEF_ASC_TEST_EN)&&(DEF_ASC_TEST_EN==1))
    //Sens_PPM = DEF_ASC_TEST_PPM_VALUE;
    ASC_Tmpr_Rt = DEF_ASC_TEST_TMPR_VALUE;
    ASC_Humi_Rt = DEF_ASC_TEST_HUMI_VALUE;
    #endif
    
    
    if(ASC_Func_En == 3)
    {   // if self-monitoring function is enable; 
        
        ASC_TimeCnt++;
        
        // whether a leakage signal had been detected;
        if(LFL_LeakSignal_Rt == 1)
        {   
            LFL_Leakage_Flag = 1;
        }
        
        #if 1
        // Test the MaxValue, MinValue and RateValue about Temperature;
        //ASC_Tmpr_Rt = 0;
        
        if(ASC_Tmpr_Index<DEF_TMPR_BUFFLEN)
        {
            ASC_Tmpr[ASC_Tmpr_Index] = ASC_Tmpr_Rt;
            ASC_Tmpr_Index++;
        }
        else
        {
            for(loc_cnt=0;loc_cnt<DEF_TMPR_BUFFLEN-1;loc_cnt++)
            {
                ASC_Tmpr[loc_cnt] = ASC_Tmpr[loc_cnt+1];
            }
            ASC_Tmpr[DEF_TMPR_BUFFLEN-1] = ASC_Tmpr_Rt;
        }
        
        if(ASC_Tmpr_Index>=DEF_TMPR_BUFFLEN)
        {
            ASC_Tmpr_Min = 32767;
            ASC_Tmpr_Max = -32768;
            
            for(loc_cnt=0;loc_cnt<DEF_TMPR_BUFFLEN;loc_cnt++)
            {
                if(ASC_Tmpr[loc_cnt]<ASC_Tmpr_Min)
                {
                    ASC_Tmpr_Min = ASC_Tmpr[loc_cnt];
                }
                
                if(ASC_Tmpr[loc_cnt]>ASC_Tmpr_Max)
                {
                    ASC_Tmpr_Max = ASC_Tmpr[loc_cnt];
                }
            }
            
            if(ASC_Tmpr_Min<=ASC_Tmpr_Min30M)
            {
                ASC_Tmpr_Min30M = ASC_Tmpr_Min;
            }
            
            if(ASC_Tmpr_Max>=ASC_Tmpr_Max30M)
            {
                ASC_Tmpr_Max30M = ASC_Tmpr_Max;
            }
            
            ASC_Tmpr_Rate = ASC_Tmpr_Max - ASC_Tmpr_Min;
            ASC_Tmpr_Rate *= 60;
            
            if(ASC_Tmpr_Rate > ASC_Tmpr_RateMax30M)
            {
                ASC_Tmpr_RateMax30M = ASC_Tmpr_Rate;
            }
            
        }
        #endif
        
        #if 1
        // Test the MaxValue, MinValue and RateValue about Humidity;
        //ASC_Humi_Rt = 0;
        if(ASC_Humi_Index<DEF_HUMI_BUFFLEN)
        {
            ASC_Humi[ASC_Humi_Index] = ASC_Humi_Rt;
            ASC_Humi_Index++;
        }
        else
        {
            for(loc_cnt=0;loc_cnt<DEF_HUMI_BUFFLEN-1;loc_cnt++)
            {
                ASC_Humi[loc_cnt] = ASC_Humi[loc_cnt+1];
            }
            ASC_Humi[DEF_HUMI_BUFFLEN-1] = ASC_Humi_Rt;
        }
        
        if(ASC_Humi_Index>=DEF_HUMI_BUFFLEN)
        {
            ASC_Humi_Min = 32767;
            ASC_Humi_Max = -32768;
            
            for(loc_cnt=0;loc_cnt<DEF_HUMI_BUFFLEN;loc_cnt++)
            {
                if(ASC_Humi[loc_cnt]<ASC_Humi_Min)
                {
                    ASC_Humi_Min = ASC_Humi[loc_cnt];
                }
                
                if(ASC_Humi[loc_cnt]>ASC_Humi_Max)
                {
                    ASC_Humi_Max = ASC_Humi[loc_cnt];
                }
            }
            
            if(ASC_Humi_Min<=ASC_Humi_Min30M)
            {
                ASC_Humi_Min30M = ASC_Humi_Min;
            }
            
            if(ASC_Humi_Max>=ASC_Humi_Max30M)
            {
                ASC_Humi_Max30M = ASC_Humi_Max;
            }
            
            ASC_Humi_Rate = ASC_Humi_Max - ASC_Humi_Min;
            ASC_Humi_Rate *= 60;
            
            if(ASC_Humi_Rate > ASC_Humi_RateMax30M)
            {
                ASC_Humi_RateMax30M = ASC_Humi_Rate;
            }
            
        }
        #endif
        
        
        #if 1
        // Test data change direct and count;
        {
            if(ASC_DeltDire_Cnt<DEF_ASC_DELTDIRC_BUFFLEN)
            {
                ASC_DeltDire_Buff[ASC_DeltDire_Cnt] = Sens_PPM_After_All_I32;
                ASC_DeltDire_Cnt++;
            }
            else
            {
                for(loc_cnt=0;loc_cnt<DEF_ASC_DELTDIRC_BUFFLEN-1;loc_cnt++)
                {
                    ASC_DeltDire_Buff[loc_cnt] = ASC_DeltDire_Buff[loc_cnt+1];
                }
                ASC_DeltDire_Buff[DEF_HUMI_BUFFLEN-1] = Sens_PPM_After_All_I32;
            }
            
            if(ASC_DeltDire_Cnt>=DEF_ASC_DELTDIRC_BUFFLEN)
            {
                
                #if((defined(DEF_GAS_TYPE))&&(DEF_GAS_TYPE == DEF_GAS_R454B))
                // For R454B;
                ASC_Dlt_ThPos = 115000/100;
                ASC_Dlt_ThNeg = (0-ASC_Dlt_ThPos);
                #endif
                
                #if((defined(DEF_GAS_TYPE))&&(DEF_GAS_TYPE == DEF_GAS_R32))
                // For R32;
                ASC_Dlt_ThPos = 144000/100;
                ASC_Dlt_ThNeg = (0-ASC_Dlt_ThPos);
                #endif
                
                ASC_Dlt_Value = ASC_DeltDire_Buff[DEF_HUMI_BUFFLEN-1]-ASC_DeltDire_Buff[DEF_HUMI_BUFFLEN-2];
                
                if(ASC_Dlt_Value>ASC_Dlt_ThPos)
                {
                    ASC_Dlt_Direct_Current = 1;
                }
                else if(ASC_Dlt_Value<ASC_Dlt_ThNeg)
                {
                    ASC_Dlt_Direct_Current = -1;
                }
                else
                {
                    ASC_Dlt_Direct_Current = 0;
                }
                
                if(ASC_Dlt_Direct_Last*ASC_Dlt_Direct_Current == 1)
                {
                    ASC_Dlt_SameDire_Cnt++;
                }
                else
                {
                    ASC_Dlt_SameDire_Cnt = 0;
                }
                
                if(ASC_Dlt_SameDire_Cnt > ASC_Dlt_SameDire_Cnt30M)
                {
                    ASC_Dlt_SameDire_Cnt30M = ASC_Dlt_SameDire_Cnt;
                }
                
                ASC_Dlt_Direct_Last = ASC_Dlt_Direct_Current;
            }
        }
        #endif
        
        
        // Collect PPM for calculate average value;
        if(ASC_PPM_Total<2147418112)
        {
            ASC_PPM_Total += Sens_PPM_After_All_I32;
            ASC_PPM_Cnt++;
        }
        
        // Calculate data or time;
        if(ASC_Fast_DataCnt<60000)
        {
            ASC_Fast_DataCnt++;
        }
        
        //
        if(ASC_Stage==0)
        {
            if(ASC_Fast_DataCnt==8)
            {
                ASC_Init_Value = ASC_PPM_Total/ASC_PPM_Cnt;
                
                //if((ASC_Init_Value>ASC_PPM_LowTh)
                    //||(ASC_Init_Value<(0-ASC_PPM_LowTh)))
                if(((ASC_Init_Value>ASC_PPM_LowTh_S32)&&(ASC_Init_Value<ASC_PPM_HighTh_S32))\
                    ||((ASC_Init_Value<(0-ASC_PPM_LowTh_S32))&&(ASC_Init_Value>(0-ASC_PPM_HighTh_S32))))
                {
                    ASC_Init_Error = 1;
                }
                else
                {
                    ASC_Init_Error = 0; 
                    ASC_Stage = 1;
                }
            }
            
        }
        
        if(ASC_Stage == 0)
        {
            #if(defined(DEF_ASC_TEST_EN)&&(DEF_ASC_TEST_EN==1))
            ASC_TimeCnt_Th = DEF_ASC_FAST_TIME;
            #else
            ASC_TimeCnt_Th = 20;   // Data Cycle, 20 sec;
            #endif
        }
        else
        {
            #if(defined(DEF_ASC_TEST_EN)&&(DEF_ASC_TEST_EN==1))
            ASC_TimeCnt_Th = DEF_ASC_NORM_TIME;
            #else
            //ASC_TimeCnt_Th = 300;   // Data Cycle, 5 min;
            ASC_TimeCnt_Th = 1800;   // Data Cycle, 0.5 hour;
            #endif
        }
        
        //if(ASC_TimeCnt>=3600)   // 1hour;
        //if(ASC_TimeCnt>=1800)   // 0.5hour;   //
        //if(ASC_TimeCnt>=900)    // 15min;
        //if(ASC_TimeCnt>=600)    // 10minute;
        //if(ASC_TimeCnt>=300)    // 5minute;
        //if(ASC_TimeCnt>=180)    // 3minute;
        if(ASC_TimeCnt >= ASC_TimeCnt_Th)
        {   // if add data keep 1 hour timeout;
            
            //if(LFL_Leakage_Flag == 0)
            if(\
                ((ASC_Tmpr_Min30M>=150)&&(ASC_Tmpr_Max30M<=350)&&(ASC_Tmpr_RateMax30M<ASC_Tmpr_RateTh))\
                &&((ASC_Humi_Min30M>=300)&&(ASC_Humi_Max30M<=700)&&(ASC_Humi_RateMax30M<ASC_Humi_RateTh))\
                &&(ASC_Dlt_SameDire_Cnt30M<3)\
                )
            {   
                
                ASC_PPM_Average = ASC_PPM_Total/ASC_PPM_Cnt;
                
                if(ASC_Average_Index<ASC_ARRAYLEN)
                {
                    ASC_Average_Array[ASC_Average_Index++] = ASC_PPM_Average;
                }
                else
                {   
                    for(loc_cnt=0;loc_cnt<ASC_ARRAYLEN-1;loc_cnt++)
                    {
                        ASC_Average_Array[loc_cnt] = ASC_Average_Array[loc_cnt+1];
                    }
                    ASC_Average_Array[ASC_ARRAYLEN-1] = ASC_PPM_Average;
                }
                
                
                if(ASC_Average_Index >= ASC_ARRAYLEN)
                {   
                    
                    ASC_Init_Error++;
                    
                    // if all data > limit or all data < limit;
                    //int32_tmp1 = ASC_PPM_LowTh; 
                    //int32_tmp2 = ASC_PPM_HighTh; 
                    
                    int32_tmp1 = ASC_PPM_LowTh_S32; 
                    int32_tmp2 = ASC_PPM_HighTh_S32; 
                    
                    for(loc_cnt=0;loc_cnt<ASC_ARRAYLEN;loc_cnt++)
                    {
                        if((ASC_Average_Array[loc_cnt]>int32_tmp1)&&(ASC_Average_Array[loc_cnt]<int32_tmp2))
                        {
                            
                        }
                        else
                        {
                            break;
                        }
                    }
                    
                    if(loc_cnt==ASC_ARRAYLEN)
                    {
                        
                        int32_tmp = 0;
                        
                        for(loc_cnt2=0;loc_cnt2<ASC_ARRAYLEN;loc_cnt2++)
                        {
                            int32_tmp += ASC_Average_Array[loc_cnt2];
                        }
                        
                        int32_tmp /= ASC_ARRAYLEN;
                        
                        if(ASC_Adjust_Cnt<DEF_ASC_ADJUST_VALUE_MAX)
                        {
                            ASC_Adjust_Value[ASC_Adjust_Cnt] = int32_tmp;
                            
                            DF_Data[DEF_ASC_VALUE1_INDEX+ASC_Adjust_Cnt*2] = (uint8_t)int32_tmp;
                            DF_Data[DEF_ASC_VALUE1_INDEX+ASC_Adjust_Cnt*2+1] = (uint8_t)(int32_tmp>>8);
                            
                            ASC_Adjust_Cnt++;
                            
                            DF_Data[DEF_ASC_CNT_INDEX] = (uint8_t)ASC_Adjust_Cnt;
                            DF_Data[DEF_ASC_CNT_INDEX+1] = (uint8_t)(ASC_Adjust_Cnt>>8);
                            
                            DF_UpdateReal_Flag = 1;
                        }
                        else
                        {
                            #if 0
                            for(loc_cnt2=0;loc_cnt2<DEF_ASC_ADJUST_VALUE_MAX-1;loc_cnt2++)
                            {
                                ASC_Adjust_Value[loc_cnt2] = ASC_Adjust_Value[loc_cnt2+1];
                                
                                DF_Data[DEF_ASC_VALUE1_INDEX+loc_cnt2*2] = (uint8_t)ASC_Adjust_Value[loc_cnt2];
                                DF_Data[DEF_ASC_VALUE1_INDEX+loc_cnt2*2+1] = (uint8_t)(ASC_Adjust_Value[loc_cnt2]>>8);
                            }
                            
                            ASC_Adjust_Value[loc_cnt2] = int32_tmp;
                            
                            DF_Data[DEF_ASC_VALUE1_INDEX+loc_cnt2*2] = (uint8_t)int32_tmp;
                            DF_Data[DEF_ASC_VALUE1_INDEX+loc_cnt2*2+1] = (uint8_t)(int32_tmp>>8);
                            
                            DF_UpdateReal_Flag = 1;
                            #endif
                        }
                        
                        
                        #if(defined(DEF_ASC_FAST_EN)&&(DEF_ASC_FAST_EN==1))
                        if(ASC_Stage==0)
                        {
                            ASC_Fast_Rslt = 1;
                            ASC_Fast_SuccCnt++;
                            ASC_Fast_Value = ASC_PPM_Average;
                        }
                        #endif
                        
                        
                        #if 1
                        if((ASC_Func_En==3)&&(ASC_Adjust_Cnt>0))
                        {
                            uint8_t i;
                            ASC_Adjust_Total = 0;
                            for(i=0;i<ASC_Adjust_Cnt;i++)
                            {
                                ASC_Adjust_Total += ASC_Adjust_Value[i];
                            }
                        }
                        else
                        {
                            ASC_Adjust_Total = 0;
                        }
                        #endif
                        
                        ASC_Init_Error = 0;
                        
                    }
                    
                    if(loc_cnt<ASC_ARRAYLEN)
                    {
                        //int32_tmp1 = (int16_t)(0-ASC_PPM_HighTh);
                        //int32_tmp2 = (int16_t)(0-ASC_PPM_LowTh);
                        
                        int32_tmp1 = (0-ASC_PPM_HighTh_S32);
                        int32_tmp2 = (0-ASC_PPM_LowTh_S32);
                        
                        for(loc_cnt=0;loc_cnt<ASC_ARRAYLEN;loc_cnt++)
                        {
                            if((ASC_Average_Array[loc_cnt]>int32_tmp1)&&(ASC_Average_Array[loc_cnt]<int32_tmp2))
                            {
                                
                            }
                            else
                            {
                                break;
                            }
                        }
                        
                        if(loc_cnt==ASC_ARRAYLEN)
                        {
                            
                            int32_tmp = 0;
                            
                            for(loc_cnt2=0;loc_cnt2<ASC_ARRAYLEN;loc_cnt2++)
                            {
                                int32_tmp += ASC_Average_Array[loc_cnt2];
                            }
                            
                            int32_tmp /= ASC_ARRAYLEN;
                            
                            if(ASC_Adjust_Cnt<DEF_ASC_ADJUST_VALUE_MAX)
                            {
                                ASC_Adjust_Value[ASC_Adjust_Cnt] = int32_tmp;
                                
                                DF_Data[DEF_ASC_VALUE1_INDEX+ASC_Adjust_Cnt*2] = (uint8_t)int32_tmp;
                                DF_Data[DEF_ASC_VALUE1_INDEX+ASC_Adjust_Cnt*2+1] = (uint8_t)(int32_tmp>>8);
                                
                                ASC_Adjust_Cnt++;
                                
                                DF_Data[DEF_ASC_CNT_INDEX] = (uint8_t)ASC_Adjust_Cnt;
                                DF_Data[DEF_ASC_CNT_INDEX+1] = (uint8_t)(ASC_Adjust_Cnt>>8);
                                
                                DF_UpdateReal_Flag = 1;
                            }
                            else
                            {
                                #if 0
                                for(loc_cnt2=0;loc_cnt2<DEF_ASC_ADJUST_VALUE_MAX-1;loc_cnt2++)
                                {
                                    ASC_Adjust_Value[loc_cnt2] = ASC_Adjust_Value[loc_cnt2+1];
                                    
                                    DF_Data[DEF_ASC_VALUE1_INDEX+loc_cnt2*2] = (uint8_t)ASC_Adjust_Value[loc_cnt2];
                                    DF_Data[DEF_ASC_VALUE1_INDEX+loc_cnt2*2+1] = (uint8_t)(ASC_Adjust_Value[loc_cnt2]>>8);
                                }
                                
                                ASC_Adjust_Value[loc_cnt2] = int32_tmp;
                                
                                DF_Data[DEF_ASC_VALUE1_INDEX+loc_cnt2*2] = (uint8_t)int32_tmp;
                                DF_Data[DEF_ASC_VALUE1_INDEX+loc_cnt2*2+1] = (uint8_t)(int32_tmp>>8);
                                
                                DF_UpdateReal_Flag = 1;
                                #endif
                            }
                            
                            
                            #if(defined(DEF_ASC_FAST_EN)&&(DEF_ASC_FAST_EN==1))
                            if(ASC_Stage==0)
                            {
                                ASC_Fast_Rslt = 1;
                                ASC_Fast_SuccCnt++;
                                ASC_Fast_Value = ASC_PPM_Average;
                            }
                            #endif
                            
                            #if 1
                            if((ASC_Func_En==3)&&(ASC_Adjust_Cnt>0))
                            {
                                uint8_t i;
                                ASC_Adjust_Total = 0;
                                for(i=0;i<ASC_Adjust_Cnt;i++)
                                {
                                    ASC_Adjust_Total += ASC_Adjust_Value[i];
                                }
                            }
                            else
                            {
                                ASC_Adjust_Total = 0;
                            }
                            #endif
                            
                            ASC_Init_Error=0;
                        }
                        
                    }
                    else
                    {
                        
                    }
                    
                    if(ASC_Stage == 0)
                    {
                        if(ASC_Init_Error==0)
                        {
                            ASC_Stage = 1;
                            for(loc_cnt=0;loc_cnt<ASC_ARRAYLEN;loc_cnt++)
                            {
                                ASC_Average_Array[loc_cnt] = 0;
                            }
                            ASC_Average_Index = 0;
                        }
                        else
                        {
                            if(ASC_Fast_DataCnt>=300)
                            {
                                ASC_Stage = 1;
                                ASC_Init_Error = 0;
                                for(loc_cnt=0;loc_cnt<ASC_ARRAYLEN;loc_cnt++)
                                {
                                    ASC_Average_Array[loc_cnt] = 0;
                                }
                                ASC_Average_Index = 0;
                                
                                
                                ASC_Fast_Rslt = 2;
                                ASC_Fast_FailCnt++;
                                ASC_Fast_Value = ASC_PPM_Average;
                                
                                #if(defined(DEF_ASC_FAST_EN)&&(DEF_ASC_FAST_EN==1))
                                {
                                    
                                    DF_Data[DEF_ASC_FAST_PROCCNT_INDEX] = ASC_Fast_SuccCnt;
                                    DF_Data[DEF_ASC_FAST_PROCCNT_INDEX+1] = ASC_Fast_FailCnt;
                                    
                                    ASC_Fast_ProcCnt = DF_Data[DEF_ASC_FAST_PROCCNT_INDEX+1];
                                    ASC_Fast_ProcCnt <<= 8;
                                    ASC_Fast_ProcCnt += DF_Data[DEF_ASC_FAST_PROCCNT_INDEX];
                                    
                                    DF_Data[DEF_ASC_FAST_VALUE_INDEX] = ASC_Fast_Value;
                                    DF_Data[DEF_ASC_FAST_VALUE_INDEX+1] = ASC_Fast_Value>>8;
                                    
                                    DF_UpdateReal_Flag = 1;
                                    
                                }
                                #endif
                            }
                        }
                    }
                }
            }
            else
            {
                for(loc_cnt=0;loc_cnt<ASC_ARRAYLEN;loc_cnt++)
                {
                    ASC_Average_Array[loc_cnt] = 0;
                    ASC_Average_Index = 0;
                }
                
                if(ASC_Stage==0)
                {
                    if(ASC_Fast_DataCnt>=300)
                    {
                        ASC_Stage = 1;
                        ASC_Init_Error = 0;
                        for(loc_cnt=0;loc_cnt<ASC_ARRAYLEN;loc_cnt++)
                        {
                            ASC_Average_Array[loc_cnt] = 0;
                        }
                        ASC_Average_Index = 0;
                        
                        ASC_Fast_Rslt = 2;
                        ASC_Fast_FailCnt++;
                        ASC_Fast_Value = ASC_PPM_Average;
                        
                        #if(defined(DEF_ASC_FAST_EN)&&(DEF_ASC_FAST_EN==1))
                        {
                            
                            DF_Data[DEF_ASC_FAST_PROCCNT_INDEX] = ASC_Fast_SuccCnt;
                            DF_Data[DEF_ASC_FAST_PROCCNT_INDEX+1] = ASC_Fast_FailCnt;
                            
                            ASC_Fast_ProcCnt = DF_Data[DEF_ASC_FAST_PROCCNT_INDEX+1];
                            ASC_Fast_ProcCnt <<= 8;
                            ASC_Fast_ProcCnt += DF_Data[DEF_ASC_FAST_PROCCNT_INDEX];
                            
                            DF_Data[DEF_ASC_FAST_VALUE_INDEX] = ASC_Fast_Value;
                            DF_Data[DEF_ASC_FAST_VALUE_INDEX+1] = ASC_Fast_Value>>8;
                            
                            DF_UpdateReal_Flag = 1;
                            
                        }
                        #endif
                    }
                }
            }
            
            LFL_Leakage_Flag = 0;
            
            //ASC_Tmpr_Index = 0;
            ASC_Tmpr_Min30M = 32767;
            ASC_Tmpr_Max30M = -32768;
            ASC_Tmpr_RateMax30M = 0;
            
            //ASC_Humi_Index = 0;
            ASC_Humi_Min30M = 32767;
            ASC_Humi_Max30M = -32768;
            ASC_Humi_RateMax30M = 0;
            
            
            ASC_DeltDire_Cnt = 0;
            ASC_Dlt_Direct_Last = 0;
            ASC_Dlt_Direct_Current = 0;
            ASC_Dlt_SameDire_Cnt = 0;
            ASC_Dlt_SameDire_Cnt30M = 0;
            
            
            ASC_TimeCnt = 0;
            ASC_PPM_Total = 0;
            ASC_PPM_Cnt = 0;
            
            // ASC_Adjust_Cnt = 0;
            
        }
    }
    else
    {
        
        ASC_Average_Index = 0;
        LFL_Leakage_Flag = 0;
        ASC_TimeCnt = 0;
        ASC_PPM_Total = 0;
        ASC_PPM_Cnt = 0;
        
        #if(defined(DEF_ASC_EN)&&(DEF_ASC_EN==1))
        
        //ASC_Tmpr_Rt = 0;
        ASC_Tmpr_Index = 0;
        ASC_Tmpr_Min = 0;
        ASC_Tmpr_Max = 0;
        ASC_Tmpr_Min30M = 32767;
        ASC_Tmpr_Max30M = -32768;
        ASC_Tmpr_Rate = 0;
        //ASC_Tmpr_RateTh = 0;
        ASC_Tmpr_RateMax30M = 0;
        
        //ASC_Humi_Rt = 0;
        ASC_Humi_Index = 0;
        ASC_Humi_Min = 0;
        ASC_Humi_Max = 0;
        ASC_Humi_Min30M = 32767;
        ASC_Humi_Max30M = -32768;
        ASC_Humi_Rate = 0;
        //ASC_Humi_RateTh = 0;
        ASC_Humi_RateMax30M = 0;
        
        #endif
        
        ASC_Stage = 1;
        ASC_Init_Error = 0;
        
    }
}

#endif

#if((defined(DEBUG_HUMI_RATE_EN))&&(DEBUG_HUMI_RATE_EN==1))
//#define EEPROM_HUMI_RATE_THRE_ADDSTART      208 //0xD0;
//#define DEF_RH_BUFF_LEN       3
uint16_t ExtSens_RH_Rate;
uint16_t ExtSens_RH_Thre;
uint16_t ExtSens_RH_Buff[DEF_RH_BUFF_LEN];
uint8_t ExtSens_RH_BufIdx;
uint8_t Flag_RH_Rate_Exceed;
uint8_t Flag_RH_Rate_En;
uint16_t ExtSens_RH_Total;
uint8_t ExtSens_RH_TolIdx;
uint16_t ExtSens_RH_Max;
uint16_t ExtSens_RH_Min;
#endif



uint16_t Sens_LFL_U16_Cust;
uint16_t ErrorData1_Cust;
uint16_t Psf_Gas_TypeCode_Cust;
int16_t TH_Sensor_Temperature_out_Cust;
uint16_t TH_Sensor_Humidity_out_Cust;




#if(defined(DEF_HEAT_BOARD_EN)&&(DEF_HEAT_BOARD_EN == 1))

//#define EEPROM_HEATBOARD_DUTY_ADDRSTART     210 // 0xD2
//#define EEPROM_HEATBOARD_PROD_ADDRSTART     212 // 0xD4

volatile unsigned char HeatBoard_Flag;
volatile unsigned char HeatBoard_ParamFlag;
unsigned int HeatBoard_Duty;
unsigned int HeatBoard_Period;
unsigned int HeatBoard_Cnt;
unsigned int HeatBoard_PreTime;
#endif

#if(defined(DEF_HPC_FUNC_EN)&&(DEF_HPC_FUNC_EN==1))
uint8_t HPC_Func_En;
int16_t HPC_Tmpr;
uint16_t HPC_Humi;
uint8_t HPC_PreHeat_Flag;
uint8_t HPC_Heat_Flag;
int16_t HPC_HumiRate;
uint16_t HPC_HoldCount;
uint8_t HPC_PWM_Data;

void HPC_InitSetup(unsigned char arg)
{
    HPC_Func_En = arg;
    HPC_Tmpr = 0;
    HPC_Humi = 0;
    HPC_PreHeat_Flag = 0;
    HPC_Heat_Flag = 0;
    HPC_HumiRate = 0;
    HPC_HoldCount = 0;
    HPC_PWM_Data = 0;
    
    HeatBoard_Cool();
    
    HeatBoard_Cnt = 0;
    //HeatBoard_Duty = 0;
    //HeatBoard_Period = 0;
    HeatBoard_Flag = 0;
}

void HPC_MainLoop(void)
{
    if((HPC_Func_En==1)&&(HeatBoard_ParamFlag>0))
    {
        // update HPC_PreHeat_Flag;
        if((HPC_Tmpr<150)&&(HPC_HumiRate>600))
        {
            if(HPC_HoldCount<65535)
            {
                HPC_HoldCount++;
            }
        }
        else
        {
            HPC_PreHeat_Flag = 0;
            HPC_HoldCount = 0;
        }
        
        //if(HPC_HoldCount>10)
        if(HPC_HoldCount>HeatBoard_PreTime)
        {
            HPC_PreHeat_Flag = 1;
        }
        else
        {
            
        }
        
        // Update HPC_Heat_Flag;
        if((HPC_PreHeat_Flag==1)&&(HPC_Humi>500))
        {
            HeatBoard_Cnt = HeatBoard_Period-1;
            
            HPC_Heat_Flag = 1;
            
            HeatBoard_Flag = 1;
        }
        
        // Start and Stop Heatting.
        
        if(HPC_Heat_Flag == 1)
        {
            if(HPC_Humi<=500)
            {
                // HeatBoard_Cnt = 0;
                HPC_Heat_Flag = 0;
                
                HeatBoard_Flag = 0;
            }
            else
            {
                
            }
        }
    }
    else
    {
        
    }
}

#endif

#if(defined(DEF_TMPR_RATE_EN)&&(DEF_TMPR_RATE_EN==1))
int8_t TR_Data_Cnt;
int32_t TR_Tmpr[2];
int32_t TR_Tmpr_Delt;
int32_t TR_Tmpr_Interval;
int32_t TR_Tmpr_Rate;
#endif

#if(defined(DEF_HUMI_RATE_EN)&&(DEF_HUMI_RATE_EN==1))
int8_t HR_Data_Cnt;
int32_t HR_Humi[2];
int32_t HR_Humi_Delt;
int32_t HR_Humi_Interval;
int32_t HR_Humi_Rate;
#endif

#if(defined(DEF_PRES_RATE_EN)&&(DEF_PRES_RATE_EN==1))
int8_t PR_Data_Cnt;
int32_t PR_Pres[2];
int32_t PR_Pres_Delt;
int32_t PR_Pres_Interval;
int32_t PR_Pres_Rate;
#endif

int32_t Usr_DataRate_DltPerMin(int32_t data1,int32_t data2,int32_t *rate)
{   
    int32_t delt = 0;
    int32_t rat = 0;
    
    
    {
        delt = data2-data1;
        rat = delt*60;
    }
    
    *rate = rat;
    
    return rat;
}

#endif



