/*
 *  Operation Systems (OSs) Course Assignment 5
 *  Active Object (AO) - Tasks Header File
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

#ifndef _TASK_H
#define _TASK_H

/*
 * @brief A struct representing a task.
 * @param numbers The number of numbers to check.
 * @param seed The seed for the random number generator.
 * @param num The number to check.
 * @note The struct is not thread safe by default.
*/
typedef struct _Task {

	/*
	 * @brief The number of numbers to check.
	*/
	int numbers;

	/*
	 * @brief The seed for the random number generator.
	 * @note If this value is 0, the seed will be generated randomly.
	*/
	long seed;

	/*
	 * @brief The number to check.
	*/
	unsigned int num;
} Task, *PTask;

/*
 * @brief The function checks if a given number is a prime number.
 * @param num The number to check.
 * @return 1 if the number is prime, 0 otherwise.
 * @note The function is not thread safe by default.
 * @note The function checks only odd numbers.
 */
int check_prime(unsigned int num);

#endif // _TASK_H
