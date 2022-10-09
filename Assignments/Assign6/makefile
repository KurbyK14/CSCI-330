#
# PROGRAM:    Assignment 6
# PROGRAMMER: your name
# LOGON ID:   your z-ID
# DATE DUE:   9/15/2022
#

# Compiler variables
CXX = g++
CXXFLAGS = -Wall -std=c++11

# Rules to link object code files to create executable file
all: pipe

pipe: pipe.o
	$(CXX) $(CXXFLAGS) -o pipe $^

# Rules to compile source code files to object code
pipe.o: pipe.cc

# Pseudo-target to remove object code and executable files
clean:
	rm -f pipe *.o
