#ifndef __USR_TASK_H__
#define __USR_TASK_H__


#define TASK_STACK_DEPTH     (64)


#define DEF_TASK_TEST1_EN   0
#define DEF_TASK_TEST2_EN   0
#define DEF_TASK_TEST3_EN   0
#define DEF_TASK_TEST4_EN   0
#define DEF_TASK_TEST5_EN   0

#define DEF_TASK_I2CA_EN    0
#define DEF_TASK_I2CS_EN    1

#define DEF_TASK_UART_EN    1


extern SemaphoreHandle_t Usr_SemaphoreHandle_Print;


void Usr_Task_Create(void);


#if(defined(DEF_TASK_TEST1_EN)&&(DEF_TASK_TEST1_EN == 1))

extern const char * const Task_Test1_Name;
extern const configSTACK_DEPTH_TYPE Task_Test1_StackDepth;
extern uint32_t Task_Test1_Arg;
extern uint32_t *Task_Test1_ArgPtr;
extern UBaseType_t Task_Test1_Priority;
extern TaskHandle_t Task_Test1_Handle;

extern void Usr_Task_Test1(void *TaskParameter);
#endif

#if(defined(DEF_TASK_TEST2_EN)&&(DEF_TASK_TEST2_EN == 1))
extern const char * const Task_Test2_Name;
extern const configSTACK_DEPTH_TYPE Task_Test2_StackDepth;
extern uint32_t Task_Test2_Arg;
extern uint32_t *Task_Test2_ArgPtr;
extern UBaseType_t Task_Test2_Priority;
extern TaskHandle_t Task_Test2_Handle;

void Usr_Task_Test2(void *TaskParameter);
#endif

#if(defined(DEF_TASK_TEST3_EN)&&(DEF_TASK_TEST3_EN == 1))
extern const char * const Task_Test3_Name;
extern const configSTACK_DEPTH_TYPE Task_Test3_StackDepth;
extern uint32_t Task_Test3_Arg;
extern uint32_t *Task_Test3_ArgPtr;
extern UBaseType_t Task_Test3_Priority;
extern TaskHandle_t Task_Test3_Handle;

void Usr_Task_Test3(void *TaskParameter);
#endif

#if(defined(DEF_TASK_TEST4_EN)&&(DEF_TASK_TEST4_EN == 1))
extern const char * const Task_Test4_Name;
extern const configSTACK_DEPTH_TYPE Task_Test4_StackDepth;
extern uint32_t Task_Test4_Arg;
extern uint32_t *Task_Test4_ArgPtr;
extern UBaseType_t Task_Test4_Priority;
extern TaskHandle_t Task_Test4_Handle;

void Usr_Task_Test4(void *TaskParameter);
#endif

#if(defined(DEF_TASK_TEST5_EN)&&(DEF_TASK_TEST5_EN == 1))
extern const char * const Task_Test5_Name;
extern const configSTACK_DEPTH_TYPE Task_Test5_StackDepth;
extern uint32_t Task_Test5_Arg;
extern uint32_t *Task_Test5_ArgPtr;
extern UBaseType_t Task_Test5_Priority;
extern TaskHandle_t Task_Test5_Handle;

void Usr_Task_Test5(void *TaskParameter);
#endif


#endif

