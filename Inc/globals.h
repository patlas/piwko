#ifndef __GLOBALS_H__
#define __GLOBALS_H__

#include "FreeRTOS.h"
#include "queue.h"

extern QueueHandle_t keyQueue;

typedef enum{
 NO_KEY=0,
 KEY_DN,
 KEY_UP,	
 KEY_L,			
 KEY_R,		
 KEY_OK
} Key_t;	

#endif