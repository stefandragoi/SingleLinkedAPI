/*
 * main.c
 *
 *  Created on: Nov 20, 2019
 *      Author: sdragoi
 */
#include "list.h"

typedef struct {
	int id;
} thread_info_t;

pthread_mutex_t mutex;
pthread_barrier_t barrier;

node_t *head;

void* thread_job(void *arg) {
	int id;
	thread_info_t* t_info;
	t_info = (thread_info_t*)arg;

	id = t_info->id;

	pthread_barrier_wait(&barrier);

	switch(id) {
	case 0:
		add_node(id, &head, &mutex, 2);
		add_node(id, &head, &mutex, 10);
		add_node(id, &head, &mutex, 4);
		delete_node(id, &head, &mutex, 2);
		sort_list(id, &head, &mutex);
		delete_node(id, &head, &mutex, 10);
		delete_node(id, &head, &mutex, 5);
	break;
	case 1:
		add_node(id, &head, &mutex, 11);
		add_node(id, &head, &mutex, 1);
		delete_node(id, &head, &mutex, 11);
		add_node(id, &head, &mutex, 8);
		print_list(id, &head, &mutex);
	break;
	case 2:
		add_node(id, &head, &mutex, 30);
		add_node(id, &head, &mutex, 25);
		add_node(id, &head, &mutex, 100);
		sort_list(id, &head, &mutex);
		print_list(id, &head, &mutex);
		delete_node(id, &head, &mutex, 100);
	break;
	default:
	break;
	}

	return NULL;
}

int main() {
	int i;
	thread_info_t t_info[NUM_THREADS];
	pthread_t threads[NUM_THREADS];

	head = NULL;
	pthread_barrier_init(&barrier, NULL, NUM_THREADS);
    pthread_mutex_init(&mutex, NULL);

	for (i = 0; i < NUM_THREADS; i++) {
		t_info[i].id = i;
		if (pthread_create(&threads[i], NULL, &thread_job, (void *)&t_info[i])) {
			printf("Error creating thread number %d\n", i);
			return 1;
		}
	}

	for (i = 0; i < NUM_THREADS; i++) {
		if (pthread_join(threads[i], NULL))
			printf("Error joining thread number %d\n", i);
	}

	pthread_barrier_destroy(&barrier);

	printf("Done!\n");
	return 0;
}
