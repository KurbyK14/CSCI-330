//*********************************************************************
//
// CSCI 330 Assignment 6 Pipe: main.cc
//
// Created by: Jacob Kurbis (z1945650)
// 
// Description: Is to write a program that willIs to write a program that will pipe the first command
//              through the second command.
//
//              This is the makefile that will combine main.cc, pipe.h, and pipe.cc
//              to make the pipe program
//
// Due Date: 10/10/2022
//
//*********************************************************************

#include <iostream>
#include <fstream>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <cstring>
#include "pipe.h"

using namespace std;

int main()
{
    //Variables
    int pipefd[2];//An array of intgers to pipe the commands through
    int rs;//An integer that will store the pipe
    char command1[256];//A character array that holds the value of the first command
    char command2[256];//A character array that holds the value of the second command
    char* cmd1[256];//A character array that will hold the command 1 pointer
    char* cmd2[256];//A character array that that will hold the command 1 pointer
    pid_t pid = 0;//A pid_t variable type that holds the child's process pid

    cout << "Enter a command for both prompt 1 and 2" << endl
         << "Enter 'END' for either to end the program" << endl;

    cout << "command 1?: ";
    cin.getline(command1, 255);
    cout << endl;

    if(strcmp(command1, "END") == 0)
        {
            cout << "Process END\n";
            exit(1);
        }

    cout << "command 2?: ";
    cin.getline(command2, 255);
    cout << endl;

    if(strcmp(command2, "END") == 0)
        {
            cout << "Process END\n";
            exit(1);
        }
    
    cmd1[256] = strtok(command1, " ");
    
    cmd2[256] = strtok(command2, " ");


    //Creating Pipe
    rs = pipe(pipefd);
    //Error Check
    if(rs < 0)
    {
        perror("PIPE");
        exit(1);
    }

    //while(command1 != "END" && command2 != "END")
    //{

    if(strcmp(command1 , "END") != 0 && strcmp(command2 , "END") != 0)
    {
        pipe_fork(pipefd, rs, pid, cmd1[256], cmd2[256]);
    }

    else
    {
        perror("You need to type in a command!");
        return 1;
    }
    //}

    return 0;
}