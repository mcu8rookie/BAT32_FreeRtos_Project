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
int16_t Sens_DltSRaw;
int16_t Sens_SRawComp;

uint16_t ErrorData0;
uint16_t ErrorData1;
uint16_t ErrorData2;



uint16_t Sens_DC_Y;

int32_t Sens_CaliData;

int16_t Sens_Raw_After_Mems;
int16_t Sens_Raw_After_Filter;
int16_t Sens_Raw_After_TmpComp;
int16_t Sens_Raw_After_HtComp;
int16_t Sens_Raw_After_DltRaw;
int16_t Sens_Raw_After_All;


uint16_t Sens_PPM_After_Cali;
uint16_t Sens_PPM_After_HumComp;
uint16_t Sens_PPM_After_PrsComp;
uint16_t Sens_PPM_After_PrsComp2;
uint16_t Sens_PPM_After_DCY;
uint16_t Sens_PPM_After_TmRtComp;
uint16_t Sens_PPM_After_ASC;
uint16_t Sens_PPM_After_All;
int32_t     Sens_PPM_After_All_I32;

double Sens_LFL_dbl;
uint16_t Sens_LFL_U16;


int32_t Sens_PPM;
int32_t Sens_PPM_Dbl;

#if(defined(DEF_CONCEN_THRE_EN)&&(DEF_CONCEN_THRE_EN==1))
uint16_t Concen_Threshold;
uint8_t Flag_Concen_Threshol_Alarm;
uint8_t Flag_Concen_Threshold_En;
uint16_t Donot_Alarm_5s;
uint16_t Concentration_Alarm_HoldTime;
#endif

uint16_t Tmpr_TRaw;

int16_t Tmpr_DltTRaw;

uint16_t TComp_TRawBase;
int32_t TComp_P0;
int32_t TComp_P1;
int32_t TComp_P2;
int32_t TComp_P3;

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

double HumComp_Tmp0;
double HumComp_Tmp1;
double HumComp_Tmp2;

uint16_t Flag_HumiCompParameter;
uint16_t Flag_HumiCompParameter2;


double Usr_HumComp_K;
double Usr_HumComp_PPMC;
int16_t Usr_HumComp_PPMC_INT;


int16_t Usr_Delta_Raw;
int16_t Usr_Delta_PPM1;



#if(defined(DEF_HUMCOMP_EN)&&(DEF_HUMCOMP_EN==1))

double Usr_HumComp_Calc_K1(double temp)
{   
    if((Flag_HumiCompParameter == 0)||(HumComp_Flag == 0))
    {
        return 0.0;
    }
    
    
    HumComp_Tmp0 = HumComp_M2_S[0];
    
    HumComp_Tmp1 = HumComp_M2_S[1]*temp;
    HumComp_Tmp0 += HumComp_Tmp1;
    
    HumComp_Tmp1 = temp*temp;
    HumComp_Tmp1 *= HumComp_M2_S[2];
    HumComp_Tmp0 += HumComp_Tmp1;
    
    HumComp_Tmp1 = temp*temp;
    HumComp_Tmp1 *= temp;
    HumComp_Tmp1 *= HumComp_M2_S[3];
    HumComp_Tmp0 += HumComp_Tmp1;
    
    return HumComp_Tmp0;
}

#endif


double Usr_HumComp_Calc_D(short T, unsigned short RH)
{
    double deltaPPM = 0.0;
    unsigned long *pTemp = (unsigned long*)&HumComp_M2_S[4];
    
    if((Flag_HumiCompParameter2 == 0)||(HumComp_Flag == 0))
    {   
        return 0.0;
    }
    
    //if((T > 750) && (RH <= 127))
    if(T > 800)
    {
        // if(((pTemp[0] != 0xFFFFFFFF)||(pTemp[0] != 0x00)) && ((pTemp[1] != 0xFFFFFFFF)||(pTemp[1] != 0x00)))
        {
            // deltaPPM = -297.34*ExtSens_Tmpr+18382;
            deltaPPM = T;
            deltaPPM *= HumComp_M2_S[5];
            deltaPPM /= 10;
            deltaPPM += HumComp_M2_S[4];
        }
    }
    
    return deltaPPM;
}



#if(defined(DEF_PRESCOMP_EN)&&(DEF_PRESCOMP_EN == 1))

uint16_t PresComp_PBase;

float PresComp_K[DEF_PRESCOMP_PARAM_MAX];

uint16_t PresComp_Flag;

uint16_t Flag_PresCompParameter;

float delta_ppm_pressure;
int16_t dlt_ppm_pressure_int;

float tmp0 = 0;
float tmp1 = 0;
float tmp2 = 0;
float tmp3 = 0;
float tmp4 = 0;

float out;

unsigned char Delta_Pressure_Compensation(double prsu)
{   
    if((PresComp_Flag == 0)||(Flag_PresCompParameter == 0)||(PresComp_PBase == 0)||(PresComp_PBase == 0xFFFF))
    {   
        delta_ppm_pressure = 0;
        
        return 0;
    }
    else
    {   
        tmp0 = prsu;                // Real pressure; Unit: 1Pa;
        
        tmp1 = tmp0/10;             // Real pressure; Unit: 10Pa;
        
        tmp2 = tmp1 - PresComp_PBase;   // Delta pressure; Unit: 10Pa;
        
        tmp0 = tmp2/10000.0;            // Delta pressure; Unit: 100000Pa = 1Bar;
        
        // tmp0 = tmp2*10;                 // Delta pressure; Unit: 1Pa;
        
        tmp1 = PresComp_K[0];           // 
        
        tmp2 = PresComp_K[1]*tmp0;
        
        tmp1 += tmp2;
        
        tmp2 = tmp0*tmp0;
        
        tmp2 *= PresComp_K[2];
        
        tmp1 += tmp2;
        
        delta_ppm_pressure = tmp1;
    }
    
    return 1;
}

#endif

#if(defined(DEF_TEMPRATE_EN)&&(DEF_TEMPRATE_EN == 1))

int16_t TmpRate_P;

double Usr_TmpRate_Comp(double arg)
{   
    //s32 tmp_s32;
    
    if((TmpRate_P == 0)||((uint16_t)TmpRate_P == 65535))
    {   
        return arg;
    }
    else
    {   
        //tmp1 = (signed int)Sensor1_TableX[14];
        //tmp2 = Delta_Tmp_Raw;
        
        tmp1 = TmpRate_P;
        tmp2 = (float)Tmpr_DltTRaw;
        
        tmp3 = tmp1*tmp2;
        tmp3 = tmp3/1048576;
        tmp3 = 1+ tmp3;
        tmp4 = arg/tmp3;
        
        return tmp4;
    }
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

unsigned char IsHumidityLargerThanDewRH(double T)
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

unsigned char Usr_DataBits(unsigned char typ, unsigned char* byt)
{
    unsigned char flg_sign;
    unsigned char byt_nbr;
    unsigned char bit_nbr;
    
    unsigned char idx1, idx2;
    
    unsigned char temp1;
    
    unsigned char bytehigh;
    
    flg_sign = 0;
    
    switch (typ)
    {
        case DEF_TYPE_SCHAR:
        {   
            byt_nbr = 1;
            
            bytehigh =  *(byt + byt_nbr - 1);
            
            if ((bytehigh & 0x80) != 0)
            {
                flg_sign = 1;
            }
        }
        break;
        case DEF_TYPE_UCHAR:
        {
            byt_nbr = 1;
            flg_sign = 0;
        }
        break;
        case DEF_TYPE_SINT16:
        {
            byt_nbr = 2;
            
            bytehigh = *(byt + byt_nbr - 1);
            
            if ((bytehigh & 0x80) != 0)
            {
                flg_sign = 1;
            }
        }
        break;
        case DEF_TYPE_UINT16:
        {
            flg_sign = 0;
            byt_nbr = 2;
        }
        break;
        case DEF_TYPE_SINT32:
        {
            byt_nbr = 4;
            
            bytehigh = *(byt + byt_nbr - 1);
            
            if ((bytehigh & 0x80) != 0)
            {
                flg_sign = 1;
            }
        }
        break;
        case DEF_TYPE_UINT32:
	{
		flg_sign = 0;
		byt_nbr = 4;
	}
	break;
	default:
	{
		flg_sign = 0;
		byt_nbr = 0;
		bit_nbr = 0;

		return bit_nbr;
	}
	//break;
	}

	bit_nbr = 0;

	if (flg_sign == 0)
	{
		for (idx1 = 0;idx1 < byt_nbr;idx1++)
		{
			for (idx2 = 0;idx2 < 8;idx2++)
			{
				if (((*(unsigned char*)(byt + byt_nbr - idx1 - 1)) & (0x80 >> idx2)) == 0x00)
				{

				}
				else
				{
					goto Calcu;
				}
			}
		}
	}
	else
	{
		for (idx1 = 0;idx1 < byt_nbr;idx1++)
		{
			for (idx2 = 0;idx2 < 8;idx2++)
			{
				if (((*(unsigned char*)(byt + byt_nbr - idx1 - 1)) & (0x80 >> idx2)) != 0x00)
				{

				}
				else
				{
					goto Calcu;
				}
			}
		}
	}

Calcu:
	bit_nbr = byt_nbr * 8;
	temp1 = idx1 * 8;
	bit_nbr -= temp1;
	if (idx2 < 8)
	{
		bit_nbr -= idx2;
	}

	//return bit_nbr;
	return bit_nbr + flg_sign;
}


void Usr_TComp_Polynomial_Cubic(int16_t nbr, int16_t *out)
{   
    int32_t item3;
    int32_t tmp_s32;
    int32_t tmp_A_Item;
    
    uint8_t nbr_bit1;
    uint8_t nbr_bit2;
    uint8_t nbr_shift;
    
    
    if((TComp_TRawBase == 0)||(TComp_TRawBase==0xFFFF))
    {   // if without correct parameters;
        *out = 0;
        
        return;
    }
    
    //printf("nbr,%d,", nbr);
    
    nbr_shift = 0;
    
    item3 = TComp_P3;
    
    nbr_bit1 = Usr_DataBits(DEF_TYPE_SINT32,(unsigned char*)(&item3));
    nbr_bit2 = Usr_DataBits(DEF_TYPE_SINT16,(unsigned char*)(&nbr));
    if(nbr_bit1 + nbr_bit2 >= 32)
    {
        item3 >>= 10;
        nbr_shift += 10;
    }
    nbr_bit1 = Usr_DataBits(DEF_TYPE_SINT32,(unsigned char*)(&item3));
    nbr_bit2 = Usr_DataBits(DEF_TYPE_SINT16,(unsigned char*)(&nbr));
    if(nbr_bit1 + nbr_bit2 >= 32)
    {
        item3 >>= 10;
        nbr_shift += 10;
    }
    item3 *= (int16_t)nbr;
    
    nbr_bit1 = Usr_DataBits(DEF_TYPE_SINT32,(unsigned char*)(&item3));
    nbr_bit2 = Usr_DataBits(DEF_TYPE_SINT16,(unsigned char*)(&nbr));
    if(nbr_bit1 + nbr_bit2 >= 32)
    {
        item3 >>= 10;
        nbr_shift += 10;
    }
    nbr_bit1 = Usr_DataBits(DEF_TYPE_SINT32,(unsigned char*)(&item3));
    nbr_bit2 = Usr_DataBits(DEF_TYPE_SINT16,(unsigned char*)(&nbr));
    if(nbr_bit1 + nbr_bit2 >= 32)
    {
        item3 >>= 10;
        nbr_shift += 10;
    }
    item3 *= (int16_t)nbr;
    
    nbr_bit1 = Usr_DataBits(DEF_TYPE_SINT32,(unsigned char*)(&item3));
    nbr_bit2 = Usr_DataBits(DEF_TYPE_SINT16,(unsigned char*)(&nbr));
    if(nbr_bit1 + nbr_bit2 >= 32)
    {
        item3 >>= 10;
        nbr_shift += 10;
    }
    nbr_bit1 = Usr_DataBits(DEF_TYPE_SINT32,(unsigned char*)(&item3));
    nbr_bit2 = Usr_DataBits(DEF_TYPE_SINT16,(unsigned char*)(&nbr));
    if(nbr_bit1 + nbr_bit2 >= 32)
    {
        item3 >>= 10;
        nbr_shift += 10;
    }
    item3 *= (int16_t)nbr;
    
    item3 >>= (30-nbr_shift);
    
    //printf("item3,%d,", item3);
    
    //tmp_A_Item = *(s32*)(Sensor1_TableX+12);
    tmp_A_Item = TComp_P2;
    tmp_A_Item *= (int16_t)nbr;
    tmp_A_Item >>= 10;
    tmp_A_Item *= (int16_t)nbr;
    tmp_A_Item >>= 10;
    
    //printf("item2,%d,", tmp_A_Item);
    
    //tmp_s32 = (s16)Sensor1_TableY[12];
    tmp_s32 = TComp_P1;
    tmp_s32 *= (int16_t)nbr;
    tmp_s32 >>= 10;
    
    //printf("item1,%d,", tmp_s32);
    
    tmp_A_Item += item3;
    
    tmp_A_Item += tmp_s32;
    
    //tmp_s32 = (s16)Sensor1_TableY[13];
    tmp_s32 = TComp_P0;
    
    //printf("item0,%d,", tmp_s32);
    
    tmp_A_Item += tmp_s32;
    
    
    //printf("Poly,%d,", tmp_A_Item);
    
    if(tmp_A_Item >= (int32_t)32767)
    {
        *out = 32767;
        return;
    }
    else if (tmp_A_Item <= (-32768))
    {
        *out = -32768;
        return;
    }
    
    *out = (unsigned int)tmp_A_Item;
    
    //printf("return,%d,", *out);
    return;
}


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



double f32_tmp;


//u8 Usr_BrokenLine2(u16 datain,long*dataout,u16* Xcoordinates,volatile unsigned long* Ycoordinates,u8 nbr)
uint8_t Usr_BrokenLine2(int16_t datain,int32_t *dataout,int16_t * Xcoordinates,uint32_t* Ycoordinates,uint8_t nbr)
{   
    uint8_t k;
    
    
    if(dataout == 0)
    {   
        return 1;
    }
    else if(nbr < 2)
    {   
        *dataout = 0;
        return 1;
    }   
    else
    {   
        #if 1   
        if((datain<Xcoordinates[0])&&(Xcoordinates[0]<Xcoordinates[1]))
        {
            //double f32_tmp = 0;
            
            f32_tmp = ((double)datain - (double)Xcoordinates[0])*((double)Ycoordinates[1] - (double)Ycoordinates[0]);
            f32_tmp = f32_tmp/((double)Xcoordinates[1] - (double)Xcoordinates[0]);
            f32_tmp = Ycoordinates[0] + f32_tmp;
            *dataout = (int32_t)f32_tmp;
            
            return 0;
        }
        #endif
        
        for(k=0; k<nbr-1; k++)
        {   
            if(Xcoordinates[k] >= Xcoordinates[k+1])
            {
                *dataout = Ycoordinates[k];
                
                return 3;
            }
            else if(datain <= Xcoordinates[k])
            {
                *dataout =  Ycoordinates[k];
                
                return 0;
            }
            else if(datain > Xcoordinates[k] && datain <= Xcoordinates[k+1])
            {   
                //double f32_tmp = 0;
                
                #if 1   
                
                f32_tmp = ((double)datain - (double)(Xcoordinates[k]))*((double)(Ycoordinates[k+1]) - (double)(Ycoordinates[k]));
                
                f32_tmp = f32_tmp/((double)(Xcoordinates[k+1]) - (double)(Xcoordinates[k]));
                
                f32_tmp = (double)(Ycoordinates[k]) + f32_tmp;
                
                *dataout = (int32_t)f32_tmp;
                
                #endif
                
                return 0;
            }
            else if(k >= nbr-2)
            {
                *dataout = Ycoordinates[nbr-1];
                
                return 0;
            }
        }
    }
    // never run here;
    
    return 4;
}

#if((defined(DEF_OVERRANGE_ALARM_EN))&&(DEF_OVERRANGE_ALARM_EN == 1))

#define DEF_TBL_Y_IDLE      (0xFFFF)
//#define DEF_TBL_Y_IDLE      (0x7FFF)

uint8_t Flag_Overrange_Ppm;
//uint8_t Flag_Overrange_Percentage;
int32_t PPM_RangeMax;

void Usr_CheckRangeMax(void)
{   
    unsigned char cnt;
    
    Flag_Overrange_Ppm = 0;
    //Flag_Overrange_Percentage = 0;
    
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
unsigned char FP32_IsNumerical(unsigned char *ptr)
{   
    unsigned char u8_tmp;
    
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

uint8_t SelfMoni2_LeakSignal_Rt;

uint16_t SelfMoni2_Leakage_Flag;

int32_t ASC_PPM_Total;
int32_t  ASC_PPM_Cnt;
int32_t  ASC_PPM_Average;


#if(defined(DEF_ASC_EN)&&(DEF_ASC_EN==1))

uint16_t ASC_Func_En;

uint16_t ASC_PPM_HighTh;
uint16_t ASC_PPM_LowTh;

uint16_t ASC_Adjust_Cnt;

int16_t ASC_Adjust_Value[DEF_ASC_ADJUST_VALUE_MAX];
int16_t ASC_Adjust_Total;

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
int16_t ASC_Humi_Thre;

#endif


void Usr_ASC_MainLoop(void)
{   
    unsigned char loc_cnt;
    
    unsigned char loc_cnt2;
    
    int32_t int32_tmp;
    
    
    if(ASC_Func_En == 1)
    {   // if self-monitoring function is enable; 
        
        ASC_TimeCnt++;
        
        //if(Flag_LeakSignal == 1)
        //if(SelfMoni2_LeakSignal_Rt == 1)
        //if(Flag_Concen_Threshol_Alarm == 1)
        if(SelfMoni2_LeakSignal_Rt == 1)
        {   
            SelfMoni2_Leakage_Flag = 1;
        }
        
        
        #if(defined(DEF_ASC_EN)&&(DEF_ASC_EN==1))
        
        #if 1
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
            
            if(ASC_Tmpr_Min<ASC_Tmpr_Min30M)
            {
                ASC_Tmpr_Min30M = ASC_Tmpr_Min;
            }
            
            if(ASC_Tmpr_Max>ASC_Tmpr_Min30M)
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
            
            if(ASC_Humi_Min<ASC_Humi_Min30M)
            {
                ASC_Humi_Min30M = ASC_Humi_Min;
            }
            
            if(ASC_Humi_Max>ASC_Humi_Min30M)
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
        
        #endif
        
        // if(ASC_PPM_Total<4294901760UL)
        if(ASC_PPM_Total<2147418112)
        {
            ASC_PPM_Total += Sens_PPM_After_All_I32;
            ASC_PPM_Cnt++;
        }
        
        //if(ASC_TimeCnt>=3600)   // 1hour;
        //if(ASC_TimeCnt>=1800)   // 0.5hour;   //
        //if(ASC_TimeCnt>=900)    // 15min;
        //if(ASC_TimeCnt>=600)    // 10minute;
        if(ASC_TimeCnt>=300)    // 5minute;
        //if(ASC_TimeCnt>=180)    // 3minute;
        {   // if add data keep 1 hour timeout;
            
            //if(SelfMoni2_Leakage_Flag == 0)
            if((SelfMoni2_Leakage_Flag == 0)\
                &&((ASC_Tmpr_Min30M>=150)&&(ASC_Tmpr_Max30M<=350)&&(ASC_Tmpr_RateMax30M<ASC_Tmpr_RateTh))\
                &&((ASC_Humi_Min30M>=300)&&(ASC_Humi_Max30M<=700)&&(ASC_Humi_RateMax30M<ASC_Humi_RateTh)))
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
                    // if all data > limit or all data < limit;
                    int32_tmp = ASC_PPM_HighTh; 
                    
                    for(loc_cnt=0;loc_cnt<ASC_ARRAYLEN;loc_cnt++)
                    {
                        if(ASC_Average_Array[loc_cnt]>int32_tmp)
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
                            #if 1
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
                        
                        #if 1
                        if((ASC_Func_En==1)&&(ASC_Adjust_Cnt>0)&&(ASC_Adjust_Cnt<=3))
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
                    }
                    else
                    {
                        
                    }
                    
                    if(loc_cnt<ASC_ARRAYLEN)
                    {
                        int32_tmp = (int16_t)(0-ASC_PPM_HighTh); 
                        
                        for(loc_cnt=0;loc_cnt<ASC_ARRAYLEN;loc_cnt++)
                        {
                            if(ASC_Average_Array[loc_cnt]<int32_tmp)
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
                                #if 1
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
                            
                            
                            #if 1
                            if((ASC_Func_En==1)&&(ASC_Adjust_Cnt>0)&&(ASC_Adjust_Cnt<=3))
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
                        }
                        
                    }
                    else
                    {
                        
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
            }
            
            SelfMoni2_Leakage_Flag = 0;
            
            //ASC_Tmpr_Index = 0;
            ASC_Tmpr_Min30M = 32767;
            ASC_Tmpr_Max30M = -32768;
            ASC_Tmpr_RateMax30M = 0;
            
            //ASC_Humi_Index = 0;
            ASC_Humi_Min30M = 32767;
            ASC_Humi_Max30M = -32768;
            ASC_Humi_RateMax30M = 0;
            
            ASC_TimeCnt = 0;
            ASC_PPM_Total = 0;
            ASC_PPM_Cnt = 0;
            
            ASC_Adjust_Cnt = 0;
            
        }
    }
    else
    {
        
        ASC_Average_Index = 0;
        SelfMoni2_Leakage_Flag = 0;
        ASC_TimeCnt = 0;
        ASC_PPM_Total = 0;
        ASC_PPM_Cnt = 0;
        
        #if(defined(DEF_ASC_EN)&&(DEF_ASC_EN==1))
        
        ASC_Tmpr_Rt = 0;
        ASC_Tmpr_Index = 0;
        ASC_Tmpr_Min = 0;
        ASC_Tmpr_Max = 0;
        ASC_Tmpr_Min30M = 0;
        ASC_Tmpr_Max30M = 0;
        ASC_Tmpr_Rate = 0;
        ASC_Tmpr_RateTh = 0;
        ASC_Tmpr_RateMax30M = 0;
        
        ASC_Humi_Rt = 0;
        ASC_Humi_Index = 0;
        ASC_Humi_Min = 0;
        ASC_Humi_Max = 0;
        ASC_Humi_Min30M = 0;
        ASC_Humi_Max30M = 0;
        ASC_Humi_Rate = 0;
        ASC_Humi_RateTh = 0;
        ASC_Humi_RateMax30M = 0;
        
        #endif
        
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





#endif



