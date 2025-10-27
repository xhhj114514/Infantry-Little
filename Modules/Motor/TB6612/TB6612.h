#ifndef TB6612_H
#define TB6612_H

#include "main.h"
#include "gpio.h"
#include "tim.h"

#include "controller.h"


typedef enum
{
    MOTOR_NORMAL = 0x00,
    MOTOR_REVERSE = 0x01,
}ReverseFlag_e;

typedef struct __TB6612_Config__
{
    uint8_t ID;
    TIM_HandleTypeDef *pwmhtim;
    TIM_HandleTypeDef *A1Encoderhtim;
    TIM_HandleTypeDef *B1Encoderhtim;

    GPIO_TypeDef *AIN1_GPIOx;
    GPIO_TypeDef *AIN2_GPIOx;
    GPIO_TypeDef *BIN1_GPIOx;
    GPIO_TypeDef *BIN2_GPIOx;
    uint16_t xAIN1_Pin;
    uint16_t xAIN2_Pin;
    uint16_t xBIN1_Pin;
    uint16_t xBIN2_Pin;


    float *A_SpeedPtr;
    PID_Init_Config_s  A_SpeedPID;
    ReverseFlag_e A_ReverseFlag;
    uint16_t A_CHANNEL;


    float *B_SpeedPtr;
    PID_Init_Config_s  B_SpeedPID;
    ReverseFlag_e B_ReverseFlag;
    uint16_t B_CHANNEL;

    uint8_t PPR;
    uint8_t RERATIO;

}TB6612_Config_t;

typedef struct __TB6612_Instance__
{
    uint8_t ID;
    TIM_HandleTypeDef *pwmhtim;
    TIM_HandleTypeDef *A1Encoderhtim;
    TIM_HandleTypeDef *B1Encoderhtim;

    GPIO_TypeDef *AIN1_GPIOx;
    GPIO_TypeDef *AIN2_GPIOx;
    GPIO_TypeDef *BIN1_GPIOx;
    GPIO_TypeDef *BIN2_GPIOx;
    uint16_t xAIN1_Pin;
    uint16_t xAIN2_Pin;
    uint16_t xBIN1_Pin;
    uint16_t xBIN2_Pin;

    int At1;
    int Aj1;
    float *A_SpeedPtr;
    float A_SpeeedRef;
    PIDInstance  A_SpeedPID;
    ReverseFlag_e A_ReverseFlag;
    uint16_t A_CHANNEL;

    int Bt1;
    int Bj1;
    float *B_SpeedPtr;
    float B_SpeeedRef;
    PIDInstance  B_SpeedPID;
    ReverseFlag_e B_ReverseFlag;
    uint16_t B_CHANNEL;


    int32_t AlastCount;   //上一次计数值
    int32_t AtotalCount;  //总计数值
    int16_t AoverflowNum; //溢出次数
    float Aspeed;         //电机转速
    uint8_t Adirect;      //旋转方向
    

    int32_t BlastCount;   //上一次计数值
    int32_t BtotalCount;  //总计数值
    int16_t BoverflowNum; //溢出次数
    float Bspeed;         //电机转速
    uint8_t Bdirect;      //旋转方向

    uint8_t PPR;
    uint8_t RERATIO;

}TB6612_Instance_t;

TB6612_Instance_t* TB6612_Init(TB6612_Config_t* config);
void TB6612_Set_Motor(TB6612_Instance_t* _instance);

void TB6612_Motor_Init();
void TB6612_Motor_Control();


void LinearMapVxy(float Vx,float Vy,float Wz);


#endif //TB6612_H