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
 * @file semaphore.c
 * @author Egor Anikin <egor-anikin@inbox.ru>
 * @brief FreeRTOS semaphore test
 */

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "environment.h"

#define ITER 1000
#define TASK 2

int current[2] = { 0, 0 };
int check[2][ITER * TASK];
double average[TASK];
bool flag = 0;

static SemaphoreHandle_t xMutex = NULL;


static void vTask(void *params) {
        int n = (int)params;
        int curTime, prevTime;

        prevTime = clock();
        for (int i = 0; i < ITER; i++) {
                xSemaphoreTake(xMutex, 0);
                check[0][current[0]]++;
                current[0]++;
                xSemaphoreGive(xMutex);
        }
        curTime = clock();

        average[n] = curTime - prevTime;

        prevTime = clock();
        for (int i = 0; i < ITER; i++) {
                check[1][current[1]]++;
                current[1]++;
        }
        curTime = clock();

        average[n] = (average[n] - curTime + prevTime) / ITER;

        if (n == 0) {
                while (flag == 0);

                for (int i = 0; i < ITER * TASK; i++) {
                        if (check[0][i] != 0) {
                                error("Semaphore fail"); 
                        }
                }

                double result = 0;
                for (int i = 0; i < TASK; i++) {
                        result += average[i];
                }

                single("Semaphore", result / TASK);
        } else {
                flag = 1;
        }

        vTaskDelete(NULL);
}

void app_main(void)
{
        for (int i = 0; i < ITER * TASK; i++) {
                check[0][i] = -1;
        }

        xMutex = xSemaphoreCreateRecursiveMutex();

        if (xMutex != NULL) {
                xTaskCreate(vTask, "Task 1", configMINIMAL_STACK_SIZE + 1000, (void *)0, tskIDLE_PRIORITY + 1, NULL);
                xTaskCreate(vTask, "Task 2", configMINIMAL_STACK_SIZE + 1000, (void *)1, tskIDLE_PRIORITY + 1, NULL);
        }
        vTaskStartScheduler();
}
