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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ActiveObject.h"
#include "Tasks.h"

int main(int argc, char **args) {
	int n = 0;
	long seed = 0;

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
			seed = time(NULL);
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

	fprintf(stdout, "main() started with %d tasks and seed %ld\n", n, seed);

	return 0;
}