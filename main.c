/*
 * main.c
 *
 *  Created on: Nov 20, 2019
 *      Author: sdragoi
 */
#include "utils.h"

pthread_mutex_t mutex;

void* thread1_job(void *arg) {
	pthread_barrier_t *barrier;
	barrier = (pthread_barrier_t*) arg;
	pthread_barrier_wait(barrier);

	add_node(&mutex, 2);
	add_node(&mutex, 4);
	add_node(&mutex, 10);
	delete_node(&mutex, 2);
	sort_list(&mutex);
	delete_node(&mutex, 10);
	delete_node(&mutex, 5);
	return NULL;
}

void* thread2_job(void *arg) {
	pthread_barrier_t *barrier;
	barrier = (pthread_barrier_t*) arg;
	pthread_barrier_wait(barrier);

	add_node(&mutex, 11);
	add_node(&mutex, 1);
	delete_node(&mutex, 11);
	add_node(&mutex, 8);
	print_list(&mutex);
	return NULL;
}

void* thread3_job(void *arg) {
	pthread_barrier_t *barrier;
	barrier = (pthread_barrier_t*) arg;
	pthread_barrier_wait(barrier);

	add_node(&mutex, 30);
	add_node(&mutex, 25);
	add_node(&mutex, 100);
	sort_list(&mutex);
	print_list(&mutex);
	delete_node(&mutex, 100);
	return NULL;

}

int main() {
	pthread_barrier_t barrier;
	pthread_barrier_init(&barrier, NULL, 2);

    pthread_mutex_init(&mutex, NULL);

	pthread_t thread1, thread2, thread3;
	pthread_create(&thread1, NULL, &thread1_job, (void*)&barrier);
	pthread_create(&thread2, NULL, &thread2_job, (void*)&barrier);
	pthread_create(&thread3, NULL, &thread3_job, (void*)&barrier);

	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	pthread_join(thread3, NULL);

	pthread_barrier_destroy(&barrier);

	printf("Done!\n");
	return 0;
}
