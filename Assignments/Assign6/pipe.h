#ifndef PIPE_H
#define PIPE_H

//*********************************************************************
//
// CSCI 330 Assignment 6 Pipe: pipe.h
//
// Created by: Jacob Kurbis (z1945650)
// 
// Description: Is to write a program that will pipe the first command
//              through the second command.
//
//              This is the header file that declares the function
//              definitions for the C++ file main.cc.
//
// Due Date: 10/10/2022
//
//*********************************************************************

#include <sys/types.h>

//Function Prototypes

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
void pipe_fork(int[], int, pid_t, char[], char[]);


#endif
