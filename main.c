/*
 * main.c
 *
 *  Created on: Nov 20, 2019
 *      Author: sdragoi
 */
#include <stdio.h>
#include <pthread.h>

static void *show(void *arg)
{
	printf("This is thread %u\n", pthread_self());

	return NULL;
}

int main() {
	printf("Hello World!\n");

	pthread_t ths[3];
	int j;

	for (j = 0; j < 3; j++)
		pthread_create(&ths[j], NULL, &show, NULL);

	for (j = 0; j < 3; j++)
		pthread_join(ths[j], NULL);

	return 0;
}
