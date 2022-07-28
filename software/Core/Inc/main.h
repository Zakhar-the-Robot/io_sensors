/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
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
#define BUTTON_BLUE_Pin GPIO_PIN_13
#define BUTTON_BLUE_GPIO_Port GPIOC
#define USART_TX_D1_Pin GPIO_PIN_2
#define USART_TX_D1_GPIO_Port GPIOA
#define USART_RX_D0_Pin GPIO_PIN_3
#define USART_RX_D0_GPIO_Port GPIOA
#define LED_GREEN_D13_Pin GPIO_PIN_5
#define LED_GREEN_D13_GPIO_Port GPIOA
#define CAN_CS_Pin GPIO_PIN_6
#define CAN_CS_GPIO_Port GPIOA
#define SON_TRIG_R_D11_Pin GPIO_PIN_7
#define SON_TRIG_R_D11_GPIO_Port GPIOA
#define PHOTORES_NUCLEO_A3_Pin GPIO_PIN_0
#define PHOTORES_NUCLEO_A3_GPIO_Port GPIOB
#define SON_ECHO_C_D6_Pin GPIO_PIN_10
#define SON_ECHO_C_D6_GPIO_Port GPIOB
#define SON_TRIG_C_D7_Pin GPIO_PIN_8
#define SON_TRIG_C_D7_GPIO_Port GPIOA
#define USART1_TX_D8_Pin GPIO_PIN_9
#define USART1_TX_D8_GPIO_Port GPIOA
#define USART1_RX_D2_Pin GPIO_PIN_10
#define USART1_RX_D2_GPIO_Port GPIOA
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA
#define SWO_Pin GPIO_PIN_3
#define SWO_GPIO_Port GPIOB
#define SON_TRIG_L_D5_Pin GPIO_PIN_4
#define SON_TRIG_L_D5_GPIO_Port GPIOB
#define SON_ECHO_L_D4_Pin GPIO_PIN_5
#define SON_ECHO_L_D4_GPIO_Port GPIOB
#define SON_ECHO_R_D10_Pin GPIO_PIN_6
#define SON_ECHO_R_D10_GPIO_Port GPIOB
#define I2C1_SCL_D15_Pin GPIO_PIN_8
#define I2C1_SCL_D15_GPIO_Port GPIOB
#define I2C1_SDA_D14_Pin GPIO_PIN_9
#define I2C1_SDA_D14_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
