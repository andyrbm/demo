CC = gcc
CFLAGS = -O3 -g -lm

all : make_member make_sales

clean :
	rm -f make_member make_sales

make_member : make_member.c rand_tools.h demo_limits.h
	$(CC) $(CFLAGS) -o $@ $<

make_sales : make_sales.c rand_tools.h demo_limits.h
	$(CC) $(CFLAGS) -o $@ $<


.PHONY : all

