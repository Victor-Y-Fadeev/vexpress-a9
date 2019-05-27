/**
 * Copyright (c) 2019 OS Research Group.
 * All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 * @file process.c
 * @author Egor Anikin <egor-anikin@inbox.ru>
 * @brief FreeRTOS process test
 */

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "environment.h"

#define ITER 1000000
#define TASK 2

int curent = 0;
int curent2 = 0;
int chek[ITER*TASK];
int chek2[ITER*TASK];
double ave[TASK];

static SemaphoreHandle_t xMutex = NULL;


static void task(void *params) {
    int n = (int)params; 

    int cur_time = 0;
	int prev_time = 0;

	prev_time = clock();
	for(int i = 0; i < ITER; i++)
	{
	        xSemaphoreTake(xMutex, 0);
                chek[curent] += 1;
                curent++;
                xSemaphoreGive(xMutex);
	}
	cur_time = clock();

	ave[n] = cur_time - prev_time;

	prev_time = clock();
	for(int i = 0; i < ITER; i++)
	{
		chek2[curent2] += 1;
                curent2++;
	}
	cur_time = clock();

	ave[n] = (ave[n] - cur_time + prev_time)/ITER; 
        if(n == 0)
        single("Semaphore",ave[n]);
        vTaskDelete(NULL);
}

void app_main(void)
{ 
        xMutex = xSemaphoreCreateRecursiveMutex();

        xTaskCreate(task, "Task 1", configMINIMAL_STACK_SIZE, (void *)0, tskIDLE_PRIORITY + 1, NULL);
        xTaskCreate(task, "Task 2", configMINIMAL_STACK_SIZE, (void *)1, tskIDLE_PRIORITY + 1, NULL);
        vTaskStartScheduler();
}
