//*********************************************************************
//
// CSCI 330 Assignment 5 Dog: main.cc
//
// Created by: Jacob Kurbis (z1945650)
// 
// Description: Is to write a program that will take the previous cat 
//              program assignment and upgrade it to add more features.
//
//              This is the C++ file that holds the function "int main"
//              that will call upon the dog.h header file and the 
//              dog.cc C++ file to implement a better "cat" command for
//              UNIX "dog".
//
// Due Date: 10/04/2022
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
#include "dog.h"

int main(int argc, char* argv[])
{
    //Variables
    int fd,//An integer to hold the file
        opt;//An integer to return the ASCII value of the optional parameter
    
    ssize_t buffer_size = 20,//A ssize_t integer that holds the number of bytes to read per cycle
            num = 0,//A ssize_t integer to hold the '-n' optional parameter and intialize it to 0
            shift_k,//A ssize_t integer to hold the amount of k letters to shift 
            num_bytes_read = 1,//A ssize_t integer that holds the number of bytes to be read from
            total_nBr;//A ssize_t integer that holds the total number of bytes read so far
    
    bool flag_n = false,
         flag_r = false,//A boolean value that holds false until proven true for the optional parameter -r
         flag_C = false,//A boolean value that holds false until proven true for optional parameter -C
         flag_X = false,//A boolean value that holds false until proven true for optional parameter -X
         flag_B = false;//A boolean value that holds false until proven true for optional parameter -B

    char * buffer;//An array of characters to hold the file information
    char * buff_hex;//An array of characters to hold the file information in hexadecimal
    char * buff_bin;//An array of characters to hold the file information in binary
    char optstring[] = {"b:n:C:r:XB"};//An array of characters to be sent into the getopt function to check for optional parameters
        
    //while loop utilizing getopt
    while((opt = getopt(argc, argv, optstring)) != -1)
    {
        switch(opt)
        {
            //To change the size of the buffer used for calls to read and write to N bytes
            case 'b':
            
            buffer_size = atoi(optarg);
            
            break;


            //To change the number of bytes read from each file before finishing to N
            case 'n':
            
            flag_n = true;//Setting the flag to true if the optional comamnd line argument 'n' is present
            num = atoi(optarg);

            break;


            //To apply a Caesar cipher with a shift of k letters to alphabetical characters in the data read in before writing the results
            case 'C':

            flag_C = true;//Setting the flag to true if the optional comamnd line argument 'C' is present
            shift_k = atoi(optarg);

            break;


            //To apply a general rotation (Caesar shift for all characters, not just letters) with a shift of k to the input data before
            //writing it back out
            case 'r':
            
            flag_r = true;//Setting the flag to true if the optional comamnd line argument 'r' is present
            shift_k = atoi(optarg);

            break;


            //To output the data from the file in hexadecimal format
            case 'X':
            
            flag_X = true;//Setting the flag to true if the optional comamnd line argument 'X' is present

            break;


            //To output the data from the file in binary notation, most significant bit first
            case 'B':
            
            flag_B = true;//Setting the flag to true if the optional comamnd line argument 'B' is present
            break;
            

            default:
            perror("There was no optional parameters selected!");//print error message if all other cases fail

        }
    }

    //Declare new char arrays for optional parameters '-X' and '-B'
    buffer = new char[buffer_size];
    buff_hex = new char[buffer_size * 2];
    buff_bin = new char[buffer_size * 8 + 1];

    //Checking for a standard input ("-") command
    for(int i = optind; i <= argc - 1; i++)
    {
        //Checks for standard input command
        if(strcmp(argv[i], "-") == 0) 
        {
            fd = 0;//Sets the file descriptor to standard input
        }

        else 
        {   //If the file has any normal name
            fd = open(argv[i], O_RDONLY, 0644); //opens and records the file descriptor of the file in the argument

            //Check for open error
            if(fd == -1) 
            {
                perror("OPEN");
                return 1;
            }
        }
    
        //Reading and Writing the file
        while((num_bytes_read = read(fd, buffer, (flag_n ? min(buffer_size, num - total_nBr) : buffer_size))) > 0) 
        {   
            //Accumulating the number of total bytes read
            total_nBr += num_bytes_read;

            if(num_bytes_read == -1) 
            {   //Check for read error
                perror("READ");
                return 3;
            }

            //If optional parameters 'r' and 'C' are specified
            if(flag_r == true && flag_C == true)
            {
                perror("READ: optional parameters -r and -C cannot be used at the same time, specify only one at a time");
                return 2;
            }

            //If optional parameters 'X' and 'B' are specified
            if(flag_X == true && flag_B == true)
            {
                perror("READ: optional parameters -X and -B cannot be used at the same time, specify only one at a time");
                return 2;
            }

            //If optional parameter 'C' is present 
            if(flag_C == true)
            {
                caesarCipher(buffer, num_bytes_read, shift_k);
            }

            //If optional parameter 'r' is present 
            if(flag_r == true)
            {
                byteRotator(buffer, num_bytes_read, shift_k);
            }
            
            //If optional parameter 'X' is present 
            if(flag_X == true)
            {
                hexConverter(buffer, num_bytes_read, buff_hex);

                //Formatting the bytes to write in binary
                write(1, buff_hex, num_bytes_read * 4);
            }

            //If optional parameter 'B' is present 
            else if(flag_B == true)
            {
                binaryConverter(buffer, num_bytes_read, buff_bin);

                //Formatting the bytes to write in binary
                write(1, buff_bin, num_bytes_read * 8); 
            }

            else
            {
                //Writes the bytes of the file
                write(1, buffer, num_bytes_read);
            }

        }
    }

    if(fd == -1) 
    {   //Check for close error
        perror("CLOSE");
    }

//Checking if the file is open and closing it
if(fd > 0) 
{
    close(fd);
}
//Delete the character arrays
delete[] buffer;  
delete[] buff_hex;
delete[] buff_bin;

return 0;
}
