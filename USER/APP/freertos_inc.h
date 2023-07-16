#ifndef __FREERTOS_H
#define __FREERTOS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "FreeRTOS.h"
#include "cmsis_os.h"
#include "cmsis_os2.h"
#include "portmacro.h"
#include "task.h"


// List of semaphores
extern osSemaphoreId semCan1Tx;
extern osSemaphoreId semCan2Tx;

extern osSemaphoreId elog_lockHandle;
extern osSemaphoreId elog_asyncHandle;


// List of Tasks
/*--------------------------------- System Tasks -------------------------------------*/
extern osThreadId_t defaultTaskHandle;

/*---------------------------------- User Tasks --------------------------------------*/
extern osThreadId_t usbTaskHandle;
extern osThreadId_t tick1kHzRealtimeTaskHandle;
extern osThreadId_t tickTaskHandle;
extern osThreadId_t oledTaskHandle;
extern osThreadId_t buzzerTaskHandle;
extern osThreadId_t periphTaskHandle;
extern osThreadId_t easylogTaskHandle;


#ifdef __cplusplus
}
#endif

#endif