#include <stdio.h>
#include <mqueue.h>
#include <assert.h>
#include <unistd.h>

#define MY_MQ_NAME "/mq_test3"

static struct mq_attr my_mq_attr;
static mqd_t my_mq;
char message[10];
//int message;


void receive()
{
	// int status;
	// status = mq_receive(my_mq, (char*)&message, sizeof(message) * 4, NULL);
	// printf("%d", message);
}

void send()
{
	int status;
	status = mq_send(my_mq, (const char*)&message, sizeof(message) * 4, 1);
	assert(status != -1);
}

int main()
{
	my_mq_attr.mq_maxmsg = 100;
	message[0] = '5';
	message[1] = '3';
	message[2] = '3';
	my_mq_attr.mq_msgsize = sizeof(message);
	//sprintf("*\n");

	//my_mq = mq_open(MY_MQ_NAME, O_CREAT | O_RDWR | O_NONBLOCK, 0666, &my_mq_attr);
	my_mq = mq_open(MY_MQ_NAME, O_WRONLY);


	assert(my_mq != -1);

	send();
	// receive();
	sleep(5);
	mq_close(my_mq);
	mq_unlink(MY_MQ_NAME);

	return 0;
}