/*
 *  Operation Systems (OSs) Course Assignment 5
 *  Active Object (AO) - Main
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

#include "Tasks.h"
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

// An array of pointers to Active Objects, used by the active objects functions.
PActiveObject *ActiveObjects_Array = NULL;

// A pointer to the task_init, which is the first task that is being sent to the queue of the first Active Object, which starts the chain of tasks.
PTask task_init = NULL;

/*
 * @brief The main function of the program.
 * @param argc The number of arguments.
 * @param args The arguments.
 * @return 0 if the program ran successfully, 1 otherwise.
 * @note The main function receives the number of tasks to be created, and the seed for the random number generator.
 * @note The main function creates the Active Objects, and the first task, and then starts the chain of tasks.
 * @note The main function also frees all the allocated memory.
*/
int main(int argc, char **args) {
	// Initialize the Functions_Array which contains the functions pointers for each Active Object.
	PQueueFunc Functions_Array[ACTIVE_OBJECTS_NUM] =
	{
		ActiveObjectTask1,
		ActiveObjectTask2,
		ActiveObjectTask3,
		ActiveObjectTask4
	};

	// Variables for the main function.
	unsigned int n = 0, seed = 0;

	// Check the number of arguments, and validate them.
	switch(argc)
	{
		// If there are no arguments, print the usage message and exit.
		case 1:
		{
			fprintf(stderr, "Usage: %s <n> [<seed>]\n", *args);
			return 1;
		}

		// If there is one argument, validate it.
		case 2:
		{
			if (atoi(*(args + 1)) < 0)
			{
				fprintf(stderr, "Error: n must be a positive integer.\n");
				return 1;
			}

			n = atoi(*(args + 1));

			break;
		}

		// If there are two arguments, validate them.
		case 3:
		{
			if (atoi(*(args + 1)) <= 0)
			{
				fprintf(stderr, "Error: n must be a positive integer.\n");
				return 1;
			}

			else if (atoi(*(args + 2)) <= 0)
			{
				fprintf(stderr, "Error: seed must be a positive integer.\n");
				return 1;
			}

			n = atoi(*(args + 1));
			seed = atoi(*(args + 2));

			break;
		}

		// If there are more than two arguments, print the usage message and exit.
		default:
		{
			fprintf(stderr, "Usage: %s <n> [<seed>]\n", *args);
			return 1;
		}
	}

	// Set the signal handler for SIGINT.
	signal(SIGINT, sigint_handler);

	// Memory allocations for the ActiveObjects_Array, Functions_Array and task_init.
	ActiveObjects_Array = (PActiveObject *) malloc(sizeof(PActiveObject) * ACTIVE_OBJECTS_NUM);
	task_init = createTask(n, seed);

	if (ActiveObjects_Array == NULL || task_init == NULL)
	{
		perror("malloc() falied\n");

		if (ActiveObjects_Array != NULL)
			free(ActiveObjects_Array);

		if (task_init != NULL)
			free(task_init);

		return 1;
	}

	// Create the Active Objects.
	for (int i = 0; i < ACTIVE_OBJECTS_NUM; i++)
	{
		*(ActiveObjects_Array + i) = CreateActiveObject(*(Functions_Array + i));

		if (*(ActiveObjects_Array + i) == NULL)
		{
			fprintf(stderr, "createActiveObject() failed\n");

			for (int j = 0; j < i; j++)
				stopActiveObject(*(ActiveObjects_Array + j));
			
			free(task_init);
			free(ActiveObjects_Array);

			return 1;
		}
	}

	// Queue the first task to the queue of the first Active Object.
	ENQUEUE(getQueue(*(ActiveObjects_Array)), task_init);

	// Join the threads.
	for (int i = 0; i < ACTIVE_OBJECTS_NUM; i++)
	{
		int ret = pthread_join((*(ActiveObjects_Array + i))->thread, NULL);

		if (ret != 0)
		{
			fprintf(stderr, "pthread_join() failed: %s\n", strerror(ret));

			for (int j = 0; j < ACTIVE_OBJECTS_NUM; j++)
				stopActiveObject(*(ActiveObjects_Array + j));
			
			destroyTask(task_init);
			free(ActiveObjects_Array);

			return 1;
		}
	}

	// Clean up the active objects after the threads are done.
	for (int i = 0; i < ACTIVE_OBJECTS_NUM; i++)
		stopActiveObject(*(ActiveObjects_Array + i));

	// Free all remaining memory allocations.
	destroyTask(task_init);
	free(ActiveObjects_Array);

	return 0;
}

void sigint_handler(int sig) {
	// Check if the signal is not SIGINT, as this function is only for SIGINT.
	if (sig != SIGINT)
		return;

	// Check if the ActiveObjects_Array and task_init are not NULL, as free for NULL is a no-op.
	if (ActiveObjects_Array == NULL || task_init == NULL)
		return;

	if (DEBUG_MESSAGES)
		fprintf(stdout, "\nSIGINT was received, memory cleanup is in progress...\n");
	
	// Clean up the active objects if the user pressed CTRL+C.
	for (int i = 0; i < ACTIVE_OBJECTS_NUM; i++)
		stopActiveObject(*(ActiveObjects_Array + i));

	// Free all remaining memory allocations.
	destroyTask(task_init);
	free(ActiveObjects_Array);

	exit(0);
}