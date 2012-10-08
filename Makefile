#    Makefile - build a simple memtest
#    Copyright (C) 2012 Christoffer Dall <cdall@cs.columbia.edu>
#
#    This program is free software: you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#
#    This program is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License
#    along with this program.  If not, see <http://www.gnu.org/licenses/>.# 

GCC=$(CROSS_COMPILE)gcc
CC=$(CROSS_COMPILE)gcc
AS=$(CROSS_COMPILE)as
LD=$(CROSS_COMPILE)ld


all: mtest bigass

bigass_loop.S: generate.py
	./generate.py > bigass_loop.S

bigass_loop.o: bigass_loop.S
	$(AS) -o $@ $<

bigass.o: bigass.c
	$(CC) -g -c -marm -o $@ $<

BIGASS_OBJS = bigass_loop.o bigass.o

bigass: $(BIGASS_OBJS)
	$(GCC) -o $@ $^

MTEST_OBJS	= mtest.o
mtest: $(MTEST_OBJS)
	$(GCC) -o $@ $^

%.o: %.c
	$(CC) -O3 -g -c -o $@ $<

clean distclean:
	rm -f mtest mtest.o bigass.o bigass bigass_loop.o bigass_loop.S
