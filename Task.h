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

/********************/
/* Includes Section */
/********************/

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
 * @note The struct is used to pass data to the active objects.
*/
typedef struct _Task {

	/*
	 * @brief The number of tasks to generate.
	 * @note In the context of the assignment, this is the number of tasks to generate for the producer.
	 * 			For the consumers, this is the number of tasks to consume.
	 * @warning Only the producer should set this field, and only once. The consumers should only read this field.
	*/
	unsigned int num_of_tasks;

	/*
	 * @brief Genereic purpose unsigned integer.
	 * @note In the context of the assignment, For Active Object 1 (Producer) it is the seed for the random number generator.
	 * 			For Active Objects 2-4 (First, second and third consumers) its the generated number itself.
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

/*
 * @brief The function creates a task.
 * @param num_of_tasks The number of tasks to generate.
 * @param _data Genereic purpose unsigned integer.
 * @return A pointer to the created task, NULL otherwise.
 * @note The function is not thread safe by default.
 */
PTask createTask(unsigned int num_of_tasks, unsigned int _data);

/*
 * @brief The function destroys a task.
 * @param task A pointer to the task to destroy.
 * @note The function is not thread safe by default.
 */
void destroyTask(PTask task);

/*
 * @brief The function prints a task.
 * @param task A pointer to the task to print.
 * @note The function is not thread safe by default.
 * @note The function prints the task in the following format: "Task: <num_of_tasks> <_data>".
 * @note Used for debugging purposes only.
 */
void printTask(PTask task);

#endif // _TASK_H
