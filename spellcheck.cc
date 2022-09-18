/*
 * spellcheck.c -- programming assignment #1
 *                 primitive spell checker
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
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>

#include "ht.h"


using namespace std;


inline const void *stringkey(const string &key)
{
	(void) key;

	return key.data();
}

inline size_t stringsiz(const string &key)
{
	return key.size();
}


int main(int argc, char **argv)
{
	(void) argc;

	htt<string> dict(stringkey, stringsiz);

	ifstream ifile;
	ofstream ofile;
	string   tmp;

	clock_t t0;
	clock_t t1;

	cout << "Path to dictionary: ";
	cin >> tmp;

	ifile.open(tmp);
	if (!ifile) {
		cerr << argv[0] << ": '" << tmp << "' not found!\n";
		return EXIT_FAILURE;
	}

	t0 = clock();
	while (getline(ifile, tmp)) {
		transform(tmp.begin(), tmp.end(), tmp.begin(), ::tolower);
		dict.insert(tmp);
	}
	t1 = clock();
	cout << "loaded dictionary in " << (t1 - t0) / CLOCKS_PER_SEC << "s\n";

	return EXIT_SUCCESS;
}
