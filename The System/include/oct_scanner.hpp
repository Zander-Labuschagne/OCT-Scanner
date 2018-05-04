#include <pthread.h>

#define START_BUTTON 1
#define SCAN_TYPE_SWITCH 2//TODO: Update accordingly

#define OCT 1
#define PG 2 

#define QUEUE_KEY 8500

char scan_type;
unsigned short scan_resolution;

pthread_t t_scan_type;
pthread_t t_scan_resolution;
pthread_t t_start_button;
pthread_t t_reset_button;

pthread_t t_oct_scan;
pthread_t t_pg_scan;

int init();

void poll_scan_type_switch();
void poll_scan_resolution_knob();
void poll_start_button();
void poll_reset_button();

int oct_scan();
int pg_scan();