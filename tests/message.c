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
 * @file message.c
 * @author Egor Anikin <egor-anikin@inbox.ru>
 * @brief FreeRTOS message test
 */

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "environment.h"

#define ITER 100

static int var[ITER];
static int current = 0;

static xQueueHandle xQueue = NULL;


static void vTask1(void *params)
{
        int time;
  
        while (current < ITER) {
                time = clock();
                xQueueSendToBack(xQueue, &time, 0);
        }

        vTaskDelete(NULL);
}

static void vTask2(void *params)
{
        int time, curTime;
        portBASE_TYPE xStatus;

        while (current < ITER) {
                xStatus = xQueueReceive(xQueue, &time, 0);
                curTime = clock();

                if (xStatus == pdPASS) {
                        var[current] = curTime - time;
                        current++;

                        if (current == ITER) {
                                output("Full message test", var, ITER);
                        }
                }
        }

        vTaskDelete(NULL);
}

void app_main(void)
{
        xQueue = xQueueCreate(1, sizeof(int));

        if (xQueue != NULL) {
                xTaskCreate(vTask1, "Task 1", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, NULL);
                xTaskCreate(vTask2, "Task 2", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, NULL);
        }

        vTaskStartScheduler();
}
