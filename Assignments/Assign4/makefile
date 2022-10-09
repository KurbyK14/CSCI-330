#
# PROGRAM:    Assignment 3
# PROGRAMMER: your name
# LOGON ID:   your z-ID
# DATE DUE:   9/15/2022
#

# Compiler variables
CXX = g++
CXXFLAGS = -Wall -std=c++11

# Rules to link object code files to create executable file
all: privileges

cat: privileges.o
	$(CXX) $(CXXFLAGS) -o privileges $^

# Rules to compile source code files to object code
privileges.o: privileges.cc

# Pseudo-target to remove object code and executable files
clean:
	rm -f privileges *.o
