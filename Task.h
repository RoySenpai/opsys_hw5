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

#if !defined(_XOPEN_SOURCE) && !defined(_POSIX_C_SOURCE)
	#if __STDC_VERSION__ >= 199901L
		#define _XOPEN_SOURCE 600   /* SUS v3, POSIX 1003.1 2004 (POSIX 2001 + Corrigenda) */
	#else
		#define _XOPEN_SOURCE 500   /* SUS v2, POSIX 1003.1 1997 */
	#endif /* __STDC_VERSION__ */
#endif /* !_XOPEN_SOURCE && !_POSIX_C_SOURCE */

/*
 * @brief A macro for printing debug messages.
*/
#define DEBUG_MESSAGES 1

/*
 * @brief A struct representing a task initialization data.
 * @param n The number of numbers to check.
 * @param seed The seed for the random number generator.
 * @note The struct is not thread safe by default.
*/
typedef struct _Task_Init_Data {
	int n;
	long seed;
} TaskInit, *PTaskInit;

/*
 * @brief A struct representing a task data.
 * @param num The number to check.
 * @note The struct is not thread safe by default.
*/
typedef struct _Task_Data {
	unsigned long num;
} TaskData, *PTaskData;

/*
 * @brief The function checks if a given number is a prime number.
 * @param num The number to check.
 * @return 1 if the number is prime, 0 otherwise.
 * @note The function is not thread safe by default.
 * @note The function checks only odd numbers.
 */
int check_prime(unsigned int num);

#endif // _TASK_H
