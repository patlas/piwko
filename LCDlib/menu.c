/*
 * menu.c
 *
 *  Created on: Nov 12, 2010
 *      Author: Automatyk
 */

//////////////////////////////////////////////////////////////////////
// WAZNE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!  //
// adresowanie tablicy menu_strings w postaci [submenu][menu]       //
// czyli troche na odwrot                                           //
//////////////////////////////////////////////////////////////////////

#include "menu.h"



volatile int8_t menu_item, submenu_item;
extern uint32_t TDelay;
int16_t rez=-2;								// taka tam przykladowa wartosc

/**************************************************************************/
/* Menu typu uproszczonego (tekstowego) ***********************************/
/**************************************************************************/
void menu(void)
{
	Key_t key;
	uint8_t x_size, y_size, exit;
	menu_item=0;
	submenu_item=0;
	exit=0;
	y_size = sizeof(menu_strings)/sizeof(menu_strings[0]);			// ilosc podmenu
	x_size = sizeof(menu_strings[0])/sizeof(menu_strings[0][0]);	// ilosc menu

	LcdClearLine(2);
	LcdClearLine(3);

	show_menu(menu_item, submenu_item);

	do
	{
		key=getkey();
		if(key==KEY_R)													// menu(submenu) +
		{
			if(submenu_item==0)											// jezelipoziom glowny menu
			{
				if((++menu_item)==x_size) menu_item=0;					// menu +
			}
			else														// jezeli poziom podmenu
				if((++submenu_item)==y_size) submenu_item=y_size - 1;	// submenu max
				if((menu_strings[submenu_item][menu_item])=="") submenu_item--;	// puste submenu
			show_menu(menu_item, submenu_item);
		}
		else if(key==KEY_L)												// menu(submenu) -
		{
			if(submenu_item==0)											// jezeli poziom glowny menu
			{
				if((--menu_item)<0) menu_item=x_size-1;					// menu -
			}
			else														// jezeli poziom podmenu
				if((--submenu_item)==0) submenu_item=1;					// submenu = 1
			show_menu(menu_item, submenu_item);
		}
		else if(key==KEY_OK)											// ENTER
		{
			if(submenu_item==0)											// jezeli poziom glowny menu
				if(menu_strings[1][menu_item]!="")						// jezeli menu poziada jakies podmenu
				{
					submenu_item++;										// submenu + ( w zasadzie submenu = 1)
					show_menu(menu_item, submenu_item);
				}
				else													// jezeli menu nie posiada zadnych podmenu
					enter_menu(menu_item, submenu_item);				// wejscie w obsluge menu
			else														// jezeli poziom podmenu
				enter_menu(menu_item, submenu_item);					// wejscie w obsluge podmenu
		}
		if(key==KEY_UP)													// ESC
		{
			if(submenu_item>0)											// jezeli poziom podmenu
				submenu_item=0;											// wyjscie do poziomu glownego menu
			else														// jezeli poziom glowny menu
				exit=1;													// wyjscie z obslugi menu
			show_menu(menu_item, submenu_item);
		}
	}while(exit==0);													// koniec procedury
	exit_from_menu();
}

/**************************************************************************/
/* Pokazanie menu typu uproszczonego (tekstowego) *************************/
/**************************************************************************/
void  show_menu(uint8_t menu_no, uint8_t submenu_no)
{
	LcdClearLine(2);
	LcdGotoXY(1,2);
	LcdStr(FONT_1X,FONT_POSITIVE, (unsigned char*)menu_strings[submenu_item][menu_item]);
}

/**************************************************************************/
/* Wyjscie z menu typu uproszczonego (tekstowego) *************************/
/**************************************************************************/
void exit_from_menu(void)
{
	LcdClear();
	LcdFillLine(1);
	LcdGotoXY(1,1);
	LcdStr(FONT_1X,FONT_NEGATIVE,"   LCD DEMO   ");

	LcdFillLine(6);
	LcdGotoXY(1,6);
	LcdStr(FONT_1X,FONT_NEGATIVE,"   LCD DEMO   ");}

/**************************************************************************/
/* Uruchomienie procedury obslugi danej pozycji menu **********************/
/**************************************************************************/
void enter_menu(uint8_t menu_no, uint8_t submenu_no)
{
	char s[20];
	if(menu_no==0 && submenu_no==2)						// Menu 1.2
		rez=enter_integer(rez,-10,100,1,3, "WARTOSC" , "s");
	LcdClearLine(3);
	LcdGotoXY(1,3);
	sprintf(s,"ENTER %1u.%1u:%d",menu_no + 1, submenu_no, rez);
	LcdStr(FONT_1X, FONT_POSITIVE, (unsigned char*)s);
	delay_ms(1000);
	LcdClearLine(3);
}

/**************************************************************************/
/* Funkcja wprowania wartosci *********************************************/
/* val -> wartosc poczatkowa **********************************************/
/* min -> minimalna mozliwa wartosc do wprowadzania ***********************/
/* max -> maxymalna mozliwa wartosc do wprowadzania ***********************/
/* x -> wspolrzedna x na wyswietlaczu *************************************/
/* y -> wspolrzedna y na wyswietlaczu *************************************/
/* var_name -> nazwa wprowadzanej zmiennej (do wyswietlania przed wprowadzana zmienna) */
/* var_unit -> jednostka wprowadzanej zmiennej (do wyswietlania po wprowadzanej zmiennej) */
/**************************************************************************/
int16_t enter_integer(int16_t val, int16_t min, int16_t max, uint8_t x, uint8_t y, char *var_name, char *var_unit )
{
	  int16_t temp_val;
	  char s[10];
	  volatile Key_t key;
	  char *format;

	  if(min>0 && max>0)						// wprowadzane beda wartosci dodatnie
	  {
		  if (max<10) format="%01d";
		  else if(max<100) format = "%02d";
		  else if(max<1000) format = "%03d";
		  else if(max<10000) format = "%04d";
		  else format = "%05d";
	  }
	  else										// moze sie zdazyc wartosc ujemna
	  {
		  if (max<10) format="%+02d";
		  else if(max<100) format = "%+03d";
		  else if(max<1000) format = "%+04d";
		  else if(max<10000) format = "%+05d";
		  else format = "%+06d";
	  }
	  temp_val=val;
	  LcdGotoXY(x,y);
	  LcdStr(FONT_1X, FONT_POSITIVE, (unsigned char*)var_name);
	  LcdStr(FONT_1X, FONT_POSITIVE,": ");
	  sprintf(s,format,temp_val);
	  LcdStr(FONT_1X,FONT_NEGATIVE,(unsigned char*)s);
	  LcdStr(FONT_1X, FONT_POSITIVE,(unsigned char*)var_unit);
	  do
	  {
	    key=getkey();
	    switch(key)
	    {
	      case KEY_UP:
	        if(temp_val++ >= max)
	          temp_val=min;
	        LcdGotoXY(x,y);
	        LcdStr(FONT_1X, FONT_POSITIVE, (unsigned char*)var_name);
	        LcdStr(FONT_1X, FONT_POSITIVE,": ");
	  	    sprintf(s,format,temp_val);
	        LcdStr(FONT_1X,FONT_NEGATIVE,(unsigned char*)s);
	        LcdStr(FONT_1X, FONT_POSITIVE,(unsigned char*)var_unit);
	        break;
	      case KEY_DN:
	        if(--temp_val< min)
	          temp_val=max;
	        LcdGotoXY(x,y);
	        LcdStr(FONT_1X, FONT_POSITIVE, (unsigned char*)var_name);
	        LcdStr(FONT_1X, FONT_POSITIVE,": ");
	        sprintf(s,format,temp_val);
	        LcdStr(FONT_1X,FONT_NEGATIVE,(unsigned char*)s);
	        LcdStr(FONT_1X, FONT_POSITIVE,(unsigned char*)var_unit);

	        break;
	    }

	    LcdGotoXY(x,y);
	    LcdStr(FONT_1X, FONT_POSITIVE, (unsigned char*)var_name);
		LcdStr(FONT_1X, FONT_POSITIVE,": ");
		sprintf(s,format,temp_val);
		/*if(TDelay>500)									//miganie wartosci wprowadzanej
	      LcdStr(FONT_1X,FONT_POSITIVE,(unsigned char*)s);				//
	    else*/											//
		  LcdStr(FONT_1X,FONT_NEGATIVE,(unsigned char*)s);				//
		LcdStr(FONT_1X, FONT_POSITIVE,(unsigned char*)var_unit);
	  }while(key!=KEY_OK/* & key!=KEY_ESC*/);
//	  if(key==KEY_ESC)
//	    temp_val=0xff;				// zwracanie przez funkcje wartosci 0xff oznacza ze nacisnieto ESC
	  LcdGotoXY(x,y);
      LcdStr(FONT_1X, FONT_POSITIVE, (unsigned char*)var_name);
      LcdStr(FONT_1X, FONT_POSITIVE,": ");
	  sprintf(s,format,val);
      LcdStr(FONT_1X,FONT_NEGATIVE,(unsigned char*)s);
      LcdStr(FONT_1X, FONT_POSITIVE,(unsigned char*)var_unit);

	  return(temp_val);
}


/**************************************************************************/
/* Menu typu semi-graficznego z animacjami ********************************/
/**************************************************************************/
void graphic_menu()
{
	Key_t key;
	uint8_t x_size, y_size, exit;
	volatile uint8_t i;
	menu_item=0;
	submenu_item=0;
	exit=0;
	y_size = sizeof(menu_strings)/sizeof(menu_strings[0]);			// ilosc podmenu
	x_size = sizeof(menu_strings[0])/sizeof(menu_strings[0][0]);	// ilosc menu

	LcdFillLine(1);
	LcdGotoXY(2,1);
	LcdStr(FONT_1X,FONT_NEGATIVE,"MENU");
	slide_down();													// anmacja

	show_graphic_menu(menu_item, submenu_item);						// pokazanie menu
	do
	{
		key=getkey();
		if(key==KEY_DN)													// menu(submenu) +
		{
			if(submenu_item==0)											// jezelipoziom glowny menu
			{
				if((++menu_item)==x_size) menu_item=0;					// menu +
			}
			else														// jezeli poziom podmenu
				if((++submenu_item)==y_size) submenu_item=y_size - 1;	// submenu max
				if((menu_strings[submenu_item][menu_item])=="") submenu_item--;	// puste submenu
			show_graphic_menu(menu_item, submenu_item);
		}
		else if(key==KEY_UP)											// menu(submenu) -
		{
			if(submenu_item==0)											// jezeli poziom glowny menu
			{
				if((--menu_item)<0) menu_item=x_size-1;					// menu -
			}
			else														// jezeli poziom podmenu
				if((--submenu_item)==0) submenu_item=1;					// submenu = 1
			show_graphic_menu(menu_item, submenu_item);
		}
		else if(key==KEY_OK)											// ENTER
		{
			if(submenu_item==0)											// jezeli poziom glowny menu
				if(menu_strings[1][menu_item]!="")						// jezeli menu poziada jakies podmenu
				{
					submenu_item++;										// submenu + ( w zasadzie submenu = 1)
					slide_up();											// animacja
					slide_down();										//
					show_graphic_menu(menu_item, submenu_item);
				}
				else													// jezeli menu nie posiada zadnych podmenu
				{
					slide_up();											// animacja
					enter_graphic_menu(menu_item, submenu_item);		// wejscie w obsluge menu
				}
			else														// jezeli poziom podmenu
			{
				slide_up();												// animacja
				enter_graphic_menu(menu_item, submenu_item);			// wejscie w obsluge podmenu
			}
		}
		if(key==KEY_L)													// ESC
		{
			if(submenu_item>0)											// jezeli poziom podmenu
				submenu_item=0;											// wyjscie do poziomu glownego menu
			else														// jezeli poziom glowny menu
				exit=1;													// wyjscie z obslugi menu
			if(exit==0)
			{
				slide_up();												// animacja
				slide_down();											//
				show_graphic_menu(menu_item, submenu_item);
			}
		}
	}while(exit==0);													// koniec procedury
	exit_from_graphic_menu();
}


/**************************************************************************/
/* Pokazywanie menu typu semi-graficznego z animacjami ********************/
/**************************************************************************/
void show_graphic_menu(uint8_t menu_no, uint8_t submenu_no)
{
	volatile uint8_t i,j;
	volatile uint8_t x_size, y_size;
	int a;

	i=1;
	y_size = sizeof(menu_strings)/sizeof(menu_strings[0]);			// makzymalna ilosc podmenu
	x_size = sizeof(menu_strings[0])/sizeof(menu_strings[0][0]);	// ilosc menu
	a=0;
	do																// rzeczywista ilosc podmenu
	{																//
		a=strlen(menu_strings[i][menu_no]);							//
	}while(a>0 && i++ < (y_size - 1) );									//
	y_size=i;														//

	LcdFillLine(1);
	LcdGotoXY(2,1);
	LcdStr(FONT_1X,FONT_NEGATIVE,"MENU");

	for(i=2;i<7;i++) LcdClearLine(i);								// wyczyszczenie sektora wyswietlajacego pozycje menu
	if(submenu_no==0)												// jezeli menu glowne
	{
		i=0;
		if (menu_no<5)	j=0;										// jezeli ilosc pozycji przekracza wielkosc ekranu
		else j=menu_no-4;											// to menu trzeba przewijac
		do
		{
			LcdClearLine(i+2);
			LcdGotoXY(2, i+2);
			if(j==menu_no)											// podswietlanie wybranego menu
				LcdStr(FONT_1X,FONT_NEGATIVE,(unsigned char*)menu_strings[0][j]);	//
			else
				LcdStr(FONT_1X,FONT_POSITIVE,(unsigned char*)menu_strings[0][j]);
			j++;
		}while((++i)!=x_size && i < 6);
		LcdRectangle(0, 0, 83, 47,TRANSPARENT);						// rysowanie ramki
		LcdVerticalScrollBar(((menu_no*100)/(x_size-1)),79,8,83,47);// i suwaka pionowego
	}
	else if(submenu_no>0)											// jezeli podmenu
	{
		i=0;
		if (submenu_no<5)	j=1;									// jezeli ilosc pozycji podmenu przekracza romiar ekranu
		else j=submenu_no-4;										// to menu trzeba przewijac

		do
		{
			i++;
			LcdGotoXY(2,1);
			LcdStr(FONT_1X,FONT_NEGATIVE,"MENU>");
			LcdStr(FONT_1X,FONT_NEGATIVE,(unsigned char*)menu_strings[0][menu_no]);
			LcdClearArea(i + 1,2,14);
			LcdGotoXY(2,i + 1);
			if(j==submenu_no)										// podswietlanie wybranej pozycji menu
				LcdStr(FONT_1X,FONT_NEGATIVE,(unsigned char*)menu_strings[j][menu_no]);
			else
				LcdStr(FONT_1X,FONT_POSITIVE,(unsigned char*)menu_strings[j][menu_no]);
			j++;
		}while(j!=y_size && i < 6);
		LcdRectangle(0, 0, 83, 47,TRANSPARENT);								// ramka
		LcdVerticalScrollBar((100 * (submenu_no-1)/(y_size-2)),79,8,83,47); // suwak
	}
}

/**************************************************************************/
/* Uruchamianie funkcji przyporzadkowanych poszczegolnym pozycjom menu ****/
/**************************************************************************/
void enter_graphic_menu(uint8_t menu_no, uint8_t submenu_no)
{
	char s[20];
	LcdFillLine(1);
	slide_down();										// animacja
	LcdClear();
	if(menu_no==0 && submenu_no==2)						// Menu 1.2
	{
		LcdRectangle(0, 0, 83, 47,TRANSPARENT);			// ramka
		rez=enter_integer(rez,-10,100,2,3, "WART." , "s");	// funkcja obslugi danej pozycji menu
	}
	LcdRectangle(0, 0, 83, 47,TRANSPARENT);				// przykladowy kod po powrocie z funkcji obslugi menu
	LcdClearArea(3,2,13);
	LcdGotoXY(2,3);
	sprintf(s,"MENU %1u.%1u:%d",menu_no + 1, submenu_no, rez);
	LcdStr(FONT_1X, FONT_POSITIVE, (unsigned char*)s);
	delay_ms(1000);

	LcdFillLine(1);										// powrot do menu
	LcdGotoXY(2,1);
	slide_up();											// animacja
	LcdStr(FONT_1X,FONT_NEGATIVE,"MENU");
	slide_down();										// animacja
	show_graphic_menu(menu_item,submenu_item);			// pokazanie menu
}

/**************************************************************************/
/* Wyjscie z menu *********************************************************/
/**************************************************************************/
void exit_from_graphic_menu()
{
	uint8_t i;

	slide_up();											// animacja
	LcdClear();											// powrot do trybu normalnego
	LcdFillLine(1);
	LcdGotoXY(1,1);
	LcdStr(FONT_1X,FONT_NEGATIVE,"   LCD DEMO   ");
	LcdFillLine(6);
	LcdGotoXY(1,6);
	LcdStr(FONT_1X,FONT_NEGATIVE,"   LCD DEMO   ");
}

/**************************************************************************/
/* Animacja ***************************************************************/
/**************************************************************************/
void slide_down()
{
	uint8_t i;

	for(i=1;i<6;i++)
	{
		LcdClearLine(i+1);
		LcdRectangle(0,8,83,(i+1)*8,TRANSPARENT);
		if(i==5)
			LcdLine(0,47,83,47,PIXEL_ON);
		delay_ms(50);
	}
}

/**************************************************************************/
/* Animacja ***************************************************************/
/**************************************************************************/
void slide_up()
{
	uint8_t i;
	for(i=5;i>1;i--)
	{
		LcdRectangle(0,8,83,(i * 8) - 1,TRANSPARENT);
		LcdClearLine(i+1);
		delay_ms(50);
	}
}

