#ifndef __USR_SOFT_I2C_C__
#define __USR_SOFT_I2C_C__

#include"stdint.h"

//#include"Usr_Code.h"

#include"Usr_Config.h"

#include "BAT32A237.h"
#include "gpio.h"

#include"Usr_Soft_I2C.h"
#include "Usr_HDC3020.h"

unsigned char iic_tmp1 = 0;
unsigned char iic_tmp2 = 0;

unsigned char HTS_I2C_Address_7B;
unsigned char HTS_I2C_Address_8B_Rd;
unsigned char HTS_I2C_Address_8B_Wt;

#define IIC_Channel_SHT41       1
#define IIC_Channel_CPS122      2
#define IIC_Channel_HDC2010     3
#define IIC_Channel_CMP201      4

#if(defined(DEF_MCU_CLASS)&&(DEF_MCU_CLASS==MCU_CLS_HT8))


#endif

#if(defined(DEF_MCU_CLASS)&&(DEF_MCU_CLASS==MCU_CLS_BAT32))

void Usr_IIC_DelayUs(unsigned int nbr)
{
    while(nbr>0)
    {
        nbr--;
    }
}


void Usr_IIC1_SCL_SetOut(void)
{
    PORT_Init(IIC1_SCL_PORT,IIC1_SCL_PIN,OUTPUT);
}
void Usr_IIC1_SCL_SetIn(void)
{
    PORT_Init(IIC1_SCL_PORT,IIC1_SCL_PIN,PULLUP_INPUT);
}
void Usr_IIC1_SDA_SetOut(void)
{
    PORT_Init(IIC1_SDA_PORT,IIC1_SDA_PIN,OUTPUT);
}
void Usr_IIC1_SDA_SetIn(void)
{
    PORT_Init(IIC1_SDA_PORT,IIC1_SDA_PIN,PULLUP_INPUT);
}


void Usr_IIC2_SCL_SetOut(void)
{
    PORT_Init(IIC2_SCL_PORT,IIC2_SCL_PIN,OUTPUT);
}
void Usr_IIC2_SCL_SetIn(void)
{
    PORT_Init(IIC2_SCL_PORT,IIC2_SCL_PIN,PULLUP_INPUT);
}

void Usr_IIC2_SDA_SetOut(void)
{
    PORT_Init(IIC2_SDA_PORT,IIC2_SDA_PIN,OUTPUT);
}
void Usr_IIC2_SDA_SetIn(void)
{
    PORT_Init(IIC2_SDA_PORT,IIC2_SDA_PIN,PULLUP_INPUT);
}

void Usr_IIC3_SCL_SetOut(void)
{
    PORT_Init(IIC3_SCL_PORT,IIC3_SCL_PIN,OUTPUT);
}
void Usr_IIC3_SCL_SetIn(void)
{
    PORT_Init(IIC3_SCL_PORT,IIC3_SCL_PIN,PULLUP_INPUT);
}
void Usr_IIC3_SDA_SetOut(void)
{
    PORT_Init(IIC3_SDA_PORT,IIC3_SDA_PIN,OUTPUT);
}
void Usr_IIC3_SDA_SetIn(void)
{
    PORT_Init(IIC3_SDA_PORT,IIC3_SDA_PIN,PULLUP_INPUT);
}



void Usr_IIC1_SCL_Set(unsigned char nbr)
{
    if(nbr == 0)
    {
        PORT_ClrBit(IIC1_SCL_PORT,IIC1_SCL_PIN);
    }
    else
    {
        PORT_SetBit(IIC1_SCL_PORT,IIC1_SCL_PIN);
    }
}

void Usr_IIC1_SDA_Set(unsigned char nbr)
{
    if(nbr == 0)
    {
        PORT_ClrBit(IIC1_SDA_PORT,IIC1_SDA_PIN);
    }
    else
    {
        PORT_SetBit(IIC1_SDA_PORT,IIC1_SDA_PIN);
    }
}

void Usr_IIC2_SCL_Set(unsigned char nbr)
{
    if(nbr == 0)
    {
        PORT_ClrBit(IIC2_SCL_PORT,IIC2_SCL_PIN);
    }
    else
    {
        PORT_SetBit(IIC2_SCL_PORT,IIC2_SCL_PIN);
    }
}

void Usr_IIC2_SDA_Set(unsigned char nbr)
{
    if(nbr == 0)
    {
        PORT_ClrBit(IIC2_SDA_PORT,IIC2_SDA_PIN);
    }
    else
    {
        PORT_SetBit(IIC2_SDA_PORT,IIC2_SDA_PIN);
    }
}

void Usr_IIC3_SCL_Set(unsigned char nbr)
{
    if(nbr == 0)
    {
        PORT_ClrBit(IIC3_SCL_PORT,IIC3_SCL_PIN);
    }
    else
    {
        PORT_SetBit(IIC3_SCL_PORT,IIC3_SCL_PIN);
    }
}

void Usr_IIC3_SDA_Set(unsigned char nbr)
{
    if(nbr == 0)
    {
        PORT_ClrBit(IIC3_SDA_PORT,IIC3_SDA_PIN);
    }
    else
    {
        PORT_SetBit(IIC3_SDA_PORT,IIC3_SDA_PIN);
    }
}

void Usr_IIC4_SCL_Set(unsigned char nbr)
{
    if(nbr == 0)
    {
        PORT_ClrBit(IIC4_SCL_PORT,IIC4_SCL_PIN);
    }
    else
    {
        PORT_SetBit(IIC4_SCL_PORT,IIC4_SCL_PIN);
    }
}

void Usr_IIC4_SDA_Set(unsigned char nbr)
{
    if(nbr == 0)
    {
        PORT_ClrBit(IIC4_SDA_PORT,IIC4_SDA_PIN);
    }
    else
    {
        PORT_SetBit(IIC4_SDA_PORT,IIC4_SDA_PIN);
    }
}

unsigned char Usr_IIC1_SCL_State(void)
{
    if(0 == PORT_GetBit(IIC1_SCL_PORT,IIC1_SCL_PIN))
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

unsigned char Usr_IIC1_SDA_State(void)
{
    if(0 == PORT_GetBit(IIC1_SDA_PORT,IIC1_SDA_PIN))
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

unsigned char Usr_IIC2_SCL_State(void)
{
    if(0 == PORT_GetBit(IIC2_SCL_PORT,IIC2_SCL_PIN))
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

unsigned char Usr_IIC2_SDA_State(void)
{
    if(0 == PORT_GetBit(IIC2_SDA_PORT,IIC2_SDA_PIN))
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

unsigned char Usr_IIC3_SCL_State(void)
{
    if(0 == PORT_GetBit(IIC3_SCL_PORT,IIC3_SCL_PIN))
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

unsigned char Usr_IIC3_SDA_State(void)
{
    if(0 == PORT_GetBit(IIC3_SDA_PORT,IIC3_SDA_PIN))
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

unsigned char Usr_IIC4_SCL_State(void)
{
    if(0 == PORT_GetBit(IIC4_SCL_PORT,IIC4_SCL_PIN))
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

unsigned char Usr_IIC4_SDA_State(void)
{
    if(0 == PORT_GetBit(IIC4_SDA_PORT,IIC4_SDA_PIN))
    {
        return 0;
    }
    else
    {
        return 1;
    }
}



void Usr_Soft_IIC_Init(unsigned char nbr)
{   
    
    if(nbr == I2C_CHANNEL_E703)
    {   
         PORT_Init(IIC1_SCL_PORT,IIC1_SCL_PIN,OUTPUT);
         PORT_Init(IIC1_SDA_PORT,IIC1_SDA_PIN,OUTPUT);
         
         Usr_IIC1_SCL_Set(0);
         Usr_IIC1_SCL_Set(1);
         Usr_IIC_DelayUs(10);
         Usr_IIC1_SCL_Set(1);
    }
    
    if(nbr == I2C_CHANNEL_HDC3020)
    {   
         PORT_Init(IIC2_SCL_PORT,IIC2_SCL_PIN,OUTPUT);
         PORT_Init(IIC2_SDA_PORT,IIC2_SDA_PIN,OUTPUT);
         
         Usr_IIC2_SCL_Set(0);
         Usr_IIC2_SCL_Set(1);
         Usr_IIC_DelayUs(10);
         Usr_IIC2_SCL_Set(1);
    }
    
    if(nbr == I2C_CHANNEL_CMP201)
    {   
         PORT_Init(IIC3_SCL_PORT,IIC3_SCL_PIN,OUTPUT);
         PORT_Init(IIC3_SDA_PORT,IIC3_SDA_PIN,OUTPUT);
         
         Usr_IIC3_SCL_Set(0);
         Usr_IIC3_SCL_Set(1);
         Usr_IIC_DelayUs(10);
         Usr_IIC3_SCL_Set(1);
    }
    
}
#endif

void iic_start_signal(unsigned char nbr)
{   
    if(nbr == I2C_CHANNEL_E703)
    {
        //IIC1_SDA_Pin = 1;
        //IIC1_SCL_Pin = 1;
        //GCC_DELAY(2);
        //IIC1_SDA_Pin = 0;
        //GCC_DELAY(3);
        //IIC1_SCL_Pin = 0;
        //GCC_DELAY(2);
        
        Usr_IIC1_SDA_Set(1);
        Usr_IIC1_SCL_Set(1);
        Usr_IIC_DelayUs(20);
        Usr_IIC1_SDA_Set(0);
        Usr_IIC_DelayUs(30);
        Usr_IIC1_SCL_Set(0);
        Usr_IIC_DelayUs(20);
        
    }
    
    if(nbr == I2C_CHANNEL_HDC3020)
    {
        Usr_IIC2_SDA_Set(1);
        Usr_IIC2_SCL_Set(1);
        Usr_IIC_DelayUs(20);
        Usr_IIC2_SDA_Set(0);
        Usr_IIC_DelayUs(30);
        Usr_IIC2_SCL_Set(0);
        Usr_IIC_DelayUs(20);
        
    }
    
    if(nbr == I2C_CHANNEL_CMP201)
    {
        Usr_IIC3_SDA_Set(1);
        Usr_IIC3_SCL_Set(1);
        Usr_IIC_DelayUs(20);
        Usr_IIC3_SDA_Set(0);
        Usr_IIC_DelayUs(30);
        Usr_IIC3_SCL_Set(0);
        Usr_IIC_DelayUs(20);
        
    }
}

void iic_stop_signal(unsigned char nbr)
{
    if(nbr == I2C_CHANNEL_E703)
    {
        //GCC_DELAY(1);
        //IIC1_SDA_Pin = 0;
        //GCC_DELAY(1);
        //IIC1_SCL_Pin = 1;
        //GCC_DELAY(1);
        //IIC1_SDA_Pin = 1;
        //GCC_DELAY(7);
        
        Usr_IIC_DelayUs(10);
        Usr_IIC1_SDA_Set(0);
        Usr_IIC_DelayUs(10);
        Usr_IIC1_SCL_Set(1);
        Usr_IIC_DelayUs(10);
        Usr_IIC1_SDA_Set(1);
        Usr_IIC_DelayUs(70);
        
    }
    
    if(nbr == I2C_CHANNEL_HDC3020)
    {
        
        Usr_IIC_DelayUs(10);
        Usr_IIC2_SDA_Set(0);
        Usr_IIC_DelayUs(10);
        Usr_IIC2_SCL_Set(1);
        Usr_IIC_DelayUs(10);
        Usr_IIC2_SDA_Set(1);
        Usr_IIC_DelayUs(70);
        
    }

    if(nbr == I2C_CHANNEL_CMP201)
    {
        
        Usr_IIC_DelayUs(10);
        Usr_IIC3_SDA_Set(0);
        Usr_IIC_DelayUs(10);
        Usr_IIC3_SCL_Set(1);
        Usr_IIC_DelayUs(10);
        Usr_IIC3_SDA_Set(1);
        Usr_IIC_DelayUs(70);
        
    }
    
}


unsigned char iic_wait_ack(unsigned char nbr)
{
    if(nbr == I2C_CHANNEL_E703)
    {
        /*IIC1_SDA_SetIn;
        
        GCC_DELAY(2);
        IIC1_SCL_Pin = 1;
        GCC_DELAY(2);
        if(IIC1_SDA_Pin == 1)
        {
            IIC1_SDA_SetOut;
            IIC1_SCL_Pin = 0;
            return 1;
        }
        GCC_DELAY(3);
        if(IIC1_SDA_Pin == 1)
        {
            IIC1_SDA_SetOut;
            IIC1_SCL_Pin = 0;
            return 1;
        }
        IIC1_SCL_Pin = 0;
        IIC1_SDA_SetOut;
        GCC_DELAY(3);
        */
        
        
        Usr_IIC1_SDA_SetIn();
        
        Usr_IIC_DelayUs(20);
        Usr_IIC1_SCL_Set(1);
        Usr_IIC_DelayUs(20);
        if(Usr_IIC1_SDA_State() == 1)
        {
            Usr_IIC1_SDA_SetOut();
            Usr_IIC1_SCL_Set(0);
            return 1;
        }
        Usr_IIC_DelayUs(30);
        if(Usr_IIC1_SDA_State() == 1)
        {
            Usr_IIC1_SDA_SetOut();
            Usr_IIC1_SCL_Set(0);
            return 1;
        }
        Usr_IIC1_SCL_Set(0);
        Usr_IIC1_SDA_SetOut();
        Usr_IIC_DelayUs(30);
        
    }
    
    if(nbr == I2C_CHANNEL_HDC3020)
    {
        
        Usr_IIC2_SDA_SetIn();
        
        Usr_IIC_DelayUs(20);
        Usr_IIC2_SCL_Set(1);
        Usr_IIC_DelayUs(20);
        if(Usr_IIC2_SDA_State() == 1)
        {
            Usr_IIC2_SDA_SetOut();
            Usr_IIC2_SCL_Set(0);
            return 1;
        }
        Usr_IIC_DelayUs(30);
        if(Usr_IIC2_SDA_State() == 1)
        {
            Usr_IIC2_SDA_SetOut();
            Usr_IIC2_SCL_Set(0);
            return 1;
        }
        Usr_IIC2_SCL_Set(0);
        Usr_IIC2_SDA_SetOut();
        Usr_IIC_DelayUs(30);
        
    }
    
    if(nbr == I2C_CHANNEL_CMP201)
    {
        
        Usr_IIC3_SDA_SetIn();
        
        Usr_IIC_DelayUs(20);
        Usr_IIC3_SCL_Set(1);
        Usr_IIC_DelayUs(20);
        if(Usr_IIC3_SDA_State() == 1)
        {
            Usr_IIC3_SDA_SetOut();
            Usr_IIC3_SCL_Set(0);
            return 1;
        }
        Usr_IIC_DelayUs(30);
        if(Usr_IIC3_SDA_State() == 1)
        {
            Usr_IIC3_SDA_SetOut();
            Usr_IIC3_SCL_Set(0);
            return 1;
        }
        Usr_IIC3_SCL_Set(0);
        Usr_IIC3_SDA_SetOut();
        Usr_IIC_DelayUs(30);
        
    }
    
    return 0;
}


unsigned char iic_send_8bit(unsigned char nbr,unsigned char arg)
{
    if(nbr == I2C_CHANNEL_E703)
    {
        iic_tmp2 = 0x80;
        
        for(iic_tmp1=0;iic_tmp1<8;iic_tmp1++)
        {   
            #if 0
            if((arg&iic_tmp2) == 0)
            {
                IIC1_SDA_Pin = 0;
            }
            else
            {
                IIC1_SDA_Pin = 1;
            }
            GCC_DELAY(1);
            IIC1_SCL_Pin = 1;
            GCC_DELAY(7);
            IIC1_SCL_Pin = 0;
            GCC_DELAY(2);
            
            iic_tmp2>>=1;
            #endif
            
            
            #if 1
            if((arg&iic_tmp2) == 0)
            {
                Usr_IIC1_SDA_Set(0);
                
            }
            else
            {
                Usr_IIC1_SDA_Set(1);
            }
            Usr_IIC_DelayUs(10);
            Usr_IIC1_SCL_Set(1);
            Usr_IIC_DelayUs(70);
            Usr_IIC1_SCL_Set(0);
            Usr_IIC_DelayUs(20);
            iic_tmp2>>=1;
            #endif
        }
        
        //return iic_wait_ack(nbr);
        #if 0
        {
            IIC1_SDA_SetIn;
            
            GCC_DELAY(2);
            IIC1_SCL_Pin = 1;
            GCC_DELAY(2);
            if(IIC1_SDA_Pin == 1)
            {
                IIC1_SCL_Pin = 0;
                IIC1_SDA_SetOut;
                GCC_DELAY(3);
                IIC1_SDA_Pin = 1;
                return 1;
            }
            //GCC_DELAY(3);
            else if(IIC1_SDA_Pin == 0)
            {
                IIC1_SCL_Pin = 0;
                IIC1_SDA_SetOut;
                GCC_DELAY(3);
                IIC1_SDA_Pin = 1;
                return 0;
            }
            else
            {
                
            }
            IIC1_SDA_SetOut;
            IIC1_SDA_Pin = 1;
        }
        #endif
        
        #if 1
        {
            Usr_IIC1_SDA_SetIn();
            
            Usr_IIC_DelayUs(10);
            Usr_IIC1_SCL_Set(1);
            Usr_IIC_DelayUs(20);
            if(Usr_IIC1_SDA_State() == 1)
            {
                Usr_IIC1_SCL_Set(0);
                Usr_IIC1_SDA_SetOut();
                Usr_IIC_DelayUs(30);
                Usr_IIC1_SDA_Set(1);
                return 1;
            }
            else if(Usr_IIC1_SDA_State() == 0)
            {
                Usr_IIC1_SCL_Set(0);
                Usr_IIC1_SDA_SetOut();
                Usr_IIC_DelayUs(30);
                Usr_IIC1_SDA_Set(1);
                return 0;
            }
            else
            {
                
            }
            Usr_IIC1_SDA_SetOut();
            Usr_IIC1_SDA_Set(1);
        }
        #endif
        
        return 0;
    }
    
    if(nbr == I2C_CHANNEL_HDC3020)
    {
        iic_tmp2 = 0x80;
        
        for(iic_tmp1=0;iic_tmp1<8;iic_tmp1++)
        {   
            
            if((arg&iic_tmp2) == 0)
            {
                Usr_IIC2_SDA_Set(0);
                
            }
            else
            {
                Usr_IIC2_SDA_Set(1);
            }
            Usr_IIC_DelayUs(10);
            Usr_IIC2_SCL_Set(1);
            Usr_IIC_DelayUs(70);
            Usr_IIC2_SCL_Set(0);
            Usr_IIC_DelayUs(20);
            iic_tmp2>>=1;
        }
        
        //return iic_wait_ack(nbr);
        {
            Usr_IIC2_SDA_SetIn();
            
            Usr_IIC_DelayUs(10);
            Usr_IIC2_SCL_Set(1);
            Usr_IIC_DelayUs(20);
            if(Usr_IIC2_SDA_State() == 1)
            {
                Usr_IIC2_SCL_Set(0);
                Usr_IIC2_SDA_SetOut();
                Usr_IIC_DelayUs(30);
                Usr_IIC2_SDA_Set(1);
                return 1;
            }
            else if(Usr_IIC2_SDA_State() == 0)
            {
                Usr_IIC2_SCL_Set(0);
                Usr_IIC2_SDA_SetOut();
                Usr_IIC_DelayUs(30);
                Usr_IIC2_SDA_Set(1);
                return 0;
            }
            else
            {
                
            }
            Usr_IIC2_SDA_SetOut();
            Usr_IIC2_SDA_Set(1);
        }
        
        return 0;
    }
    
    if(nbr == I2C_CHANNEL_CMP201)
    {
        iic_tmp2 = 0x80;
        
        for(iic_tmp1=0;iic_tmp1<8;iic_tmp1++)
        {   
            
            if((arg&iic_tmp2) == 0)
            {
                Usr_IIC3_SDA_Set(0);
                
            }
            else
            {
                Usr_IIC3_SDA_Set(1);
            }
            Usr_IIC_DelayUs(10);
            Usr_IIC3_SCL_Set(1);
            Usr_IIC_DelayUs(70);
            Usr_IIC3_SCL_Set(0);
            Usr_IIC_DelayUs(20);
            iic_tmp2>>=1;
        }
        
        //return iic_wait_ack(nbr);
        {
            Usr_IIC3_SDA_SetIn();
            
            Usr_IIC_DelayUs(10);
            Usr_IIC3_SCL_Set(1);
            Usr_IIC_DelayUs(20);
            if(Usr_IIC3_SDA_State() == 1)
            {
                Usr_IIC3_SCL_Set(0);
                Usr_IIC3_SDA_SetOut();
                Usr_IIC_DelayUs(30);
                Usr_IIC3_SDA_Set(1);
                return 1;
            }
            else if(Usr_IIC3_SDA_State() == 0)
            {
                Usr_IIC3_SCL_Set(0);
                Usr_IIC3_SDA_SetOut();
                Usr_IIC_DelayUs(30);
                Usr_IIC3_SDA_Set(1);
                return 0;
            }
            else
            {
                
            }
            Usr_IIC3_SDA_SetOut();
            Usr_IIC3_SDA_Set(1);
        }
        
        return 0;
    }
    
    return 1;
}

unsigned char iic_receive_8bit(unsigned char nbr,unsigned char *parg,unsigned char fack)
{   
    if(nbr == 1)
    {
        iic_tmp2 = 0;
        
        //IIC1_SCL_Pin = 0;
        //GCC_DELAY(2);
        //IIC1_SDA_SetIn;
        
        Usr_IIC1_SCL_Set(0);
        Usr_IIC_DelayUs(20);
        Usr_IIC1_SDA_SetIn();
        
        for(iic_tmp1=0;iic_tmp1<8;iic_tmp1++)
        {
            iic_tmp2 <<= 1;
            
            #if 0
            IIC1_SCL_Pin = 1;
            GCC_DELAY(2);
            if(IIC1_SDA_Pin == 1)
            {
                iic_tmp2 += 1;
            }
            else
            {
                iic_tmp2 += 0;
            }
            GCC_DELAY(5);
            IIC1_SCL_Pin = 0;
            GCC_DELAY(2);
            #endif
            
            
            Usr_IIC1_SCL_Set(1);
            Usr_IIC_DelayUs(20);
            if(Usr_IIC1_SDA_State() == 1)
            {
                iic_tmp2 += 1;
            }
            else
            {
                iic_tmp2 += 0;
            }
            Usr_IIC_DelayUs(50);
            Usr_IIC1_SCL_Set(0);
            Usr_IIC_DelayUs(20);
        }
        
        //IIC1_SDA_SetOut;
        Usr_IIC1_SDA_SetOut();
        
        *parg = iic_tmp2;
        
        
        if(fack == 0)
        {   
            #if 0
            IIC1_SCL_Pin = 0;
            GCC_DELAY(1);
            IIC1_SDA_Pin = 1;
            GCC_DELAY(1);
            IIC1_SCL_Pin = 1;
            GCC_DELAY(7);
            IIC1_SCL_Pin = 0;
            GCC_DELAY(3);
            #endif
            
            Usr_IIC1_SCL_Set(0);
            Usr_IIC_DelayUs(10);
            Usr_IIC1_SDA_Set(1);
            Usr_IIC_DelayUs(10);
            Usr_IIC1_SCL_Set(1);
            Usr_IIC_DelayUs(70);
            Usr_IIC1_SCL_Set(0);
            Usr_IIC_DelayUs(30);
        }
        else
        {
            #if 0
            IIC1_SCL_Pin = 0;
            GCC_DELAY(1);
            IIC1_SDA_Pin = 0;
            GCC_DELAY(1);
            IIC1_SCL_Pin = 1;
            GCC_DELAY(7);
            IIC1_SCL_Pin = 0;
            GCC_DELAY(3);
            #endif
            
            Usr_IIC1_SCL_Set(0);
            Usr_IIC_DelayUs(10);
            Usr_IIC1_SDA_Set(0);
            Usr_IIC_DelayUs(10);
            Usr_IIC1_SCL_Set(1);
            Usr_IIC_DelayUs(70);
            Usr_IIC1_SCL_Set(0);
            Usr_IIC_DelayUs(30);
        }
    }
    
    if(nbr == 2)
    {
        iic_tmp2 = 0;
        
        Usr_IIC2_SCL_Set(0);
        Usr_IIC_DelayUs(20);
        Usr_IIC2_SDA_SetIn();
        
        for(iic_tmp1=0;iic_tmp1<8;iic_tmp1++)
        {
            iic_tmp2 <<= 1;
            
            Usr_IIC2_SCL_Set(1);
            Usr_IIC_DelayUs(20);
            if(Usr_IIC2_SDA_State() == 1)
            {
                iic_tmp2 += 1;
            }
            else
            {
                iic_tmp2 += 0;
            }
            Usr_IIC_DelayUs(50);
            Usr_IIC2_SCL_Set(0);
            Usr_IIC_DelayUs(20);
        }
        
        Usr_IIC2_SDA_SetOut();
        
        *parg = iic_tmp2;
        
        if(fack == 0)
        {   
            Usr_IIC2_SCL_Set(0);
            Usr_IIC_DelayUs(10);
            Usr_IIC2_SDA_Set(1);
            Usr_IIC_DelayUs(10);
            Usr_IIC2_SCL_Set(1);
            Usr_IIC_DelayUs(70);
            Usr_IIC2_SCL_Set(0);
            Usr_IIC_DelayUs(30);
        }
        else
        {   
            Usr_IIC2_SCL_Set(0);
            Usr_IIC_DelayUs(10);
            Usr_IIC2_SDA_Set(0);
            Usr_IIC_DelayUs(10);
            Usr_IIC2_SCL_Set(1);
            Usr_IIC_DelayUs(70);
            Usr_IIC2_SCL_Set(0);
            Usr_IIC_DelayUs(30);
        }
    }
    
    if(nbr == 3)
    {
        iic_tmp2 = 0;
        
        Usr_IIC3_SCL_Set(0);
        Usr_IIC_DelayUs(20);
        Usr_IIC3_SDA_SetIn();
        
        for(iic_tmp1=0;iic_tmp1<8;iic_tmp1++)
        {
            iic_tmp2 <<= 1;
            
            Usr_IIC3_SCL_Set(1);
            Usr_IIC_DelayUs(20);
            if(Usr_IIC3_SDA_State() == 1)
            {
                iic_tmp2 += 1;
            }
            else
            {
                iic_tmp2 += 0;
            }
            Usr_IIC_DelayUs(50);
            Usr_IIC3_SCL_Set(0);
            Usr_IIC_DelayUs(20);
        }
        
        Usr_IIC3_SDA_SetOut();
        
        *parg = iic_tmp2;
        
        if(fack == 0)
        {   
            Usr_IIC3_SCL_Set(0);
            Usr_IIC_DelayUs(10);
            Usr_IIC3_SDA_Set(1);
            Usr_IIC_DelayUs(10);
            Usr_IIC3_SCL_Set(1);
            Usr_IIC_DelayUs(70);
            Usr_IIC3_SCL_Set(0);
            Usr_IIC_DelayUs(30);
        }
        else
        {   
            Usr_IIC3_SCL_Set(0);
            Usr_IIC_DelayUs(10);
            Usr_IIC3_SDA_Set(0);
            Usr_IIC_DelayUs(10);
            Usr_IIC3_SCL_Set(1);
            Usr_IIC_DelayUs(70);
            Usr_IIC3_SCL_Set(0);
            Usr_IIC_DelayUs(30);
        }
    }
    
    
    return 0;
}

#if((defined(SENSOR_HT_TYPE))&&(SENSOR_HT_TYPE == SENSOR_TYPE_HDC3020))
//unsigned char HDC3020_ReadFlag;
#endif

unsigned char i2c_burst_read(unsigned char sn,unsigned char devID,unsigned char u8Addr, unsigned char *pu8Data, unsigned char u8Len)
{   
    unsigned char errcode = 0;
    unsigned char rtncode = 0;
    unsigned char tmp_cnt1 = 0;
    
    if((u8Len < 1)||(pu8Data == 0))
    {
        return 1;
    }
    
    #if((defined(SENSOR_HT_TYPE))&&(SENSOR_HT_TYPE == SENSOR_TYPE_HDC3020))
    if(HDC3020_ReadFlag == 0)
    #endif
    {
        iic_start_signal(sn);
        
        rtncode = iic_send_8bit(sn,(devID<<1));
        if(rtncode > 0)
        {
            errcode += 1;
        }
        
        rtncode = iic_send_8bit(sn,u8Addr);
        if(rtncode > 0)
        {
            errcode += 1;
        }
        
        //iic_stop_signal(sn);
    }
    
    iic_start_signal(sn);
    
    rtncode = iic_send_8bit(sn,(devID<<1)+1);
    if(rtncode > 0)
    {
        errcode += 1;
    }
    
    //GCC_DELAY(2);
    Usr_IIC_DelayUs(20);
    
    if(u8Len>1)
    {
        for(tmp_cnt1 = 0;tmp_cnt1<u8Len-1;tmp_cnt1++)
        {
            rtncode = iic_receive_8bit(sn,pu8Data+tmp_cnt1,1);
            if(rtncode > 0)
            {
                errcode += 1;
            }
        }
    }
    
    rtncode = iic_receive_8bit(sn,pu8Data+tmp_cnt1,0);
    if(rtncode > 0)
    {
        errcode += 1;
    }
    
    iic_stop_signal(sn);
    
    return errcode;
}

unsigned char i2c_burst_write(unsigned char sn,unsigned char devID,unsigned char u8Addr, unsigned char *pu8Data, unsigned char u8Len)
{   
    unsigned char errcode = 0;
    unsigned char rtncode = 0;
    unsigned char tmp_cnt1;
    
    if((u8Len < 1)||(pu8Data == 0))
    {
        return 1;
    }
    
    iic_start_signal(sn);
    
    rtncode = iic_send_8bit(sn,(devID<<1));
    if(rtncode > 0)
    {
        errcode += 1;
    }
    
    rtncode = iic_send_8bit(sn,u8Addr);
    if(rtncode > 0)
    {
        errcode += 1;
    }
    
    for(tmp_cnt1 = 0;tmp_cnt1<u8Len;tmp_cnt1++)
    {
        rtncode = iic_send_8bit(sn,*(pu8Data+tmp_cnt1));
        if(rtncode > 0)
        {
            errcode += 1;
        }
    }
    
    iic_stop_signal(sn);
    
    return errcode;
}



#endif

