/*
 * ht.cc -- hash table
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

#include "ht.h"

#include <cstdint>
#include <cstring>


bool ht::exists(const void *key, std::size_t siz) const
{
	// invalid key size
	if (!siz) return false;

	// empty hash table
	if (!ent_cnt) return false;

	std::uint64_t pos = hash(key, siz) % ent.size();

	std::size_t i = 0;
	do {
		// we've somehow traversed the entire hash table
		if (i > ent.size()) return false;

		const ht_ent_t &cur = ent[pos];

		if (!cur.key) return false;

		if (cur.siz != siz) continue;

		if (!std::memcmp(cur.key, key, siz)) return true;
	} while (pos = (pos + 1) % ent.size(), ++i, true);

	return false;
}
