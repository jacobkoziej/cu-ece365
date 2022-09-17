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


#include <cstdint>
#include <cstdlib>
#include <vector>


class ht {
	typedef struct ht_ent_s {
		void        *key = nullptr;
		std::size_t  siz;
		void        *val;
		bool         del = false;
	} ht_ent_t;

	std::vector<ht_ent_t> ent;
	std::size_t           ent_cnt;

	static std::uint64_t fnv1a_hash(const void *key, std::size_t siz);

	void rehash(void);

public:
	ht(std::size_t defsiz = 64);
	~ht(void);

	bool exists(const void *key, std::size_t siz) const;
	int  get(const void *key, std::size_t siz, void **val) const;
	int  insert(const void *key, std::size_t siz, void *val = nullptr);
	int  rm(const void *key, std::size_t siz);
	int  set(const void *key, std::size_t siz, void *val);
};

template <typename T>
class htt {
	ht p_ht;

	const void *(*key)(const T &key) = nullptr;
	std::size_t (*siz)(const T &key) = nullptr;

public:
	htt(const void *(*key)(const T &key), std::size_t (*siz)(const T &key));

	inline bool exists(const T &key) const;
	inline int  get(const T &key, void **val) const;
	inline int  insert(const T &key, void *val = nullptr);
	inline int  rm(const T &key);
	inline int  set(const T &key, void *val);
};

template <typename T>
htt<T>::htt(const void *(*key)(const T &key), std::size_t (*siz)(const T &key))
{
	this->key = key;
	this->siz = siz;
}

template <typename T>
inline bool htt<T>::exists(const T &key) const
{
	return p_ht.exists(this->key(key), this->siz(key));
}

template <typename T>
inline int htt<T>::get(const T &key, void **val) const
{
	return p_ht.get(this->key(key), this->siz(key), val);
}

template <typename T>
inline int htt<T>::insert(const T &key, void *val)
{
	return p_ht.insert(this->key(key), this->siz(key), val);
}

template <typename T>
inline int htt<T>::rm(const T &key)
{
	return p_ht.rm(this->key(key), this->siz(key));
}

template <typename T>
inline int htt<T>::set(const T &key, void *val)
{
	return p_ht.set(this->key(key), this->siz(key), val);
}


#endif /* CU_ECE365_HT_H */
