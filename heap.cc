/*
 * heap.cc -- binary heap
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

#include "heap.h"

#include <cstddef>
#include <string>


inline const void *heap::stringkey(const std::string &key)
{
	return key.data();
}

inline std::size_t heap::stringsiz(const std::string &key)
{
	return key.size();
}

void heap::percolate_up(std::size_t pos)
{
	auto tmp = nodes[pos];
	auto prv = pos;

	// when called, we already know the parent is greater
	pos >>= 1;

	while (true) {
		nodes[prv] = nodes[pos];
		idmap->set(nodes[prv].id, &nodes[prv]);

		if (pos <= 1) break;

		if (tmp.key >= nodes[pos >> 1].key) break;

		prv = pos;
		pos >>= 1;
	}

	nodes[pos] = tmp;
	idmap->set(nodes[pos].id, &nodes[pos]);
}


heap::heap(std::size_t siz)
{
	idmap = new htt<std::string>(heap::stringkey, heap::stringsiz, siz * 2);
	nodes.resize(siz + 1);

	this->siz = siz;
	use       = 0;
}

heap::~heap(void)
{
	delete idmap;
}

int heap::insert(const std::string &id, int key, void *val)
{
	// heap filled to capacity
	if (use + 1 > siz) return 1;

	void *node = nullptr;

	// given id already exists
	if (!idmap->get(id, &node)) return 2;

	std::size_t pos = ++use;

	nodes[pos].id  = id;
	nodes[pos].key = key;
	nodes[pos].val = val;
	idmap->insert(id, &nodes[pos]);

	if (pos == 1) return 0;

	if (nodes[pos << 1].key > nodes[pos].key) percolate_up(pos);

	return 0;
}

int heap::setKey(const std::string &id, int key)
{
	(void) id;
	(void) key;

	return 0;
}

int heap::deleteMin(const std::string *id, int *key, void **val)
{
	(void) id;
	(void) key;
	(void) val;

	return 0;
}

int heap::remove(const std::string  &id, int *key, void **val)
{
	(void) id;
	(void) key;
	(void) val;

	return 0;
}
