/*
 * dijkstra.cc -- programming assignment #3
 *                dijkstra's algorithm
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

#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>

#include "graph.h"


using namespace std;


void parse_graph(const string &path, graph &input)
{
	ifstream file;

	file.open(path);
	if (!file) {
		cerr << path << ": could not be opened\n";
		exit(EXIT_FAILURE);
	}

	string tmp;
	while (getline(file, tmp)) {
		stringstream  ss(tmp);
		string        token;
		queue<string> tokens;

		while (getline(ss, token, ' '))
			tokens.push(token);

		string v = tokens.front();
		tokens.pop();

		string w = tokens.front();
		tokens.pop();
		int cost = stoi(tokens.front());

		input.add_edge(v, w, cost);
	}

	file.close();
}


int main(void)
{
	graph dijkstra;

	string path;

	cout << "path to graph file: ";
	cin  >> path;

	parse_graph(path, dijkstra);

	bool    bad;
	clock_t t0;
	clock_t t1;

	do {
		string start;
		cout << "starting vertex: ";
		cin >> start;

		t0 = clock();
		bad = dijkstra.dijkstra(start);
		t1 = clock();
	} while (bad);

	float dt = t1 - t0;
	dt /= CLOCKS_PER_SEC;
	cout << "applied dijkstra's algorithm in " << dt << "s\n";

	cout << "path to output file: ";
	cin  >> path;

	ofstream file(path);
	if (!file) {
		cerr << ": cannot be opened\n";
		return EXIT_FAILURE;
	}

	file << dijkstra;
	file.close();

	return EXIT_SUCCESS;
}
