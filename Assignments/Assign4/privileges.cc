//***************************************************************************
//
//  privileges.cc
//  UNIX 330 Assignment 4: privileges implementation
//  
//  Purpose: To write a C++ program that will allow you to add messages
//           to a file that has no permissions granted for any user.
//
//  Created by: Jacob Kurbis (z1945650)
//
//**************************************************************************/

#include <iostream>
#include <iomanip>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

using namespace std;

int main(int argc, char *argv[]) 
{
    //Variables
    int fd;//An integer to hold the file
    int filePosition = 1;//An integer to hold the file position
    int opt;//An integer to return the ASCII value of the optional parameter
    bool flag = true;//A boolean value that hold true until a optional parameter is found
    char optstring[2] = {'c'};//A char array to be sent into the getopt function
    
    //Chceking if there are less than 3 arguments provided
    if( argc < 3)
    {
        cerr << "Program [-c] file no string message" << endl;//Print out compilation error message if there are less than 3 arguments provided
    }

    //Initializing the stat buf structure
    struct stat buf;

    //Checkiing for any "-c" or optional parameters provided in the command line arguments
    while((opt = getopt(argc, argv, optstring)) != -1)
    {
        switch(opt)
        {
            case 'c':
            fd = 2;//Setting the file to argument position 2
            flag = false;//Setting the flag to false if there is an optional comamnd line argument present
            break;

            default:
            perror("What did you do?!");//print error message if case 'c' fails
        }
    }

    //Getting the stat permissions of the file
    int status = stat(argv[filePosition], &buf);

    //Creating a new file giving user write permissions only
    if( status == -1)
    {
        fd = open(argv[filePosition], O_WRONLY | O_CREAT, S_IWUSR);

        //Error if file fails to open
        if( fd == -1)
        {
            perror("open error");
            return 2;
        }

        close(fd);//CLosing the file immediately after creating it

    }

    //If the pointer buf at st_mode is not equal to the permission bits
    else if((buf.st_mode) != 32768)
    {
        cout << "Permission Denied" << endl;
    }

    //Changing the permissions of the file
    int changePriv = chmod(argv[filePosition], 0700);

    //If changing the permissions fails
    if(changePriv < 0)
    {
        perror("chmod error");
        return 3;
    }

    //Adding a newline charcter at the end of the file
    strcat(argv[filePosition + 1], "\n");

    //If the file exists and there is no optional parameter "-c", write and append to the end of the file
    if(flag)
    {
        int fd = open(argv[filePosition], O_WRONLY | O_APPEND);

        //Error if file fails to open
        if(fd == -1)
        {
            perror("write error");//Error if file fails to write
            return 4;
        }
    }

    else
    {
        //If the file exists and there is an optional parameter "-c", write after truncating the file
        int fd = open(argv[filePosition], O_WRONLY | O_TRUNC);

        //Error if file fails to open
        if(fd == -1)
        {
            perror("open error");
            return 5;
        }

        int writeNew = write(fd, argv[filePosition + 1], strlen(argv[filePosition + 1]));

        //Error if new write call fails
        if(writeNew == -1)
        {
            perror("write error");
            return 6;
        }
    }

    //Resetting the permissions back to secure state
    changePriv = chmod(argv[filePosition], 0000);

    if(changePriv < 0)
    {
        perror("chmod error");//Error if permissions fail to be changed back
    }

    close(fd);//Close the file 

    //End of Program

}