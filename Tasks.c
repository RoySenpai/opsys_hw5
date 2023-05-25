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


#include "ActiveObject.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

extern PActiveObject *ActiveObjects_Array;

int ActiveObjectTask1(void *task) {
    PTask task_init = (PTask) task;
	PQueue queue = NULL;

    unsigned int n = task_init->n1;
    unsigned int seed = task_init->n2;

    if (seed == 0)
        seed = time(NULL);

    srand(seed);

    for (unsigned int i = 0; i < n; i++)
	{
        unsigned int num = (rand() % 900000) + 100000;

        PTask task_data = (PTask) malloc(sizeof(Task));

        if (task_data == NULL)
		{
            printf("Error: malloc has failed\n");
            exit(1);
        }

        task_data->n1 = n;
		task_data->n2 = num;

        do
		{
			queue = getQueue(*(ActiveObjects_Array + 1));
		}

		while (queue == NULL);

		queueEnqueue(queue, task_data);

		usleep(1000);
    }

	free(task_init);

	return 0;
}

int ActiveObjectTask2(void *task) {
	static unsigned int count = 0;
	PTask task_data = (PTask) task;
	PQueue queue = NULL;

	unsigned int iterations = task_data->n1;
	unsigned int num = task_data->n2;

	fprintf(stdout, "%u\n%s\n", num, check_prime(num) ? "true" : "false");

	task_data->n2 += 11;

	do
	{
		queue = getQueue(*(ActiveObjects_Array + 2));
	}

	while (queue == NULL);

	queueEnqueue(queue, task_data);
	usleep(1000);

	if (iterations <= ++count)
		return 0;

	return 1;
}

int ActiveObjectTask3(void *task) {
	static unsigned int count = 0;
	PQueue queue = NULL;
	PTask task_data = (PTask) task;

	unsigned int iterations = task_data->n1;
	unsigned int num = task_data->n2;

	fprintf(stdout, "%u\n%s\n", num, check_prime(num) ? "true" : "false");

	task_data->n2 -= 13;

	do
	{
		queue = getQueue(*(ActiveObjects_Array + 3));
	}

	while (queue == NULL);

	queueEnqueue(queue, task_data);
	usleep(1000);

	if (iterations <= ++count)
		return 0;

	return 1;
}

int ActiveObjectTask4(void *task) {
	static unsigned int count = 0;
	PTask task_data = (PTask) task;

	unsigned int iterations = task_data->n1;
	unsigned int num = task_data->n2;

	fprintf(stdout, "%u\n%s\n", num, check_prime(num) ? "true" : "false");

	num += 2;

	fprintf(stdout, "%u\n", num);

	free(task_data);
	
	if (iterations <= ++count)
		return 0;
	
	return 1;
}