/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define PWMPRSC 168-1
#define CORECLK 168000000
#define PWMFREQ 15000
#define PWMPERIOD CORECLK/(PWMFREQ*(PWMPRSC+1))
#define KEY1_Pin GPIO_PIN_3
#define KEY1_GPIO_Port GPIOE
#define KEY2_Pin GPIO_PIN_4
#define KEY2_GPIO_Port GPIOE
#define ENC5A_Pin GPIO_PIN_0
#define ENC5A_GPIO_Port GPIOA
#define ENC5B_Pin GPIO_PIN_1
#define ENC5B_GPIO_Port GPIOA
#define PWM3_Pin GPIO_PIN_5
#define PWM3_GPIO_Port GPIOA
#define LED2_Pin GPIO_PIN_6
#define LED2_GPIO_Port GPIOA
#define LED3_Pin GPIO_PIN_7
#define LED3_GPIO_Port GPIOA
#define FLASH_CS_Pin GPIO_PIN_0
#define FLASH_CS_GPIO_Port GPIOB
#define ENC1A_Pin GPIO_PIN_9
#define ENC1A_GPIO_Port GPIOE
#define ENC1B_Pin GPIO_PIN_11
#define ENC1B_GPIO_Port GPIOE
#define PWM1_Pin GPIO_PIN_10
#define PWM1_GPIO_Port GPIOB
#define PWM2_Pin GPIO_PIN_11
#define PWM2_GPIO_Port GPIOB
#define ENC4A_Pin GPIO_PIN_12
#define ENC4A_GPIO_Port GPIOD
#define ENC4B_Pin GPIO_PIN_13
#define ENC4B_GPIO_Port GPIOD
#define ENC3A_Pin GPIO_PIN_6
#define ENC3A_GPIO_Port GPIOC
#define ENC3B_Pin GPIO_PIN_7
#define ENC3B_GPIO_Port GPIOC
#define PWM4_Pin GPIO_PIN_8
#define PWM4_GPIO_Port GPIOC
#define M3IN1_Pin GPIO_PIN_2
#define M3IN1_GPIO_Port GPIOD
#define M3IN2_Pin GPIO_PIN_3
#define M3IN2_GPIO_Port GPIOD
#define M4IN1_Pin GPIO_PIN_4
#define M4IN1_GPIO_Port GPIOD
#define M4IN2_Pin GPIO_PIN_5
#define M4IN2_GPIO_Port GPIOD
#define M2IN1_Pin GPIO_PIN_6
#define M2IN1_GPIO_Port GPIOD
#define M2IN2_Pin GPIO_PIN_7
#define M2IN2_GPIO_Port GPIOD
#define NRF_CE_Pin GPIO_PIN_6
#define NRF_CE_GPIO_Port GPIOB
#define NRF_CS_Pin GPIO_PIN_7
#define NRF_CS_GPIO_Port GPIOB
#define NRF_IRQ_Pin GPIO_PIN_8
#define NRF_IRQ_GPIO_Port GPIOB
#define NRF_IRQ_EXTI_IRQn EXTI9_5_IRQn
#define M1IN1_Pin GPIO_PIN_0
#define M1IN1_GPIO_Port GPIOE
#define M1IN2_Pin GPIO_PIN_1
#define M1IN2_GPIO_Port GPIOE

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
