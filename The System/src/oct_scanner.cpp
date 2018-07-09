#include <unistd.h>
#include <wiringPi.h>




#include "../include/lcd.hpp"
#include "../include/oct_scanner.h"

int main()
{
	init();
	//wag vir threads om klaar te maak
	t_scan_type.join();
	t_scan_resolution.join();
	t_start_button.join();

	t_oct_scan.join();
	t_pg_scan.join();

	return 0;
}

void init()
{
	wiringPiSetup();

//	LCD lcd();
//	lcd.display("Initializing...");

	//yellow start push button
	pinMode(START_BUTTON, INPUT); 
	pullUpDnControl(START_BUTTON, PUD_UP);

	//scan type switch
//	pinMode(SCAN_TYPE_SWITCH, INPUT_PULLDOWN);//Die gaan dalk moet aanpas vir wiringpi

//	lcd.display("OCT/3D Scanner\nReady"); //TODO: Maak hom dalk flikker?

//	if (digitalRead(SCAN_TYPE_SWITCH) == LOW) {
//		scan_type = PG;
//		display("3D Scanner\nReady");

//	} else {
//		scan_type = OCT;
//		display("OCT Scanner\nReady");
//	}

	scan_resolution = 16; //= knob value


	//TODO: Add knob to change scan resolution including real time on screen display update

	pthread_create(&t_scan_type, NULL, poll_scan_type_switch, NULL);
	pthread_create(&t_scan_resolution, NULL, poll_scan_resolution_knob, NULL);
	pthread_create(&t_start_button, NULL, poll_start_button, NULL);
}

void poll_scan_type_switch()
{
//	while (1) {
//		if (digitalRead(SCAN_TYPE_SWITCH) == LOW) {
//			scan_type = PG;
//			display("3D Scanner\nReady");
//		} else {
//			scan_type = OCT;
//			display("OCT Scanner\nReady");
//		}

//		usleep(50000);
//	}
}

void poll_scan_resolution_knob()
{
//	while (1) {
		//scan_resolution = knob_value
//		usleep(50000);
//	}
}

void poll_start_button()
{
	while (1) {
		if (digitalRead(START_BUTTON) == 0) {//TODO: Check and Update values accordingly
			//TODO: stop die ander threads wat settings poll - hoe????
			//printf("High\n");
			if (scan_type == OCT) //Doen OCT scan
				pthread_create(&t_oct_scan, NULL, oct_scan, NULL);
			else if (scan_type == PG) { //Doen photogrammetry scan
				pthread_create(&t_pg_scan, NULL, pg_scan, NULL);
			pthread_create(&t_reset_button, NULL, poll_reset_button, NULL);
			
			break;
		}
		else
			printf("Low\n");
		usleep(50000);
	}
}

void poll_reset_button()
{
	long hold_counter = 0;
	while (1) {
		//if pressed increase counter
		if (digitalRead(START_BUTTON) == 0) //TODO: Check and update values accordingly
			++hold_counter;
		else
			hold_counter = 0;
		//if counter >= seker waarde dan lank genoeg ingehou vir reset proses
		if (hold_counter >= 2000) {
			//TODO: stop scan en ander threads hoe??????????
			//begin start button en ander settings te poll
			pthread_create(&t_scan_type, NULL, poll_scan_type_switch, NULL);
			pthread_create(&t_scan_resolution, NULL, poll_scan_resolution_knob, NULL);
			pthread_create(&t_start_button, NULL, poll_start_button, NULL);

			break;
		}
		usleep(50000);
	}
}

void oct_scan()
{
	//TODO: backlighting moet aktiveer
}

void pg_scan()
{
	//TODO: ambient lighting moet aktiveer

	
	for (unsigned short iii = 0; iii < scan_resolution; ++iii) {
		//roep python kode EN WAG tot hy klaar is
		int a = system("python step.py");//TODO: Vervang die met IPC metode -- semaphore, message queue, UNIX domain socket, D-Bus subsystem
							// http://www.chandrashekar.info/articles/linux-system-programming/introduction-to-linux-ipc-mechanims.html
							// https://www.thegeekstuff.com/2010/08/ipcs-command-examples/
							// http://www.tldp.org/LDP/lpg/node7.html
							// https://beej.us/guide/bgipc/
							// https://en.wikipedia.org/wiki/Unix_domain_socket
							// https://stackoverflow.com/questions/6915191/simple-ipc-between-c-and-python-cross-platform
							// http://zeromq.org/
							// http://zeromq.org/intro:read-the-manual
							// https://stackoverflow.com/questions/16173215/using-linux-posix-ipc-message-queue
							// https://stackoverflow.com/questions/3056307/how-do-i-use-mqueue-in-a-c-program-on-a-linux-based-system
		//usleep(5000 * 1000); //ms * 1000 want hy verwag microseconds
		//sleep(5);//seconds
		//Neem foto

	}
}