/*
 *  Operation Systems (OSs) Course Assignment 5
 *  Active Object (AO) - Queue Implementation
 *  Copyright (C) 2023  Roy Simanovich and Linor Ronen
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "Queue.h"
#include <stdio.h>
#include <stdlib.h>

PQueue queueCreate() {
	PQueue queue = (PQueue)malloc(sizeof(Queue));

	if (queue == NULL)
	{
		perror("malloc() failed");
		return NULL;
	}

	queue->head = NULL;
	queue->tail = NULL;
	queue->size = 0;

	pthread_mutex_init(&queue->lock, NULL);

	return queue;
}

void queueDestroy(PQueue queue) {
	if (queue == NULL)
	{
		fprintf(stderr, "queueDestroy() failed: queue is NULL\n");
		return;
	}

	pthread_mutex_lock(&queue->lock);

	PQueueNode node = queue->head;

	// If the queue isn't empty, free all the nodes and free the data they hold.
	while (node != NULL)
	{
		PQueueNode next = node->next;
		free(node->data);
		free(node);
		node = next;
	}

	pthread_mutex_unlock(&queue->lock);
	pthread_mutex_destroy(&queue->lock);
	free(queue);
}

void queueEnqueue(PQueue queue, void *data) {
	if (queue == NULL)
	{
		fprintf(stderr, "queueEnqueue() failed: queue is NULL\n");
		return;
	}

	PQueueNode node = (PQueueNode)malloc(sizeof(QueueNode));

	if (node == NULL)
	{
		perror("malloc() failed");
		return;
	}

	node->data = data;
	node->next = NULL;

	pthread_mutex_lock(&queue->lock);

	if (queue->head == NULL)
	{
		queue->head = node;
		queue->tail = node;
	}

	else
	{
		queue->tail->next = node;
		queue->tail = node;
	}

	queue->size++;

	pthread_mutex_unlock(&queue->lock);
}

void *queueDequeue(PQueue queue) {
	if (queue == NULL)
	{
		fprintf(stderr, "queueDequeue() failed: queue is NULL\n");
		return NULL;
	}

	pthread_mutex_lock(&queue->lock);

	if (queue->head == NULL)
	{
		pthread_mutex_unlock(&queue->lock);
		return NULL;
	}

	PQueueNode node = queue->head;
	void *data = node->data;

	queue->head = node->next;

	if (queue->head == NULL)
		queue->tail = NULL;

	free(node);
	queue->size--;

	pthread_mutex_unlock(&queue->lock);

	return data;
}

int queueIsEmpty(PQueue queue) {
	if (queue == NULL)
	{
		fprintf(stderr, "queueIsEmpty() failed: queue is NULL\n");
		return -1;
	}

	pthread_mutex_lock(&queue->lock);
	int isEmpty = (queue->size == 0);
	pthread_mutex_unlock(&queue->lock);

	return isEmpty;
}

#if DEBUG_MESSAGES == 1
	int queueSize(PQueue queue) {
		if (queue == NULL)
		{
			fprintf(stderr, "queueSize() failed: queue is NULL\n");
			return -1;
		}

		pthread_mutex_lock(&queue->lock);
		int size = queue->size;
		pthread_mutex_unlock(&queue->lock);

		return size;
	}

	void *queuePeek(PQueue queue) {
		if (queue == NULL)
		{
			fprintf(stderr, "queuePeek() failed: queue is NULL\n");
			return NULL;
		}

		pthread_mutex_lock(&queue->lock);

		if (queue->head == NULL)
		{
			pthread_mutex_unlock(&queue->lock);
			return NULL;
		}

		void *data = queue->head->data;

		pthread_mutex_unlock(&queue->lock);

		return data;
	}

	void *queuePeekTail(PQueue queue) {
		if (queue == NULL)
		{
			fprintf(stderr, "queuePeekTail() failed: queue is NULL\n");
			return NULL;
		}

		pthread_mutex_lock(&queue->lock);

		if (queue->tail == NULL)
		{
			pthread_mutex_unlock(&queue->lock);
			return NULL;
		}

		void *data = queue->tail->data;

		pthread_mutex_unlock(&queue->lock);

		return data;
	}
#endif // DEBUG_MESSAGES