/*
 * main.c
 *
 *  Created on: Nov 20, 2019
 *      Author: sdragoi
 */
#include "list.h"

pthread_mutex_t mutex;
struct node *head;

void* thread1_job(void *arg) {
	pthread_barrier_t *barrier;
	barrier = (pthread_barrier_t*) arg;
	pthread_barrier_wait(barrier);

	add_node(&head, &mutex, 2);
	add_node(&head, &mutex, 10);
	add_node(&head, &mutex, 4);
	delete_node(&head, &mutex, 2);
	sort_list(&head, &mutex);
	delete_node(&head, &mutex, 10);
	delete_node(&head, &mutex, 5);

	return NULL;
}

void* thread2_job(void *arg) {
	pthread_barrier_t *barrier;
	barrier = (pthread_barrier_t*) arg;
	pthread_barrier_wait(barrier);

	add_node(&head, &mutex, 11);
	add_node(&head, &mutex, 1);
	delete_node(&head, &mutex, 11);
	add_node(&head, &mutex, 8);
	print_list(&head, &mutex);

	return NULL;
}

void* thread3_job(void *arg) {
	pthread_barrier_t *barrier;
	barrier = (pthread_barrier_t*) arg;
	pthread_barrier_wait(barrier);

	add_node(&head, &mutex, 30);
	add_node(&head, &mutex, 25);
	add_node(&head, &mutex, 100);
	sort_list(&head, &mutex);
	print_list(&head, &mutex);
	delete_node(&head, &mutex, 100);

	return NULL;
}

int main() {
	head = NULL;

	pthread_barrier_t barrier;
	pthread_barrier_init(&barrier, NULL, NUM_THREADS);

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
