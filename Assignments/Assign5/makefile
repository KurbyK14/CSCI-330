#
# CSCI 330 Assignment 5 Dog: makefile
#
# Created By: Jacob Kurbis (z1945650)
#
# Description: Is to write a program that will take the previous cat 
#              program assignment and upgrade it to add more features.
#
#              This is the makefile for the dog program, it will take
#              the files dog.h, main.cc, and dog.cc and combine them
#              to make the dog program.
#
# DATE DUE:   10/04/2022
#


# Compiler variables
CXX = g++
CXXFLAGS = -Wall -Werror -std=c++11#Wextra #pedantic

# Rules to link object code files to create executable file
dog: main.o dog.o
	$(CXX) $(CXXFLAGS) -o dog $^

# Rules to compile source code files to object code
main.o: main.cc dog.h
dog.o: dog.cc dog.h

# Pseudo-target to remove object code and executable files
clean:
	rm -f dog *.o
