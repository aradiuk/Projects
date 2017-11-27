/**
  ******************************************************************************
  * File Name          : main.c
  * Description        : Main program body
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2017 STMicroelectronics
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
#include "main.h"
#include "stm32f3xx_hal.h"
#include "usart.h"
#include "gpio.h"
#include <string.h>
#include <stdlib.h>

/* USER CODE BEGIN Includes */

#define MINIMAL_COMMAND "set interval=0"
#define MINIMAL_DELAY 10
#define NUM_LEDS 8

/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/
uint16_t LEDS_1[8] = {GPIO_PIN_9, GPIO_PIN_10, GPIO_PIN_11, GPIO_PIN_12,
					GPIO_PIN_13, GPIO_PIN_14, GPIO_PIN_15, GPIO_PIN_8};

static int clockwise = 1;	//	1 - clockwise, 0 - counterclockwise
static int i = 0;
static int command_object = 0;
static int delay = 500;
volatile int pressed = 0;
volatile int command = 0;
volatile int pre_delay = 500;
volatile int pre_dir = 1;

volatile int Rx_indx = 0;
volatile char Rx_data[2] = {0};
volatile char Rx_buffer[256] = {0};
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

void null_all_leds()
{
	int i = 0;

	while (i < NUM_LEDS)
	{
		HAL_GPIO_WritePin(GPIOE, LEDS_1[i], GPIO_PIN_RESET);
		++i;
	}
}

int check_set(char Rx_buffer[])
{
	char set[4] = {0};
	int i;

	/*
	 *	Read first four bytes and check if
	 *	they are equal to 'set '. Return 1 if not.
	 */
	i = 0;
	while (i < sizeof(set))
	{
		set[i] = Rx_buffer[i];
		++i;
	}
	if (strncmp(set, "set ", sizeof(set)))
		return (1);
	else
		return (0);
}

int check_object(char Rx_buffer[])
{
	char object[10] = {0};
	int	obj_len;
	int i;
	int set_len;

	/*
	 *	Read first ten bytes, starting after 'set '
	 *	and check if they are equal 'interval=' or
	 *	'direction='. Return 1 if not.
	 */
	i = 0;
	set_len = strlen("set ");
	obj_len = sizeof(object);
	while (i < obj_len)
	{
		object[i] = Rx_buffer[i + set_len];

			//	'interval=' has length equal nine, so we should check it here.
		if (i == 8)
		{
			if (strncmp(object, "interval=", obj_len - 1) == 0)
			{
				command_object = 2;
				return (0);
			}
		}
		++i;
	}
	if (strncmp(object, "direction=", obj_len))
		return (1);
	else
	{
		command_object = 1;
		return (0);
	}
}

int check_value(char Rx_buffer[], int len)
{
	char value_str[6] = {0};
	int	value;
	int i;
	int j;

	/*
	 * Iterate through buffer until '=' is found
	 */
	i = 0;
	j = 0;
	while (i < len && Rx_buffer[i] != '=')		//	Stops on '='
		++i;
	++i;

	/*
	 *	Read first six bytes, starting after the '=' sign
	 *	and check if they are equal 'left'/'right' or a
	 *	valid number, depending on what parameter we are
	 *	changing.
	 */
	while (i + j < len)
	{
		if (j > sizeof(value))			//	If value is longer, than allowed
			return (1);
		value_str[j] = Rx_buffer[i + j];
		++j;
	}
	if (command_object == 1)
	{
		if (strcmp(value_str, "left") == 0)
			pre_dir = 0;
		else if (strcmp(value_str, "right") == 0)
			pre_dir = 1;
		else
			return (1);
	}
	else if (command_object == 2)
	{
		value = atoi(value_str);

		if (value < MINIMAL_DELAY)
			return (1);
		pre_delay = value;
	}
	return (0);

}

int check_command(char Rx_buffer[])
{
	int len = strlen(Rx_buffer);

	/*
	 *	Check different parts of command for validity.
	 *	If all parts are valid, set 'command' to 1 and
	 *	return 0.
	 */
	if (len < strlen(MINIMAL_COMMAND))
		return (1);
	if (check_set(Rx_buffer))
		return (1);
	if (check_object(Rx_buffer))
		return (1);
	if (check_value(Rx_buffer, len))
		return (1);

	command = 1;
	return (0);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	int i;
	volatile HAL_StatusTypeDef Tx_status = HAL_OK;

	if (huart->Instance == UART4)
	{
			//	Clear buffer before each command
		if (Rx_indx == 0)
		{
			for (i = 0; i < sizeof(Rx_buffer); ++i)
				Rx_buffer[i] = 0;
		}

		/*
		 *	Read bytes until '\r' is read, write them into
		 *	buffer and send back. When '\r' is read check
		 *	whole command for validity and send appropriate
		 *	message.
		 */
		if (Rx_indx == 0 && Rx_data[0] == '\r')
		{
			HAL_UART_Transmit_IT(huart, "\r\n> ", 4);
		}
		else if (Rx_data[0] != '\r' && Rx_indx >= 0)
		{
			if (Rx_indx > 0 && Rx_data[0] == '\b' && Rx_indx < sizeof(Rx_buffer))
			{
				--Rx_indx;

				Rx_buffer[Rx_indx] = 0;
				do
				{
					HAL_UART_AbortTransmit_IT(huart);
					Tx_status = HAL_UART_Transmit_IT(huart, "\b \b", 3);
				}while (Tx_status != HAL_OK);

			}
			else if (Rx_indx < sizeof(Rx_buffer) - 1 && Rx_data[0] != '\b')
			{
				Rx_buffer[Rx_indx] = Rx_data[0];
				++Rx_indx;

				do
				{
					HAL_UART_AbortTransmit_IT(huart);
					Tx_status = HAL_UART_Transmit_IT(huart, Rx_data, 1);
				}while (Tx_status != HAL_OK);
			}
		}
		else
		{
			Rx_indx = 0;
			if (check_command(Rx_buffer))
			{
				HAL_UART_Transmit_IT(huart, "\r\nError\r\n> ", 11);
			}
			else
			{
				HAL_UART_Transmit_IT(huart, "\r\nOK\r\n> ", 8);
			}
		}
		HAL_UART_Receive_IT(huart, Rx_data, 1);
	}
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if (GPIO_Pin == GPIO_PIN_0)
	{
		pressed = !pressed;
	}
}

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

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
  MX_UART4_Init();

  /* USER CODE BEGIN 2 */

  HAL_UART_Transmit_IT(&huart4, "\r\n> ", 4);
  HAL_UART_Receive_IT(&huart4, Rx_data, 1);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */

	  if (pressed == 1 || command == 1)
	  {
		  null_all_leds();			//	Set all LED's to 'RESET' state
		  i = 0;				//	Start from the first LED

		  if (pressed == 1)			//	Change direction on button press
			  clockwise = !clockwise;
		  else if (command == 1)		//	Command received (not button)
		  {
			  if (command_object == 1)	//	direction command
				  clockwise = pre_dir;
			  else				//	interval command
				  delay = pre_delay;
		  }
		  pressed = 0;
		  command = 0;
	  }

	  HAL_GPIO_TogglePin(GPIOE, LEDS_1[i]);
	  HAL_Delay(delay);

	  /*	If LEDS are moving clockwise = 1 - set i to 0 if
	   * 	i points on the last LED in array, otherwise - add 1.
	   * 	If LEDS are moving counterclockwise (clockwise = 0) -
	   * 	set i to last LED in array if i equals 0, else - subtract 1.
	   */
	  if (i == (NUM_LEDS - 1) * clockwise)
		  i = (NUM_LEDS - 1) * (1 - clockwise);
	  else
		  i = (i + 1) * clockwise + (i - 1) * (1 - clockwise);
  }
  /* USER CODE END 3 */
}


/** System Clock Configuration
*/
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_PeriphCLKInitTypeDef PeriphClkInit;

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_UART4;
  PeriphClkInit.Uart4ClockSelection = RCC_UART4CLKSOURCE_SYSCLK;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void _Error_Handler(char * file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1) 
  {
  }
  /* USER CODE END Error_Handler_Debug */ 
}

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
