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
#include <string.h>
#include <time.h>
#include <unistd.h>

// An array of pointers to Active Objects, used by the active objects functions.
PActiveObject *ActiveObjects_Array = NULL;

int main(int argc, char **args) {
	unsigned int n = 0, seed = 0;

	// Check the number of arguments, and validate them.
	switch(argc)
	{
		case 1:
		{
			fprintf(stderr, "Usage: %s <n> [<seed>]\n", *args);
			return 1;
		}

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

		default:
		{
			fprintf(stderr, "main() failed: too many arguments\n");
			return 1;
		}
	}

	// Memory allocations for the ActiveObjects_Array, Functions_Array and task_init.
	ActiveObjects_Array = (PActiveObject *) malloc(sizeof(PActiveObject) * ACTIVE_OBJECTS_NUM);
	PQueueFunc *Functions_Array = (PQueueFunc *) malloc(sizeof(PQueueFunc) * ACTIVE_OBJECTS_NUM);
	PTask task_init = (PTask) malloc(sizeof(Task));

	if (task_init == NULL || Functions_Array == NULL || ActiveObjects_Array == NULL)
	{
		perror("malloc() falied\n");
		return 1;
	}

	// Initialize the task_init.
	task_init->num_of_tasks = n;
	task_init->_data = seed;

	// Initialize the Functions_Array which contains the functions pointers for each Active Object.
	*(Functions_Array) = ActiveObjectTask1;
	*(Functions_Array + 1) = ActiveObjectTask2;
	*(Functions_Array + 2) = ActiveObjectTask3;
	*(Functions_Array + 3) = ActiveObjectTask4;

	// Create the Active Objects.
	for (int i = 0; i < ACTIVE_OBJECTS_NUM; i++)
	{
		*(ActiveObjects_Array + i) = CreateActiveObject(*(Functions_Array + i));

		if (*(ActiveObjects_Array + i) == NULL)
		{
			fprintf(stderr, "createActiveObject() failed\n");
			return 1;
		}
	}

	// Queue the first task to the queue of the first Active Object.
	PQueue queue = getQueue(*(ActiveObjects_Array));
	queueEnqueue(queue, task_init);

	// Join the threads.
	for (int i = 0; i < ACTIVE_OBJECTS_NUM; i++)
	{
		int ret = pthread_join((*(ActiveObjects_Array + i))->thread, NULL);

		if (ret != 0)
		{
			fprintf(stderr, "pthread_join() failed: %s\n", strerror(ret));
			stopActiveObject(*(ActiveObjects_Array));
			stopActiveObject(*(ActiveObjects_Array + 1));
			stopActiveObject(*(ActiveObjects_Array + 2));
			stopActiveObject(*(ActiveObjects_Array + 3));
			free(Functions_Array);
			free(ActiveObjects_Array);
			return 1;
		}
	}

	// Clean up the active objects after the threads are done.
	for (int i = 0; i < ACTIVE_OBJECTS_NUM; i++)
		stopActiveObject(*(ActiveObjects_Array + i));

	// Free all remaining memory allocations.
	free(Functions_Array);
	free(ActiveObjects_Array);

	return 0;
}