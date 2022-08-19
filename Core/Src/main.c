/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "iwdg.h"
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "run.h"
#include "led.h"
#include "touchkey.h"
#include "motor.h"
#include "buzzer.h"
#include "key.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
 uint16_t KeyValue,sidekey;
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
  //  uint16_t KeyValue;
   uint8_t i;
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */
   
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_ADC_Init();
 // MX_IWDG_Init();
 ICman_Init_SET(SC12B_ADDR);
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
  HAL_TIM_Base_Start_IT(&htim2);//
 
 // HAL_TIM_Base_Start(&htim2);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
     
      
  #if 1
    
      
       if(run_t.powerOn ==0){
          
                run_t.powerOn++;
               run_t.passwordsMatch =0;
               run_t.password_unlock =2;
               run_t.unLock_times=1;
               run_t.gTimer_2s=0;
			   run_t.lowPower_flag=0; //low power flag
  			  POWER_ON();
           
         } 
      
       sidekey = Scan_Key();
       if(sidekey == 0x01){
               
			if(run_t.powerOn ==1 || run_t.powerOn==0){
			    run_t.powerOn=2;
			   run_t.factory_test = 1;
			  run_t.gTimer_60s =0;
			  run_t.buzzer_flag =1;
			  POWER_ON();
			   
		   }
           else{
			  run_t.retimes =0;
			  run_t.gTimer_8s=0;
		   	 run_t.buzzer_flag =1;
		     run_t.getKey = 0x01; // return 0x01;  //long key occur
		  }
      }
      if(sidekey== 0x81){

        run_t.clearEeprom = 1;
        POWER_ON();

      }

	 if(run_t.passwordsMatch==0 && run_t.panel_lock==0){
		if(I2C_Read_From_Device(SC12B_ADDR,0x08,SC_Data,2)==DONE){
        // if(I2C_Simple_Read_From_Device(SC12B_ADDR,SC_Data,2) ==DONE){
			KeyValue =(uint16_t)(SC_Data[0]<<8) + SC_Data[1];
			RunCheck_Mode(KeyValue); 
            if(KeyValue ==0){

				run_t.SpecialKey_pressedNumbers=0;
				run_t.SpecialKey_pressedNumbers_2=0;
			    run_t.NumbersKey_pressedNumbers = 0;
				run_t.getSpecial_1_key++;
				run_t.getSpecial_2_key++;
				run_t.getNumbers_key=0x40;


            }
			  
			}
		}
		 
	    if(run_t.passwordsMatch ==1 && run_t.adminiId !=1){
		  
		  run_t.passwordsMatch=0;
          run_t.gTimer_8s=0;
          RunCommand_Unlock();
            
	  }
	  if(run_t.password_unlock==2){ //lock turn on Open 
	       run_t.gTimer_8s =0;
		  //set up flag permit to save data to EEPROM
		  if(run_t.getKey == 0x01 ){
			   run_t.getKey = 0;
			  run_t.Confirm_newPassword = 1;
			  run_t.Numbers_counter=0;
			  run_t.unLock_times =0;
			  run_t.retimes =0;
			  run_t.BackLight =1;
			  for(i=0;i<6;i++){ //WT.EDIT .2022.08.13
				   pwd2[i]=0;
			
			  	   pwd1[i]=0;
			
			    }
			  
		  }
		  //To save data to EEPROM
		  if(run_t.Confirm_newPassword ==1 && run_t.adminiId==1){
			 run_t.gTimer_8s=0;
			 SavePassword_To_EEPROM();
			  
			  
		  }
		  //return to home position
		  if(run_t.unLock_times==1 && run_t.adminiId==0){ //if(run_t.gTimer_2s ==2 && run_t.unLock_times==1 && run_t.Confirm == 0){
                   run_t.gTimer_8s =0;
				   POWER_ON();
				   if(run_t.gTimer_2s > 2){
				   	   run_t.powerOn=2;
					   Motor_CW_Run();// Close 
					   HAL_Delay(2120);//2010//(815);
					   Motor_Stop();
					   run_t.unLock_times =0;
					   for(i=0;i<6;i++){ //WT.EDIT .2022.08.13
						  
					       pwd1[i]=0;
						   Readpwd[i]=0;
					   }

					  run_t.unLock_times=0;//WT.EDIT 2022.08.18
					  run_t.password_unlock=0;
                   }

			
				  
			  }
  
		  }
	  
		 
		  DispLed_Fun();
         #endif 
      }
  
	
  
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_LSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLLMUL_3;
  RCC_OscInitStruct.PLL.PLLDIV = RCC_PLLDIV_2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
