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
    PTask task_init = (PTask) task;
	PQueue queue = NULL;

    unsigned int n = task_init->num_of_tasks, seed = task_init->_data;

    srand(seed != 0 ? seed : time(NULL));

    for (unsigned int i = 0; i < n; i++)
	{
        unsigned int num = (rand() % 900000) + 100000;

        PTask task_data = (PTask) malloc(sizeof(Task));

        if (task_data == NULL)
		{
            printf("Error: malloc has failed\n");
            exit(1);
        }

        task_data->num_of_tasks = n;
		task_data->_data = num;

		queue = getQueue(*(ActiveObjects_Array + 1));
		queueEnqueue(queue, task_data);

		usleep(1000);
    }

	free(task_init);

	return 0;
}

int ActiveObjectTask2(void *task) {
	static unsigned int count = 0;
	PTask task_data = (PTask) task;

	unsigned int iterations = task_data->num_of_tasks, num = task_data->_data;

	fprintf(stdout, "%u\n%s\n", num, check_prime(num) ? "true" : "false");
	task_data->_data += 11;

	PQueue queue = getQueue(*(ActiveObjects_Array + 2));
	queueEnqueue(queue, task_data);

	if (iterations <= ++count)
		return 0;

	return 1;
}

int ActiveObjectTask3(void *task) {
	static unsigned int count = 0;
	PTask task_data = (PTask) task;

	unsigned int iterations = task_data->num_of_tasks, num = task_data->_data;

	fprintf(stdout, "%u\n%s\n", num, check_prime(num) ? "true" : "false");
	task_data->_data -= 13;

	PQueue queue = getQueue(*(ActiveObjects_Array + 3));
	queueEnqueue(queue, task_data);

	return (iterations <= ++count) ? 0 : 1;
}

int ActiveObjectTask4(void *task) {
	static unsigned int count = 0;
	PTask task_data = (PTask) task;

	unsigned int iterations = task_data->num_of_tasks, num = task_data->_data;

	fprintf(stdout, "%u\n%s\n", num, check_prime(num) ? "true" : "false");
	num += 2;
	fprintf(stdout, "%u\n", num);

	free(task_data);
	
	return (iterations <= ++count) ? 0 : 1;
}