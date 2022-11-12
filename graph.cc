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
#include <string>

#include "ht.h"


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
