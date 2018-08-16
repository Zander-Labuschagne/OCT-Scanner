import RPi.GPIO as GPIO
import time
import sys
#import posix_ipc


GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)

IN1 = 4 # pink
IN2 = 17 # orange
IN3 = 23 # blue
IN4 = 24 # yellow

QUEUE_KEY = 8500

step_count = 8
seq = list(range(0, step_count))
seq[0] = [1,0,0,0]
seq[1] = [1,1,0,0]
seq[2] = [0,1,0,0]
seq[3] = [0,1,1,0]
seq[4] = [0,0,1,0]
seq[5] = [0,0,1,1]
seq[6] = [0,0,0,1]
seq[7] = [1,0,0,1]

GPIO.setup(IN1, GPIO.OUT)
GPIO.setup(IN2, GPIO.OUT)
GPIO.setup(IN3, GPIO.OUT)
GPIO.setup(IN4, GPIO.OUT)

def set_step(w1, w2, w3, w4):
	GPIO.output(IN1, w1)
	GPIO.output(IN2, w2)
	GPIO.output(IN3, w3)
	GPIO.output(IN4, w4)

#Die funksie is vir die IPC metode wat dan deur volle omwenteling hardloop en kommunikeer met C++
def rotate(scan_resolution):
	for i in range(scan_resolution):
		for ii in range(step_count):
			set_step(seq[ii][0], seq[ii][1], seq[ii][2], seq[ii][3])
			time.sleep(0.005)

#Die funksie is vir die Shell exec metode wat net step elke keer as hy geroep word, nie IPC
# def step(resolution):
# 	for i in range(resolution):
# 		for ii in range(step_count):
# 			set_step(seq[ii][0], seq[ii][1], seq[ii][2], seq[ii][3])
# 			time.sleep(0.005)


#Al wat die kode moet doen is roteer die stepper een step dan return vir C++ om foto te neem
if __name__ == '__main__':
	#IPC DEEL
	# try:
	# 	mq = posix_ipc.MessageQueue(params["/stepper_queue"], posix_ipc.O_CREX) #create message queue
	# except: sysv_ipc.ExistentialError:
	# 	print "ERROR: message queue creation failed"

	# mq.send(“rotated”, True)
	rotate(int(sys.argv[1]))
