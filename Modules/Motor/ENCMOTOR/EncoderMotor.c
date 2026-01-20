#include "EncoderMotor.h"

EncoderMotor_Instance_t* EncoderMotorList[ENCM_MX_CNT] = {NULL};
static uint8_t idx = 0;

static EncoderMotor_Instance_t* MOTORMODULE1;
static EncoderMotor_Instance_t* MOTORMODULE2;

EncoderMotor_Instance_t* EncoderMotor_Init(EncoderMotor_Config_t* config)
{
    EncoderMotor_Instance_t* _instance = (EncoderMotor_Instance_t*)malloc(sizeof(EncoderMotor_Instance_t));
    _instance->ID = config->ID;
    _instance->pwmhtim = config->pwmhtim;
    _instance->Encoderhtim = config->Encoderhtim;

    _instance->PCHANNEL = config->PCHANNEL;
    
    _instance->IN1_GPIOx = config->IN1_GPIOx;
    _instance->IN2_GPIOx = config->IN2_GPIOx;
    _instance->xIN1_Pin = config->xIN1_Pin;
    _instance->xIN2_Pin = config->xIN2_Pin;
    _instance->ReverseFlag = config->ReverseFlag;
    PIDInit(&_instance->SpeedPID,&config->SpeedPID);

    if(_instance->pwmhtim != NULL)
    {
        __HAL_TIM_SET_COMPARE(_instance->pwmhtim, _instance->PCHANNEL ,0);
        HAL_TIM_PWM_Start(_instance->pwmhtim,_instance->PCHANNEL );
    }
    else if(_instance->Encoderhtim != NULL )
    {
        HAL_TIM_Encoder_Start(_instance->Encoderhtim, TIM_CHANNEL_ALL);
        __HAL_TIM_ENABLE_IT(_instance->Encoderhtim,TIM_IT_UPDATE);
        __HAL_TIM_SET_COUNTER(_instance->Encoderhtim,10000);
    }
    else
    {
        //ERROR HANDLE
    }

    if(idx < ENCM_MX_CNT && _instance != NULL)
    {
       EncoderMotorList[idx++]=_instance;
    }
    else
    {
        free(_instance);
        return NULL;
    }
    return _instance;
}

static void EncoderMotorControl(EncoderMotor_Instance_t* _instance)
{
    /**TEST */
                // HAL_GPIO_WritePin(_instance->BIN1_GPIOx,_instance->xBIN1_Pin,GPIO_PIN_SET);
                // HAL_GPIO_WritePin(_instance->BIN2_GPIOx,_instance->xBIN2_Pin,GPIO_PIN_RESET);
                // __HAL_TIM_SetCompare(_instance->pwmhtim, _instance->B_CHANNEL,(uint16_t)(20));
                // HAL_GPIO_WritePin(_instance->AIN1_GPIOx,_instance->xAIN1_Pin,GPIO_PIN_SET);
                // HAL_GPIO_WritePin(_instance->AIN2_GPIOx,_instance->xAIN2_Pin,GPIO_PIN_RESET);
                // __HAL_TIM_SetCompare(_instance->pwmhtim, _instance->A_CHANNEL,(uint16_t)(20));
    switch(_instance->ReverseFlag)
    {
        case MOTOR_NORMAL:
            if(_instance->SpeedPID.Output >= 0)
            {
                HAL_GPIO_WritePin(_instance->IN1_GPIOx,_instance->xIN1_Pin,GPIO_PIN_SET);
                HAL_GPIO_WritePin(_instance->IN2_GPIOx,_instance->xIN2_Pin,GPIO_PIN_RESET);
                __HAL_TIM_SetCompare(_instance->pwmhtim, _instance->PCHANNEL,(uint16_t)(_instance->SpeedPID.Output));
            }
            else
            {
                HAL_GPIO_WritePin(_instance->IN1_GPIOx,_instance->xIN1_Pin,GPIO_PIN_RESET);
                HAL_GPIO_WritePin(_instance->IN2_GPIOx,_instance->xIN2_Pin,GPIO_PIN_SET);
                __HAL_TIM_SetCompare(_instance->pwmhtim, _instance->PCHANNEL,(uint16_t)(-1 * _instance->SpeedPID.Output));
            }
            break;
        case MOTOR_REVERSE:
            if(_instance->SpeedPID.Output >= 0)
            {
                HAL_GPIO_WritePin(_instance->IN1_GPIOx,_instance->xIN1_Pin,GPIO_PIN_RESET);
                HAL_GPIO_WritePin(_instance->IN2_GPIOx,_instance->xIN2_Pin,GPIO_PIN_SET);
                __HAL_TIM_SetCompare(_instance->pwmhtim, _instance->PCHANNEL,(uint16_t)(_instance->SpeedPID.Output));
            }
            else
            {
                HAL_GPIO_WritePin(_instance->IN1_GPIOx,_instance->xIN1_Pin,GPIO_PIN_SET);
                HAL_GPIO_WritePin(_instance->IN2_GPIOx,_instance->xIN2_Pin,GPIO_PIN_RESET);
                __HAL_TIM_SetCompare(_instance->pwmhtim, _instance->PCHANNEL,(uint16_t)(-1 * _instance->SpeedPID.Output));
            }
    }
}

void STOPALLEncoderMOTOR(EncoderMotor_Instance_t* _instance)
{
    HAL_GPIO_WritePin(_instance->IN1_GPIOx,_instance->xIN1_Pin,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(_instance->IN2_GPIOx,_instance->xIN2_Pin,GPIO_PIN_RESET);
    __HAL_TIM_SetCompare(_instance->pwmhtim, _instance->PCHANNEL,(uint16_t)(0));
    _instance->SpeedPID.Output = -1.0;
}

void Motor_SetSpeedRef(float SpeedRef)
{
    EncoderMotorList[0]->SpeedPID.Ref = SpeedRef;
}

void Motor_Init()
{
    EncoderMotor_Config_t motorconfig={};
    MOTORMODULE1 = EncoderMotor_Init(&motorconfig);

    HAL_TIM_Base_Start_IT(&htim6);//100HzSPDCalc
}

void Motor_Control()
{
    for(int i = 0;i<idx;i++)
    {
        if(EncoderMotorList[i]->MotorMode == MOTOR_START)
        {
            EncoderMotorControl(EncoderMotorList[i]);
        }   
        else
        {
            STOPALLEncoderMOTOR(EncoderMotorList[i]);
        }
    }
}

// void LinearMapVelocity(float v_lf,float v_lb,float v_rf,float v_rb)
// {
//     MOTORMODULE1->A_SpeedPID.Output = v_lf/3.22 *(htim1.Init.Period+1);

//     MOTORMODULE2->A_SpeedPID.Output = v_lb/3.22 *(htim1.Init.Period+1);
// }

// void LinearMapVxy(float Vx,float Vy,float Wz)
// {
//     static float v_lf,v_lb,v_rf,v_rb;
//     v_rf = (Vx*arm_cos_f32(PI/4.0) - Vy*arm_sin_f32(PI/4.0)) + Wz;
//     v_rb = (-Vx*arm_cos_f32(PI/4.0) - Vy*arm_sin_f32(PI/4.0)) + Wz;
//     v_lf = (Vx*arm_cos_f32(PI/4.0) + Vy*arm_sin_f32(PI/4.0)) + Wz;
//     v_lb = (-Vx*arm_cos_f32(PI/4.0) + Vy*arm_sin_f32(PI/4.0)) + Wz;
//     LinearMapVelocity(v_lf,v_lb,v_rf,v_rb);
// }


void OVERCNTCALLBACK(TIM_HandleTypeDef *HZ100htim)
{
    static uint8_t i;
    i=0;
    
    for(i=0;i<idx;i++)
    {
        if(EncoderMotorList[i]->Encoderhtim == HZ100htim)
        {
            if(__HAL_TIM_GetCounter(HZ100htim) < 10000) EncoderMotorList[i]->overflowNum++;       //如果是向上溢出
            else if(__HAL_TIM_GetCounter(HZ100htim) >= 10000) EncoderMotorList[i]->overflowNum--; //如果是向下溢出
            __HAL_TIM_SetCounter(HZ100htim, 10000); 
        }
    }
    
}

void CalSpeed(TIM_HandleTypeDef *SPDhtim)
{
    static uint8_t i;
    i=0;
    for(i=0;i<idx;i++)
    {
        EncoderMotorList[i]->direct = __HAL_TIM_IS_TIM_COUNTING_DOWN(EncoderMotorList[i]->Encoderhtim);
        EncoderMotorList[i]->totalCount = __HAL_TIM_GetCounter(EncoderMotorList[i]->Encoderhtim) + EncoderMotorList[i]->overflowNum * __HAL_TIM_GetAutoreload(EncoderMotorList[i]->Encoderhtim);
        EncoderMotorList[i]->speed = (float)( EncoderMotorList[i]->totalCount - EncoderMotorList[i]->lastCount) / (4 * EncoderMotorList[i]->RERATIO * EncoderMotorList[i]->PPR) * 10 * LINE_SPEED_C;
        if(EncoderMotorList[i]->direct==0)
		{
				EncoderMotorList[i]->t1 =  EncoderMotorList[i]->speed/1;
				EncoderMotorList[i]->j1=(EncoderMotorList[i]->speed - EncoderMotorList[i]->t1)*10000;
		}
		else
		{
				EncoderMotorList[i]->t1 =  -EncoderMotorList[i]->speed/1;
				EncoderMotorList[i]->j1=(EncoderMotorList[i]->speed + EncoderMotorList[i]->t1)*10000;
		}
        EncoderMotorList[i]->lastCount = EncoderMotorList[i]->totalCount;
    }
}

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM14 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */
  
  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM7) 
  {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */
  else if(htim == &htim6)
  {
    CalSpeed(htim);
    OVERCNTCALLBACK(htim);
  }
  
  /* USER CODE END Callback 1 */
}