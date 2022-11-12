/*
 * graph.h -- directed graph
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

#ifndef CU_ECE365_GRAPH_H
#define CU_ECE365_GRAPH_H


#include <climits>
#include <cstddef>
#include <iostream>
#include <string>
#include <vector>

#include "ht.h"


class graph {
	typedef struct node_s {
		struct edge_s {
			unsigned       cost;
			struct node_s *node;
		};

		std::string                id;
		int                        dist;
		std::vector<struct edge_s> edge;

		struct node_s *parent;
		struct node_s *child;

		node_s(void) {
			dist = INT_MAX;

			parent = nullptr;
			child  = nullptr;
		}
	} node_t;

	static inline const void  *stringkey(const std::string &key);
	static inline std::size_t  stringsiz(const std::string &key);

	std::vector<node_t*>  node;
	htt<std::string>     *idmap;

	node_t *start;

public:
	graph(void);
	~graph(void);

	void add_edge(std::string &src_id, std::string &dst_id, int cost);
	int  dijkstra(std::string &start_id);

	friend std::ostream& operator << (std::ostream &out, const graph &g);
};


#endif /* CU_ECE365_GRAPH_H */
