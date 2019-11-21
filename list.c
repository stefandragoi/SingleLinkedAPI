/*
 * list.c
 *
 *  Created on: Nov 21, 2019
 *      Author: sdragoi
 */
#include "list.h"

void print_element(int x) {
	printf("%d; ", x);
}

struct node* create_node(int data) {
	struct node* new_node;

	new_node = malloc(sizeof(struct node*));
	new_node->next = NULL;
	new_node->callback_print = print_element;
	new_node->value = data;

	return new_node;
}

void add_node(struct node **head, pthread_mutex_t* mutex, int data) {
	struct node* prev_node;
	struct node* new_node;

	pthread_mutex_lock(mutex);
	prev_node = *head;
	new_node = create_node(data);
	if (NULL == new_node) {
		printf("Thread no. %lu tried to add the following element: %d, malloc failed\n", (unsigned long)pthread_self(), data);
		return;
	}

	if (NULL == prev_node) {
		*head = new_node;
	} else {
		while (NULL != prev_node->next)
			prev_node = prev_node->next;

		prev_node->next = new_node;
	}

	printf("Thread no. %lu added the following element: %d\n", (unsigned long)pthread_self(), data);
	pthread_mutex_unlock(mutex);
}

void delete_node(struct node **head, pthread_mutex_t* mutex, int data) {
	struct node* current_node;
	struct node* prev_node;

	pthread_mutex_lock(mutex);
	current_node = *head;

	if (NULL == current_node) {
		printf("Thread no. %lu tried to delete the following element, list is empty: %d\n", (unsigned long)pthread_self(), data);
		return;
	} else if (data == current_node->value) {
		*head = current_node->next;
		free(current_node);
		printf("Thread no. %lu deleted the following element: %d\n", (unsigned long)pthread_self(), data);
	} else {
		while (NULL != current_node) {
			if (data == current_node->value) {
				prev_node->next = current_node->next;
				free(current_node);
				printf("Thread no. %lu deleted the following element: %d\n", (unsigned long)pthread_self(), data);
				break;
			}
			prev_node = current_node;
			current_node = current_node->next;
		}

		if (NULL == current_node) {
			printf("Thread no. %lu tried to delete the following unavailable element: %d\n", (unsigned long)pthread_self(), data);
		}
	}
	pthread_mutex_unlock(mutex);
}

void print_list(struct node** head, pthread_mutex_t* mutex) {
	struct node* current_node;

	pthread_mutex_lock(mutex);
	current_node = *head;
	printf("Thread no. %lu is printing the list: ", (unsigned long)pthread_self());

	while(NULL != current_node) {
		current_node->callback_print(current_node->value);
		current_node = current_node->next;
	}
	printf("\n");
	pthread_mutex_unlock(mutex);
}

void sort_list(struct node** head, pthread_mutex_t* mutex) {
	int count, i;
	struct node* aux_node;
	struct node* node_j;
	struct node* prev_j;

	pthread_mutex_lock(mutex);
	aux_node = *head;
	count = 0;
	while(NULL != aux_node) {
		count++;
		aux_node = aux_node->next;
	}

	for (i = 0; i < count - 1; i++) {
		node_j = *head;
		prev_j = NULL;

		while(NULL != node_j && NULL != node_j->next) {
			if (node_j->value > node_j->next->value) {
				if (prev_j == NULL)
					*head = node_j->next;
				else
					prev_j->next = node_j->next;

				aux_node = node_j->next;
				node_j->next = node_j->next->next;
				aux_node->next = node_j;
			}

			prev_j = node_j;
			node_j = node_j->next;
		}
	}
	printf("Thread no. %lu sorted the list\n", (unsigned long)pthread_self());
	pthread_mutex_unlock(mutex);
}

void flush_list(struct node** head, pthread_mutex_t* mutex) {
	struct node* current_node;
	struct node* aux_node;

	pthread_mutex_lock(mutex);
	current_node = *head;
	*head = NULL;
	while(NULL != current_node) {
		aux_node = current_node;
		current_node = current_node->next;
		free(aux_node);
	}

	printf("Thread no. %lu flushed the list\n", (unsigned long)pthread_self());
	pthread_mutex_unlock(mutex);
}
