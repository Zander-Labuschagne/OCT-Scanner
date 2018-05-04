#include <unistd.h>
#include <wiringPi.h>

#include "../include/lcd.hpp"
#include "../include/oct_scanner.h"

int main()
{
	wiringPiSetup();

	LCD lcd();
	lcd.display("Initializing...");

	//yellow start push button
	pinMode(START_BUTTON, INPUT); 
	pullUpDnControl(START_BUTTON, PUD_UP);

	lcd.display("OCT/3D Scanner\nReady"); //TODO: Maak hom dalk flikker?

	scan_type = PG; //= switch position
	scan_resolution = 16; //= knob value

	//TODO: Add switch to choose between 3D and OCT and update display accordingly
	// if (scan_type == OCT)
	// 	display("OCT Scanner\nReady");
	// else if (scan_type == 3D)
	// 	display("3D Scanner\nReady");

	//TODO: Add knob to change scan resolution including real time on screen display update

	pthread_create(&t_scan_type, NULL, poll_scan_type_switch, NULL);
	pthread_create(&t_scan_resolution, NULL, poll_scan_resolution_knob, NULL);
	pthread_create(&t_start_button, NULL, poll_start_button, NULL);

	//wag vir threads om klaar te maak
	t_scan_type.join();
	t_scan_resolution.join();
	t_start_button.join();

	t_oct_scan.join();
	t_pg_scan.join();

	return 0;
}

void poll_scan_type_switch()
{
	while (1) {
		//scan_type = switch_position
		usleep(50000);
	}
}

void poll_scan_resolution_knob()
{
	while (1) {
		//scan_resolution = knob_value
		usleep(50000);
	}
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
	

}