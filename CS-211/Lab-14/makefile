# these two lines specify make "variables"
# makes it easy to change to a different compiler and
# change the flags.  Notice the variables are "expanded"
# with a $ sign.
CC=gcc 
FLAGS=-Wall

deq_tst: deq.o deq_tst.c
	$(CC) $(FLAGS) deq_tst.c deq.o -o deq_tst

deq.o: deq.h deq.c
	$(CC) $(FLAGS) -c deq.c

clean:
	rm -f *.o deq_tst

