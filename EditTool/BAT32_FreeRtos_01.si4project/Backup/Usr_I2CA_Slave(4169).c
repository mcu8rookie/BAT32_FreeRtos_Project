#ifndef __USR_I2CA_SLAVE_C__
#define __USR_I2CA_SLAVE_C__


#include <stdint.h>

#include "userdefine.h"
//#include "BAT32A237.h"
#include "iica.h"

#include "Usr_I2CA_Slave.h"

void Usr_I2CA_InitSetup(void)
{
    IICA0_Init();
}

#endif



