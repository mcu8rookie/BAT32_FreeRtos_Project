#ifndef __USR_I2CA_TASK_C__
#define __USR_I2CA_TASK_C__

#include "Usr_Config.h"
#include"Usr_Debug.h"

#include "FreeRTOS.h"
#include "task.h"

#include"Usr_I2CA_Task.h"

#include "Usr_I2C.h"



#if(defined(DEF_TASK_I2CA_EN)&&(DEF_TASK_I2CA_EN==1))

const char * const Task_I2CA_Name = "Task_I2CA";
const configSTACK_DEPTH_TYPE    Task_I2CA_StackDepth = 128;
uint32_t Task_I2CA_Arg = 6;
uint32_t *Task_I2CA_ArgPtr = &Task_I2CA_Arg;
UBaseType_t Task_I2CA_Priogrity = 6;
TaskHandle_t Task_I2CA_Handle;

void Usr_Task_I2CA(void *TaskParameter)
{
    static uint32_t task_Cnt = 0;
    
    Usr_I2C_InitSetup();
    
    Debug_printf_Mut("\nTask_I2CA RunCnt = %d;",task_Cnt);
    
    while(1)
    {
        task_Cnt++;
        
        Usr_I2C_MainLoop();
        
        Debug_printf_Mut("\nTask_I2CA RunCnt = %d;",task_Cnt);
        
        
        vTaskDelay(1000);
    }
}

void Usr_Create_I2CA_Task(void)
{
    BaseType_t rtn;
    
    #if 1
    // about I2CA_Task;
    Debug_printf("\n");
    {
        Debug_printf("Create Task: %s;",Task_I2CA_Name);
        
        rtn = xTaskCreate(
            Usr_Task_I2CA,
            Task_I2CA_Name,
            Task_I2CA_StackDepth,
            Task_I2CA_ArgPtr,
            Task_I2CA_Priogrity,
            &Task_I2CA_Handle
            );
        if(rtn == pdPASS)
        {
            Debug_printf("\tCreate OK, rtn = %d;\n",rtn);
        }
        else
        {
            Debug_printf("\tCreate NG, rtn = %d;\n",rtn);
        }
    }
    #endif
}

#endif


#if(defined(DEF_TASK_I2C20_EN)&&(DEF_TASK_I2C20_EN==1))

const char * const Task_I2C20_Name = "Task_I2C20";
const configSTACK_DEPTH_TYPE    Task_I2C20_StackDepth = 128;
uint32_t Task_I2C20_Arg = 6;
uint32_t *Task_I2C20_ArgPtr = &Task_I2C20_Arg;
UBaseType_t Task_I2C20_Priogrity = 1;
TaskHandle_t Task_I2C20_Handle;

void Usr_Task_I2C20(void *TaskParameter)
{
    static uint32_t task_Cnt = 0;
    
    
    #if(defined(DEF_TASK_I2C20_EN)&&(DEF_TASK_I2C20_EN==1))
    Usr_I2CS_InitSetup();
    #endif
    
    Debug_printf_Mut("\nTask_I2C20 RunCnt = %d;",task_Cnt);
    
    while(1)
    {
        task_Cnt++;
        
        Usr_I2C20_MainLoop();
        
        Debug_printf_Mut("\nTask_I2C20 RunCnt = %d;",task_Cnt);
        
        
        vTaskDelay(1000);
    }
}

void Usr_Create_I2C20_Task(void)
{
    BaseType_t rtn;
    
    #if 1
    // about I2C20_Task;
    Debug_printf("\n");
    {
        Debug_printf("Create Task: %s;",Task_I2C20_Name);
        
        rtn = xTaskCreate(
            Usr_Task_I2C20,
            Task_I2C20_Name,
            Task_I2C20_StackDepth,
            Task_I2C20_ArgPtr,
            Task_I2C20_Priogrity,
            &Task_I2C20_Handle
            );
        if(rtn == pdPASS)
        {
            Debug_printf("\tCreate OK, rtn = %d;\n",rtn);
        }
        else
        {
            Debug_printf("\tCreate NG, rtn = %d;\n",rtn);
        }
    }
    #endif
}

#endif


#endif

