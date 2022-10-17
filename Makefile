# Makefile
# Copyright (C) 2022  Jacob Koziej <jacobkoziej@gmail.com>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

SRC := $(wildcard *.cc)
DEP := $(SRC:.cc=.d)

ARFLAGS  := crs
CXXFLAGS := -Wall -Wextra -Wpedantic -g -std=c++11


.PHONY: all
all: spellcheck useheap


-include $(DEP)


.PHONY: clean
clean:
	@rm -rvf *.a *.d *.o spellcheck useheap


spellcheck: spellcheck.o ht.a
	$(CXX) $(CXXFLAGS) -o $@ $^


useheap: useheap.o heap.a
	$(CXX) $(CXXFLAGS) -o $@ $^


heap.a: heap.o ht.o
	$(AR) $(ARFLAGS) $@ $?


ht.a: ht.o
	$(AR) $(ARFLAGS) $@ $?


%.o: %.cc
	$(CXX) $(CXXFLAGS) -MM $< -MF $*.d
	$(CXX) $(CXXFLAGS) -c $<
