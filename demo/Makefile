# Makefile for PhysicsEngine Demo
# Creates libphysengine.so library to ../test
# Author: Lauri Westerholm

CC=g++ -std=c++17
CFLAGS=-Wall -pedantic -Wextra -g
TEST_DIR=../test/
LINKER=-pthread -lsfml-graphics -lsfml-window -lsfml-system
UI_dir=UI-elements/
OBJECTS=$(filter-out demo.cpp, $(wildcard *.cpp $(UI_dir)*.cpp))
OBJ=$(OBJECTS:%.cpp=%.o)

.PHONY:	run clean clean-objects

all: demo

run: demo
	./$<

$(TEST_DIR)libphysengine.so:
	$(MAKE) -C $(TEST_DIR) libphysengine.so

# compile objects
%.o:	%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# compile the main (demo.cpp)
demo:	$(TEST_DIR)libphysengine.so demo.cpp $(OBJ)
	$(CC) $(CFLAGS) $(LINKER) $^ -o $@

clean:
	$(RM) *.o demo $(UI_dir)*.o
	$(MAKE) -C $(TEST_DIR) clean

clean-objects:
	$(RM) *.o $(UI_dir)*.o
