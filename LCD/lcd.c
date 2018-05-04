#include <wiringPi.h>
#include <lcd.h>
#include <unistd.h>

#define LCD_RS 25 //Register select pin
#define LCD_E 24 //Enable pin
#define LCD_D4 23 //Datapin 4
#define LCD_D5 22 //Datapin 5
#define LCD_D6 21 //Datapin 6
#define LCD_D7 14 //Datapin 7

int main()
{
	int lcd;
	wiringPiSetup();
	lcd = lcdInit(2, 16, 4, LCD_RS, LCD_E, LCD_D4, LCD_D5, LCD_D6, LCD_D7, 0, 0, 0, 0);
	lcdPuts(lcd, "OCT Scanner");

	usleep(5000000);
	return 0;
}
