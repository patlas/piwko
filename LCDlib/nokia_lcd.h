/*
 * nokia_lcd.h
 *
 *  Created on: Nov 9, 2010
 *      Author: Automatyk
 */

#ifndef NOKIA_LCD_H_
#define NOKIA_LCD_H_

//#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal.h"
#include "delay_port.h"
//definicja portu
#define PORT_DISP_NOKIA 			GPIOA
#define RCC_APB2Periph_DISP_NOKIA 	RCC_APB2Periph_GPIOA
//definicja linii portu
#define CLK 		GPIO_PIN_0  //CLK PA0
#define DATA 		GPIO_PIN_1 //DATA PA1
#define DC 			GPIO_PIN_2   //D_nC PA2
#define RES 		GPIO_PIN_4  //RESET PA3
#define SCE 		GPIO_PIN_3  //SCE PA4
#define LCD_PWR		GPIO_PIN_7
#define LCD_BKLT	GPIO_PIN_9

#define NULL                       0
#define False                      0
#define True                       1

#define FONT_POSITIVE	0
#define FONT_NEGATIVE	1

#define LCD_X_RES                  84
#define LCD_Y_RES                  48


//#define LCD_CACHE_SIZE             ((LCD_X_RES * LCD_Y_RES) / 8)
#define LCD_CACHE_SIZE             604

#define TRUE	0
#define FALSE	1


typedef enum
{
    LCD_CMD  = 0,
    LCD_DATA = 1

} LcdCmdData;

typedef enum
{
    PIXEL_OFF =  0,
    PIXEL_ON  =  1,
    PIXEL_XOR =  2

} LcdPixelMode;

typedef enum
{
    FONT_1X = 1,
    FONT_2X = 2

} LcdFontSize;

typedef enum
{
    TRANSPARENT =  0,
    CLEAR  =  1,
    FILL =  2

} LcdRectangleMode;
/*--------------------------------------------------------------------------------------------------
                                 Public function prototypes
--------------------------------------------------------------------------------------------------*/
void LcdInit       	( void );
void LcdClear      	( void );
void LcdUpdate     	( void );
void LcdGotoXY     	( unsigned char x, unsigned char y );
void LcdGotoSmallXY	( unsigned char x, unsigned char y );
void LcdChr        	( LcdFontSize size,unsigned char negative, unsigned char ch );
void LcdSmallChr   	( unsigned char negative,unsigned char ch );
void LcdStr        	( LcdFontSize size, unsigned char negative, unsigned char *dataPtr );
void LcdPixel      	( unsigned char x, unsigned char y, LcdPixelMode mode );
void LcdLine       	( unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2, LcdPixelMode mode );
void LcdClearArea	(unsigned char line, unsigned char startX, unsigned char endX);
void LcdClearLine	(unsigned char line);
void LcdFillLine	(unsigned char line);
void LcdRectangle	(unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2, LcdRectangleMode mode);
void LcdVerticalScrollBar(unsigned char percentage, unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2);


void WriteSPI(unsigned char data);
void ClrBit(int bits);
void SetBit(int bits);
void WriteData(unsigned char data);
void WriteCmd(unsigned char data);

void Delay(unsigned int wait);

#endif /* NOKIA_LCD_H_ */
