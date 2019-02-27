# Makefile for the test directory

CC=g++ -std=c++17
CFLAGS=-Wall -pedantic -Wextra -g
LINKER=-lpthread
UTILS=../utils/
SOURCE=../src/
TESTS=$(wildcard *_test.cpp)
EXE=$(TESTS:.cpp=.exe)
SRC=$(wildcard $(UTILS)*.cpp $(SOURCE)*.cpp)
OBJECTS=$(SRC:.cpp=.o)
OBJ=$(notdir $(OBJECTS))


all:	$(EXE)

#compile objects
%.o:	%.cpp
	$(CC) $(CFLAGS) -c $< -o $(notdir $@)

#compile all tests
%.exe:	%.cpp $(OBJECTS)
	$(CC) $(CFLAGS) ${OBJ} $(LINKER) $< -o $@

clean:
	$(RM) *.o *.exe

clean-objects:
	$(RM) *.o
