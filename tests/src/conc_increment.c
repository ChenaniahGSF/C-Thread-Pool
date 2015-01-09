#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include "../../thpool.h"

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int sum=0;


void add_one() {
	pthread_mutex_lock(&mutex);
	sum ++;
	pthread_mutex_unlock(&mutex);
}


int main(int argc, char *argv[]){
	
	char* p;
	if (argc != 3){
		puts("This testfile needs excactly two arguments");
		exit(1);
	}
	int jobs    = strtol(argv[1], &p, 10);
	int threads = strtol(argv[2], &p, 10);

	thpool_t* threadpool;
	threadpool = thpool_init(threads);
	
	int n;
	for (n=0; n<jobs; n++){
		thpool_add_work(threadpool, (void*)add_one, NULL);
	}
	
	thpool_wait(threadpool);

	printf("%d\n", sum);

	return 0;
}
