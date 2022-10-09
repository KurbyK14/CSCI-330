//*********************************************************************
//
// CSCI 330 Assignment 3 Cat: cat.cc
//
// Created by: Jacob Kurbis (z1945650)
// 
// Description: To write a basic implementation of the cat command to 
//              practice using the system calls for working with files 
//              on a UNIX system.
//
// Due Date: 09/16/2022
//
//*********************************************************************

#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>
#include <errno.h>

using namespace std;

#define BUFFER_SIZE 20 //constant that represents the amounts of bytes read per cycle

/**
 * In main, each file argument is read or created, and then written 20 bytes at a time.
 * This allows for any file size and standard input given the argument "-".
 *
 * @param argc An integer representing the amount of arguments of the command line.
 * @param argv[] An array of the arguments of the command line. Used to site files.
 *
 * @return An integer representing different outcomes of the function.
 ********************************************************************************/

int main(int argc, char* argv[])
{
    //Variables
    int fd;//An integer to hold the file
    ssize_t num_bytes = 1;//A special integer that holds the number of bytes to be read from
    char buffer[BUFFER_SIZE + 1];//An array of characters to hold the file information and initializes the buffer with the constant size

    for(int i = 1; i < argc && argc > 1; i++) 
    {   //This loop will run through all the files given as arguments

		if(strcmp(argv[i] , "-") == 0) 
        {    //checks for standard input command
			 fd = 0; //0 is the file descriptor for standard input
		}

        else 
        {   //if the file has any normal name
            fd = open(argv[i], O_RDWR | O_CREAT, 0644); //opens and records the file descriptor of the file in the argument

            if(fd == -1) 
            {   //checks for error
                perror("open");
                return 2;
            }
		}


        buffer[num_bytes] = 0;//places null terminator there

		while(num_bytes > 0) 
        {   //runs for every byte in the given range
		    num_bytes = read(fd, buffer, BUFFER_SIZE);

			if(num_bytes == -1) 
            {   //checks for errors
                perror("read");
                return 3;
            }

			write(1, buffer, num_bytes); //writes the certain amount of bytes of the file
		}


        int close_file = close(fd); //the file will be closed

        if(close_file == -1) 
        {   //error if close_file does not close properly
            perror("close");
        }

    }

    if(argc <= 1) 
    {   //will spit out an error if there are no arguments
        cerr << "Missing argument\n"<< "Usage: file\n";
        return 1;
    }

	return 0;
}
