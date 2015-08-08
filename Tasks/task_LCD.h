#ifndef __TASK_LCD_H__
#define __TASK_LCD_H__

#include "FreeRTOS.h"
#include "task.h"
#include "nokia_lcd.h"
#include "globals.h"
#include "menu.h"

void task_LCD(void *);
void task_MENU(void *);




#endif
