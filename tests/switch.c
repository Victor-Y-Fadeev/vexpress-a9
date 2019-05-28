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
 * @file switch.c
 * @author Egor Anikin <egor-anikin@inbox.ru>
 * @brief FreeRTOS switch test
 */

#include "FreeRTOS.h"
#include "task.h"
#include "environment.h"

#define ITER 10

int curTime, prevTime;


static void vTask(void *params) {
        vTaskDelete(NULL);
}

static void vTaskOut(void *params) {
        curTime = clock();

        double average = curTime - prevTime;
        char buf[16];

        prevTime = clock();
        for (int i = 0; i < ITER; i++) {
                basic_sprintf(buf, "Task %d", i);
        }
        curTime = clock();

        average = (average - curTime + prevTime) / ITER;
        single("Switching test", average);

        vTaskDelete(NULL);
}

void app_main(void)
{
        char buf[16];
        xTaskCreate(vTaskOut, "Task Out", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, NULL);

        prevTime = clock();
        for (int i = 0; i < ITER; i++) {
                basic_sprintf(buf, "Task %d", i);
                xTaskCreate(vTask, buf, configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 2, NULL);
        }

        vTaskStartScheduler();
}
