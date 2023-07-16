/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
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

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "common_inc.h"
#include "my_task.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
osSemaphoreId elog_lockHandle;
osSemaphoreId elog_asyncHandle;
osThreadId_t easylogTaskHandle;
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
/* Definitions for led_task */
osThreadId_t led_taskHandle;
const osThreadAttr_t led_task_attributes = {
  .name = "led_task",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for elogTask */
osThreadId_t elogTaskHandle;
const osThreadAttr_t elogTask_attributes = {
  .name = "elogTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void LED_TASK(void *argument);
void ThreadElog(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
    /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
    /* add semaphores, ... */
    osSemaphoreDef(elog_lockHandle);
    elog_lockHandle = osSemaphoreNew(1, 1, osSemaphore(elog_lockHandle));

    osSemaphoreDef(elog_asyncHandle);
    elog_asyncHandle = osSemaphoreNew(1, 1, osSemaphore(elog_asyncHandle));
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
    /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
    /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of led_task */
  led_taskHandle = osThreadNew(LED_TASK, NULL, &led_task_attributes);

  /* creation of elogTask */
  elogTaskHandle = osThreadNew(ThreadElog, NULL, &elogTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
    /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
    /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_LED_TASK */
/**
  * @brief  Function implementing the led_task thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_LED_TASK */
void LED_TASK(void *argument)
{
  /* USER CODE BEGIN LED_TASK */
    log_i ("hello! you can use elog!");
    /* Infinite loop */
    for(;;)
    {
        my_task();
    }
  /* USER CODE END LED_TASK */
}

/* USER CODE BEGIN Header_ThreadElog */
/**
* @brief Function implementing the elogTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_ThreadElog */
//void ThreadElog(void *argument)
//{
//  /* USER CODE BEGIN ThreadElog */
//////////  /* Infinite loop */
//////////  for(;;)
//////////  {
//////////    osDelay(1);
//////////  }
//  /* USER CODE END ThreadElog */
//}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

