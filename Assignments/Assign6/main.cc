//*********************************************************************
//
// CSCI 330 Assignment 6 Pipe: main.cc
//
// Created by: Jacob Kurbis (z1945650)
// 
// Description: Is to write a program that will
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
#include <stdlib.h>
#include <stdio.h>
#include "pipe.h"

using namespace std;

int main(int argc, char* argv[])
{
    //Variables
    int pipefd[2];//
    //char * buffer;
    int rs;//
    char command1[255];//
    char command2[255];//

    cout << "Enter a command for both prompt 1 and 2" << endl
         << "Enter 'END' for either to end the program" << endl;

    cout << "command 1?: ";
    cin.getline(command1, 255);
    cout << endl;

    if(strcmp(command1, "END") == 0)
        {
            return 0;
        }

    cout << "command 2?: ";
    cin.getline(command2, 255);
    cout << endl;

    if(strcmp(command2, "END") == 0)
        {
            return 0;
        }

    //while(command1 != "END" && command2 != "END")
    //{

    if(strcmp(command1 , "END") != 0 && strcmp(command2 , "END") != 0)
    {
        pipe_fork(pipefd, rs);
    }

    else
    {
        perror("You need to type in a command!");
        return 1;
    }
    //}

    return 0;
}