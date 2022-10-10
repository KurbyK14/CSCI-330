#
# CSCI 330 Assignment 6 Pipe: makefile
#
# Created By: Jacob Kurbis (z1945650)
#
# Description: Is to write a program that will 
#
#              This is the makefile for the pipe program, it will take
#              the files pipe.h, and main.cc and combine them
#              to make the pipe program.
#
# DATE DUE:   10/10/2022
#

# Compiler variables
CXX = g++
CXXFLAGS = -Wall -std=c++11

# Rules to link object code files to create executable file
pipe: main.o pipe.o
	$(CXX) $(CXXFLAGS) -o pipe $^

# Rules to compile source code files to object code
main.o: main.cc pipe.h
pipe.o: pipe.cc pipe.h

# Pseudo-target to remove object code and executable files
clean:
	rm -f pipe *.o
