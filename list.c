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

node_t* create_node(int data) {
	node_t* new_node;

	new_node = malloc(sizeof(*new_node));
	new_node->next = NULL;
	new_node->callback_print = print_element;
	new_node->value = data;

	return new_node;
}

int add_node(int id, node_t **head, pthread_mutex_t* mutex, int data) {
	node_t* prev_node;
	node_t* new_node;

	if (mutex == NULL) {
		printf("Invalid mutex variable\n");
		return 0;
	}

	pthread_mutex_lock(mutex);
	prev_node = *head;
	new_node = create_node(data);
	if (NULL == new_node) {
		printf("Thread no. %d tried to add the following element: %d, malloc failed\n", id, data);
		pthread_mutex_unlock(mutex);
		return 0;
	}

	if (NULL == *head) {
		*head = new_node;
	} else {
		while (NULL != prev_node->next)
			prev_node = prev_node->next;

		prev_node->next = new_node;
	}

	printf("Thread no. %d added the following element: %d\n", id, data);
	pthread_mutex_unlock(mutex);
	return 1;
}

int delete_node(int id, node_t **head, pthread_mutex_t* mutex, int data) {
	node_t* current_node;
	node_t* prev_node;

	if (mutex == NULL) {
		printf("Invalid mutex variable\n");
		return 0;
	}

	pthread_mutex_lock(mutex);
	current_node = *head;

	if (NULL == current_node) {
		printf("Thread no. %d tried to delete the following element, list is empty: %d\n", id, data);
		pthread_mutex_unlock(mutex);
		return 0;
	} else if (data == current_node->value) {
		*head = current_node->next;
		free(current_node);
		printf("Thread no. %d deleted the following element: %d\n", id, data);
		pthread_mutex_unlock(mutex);
		return 1;
	} else {
		while (NULL != current_node) {
			if (data == current_node->value) {
				prev_node->next = current_node->next;
				free(current_node);
				printf("Thread no. %d deleted the following element: %d\n", id, data);
				pthread_mutex_unlock(mutex);
				return 1;
			}
			prev_node = current_node;
			current_node = current_node->next;
		}

		printf("Thread no. %d tried to delete the following unavailable element: %d\n", id, data);
		pthread_mutex_unlock(mutex);
		return 0;
	}
}

int print_list(int id, node_t** head, pthread_mutex_t* mutex) {
	node_t* current_node;

	if (mutex == NULL) {
		printf("Invalid mutex variable\n");
		return 0;
	}

	pthread_mutex_lock(mutex);
	current_node = *head;
	printf("Thread no. %d is printing the list: ", id);

	while(NULL != current_node) {
		current_node->callback_print(current_node->value);
		current_node = current_node->next;
	}
	printf("\n");
	pthread_mutex_unlock(mutex);
	return 1;
}

int sort_list(int id, node_t** head, pthread_mutex_t* mutex) {
	int count, i;
	node_t* aux_node;
	node_t* node_j;
	node_t* prev_j;

	if (mutex == NULL) {
		printf("Invalid mutex variable\n");
		return 0;
	}

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

	printf("Thread no. %d sorted the list\n", id);
	pthread_mutex_unlock(mutex);
	return 1;
}

int flush_list(int id, node_t** head, pthread_mutex_t* mutex) {
	node_t* current_node;
	node_t* aux_node;

	if (mutex == NULL) {
		printf("Invalid mutex variable\n");
		return 0;
	}

	pthread_mutex_lock(mutex);
	current_node = *head;
	*head = NULL;
	while(NULL != current_node) {
		aux_node = current_node;
		current_node = current_node->next;
		free(aux_node);
	}

	printf("Thread no. %d flushed the list\n", id);
	pthread_mutex_unlock(mutex);
	return 1;
}
