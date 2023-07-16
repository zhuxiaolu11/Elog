/*
 * This file is part of the EasyLogger Library.
 *
 * Copyright (c) 2015, Armink, <armink.ztl@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * 'Software'), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * Function: Portable interface for each platform.
 * Created on: 2015-04-28
 */
 
#include <elog.h>
#include <stdio.h>
#include "string.h"
#include "cmsis_os2.h"
#include "freertos_inc.h"
#include "usart.h"

/**
 * EasyLogger port initialize
 *
 * @return result
 */
ElogErrCode elog_port_init(void)
{
    ElogErrCode result = ELOG_NO_ERR;

    if(elog_lockHandle != NULL)
    osSemaphoreRelease(elog_lockHandle);

    /* add your code here */

    return result;
}

/**
 * EasyLogger port deinitialize
 *
 */
void elog_port_deinit(void)
{

    /* add your code here */
}

/**
 * output log port interface
 *
 * @param log output of log
 * @param size log size
 */
void elog_port_output(const char *log, size_t size)
{

    /* add your code here */
    //printf("%s", log);
    //CDC_Transmit_FS((uint8_t *)log, size);
    HAL_UART_Transmit(&huart2, (uint8_t *)log, size, 0xffff);
//    memcpy(usart6TxBuffer,log,size);
//    SCB_InvalidateDCache_by_Addr ((uint32_t *)usart6TxBuffer, TX_BUFFER_SIZE);
//    HAL_UART_Transmit_DMA(&huart6,usart6TxBuffer,size);
}

/**
 * output lock
 */
void elog_port_output_lock(void)
{

    /* add your code here */
    osSemaphoreAcquire(elog_lockHandle, osWaitForever);
}

/**
 * output unlock
 */
void elog_port_output_unlock(void)
{

    /* add your code here */
    osSemaphoreRelease(elog_lockHandle);
}

/**
 * get current time interface
 *
 * @return current time
 */
const char *elog_port_get_time(void)
{

    /* add your code here */
    return "10:08:12";
}

/**
 * get current process name interface
 *
 * @return current process name
 */
const char *elog_port_get_p_info(void)
{

    /* add your code here */
    return "pid:1008";
}

/**
 * get current thread name interface
 *
 * @return current thread name
 */
const char *elog_port_get_t_info(void)
{

    /* add your code here */
    return "tid:24";
}

void elog_async_output_notice(void)
{
    osSemaphoreRelease(elog_asyncHandle);
}

void ThreadElog(void *argument)
{
    size_t get_log_size = 0;
    static char poll_get_buf[ELOG_LINE_BUF_SIZE - 4];

    if (elog_port_init() != ELOG_NO_ERR)
    {
        goto fail;
    }

    while (1)
    {
        if (osOK == osSemaphoreAcquire(elog_asyncHandle, osWaitForever))
        {
            while (1)
            {
                #ifdef ELOG_ASYNC_LINE_OUTPUT
                get_log_size = elog_async_get_line_log(poll_get_buf, sizeof(poll_get_buf));
                #else
                get_log_size = elog_async_get_log(poll_get_buf, sizeof(poll_get_buf));
                #endif

                if (get_log_size)
                {
                    elog_port_output(poll_get_buf, get_log_size);
                }else{
                    break;
                }
            }
        }
    }

fail:
    osThreadTerminate(NULL);
}