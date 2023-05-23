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

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Task.h"

int check_prime(unsigned int num) {
	if (num <= 2)
		return 0;

	unsigned int root = (unsigned int)sqrt(num);

	for (unsigned int i = 3; i <= root; i += 2)
	{
		if (num % i == 0)
			return 0;
	}

	return 1;
}