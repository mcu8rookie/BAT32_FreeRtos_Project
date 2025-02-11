#ifndef __USR_TASK_C__
#define __USR_TASK_C__

#include "Usr_Config.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

#include "Usr_Task.h"

#include"gpio.h"
#include"Usr_GPIO.h"

#include"Usr_Debug.h"

#include"Usr_Main.h"

#include "queue.h"



SemaphoreHandle_t Usr_SemaphoreHandle_Print = NULL;

QueueHandle_t QueuePtr_Task1_To_Task2;
QueueHandle_t QueuePtr_Task2_To_Task3;
QueueHandle_t QueuePtr_Task3_To_Task4;
QueueHandle_t QueuePtr_Task4_To_Task5;






void Usr_Task_Create(void)
{
    BaseType_t rtn = 0;
    
    Debug_printf("\nRun Usr_Task_Create();\n");
    
    Usr_SemaphoreHandle_Print = NULL;
    Usr_SemaphoreHandle_Print = xSemaphoreCreateMutex();
    if(Usr_SemaphoreHandle_Print != NULL)
    {
        Debug_printf("\nError: xSemaphoreCreateMutex() OK;");
    }
    else
    {
        Debug_printf("\nError: xSemaphoreCreateMutex() NG;");
    }
    
    QueuePtr_Task1_To_Task2 = xQueueCreate(8, 32);
    if(QueuePtr_Task1_To_Task2 != NULL)
    {
        Debug_printf("\nError: xQueueCreate() OK;");
    }
    else
    {
        Debug_printf("\nError: xQueueCreate() NG;");
    }
    
    QueuePtr_Task2_To_Task3 = xQueueCreate(8, 32);
    if(QueuePtr_Task1_To_Task2 != NULL)
    {
        Debug_printf("\nError: xQueueCreate() OK;");
    }
    else
    {
        Debug_printf("\nError: xQueueCreate() NG;");
    }
    
    QueuePtr_Task3_To_Task4 = xQueueCreate(8, 32);
    if(QueuePtr_Task3_To_Task4 != NULL)
    {
        Debug_printf("\nError: xQueueCreate() OK;");
    }
    else
    {
        Debug_printf("\nError: xQueueCreate() NG;");
    }
    
    QueuePtr_Task4_To_Task5 = xQueueCreate(8, 32);
    if(QueuePtr_Task4_To_Task5 != NULL)
    {
        Debug_printf("\nError: xQueueCreate() OK;");
    }
    else
    {
        Debug_printf("\nError: xQueueCreate() NG;");
    }
    
    
    
    #if 1
    {
        Debug_printf("Create Task: %s;",Task_Test1_Name);
        
        rtn = xTaskCreate(
            Usr_Task_Test1,
            Task_Test1_Name,
            Task_Test1_StackDepth, 
            Task_Test1_ArgPtr,
            Task_Test1_Priority,
            &Task_Test1_Handle);
        
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
    
    #if 1
    {
        Debug_printf("Create Task: %s;",Task_Test2_Name);
        
        rtn = xTaskCreate(
            Usr_Task_Test2,
            Task_Test2_Name,
            Task_Test2_StackDepth, 
            Task_Test2_ArgPtr,
            Task_Test2_Priority,
            &Task_Test2_Handle);
        
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
    
    #if 1
    {
        Debug_printf("Create Task: %s;",Task_Test3_Name);
        
        rtn = xTaskCreate(
            Usr_Task_Test3,
            Task_Test3_Name,
            Task_Test3_StackDepth, 
            Task_Test3_ArgPtr,
            Task_Test3_Priority,
            &Task_Test3_Handle);
        
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
    
    #if 1
    {
        Debug_printf("Create Task: %s;",Task_Test4_Name);
        
        rtn = xTaskCreate(
            Usr_Task_Test4,
            Task_Test4_Name,
            Task_Test4_StackDepth, 
            Task_Test4_ArgPtr,
            Task_Test4_Priority,
            &Task_Test4_Handle);
        
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
    
    #if 1
    {
        Debug_printf("Create Task: %s;",Task_Test5_Name);
        
        rtn = xTaskCreate(
            Usr_Task_Test5,
            Task_Test5_Name,
            Task_Test5_StackDepth, 
            Task_Test5_ArgPtr,
            Task_Test5_Priority,
            &Task_Test5_Handle);
        
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



const char * const Task_Test1_Name = "Task_Test1";
const configSTACK_DEPTH_TYPE Task_Test1_StackDepth = 128;
uint32_t Task_Test1_Arg = 1;
uint32_t *Task_Test1_ArgPtr = &Task_Test1_Arg;
UBaseType_t Task_Test1_Priority = 2;
TaskHandle_t Task_Test1_Handle;

void Usr_Task_Test1(void *TaskParameter)
{   
    
    
    static int8_t flg = 0;
    
    BaseType_t RtnCode = 0;
    uint8_t buff[16];
    uint8_t *sndptr;
    
    while(1)
    {
        if(flg == 0)
        {
            Debug_printf_Mut("Mcu_Timestamp,%d,\n",Mcu_Timestamp);
            Debug_printf_Mut("\nTast1 flg = %d;\n",flg);
            
            PORT_ClrBit(Usr_LED1_PORT,Usr_LED1_PIN);
            flg = 1;
        }
        else
        {
            Debug_printf_Mut("Mcu_Timestamp,%d,\n",Mcu_Timestamp);
            Debug_printf_Mut("\nTast1 flg = %d;\n",flg);
            
            PORT_SetBit(Usr_LED1_PORT,Usr_LED1_PIN);
            flg= 0;
        }
        
        if(QueuePtr_Task1_To_Task2 != NULL)
        {
            sndptr = "Q:T1 to T2;";
            
            RtnCode = xQueueSend(QueuePtr_Task1_To_Task2,sndptr,1000);
            
            if(RtnCode == pdPASS)
            {
                
            }
            else
            {
                Debug_printf_Mut("\nError: xQueueSend,%d,\n",RtnCode);
            }
        }
        
        vTaskDelay(1000);
    }
}

const char * const Task_Test2_Name = "Task_Test2";
const configSTACK_DEPTH_TYPE Task_Test2_StackDepth = 128;
uint32_t Task_Test2_Arg = 2;
uint32_t *Task_Test2_ArgPtr = &Task_Test2_Arg;
UBaseType_t Task_Test2_Priority = 3;
TaskHandle_t Task_Test2_Handle;

void Usr_Task_Test2(void *TaskParameter)
{   
    static int8_t flg = 0;
    
    BaseType_t RtnCode = 0;
    uint8_t *sndptr;
    uint8_t buff[16];
    
    while(1)
    {
        
        if(QueuePtr_Task1_To_Task2 != NULL)
        {
            
            RtnCode = NULL;
            RtnCode = xQueueReceive(QueuePtr_Task1_To_Task2,buff,1100);
            
            if(RtnCode != NULL)
            {
                
            }
            else
            {
                Debug_printf_Mut("\nError: xQueueReceive %d.\n",RtnCode);
            }
        }
        else
        {
            Debug_printf_Mut("\nError: None QueuePtr_Task1_To_Task2.\n");
            return;
        }
        
        if(flg == 0)
        {
            Debug_printf_Mut("Mcu_Timestamp,%d,\n",Mcu_Timestamp);
            Debug_printf_Mut("\nTast2 flg = %d;\n",flg);
            
            PORT_ClrBit(Usr_LED2_PORT,Usr_LED2_PIN);
            flg = 1;
        }
        else
        {
            Debug_printf_Mut("Mcu_Timestamp,%d,\n",Mcu_Timestamp);
            Debug_printf_Mut("\nTast2 flg = %d;\n",flg);
            
            PORT_SetBit(Usr_LED2_PORT,Usr_LED2_PIN);
            flg= 0;
        }
        
        if(QueuePtr_Task2_To_Task3 != NULL)
        {
            
            sndptr = "Q:T2 to T3;";
            
            RtnCode = xQueueSend(QueuePtr_Task2_To_Task3,sndptr,1000);
            if(RtnCode == pdPASS)
            {
                
            }
            else
            {
                Debug_printf_Mut("\nError: xQueueSend,%d,\n",RtnCode);
            }
        }
        else
        {
            vTaskDelay(2000);
        }
    }
}


const char * const Task_Test3_Name = "Task_Test3";
const configSTACK_DEPTH_TYPE Task_Test3_StackDepth = 128;
uint32_t Task_Test3_Arg = 2;
uint32_t *Task_Test3_ArgPtr = &Task_Test3_Arg;
UBaseType_t Task_Test3_Priority = 3;
TaskHandle_t Task_Test3_Handle;

void Usr_Task_Test3(void *TaskParameter)
{   
    static int8_t flg = 0;
    
    BaseType_t RtnCode = 0;
    uint8_t *sndptr;
    uint8_t buff[16];
    
    while(1)
    {
        if(QueuePtr_Task2_To_Task3 != NULL)
        {
            
            RtnCode = NULL;
            RtnCode = xQueueReceive(QueuePtr_Task2_To_Task3,buff,1100);
            
            if(RtnCode != NULL)
            {
                
            }
            else
            {
                Debug_printf_Mut("\nError: xQueueReceive %d.\n",RtnCode);
            }
        }
        else
        {
            Debug_printf_Mut("\nError: None QueuePtr_Task2_To_Task3.\n");
            return;
        }
        
        
        if(flg == 0)
        {
            Debug_printf_Mut("Mcu_Timestamp,%d,\n",Mcu_Timestamp);
            Debug_printf_Mut("\nTast3 flg = %d;\n",flg);
            
            flg = 1;
        }
        else
        {
            Debug_printf_Mut("Mcu_Timestamp,%d,\n",Mcu_Timestamp);
            Debug_printf_Mut("\nTast3 flg = %d;\n",flg);
            
            flg= 0;
        }
        
        if(QueuePtr_Task3_To_Task4 != NULL)
        {
            
            sndptr = "Q:T3 to T4;";
            
            RtnCode = xQueueSend(QueuePtr_Task3_To_Task4,sndptr,1000);
            if(RtnCode == pdPASS)
            {
                
            }
            else
            {
                Debug_printf_Mut("\nError: xQueueSend,%d,\n",RtnCode);
            }
        }
        else
        {
            vTaskDelay(3000);
        }
        
    }
}


const char * const Task_Test4_Name = "Task_Test4";
const configSTACK_DEPTH_TYPE Task_Test4_StackDepth = 128;
uint32_t Task_Test4_Arg = 2;
uint32_t *Task_Test4_ArgPtr = &Task_Test4_Arg;
UBaseType_t Task_Test4_Priority = 3;
TaskHandle_t Task_Test4_Handle;

void Usr_Task_Test4(void *TaskParameter)
{   
    static int8_t flg = 0;
    
    BaseType_t RtnCode = 0;
    uint8_t *sndptr;
    uint8_t buff[16];
    
    while(1)
    {
        
        if(QueuePtr_Task3_To_Task4 != NULL)
        {
            
            RtnCode = NULL;
            RtnCode = xQueueReceive(QueuePtr_Task3_To_Task4,buff,1100);
            
            if(RtnCode != NULL)
            {
                
            }
            else
            {
                Debug_printf_Mut("\nError: xQueueReceive %d.\n",RtnCode);
            }
        }
        else
        {
            Debug_printf_Mut("\nError: None QueuePtr_Task3_To_Task4.\n");
            return;
        }
        
        if(flg == 0)
        {
            Debug_printf_Mut("Mcu_Timestamp,%d,\n",Mcu_Timestamp);
            Debug_printf_Mut("\nTast4 flg = %d;\n",flg);
            
            flg = 1;
        }
        else
        {
            Debug_printf_Mut("Mcu_Timestamp,%d,\n",Mcu_Timestamp);
            Debug_printf_Mut("\nTast4 flg = %d;\n",flg);
            
            flg= 0;
        }
        
        if(QueuePtr_Task4_To_Task5 != NULL)
        {
            
            sndptr = "Q:T4 to T5;";
            
            RtnCode = xQueueSend(QueuePtr_Task4_To_Task5,sndptr,1000);
            if(RtnCode == pdPASS)
            {
                
            }
            else
            {
                Debug_printf_Mut("\nError: xQueueSend,%d,\n",RtnCode);
            }
        }
        else
        {
            vTaskDelay(4000);
        }
    }
}


const char * const Task_Test5_Name = "Task_Test5";
const configSTACK_DEPTH_TYPE Task_Test5_StackDepth = 128;
uint32_t Task_Test5_Arg = 2;
uint32_t *Task_Test5_ArgPtr = &Task_Test5_Arg;
UBaseType_t Task_Test5_Priority = 3;
TaskHandle_t Task_Test5_Handle;

void Usr_Task_Test5(void *TaskParameter)
{   
    static int8_t flg = 0;
    
    BaseType_t RtnCode = 0;
    uint8_t *sndptr;
    uint8_t buff[16];
    
    while(1)
    {
        if(QueuePtr_Task4_To_Task5 != NULL)
        {
            
            RtnCode = NULL;
            RtnCode = xQueueReceive(QueuePtr_Task4_To_Task5,buff,1100);
            
            if(RtnCode != NULL)
            {
                
            }
            else
            {
                Debug_printf_Mut("\nError: xQueueReceive %d.\n",RtnCode);
            }
        }
        else
        {
            Debug_printf_Mut("\nError: None QueuePtr_Task4_To_Task5.\n");
            return;
        }
        
        if(flg == 0)
        {
            Debug_printf_Mut("Mcu_Timestamp,%d,\n",Mcu_Timestamp);
            Debug_printf_Mut("\nTast5 flg = %d;\n",flg);
            
            flg = 1;
        }
        else
        {
            Debug_printf_Mut("Mcu_Timestamp,%d,\n",Mcu_Timestamp);
            Debug_printf_Mut("\nTast5 flg = %d;\n",flg);
            
            flg= 0;
        }
        
        //vTaskDelay(5000);
        vTaskDelay(500);
    }
}







#endif


