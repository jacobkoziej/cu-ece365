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
#include <utility>


void merge::delete_bitmap(void)
{
	for (std::size_t i = 0; i < ydim; i++)
		delete[] bitmap[i];

	delete[] bitmap;

	bitmap = nullptr;
}


merge::merge(void)
{
	bitmap = nullptr;
}

merge::merge(std::string &a, std::string &b)
{
	bitmap = nullptr;

	set_strings(a, b);
}

merge::~merge(void)
{
	if (!bitmap) return;

	delete_bitmap();
}

void merge::set_strings(std::string &a, std::string &b)
{
	if (bitmap) delete_bitmap();

	this->a = a;
	this->b = b;

	// we want to use make sure string `a` is the larger of the two
	// since it will increase the efficiency of the bit-packing
	if (this->a.size() < this->b.size()) std::swap(this->a, this->b);

	xdim = this->a.size() + 1;
	ydim = this->b.size() + 1;

	bitmap = new bitmap_t*[ydim];

	std::size_t xdim_siz = xdim / (sizeof(bitmap_t) << 3);
	if (xdim & 0x07) ++xdim_siz;


	for (std::size_t i = 0; i < ydim; i++)
		bitmap[i] = new bitmap_t[xdim_siz];
}


int main(void)
{
	return EXIT_SUCCESS;
}
