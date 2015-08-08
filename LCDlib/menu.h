/*
 * menu.h
 *
 *  Created on: Nov 12, 2010
 *      Author: Automatyk
 */

#ifndef MENU_H_
#define MENU_H_


#include <stddef.h>
//#include "stm32f10x.h"
#include "nokia_lcd.h"
#include <string.h>
#include <stdio.h>
#include "delay_port.h"
#include "globals.h"

extern void delay_ms(uint32_t time);

void menu(void);
void show_menu(uint8_t menu_no, uint8_t submenu_no);
void enter_menu(uint8_t menu_no, uint8_t submenu_no);
void exit_from_menu(void);

void graphic_menu(void);
void show_graphic_menu(uint8_t menu_no, uint8_t submenu_no);
void enter_graphic_menu(uint8_t menu_no, uint8_t submenu_no);
void exit_from_graphic_menu(void);

void slide_down(void);
void slide_up(void);

int16_t enter_integer(int16_t val, int16_t min, int16_t max, uint8_t x, uint8_t y, char *var_name, char *var_unit);

extern Key_t getkey(void);

//////////////////////////////////////////////////////////////////////
// WAZNE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!  //
// adresowanie tablicy menu_strings w postaci [submenu][menu]       //
// czyli troche na odwrot                                           //
//////////////////////////////////////////////////////////////////////

static const char *menu_strings[9][8]={				// menu_strings[submenu, menu]
		{"MENU1", "MENU2", "MENU3","MENU4","MENU5","MENU6","MENU7","MENU8"},
		{"MENU1.1", "MENU2.1", "MENU3.1","","","MENU6.1","",""},
		{"MENU1.2","MENU2.2", "MENU3.2","","","","",""},
		{"MENU1.3","","","","","","",""},
		{"MENU1.4","","","","","","",""},
		{"MENU1.5","","","","","","",""},
		{"MENU1.6","","","","","","",""},
		{"MENU1.7","","","","","","",""},
		{"MENU1.8","","","","","","",""}
};


#endif /* MENU_H_ */
