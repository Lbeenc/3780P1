# CMP SCI 3780 — Project 1 Makefile
CXX := g++
CXXFLAGS_DEBUG := -std=c++17 -O0 -g -fno-omit-frame-pointer -Wall -Wextra -pedantic
CXXFLAGS := -std=c++17 -O2 -g -Wall -Wextra -pedantic

all: task1 task2 task3

task1: task1.cpp
	$(CXX) $(CXXFLAGS_DEBUG) $< -o $@

task2: task2.cpp
	$(CXX) $(CXXFLAGS_DEBUG) $< -o $@

task3: task3.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -f task1 task2 task3

.PHONY: all clean
