#ifndef LED_H
#define LED_H


#ifdef __cplusplus
extern "C" {
#endif


#include "main.h"
#include "gpio.h"


class LED
{
    public:
    LED(GPIO_TypeDef* L_Port, uint32_t L_Pin);
    void ON();
    void OFF();
    void TOGGLE();


    private:
    uint32_t Pin;
    GPIO_TypeDef* Port;
};




#ifdef __cplusplus
}
#endif

#endif // !LED_H
