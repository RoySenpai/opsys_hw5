/*
 *  Operation Systems (OSs) Course Assignment 5
 *  Active Object (AO) - Queue Header File
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

#ifndef _QUEUE_H
#define _QUEUE_H

#include "Task.h"
#include <pthread.h>


/******************************/
/* Struct Definitions Section */
/******************************/

/*
 * @brief A queue node struct.
 * @param data The data stored in the node.
 * @param next The next node in the queue.
 * @note This struct is used to store data in the queue.
*/
typedef struct _QueueNode {
	/*
	 * @brief The data stored in the node.
	 * @note This is a void pointer, so it can be used to store any type of data.
	*/
	void *data;

	/*
	 * @brief The next node in the queue.
	 * @note This is a pointer to a QueueNode struct.
	*/
	struct _QueueNode *next;
} QueueNode, *PQueueNode;

/*
 * @brief A queue struct.
 * @param head The head of the queue.
 * @param tail The tail of the queue.
 * @param size The number of nodes in the queue.
 * @param lock A mutex lock for the queue, to make the queue thread-safe.
 * @note This struct is used to represent the queue itself.
*/
typedef struct _Queue {

	/*
	 * @brief The head of the queue.
	 * @note This is a pointer to a QueueNode struct.
	*/
	PQueueNode head;

	/*
	 * @brief The tail of the queue.
	 * @note This is a pointer to a QueueNode struct.
	*/
	PQueueNode tail;

	/*
	 * @brief The number of nodes in the queue.
	*/
	unsigned int size;

	/*
	 * @brief A mutex lock for the queue.
	 * @note When a thread wants to access the queue, it must first lock it.
	 * @note When a thread is done accessing the queue, it must unlock it.
	 * @note This is a pointer to a pthread_mutex_t struct.
	*/
	pthread_mutex_t lock;
} Queue, *PQueue;


/********************************/
/* Function Declaratios Section */
/********************************/

/*
 * @brief Creates a new queue.
 * @return A pointer to the new queue.
 * @note The user is responsible for freeing the memory of the queue with queueDestroy().
*/
PQueue queueCreate();

/*
 * @brief Destroys a queue.
 * @param queue A pointer to the queue to destroy.
*/
void queueDestroy(PQueue queue);

/*
 * @brief Enqueues data to the queue.
 * @param queue A pointer to the queue to enqueue to.
 * @param data A pointer to the data to enqueue.
*/
void queueEnqueue(PQueue queue, void *data);

/*
 * @brief Dequeues data from the queue.
 * @param queue A pointer to the queue to dequeue from.
 * @return A pointer to the dequeued data.
*/
void *queueDequeue(PQueue queue);

/*
 * @brief Checks if the queue is empty.
 * @param queue A pointer to the queue to check.
 * @return 1 if the queue is empty, 0 otherwise.
*/
int queueIsEmpty(PQueue queue);

#endif // _QUEUE_H