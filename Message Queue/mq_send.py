import posix_ipc
import time

def send():
	params = {}
	line1 = "ITERATIONS=10"
	line2 = "MESSAGE_QUEUE_NAME=/mq_test2"

	name, value = line1.split('=')
	name = name.upper().strip()
	if name == "PERMISSIONS":
		value = int(value, 8)
	elif "NAME" in name:
		# This is a string; leave it alone.
		pass
	else:
		value = int(value)

	params[name] = value

	name, value = line2.split('=')
	name = name.upper().strip()
	if name == "PERMISSIONS":
		value = int(value, 8)
	elif "NAME" in name:
		# This is a string; leave it alone.
		pass
	else:
		value = int(value)

	params[name] = value

	mq = posix_ipc.MessageQueue(params["MESSAGE_QUEUE_NAME"], posix_ipc.O_CREX) #create message queue

	mq.send("5")

	time.sleep(5)
	mq.close()
	posix_ipc.unlink_message_queue(params["MESSAGE_QUEUE_NAME"]) # of mq.unlink

def receive():
	params = {}
	line1 = "ITERATIONS=10"
	line2 = "MESSAGE_QUEUE_NAME=/test"

	name, value = line1.split('=')
	name = name.upper().strip()
	if name == "PERMISSIONS":
		value = int(value, 8)
	elif "NAME" in name:
		# This is a string; leave it alone.
		pass
	else:
		value = int(value)

	params[name] = value

	name, value = line2.split('=')
	name = name.upper().strip()
	if name == "PERMISSIONS":
		value = int(value, 8)
	elif "NAME" in name:
		# This is a string; leave it alone.
		pass
	else:
		value = int(value)

	params[name] = value


	mq = posix_ipc.MessageQueue(params["MESSAGE_QUEUE_NAME"])

	s, _ = mq.receive()
	#s = s.decode()
	print(s)


if __name__ == '__main__':
	send()
	#receive()