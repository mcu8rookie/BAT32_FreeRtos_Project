#ifndef __USR_ALSENSOR_C__
#define __USR_ALSENSOR_C__


//#include "Usr_Config.h"

//#include "Usr_Code.h"

//#include"Usr_IIC_Soft.h"

#include "Usr_ALSensor.h"

#include"Usr_Uart.h"

//#include"Usr_Algorithm.h"

#include "Usr_HDC2010.h"

#include "Usr_HDC3020.h"

#include"Usr_Config.h"
#include"Usr_Soft_I2C.h"


short TH_Sensor_Temperature_out;

unsigned short TH_Sensor_Humidity_out;



unsigned char TH_RdBuf[6];

volatile unsigned int TH_DelayMs;

unsigned char ALSensor_TH_Stage;
volatile unsigned int ALSensor_TH_HoleTime;
unsigned char ALSensor_TH_RepeatCnt;


unsigned int ALSensor_TH_VID;
unsigned int ALSensor_TH_PID;

long th_sensor_tmp;

unsigned char Flag_TH_Err_Comm;
unsigned char Flag_TH_Err_TRange;
unsigned char Flag_TH_Err_HRange;

double ExtSens_Tmpr;
double ExtSens_RH;

double ExtSens_Prs;
double ExtSens_Tmpr2;

unsigned int ExtSens_RH0D1P_U16;

unsigned int ExtSens_Tmpr_Raw;
unsigned int ExtSens_RH_Raw;

unsigned char ALSensor_TH_MainLoop(void)
{   
    
    unsigned char rtncode = 0;
    unsigned char errcode = 0;
    
    switch(ALSensor_TH_Stage)
    {    
        case ALSENSOR_STAGE_UNINIT:
        {    
            if(ALSensor_TH_HoleTime == 0)
            {    
                //Usr_Soft_IIC_Init(3);   // TH sensor I2C bus; for HDC2010 and HDC3020;
                Usr_Soft_IIC_Init(I2C_CHANNEL_HDC3020);
                ALSensor_TH_Stage = ALSENSOR_STAGE_KNOCK;
                
                ALSensor_TH_HoleTime = 5;
                
                ALSensor_TH_VID = 0;
                ALSensor_TH_PID = 0;
                
                #if 1
                Flag_TH_Err_Comm = 0;
                Flag_TH_Err_TRange = 0;
                Flag_TH_Err_HRange = 0;
                #endif
            }
            
        }
        break;
        case ALSENSOR_STAGE_KNOCK:
        {    
            if(ALSensor_TH_HoleTime == 0)
            {
                
                #if((defined(SENSOR_HT_TYPE))&&(SENSOR_HT_TYPE == SENSOR_TYPE_HDC2010))
                
                HDC2010_ReadID(TH_RdBuf);
                
                ALSensor_TH_VID = TH_RdBuf[1];
                ALSensor_TH_VID <<= 8;
                ALSensor_TH_VID += TH_RdBuf[0];
                
                ALSensor_TH_PID = TH_RdBuf[3];
                ALSensor_TH_PID <<= 8;
                ALSensor_TH_PID += TH_RdBuf[2];
                
                #endif
                
                
                #if((defined(SENSOR_HT_TYPE))&&(SENSOR_HT_TYPE == SENSOR_TYPE_HDC3020))
                
                HDC3020_ReadID(TH_RdBuf);
                
                ALSensor_TH_VID = TH_RdBuf[0];
                ALSensor_TH_VID <<= 8;
                ALSensor_TH_VID += TH_RdBuf[1];
                
                ALSensor_TH_PID = DEF_HT_PID;
                
                #endif
                
                
                if((ALSensor_TH_VID == DEF_HT_VID)&&(ALSensor_TH_PID == DEF_HT_PID))  
                {
                    #if((defined(SENSOR_HT_TYPE))&&(SENSOR_HT_TYPE == SENSOR_TYPE_HDC2010))
                    ALSensor_TH_Stage = ALSENSOR_STAGE_INIT;
                    #endif
                    
                    #if((defined(SENSOR_HT_TYPE))&&(SENSOR_HT_TYPE == SENSOR_TYPE_HDC3020))
                    ALSensor_TH_Stage = ALSENSOR_STAGE_WAIT1;
                    #endif
                    
                    ALSensor_TH_HoleTime = 5;
                    ALSensor_TH_RepeatCnt = 0;
                    
                    Flag_TH_Err_Comm = 0;
                }
                else
                {    
                    ALSensor_TH_Stage = ALSENSOR_STAGE_UNINIT;
                    ALSensor_TH_HoleTime = 10;
                    ALSensor_TH_RepeatCnt++;
                    
                    if(ALSensor_TH_RepeatCnt > 32)
                    {
                        ALSensor_TH_HoleTime = 1000;
                        ALSensor_TH_RepeatCnt = 0;
                    }
                    
                    Flag_TH_Err_Comm = 1;
                }
                
            }
        }
        break;
        #if((defined(SENSOR_HT_TYPE))&&(SENSOR_HT_TYPE == SENSOR_TYPE_HDC2010))
        case ALSENSOR_STAGE_INIT:
        {    
            if(ALSensor_TH_HoleTime == 0)
            {    
                rtncode = HDC2010_InitSetup();
                
                if(0 == rtncode)
                {    
                    //rtncode = HDC2010_ConvertStart();
                    
                    rtncode = HDC2010_ConvertStop();
                    
                    if(0 == rtncode)
                    {
                        
                    }
                    else
                    {
                        errcode += 1;
                    }
                }
                else
                {
                    errcode += 1;
                }
                
                if(errcode == 0)
                {
                    ALSensor_TH_Stage = ALSENSOR_STAGE_WAIT1;
                    ALSensor_TH_HoleTime = 5;
                    ALSensor_TH_RepeatCnt = 0;
                    
                    Flag_TH_Err_Comm = 0;
                }
                else
                {
                    ALSensor_TH_HoleTime = 10;
                    ALSensor_TH_RepeatCnt ++;
                    
                    if(ALSensor_TH_RepeatCnt > 32)
                    {
                        ALSensor_TH_Stage = ALSENSOR_STAGE_UNINIT;
                        
                        ALSensor_TH_RepeatCnt = 0;
                    }
                    
                    Flag_TH_Err_Comm = 1;
                }
            }
        }
        break;
        #endif
        case ALSENSOR_STAGE_WAIT1:
        {
            if(ALSensor_TH_HoleTime == 0)
            {
                #if((defined(SENSOR_HT_TYPE))&&(SENSOR_HT_TYPE == SENSOR_TYPE_HDC2010))
                rtncode = HDC2010_ConvertStart();
                #endif
                
                #if((defined(SENSOR_HT_TYPE))&&(SENSOR_HT_TYPE == SENSOR_TYPE_HDC3020))
                rtncode = HDC3020_ConvertStart();
                #endif
                
                if(rtncode == 0)
                {
                    ALSensor_TH_Stage = ALSENSOR_STAGE_GETDATA;
                    //ALSensor_TH_HoleTime = 5;
                    ALSensor_TH_HoleTime = 10;
                    ALSensor_TH_RepeatCnt = 0;
                    
                    Flag_TH_Err_Comm = 0;
                }
                else
                {
                    ALSensor_TH_HoleTime = 10;
                    ALSensor_TH_RepeatCnt ++;
                    
                    if(ALSensor_TH_RepeatCnt > 32)
                    {
                        #if((defined(SENSOR_HT_TYPE))&&(SENSOR_HT_TYPE == SENSOR_TYPE_HDC2010))
                        ALSensor_TH_Stage = ALSENSOR_STAGE_INIT;
                        #endif
                        
                        #if((defined(SENSOR_HT_TYPE))&&(SENSOR_HT_TYPE == SENSOR_TYPE_HDC3020))
                        ALSensor_TH_Stage = ALSENSOR_STAGE_KNOCK;
                        #endif
                        
                        ALSensor_TH_RepeatCnt = 0;
                    }
                    
                    Flag_TH_Err_Comm = 1;
                }
            }
        }
        break;
        case ALSENSOR_STAGE_GETDATA:
        {
            if(ALSensor_TH_HoleTime == 0)
            {
                #if((defined(SENSOR_HT_TYPE))&&(SENSOR_HT_TYPE == SENSOR_TYPE_HDC2010))
                rtncode =  HDC2010_ReadHT(TH_RdBuf);
                
                if(rtncode == 0)
                {   
                    double dbl_tmp1 = 0;
                    
                    th_sensor_tmp = 0;
                    th_sensor_tmp = TH_RdBuf[1];
                    th_sensor_tmp <<= 8;
                    th_sensor_tmp += TH_RdBuf[0];
                    
                    ExtSens_Tmpr_Raw = th_sensor_tmp;
                    
                    dbl_tmp1 = (double)th_sensor_tmp;
                    dbl_tmp1 *= 165.0;
                    dbl_tmp1 /= 65535.0;
                    dbl_tmp1 -= 40.0;       // 1.0 degree centigrade;
                    
                    dbl_tmp1 *= 10.0;       // 0.1 degree centigrade;
                    
                    if(dbl_tmp1<(-400))
                    {
                        //dbl_tmp1 = -400;
                        Flag_TH_Err_TRange = 1;
                    }
                    else if(dbl_tmp1>850)
                    {
                        //dbl_tmp1 = 850;
                        Flag_TH_Err_TRange = 1;
                    }
                    else
                    {
                        Flag_TH_Err_TRange = 0;
                    }
                    
                    TH_Sensor_Temperature_out = (unsigned int)dbl_tmp1;
                    
                    ExtSens_Tmpr = dbl_tmp1/10.0f;
                    
                    th_sensor_tmp = 0;
                    th_sensor_tmp = TH_RdBuf[3];
                    th_sensor_tmp <<= 8;
                    th_sensor_tmp += TH_RdBuf[2];
                    
                    ExtSens_RH_Raw = th_sensor_tmp;
                    
                    dbl_tmp1 = (double)th_sensor_tmp;
                    dbl_tmp1 *= 1000;
                    dbl_tmp1 /= 65535.0;
                    
                    if(dbl_tmp1<0)
                    {
                        dbl_tmp1 = 0;
                        Flag_TH_Err_HRange = 1;
                    }
                    else if(dbl_tmp1>1000)
                    {
                        dbl_tmp1 = 1000;
                        Flag_TH_Err_HRange = 1;
                    }
                    else
                    {
                        Flag_TH_Err_HRange = 0;
                    }
                    
                    TH_Sensor_Humidity_out = (unsigned int)dbl_tmp1;
                    
                    ExtSens_RH = dbl_tmp1/1000.0f;
                    
                    ExtSens_RH0D1P_U16 = dbl_tmp1;
                    
                    ALSensor_TH_Stage = ALSENSOR_STAGE_WAIT2;
                    
                    ALSensor_TH_HoleTime = 190;
                    
                    ALSensor_TH_RepeatCnt = 0;
                    
                    Flag_TH_Err_Comm = 0;
                    
                    
                    
                    #if((defined(DEBUG_HUMI_RATE_EN))&&(DEBUG_HUMI_RATE_EN==1))
                    {
                        int i;
                        
                        
                        //Filter and obtain one RH data;
                        ExtSens_RH_Total += ExtSens_RH0D1P_U16;
                        ExtSens_RH_TolIdx++;
                        
                        if(ExtSens_RH_TolIdx>=5)
                        {
                            for(i=(DEF_RH_BUFF_LEN-2);i>(-1);i--)
                            {
                                ExtSens_RH_Buff[i+1] = ExtSens_RH_Buff[i];
                            }
                            ExtSens_RH_Buff[0] = ExtSens_RH_Total/ExtSens_RH_TolIdx;
                            
                            if(ExtSens_RH_BufIdx<DEF_RH_BUFF_LEN)
                            {
                                ExtSens_RH_BufIdx ++;
                                
                                ExtSens_RH_Max = 0;
                                ExtSens_RH_Min = 0xFFFF;
                            }
                            
                            ExtSens_RH_TolIdx = 0;
                            ExtSens_RH_Total = 0;
                            
                            if(ExtSens_RH_BufIdx>=DEF_RH_BUFF_LEN)
                            {
                                for(i=0;i<DEF_RH_BUFF_LEN;i++)
                                {
                                    if(ExtSens_RH_Max<ExtSens_RH_Buff[i])
                                    {
                                        ExtSens_RH_Max = ExtSens_RH_Buff[i];
                                    }
                                    if(ExtSens_RH_Min>ExtSens_RH_Buff[i])
                                    {
                                        ExtSens_RH_Min = ExtSens_RH_Buff[i];
                                    }
                                }
                                
                                ExtSens_RH_Rate = ExtSens_RH_Max-ExtSens_RH_Min;
                                
                                if((Flag_RH_Rate_En == 1)&&(ExtSens_RH_Rate > ExtSens_RH_Thre))
                                {
                                    Flag_RH_Rate_Exceed = 1;
                                }
                                else
                                {
                                    Flag_RH_Rate_Exceed = 0;
                                }
                            }
                            
                        }
                    }
                    #endif
                    
                }
                #endif
                
                #if((defined(SENSOR_HT_TYPE))&&(SENSOR_HT_TYPE == SENSOR_TYPE_HDC3020))
                
                rtncode =  HDC3020_ReadTH(TH_RdBuf);
                
                if(rtncode == 0)
                {   
                    double dbl_tmp1 = 0;
                    
                    th_sensor_tmp = 0;
                    th_sensor_tmp = TH_RdBuf[0];
                    th_sensor_tmp <<= 8;
                    th_sensor_tmp += TH_RdBuf[1];
                    
                    dbl_tmp1 = (double)th_sensor_tmp;
                    dbl_tmp1 *= 175.0;
                    dbl_tmp1 /= 65535.0;
                    dbl_tmp1 -= 45.0;       // 1.0 degree centigrade;
                    
                    dbl_tmp1 *= 10.0;       // 0.1 degree centigrade;
                    
                    if(dbl_tmp1<(-400))
                    {
                        //dbl_tmp1 = -400;
                        Flag_TH_Err_TRange = 1;
                    }
                    else if(dbl_tmp1>1250)
                    {
                        //dbl_tmp1 = 850;
                        Flag_TH_Err_TRange = 1;
                    }
                    else
                    {
                        Flag_TH_Err_TRange = 0;
                    }
                    
                    TH_Sensor_Temperature_out = (unsigned int)dbl_tmp1;
                    
                    ExtSens_Tmpr = dbl_tmp1/10.0f;
                    
                    th_sensor_tmp = 0;
                    th_sensor_tmp = TH_RdBuf[3];
                    th_sensor_tmp <<= 8;
                    th_sensor_tmp += TH_RdBuf[4];
                    
                    dbl_tmp1 = (double)th_sensor_tmp;
                    dbl_tmp1 *= 1000;
                    dbl_tmp1 /= 65535.0;
                    
                    if(dbl_tmp1<0)
                    {
                        dbl_tmp1 = 0;
                        Flag_TH_Err_HRange = 1;
                    }
                    else if(dbl_tmp1>1000)
                    {
                        dbl_tmp1 = 1000;
                        Flag_TH_Err_HRange = 1;
                    }
                    else
                    {
                        Flag_TH_Err_HRange = 0;
                    }
                    
                    TH_Sensor_Humidity_out = (unsigned int)dbl_tmp1;
                    
                    ExtSens_RH = dbl_tmp1/1000.0f;
                    
                    ExtSens_RH0D1P_U16 = dbl_tmp1;
                    
                    ALSensor_TH_Stage = ALSENSOR_STAGE_WAIT2;
                    
                    ALSensor_TH_HoleTime = 190;
                    
                    ALSensor_TH_RepeatCnt = 0;
                    
                    Flag_TH_Err_Comm = 0;
                    
                    
                    #if((defined(DEBUG_HUMI_RATE_EN))&&(DEBUG_HUMI_RATE_EN==1))
                    {
                        int i;
                        
                        
                        //Filter and obtain one RH data;
                        ExtSens_RH_Total += ExtSens_RH0D1P_U16;
                        ExtSens_RH_TolIdx++;
                        
                        if(ExtSens_RH_TolIdx>=5)
                        {
                            for(i=(DEF_RH_BUFF_LEN-2);i>(-1);i--)
                            {
                                ExtSens_RH_Buff[i+1] = ExtSens_RH_Buff[i];
                            }
                            ExtSens_RH_Buff[0] = ExtSens_RH_Total/ExtSens_RH_TolIdx;
                            
                            ExtSens_RH_TolIdx = 0;
                            ExtSens_RH_Total = 0;
                            
                            if(ExtSens_RH_BufIdx<DEF_RH_BUFF_LEN)
                            {
                                ExtSens_RH_BufIdx ++;
                            }
                            
                            if(ExtSens_RH_BufIdx>=DEF_RH_BUFF_LEN)
                            {
                                ExtSens_RH_Max = 0;
                                ExtSens_RH_Min = 0xFFFF;
                                
                                for(i=0;i<DEF_RH_BUFF_LEN;i++)
                                {
                                    if(ExtSens_RH_Max<ExtSens_RH_Buff[i])
                                    {
                                        ExtSens_RH_Max = ExtSens_RH_Buff[i];
                                    }
                                    if(ExtSens_RH_Min>ExtSens_RH_Buff[i])
                                    {
                                        ExtSens_RH_Min = ExtSens_RH_Buff[i];
                                    }
                                }
                                
                                ExtSens_RH_Rate = ExtSens_RH_Max-ExtSens_RH_Min;
                                
                                if((Flag_RH_Rate_En == 1)&&(ExtSens_RH_Rate > ExtSens_RH_Thre))
                                {
                                    Flag_RH_Rate_Exceed = 1;
                                }
                                else
                                {
                                    Flag_RH_Rate_Exceed = 0;
                                }
                            }
                            
                        }
                    }
                    #endif
                    
                }
                #endif
                else
                {
                    ALSensor_TH_Stage = ALSENSOR_STAGE_WAIT1;
                    ALSensor_TH_HoleTime = 100;
                    ALSensor_TH_RepeatCnt ++;
                    
                    Flag_TH_Err_Comm = 1;
                }
                
            }
        }
        break;
        case ALSENSOR_STAGE_PROC:
        {
        
        }
        break;
        case ALSENSOR_STAGE_WAIT2:
        {
            if(ALSensor_TH_HoleTime == 0)
            {
                ALSensor_TH_Stage = ALSENSOR_STAGE_WAIT1;
                ALSensor_TH_HoleTime = 0;
                ALSensor_TH_RepeatCnt = 0;
            }
        }
        break;
        case ALSENSOR_STAGE_STOP:
        {
        
        }
        break;
        case ALSENSOR_STAGE_QUIT:
        {
        
        }
        break;
        
        default:
        {
        
        }
        break;
    }
    
    return errcode;
}




unsigned int CPS122_Temperature_0D1C;
unsigned int PSensor_Pressure_10Pa;

long TPSensor_Temporary;


#if(defined(SENSOR_PT_TYPE)&&(SENSOR_PT_TYPE == SENSOR_TYPE_CMP201))

#include "Usr_CMP201.h"


unsigned char ALSensor_CMP201_Stage = 0;
volatile unsigned int ALSensor_CMP201_HoleTime = 0;
unsigned char ALSensor_RepeatCnt;

unsigned char ALSensor_CMP201_ChipID;
unsigned char ALSensor_CMP201_RevID;
unsigned char ALSensor_CMP201_RegSta;
unsigned char CMP201_Data[6];

unsigned char Flag_CMP201_Err_Comm;
unsigned char Flag_CMP201_Err_TRange;
unsigned char Flag_CMP201_Err_PRange;


unsigned char ALSensor_CMP201_InitSetup(void)
{
    unsigned char errcode = 0;
    
    unsigned char rc;
    
    /***** CMP201 initialization setup *****/
    
    cmp201_software_reset_process();
    
    cmp201_initialization();
    
    /***** CMP201 enable PT func	*****/
    
    rc = cmp201_enable_PT_meas();
    
    if (rc != 0)
    {
        errcode += 1;
    }
    
    return errcode;
}


unsigned char ALSensor_CMP201_MainLoop(void)
{
    unsigned char rtncode = 0;
    unsigned char errcode = 0;
    
    switch(ALSensor_CMP201_Stage)
    {
        case ALSENSOR_STAGE_UNINIT:
        {   
            //Usr_Soft_IIC_Init(4);
            
            Usr_Soft_IIC_Init(I2C_CHANNEL_CMP201);
            
            ALSensor_CMP201_Stage = ALSENSOR_STAGE_KNOCK;
            
            ALSensor_CMP201_HoleTime = 5;
            
            ALSensor_CMP201_ChipID = 0;
            ALSensor_CMP201_RevID = 0;
            
            Flag_CMP201_Err_Comm = 1;
            Flag_CMP201_Err_TRange = 0;
            Flag_CMP201_Err_PRange = 0;
        }
        break;
        case ALSENSOR_STAGE_KNOCK:
        {   
            if(ALSensor_CMP201_HoleTime == 0)
            {
                
                /*****  check sensor ID *****/
                cmp201_burst_read(CMP201_REG_CHIP_ID, &ALSensor_CMP201_ChipID, 1);
                
                if(ALSensor_CMP201_ChipID == 0xA0)
                {
                    ALSensor_CMP201_Stage = ALSENSOR_STAGE_INIT;
                    ALSensor_CMP201_HoleTime = 10;
                    
                    Flag_CMP201_Err_Comm = 0;
                }
                else
                {
                    ALSensor_CMP201_Stage = ALSENSOR_STAGE_UNINIT;
                    
                    Flag_CMP201_Err_Comm = 1;
                }
            }
        }
        break;
        case ALSENSOR_STAGE_INIT:
        {
            if(ALSensor_CMP201_HoleTime == 0)
            {
                rtncode = ALSensor_CMP201_InitSetup();
                
                if(rtncode != 0)
                {
                    ALSensor_CMP201_Stage = ALSENSOR_STAGE_UNINIT;
                    ALSensor_CMP201_HoleTime = 10;
                    
                    Flag_CMP201_Err_Comm = 1;
                    
                }
                else
                {
                    ALSensor_CMP201_Stage = ALSENSOR_STAGE_WAIT1;
                    ALSensor_CMP201_HoleTime = 50;
                    ALSensor_RepeatCnt = 0;
                    
                    Flag_CMP201_Err_Comm = 0;
                }
            }
        }
        break;
        case ALSENSOR_STAGE_WAIT1:
        {   
            if(ALSensor_CMP201_HoleTime == 0)
            {   
                rtncode = cmp201_burst_read(CMP201_REG_STATUS, &ALSensor_CMP201_RegSta, 1);
                
                ALSensor_RepeatCnt++;
                
                if(ALSensor_CMP201_RegSta == 0x60)
                {
                    ALSensor_CMP201_Stage = ALSENSOR_STAGE_GETDATA;
                    ALSensor_CMP201_HoleTime = 0;
                    ALSensor_RepeatCnt = 0;
                }
                else
                {
                    ALSensor_CMP201_HoleTime = 50;
                    
                    if(ALSensor_RepeatCnt>50)
                    {
                        ALSensor_CMP201_Stage = ALSENSOR_STAGE_KNOCK;
                        
                        ALSensor_RepeatCnt = 0;
                    }
                }
            }
        }
        break;
        case ALSENSOR_STAGE_GETDATA:
        {
            if(ALSensor_CMP201_HoleTime == 0)
            {
                rtncode = cmp201_burst_read(CMP201_REG_PRESS_XLSB, CMP201_Data, 6);
                
                if(rtncode == 0)
                {   
                    TPSensor_Temporary = 0;
                    TPSensor_Temporary += CMP201_Data[2];
                    TPSensor_Temporary <<= 8;
                    TPSensor_Temporary += CMP201_Data[1];
                    TPSensor_Temporary <<= 8;
                    TPSensor_Temporary += CMP201_Data[0];
                    
                    TPSensor_Temporary >>= 6;       // Pa;
                    
                    //if(TPSensor_Temporary < 300)
                    if(TPSensor_Temporary < 30000)
                    {
                        #if((DEBUG_DEBUG_1 == 1)&&(defined(DEBUG_DEBUG_1)))
                            
                        #else
                            TPSensor_Temporary = 30000;
                        #endif
                        
                        Flag_CMP201_Err_PRange = 1;
                    }
                    else if(TPSensor_Temporary > 125000)
                    {
                        #if((DEBUG_DEBUG_1 == 1)&&(defined(DEBUG_DEBUG_1)))
                            
                        #else
                            TPSensor_Temporary = 125000;
                        #endif
                        
                        Flag_CMP201_Err_PRange = 1;
                    }
                    else
                    {
                        Flag_CMP201_Err_PRange = 0;
                    }
                    
                    ExtSens_Prs = TPSensor_Temporary;         // Pa;
                    
                    PSensor_Pressure_10Pa = TPSensor_Temporary/10;
                    
                    #if 1
                    TPSensor_Temporary = 0;
                    TPSensor_Temporary += CMP201_Data[5];
                    TPSensor_Temporary <<= 8;
                    TPSensor_Temporary += CMP201_Data[4];
                    TPSensor_Temporary <<= 8;
                    TPSensor_Temporary += CMP201_Data[3];
                    
                    TPSensor_Temporary = TPSensor_Temporary/6554;
                    
                    if(TPSensor_Temporary < (-400))
                    {   
                        #if((DEBUG_DEBUG_1 == 1)&&(defined(DEBUG_DEBUG_1)))
                        
                        #else
                        TPSensor_Temporary = -400;
                        #endif
                        Flag_CMP201_Err_TRange = 1;
                    }
                    else if(TPSensor_Temporary > 850)
                    {   
                        #if((DEBUG_DEBUG_1 == 1)&&(defined(DEBUG_DEBUG_1)))
                            
                        #else
                        TPSensor_Temporary = 850;
                        #endif
                        Flag_CMP201_Err_TRange = 1;
                    }
                    else
                    {
                        
                        Flag_CMP201_Err_TRange = 0;
                    }
                    
                    CPS122_Temperature_0D1C = TPSensor_Temporary;
                    ExtSens_Tmpr2 = TPSensor_Temporary;
                    ExtSens_Tmpr2 = ExtSens_Tmpr2/10.0;
                    #endif
                    
                    ALSensor_RepeatCnt = 0;
                    
                    Flag_CMP201_Err_Comm = 0;
                    
                    
                }
                else
                {
                    ALSensor_RepeatCnt++;
                    
                    Flag_CMP201_Err_Comm = 1;
                }
                
                
                if(ALSensor_RepeatCnt>50)
                {
                    ALSensor_CMP201_Stage = ALSENSOR_STAGE_INIT;
                    ALSensor_CMP201_HoleTime = 10;
                    ALSensor_RepeatCnt = 0;
                }
                else
                {
                    ALSensor_CMP201_Stage = ALSENSOR_STAGE_WAIT1;
                    
                    ALSensor_CMP201_HoleTime = 200;
                    
                    ALSensor_RepeatCnt = 0;
                }
            }
        }
        break;
        case ALSENSOR_STAGE_PROC:
        {
        
        }
        break;
        case ALSENSOR_STAGE_WAIT2:
        {
        
        }
        break;
        case ALSENSOR_STAGE_STOP:
        {
        
        }
        break;
        case ALSENSOR_STAGE_QUIT:
        {
        
        }
        break;
        
        default:
        {
        
        }
        break;
    }
    
    return errcode;
}


#endif



#endif



