#include "delay_port.h"

void delay_ms(TickType_t ms){
	
	TickType_t xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount();

	vTaskDelayUntil( &xLastWakeTime, ms );

}
