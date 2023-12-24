/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#include "stm32f1xx_hal.h"

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
#define btnBoard_Pin GPIO_PIN_13
#define btnBoard_GPIO_Port GPIOC
#define btnBoard_EXTI_IRQn EXTI15_10_IRQn
#define ledFloor1_Pin GPIO_PIN_0
#define ledFloor1_GPIO_Port GPIOC
#define ledFloor2_Pin GPIO_PIN_1
#define ledFloor2_GPIO_Port GPIOC
#define ledFloor3_Pin GPIO_PIN_2
#define ledFloor3_GPIO_Port GPIOC
#define ledFloor4_Pin GPIO_PIN_3
#define ledFloor4_GPIO_Port GPIOC
#define txUart_Pin GPIO_PIN_2
#define txUart_GPIO_Port GPIOA
#define rxUart_Pin GPIO_PIN_3
#define rxUart_GPIO_Port GPIOA
#define ledBoard_Pin GPIO_PIN_5
#define ledBoard_GPIO_Port GPIOA
#define in2Step_Pin GPIO_PIN_10
#define in2Step_GPIO_Port GPIOC
#define in3Step_Pin GPIO_PIN_11
#define in3Step_GPIO_Port GPIOC
#define in1Step_Pin GPIO_PIN_12
#define in1Step_GPIO_Port GPIOC
#define in4Step_Pin GPIO_PIN_2
#define in4Step_GPIO_Port GPIOD

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
