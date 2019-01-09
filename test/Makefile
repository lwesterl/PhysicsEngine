# Makefile for the test directory

CC=g++ -std=c++17
CFLAGS=-Wall -pedantic -Wextra -g
UTILS=../utils/
TESTS=$(wildcard *_test.cpp)
EXE=$(TESTS:.cpp=.exe)
SRC=$(wildcard $(UTILS)*.cpp)
OBJECTS=$(SRC:.cpp=.o)
OBJ=$(notdir $(OBJECTS))


all: $(OBJECTS) $(EXE)

#compile objects
%.o:	%.cpp
	$(CC) $(CFLAGS) -c $< -o $(notdir $@)

#compile all tests
%.exe:	%.cpp
	$(CC) $(CFLAGS) ${OBJ} $< -o $@

clean:
	$(RM) *.o *.exe

clean-objects:
	$(RM) *.o
