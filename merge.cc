/*
 * merge.cc -- programming assignment #4
 *             together to the end <http://acmgnyr.org/year1998/prob_g.html>
 * Copyright (C) 2022  Jacob Koziej <jacobkoziej@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "merge.h"

#include <cstdlib>


void merge::delete_bitmap(void)
{
	for (std::size_t i = 0; i < ydim; i++)
		delete[] bitmap[i];

	delete[] bitmap;

	bitmap = nullptr;
}


int main(void)
{
	return EXIT_SUCCESS;
}
