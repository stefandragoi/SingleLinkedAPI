/*
 * utils.h
 *
 *  Created on: Nov 20, 2019
 *      Author: sdragoi
 */

#ifndef UTILS_H_
#define UTILS_H_

#define _XOPEN_SOURCE 600

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

struct node {
	struct node* next;
	void (*callback_print)(int);
	int value;

};

void print_element(int);
struct node* create_node(int);
void add_node(pthread_mutex_t*, int);
void delete_node(pthread_mutex_t*, int);
void print_list(pthread_mutex_t*);
void sort_list(pthread_mutex_t*);
void flush_list(pthread_mutex_t*);

#endif /* UTILS_H_ */
