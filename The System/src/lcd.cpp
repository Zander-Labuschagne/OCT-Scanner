#include "../include/lcd.hpp"

LCD::LCD()
{
	lcd = lcdInit(2, 16, 4, LCD_RS, LCD_E, LCD_D4, LCD_D5, LCD_D6, LCD_D7, 0, 0, 0, 0);
}

void LCD::display(char *string)
{
	lcdPuts(lcd, string);
}