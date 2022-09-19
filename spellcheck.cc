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
#include <regex>
#include <string>

#include "ht.h"


#define MAX_WORD_LEN 20


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
	float   dt;

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

	dt  = t1 - t0;
	dt /= CLOCKS_PER_SEC;
	cout << "loaded dictionary in " << dt << "s\n";
	ifile.close();

	cout << "Path to input file: ";
	cin >> tmp;

	ifile.open(tmp);
	if (!ifile) {
		cerr << argv[0] << ": '" << tmp << "' not found!\n";
		return EXIT_FAILURE;
	}

	cout << "Path to output file: ";
	cin >> tmp;

	ofile.open(tmp);
	if (!ofile) {
		cerr << argv[0] << ": '" << tmp << "' not found!\n";
		return EXIT_FAILURE;
	}

	unsigned i = 0;
	string line;
	regex word_re("[A-Za-z0-9\\-']+");

	t0 = clock();
	while (++i, getline(ifile, line)) {
		transform(line.begin(), line.end(), line.begin(), ::tolower);

		sregex_token_iterator end;

		for (
			sregex_token_iterator token(
				line.begin(),
				line.end(),
				word_re
			);
			token != end;
			token++
		) {
			tmp = *token;

			if (tmp.length() > MAX_WORD_LEN) {
				ofile
					<< "Long word at line "
					<< i
					<< ", starts: "
					<< tmp.substr(0, MAX_WORD_LEN)
					<< '\n';
				continue;
			}

			if (!dict.exists(tmp))
				ofile
					<< "Unknown word at line "
					<< i
					<< ": "
					<< tmp
					<< '\n';
		}
	}
	t1 = clock();

	dt  = t1 - t0;
	dt /= CLOCKS_PER_SEC;
	cout << "spell checked document in " << dt << "s\n";
	ifile.close();

	return EXIT_SUCCESS;
}
