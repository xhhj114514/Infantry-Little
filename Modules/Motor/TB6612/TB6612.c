#include "TB6612.h"

TB6612_Instance_t* TB6612_List[3] = {NULL};
static uint8_t idx = 0;

static TB6612_Instance_t* MOTORMODULE1;
static TB6612_Instance_t* MOTORMODULE2;

TB6612_Instance_t* TB6612_Init(TB6612_Config_t* config)
{
    TB6612_Instance_t* _instance = (TB6612_Instance_t*)malloc(sizeof(TB6612_Instance_t));
    _instance->ID = config->ID;
    _instance->pwmhtim = config->pwmhtim;
    _instance->A1Encoderhtim = config->A1Encoderhtim;
    _instance->B1Encoderhtim = config->B1Encoderhtim;

    _instance->A_CHANNEL = config->A_CHANNEL;
    
    _instance->AIN1_GPIOx = config->AIN1_GPIOx;
    _instance->AIN2_GPIOx = config->AIN2_GPIOx;
    _instance->xAIN1_Pin = config->xAIN1_Pin;
    _instance->xAIN2_Pin = config->xAIN2_Pin;
    _instance->A_ReverseFlag = config->A_ReverseFlag;
    PIDInit(&_instance->A_SpeedPID,&config->A_SpeedPID);
    
    _instance->B_CHANNEL = config->B_CHANNEL;
    _instance->BIN1_GPIOx = config->BIN1_GPIOx;
    _instance->BIN2_GPIOx = config->BIN2_GPIOx;
    _instance->xBIN1_Pin = config->xBIN1_Pin;
    _instance->xBIN2_Pin = config->xBIN2_Pin;
    _instance->B_ReverseFlag = config->B_ReverseFlag;
    PIDInit(&_instance->B_SpeedPID,&config->B_SpeedPID);
    if(idx < 2 && _instance != NULL)
    {
        TB6612_List[idx++]=_instance;
    }
    if(_instance->pwmhtim != NULL)
    {
        __HAL_TIM_SET_COMPARE(_instance->pwmhtim, _instance->A_CHANNEL | _instance->B_CHANNEL,0);
        HAL_TIM_PWM_Start(_instance->pwmhtim,_instance->A_CHANNEL );
        HAL_TIM_PWM_Start(_instance->pwmhtim,_instance->B_CHANNEL );
    }
    if(_instance->A1Encoderhtim != NULL && _instance->B1Encoderhtim != NULL)
    {
        HAL_TIM_Encoder_Start(_instance->A1Encoderhtim, TIM_CHANNEL_ALL);
        HAL_TIM_Encoder_Start(_instance->B1Encoderhtim, TIM_CHANNEL_ALL); 
        __HAL_TIM_ENABLE_IT(_instance->A1Encoderhtim,TIM_IT_UPDATE);
        __HAL_TIM_ENABLE_IT(_instance->B1Encoderhtim,TIM_IT_UPDATE);
        __HAL_TIM_SET_COUNTER(_instance->A1Encoderhtim,10000);
        __HAL_TIM_SET_COUNTER(_instance->B1Encoderhtim,10000);
    }
    return _instance;
}

void TB6612_Set_Motor(TB6612_Instance_t* _instance)
{
    /**TEST */
                // HAL_GPIO_WritePin(_instance->BIN1_GPIOx,_instance->xBIN1_Pin,GPIO_PIN_SET);
                // HAL_GPIO_WritePin(_instance->BIN2_GPIOx,_instance->xBIN2_Pin,GPIO_PIN_RESET);
                // __HAL_TIM_SetCompare(_instance->pwmhtim, _instance->B_CHANNEL,(uint16_t)(20));
                // HAL_GPIO_WritePin(_instance->AIN1_GPIOx,_instance->xAIN1_Pin,GPIO_PIN_SET);
                // HAL_GPIO_WritePin(_instance->AIN2_GPIOx,_instance->xAIN2_Pin,GPIO_PIN_RESET);
                // __HAL_TIM_SetCompare(_instance->pwmhtim, _instance->A_CHANNEL,(uint16_t)(20));
    switch(_instance->A_ReverseFlag)
    {
        case MOTOR_NORMAL:
            if(_instance->A_SpeedPID.Output >= 0)
            {
                HAL_GPIO_WritePin(_instance->AIN1_GPIOx,_instance->xAIN1_Pin,GPIO_PIN_SET);
                HAL_GPIO_WritePin(_instance->AIN2_GPIOx,_instance->xAIN2_Pin,GPIO_PIN_RESET);
                __HAL_TIM_SetCompare(_instance->pwmhtim, _instance->A_CHANNEL,(uint16_t)(_instance->A_SpeedPID.Output));
            }
            else
            {
                HAL_GPIO_WritePin(_instance->AIN1_GPIOx,_instance->xAIN1_Pin,GPIO_PIN_RESET);
                HAL_GPIO_WritePin(_instance->AIN2_GPIOx,_instance->xAIN2_Pin,GPIO_PIN_SET);
                __HAL_TIM_SetCompare(_instance->pwmhtim, _instance->A_CHANNEL,(uint16_t)(-1 * _instance->A_SpeedPID.Output));
            }
            break;
        case MOTOR_REVERSE:
            if(_instance->A_SpeedPID.Output >= 0)
            {
                HAL_GPIO_WritePin(_instance->AIN1_GPIOx,_instance->xAIN1_Pin,GPIO_PIN_RESET);
                HAL_GPIO_WritePin(_instance->AIN2_GPIOx,_instance->xAIN2_Pin,GPIO_PIN_SET);
                __HAL_TIM_SetCompare(_instance->pwmhtim, _instance->A_CHANNEL,(uint16_t)(_instance->A_SpeedPID.Output));
            }
            else
            {
                HAL_GPIO_WritePin(_instance->AIN1_GPIOx,_instance->xAIN1_Pin,GPIO_PIN_SET);
                HAL_GPIO_WritePin(_instance->AIN2_GPIOx,_instance->xAIN2_Pin,GPIO_PIN_RESET);
                __HAL_TIM_SetCompare(_instance->pwmhtim, _instance->A_CHANNEL,(uint16_t)(-1 * _instance->A_SpeedPID.Output));
            }
    }
    switch(_instance->B_ReverseFlag)
    {
        case MOTOR_NORMAL:
            if(_instance->B_SpeedPID.Output >= 0)
            {
                HAL_GPIO_WritePin(_instance->BIN1_GPIOx,_instance->xBIN1_Pin,GPIO_PIN_SET);
                HAL_GPIO_WritePin(_instance->BIN2_GPIOx,_instance->xBIN2_Pin,GPIO_PIN_RESET);
                __HAL_TIM_SetCompare(_instance->pwmhtim, _instance->B_CHANNEL,(uint16_t)(_instance->B_SpeedPID.Output));
            }
            else
            {
                HAL_GPIO_WritePin(_instance->BIN1_GPIOx,_instance->xBIN1_Pin,GPIO_PIN_RESET);
                HAL_GPIO_WritePin(_instance->BIN2_GPIOx,_instance->xBIN2_Pin,GPIO_PIN_SET);
                __HAL_TIM_SetCompare(_instance->pwmhtim, _instance->B_CHANNEL,(uint16_t)(-1 * _instance->B_SpeedPID.Output));
            }
            break;
        case MOTOR_REVERSE:
            if(_instance->B_SpeedPID.Output >= 0)
            {
                HAL_GPIO_WritePin(_instance->BIN1_GPIOx,_instance->xBIN1_Pin,GPIO_PIN_RESET);
                HAL_GPIO_WritePin(_instance->BIN2_GPIOx,_instance->xBIN2_Pin,GPIO_PIN_SET);
                __HAL_TIM_SetCompare(_instance->pwmhtim, _instance->B_CHANNEL,(uint16_t)(_instance->B_SpeedPID.Output));
            }
            else
            {
                HAL_GPIO_WritePin(_instance->BIN1_GPIOx,_instance->xBIN1_Pin,GPIO_PIN_SET);
                HAL_GPIO_WritePin(_instance->BIN2_GPIOx,_instance->xBIN2_Pin,GPIO_PIN_RESET);
                __HAL_TIM_SetCompare(_instance->pwmhtim, _instance->B_CHANNEL,(uint16_t)(-1 * _instance->B_SpeedPID.Output));
            }
    }

}

void TB6612_Motor_SetSpeedRef(float SpeedARef,float SpeedBRef)
{
    TB6612_List[0]->A_SpeedPID.Ref = SpeedARef;
    TB6612_List[1]->B_SpeedPID.Ref = SpeedBRef;
}

void TB6612_Motor_Init()
{
    TB6612_Config_t motorconfig={
    .ID = 0,
    .pwmhtim = &htim1,
    // .A1Encoderhtim = &htim2,
    // .B1Encoderhtim = &htim3,
    .AIN1_GPIOx = AIN1_GPIO_Port,
    .xAIN1_Pin = AIN1_Pin,
    .AIN2_GPIOx = AIN2_GPIO_Port,
    .xAIN2_Pin = AIN2_Pin,
    .A_CHANNEL = TIM_CHANNEL_1,
    .A_ReverseFlag = MOTOR_NORMAL,

    .BIN1_GPIOx = BIN1_GPIO_Port,
    .xBIN1_Pin = BIN1_Pin,
    .BIN2_GPIOx = BIN2_GPIO_Port,
    .xBIN2_Pin = BIN2_Pin,
    .B_CHANNEL = TIM_CHANNEL_2,
    .B_ReverseFlag = MOTOR_NORMAL,
  };
  MOTORMODULE1 = TB6612_Init(&motorconfig);
  
//   TB6612_Set_Motor(MOTORMODULE1);

    TB6612_Config_t motorconfig2={
    .ID = 0,
    .pwmhtim = &htim1,
    // .A1Encoderhtim = &htim4,
    // .B1Encoderhtim = &htim8,
    .AIN1_GPIOx = _AIN1_GPIO_Port,
    .xAIN1_Pin = _AIN1_Pin,
    .AIN2_GPIOx = _AIN2_GPIO_Port,
    .xAIN2_Pin = _AIN2_Pin,
    .A_CHANNEL = TIM_CHANNEL_3,
    .A_ReverseFlag = MOTOR_NORMAL,

    .BIN1_GPIOx = _BIN1_GPIO_Port,
    .xBIN1_Pin = _BIN1_Pin,
    .BIN2_GPIOx = _BIN2_GPIO_Port,
    .xBIN2_Pin = _BIN2_Pin,
    .B_CHANNEL = TIM_CHANNEL_4,
    .B_ReverseFlag = MOTOR_NORMAL,
  };
  MOTORMODULE2 = TB6612_Init(&motorconfig2);
//   TB6612_Set_Motor(MOTORMODULE2);
  HAL_TIM_Base_Start_IT(&htim6);
}

void TB6612_Motor_Control()
{
    for(int i = 0;i<idx;i++)
    {
        TB6612_Set_Motor(TB6612_List[i]);
    }
}

void LinearMapVelocity(float v_lf,float v_lb,float v_rf,float v_rb)
{
    MOTORMODULE1->A_SpeedPID.Output = v_lb/3.22 *(htim1.Init.Period+1);
    MOTORMODULE1->B_SpeedPID.Output = v_rb/3.22 *(htim1.Init.Period+1);

    MOTORMODULE2->A_SpeedPID.Output = v_lf/3.22 *(htim1.Init.Period+1);
    MOTORMODULE2->B_SpeedPID.Output = v_rf/3.22 *(htim1.Init.Period+1);
}

void LinearMapVxy(float Vx,float Vy,float Wz)
{
    static float v_lf,v_lb,v_rf,v_rb;
    v_rf = (Vx*arm_cos_f32(PI/4.0) + Vy*arm_sin_f32(PI/4.0)) - Wz;
    v_rb = (-Vx*arm_cos_f32(PI/4.0) + Vy*arm_sin_f32(PI/4.0)) - Wz;
    v_lf = (-Vx*arm_cos_f32(PI/4.0) + Vy*arm_sin_f32(PI/4.0)) + Wz;
    v_lb = (Vx*arm_cos_f32(PI/4.0) + Vy*arm_sin_f32(PI/4.0)) + Wz;
    LinearMapVelocity(v_lf,v_lb,v_rf,v_rb);
}


void OVERCNTCALLBACK(TIM_HandleTypeDef *HZ100htim)
{
    static uint8_t i;
    i=0;
    
    for(i=0;i<idx;i++)
    {
        if(TB6612_List[i]->A1Encoderhtim == HZ100htim)
        {
            if(__HAL_TIM_GetCounter(HZ100htim) < 10000) TB6612_List[i]->AoverflowNum++;       //如果是向上溢出
            else if(__HAL_TIM_GetCounter(HZ100htim) >= 10000) TB6612_List[i]->AoverflowNum--; //如果是向下溢出
            __HAL_TIM_SetCounter(HZ100htim, 10000); 
        }
        else if(TB6612_List[i]->B1Encoderhtim == HZ100htim)
        {
            if(__HAL_TIM_GetCounter(HZ100htim) < 10000) TB6612_List[i]->AoverflowNum++;       //如果是向上溢出
            else if(__HAL_TIM_GetCounter(HZ100htim) >= 10000) TB6612_List[i]->AoverflowNum--; //如果是向下溢出
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
        TB6612_List[i]->Adirect = __HAL_TIM_IS_TIM_COUNTING_DOWN(TB6612_List[i]->A1Encoderhtim);
        TB6612_List[i]->AtotalCount = __HAL_TIM_GetCounter(TB6612_List[i]->A1Encoderhtim) + TB6612_List[i]->AoverflowNum * __HAL_TIM_GetAutoreload(TB6612_List[i]->A1Encoderhtim);
        TB6612_List[i]->Aspeed = (float)( TB6612_List[i]->AtotalCount - TB6612_List[i]->AlastCount) / (4 * TB6612_List[i]->RERATIO * TB6612_List[i]->PPR) * 10;
        if(TB6612_List[i]->Adirect==0)
		{
				TB6612_List[i]->At1 =  TB6612_List[i]->Aspeed/1;
				TB6612_List[i]->Aj1=(TB6612_List[i]->Aspeed - TB6612_List[i]->At1)*10000;
		}
		else
		{
				TB6612_List[i]->At1 =  -TB6612_List[i]->Aspeed/1;
				TB6612_List[i]->Aj1=(TB6612_List[i]->Aspeed + TB6612_List[i]->At1)*10000;
		}
        TB6612_List[i]->AlastCount = TB6612_List[i]->AtotalCount;
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
  if (htim->Instance == TIM14) 
  {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */
  else if(htim->Instance == TIM2 )
  {
    //   OVERCNTCALLBACK(htim);
  }
  else if(htim == &htim6)
  {
      TB6612_Set_Motor(MOTORMODULE1);
      TB6612_Set_Motor(MOTORMODULE2);
    //   CalSpeed(htim);
  }
  /* USER CODE END Callback 1 */
}