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

#ifndef _TASKS_H
#define _TASKS_H

#include "ActiveObject.h"

/********************/
/* Settings Section */
/********************/

/*
 * @brief The number of active objects.
 * @note The number of active objects must be greater than 0.
 * @note The default number of active objects is 4.
 */
#define ACTIVE_OBJECTS_NUM 4

/********************************/
/* Function Declaratios Section */
/********************************/

/*
 * @brief The first active object task. The active object generates random numbers and
			sends them to the queue of the second active object, one by one, 1ms apart from each other, and then dies.
 * @param task The task's argument (A Task object).
 * @return Always returns 1 after the task is done, as the Active Object should die after the task is done.
 * @note The task is using the passed arguments to determine the number of random numbers to generate,
			and the seed for the random number generator.
*/
int ActiveObjectTask1(void *task);

/*
 * @brief The second active object task. The active object receives random numbers from the queue of the first active object,
			and checks if they are prime numbers, prints the result to the standard output, adds 11 to the number,
			and sends it to the queue of the third active object.
 * @param task The task's argument (A Task object).
 * @return 1 If the task should continue executing, 0 if the task should stop executing.
 * @note The task checks if a given number is a prime number.
 * @note The task prints the result to the standard output.
*/
int ActiveObjectTask2(void *task);

/*
 * @brief The third active object task. The active object receives numbers from the queue of the second active object,
			and checks if they are prime numbers, prints the result to the standard output, subtracts 13 from the number,
			and sends it to the queue of the fourth active object.
 * @param task The task's argument (A Task object).
 * @return 1 If the task should continue executing, 0 if the task should stop executing.
 * @note The task checks if a given number is a prime number.
 * @note The task prints the result to the standard output.
*/
int ActiveObjectTask3(void *task);

/*
 * @brief The fourth active object task. The active object receives numbers from the queue of the third active object,
			and checks if they are prime numbers, prints the result to the standard output, adds 2 to the number,
			and prints the result to the standard output. The final print should be the same as the first print of
			the number from the second active object.
 * @param task The task's argument (A Task object).
 * @return 1 If the task should continue executing, 0 if the task should stop executing.
 * @note The task checks if a given number is a prime number.
 * @note The task prints the result to the standard output.
*/
int ActiveObjectTask4(void *task);

#endif // _TASKS_H
