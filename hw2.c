/*
* Author: Matthew Taylor
* Homework: Concurrency 1
* Date: 4/8/2016
*
*REFERENCE: Intel https://software.intel.com/en-us/articles/intel-digital-random-number-generator-drng-software-implementation-guide
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include "mt19937ar.c"


struct buffer {
	int value;
	int waitTime;
};
void main() {
	pthread_t produce, consume;

	// init mutex
	pthread_mutex_init(&mu, NULL);	
	
	// Condition Variables
	pthread_cond_init(&sigToConsumer, NULL);
	pthread_cond_init(&sigToProducer, NULL);

	// Thread Creation
	pthread_create(&consume, NULL, consumer, NULL);
	pthread_create(&produce, NULL, producer, NULL);

	// Once threads finish, kill 'em
	pthread_join(consume, NULL);
	pthread_join(produce, NULL);

	// Cleanup
	pthread_mutex_destroy(&mu);	
	pthread_cond_destroy(&sigToConsumer);
	pthread_cond_destroy(&sigToProducer);
}
