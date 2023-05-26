/*
 *  Operation Systems (OSs) Course Assignment 5
 *  Active Object (AO) - Task Implementation
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

#include "Task.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>

int check_prime(unsigned int num) {
	if (num <= 2 || num % 2 == 0)
		return 0;

	unsigned int root = (unsigned int)sqrt(num);

	for (unsigned int i = 3; i <= root; i += 2)
	{
		if (num % i == 0)
			return 0;
	}

	return 1;
}

PTask createTask(unsigned int num_of_tasks, unsigned int _data) {
	PTask task = (PTask)malloc(sizeof(Task));

	if (task == NULL)
	{
		perror("malloc() failed");
		return NULL;
	}

	task->num_of_tasks = num_of_tasks;
	task->_data = _data;

	return task;
}

void destroyTask(PTask task) {
	if (task == NULL)
	{
		fprintf(stderr, "destroyTask() failed: task is NULL\n");
		return;
	}

	free(task);
}

void printTask(PTask task) {
	if (task == NULL)
	{
		fprintf(stderr, "printTask() failed: task is NULL\n");
		return;
	}

	printf("Task: %u %u\n", task->num_of_tasks, task->_data);
}