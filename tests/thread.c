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
 * @file thread.c
 * @author Egor Anikin <egor-anikin@inbox.ru>
 * @brief FreeRTOS thread test
 */

#include "FreeRTOS.h"
#include "task.h"
#include "environment.h"

#define ITER 100

int period[3]= { 0, 0, 0 };

int current[3] = { 0, 0, 0 };
int var[ITER][3];
int flag = 0;


static void vTask(void *params) {
        int n = (int)params;
        int first, second, curTime;

        while (current[n] < ITER) {
                first = period[(n + 1) % 3];
                second = period[(n + 2) % 3];
                curTime = clock();

                if (first != 0 && second != 0) {
                        if (first < second) {
                                var[current[n]][n] = curTime - first;
                        } else {
                                var[current[n]][n] = curTime - second;
                        }
                        current[n]++;
                }
                period[n] = clock();
        }

        if (n == 0) {
                while (flag < 2);
                int varFull[ITER * 3];

                for (int i = 0; i < ITER; i++) {
                        for (int j = 0; j < 3; j++) {
                                varFull[i * 3 + j] = var[i][j];
                        }
                }
        
                output("Thread", varFull, ITER * 3);
        } else {
                flag++;
        }

        vTaskDelete(NULL);
}

void app_main(void)
{ 
        xTaskCreate(vTask, "Task 1", configMINIMAL_STACK_SIZE + 1000, (void *)0, tskIDLE_PRIORITY + 1, NULL);
        xTaskCreate(vTask, "Task 2", configMINIMAL_STACK_SIZE + 1000, (void *)1, tskIDLE_PRIORITY + 1, NULL);
        xTaskCreate(vTask, "Task 3", configMINIMAL_STACK_SIZE + 1000, (void *)2, tskIDLE_PRIORITY + 1, NULL);
        vTaskStartScheduler();
}
