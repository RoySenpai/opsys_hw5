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

/********************/
/* Settings Section */
/********************/

/*
 * @brief A macro for printing debug messages.
 * @note 1 for printing debug messages, 0 otherwise.
 * @note The default value is 0.
*/
#define DEBUG_MESSAGES 0

/*******************/
/* Structs Section */
/*******************/

/*
 * @brief A struct representing a task initialization data.
 * @param num_of_tasks Used to indicate how many tasks to generate.
 * @param _data Genereic purpose unsigned integer.
 * 			For AO1 it is the seed for the random number generator.
 * 			For AO2-4 its the generated number itself.
 * @note The struct is not thread safe by default.
*/
typedef struct _Task {

	/*
	 * @brief The number of tasks to generate.
	*/
	unsigned int num_of_tasks;

	/*
	 * @brief Genereic purpose unsigned integer.
	 * 			For AO1 it is the seed for the random number generator.
	 * 			For AO2-4 its the generated number itself.
	*/
	unsigned int _data;
} Task, *PTask;


/********************************/
/* Function Declaratios Section */
/********************************/

/*
 * @brief The function checks if a given number is a prime number.
 * @param num The number to check.
 * @return 1 if the number is prime, 0 otherwise.
 * @note The function is not thread safe by default.
 * @note The function checks only odd numbers.
 */
int check_prime(unsigned int num);

#endif // _TASK_H
