#ifndef REF_COMMON_INC_H
#define REF_COMMON_INC_H


/*---------------------------- C Scope ---------------------------*/
#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include "main.h"
#include "FreeRTOS.h"
#include "task.h"
//#include "time_utils.h"
//#include "st_hardware.h"
//#include "i2c.h"
//#include "adc.h"
//#include "can.h"
#include "elog.h"
#include "cmsis_os2.h"


extern uint64_t serialNumber;
extern bool usbReady;


void Main(void);
void ErrorHandler(void);


#ifdef __cplusplus
}

/*---------------------------- C++ Scope ---------------------------*/
//#include "random_flash_interface.h"
//#include "timer.h"
#include "peripherals.h"
//#include "analog.h"
//#include "U8g2lib.hpp"


// Universal Board Configs definition
enum configStatus_t
{
    CONFIG_RESTORE = 0,
    CONFIG_OK,
    CONFIG_COMMIT
};

struct BoardConfig_t
{
    configStatus_t configStatus;
    uint8_t volumeId;
} ;

extern BoardConfig_t boardConfig;
//extern Analog analog;


//void HomeScreen(U8G2* screen);

#endif
#endif
