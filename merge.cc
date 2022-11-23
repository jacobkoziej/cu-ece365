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

#include <algorithm>
#include <cctype>
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

	// merge
	for (size_t i = 1; i <= b.size(); i++)
		for (size_t j = 1; j <= a.size(); j++) {
			size_t pos;

			// vertical attempt
			pos = matrix[i - 1][j] + 1;
			if (pos) {
				if (c[pos] == a[j - 1]) {
					matrix[i][j] = pos;
					continue;
				}
				if ((j - 1 < b.size()) && (c[pos] == b[i - 1])) {
					matrix[i][j] = pos;
					continue;
				}
			}

			// horizontal attempt
			pos = matrix[i][j - 1] + 1;
			if (pos) {
				if (c[pos] == b[i - 1]) {
					matrix[i][j] = pos;
					continue;
				}
				if ((i - 1 < a.size()) && (c[pos] == a[j - 1])) {
					matrix[i][j] = pos;
					continue;
				}
			}

			matrix[i][j] = SIZE_MAX;
		}

	size_t apos = a.size();
	size_t bpos = b.size();

	if (matrix[bpos][apos] == SIZE_MAX)
		return "*** NOT A MERGE ***";

	string out;

	// initial output generation
	while (apos && bpos) {
		if (matrix[bpos][apos - 1] == SIZE_MAX) {
			out.push_back(b[--bpos]);
			continue;
		}
		if (matrix[bpos - 1][apos] == SIZE_MAX) {
			out.push_back(toupper(a[--apos]));
			continue;
		}
	}

	// finish up
	while (apos) out.push_back(toupper(a[--apos]));
	while (bpos) out.push_back(b[--bpos]);

	// invert output
	reverse(out.begin(), out.end());

	return out;
}


int main(void)
{
	return EXIT_SUCCESS;
}
