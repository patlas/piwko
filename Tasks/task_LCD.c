#include "task_LCD.h"

void task_LCD(void *param){
	
	LcdInit();
	LcdStr(FONT_1X, FONT_POSITIVE, "TEST");
	
	for(;;){
		
		LcdInit();
		//LcdGotoXY(0,0);
		LcdStr(FONT_1X, FONT_POSITIVE, "TEST");
		vTaskDelay(500);
		
	}
	
}

void task_MENU(void *param){
	
	LcdInit();
  LcdFillLine(1);
  LcdGotoXY(1,1);
  LcdStr(FONT_1X,FONT_NEGATIVE,"   LCD DEMO   ");

  LcdFillLine(6);
  LcdGotoXY(1,6);
  LcdStr(FONT_1X,FONT_NEGATIVE,"   LCD DEMO   ");
	
	Key_t key = KEY_OK;

  while (1)							// petla
  {

	//key=getkey();





	if(key==KEY_UP)
	{
		LcdClearLine(2);
		LcdClearLine(3);
		LcdGotoXY(2,3);
		LcdStr(FONT_2X,FONT_POSITIVE,"UP");
	}
	if(key==KEY_DN)
	{
		LcdClearLine(2);
		LcdClearLine(3);
		LcdGotoXY(2,3);
		LcdStr(FONT_2X,FONT_POSITIVE,"DN");

	}
	if(key==KEY_L)
	{
		LcdClearLine(2);
		LcdClearLine(3);
		LcdGotoXY(2,3);
		LcdStr(FONT_2X,FONT_POSITIVE,"LEFT");

	}
	if(key==KEY_R)
	{
		LcdClearLine(2);
		LcdClearLine(3);
		LcdGotoXY(2,3);
		LcdStr(FONT_2X,FONT_POSITIVE,"RIGHT");

	}

	if(key==KEY_OK)
	{
		graphic_menu();
	}

  }

}

