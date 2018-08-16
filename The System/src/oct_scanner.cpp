//compile vir C++ wiringPi:
// g++ oct_scanner.cpp -o oct_scanner -lwiringPi

//compile vir C++ p_thread
// g++ oct_scanner.cpp -o oct_scanner -lpthread

//compile vir C++ image capture:
//g++ simpletest_raspicam.cpp -o simpletest_raspicam -I/usr/local/include -lraspicam -lmmal -lmmal_core -lmmal_util

//compile vir OpenCV image capture:
// g++ simpletest_raspicam_cv.cpp -o  simpletest_raspicam_cv -I/usr/local/include/ -lraspicam -lraspicam_cv -lmmal -lmmal_core -lmmal_util -lopencv_core -lopencv_highgui

//CMake vir C++ image capture
//  #####################################
// cmake_minimum_required (VERSION 2.8)
// project (raspicam_test)
// find_package(raspicam REQUIRED)
// add_executable (simpletest_raspicam simpletest_raspicam.cpp)
// target_link_libraries (simpletest_raspicam ${raspicam_LIBS})
// #####################################

//CMake vir OpenCV image capture
//  #####################################
// cmake_minimum_required (VERSION 2.8)
// project (raspicam_test)
// find_package(raspicam REQUIRED)
// find_package(OpenCV)
// IF  ( OpenCV_FOUND AND raspicam_CV_FOUND)
// MESSAGE(STATUS "COMPILING OPENCV TESTS")
// add_executable (simpletest_raspicam_cv simpletest_raspicam_cv.cpp)
// target_link_libraries (simpletest_raspicam_cv ${raspicam_CV_LIBS})
// ELSE()
// MESSAGE(FATAL_ERROR "OPENCV NOT FOUND IN YOUR SYSTEM")
// ENDIF()
// #####################################

//Run CMake
// mkdir build
// cd build
// cmake ..
// make
// ./simpletest_raspicam_cv

#include <unistd.h>	//usleep, sleep
#include <ctime>	//sleep, time_t
#include <fstream>
#include <iostream>

#include <wiringPi.h>

#include "../include/lcd.hpp"
#include "../include/oct_scanner.hpp"

int main()
{
	init();
	//wag vir threads om klaar te maak
	//t_scan_type.join();
	//t_scan_resolution.join();
	//t_start_button.join();

	// t_oct_scan.join();
	//t_pg_scan.join();

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

	scan_resolution = 8; //= knob value
	camera_ready = false;

	poll_start_button();


	//TODO: Add knob to change scan resolution including real time on screen display update

	//pthread_create(&t_scan_type, NULL, poll_scan_type_switch, NULL);
	//pthread_create(&t_scan_resolution, NULL, poll_scan_resolution_knob, NULL);
	//pthread_create(&t_start_button, NULL, poll_start_button, NULL);
}

int init_camera()
{
	// Allowable values: RASPICAM_FORMAT_GRAY,RASPICAM_FORMAT_RGB,RASPICAM_FORMAT_BGR,RASPICAM_FORMAT_YUV420
	camera.setFormat(raspicam::RASPICAM_FORMAT_GRAY);
	// Allowable widths: 320, 640, 1280
	// Allowable heights: 240, 480, 960
	camera.setCaptureSize(1280, 960);

	// Open camera
	//Kan ek nie hierdie open deel een keer doen in init_camera nie, sodat hy nie vir elke beeld moet open nie
	if (!camera.open()) {
		std::cerr << "Error opening camera" << std::endl;

		return -1;
	}
	//wait a while(3 seconds) until camera stabilizes
	sleep(3);
	camera_ready = true;

	return 0;
}

int init_camera_cv()
{
	// //set camera parameters
	// camera_cv.set(CV_CAP_PROP_FORMAT, CV_8UC1);
	// //Open camera
	// if (!camera_cv.open()) {
	// 	std::cerr << "Error opening the camera" << std::endl;
	//
	// 	return -1;
	// }
	//
	// camera_ready = true;
	//
	// return 0;
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
			printf("High\n");
			// if (scan_type == OCT) //Doen OCT scan
			// 	pthread_create(&t_oct_scan, NULL, oct_scan, NULL);
			// else if (scan_type == PG) { //Doen photogrammetry scan
				//pthread_create(&t_pg_scan, NULL, pg_scan, NULL);
				pg_scan();
			// pthread_create(&t_reset_button, NULL, poll_reset_button, NULL);

			break;
		}
		else
			printf("Low\n");
		usleep(50000);
	}
}

//Vervang dalk met interrupt ipv polling...
		// https://www.waveshare.com/wiki/Raspberry_Pi_Tutorial_Series:_External_Button
void poll_reset_button()
{
	// long hold_counter = 0;
	// while (1) {
	// 	//if pressed increase counter
	// 	if (digitalRead(START_BUTTON) == 0) //TODO: Check and update values accordingly
	// 		++hold_counter;
	// 	else
	// 		hold_counter = 0;
	// 	//if counter >= seker waarde dan lank genoeg ingehou vir reset proses
	// 	if (hold_counter >= 2000) {
	// 		//TODO: stop scan en ander threads hoe??????????
	// 		//begin start button en ander settings te poll
	// 		pthread_create(&t_scan_type, NULL, poll_scan_type_switch, NULL);
	// 		pthread_create(&t_scan_resolution, NULL, poll_scan_resolution_knob, NULL);
	// 		pthread_create(&t_start_button, NULL, poll_start_button, NULL);
	//
	// 		break;
	// 	}
	// 	usleep(50000);
	// }
}

int oct_scan()
{
	//TODO: backlighting moet aktiveer
	//Is dit beter om lighting aan te hou of af en aan te sit vir elke beeld?


	return 0;
}

int pg_scan()
{
	//Get camera ready
	if (init_camera() == -1)
		return -1;

	// //Get camera ready for OpenCV
	// if (init_camera_cv() == -1)
	// 	return -1;



	//TODO: ambient lighting moet aktiveer
	//Is dit beter om lighting aan te hou of af en aan te sit vir elke beeld?

	for (unsigned short iii = 0; iii < scan_resolution; ++iii) {
		//Neem foto
		if (capture_image(iii) != 0) {
			std::cerr << "Error in image capture" << std::endl;

			return -1;
		}
		std::cout << "Neem foto" << std::endl;
		//roep python kode EN WAG tot hy klaar is
		//TODO: sit in if stelling om dalk exception handling te doen
		int a = system("sudo python step.py " + 1 / scan_resolution * 512);//TODO: Vervang die met IPC metode -- semaphore, message queue, UNIX domain socket, D-Bus subsystem
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

		std::cout << "Draai" << std::endl;
		//Neem foto met OpenCV
		// if (capture_image_cv() != 0) {
		// 	std::cerr << "Error in image capture" << std::endl;
		//
		// 	return -1;
		// }
		deactivate_camera_cv();
	}

	return 0;
}

/*
 * Must call init_camera() before calling this function
 */
//TODO: Dalk string parameter by sit vir file naam...
int capture_image(int image_number)
{
	if (!camera_ready) {
		std::cerr << "Camera not initialized" << std::endl;

		return -1;
	}

	//capture
	camera.grab();
	//allocate memory
	unsigned char *image_data = new unsigned char[camera.getImageTypeSize(raspicam::RASPICAM_FORMAT_RGB)];
	//extract the image in rgb format
	camera.retrieve(image_data, raspicam::RASPICAM_FORMAT_RGB);//get camera image
	//save image
	std::ofstream outFile("raspicam_image_" + std::to_string(image_number) + ".ppm", std::ios::binary);
	outFile << "P6\n" << camera.getWidth() << " " << camera.getHeight() << " 255\n";
	outFile.write((char*)image_data, camera.getImageTypeSize(raspicam::RASPICAM_FORMAT_RGB));
	//free resrources
	delete image_data;

	return 0;
}

/*
 * Must call init_camera() before calling this function
 */
//TODO: Dalk string parameter by sit vir file naam...
int capture_image_2()
{
	// if (!camera_ready) {
	// 	std::cerr << "Camera not initialized" << std::endl;
	//
	// 	return -1;
	// }
	//
	// int n_frames = 1000;
	// // Allocate memory for camera buffer
	// unsigned long image_bytes = camera.getImageBufferSize();
	// unsigned char *image_data = new unsigned char[bytes];
	//
	// for(int frame = 0; frame < n_frames; frame++) {
	// 	// Capture frame
	// 	camera.grab();
	//
	// 	// Extract the image
	// 	camera.retrieve(image_data, raspicam::RASPICAM_FORMAT_IGNORE);
	// }
	//
	// //Met die 3 lyntjies hier wees of binne die for?
	// std::ofstream outFile("raspicam_image.ppm", std::ios::binary);
	// outFile << "P6\n" << camera.getWidth() << " " << camera.getHeight() << " 255\n";
	// outFile.write((char*)image_data, camera.getImageTypeSize(raspicam::RASPICAM_FORMAT_RGB));
	//
	// delete image_data;

	return 0;
}

/*
 * Image capture using OpenCV instead of default C++
 * Must call init_camera() before calling this function
 */
//TODO: Dalk string parameter by sit vir file naam...
//TODO: Time die twee capture image funksies om te sien hoe verskil die tyd wat hulle neem
int capture_image_cv()
{
	if (!camera_ready) {
		std::cerr << "Camera not initialized" << std::endl;

		return -1;
	}

	// time_t timer_begin, timer_end; //Blykbaar vir tyd statistieke
	//
	// cv::Mat image;
	// int n_count = 100;
	//
	// //Start capture
	// std::cout << "Capturing " << n_count << " frames ...." << std::endl;
	// time(&timer_begin);
	// for(int i = 0; i < n_count; i++) {
        // 	camera_cv.grab();
	// 	camera_cv.retrieve(image);
	// 	if(i % 5 == 0)
	// 		std::cout << "\r captured " << i << " images" << std::flush;
	// }
	//
	// //show time statistics
	// time(&timer_end); /* get current time; same as: timer = time(NULL)  */
	// double seconds_elapsed = difftime(timer_end,timer_begin);
	// std::cout << seconds_elapsed << " seconds for " << n_count << "  frames : FPS = " << (float)((float)(n_count) / seconds_elapsed) << std::endl;
	//
	// //save image
	// cv::imwrite("raspicam_cv_image.jpg", image);

	return 0;
}

void deactivate_camera_cv()
{
	//cout<<"Stop camera..."<<endl;
	// camera_cv.release();
	// camera_ready = false;
}
