#include "robot.h"
#include "projdefs.h"
#include "robot_def.h"
#include "robot_task.h"
#include "bsp_dwt.h"
#include "SEGGER_RTT.h"

// #include "TB6612.h"

void RobotInit()
{  
    // 关闭中断,防止在初始化过程中发生中断
    // 请不要在初始化过程中使用中断和延时函数！
    // 若必须,则只允许使用DWT_Delay()
    __disable_irq();
    DWT_Init(168); // 初始化DWT
    // TB6612_Motor_Init();
    OSTaskInit(); // 创建基础任务

    // 初始化完成,开启中断
    __enable_irq();
}

void RobotTask()
{
    static uint8_t AA=0;
    SEGGER_RTT_printf(0, "HELLO!%d\r\n",AA);
    HAL_GPIO_TogglePin(LED2_GPIO_Port, LED2_Pin);
    osDelay(pdMS_TO_TICKS(1000));
    if(AA <=99)AA+=1;
    else AA=0;
}
