/*
 *  Operation Systems (OSs) Course Assignment 5
 *  Active Object (AO) - Active Object Header File
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

#ifndef _ACTIVE_OBJECT_H
#define _ACTIVE_OBJECT_H

#include "Queue.h"

/*
 * @brief A function pointer that is used to store the function that the active object will execute.
 * @note The function should receive a void pointer and return void.
*/
typedef void (*PQueueFunc)(void *);

/*
 * @brief An active object struct.
 * @param thread The thread that executes the function that is stored in the queue.
 * @param queue The queue that stores the parameters for the function that the
 					active object will pass to the function that is stored in the active object itself.
 * @param func The function that the active object will execute.
 * @note This struct is used to represent the active object itself.
 * @note The active object is a thread that executes a function that is stored in the queue.
*/
typedef struct _ActiveObject {
	/*
	 * @brief The thread that executes the function that is stored in the queue.
	 * @note This is a pthread_t struct.
	 * @note The thread is created when the active object is created.
	*/
	pthread_t thread;

	/*
	 * @brief The queue that stores the parameters for the function that the
	 			active object will pass to the function that is stored in the active object itself.
	 * @note This is a pointer to a Queue struct.
	*/
	PQueue queue;

	/*
	 * @brief The function that the active object will execute.
	 * @note This is a function pointer.
	 * @note The function should return an int and receive an unsigned int.
	*/
	PQueueFunc func;
} ActiveObject, *PActiveObject;

/*
 * @brief Creates an active object and starts its thread.
 * @param func The function that the active object will execute whenever it dequeues a parameter.
 * @return A pointer to the created active object.
 * @note The active object is created with a function pointer that is used to store
 * 			the function that the active object will execute.
 * @note The active object is a thread that executes a function that is stored in the queue.
*/
PActiveObject CreateActiveObject(PQueueFunc func);

/*
 * @brief Returns the queue of the active object.
 * @param activeObject The active object.
 * @return A pointer to the queue that stores the parameters for the function that the
 			active object will pass to the function that is stored in the active object itself.
*/
PQueue getQueue(PActiveObject activeObject);

/*
 * @brief Stops and releases the active object.
 * @param activeObject The active object.
 * @return void.
 * @note This function stops the thread of the active object and releases the memory that was allocated for the active object.
*/
void stopActiveObject(PActiveObject activeObject);

/*
 * @brief The thread function that the active object executes when it is created.
 * @param activeObject The active object itself.
 * @return The active object itself on success, NULL on failure.
*/
void *activeObjectRunFunction(void *activeObject);

#endif // _ACTIVE_OBJECT_H