//*********************************************************************
//
// CSCI 330 Assignment 6 Pipe: pipe.cc
//
// Created by: Jacob Kurbis (z1945650)
// 
// Description: Is to write a program that will pipe the first command
//              through the second command.
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
#include <cstring>
#include "pipe.h"

/*
Function: void pipe_fork(int pipefd[], int rs, pid_t pid, char cmd1[], char cmd2[])
Use: This function will create the child and parent processes to pipe the commands through. 

Arguments: pipefd: An array of intgers to pipe the commands through
           rs: An integer that will store the pipe
           pid: A pid_t variable type that holds the child's process pid
           cmd1: A character array that will hold the command 1 pointer
           cmd2: A character array that that will hold the command 2 pointer

Returns: Nothing
Notes: None
*/
void pipe_fork(int pipefd[], int rs, pid_t pid, char cmd1[], char cmd2[])
{

    //Fork into Parent and Child processes
    pid = fork();
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

        //run wc
        pid = execvp(cmd1, nullptr);
        //Error Check
        if (rs < 0)
        {
            perror("EXECVP");
            exit(1);
        }


    }

    else//Parent process
    {
        close(pipefd[0]);//close read end of the pipe, keep write end open
        close(1);//close standard output

        dup(pipefd[1]);//duplicate write end of pipe into standard output

        close(pipefd[1]);//close write end of the pipe

        //run ls
        pid = execvp(cmd2, nullptr);
        //Error Check
        if (rs < 0)
        {
            perror("EXECVP");
            exit(1);
        }

    }
}

