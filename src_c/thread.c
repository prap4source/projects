/*
 * Copyright 2017 Pradeep Gopanapalli
 * thread.c
 *
 */
#include <pthread.h>
#include "common.h"
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int count = 0;

/* Print odd/even numbers sequentially */
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

/* Classic producer consumer problem with ring */
#define MAX_SIZE 16
#define MAX_ALLOWED (100 * MAX_SIZE)
typedef struct ring_buffer_s {
	int head;
	int tail;
	long int count;
	int buffer[MAX_SIZE];
	pthread_mutex_t lock;
	pthread_cond_t cond;
} *ring_buffer;

void *prod_func(void *args) {
	ring_buffer ring = (ring_buffer)args;
	
	while (1) {
		pthread_mutex_lock(&ring->lock);
		/* Check ring full condition */
		while (ring->head == ((ring->tail + 1 + MAX_SIZE) % MAX_SIZE)) {
			log_err("[ERR]: Ring full head:%d tail%d \n", ring->head, ring->tail);
			pthread_cond_wait(&ring->cond, &ring->lock);
		}
		/* Produce element */
		ring->buffer[ring->tail] = rand() + ring->head;
		log_info("Produced element head:%d tail%d count:%ld buffer:%d\n", 
				ring->head, ring->tail, ring->count, ring->buffer[ring->tail]);
		/* Increment tail */
		ring->tail = (ring->tail + 1) % MAX_SIZE;
		ring->count++;

		pthread_cond_signal(&ring->cond);
		pthread_mutex_unlock(&ring->lock);

		/* Run threads until max count is less than MAX_ALLOWED */
		if (ring->count == MAX_ALLOWED)
			return NULL;
	}
	return NULL;
}

void *cons_func(void *args) {
	ring_buffer ring = (ring_buffer)args;
	int element;
	
	while (1) {
		pthread_mutex_lock(&ring->lock);
		/* Check ring empty condition */
		while (ring->head == ring->tail) {
			log_err("[ERR]: Ring Empty head:%d tail%d \n", ring->head, ring->tail);
			pthread_cond_wait(&ring->cond, &ring->lock);
		}
		/* Produce element */
		element = ring->buffer[ring->head];
		log_info("Consumed element head:%d tail%d buffer:%d\n", 
				ring->head, ring->tail, element);
		/* Increment tail */
		ring->head = (ring->head + 1) % MAX_SIZE;

		pthread_cond_signal(&ring->cond);
		pthread_mutex_unlock(&ring->lock);

		/* Run threads until max count is less than MAX_ALLOWED */
		if (ring->count == MAX_ALLOWED)
			return NULL;

	}
	return NULL;
}

void producer_consumer() {
	/* Create thread */
	pthread_t producer, consumer;
	/* Create Ring buffer */
	ring_buffer ring = malloc(sizeof(*ring));
	if (ring == NULL)
		return;

	/* Initialize Ring elements */
	ring->tail = ring->head = ring->count = 0;
	/*Initialize locks */
	pthread_mutex_init(&ring->lock, NULL);
	pthread_cond_init(&ring->cond, NULL);
	log_info("Initialized ring head:%d tail%d \n", ring->head, ring->tail);

	/* Create threads */
	if (pthread_create(&producer, NULL, prod_func, (void *)ring)) {
		log_err("Error creating producer \n");
		return;
	}
	if (pthread_create(&consumer, NULL, cons_func, (void *)ring)) {
		log_err("Error creating consumer \n");
		return;
	}

	/* Join threads */
	pthread_join(producer, NULL);
	pthread_join(consumer, NULL);

	/* Destroy locks */
	pthread_cond_destroy(&ring->cond);
	pthread_mutex_destroy(&ring->lock);

	log_info("Total head:%d tail%d count:%ld \n", ring->head, ring->tail, ring->count);
	free(ring);	
}

void start_thrtests(int argc, char *argv[]) {
	if (argc <= 2) {
		log_err("Use <%s> <%s> <prod_cons/odd_even>", argv[0], argv[1]);
		return;
	}
	if (!strcmp(argv[2], "prod_cons")){
		/* staring Producer consumer */
		producer_consumer();
	} else if (!strcmp(argv[2], "odd_even")){
		/* staring odd even */
		odd_even();
	} else {
		log_err("Use <%s> <%s> <prod_cons/odd_even>", argv[0], argv[1]);
	}
}
