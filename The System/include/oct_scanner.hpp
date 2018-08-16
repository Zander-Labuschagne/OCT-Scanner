#include <pthread.h>

#include <raspicam/raspicam.h>

#define START_BUTTON 1
#define SCAN_TYPE_SWITCH 2//TODO: Update accordingly

#define OCT 1
#define PG 2

#define QUEUE_KEY 8500

bool camera_ready = false;

char scan_type;
unsigned short scan_resolution;

pthread_t t_scan_type;
pthread_t t_scan_resolution;
pthread_t t_start_button;
pthread_t t_reset_button;

pthread_t t_oct_scan;
pthread_t t_pg_scan;

raspicam::RaspiCam camera; //Camera object
// raspicam::RaspiCam_Cv camera_cv; //OpenCV camera object

void init();
int init_camera();

void poll_scan_type_switch();
void poll_scan_resolution_knob();
void poll_start_button();
void poll_reset_button();

int oct_scan();
int pg_scan();

int capture_image(int image_number);
int capture_image_2();
int capture_image_cv();

void deactivate_camera_cv();
