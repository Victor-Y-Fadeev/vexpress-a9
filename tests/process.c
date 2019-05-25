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
#include "environment.h"

#define ITER 30

int t[3] = { 0, 0, 0 };

int curent[3] = { 0, 0, 0 };
int var[3][ITER];
int var_full[ITER*3];


static void task(void *params)
{
        int n = (int)params;
        int t1, t2, cur_time;

        while (curent[n] < ITER) {
                t1 = t[(n + 1) % 3];
                t2 = t[(n + 2) % 3];
                cur_time = clock();

                if ((t1 != 0) && (t2 !=0)) {
                        if (t1 > t2) {
                                var[n][curent[n]] = cur_time - t2;
                        } else {
                                var[n][curent[n]] = cur_time - t1;
                        }
                        curent[n]++;
                }
                t[n] = clock();
        }

        if (n == 0) {
                for (int i = 0; i < ITER; i++) {
                        for (int j = 0; j < 3; j++) {
                                var_full[i * 3 + j] = var[j][i];
                        }
                }
        
                output("Processes switching test", var_full, ITER * 3);
        }

        vTaskDelete(NULL);
}

void app_main(void)
{ 
        xTaskCreate(task, "Task 1", configMINIMAL_STACK_SIZE, (void *)0, tskIDLE_PRIORITY + 1, NULL);
        xTaskCreate(task, "Task 2", configMINIMAL_STACK_SIZE, (void *)1, tskIDLE_PRIORITY + 1, NULL);
        xTaskCreate(task, "Task 3", configMINIMAL_STACK_SIZE, (void *)2, tskIDLE_PRIORITY + 1, NULL);
        vTaskStartScheduler();
}
