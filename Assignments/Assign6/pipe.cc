//*********************************************************************
//
// CSCI 330 Assignment 6 Pipe: pipe.cc
//
// Created by: Jacob Kurbis (z1945650)
// 
// Description: Is to write a program that 
//
//              This is the C++ file that implements the function
//              defintions declared on the header file pipe.h and called
//              on by main.cc.
//
// Due Date: 10/10/2022
//
//*********************************************************************

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "pipe.h"

/*
Function: void pipe_fork()
Use: This function 

Arguments: 

Returns: Nothing
Notes: None
*/
void pipe_fork(int pipefd, int rs)
{
    //Creating Pipe
    rs = pipe(pipefd);
    //Error Check
    if(rs < 0)
    {
        perror("PIPE");
        exit(1);
    }

    //Fork into Parent and Child processes
    rs = fork();
    //Error Check
    if(rs < 0)
    {
        perror("FORK");
        exit(1);
    }

    if(rs == 0)//Child process
    {
        close(pipefd[1]);//close write end of pipe
        close(0);//close standard input

        dup(pipefd[0]);//Duplicate read end of pipe in standard input
        close(pipefd[0]);//close read end of pipe

        //strtok();

        //run wc
        rs = execvp();
        //Error Check
        if (rs < 0)
        {
            perror("EXECVP");
            exit(1);
        }

        //ssize_t nr = read(pipefd[0], buffer, sizeof(buffer));
        //write(1, buffer, nr);

        //cout << "pipe contained:" << buffer << endl;

    }

    else//Parent process
    {
        close(pipefd[0]);//close read end of the pipe, keep write end open
        close(1);//close standard output

        dup(pipefd[1]);//duplicate write end of pipe into standard output

        close(pipefd[1]);//close write end of the pipe

        //strtok();

        //run ls
        rs = execvp();
        //Error Check
        if (rs < 0)
        {
            perror("EXECVP");
            exit(1);
        }

        //write(1, buffer, nr);//write to right end of pipe
        //wait(&rs)
    }
}

