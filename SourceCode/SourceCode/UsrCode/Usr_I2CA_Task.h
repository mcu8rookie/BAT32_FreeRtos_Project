#ifndef __USR_I2CA_TASK_H__
#define __USR_I2CA_TASK_H__




#include "Usr_Config.h"


#if(defined(DEF_TASK_I2CA_EN)&&(DEF_TASK_I2CA_EN==1))

extern const char * const Task_I2CA_Name;
extern const configSTACK_DEPTH_TYPE    Task_I2CA_StackDepth;
extern uint32_t Task_I2CA_Arg;
extern uint32_t *Task_I2CA_ArgPtr;
extern UBaseType_t Task_I2CA_Priogrity;
extern TaskHandle_t Task_I2CA_Handle;

void Usr_Task_I2CA(void *TaskParameter);


void Usr_Create_I2CA_Task(void);

#endif

#if(defined(DEF_TASK_I2CS_EN)&&(DEF_TASK_I2CS_EN==1))

extern const char * const Task_I2C20_Name;
extern const configSTACK_DEPTH_TYPE    Task_I2CS_StackDepth;
extern uint32_t Task_I2CS_Arg;
extern uint32_t *Task_I2CS_ArgPtr;
extern UBaseType_t Task_I2CS_Priogrity;
extern TaskHandle_t Task_I2CS_Handle;

void Usr_Task_I2CS(void *TaskParameter);

void Usr_Create_I2C20_Task(void);

#endif



#endif


