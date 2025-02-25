#ifndef __USR_PSF_C__
#define __USR_PSF_C__


#include <stdint.h>

#include "Usr_Config.h"
#include "Usr_Psf.h"



unsigned short Psf_Gas_Type;
unsigned short Psf_Gas_TypeCode;
unsigned short Psf_MeasurementFlag;

unsigned char Psf_State;
unsigned char Psf_Next_State;
unsigned int Psf_State_KeepTime;


unsigned char Sens_UpdateFlag;
uint16_t Sens_SRaw;
int16_t Sens_DltSRaw;
uint16_t Sens_SRawComp;

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
uint32_t Table_32Bit[DEF_TABLE_MAX];
uint8_t Sens_TableLen;

uint8_t Flag_Overrange_Ppm;
uint8_t Flag_Overrange_Percentage;
uint32_t PPM_RangeMax;


uint16_t Sens_DC_Y;

uint32_t Sens_CaliData;



float HumComp_M2_S[DEF_HUMCOMP_PARAM_MAX];
uint16_t HumComp_Flag;

uint16_t Flag_HumiCompParameter;



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


void Usr_TComp_Polynomial_Cubic(uint16_t rawt, int16_t *out)
{   
    int32_t item3;
    int32_t tmp_s32;
    int32_t tmp_A_Item;
    
    int16_t nbr;
    
    uint8_t nbr_bit1;
    uint8_t nbr_bit2;
    uint8_t nbr_shift;
    
    uint32_t* ptr_tmp;
    
    
    if((TComp_TRawBase == 0)||(TComp_TRawBase == 0xFFFF))
    {   // if without correct parameters;
        *out = 0;
        
        return;
    }
    else
    {
        nbr = rawt - TComp_TRawBase;
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

uint16_t FilterBuff[DEF_SRAW_FILTERMAX];
uint8_t FilterIndex = 0;
uint32_t FilterTotal = 0;

uint16_t Usr_SRaw_Filter(uint16_t in)
{
    uint8_t i;
    
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
uint8_t Usr_BrokenLine2(uint16_t datain,uint32_t *dataout,uint16_t * Xcoordinates,uint32_t* Ycoordinates,uint8_t nbr)
{   
    uint8_t k;
    
    
    if(dataout == 0 \
        || nbr < 2  \
        )
    {   
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
            *dataout = (long)f32_tmp;
            
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
                
                *dataout = (long)f32_tmp;
                
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

void Usr_CheckRangeMax(void)
{   
    unsigned char cnt;
    
    Flag_Overrange_Ppm = 0;
    Flag_Overrange_Percentage = 0;
    
    for(cnt=0;cnt<DEF_TABLE_MAX;cnt++)
    {
        if(Sens_TableX[cnt] == 0xFFFF)
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


#endif



