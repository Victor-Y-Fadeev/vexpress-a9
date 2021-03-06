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
 * @file environment.h
 * @author Victor Y. Fadeev <victor.y.fadeev@gmail.com>
 * @brief Environment library
 */

#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#define clock() (xTaskGetTickCount() * portTICK_PERIOD_MS)

#define PRECISION 2


void output(const char *str, int *var, int iter);
void single(const char *str, const double average);
void error(const char *str);

#endif
