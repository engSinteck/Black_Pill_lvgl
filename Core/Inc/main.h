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
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */
#define TRUE		1
#define FALSE		0
/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LED_Pin GPIO_PIN_13
#define LED_GPIO_Port GPIOC
#define BT_USER_Pin GPIO_PIN_0
#define BT_USER_GPIO_Port GPIOA
#define ZERO_CROSS_Pin GPIO_PIN_1
#define ZERO_CROSS_GPIO_Port GPIOA
#define DIMMER_1_Pin GPIO_PIN_2
#define DIMMER_1_GPIO_Port GPIOA
#define DIMMER_2_Pin GPIO_PIN_3
#define DIMMER_2_GPIO_Port GPIOA
#define FLASH_CS_Pin GPIO_PIN_4
#define FLASH_CS_GPIO_Port GPIOA
#define MAX6675_Pin GPIO_PIN_0
#define MAX6675_GPIO_Port GPIOB
#define ADC_ALERT_Pin GPIO_PIN_1
#define ADC_ALERT_GPIO_Port GPIOB
#define TFT_RST_Pin GPIO_PIN_2
#define TFT_RST_GPIO_Port GPIOB
#define TFT_DC_Pin GPIO_PIN_10
#define TFT_DC_GPIO_Port GPIOB
#define TFT_CS_Pin GPIO_PIN_12
#define TFT_CS_GPIO_Port GPIOB
#define TFT_SCK_Pin GPIO_PIN_13
#define TFT_SCK_GPIO_Port GPIOB
#define TFT_MISO_Pin GPIO_PIN_14
#define TFT_MISO_GPIO_Port GPIOB
#define TFT_MOSI_Pin GPIO_PIN_15
#define TFT_MOSI_GPIO_Port GPIOB
#define RELAY_Pin GPIO_PIN_15
#define RELAY_GPIO_Port GPIOA
#define TOUCH_CS_Pin GPIO_PIN_3
#define TOUCH_CS_GPIO_Port GPIOB
#define PWM_IRON_Pin GPIO_PIN_4
#define PWM_IRON_GPIO_Port GPIOB
#define PWM_TFT_Pin GPIO_PIN_5
#define PWM_TFT_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
