import RPi.GPIO as GPIO
import time
 
GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)
coil_A_1_pin = 4 # pink
coil_A_2_pin = 17 # orange
coil_B_1_pin = 23 # blue
coil_B_2_pin = 24 # yellow
 
# adjust if different
StepCount = 8
Seq = list(range(0, StepCount))
Seq[0] = [1,0,0,0]
Seq[1] = [1,1,0,0]
Seq[2] = [0,1,0,0]
Seq[3] = [0,1,1,0]
Seq[4] = [0,0,1,0]
Seq[5] = [0,0,1,1]
Seq[6] = [0,0,0,1]
Seq[7] = [1,0,0,1]
 
#GPIO.setup(enable_pin, GPIO.OUT)
GPIO.setup(coil_A_1_pin, GPIO.OUT)
GPIO.setup(coil_A_2_pin, GPIO.OUT)
GPIO.setup(coil_B_1_pin, GPIO.OUT)
GPIO.setup(coil_B_2_pin, GPIO.OUT)
 
#GPIO.output(enable_pin, 1)
 
def setStep(w1, w2, w3, w4):
	GPIO.output(coil_A_1_pin, w1)
	GPIO.output(coil_A_2_pin, w2)
	GPIO.output(coil_B_1_pin, w3)
	GPIO.output(coil_B_2_pin, w4)
 
def forward():
	for i in range(32): #hy step 2 keer die waarde, 512 is full rotation
		for j in range(StepCount):
			setStep(Seq[j][0], Seq[j][1], Seq[j][2], Seq[j][3])
			time.sleep(0.005)
 
# def backwards(delay, steps):
#     for i in range(steps):
#         for j in reversed(range(StepCount)):
#             setStep(Seq[j][0], Seq[j][1], Seq[j][2], Seq[j][3])
#             time.sleep(delay)
 
if __name__ == '__main__':
    for i in range(1, 16):
        #delay = input("delay: ")
        #steps = input("steps: ")
        forward()
        time.sleep(3);
        # backwards(int(delay) / 1000.0, int(steps))
