#include "LED.h"

LED::LED(GPIO_TypeDef* L_Port, uint32_t L_Pin)
{
    HAL_GPIO_WritePin(L_Port,L_Pin,GPIO_PIN_RESET);
    this->Port = L_Port;
    this->Pin = L_Pin;
}

void LED::ON()
{
    HAL_GPIO_WritePin(this->Port,this->Pin,GPIO_PIN_RESET);
}

void LED::OFF()
{
    HAL_GPIO_WritePin(this->Port,this->Pin,GPIO_PIN_SET);// banziwenti
}

void LED::TOGGLE()
{
    HAL_GPIO_TogglePin(this->Port,this->Pin);
}