#ifndef __USR_PSF_C__
#define __USR_PSF_C__


#include <stdint.h>

#include "Usr_Config.h"
#include "Usr_Psf.h"


unsigned char Psf_State;
unsigned char Psf_Current_State;
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


#define DEF_TYPE_BIT    0
#define DEF_TYPE_BOOL   0

#define DEF_TYPE_CHAR   1   //8bit;
#define DEF_TYPE_SCHAR  1   //8bit;
#define DEF_TYPE_UCHAR  2   //16bit;
#define DEF_TYPE_SHORT  3
#define DEF_TYPE_USHORT 4
#define DEF_TYPE_SINT   5
#define DEF_TYPE_UINT   6
#define DEF_TYPE_SLONG  7
#define DEF_TYPE_ULONG  8
#define DEF_TYPE_SLLONG 9
#define DEF_TYPE_ULLONG 10

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
		//case DEF_TYPE_CHAR:
	case DEF_TYPE_SCHAR:
	{	
		byt_nbr = 1;

		bytehigh = *(byt + byt_nbr - 1);

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
	case DEF_TYPE_SHORT:
	{
		byt_nbr = 2;

		bytehigh = *(byt + byt_nbr - 1);

		if ((bytehigh & 0x80) != 0)
		{
			flg_sign = 1;
		}
	}
	break;
	case DEF_TYPE_USHORT:
	{
		flg_sign = 0;
		byt_nbr = 2;
	}
	break;
	case DEF_TYPE_SINT:
	{
		byt_nbr = 2;

		bytehigh = *(byt + byt_nbr - 1);

		if ((bytehigh & 0x80) != 0)
		{
			flg_sign = 1;
		}
	}
	break;
	case DEF_TYPE_UINT:
	{
		byt_nbr = 2;
		flg_sign = 0;
	}
	break;
	case DEF_TYPE_SLONG:
	{	
		byt_nbr = 4;
        
		bytehigh = *(byt + byt_nbr - 1);

		if ((bytehigh & 0x80) != 0)
		{
			flg_sign = 1;
		}
	}
	break;
	case DEF_TYPE_ULONG:
	{
		flg_sign = 0;
		byt_nbr = 4;
	}
	break;
	case DEF_TYPE_SLLONG:
	{	
		byt_nbr = 4;

		bytehigh = *(byt + byt_nbr - 1);

		if ((bytehigh & 0x80) != 0)
		{
			flg_sign = 1;
		}
	}
	break;
	case DEF_TYPE_ULLONG:
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
	break;
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
    uint32_t item3;
    uint32_t tmp_s32;
    uint32_t tmp_A_Item;
    
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
    
    nbr_bit1 = Usr_DataBits(DEF_TYPE_SLONG,(unsigned char*)(&item3));
    nbr_bit2 = Usr_DataBits(DEF_TYPE_SINT,(unsigned char*)(&nbr));
    if(nbr_bit1 + nbr_bit2 >= 32)
    {
        item3 >>= 10;
        nbr_shift += 10;
    }
    nbr_bit1 = Usr_DataBits(DEF_TYPE_SLONG,(unsigned char*)(&item3));
    nbr_bit2 = Usr_DataBits(DEF_TYPE_SINT,(unsigned char*)(&nbr));
    if(nbr_bit1 + nbr_bit2 >= 32)
    {
        item3 >>= 10;
        nbr_shift += 10;
    }
    item3 *= (int16_t)nbr;
    
    nbr_bit1 = Usr_DataBits(DEF_TYPE_SLONG,(unsigned char*)(&item3));
    nbr_bit2 = Usr_DataBits(DEF_TYPE_SINT,(unsigned char*)(&nbr));
    if(nbr_bit1 + nbr_bit2 >= 32)
    {
        item3 >>= 10;
        nbr_shift += 10;
    }
    nbr_bit1 = Usr_DataBits(DEF_TYPE_SLONG,(unsigned char*)(&item3));
    nbr_bit2 = Usr_DataBits(DEF_TYPE_SINT,(unsigned char*)(&nbr));
    if(nbr_bit1 + nbr_bit2 >= 32)
    {
        item3 >>= 10;
        nbr_shift += 10;
    }
    item3 *= (int16_t)nbr;
    
    nbr_bit1 = Usr_DataBits(DEF_TYPE_SLONG,(unsigned char*)(&item3));
    nbr_bit2 = Usr_DataBits(DEF_TYPE_SINT,(unsigned char*)(&nbr));
    if(nbr_bit1 + nbr_bit2 >= 32)
    {
        item3 >>= 10;
        nbr_shift += 10;
    }
    nbr_bit1 = Usr_DataBits(DEF_TYPE_SLONG,(unsigned char*)(&item3));
    nbr_bit2 = Usr_DataBits(DEF_TYPE_SINT,(unsigned char*)(&nbr));
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
    
    if(tmp_A_Item >= 32767)
    {
        *out = 32767;
        return;
    }
    else if (tmp_A_Item <= -32768)
    {
        *out = -32768;
        return;
    }
    
    *out = (unsigned int)tmp_A_Item;
    
    //printf("return,%d,", *out);
    return;
}


#endif



