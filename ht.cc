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


#define FNV_OFFSET_BASIS 0xcbf29ce484222325UL
#define FNV_PRIME        0x100000001b3UL


std::uint64_t ht::fnv1a_hash(const void *key, std::size_t siz)
{
	std::uint64_t hash = FNV_OFFSET_BASIS;

	const unsigned char *byte = static_cast<const unsigned char*>(key);
	for (size_t i = 0; i < siz; i++, byte++) {
		hash ^= *byte;
		hash *= FNV_PRIME;
	}

	return hash;
}

void ht::rehash(void)
{
	std::size_t newsiz = ent.size() * 2;

	std::vector<ht_ent_t> newent(newsiz);

	auto cnt = ent_cnt;
	for (auto &prv : ent) {
		if (!cnt) break;

		if (!prv.key) continue;
		if (!prv.del) {
			operator delete(prv.key);
			continue;
		}

		std::uint64_t pos = fnv1a_hash(prv.key, prv.siz) % newent.size();

		ht_ent_t *cur;
		while (cur = &newent[pos], !cur->key) {
			*cur = prv;
			pos = (pos + 1) % newent.size();
		}

		--cnt;
	}

	ent.swap(newent);
}


ht::ht(std::size_t defsiz)
{
	// determine highest power of two
	unsigned shift = 0;
	while (defsiz >>= 1, defsiz) ++shift;
	defsiz = ((std::size_t) 1) << shift;

	ent.resize(defsiz);
	ent_cnt = 0;
}

ht::~ht(void)
{
	auto cnt = ent_cnt;

	for (auto cur : ent) {
		if (!cnt) return;

		if (cur.key) operator delete(cur.key);
	}
}

bool ht::exists(const void *key, std::size_t siz) const
{
	// invalid key size
	if (!siz) return false;

	// empty hash table
	if (!ent_cnt) return false;

	std::uint64_t pos = fnv1a_hash(key, siz) % ent.size();

	std::size_t i = 0;
	do {
		// we've somehow traversed the entire hash table
		if (i > ent.size()) return false;

		const auto &cur = ent[pos];

		if (!cur.key && !cur.del) return false;

		if (cur.siz != siz) continue;

		if (!std::memcmp(cur.key, key, siz)) return true;
	} while (pos = (pos + 1) % ent.size(), ++i, true);

	return false;
}

int ht::get(const void *key, std::size_t siz, void **val) const
{
	// invalid key size
	if (!siz) return -1;

	// empty hash table
	if (!ent_cnt) return -1;

	std::uint64_t pos = fnv1a_hash(key, siz) % ent.size();

	std::size_t i = 0;
	do {
		// we've somehow traversed the entire hash table
		if (i > ent.size()) return -1;

		const auto &cur = ent[pos];

		if (!cur.key && !cur.del) return -1;

		if (cur.siz != siz) continue;

		if (!std::memcmp(cur.key, key, siz)) {
			*val = cur.val;
			return 0;
		}
	} while (pos = (pos + 1) % ent.size(), ++i, true);

	return -1;
}

int ht::insert(const void *key, std::size_t siz, void *val)
{
	// invalid key size
	if (!siz) return -1;

	if (ent_cnt + 1 >= ent.size() / 2) rehash();

	std::uint64_t pos = fnv1a_hash(key, siz) % ent.size();

	std::size_t i = 0;
	do {
		// we've somehow traversed the entire hash table
		if (i > ent.size()) return -1;

		auto &cur = ent[pos];

		if (cur.key) {
			if (!cur.del) {
				// duplicate entry
				if (cur.siz == siz)
					if (!std::memcmp(cur.key, key, siz))
						return -1;

				continue;
			}

			// lazily deleted entry
			operator delete(cur.key);
		}

		cur.key = operator new(siz);
		cur.siz = siz;
		cur.val = val;
		cur.del = false;

		std::memcpy(cur.key, key, siz);
		++ent_cnt;

		return 0;
	} while (pos = (pos + 1) % ent.size(), ++i, true);

	return -1;
}

int ht::rm(const void *key, std::size_t siz)
{
	// invalid key size
	if (!siz) return -1;

	// empty hash table
	if (!ent_cnt) return -1;

	std::uint64_t pos = fnv1a_hash(key, siz) % ent.size();

	std::size_t i = 0;
	do {
		// we've somehow traversed the entire hash table
		if (i > ent.size()) return -1;

		ht_ent_t &cur = ent[pos];

		if (!cur.key && !cur.del) return -1;

		if (cur.siz != siz) continue;

		if (!std::memcmp(cur.key, key, siz)) {
			cur.del = true;
			--ent_cnt;

			return 0;
		}
	} while (pos = (pos + 1) % ent.size(), ++i, true);

	return -1;
}

int ht::set(const void *key, std::size_t siz, void *val)
{
	// invalid key size
	if (!siz) return -1;

	// empty hash table
	if (!ent_cnt) return -1;

	std::uint64_t pos = fnv1a_hash(key, siz) % ent.size();

	std::size_t i = 0;
	do {
		// we've somehow traversed the entire hash table
		if (i > ent.size()) return -1;

		auto &cur = ent[pos];

		if (!cur.key && !cur.del) return -1;

		if (cur.siz != siz) continue;

		if (!std::memcmp(cur.key, key, siz)) {
			cur.val = val;
			return 0;
		}
	} while (pos = (pos + 1) % ent.size(), ++i, true);

	return -1;
}
