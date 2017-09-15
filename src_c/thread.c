/*
 * Copyright 2017 Pradeep Gopanapalli
 * thread.c
 *
 */
#include <pthread.h>
#include "common.h"
struct  Adapter {
	int data;
	struct Adapter *left;
};
typedef struct Adapter *Adapt;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int count = 0;
void *func(void *ptr)
{
	Adapt ad = (Adapt)ptr;
	printf("%s Data %d\n",__func__,ad->data);
	ad->data += 10;
	return NULL;
}

void thread_withstruc() {
	Adapt ad1 = (Adapt)malloc(sizeof(struct Adapter));
	Adapt ad2 = (Adapt)malloc(sizeof(struct Adapter));
	pthread_t pattr1,pattr2;
	ad1->data =1;
	ad2->data = 2;
	pthread_create(&pattr1,NULL,func,(void *)ad1);
	pthread_create(&pattr2,NULL,func,(void *)ad2);

	pthread_join(pattr1,NULL);
	pthread_join(pattr2,NULL);
	printf("Returned thread %d:%d\n",ad1->data,ad2->data);


}

void *even_func(void *args) {


	while (count < 20) {
		pthread_mutex_lock(&lock);
		while (count % 2)
			pthread_cond_wait(&cond, &lock);
		printf("%s %d \n",__func__, count++);
		pthread_cond_signal(&cond);
		pthread_mutex_unlock(&lock);
	}
	return NULL;
}
void *odd_func(void *args) {
	while (count < 20) {
		pthread_mutex_lock(&lock);
		while (!(count % 2))
			pthread_cond_wait(&cond, &lock);

		printf("%s %d \n",__func__, count++);
		pthread_cond_signal(&cond);
		pthread_mutex_unlock(&lock);
	}
	return NULL;

}

void odd_even() {
	/* Create threads */
	pthread_t odd, even;
	//count = 0;
	/* Intialize locks*/
	pthread_mutex_init(&lock, NULL);
	pthread_cond_init(&cond, NULL);


	pthread_create(&even, NULL,even_func,(void *)NULL);
	pthread_create(&odd, NULL, odd_func, (void *)NULL);
	sleep(1); // sleep will ensure threads wont terminate fast
	pthread_join(even, NULL);
	pthread_join(odd, NULL);

	pthread_mutex_destroy(&lock);
	pthread_cond_destroy(&cond);


}
void start_thrtests(int argc, char *argv[]) {
	pthread_t t1, t2;
}
