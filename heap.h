/*
 * heap.h -- binary heap
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

#ifndef CU_ECE365_HEAP_H
#define CU_ECE365_HEAP_H


#include <cstddef>
#include <string>
#include <vector>

#include "ht.h"


class heap {
	typedef struct node_s {
		std::string  id;
		int          key;
		void        *val;
	} node_t;

	static inline const void  *stringkey(const std::string &key);
	static inline std::size_t  stringsiz(const std::string &key);

	void percolate_down(std::size_t pos);
	void percolate_up(std::size_t pos);

	std::size_t          siz;
	std::size_t          use;
	htt<std::string>    *idmap;
	std::vector<node_t>  nodes;

public:
	heap(std::size_t siz = 1);
	~heap(void);

	int insert(const std::string &id, int key, void *val = nullptr);
	int setKey(const std::string &id, int key);
	int deleteMin(
		const std::string  *id  = nullptr,
		int                *key = nullptr,
		void              **val = nullptr
	);
	int remove(
		const std::string  &id,
		int                *key = nullptr,
		void              **val = nullptr
	);
};


#endif /* CU_ECE365_HEAP_H */
