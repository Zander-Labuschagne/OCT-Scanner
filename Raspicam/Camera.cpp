#include <ctime>	//sleep, time_t
#include <fstream>
#include <iostream>

#include <raspicam/raspicam.h>

raspicam::RaspiCam camera; //Camera object
raspicam::RaspiCam_Cv camera_cv; //OpenCV camera object

bool camera_ready = false;

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
	//set camera parameters
	camera_cv.set(CV_CAP_PROP_FORMAT, CV_8UC1);
	//Open camera
	if (!camera_cv.open()) {
		std::cerr << "Error opening the camera" << std::endl;
		
		return -1;
	}

	camera_ready = true;

	return 0;
}

/*
 * Must call init_camera() before calling this function
 */
//TODO: Dalk string parameter by sit vir file naam...
int capture_image()
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
	camera.retrieve(data, raspicam::RASPICAM_FORMAT_RGB);//get camera image
	//save image
	std::ofstream outFile("raspicam_image.ppm", std::ios::binary);
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
	if (!camera_ready) {
		std::cerr << "Camera not initialized" << std::endl;

		return -1;
	}

	int n_frames = 1000;
	// Allocate memory for camera buffer
	unsigned long image_bytes = camera.getImageBufferSize();
	unsigned char *image_data = new unsigned char[bytes];

	for(int frame = 0; frame < n_frames; frame++) {
		// Capture frame
		camera.grab();

		// Extract the image
		camera.retrieve(image_data, raspicam::RASPICAM_FORMAT_IGNORE);
	}
	
	//Met die 3 lyntjies hier wees of binne die for?
	std::ofstream outFile("raspicam_image.ppm", std::ios::binary);
	outFile << "P6\n" << camera.getWidth() << " " << camera.getHeight() << " 255\n";
	outFile.write((char*)image_data, camera.getImageTypeSize(raspicam::RASPICAM_FORMAT_RGB));

	delete image_data;

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

	time_t timer_begin, timer_end; //Blykbaar vir tyd statistieke

	cv::Mat image;
	int n_count = 100;

	//Start capture
	std::cout << "Capturing " << n_count << " frames ...." << std::endl;
	time(&timer_begin);
	for(int i = 0; i < n_count; i++) {
        	camera_cv.grab();
		camera_cv.retrieve(image);
		if(i % 5 == 0)
			std::cout << "\r captured " << i << " images" << std::flush;
	}

	//show time statistics
	time(&timer_end); /* get current time; same as: timer = time(NULL)  */
	double seconds_elapsed = difftime(timer_end,timer_begin);
	std::cout << seconds_elapsed << " seconds for " << n_count << "  frames : FPS = " << (float)((float)(n_count) / seconds_elapsed) << std::endl;

	//save image 
	cv::imwrite("raspicam_cv_image.jpg", image);

	return 0;
}

void deactivate_camera_cv()
{
	//cout<<"Stop camera..."<<endl;
	camera_cv.release();
	camera_ready = false;
} 

int main()
{
	//Get camera ready
	if (init_camera() == -1)
		return -1;

	// //Get camera ready for OpenCV
	// if (init_camera_cv() == -1)
	// 	return -1;

	//Neem foto
	if (capture_image() != 0) {
		std::cerr << "Error in image capture" << std::endl;

		return -1;
	}

	//Neem foto met OpenCV
	// if (capture_image_cv() != 0) {
	// 	std::cerr << "Error in image capture" << std::endl;

	// 	return -1;
	// }
	// deactivate_camera_cv();

	return 0;
}