
# simple makefile for HW1
#
# Try the following:
#
#   from the shell (in this directory) just type "make demo"
#
#   You will see that the compilation steps that you have been
#   doing up to now "manually" have been automated.
#
#   (the demo program has been given to you).
#
# As you develop your programs (median3.c and so on), you will
# be able to simply type "make <target>" where <target> is one of 
# the five program (executable) names.
#
# For example, when you have created median3.c and want to compile it,
# you simply type "make median3"

CC=gcc
CFLAGS=-std=c99

all: median3 stairs num_ones histogram 


demo: demo.c 
	$(CC) $(CFLAGS) -o $@ $@.c 


median3: median3.c 
	$(CC) $(CFLAGS) -o $@ $@.c 

stairs: stairs.c 
	$(CC) $(CFLAGS) -o $@ $@.c 

num_ones: num_ones.c 
	$(CC) $(CFLAGS) -o $@ $@.c 

histogram: histogram.c 
	$(CC) $(CFLAGS) -o $@ $@.c 

search: search.c 
	$(CC) $(CFLAGS) -o $@ $@.c 

clean:
	rm -f *.o demo median3 stairs num_ones histogram search
