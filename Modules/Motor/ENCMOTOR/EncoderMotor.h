#ifndef EncoderMotor_H
#define EncoderMotor_H

#include "main.h"
#include "gpio.h"
#include "tim.h"

#include "controller.h"


#define RADIUS_OF_TYRE 55 //mm
#define LINE_SPEED_C RADIUS_OF_TYRE * 2 * 3.1415
#define ENCM_MX_CNT 5

typedef enum
{
    MOTOR_NORMAL = 0x00,
    MOTOR_REVERSE = 0x01,
}ReverseFlag_e;

typedef enum
{
    MOTOR_START = 0x00,
    MOTOR_STOP = 0x01,
}WorkMode_e;

typedef struct __EncoderMotor_Config__
{
    uint8_t ID;
    TIM_HandleTypeDef *pwmhtim;
    uint16_t PCHANNEL;
    TIM_HandleTypeDef *Encoderhtim;

    GPIO_TypeDef *IN1_GPIOx;
    GPIO_TypeDef *IN2_GPIOx;
    uint16_t xIN1_Pin;
    uint16_t xIN2_Pin;

    float *SpeedPtr;
    float *CurPtr;
    PID_Init_Config_s  SpeedPID;
    ReverseFlag_e ReverseFlag;

    float PPR;
    float RERATIO;
    WorkMode_e MotorMode;
}EncoderMotor_Config_t;

typedef struct __EncoderMotor_Instance__
{
    uint8_t ID;
    TIM_HandleTypeDef *pwmhtim;
    uint16_t PCHANNEL;
    TIM_HandleTypeDef *Encoderhtim;

    GPIO_TypeDef *IN1_GPIOx;
    GPIO_TypeDef *IN2_GPIOx;
    uint16_t xIN1_Pin;
    uint16_t xIN2_Pin;

    float *SpeedPtr;
    float *CurPtr;
    PIDInstance  SpeedPID;
    ReverseFlag_e ReverseFlag;
    
    float PPR;
    float RERATIO;

    int t1;
    int j1;
    float  SpeeedRef;

    int32_t lastCount;   //上一次计数值
    int32_t totalCount;  //总计数值
    int16_t overflowNum; //溢出次数
    float speed;         //电机转速
    uint8_t direct;      //旋转方向
    WorkMode_e MotorMode;
    
}EncoderMotor_Instance_t;

EncoderMotor_Instance_t* EncoderMotor_Init(EncoderMotor_Config_t* config);
void TB6612_Set_Motor(EncoderMotor_Instance_t* _instance);

void Motor_Init();
void Motor_Control();


// void LinearMapVxy(float Vx,float Vy,float Wz);


#endif 