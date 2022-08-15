# these two lines specify make "variables"
# makes it easy to change to a different compiler and
# change the flags.  Notice the variables are "expanded"
# with a $ sign.
CC=gcc 
FLAGS=-Wall

ll_tst: llist.o ll_tst.c
	$(CC) $(FLAGS) ll_tst.c llist.o -o ll_tst

llist.o: list.h llist.c
	$(CC) $(FLAGS) -c llist.c

#clean:
#	rm -f *.o ll_tst

all: llist.o tests_pt2 tests_pt1 


tests_pt2: llist.o tests_pt2.c
	gcc -std=c99 tests_pt2.c llist.o -o tests_pt2

tests_pt1: llist.o tests_pt1.c
	gcc -std=c99 tests_pt1.c llist.o -o tests_pt1


llist.o: list.h llist.c
	gcc -std=c99 -c llist.c

clean:
	rm tests_pt1 tests_pt2 llist.o