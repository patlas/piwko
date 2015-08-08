/**
  ******************************************************************************
  * File Name          : main.c
  * Date               : 26/05/2015 22:39:39
  * Description        : Main program body
  ******************************************************************************
  *
  * COPYRIGHT(c) 2015 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"
#include "spi.h"
#include "tim.h"
#include "gpio.h"

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "semphr.h"

/* USER CODE BEGIN Includes */
#include "task_LCD.h"
#include "nokia_lcd.h"

#include "globals.h"



/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/

QueueHandle_t keyQueue;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);

/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

void Blink( void * pvParameters )
{
  for( ;; )
  {
      HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_8);
			vTaskDelay(300);
  }
}

void Blink2( void * pvParameters )
{
  for( ;; )
  {
      HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_9);
			vTaskDelay(500);
  }
}


Key_t getkey(void){
	Key_t key = NO_KEY;
	
	if(pdTRUE != xQueueReceive(keyQueue,&key,100))
		key = NO_KEY;
	
	return key;
}


int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  //MX_SPI1_Init();
  MX_TIM1_Init();

  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */
	//HAL_GPIO_WritePin(GPIOC,GPIO_PIN_8,GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_9,GPIO_PIN_SET);
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	
	keyQueue = xQueueCreate(3,sizeof(Key_t));
	
	
	
	xTaskCreate( Blink, "NAME", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY,NULL);
	xTaskCreate( Blink2, "NAME2", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY,NULL);
	//xTaskCreate( task_LCD, "LCD", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY,NULL);
	xTaskCreate( task_MENU, "MENU", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY,NULL);

	vTaskStartScheduler();
	
  while (1)
  {
  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */

  }
  /* USER CODE END 3 */

}

/** System Clock Configuration
*/
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL3;
  HAL_RCC_OscConfig(&RCC_OscInitStruct);

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_SYSCLK;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */

}

#endif

/**
  * @}
  */ 

/**
  * @}
*/ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/






Key_t getkey2(void)
{
	/*uint8_t key=NO_KEY;

	IWDG_ReloadCounter();							// reset watchdoga
	if(GPIO_ReadInputDataBit(JOY_PORT,JOY_U) == 0)	// nacisnieto przycisk UP
		{
			if(inc==increment_delay)				// przycisk jest "przytrzymywany"
				delay_ms(auto_repeat_period);						// czestotliwosc "autopowtarzania" przycisku
			while((GPIO_ReadInputDataBit(JOY_PORT,JOY_U) == 0) && (inc<increment_delay)) if(inc<increment_delay) inc++;
			delay_ms(50);
			key=KEY_UP;
		}
	else if(GPIO_ReadInputDataBit(JOY_PORT,JOY_D) == 0)	// nacisnieto przycisk DN
		{
			if(inc==increment_delay)
				delay_ms(auto_repeat_period);
			while((GPIO_ReadInputDataBit(JOY_PORT,JOY_D) == 0)&& (inc<increment_delay)) if(inc<increment_delay) inc++;
			delay_ms(50);
			key=KEY_DN;
		}
	else if(GPIO_ReadInputDataBit(JOY_PORT,JOY_L) == 0)	// nacisnieto przycisk LEFT
		{
			if(inc==increment_delay)
				delay_ms(auto_repeat_period);
			while((GPIO_ReadInputDataBit(JOY_PORT,JOY_L) == 0)&& (inc<increment_delay)) if(inc<increment_delay) inc++;
			delay_ms(50);
			key=KEY_L;
		}
	else if(GPIO_ReadInputDataBit(JOY_PORT,JOY_R) == 0)	// nacisnieto przycisk RIGHT
		{
			if(inc==increment_delay)
				delay_ms(auto_repeat_period);
			while((GPIO_ReadInputDataBit(JOY_PORT,JOY_R) == 0)&& (inc<increment_delay)) if(inc<increment_delay) inc++;
			delay_ms(50);
			key=KEY_R;
		}
	else if(GPIO_ReadInputDataBit(LED_PORT,JOY_OK) == 0)	// nacisnieto przycisk OK
		{
			while(GPIO_ReadInputDataBit(LED_PORT,JOY_OK) == 0) ;
			delay_ms(50);
			key=KEY_OK;
		}
	else
	{
		key=NO_KEY;
		inc=0;
	}
	return(key);*/
	return NO_KEY;
}
