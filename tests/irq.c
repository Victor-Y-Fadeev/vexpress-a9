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
 * @file irq.c
 * @author Egor Anikin <egor-anikin@inbox.ru>
 * @brief FreeRTOS irq test
 */

#include "FreeRTOS.h"
#include "task.h"
#include "environment.h"

#define ITER 1000000


static void vTask(void *params)
{
        int curTime, prevTime;
        double average;

        prevTime = clock();
        for (int i = 0; i < ITER; i++) {
                portYIELD_FROM_ISR(pdFALSE);
        }
        curTime = clock();

        average = curTime - prevTime;

        prevTime = clock();
        for (int i = 0; i < ITER; i++);
        curTime = clock();

        average = (average - curTime + prevTime) / ITER;
        single("IRQ", average);
}

void app_main(void)
{ 
        xTaskCreate(vTask, "Task", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, NULL);
        vTaskStartScheduler();
}
