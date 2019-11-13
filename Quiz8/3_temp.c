#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

enum { STATE_A, STATE_B } state = STATE_B;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* threadA(){
	int i = 0, rValue, loopnum;

	while(i < 5){
		pthread_mutex_lock(&mutex);
		while(state == STATE_B){
			usleep(10);
			puts("A");
		}
		pthread_mutex_unlock(&mutex);

		for(loopnum = 1; loopnum <= 5; loopnum++)
			printf("Hello %d\n", loopnum);

		pthread_mutex_lock(&mutex);
		state = STATE_B;
		pthread_mutex_unlock(&mutex);
		
		i++;
	}

	return 0;
}

void* threadB(){
	int n = 0, rValue;

	while(n < 5){
		pthread_mutex_lock(&mutex);
		while(state == STATE_A){
			usleep(10);
			puts("B");
		}
		pthread_mutex_unlock(&mutex);

		printf("Goodbye\n");

		pthread_mutex_lock(&mutex);
		state = STATE_A;
		pthread_mutex_unlock(&mutex);
		
		n++;
	}

	return 0;
}

int main(void){
	pthread_t a, b;
	
	pthread_create(&a, NULL, threadA, NULL);
	pthread_create(&b, NULL, threadB, NULL);

	pthread_join(a, NULL);
	pthread_join(b, NULL);

	return 0;
}
