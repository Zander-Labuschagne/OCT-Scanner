#include <lcd.h>
#include <wiringPi.h>

#define LCD_RS 25 //Register select pin
#define LCD_E 24 //Enable pin
#define LCD_D4 23 //Datapin 4
#define LCD_D5 22 //Datapin 5
#define LCD_D6 21 //Datapin 6
#define LCD_D7 14 //Datapin 7

class LCD
{
public:
	LCD();
	void display(char *);
private:
	int lcd;
};