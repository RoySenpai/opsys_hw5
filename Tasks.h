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

#include "Task.h"

/*
 * @brief The first active object task.
 * @param task The task's argument (A task object).
 * @return An integer, representing the status of the function that the active object will execute:
 *          1 means to continue executing the function that the active object will execute.
 *          0 means to stop executing the function that the active object will execute.
 * @note The task checks if a given number is a prime number.
 * @note The task prints the result to the standard output.
*/
int ActiveObjectTask1(void *task);

/*
 * @brief The second active object task.
 * @param task The task's argument (A task object).
 * @return void.
 * @note The task checks if a given number is a prime number.
 * @note The task prints the result to the standard output.
*/
int ActiveObjectTask2(void *task);

/*
 * @brief The third active object task.
 * @param task The task's argument (A task object).
 * @return An integer, representing the status of the function that the active object will execute:
 *          1 means to continue executing the function that the active object will execute.
 *          0 means to stop executing the function that the active object will execute.
 * @note The task checks if a given number is a prime number.
 * @note The task prints the result to the standard output.
*/
int ActiveObjectTask3(void *task);

/*
 * @brief The fourth active object task.
 * @param task The task's argument (A task object).
 * @return An integer, representing the status of the function that the active object will execute:
 *          1 means to continue executing the function that the active object will execute.
 *          0 means to stop executing the function that the active object will execute.
 * @note The task checks if a given number is a prime number.
 * @note The task prints the result to the standard output.
*/
int  ActiveObjectTask4(void *task);

#endif // _TASKS_H
