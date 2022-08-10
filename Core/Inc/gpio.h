/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.h
  * @brief   This file contains all the function prototypes for
  *          the gpio.c file
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
#ifndef __GPIO_H__
#define __GPIO_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* USER CODE BEGIN Private defines */

#define I2C_SCL_Pin             GPIO_PIN_4
#define I2C_SCL_GPIO_Port        GPIOA




#define MOTOR_CCW_Pin                   GPIO_PIN_14
#define MOTOR_CCW_GPIO_Port             GPIOC

#define MOTOR_CW_Pin                    GPIO_PIN_15
#define MOTOR_CW_GPIO_Port              GPIOC

#define BAT_VOL_Pin                     GPIO_PIN_0
#define BAT_VOL_GPIO_Port               GPIOA

#define LOW_LED_Pin                     GPIO_PIN_1
#define LOW_LED_GPIO_Port               GPIOA

#define OK_LED_Pin                      GPIO_PIN_2
#define OK_LED_GPIO_Port                GPIOA

#define ERR_LED_Pin                     GPIO_PIN_3
#define ERR_LED_GPIO_Port               GPIOA



#define BEEP_Pin                        GPIO_PIN_6
#define BEEP_GPIO_Port                  GPIOA

#define LED2_Pin                        GPIO_PIN_7   //blacklight 2
#define LED2_GPIO_Port                  GPIOA

#define LED1_Pin                        GPIO_PIN_1  //blacklight 
#define LED1_GPIO_Port                  GPIOB

#define SC12B_KEY_Pin                   GPIO_PIN_9
#define SC12B_KEY_GPIO_Port             GPIOA
#define SC12B_KEY_EXTI_IRQn             EXTI4_15_IRQn


#define KEY_Pin                         GPIO_PIN_5
#define KEY_GPIO_Port                   GPIOA
#define KEY_EXTI_IRQn                   EXTI4_15_IRQn


/* USER CODE END Private defines */

void MX_GPIO_Init(void);

/* USER CODE BEGIN Prototypes */

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ GPIO_H__ */

