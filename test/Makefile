# Makefile for the test directory
# Author: Lauri Westerholm

CC=g++ -std=c++17
CFLAGS=-Wall -pedantic -Wextra -g -fPIC
LINKER=-lpthread
UTILS=../utils/
SOURCE=../src/
TESTS=$(wildcard *_test.cpp)
EXE=$(TESTS:.cpp=.exe)
SRC=$(wildcard $(UTILS)*.cpp $(SOURCE)*.cpp)
OBJ=$(SRC:%.cpp=%.o)

.PHONY: all clean clean-objects

all:	$(EXE)

# compile objects
%.o:	%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# compile all tests
%.exe:	%.cpp $(OBJ)
		$(CC) $(CFLAGS) $(LINKER) $^ -o $@

clean:
	$(RM) *.o *.exe *.so $(SOURCE)*.o $(UTILS)*.o

clean-objects:
	$(RM) *.o

# create a dynamic library from PhysicsEngine
libphysengine.so:	$(OBJ)
	g++ $^ -shared -o $@
