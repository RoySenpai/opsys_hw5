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

#include "ActiveObject.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define ACTIVE_OBJECTS_NUM 4

PActiveObject *ActiveObjects_Array = NULL;

int main(int argc, char **args) {
	unsigned int n = 0;
	unsigned int seed = 0;

	switch(argc)
	{
		case 1:
		{
			fprintf(stderr, "main() failed: not enough arguments\n");
			return 1;
		}

		case 2:
		{
			n = atoi(*(args + 1));
			seed = 0;
			break;
		}

		case 3:
		{
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

	ActiveObjects_Array = (PActiveObject *) malloc(sizeof(PActiveObject) * ACTIVE_OBJECTS_NUM);
	PQueueFunc *Functions_Array = (PQueueFunc *) malloc(sizeof(PQueueFunc) * ACTIVE_OBJECTS_NUM);
	PTask task_init = (PTask) malloc(sizeof(Task));

	if (task_init == NULL || Functions_Array == NULL || ActiveObjects_Array == NULL)
	{
		perror("malloc() falied\n");
		return 1;
	}

	task_init->n1 = n;
	task_init->n2 = seed;

	*(Functions_Array) = ActiveObjectTask1;
	*(Functions_Array + 1) = ActiveObjectTask2;
	*(Functions_Array + 2) = ActiveObjectTask3;
	*(Functions_Array + 3) = ActiveObjectTask4;

	for (int i = 0; i < ACTIVE_OBJECTS_NUM; i++)
	{
		*(ActiveObjects_Array + i) = CreateActiveObject(*(Functions_Array + i));

		if (*(ActiveObjects_Array + i) == NULL)
		{
			fprintf(stderr, "createActiveObject() failed\n");
			return 1;
		}

		else if (i == 0)
		{
			PQueue queue = getQueue(*(ActiveObjects_Array));
			queueEnqueue(queue, task_init);
		}
	}

	for (int i = 0; i < ACTIVE_OBJECTS_NUM; i++)
		pthread_join((*(ActiveObjects_Array + i))->thread, NULL);

	for (int i = 0; i < ACTIVE_OBJECTS_NUM; i++)
		stopActiveObject(*(ActiveObjects_Array + i));

	free(Functions_Array);
	free(ActiveObjects_Array);

	return 0;
}