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
import random
import string


def gen(k: int) -> tuple[str, str, str]:
    a = ''.join(random.choices(string.ascii_lowercase, k=k))
    b = ''.join(random.choices(string.ascii_lowercase, k=k))

    aa = a
    bb = b
    cc = ''

    while len(aa) and len(bb):
        if random.choice([True, False]):
            cc += aa[:1]
            aa  = aa[1:]
        else:
            cc += bb[:1]
            bb  = bb[1:]

    while len(aa):
        cc += aa[:1]
        aa  = aa[1:]

    while len(bb):
        cc += bb[:1]
        bb  = bb[1:]


    aa = a
    bb = b
    c  = ''
    while len(cc):
        if cc[:1] == aa[:1]:
            c += aa[:1].upper()
            aa = aa[1:]
        else:
            c += bb[:1]
            bb = bb[1:]

        cc = cc[1:]

    return (a, b, c)


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

    while args.count:
        a, b, c = gen(args.length)

        args.input.write(a + '\n')
        args.input.write(b + '\n')
        args.input.write(c.lower() + '\n')

        args.output.write(c + '\n')

        args.count -= 1


if __name__ == '__main__':
    main()
