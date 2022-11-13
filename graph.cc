/*
 * graph.cc -- directed graph
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

#include "graph.h"

#include <cstddef>
#include <iostream>
#include <stack>
#include <string>

#include "ht.h"
#include "heap.h"


inline const void *graph::stringkey(const std::string &key)
{
	return key.data();
}

inline std::size_t graph::stringsiz(const std::string &key)
{
	return key.size();
}


graph::graph(void)
{
	idmap = new htt<std::string>(graph::stringkey, graph::stringsiz);

	start = nullptr;
}

graph::~graph(void)
{
	delete idmap;
}

void graph::add_edge(std::string &src_id, std::string &dst_id, int cost)
{
	node_t *src;
	node_t *dst;

	if (idmap->get(src_id, (void**) &src) < 0) {
		src = new node_t;

		src->id = src_id;
		node.push_back(src);
		idmap->insert(src_id, src);
	}

	if (idmap->get(dst_id, (void**) &dst) < 0) {
		dst = new node_t;

		dst->id = dst_id;
		node.push_back(dst);
		idmap->insert(dst_id, dst);
	}

	// convoluted way to push_back() since struct edge_s
	// is defined inside of node_t
	std::size_t pos = src->edge.size();
	src->edge.resize(pos + 1);
	src->edge[pos].cost = cost;
	src->edge[pos].node = dst;
}

int graph::dijkstra(std::string &start_id)
{
	if (idmap->get(start_id, (void**) &start) < 0) return -1;

	heap unknown(node.size());

	for (auto n : node) {
		n->dist   = INT_MAX;
		n->parent = nullptr;

		unknown.insert(n->id, n->dist, n);
	}

	start->dist = 0;
	unknown.setKey(start->id, start->dist);

	node_t *tmp;
	while (!unknown.deleteMin(nullptr, nullptr, (void**) &tmp)) {
		if (tmp->dist == INT_MAX) continue;  // no path

		for (auto e : tmp->edge) {
			int dist = tmp->dist + e.cost;

			if (dist < e.node->dist) {
				e.node->dist   = dist;
				e.node->parent = tmp;

				unknown.setKey(e.node->id, e.node->dist);
			}
		}
	}

	return 0;
}

std::ostream& operator << (std::ostream &out, const graph &g)
{
	for (auto n : g.node) {
		out << n->id << ": ";

		if (n->dist == INT_MAX) {
			out << "NO PATH\n";
			continue;
		}

		out << n->dist << " [";

		std::stack<std::string> path;
		graph::node_t *tmp = n;
		do {
			path.push(tmp->id);
			tmp = tmp->parent;
		} while (tmp);

		out << path.top();
		path.pop();

		while (!path.empty()) {
			out << ", " << path.top();
			path.pop();
		}

		out << "]\n";
	}

	return out;
}
