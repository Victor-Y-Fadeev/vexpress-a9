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
 * @file environment.c
 * @author Victor Y. Fadeev <victor.y.fadeev@gmail.com>
 * @brief Environment library
 */

#include "environment.h"
#include <basic_stdio.h>


void recursive_printf(double value, int precision)
{
        if (precision == 0) {
                return;
        }

        value *= 10;
        basic_printf("%d", (int)value);
        recursive_printf(value - (int)value, precision - 1);
}

void double_printf(double value)
{
        if (value < 0) {
                value *= -1;
        }

        basic_printf("%d.", (int)value);

        double fractional = value;
        for (int i = 0; i < PRECISION; i++) {
                fractional *= 10;
        }

        if ((int)fractional == 0) {
                recursive_printf(value - (int)value, PRECISION * 2);
        } else {
                recursive_printf(value - (int)value, PRECISION);
        }
}

void output(const char *str, int *var, int iter)
{
        var = &var[1];
        iter--;

        basic_printf("\r\n---%s---\r\n", str);
        basic_printf("Iterations: %d\r\n", iter);

        int average = 0;
        for (int i = 0; i < iter; i++) {
                average += var[i];
        }
        basic_printf("Average: ");
        double_printf(((double)average) / iter);
        basic_printf(" us\r\n");

        double variance = 0;
        for (int i = 0; i < iter; i++) {
                double temp = var[i] - ((double)average) / iter;
                variance += temp * temp;
        }
        basic_printf("Variance: ");
        double_printf(variance / iter);
        basic_printf("\r\n\r\n");

        for (int i = 0; i < iter; i++) {
                basic_printf("#%d switch - %d microsecond\r\n", i, var[i]);
        }
}

void single(const char *str, const double average)
{
        basic_printf("\r\n---%s---\r\n", str);
        basic_printf("Average: ");
        double_printf(average * 1000);
        basic_printf(" ns\r\n\r\n");
}

void error(const char *str)
{
        basic_printf("Error: %s\r\n", str);
}
