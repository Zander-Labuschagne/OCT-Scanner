#include <wiringPi.h>
#include <stdio.h>
#include <unistd.h>

int main ()
{
	wiringPiSetup();
	pinMode(1, INPUT);
	pullUpDnControl(1, PUD_UP);
	while (true) {
		if (digitalRead(1) == 0)
			printf("High\n");
		else
			printf("Low\n");
		usleep(50000);
	}

	return 0;
}
