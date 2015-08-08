/*
 * nokia_lcd.c
 *
 *  Created on: Nov 9, 2010
 *      Author: Automatyk
 */

//programowa realizacja SPI
#include "nokia_lcd.h"
#include <stddef.h>
//#include "stm32f10x.h"

unsigned char SmallFontLookup[][3] =
{
{0x1E,0x21,0x1E}, //0/ --> 0
{0x22,0x3F,0x20}, //1/ --> 1
{0x32,0x29,0x26}, //2/ --> 2
{0x21,0x25,0x1A}, //3/ --> 3
{0x0C,0x0A,0x3F}, //4/ --> 4
{0x27,0x25,0x19}, //5/ --> 5
{0x1E,0x25,0x19}, //6/ --> 6
{0x39,0x05,0x03}, //7/ --> 7
{0x1A,0x25,0x1A}, //8/ --> 8
{0x26,0x29,0x1E}, //9/ --> 9
{0x02,0x05,0x02}, //10/ --> st
{0x30,0x30,0x00}, //11/ --> .
{0x3F,0x04,0x3F}, //12/ --> N
{0x22,0x25,0x19}, //13/ --> S
{0x3F,0x25,0x21}, //14/ --> E
{0x1F,0x3C,0x1F} //15/ --> W
};



/*--------------------------------------------------------------------------------------------------
                                     Character generator

             This table defines the standard ASCII characters in a 5x7 dot format.
--------------------------------------------------------------------------------------------------*/
unsigned char FontLookup [][5] =
{
    { 0x00, 0x00, 0x00, 0x00, 0x00 },   // sp
    { 0x00, 0x00, 0x2f, 0x00, 0x00 },   // !
    { 0x00, 0x07, 0x00, 0x07, 0x00 },   // "
    { 0x14, 0x7f, 0x14, 0x7f, 0x14 },   // #
    { 0x24, 0x2a, 0x7f, 0x2a, 0x12 },   // $
    { 0xc4, 0xc8, 0x10, 0x26, 0x46 },   // %
    { 0x36, 0x49, 0x55, 0x22, 0x50 },   // &
    { 0x00, 0x05, 0x03, 0x00, 0x00 },   // '
    { 0x00, 0x1c, 0x22, 0x41, 0x00 },   // (
    { 0x00, 0x41, 0x22, 0x1c, 0x00 },   // )
    { 0x14, 0x08, 0x3E, 0x08, 0x14 },   // *
    { 0x08, 0x08, 0x3E, 0x08, 0x08 },   // +
    { 0x00, 0x00, 0x50, 0x30, 0x00 },   // ,
    { 0x10, 0x10, 0x10, 0x10, 0x10 },   // -
    { 0x00, 0x60, 0x60, 0x00, 0x00 },   // .
    { 0x20, 0x10, 0x08, 0x04, 0x02 },   // /
    { 0x3E, 0x51, 0x49, 0x45, 0x3E },   // 0
    { 0x00, 0x42, 0x7F, 0x40, 0x00 },   // 1
    { 0x42, 0x61, 0x51, 0x49, 0x46 },   // 2
    { 0x21, 0x41, 0x45, 0x4B, 0x31 },   // 3
    { 0x18, 0x14, 0x12, 0x7F, 0x10 },   // 4
    { 0x27, 0x45, 0x45, 0x45, 0x39 },   // 5
    { 0x3C, 0x4A, 0x49, 0x49, 0x30 },   // 6
    { 0x01, 0x71, 0x09, 0x05, 0x03 },   // 7
    { 0x36, 0x49, 0x49, 0x49, 0x36 },   // 8
    { 0x06, 0x49, 0x49, 0x29, 0x1E },   // 9
    { 0x00, 0x36, 0x36, 0x00, 0x00 },   // :
    { 0x00, 0x56, 0x36, 0x00, 0x00 },   // ;
    { 0x08, 0x14, 0x22, 0x41, 0x00 },   // <
    { 0x14, 0x14, 0x14, 0x14, 0x14 },   // =
    { 0x00, 0x41, 0x22, 0x14, 0x08 },   // >
    { 0x02, 0x01, 0x51, 0x09, 0x06 },   // ?
    { 0x32, 0x49, 0x59, 0x51, 0x3E },   // @
    { 0x7E, 0x11, 0x11, 0x11, 0x7E },   // A
    { 0x7F, 0x49, 0x49, 0x49, 0x36 },   // B
    { 0x3E, 0x41, 0x41, 0x41, 0x22 },   // C
    { 0x7F, 0x41, 0x41, 0x22, 0x1C },   // D
    { 0x7F, 0x49, 0x49, 0x49, 0x41 },   // E
    { 0x7F, 0x09, 0x09, 0x09, 0x01 },   // F
    { 0x3E, 0x41, 0x49, 0x49, 0x7A },   // G
    { 0x7F, 0x08, 0x08, 0x08, 0x7F },   // H
    { 0x00, 0x41, 0x7F, 0x41, 0x00 },   // I
    { 0x20, 0x40, 0x41, 0x3F, 0x01 },   // J
    { 0x7F, 0x08, 0x14, 0x22, 0x41 },   // K
    { 0x7F, 0x40, 0x40, 0x40, 0x40 },   // L
    { 0x7F, 0x02, 0x0C, 0x02, 0x7F },   // M
    { 0x7F, 0x04, 0x08, 0x10, 0x7F },   // N
    { 0x3E, 0x41, 0x41, 0x41, 0x3E },   // O
    { 0x7F, 0x09, 0x09, 0x09, 0x06 },   // P
    { 0x3E, 0x41, 0x51, 0x21, 0x5E },   // Q
    { 0x7F, 0x09, 0x19, 0x29, 0x46 },   // R
    { 0x46, 0x49, 0x49, 0x49, 0x31 },   // S
    { 0x01, 0x01, 0x7F, 0x01, 0x01 },   // T
    { 0x3F, 0x40, 0x40, 0x40, 0x3F },   // U
    { 0x1F, 0x20, 0x40, 0x20, 0x1F },   // V
    { 0x3F, 0x40, 0x38, 0x40, 0x3F },   // W
    { 0x63, 0x14, 0x08, 0x14, 0x63 },   // X
    { 0x07, 0x08, 0x70, 0x08, 0x07 },   // Y
    { 0x61, 0x51, 0x49, 0x45, 0x43 },   // Z
    { 0x00, 0x7F, 0x41, 0x41, 0x00 },   // [
    { 0x55, 0x2A, 0x55, 0x2A, 0x55 },   // 55
    { 0x00, 0x41, 0x41, 0x7F, 0x00 },   // ]
    { 0x04, 0x02, 0x01, 0x02, 0x04 },   // ^
    { 0x40, 0x40, 0x40, 0x40, 0x40 },   // _
    { 0x00, 0x01, 0x02, 0x04, 0x00 },   // '
    { 0x20, 0x54, 0x54, 0x54, 0x78 },   // a
    { 0x7F, 0x48, 0x44, 0x44, 0x38 },   // b
    { 0x38, 0x44, 0x44, 0x44, 0x20 },   // c
    { 0x38, 0x44, 0x44, 0x48, 0x7F },   // d
    { 0x38, 0x54, 0x54, 0x54, 0x18 },   // e
    { 0x08, 0x7E, 0x09, 0x01, 0x02 },   // f
    { 0x0C, 0x52, 0x52, 0x52, 0x3E },   // g
    { 0x7F, 0x08, 0x04, 0x04, 0x78 },   // h
    { 0x00, 0x44, 0x7D, 0x40, 0x00 },   // i
    { 0x20, 0x40, 0x44, 0x3D, 0x00 },   // j
    { 0x7F, 0x10, 0x28, 0x44, 0x00 },   // k
    { 0x00, 0x41, 0x7F, 0x40, 0x00 },   // l
    { 0x7C, 0x04, 0x18, 0x04, 0x78 },   // m
    { 0x7C, 0x08, 0x04, 0x04, 0x78 },   // n
    { 0x38, 0x44, 0x44, 0x44, 0x38 },   // o
    { 0x7C, 0x14, 0x14, 0x14, 0x08 },   // p
    { 0x08, 0x14, 0x14, 0x18, 0x7C },   // q
    { 0x7C, 0x08, 0x04, 0x04, 0x08 },   // r
    { 0x48, 0x54, 0x54, 0x54, 0x20 },   // s
    { 0x04, 0x3F, 0x44, 0x40, 0x20 },   // t
    { 0x3C, 0x40, 0x40, 0x20, 0x7C },   // u
    { 0x1C, 0x20, 0x40, 0x20, 0x1C },   // v
    { 0x3C, 0x40, 0x30, 0x40, 0x3C },   // w
    { 0x44, 0x28, 0x10, 0x28, 0x44 },   // x
    { 0x0C, 0x50, 0x50, 0x50, 0x3C },   // y
    { 0x44, 0x64, 0x54, 0x4C, 0x44 },   // z
    { 0x00, 0x00, 0x07, 0x05, 0x07 },	//deg
    { 0x00, 0x00, 0x05, 0x03, 0x00 },
//    { 0xff, 0xff, 0xff, 0xff, 0xff },
    { 0xff, 0xff, 0xff, 0xff, 0xff },	// "bloczki" do progressbara
    { 0x14, 0x36, 0x77, 0x36, 0x14 },	// strzalki gora i dol
//    { 0x38, 0xe4, 0x26, 0xe4, 0x38 }
    { 0x1c, 0x27, 0x64, 0x27, 0x1c },	// "wtyczka" (przy podlaczonym zasilaczu
    { 0x07, 0x02, 0xff, 0x02, 0x07 },	// poszczegolne "beleczki" miernika ilosci satelitow
    { 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0xc0, 0x00, 0x00, 0x00, 0x00 },
    { 0xc0, 0xe0, 0x00, 0x00, 0x00 },
    { 0xc0, 0xe0, 0xf0, 0x00, 0x00 },
    { 0xc0, 0xe0, 0xf0, 0xf8, 0x00 },
    { 0xc0, 0xe0, 0xf0, 0xf8, 0xfc },
    { 0xc0, 0xe0, 0xf0, 0xf8, 0xfc },
    { 0xc0, 0xe0, 0xf0, 0xf8, 0xfc },
//    { 0xef, 0x70, 0x70, 0xf8, 0xfc },

    { 0xfe, 0x43, 0x43, 0x43, 0xfe },	// poszczegolne "beleczki" miernika napiecia akumulatorow
    { 0xfe, 0x63, 0x63, 0x63, 0xfe },
    { 0xfe, 0x73, 0x73, 0x73, 0xfe },
    { 0xfe, 0x7b, 0x7b, 0x7b, 0xfe },
    { 0xfe, 0x7f, 0x7f, 0x7f, 0xfe },
    { 0x3e, 0x41, 0x22, 0x14, 0x08 },
    { 0x3e, 0x7f, 0x3e, 0x1c, 0x08 }


};

static unsigned char LcdCache [ LCD_CACHE_SIZE ];	//tablica zadeklarowana pod konkretnym adresem

volatile static int   LcdCacheIdx;
volatile static int   LoWaterMark;
volatile static int   HiWaterMark;
volatile static unsigned char  UpdateLcd;

void WriteSPI(unsigned char data)
{
	unsigned char i;
	for(i=0;i<8;i++){
		if((data&0x80)==0x80)
			SetBit(DATA);
		else
			ClrBit(DATA);
		SetBit(CLK);
		ClrBit(CLK);
		data<<=1;
	}
}

//ustawienie linii portu
void SetBit(int bits)
{
	HAL_GPIO_WritePin(PORT_DISP_NOKIA, bits,GPIO_PIN_SET);
}

//wyzerowanie linii portu
void ClrBit(int bits)
{
	HAL_GPIO_WritePin(PORT_DISP_NOKIA, bits, GPIO_PIN_RESET);
}

//zapisanie danej do sterownika
void WriteData(unsigned char data)
{
	SetBit(DC);//rejestr danych
	ClrBit(SCE);
	WriteSPI(data);
	SetBit(SCE);
}

//zapisanie komendy do sterownika
void WriteCmd(unsigned char cmd)
{
	ClrBit(DC);//rejestr komend
	ClrBit(SCE);
	WriteSPI(cmd);
	SetBit(SCE);
}


//inicjalizacja sterownika
void LcdInit(void)
{
	int i;

	HAL_GPIO_WritePin(PORT_DISP_NOKIA,LCD_PWR,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(PORT_DISP_NOKIA,LCD_BKLT,GPIO_PIN_RESET);
	delay_ms(500);
	HAL_GPIO_WritePin(PORT_DISP_NOKIA,LCD_BKLT,GPIO_PIN_SET);
	HAL_GPIO_WritePin(PORT_DISP_NOKIA,LCD_PWR,GPIO_PIN_SET);
	HAL_GPIO_WritePin(PORT_DISP_NOKIA,RES,GPIO_PIN_RESET);
	delay_ms(2);
	HAL_GPIO_WritePin(PORT_DISP_NOKIA,RES,GPIO_PIN_SET);
	WriteCmd(0x21);//komendy rozszerzone
	WriteCmd(0x05);//komenda „przelaczajaca” sterownik w tryb pracy zgodny PCD8544
	WriteCmd(0xd5);//ustawienie Vop
	Delay(2);
	//WriteCmd(0x13);//bias
	WriteCmd(0x06);//korekcja temperatury dla PCD8544
	WriteCmd(0x14);//wspólczynnik multipleksowania

	WriteCmd(0x20);//komendy standardowe - adresowanie poziome
	Delay(2);
	WriteCmd(0x0c);//tryb wyœwietlania Standard Mode
	WriteCmd(0x40);//zerowanie licznika wierszy
	WriteCmd(0x80);//zerowanie licznika kolumn
	Delay(2);
//	for(i=0;i<(48*84);i++)//612
//		WriteData(0x00);//zerowanie pamieci RAM wyswietlacza
	LoWaterMark = LCD_CACHE_SIZE;
	HiWaterMark = 0;
	LcdClear();
	LcdUpdate();

}

/*--------------------------------------------------------------------------------------------------

  Name         :  LcdClear

  Description  :  Clears the display. LcdUpdate must be called next.

  Argument(s)  :  None.

  Return value :  None.

--------------------------------------------------------------------------------------------------*/
void LcdClear ( void )
{
  unsigned int i;

  for ( i = 0; i <= LCD_CACHE_SIZE; i++ ) LcdCache[i] = 0x00;
  LoWaterMark = 0;
  HiWaterMark = LCD_CACHE_SIZE - 1;
  WriteCmd(0x80);
  WriteCmd(0x40);
  LcdUpdate();
}

void LcdUpdate ( void )
{
  int i;

  if ( LoWaterMark < 0 )  LoWaterMark = 0;
  else if ( LoWaterMark >= LCD_CACHE_SIZE ) LoWaterMark = LCD_CACHE_SIZE - 1;
  if ( HiWaterMark < 0 ) HiWaterMark = 0;
  else if ( HiWaterMark >= LCD_CACHE_SIZE ) HiWaterMark = LCD_CACHE_SIZE - 1;
  WriteCmd( 0x80 | (LoWaterMark % LCD_X_RES));
  WriteCmd( 0x40 | (LoWaterMark / LCD_X_RES));
  for ( i = LoWaterMark; i <= HiWaterMark; i++ ) WriteData( LcdCache[i]);
  LoWaterMark = LCD_CACHE_SIZE - 1;
  HiWaterMark = 0;
  UpdateLcd = FALSE;
}

void LcdGotoXY ( unsigned char x, unsigned char y )
{
    LcdCacheIdx = (x - 1) * 6 + (y - 1) * 84;
}

void LcdChr ( LcdFontSize size, unsigned char negative, unsigned char ch )
{
  unsigned char i, c;
  unsigned char b1, b2;
  int  tmpIdx;

  if ( LcdCacheIdx < LoWaterMark ) LoWaterMark = LcdCacheIdx;
//  if ( (ch < 0x20) || (ch > 0x8d) ) ch = 92;
  if ( size == FONT_1X )
  {
    for ( i = 0; i < 5; i++ )
    {
      if(negative==FONT_POSITIVE)
        LcdCache[LcdCacheIdx++] = FontLookup[ch - 32][i] << 1;
      else
        LcdCache[LcdCacheIdx++] = ~(FontLookup[ch - 32][i] << 1);
    }
  if(negative==FONT_POSITIVE)
    LcdCache[LcdCacheIdx] = 0x00;
  else
    LcdCache[LcdCacheIdx] = 0xff;
  if ( LcdCacheIdx > HiWaterMark )
  {
    HiWaterMark = LcdCacheIdx;	//nie wiem skad to 18 ale bez tego dziala zle
  }

  }
  else if ( size == FONT_2X )
  {
    tmpIdx = LcdCacheIdx - 84;
    if ( tmpIdx < LoWaterMark ) LoWaterMark = tmpIdx;
    if ( tmpIdx < 0 ) return;
    for ( i = 0; i < 5; i++ )
    {
      c = FontLookup[ch - 32][i] << 1;
      b1 =  (c & 0x01) * 3;
      b1 |= (c & 0x02) * 6;
      b1 |= (c & 0x04) * 12;
      b1 |= (c & 0x08) * 24;
      c >>= 4;
      b2 =  (c & 0x01) * 3;
      b2 |= (c & 0x02) * 6;
      b2 |= (c & 0x04) * 12;
      b2 |= (c & 0x08) * 24;
      if(negative==FONT_POSITIVE)
      {
        LcdCache[tmpIdx++] = b1;
        LcdCache[tmpIdx++] = b1;
//            LcdCache[tmpIdx + 82] = b2;
//            LcdCache[tmpIdx + 83] = b2;
        LcdCache[tmpIdx + 100] = b2;	//?
        LcdCache[tmpIdx + 101] = b2;	//?
      }
      else
      {
        LcdCache[tmpIdx++] = ~b1;
        LcdCache[tmpIdx++] = ~b1;
//            LcdCache[tmpIdx + 82] = b2;
//            LcdCache[tmpIdx + 83] = b2;
        LcdCache[tmpIdx + 100] = ~b2;	//?
        LcdCache[tmpIdx + 101] = ~b2;	//?

      }
    }
    if(negative==FONT_POSITIVE)
    {
      LcdCache[tmpIdx]=0;
      LcdCache[tmpIdx+1]=0;
      LcdCache[tmpIdx+102]=0;
      LcdCache[tmpIdx+103]=0;
      LcdCacheIdx =LcdCacheIdx + 11;
    }
    else
    {
      LcdCache[tmpIdx]=0xff;
      LcdCache[tmpIdx+1]=0xff;
      LcdCache[tmpIdx+102]=0xff;
      LcdCache[tmpIdx+103]=0xff;
      LcdCacheIdx =LcdCacheIdx + 11;
    }
//  }
    if ( LcdCacheIdx > HiWaterMark )
    {
      HiWaterMark = LcdCacheIdx + 18;	//nie wiem skad to 18 ale bez tego dziala zle
    }
  }
  LcdCacheIdx++;
  LcdUpdate();
}

void LcdStr ( LcdFontSize size, unsigned char negative, unsigned char *dataPtr )
{
  while ( *dataPtr )
  {
    LcdChr( size, negative, *dataPtr++ );
    LcdUpdate();	// dopisane przeze mnie
  }
}

void LcdPixel ( unsigned char x, unsigned char y, LcdPixelMode mode )
{
  unsigned int  index;
  unsigned char  offset;
  unsigned char  da;

  if ( x > LCD_X_RES ) return;
  if ( y > LCD_Y_RES ) return;
  index = ((y / 8) * 84) + x;
  offset  = y - ((y / 8) * 8);
  da = LcdCache[index];
  if ( mode == PIXEL_OFF ) da &= (~(0x01 << offset));
  else if ( mode == PIXEL_ON ) da |= (0x01 << offset);
  else if ( mode  == PIXEL_XOR ) da ^= (0x01 << offset);
  LcdCache[index] = da;
  if ( index < LoWaterMark ) LoWaterMark = index;
  if ( index > HiWaterMark ) HiWaterMark = index;
  LcdUpdate();
}

void LcdLine ( unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2, LcdPixelMode mode )
{
  int dx, dy, stepx, stepy, fraction;

  dy = y2 - y1;
  dx = x2 - x1;

  if ( dy < 0 )
  {
    dy    = -dy;
    stepy = -1;
  }
  else stepy = 1;
  if ( dx < 0 )
  {
    dx    = -dx;
    stepx = -1;
  }
  else stepx = 1;
  dx <<= 1;
  dy <<= 1;
  LcdPixel( x1, y1, mode );
  if ( dx > dy )
  {
    fraction = dy - (dx >> 1);
    while ( x1 != x2 )
    {
      if ( fraction >= 0 )
      {
        y1 += stepy;
        fraction -= dx;
      }
      x1 += stepx;
      fraction += dy;
      LcdPixel( x1, y1, mode );
    }
  }
  else
  {
    fraction = dx - (dy >> 1);
    while ( y1 != y2 )
    {
      if ( fraction >= 0 )
      {
        x1 += stepx;
        fraction -= dy;
      }
      y1 += stepy;
      fraction += dx;
      LcdPixel( x1, y1, mode );
    }
  }
  UpdateLcd = TRUE;
//    LcdUpdate();
}

/* Clears an area on a line */
void LcdClearArea(unsigned char line, unsigned char startX, unsigned char endX)
{
  unsigned int i;
  int start = (line-1)*84+(startX-1);
  int end = (line-1)*84+(endX-1) * 6;

  WriteCmd(0x80 |(start % LCD_X_RES));
  WriteCmd(0x40 |(start / LCD_X_RES));
  for(i=start;i<end;i++)
  {
    WriteData(0);
    LcdCache[i]=0;
  }
}

void LcdClearLine(unsigned char line)
{
 unsigned int i;
  int start = (line-1)*84;
  int end = (line-1)*84 + 84;

  WriteCmd(0x80 |(start % LCD_X_RES));
  WriteCmd(0x40 |(start / LCD_X_RES));
  for(i=start;i<end;i++)
  {
    WriteData(0x00);
    LcdCache[i]=0x00;
  }
//  LcdClearArea(line,1,LCD_X_RES / 8);
}

void LcdFillLine(unsigned char line)
{
 unsigned int i;
  int start = (line-1)*84;
  int end = (line-1)*84 + 83;

  WriteCmd(0x80 |(start % LCD_X_RES));
  WriteCmd(0x40 |(start / LCD_X_RES));
  for(i=start;i<end;i++)
  {
    WriteData(0xff);
    LcdCache[i]=0xff;
  }
}

void LcdRectangle	(unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2, LcdRectangleMode mode)
{
	unsigned char i, j, temp;
	LcdLine(x1,y1,x2,y1,PIXEL_ON);
	LcdLine(x2,y1,x2,y2,PIXEL_ON);
	LcdLine(x2,y2,x1,y2,PIXEL_ON);
	LcdLine(x1,y2,x1,y1,PIXEL_ON);
	if(mode!=TRANSPARENT)
	{
		if(x1>x2)
		{
			temp=x2;
			x2=x1;
			x1=temp;
		}
		if(y1>y2)
		{
			temp=y2;
			y2=y1;
			y1=temp;
		}
		for(i=x1+1; i<x2; i++)
			for(j=y1+1; j<y2; j++)
				LcdPixel(i,j,mode - 1);
	}
}

void LcdVerticalScrollBar(unsigned char percentage, unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2)
{
	unsigned char size,temp, pos;
	float pos_f;

	if(x1>x2)
	{
		temp=x2;
		x2=x1;
		x1=temp;
	}
	if(y1>y2)
	{
		temp=y2;
		y2=y1;
		y1=temp;
	}
	size = y2 - y1 - 5;
	pos_f=((float)(percentage)/100) * (float)(size);
	pos=y1 + (unsigned char)(pos_f);
	LcdRectangle(x1,y1,x2,y2, CLEAR);
	LcdRectangle(x1,pos,x2,pos+5, FILL);
}
void Delay(unsigned int wait)
{
	uint16_t i;
	for(i=0;i<wait;i++) __NOP() ;
}
