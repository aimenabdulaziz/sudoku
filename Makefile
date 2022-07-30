# Makefile for Sudoku
#
# Koding Kegs, Spring 2022

# uncomment to view unittesting logs
CREATE_TEST = -DCREATETEST
SOLVE_TEST = -DSOLVETEST

CC = gcc
CFLAGS = -Wall -pedantic -std=c11 -ggdb 
MAKE = make
TESTPROG = testing.sh
VGFLAGS = --leak-check=full --show-leak-kinds=all

# sudoku
PROG = sudoku
OBJS = sudoku.o create.o solve.o

# create
PROG1 = create
OBJS1 = create.c solve.c 

# solve
PROG2 = solve
OBJS2 = solve.c create.c

# fuzzssudoku
PROG3 = fuzzSudoku
OBJS3 = fuzzSudoku.o create.o solve.o

.PHONY: all fuzzSudoku test valgrind clean 

####### default ####### 
all: $(PROG) $(PROG1) $(PROG2) $(PROG3)

# Dependencies: object files depend on header files
solve.o: solve.h
create.o: create.h

####### sudoku ####### 
$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

###### create #######
$(PROG1): $(OBJS1)
	$(CC) $(CFLAGS) $(CREATE_TEST) $^ -o $@

###### solve #######
$(PROG2): $(OBJS2)
	$(CC) $(CFLAGS) $(SOLVE_TEST) $^ -o $@

####### fuzzSudoku ####### 
$(PROG3): $(OBJS3)
	$(CC) $(CFLAGS) $^ -o $@
	
####### test ####### 
test: $(TESTPROG) 
	chmod a+x $(TESTPROG)
	bash -v ./$(TESTPROG)

####### valgrind ####### 	
valgrind: $(PROG) $(PROG3)
	valgrind $(VGFLAGS) ./$(PROG) solve < tests/test2

####### clean ####### 
clean:
	rm -f *~ *.o
	rm -rf *.dSYM # MacOS debugger info
	rm -f $(PROG)
	rm -f $(PROG1)
	rm -f $(PROG2)
	rm -f $(PROG3)
