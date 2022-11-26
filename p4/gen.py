#!/usr/bin/env python3
# gen.py -- generate test cases
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

import argparse


def main():
    parser = argparse.ArgumentParser(description='generate test cases')
    parser.add_argument(
        '-i',
        '--input',
        help='generated input file',
        metavar='IN',
        required=True,
        type=argparse.FileType('w'),
    )
    parser.add_argument(
        '-c',
        '--count',
        help='generation count',
        metavar='N',
        required=True,
        type=int,
    )
    parser.add_argument(
        '-l',
        '--length',
        default=1000,
        help='maximum string length',
        metavar='N',
        type=int,
    )
    parser.add_argument(
        '-o',
        '--output',
        help='generated output file',
        metavar='OUT',
        required=True,
        type=argparse.FileType('w'),
    )

    args = parser.parse_args()


if __name__ == '__main__':
    main()
