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

struct node {
	struct node* next;
	void (*callback_print)(int);
	int value;

};

struct node* create_node(int);

void add_node(struct node**, pthread_mutex_t* mutex, int);
void delete_node(struct node **head, pthread_mutex_t* mutex, int);
void print_list(struct node**, pthread_mutex_t* mutex);
void sort_list(struct node** head, pthread_mutex_t* mutex);
void flush_list(struct node** head, pthread_mutex_t* mutex);
