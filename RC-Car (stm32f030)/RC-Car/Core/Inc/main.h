/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "stm32f0xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim15;
extern UART_HandleTypeDef huart3;

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define M_SPEED_Pin GPIO_PIN_1
#define M_SPEED_GPIO_Port GPIOB
#define LORA_TX_Pin GPIO_PIN_10
#define LORA_TX_GPIO_Port GPIOB
#define LORA_RX_Pin GPIO_PIN_11
#define LORA_RX_GPIO_Port GPIOB
#define SM1_PWM_Pin GPIO_PIN_14
#define SM1_PWM_GPIO_Port GPIOB
#define SM2_PWM_Pin GPIO_PIN_15
#define SM2_PWM_GPIO_Port GPIOB
#define M_BACKWARD_Pin GPIO_PIN_9
#define M_BACKWARD_GPIO_Port GPIOA
#define M_FORWARD_Pin GPIO_PIN_10
#define M_FORWARD_GPIO_Port GPIOA

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
