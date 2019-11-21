/*
 * list.h
 *
 *  Created on: Nov 21, 2019
 *      Author: sdragoi
 */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define _XOPEN_SOURCE 600
#define NUM_THREADS 3

void print_element(int);

typedef struct node {
	struct node *next;
	void (*callback_print)(int);
	int value;

} node_t;

node_t* create_node(int);

int add_node(int, node_t**, pthread_mutex_t* mutex, int);
int delete_node(int, node_t**, pthread_mutex_t* mutex, int);
int print_list(int, node_t**, pthread_mutex_t* mutex);
int sort_list(int, node_t**, pthread_mutex_t* mutex);
int flush_list(int, node_t**, pthread_mutex_t* mutex);
