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

#include <cstddef>
#include <cstdlib>
#include <string>


#define MAX_STRLEN 1000


using namespace std;


string merge(string a, string b, string c)
{
	static size_t matrix[MAX_STRLEN + 1][MAX_STRLEN + 1];

	// can we even have a vaild merge?
	if (a.size() + b.size() != c.size()) return "*** NOT A MERGE ***";

	// initialize matrix
	matrix[0][0] = SIZE_MAX;
	for (size_t i = 1; i <= a.size(); i++)
		matrix[0][i] = SIZE_MAX;
	for (size_t i = 1; i <= b.size(); i++)
		matrix[i][0] = SIZE_MAX;

	// initial parse
	for (size_t i = 0; i < a.size(); i++) {
		if (a[i] != c[i]) break;
		matrix[0][i + 1] = matrix[0][i] + 1;
	}
	for (size_t i = 0; i < b.size(); i++) {
		if (b[i] != c[i]) break;
		matrix[i + 1][0] = matrix[i][0] + 1;
	}

	return "*** NOT A MERGE ***";
}


int main(void)
{
	return EXIT_SUCCESS;
}
