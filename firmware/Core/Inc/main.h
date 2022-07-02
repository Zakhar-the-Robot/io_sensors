/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
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
#define SONAR0_OUT_Pin GPIO_PIN_0
#define SONAR0_OUT_GPIO_Port GPIOA
#define SONAR0_IN_Pin GPIO_PIN_1
#define SONAR0_IN_GPIO_Port GPIOA
#define SONAR1_OUT_Pin GPIO_PIN_2
#define SONAR1_OUT_GPIO_Port GPIOA
#define SONAR1_IN_Pin GPIO_PIN_3
#define SONAR1_IN_GPIO_Port GPIOA
#define SONAR2_OUT_Pin GPIO_PIN_4
#define SONAR2_OUT_GPIO_Port GPIOA
#define SONAR2_IN_Pin GPIO_PIN_5
#define SONAR2_IN_GPIO_Port GPIOA
#define LIGHT_SENSOR0_Pin GPIO_PIN_0
#define LIGHT_SENSOR0_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
