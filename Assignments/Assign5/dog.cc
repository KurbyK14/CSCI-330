//*********************************************************************
//
// CSCI 330 Assignment 5 Dog: dog.cc
//
// Created by: Jacob Kurbis (z1945650)
// 
// Description: Is to write a program that will take the previous cat 
//              program assignment and upgrade it to add more features.
//
//              This is the C++ file that implements the function
//              defintions declared on the header file dog.h and called
//              on by main.cc.
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

/*
Function: void caesarCipher()
Use: This function performs a Caesar Cipher which encrypts the text data within the file by taking the letters of the input
     and shifting them upwards alphabetically by the shift_k variable amount.

Arguments: buffer: An array of characters to hold the file information
           length: A ssize_t integer that holds the length of bytes to cycle through til length - 1 bytes
           shift_k: A ssize_t integer to hold the amount of k letters to shift

Returns: Nothing
Notes: None
*/
void caesarCipher(char * buffer, ssize_t length, ssize_t shift_k)
{
    char temp;//A char variable that will hold the character at location buffer[i]

    for(int i = 0; i <= length - 1; i++)
    {
        temp = buffer[i];

        if(isupper(temp))
        {
            //Shifting the capital letters up by k letters
            temp = ((temp - 'A' + ((shift_k % 26) + 26)) % 26) + 'A';
        }

        else if(islower(temp))
        {
            //Shifting the lowercase letters up by k letters
            temp = ((temp - 'a' + ((shift_k % 26) + 26)) % 26) + 'a';
        }

        //Storing the character back into buffer[i] location
        buffer[i] = temp;
    }

}


/*
Function: void byteRotator()
Use: This function is similar to the Caesar Cipher function where it will shift the alphabetical text data by value k, but will also
     shift any value alphabetical or not by value k to each one byte value interpreted as 0 - 255.

Arguments: buffer: An array of characters to hold the file information
           length: A ssize_t integer that holds the length of bytes to cycle through til length - 1 bytes
           shift_k: A ssize_t integer to hold the amount of k letters to shift

Returns: Nothing
Notes: None
*/
void byteRotator(char * buffer, ssize_t length, ssize_t shift_k)
{
    //Rotating the bytes by k letters
    for(int i = 0; i <= length - 1; i++)
    {
        buffer[i] = ((int)buffer[i] + shift_k) % 256; 
    }
}


/*
Function: void hexConverter()
Use: This function will encode the characters in the buffer array to a hexadecimal format

Arguments: buffer: An array of characters to hold the file information
           length: A ssize_t integer that holds the length of bytes to cycle through til length - 1 bytes
           buff_hex: An array of new char that will hold the converted hexadecimal char

Returns: Nothing
Notes: None
*/
void hexConverter(char * buffer, ssize_t length, char* buff_hex)
{
    char hex[] = "0123456789adcdef";

    //Converting the buffer array into hexadecimal
    for(int i = 0; i <= length - 1; i++)
    {
        buff_hex[i * 2] = hex[(buffer[i] & 0xF0) >> 4];
        buff_hex[i * 2 + 1] = hex[(buffer[i] & 0x0F) >> 0];
    }

}


/*
Function: void binaryConverter()
Use: This function will encode the characters in the buffer array to a binary format

Arguments: buffer: An array of characters to hold the file information
           length: A ssize_t integer that holds the length of bytes to cycle through til length - 1 bytes
           buff_bin: An array of new char that will hold the converted binary char

Returns: Nothing
Notes: None
*/
void binaryConverter(char * buffer, ssize_t length, char * buff_bin)
{
    //Converting the buffer array into binary
    for(int i = 0; i <= length - 1; i++) 
    {
        for (int j = 0; j < 8; j++)
        {
            buff_bin[i * 8 + j] = ((buffer[i] & (1 << (7 - j))) >> (7 - j)) + 48;
        }
    }

}


/*
Function: ssize_t min()
Use: This function compares the buffer size of the read function with the difference of the max bytes minus the total number of
     bytes accumulated. Then determines which is the minimum value.
 
Arguments: i: A ssize_t integer that holds the buffer_size
           j: A ssize_t integer that holds the difference of the num - total_nBr 

Returns: i: A ssize_t integer that holds the buffer_size and is returned if it is the minimum value
                                 OR
         j: A ssize_t integer that holds the difference of the num - total_nBr and is returned if it is the minimum value
Notes: None
*/
ssize_t min(ssize_t i, ssize_t j)
{
    //If buffer_size is less than the difference of maxbytes - total_nBr
    if(i < j)
    {
        return i;
    }

    //Otherwise, return the diifference of maxbytes - total_nBr
    else
    {
        return j;
    }
}

