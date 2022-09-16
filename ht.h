/*
 * ht.h -- hash table
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

#ifndef CU_ECE365_HT_H
#define CU_ECE365_HT_H


#include <cstdlib>


class ht {
	typedef struct ht_ent_s {
		void        *key;
		std::size_t  siz;
		void        *val;
		bool         set = false;
		bool         del = false;
	} ht_ent_t;

public:
	int  clear(const void *key, std::size_t siz);
	bool exists(const void *key, std::size_t siz);
	int  get(const void *key, std::size_t siz, void **val);
	int  insert(const void *key, std::size_t siz, void *val = nullptr);
	int  rm(const void *key, std::size_t siz);
	int  set(const void *key, std::size_t siz, void *val);
};


#endif /* CU_ECE365_HT_H */
