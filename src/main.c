#include "stm32f4xx.h"
#include "LCD_Pins.h"
#include "ILI9341.h"


int main(void)
{
	delay_init(180000000);
	LCD_Pin_Init();
	LCD_SPI_Init();
	ILI9341_Init();
	ILI9341_setRotation(2);
	ILI9341_Fill(COLOR_RED);

	while(1)
	{
		ILI9341_Fill(COLOR_BLUE);
		ILI9341_Fill(COLOR_GREENYELLOW);

	}
}
