/*
 *  Operation Systems (OSs) Course Assignment 5
 *  Active Object (AO) - Tasks Implementation
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

extern PActiveObject *ActiveObjects_Array;

int ActiveObjectTask1(void *task) {
	PTask task_init = (PTask)task;

	unsigned int n = task_init->num_of_tasks, seed = task_init->_data;

	srand(seed != 0 ? seed : time(NULL));

	for (unsigned int i = 0; i < n; i++)
	{
		unsigned int num = (rand() % 900000) + 100000;

		PTask task_data = createTask(n, num);

		if (task_data == NULL)
		{
			perror("malloc() failed");
			exit(1);
		}

		ENQUEUE(getQueue(*(ActiveObjects_Array + 1)), task_data);

		usleep(1000);
	}

	return 0;
}

int ActiveObjectTask2(void *task) {
	static unsigned int count = 0;
	PTask task_data = (PTask)task;

	unsigned int iterations = task_data->num_of_tasks, num = task_data->_data;

	fprintf(stdout, "%u\n%s\n", num, check_prime(num) ? "true" : "false");

	// This part ensures that the data is passed to the next active object in the chain without any interferences from other threads.
	destroyTask(task_data);

	task_data = createTask(iterations, (num + 11));

	if (task_data == NULL)
	{
		perror("malloc() failed");
		exit(1);
	}

	ENQUEUE(getQueue(*(ActiveObjects_Array + 2)), task_data);

	return (iterations <= ++count) ? 0 : 1;
}

int ActiveObjectTask3(void *task) {
	static unsigned int count = 0;
	PTask task_data = (PTask)task;

	unsigned int iterations = task_data->num_of_tasks, num = task_data->_data;

	fprintf(stdout, "%u\n%s\n", num, check_prime(num) ? "true" : "false");

	// This part ensures that the data is passed to the next active object in the chain without any interferences from other threads.
	destroyTask(task_data);

	task_data = createTask(iterations, (num - 13));

	if (task_data == NULL)
	{
		perror("malloc() failed");
		exit(1);
	}

	ENQUEUE(getQueue(*(ActiveObjects_Array + 3)), task_data);

	return (iterations <= ++count) ? 0 : 1;
}

int ActiveObjectTask4(void *task) {
	static unsigned int count = 0;
	PTask task_data = (PTask)task;

	unsigned int iterations = task_data->num_of_tasks, num = task_data->_data;

	fprintf(stdout, "%u\n%s\n%u\n", num, check_prime(num) ? "true" : "false", (num + 2));

	// Make sure the memory is freed, so we don't have a memory leak.
	// As the task that's passed is allocated in the heap (must, as it's passed to the thread from a different thread and can't be allocated in the stack).
	destroyTask(task_data);

	return (iterations <= ++count) ? 0 : 1;
}