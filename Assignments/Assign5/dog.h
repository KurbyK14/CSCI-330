#ifndef DOG_H
#define DOG_H

//*********************************************************************
//
// CSCI 330 Assignment 5 Dog: dog.h
//
// Created by: Jacob Kurbis (z1945650)
// 
// Description: Is to write a program that will take the previous cat 
//              program assignment and upgrade it to add more features.
//
//              This is the header file that declares the function
//              defintions for the C++ file dog.cc.
//
// Due Date: 10/04/2022
//
//*********************************************************************

#include <sys/types.h>

//Helper Functions Prototypes

/*
Function: void caesarCipher()
Use: This function performs a Caesar Cipher which encrypts the text data within the file by taking the letters of the input
     and shifting them upwards alphabetically by the shift_k variable amount.

Arguments: char *: An array of characters to hold the file information
           ssize_t: A ssize_t integer that holds the length of bytes to cycle through til length - 1 bytes
           ssize_t: A ssize_t integer to hold the amount of k letters to shift

Returns: Nothing
Notes: None
*/
void caesarCipher(char *, ssize_t, ssize_t);


/*
Function: void byteRotator()
Use: This function is similar to the Caesar Cipher function where it will shift the alphabetical text data by value k, but will also
     shift any value alphabetical or not by value k to each one byte value interpreted as 0 - 255.

Arguments: char *: An array of characters to hold the file information
           ssize_t: A ssize_t integer that holds the length of bytes to cycle through til length - 1 bytes
           ssize_t: A ssize_t integer to hold the amount of k letters to shift

Returns: Nothing
Notes: None
*/
void byteRotator(char *, ssize_t, ssize_t);


/*
Function: void hexConverter()
Use: This function will encode the characters in the buffer array to a hexadecimal format

Arguments: char *: An array of characters to hold the file information
           ssize_t: A ssize_t integer that holds the length of bytes to cycle through til length - 1 bytes
           char *: An array of new char that will hold the converted hexadecimal char

Returns: Nothing
Notes: None
*/
void hexConverter(char *, ssize_t, char *);


/*
Function: void binaryConverter()
Use: This function will encode the characters in the buffer array to a binary format

Arguments: char *: An array of characters to hold the file information
           ssize_t: A ssize_t integer that holds the length of bytes to cycle through til length - 1 bytes
           char *: An array of new char that will hold the converted binary char

Returns: Nothing
Notes: None
*/
void binaryConverter(char *, ssize_t, char *);


/*
Function: ssize_t min()
Use: This function compares the buffer size of the read function with the difference of the max bytes minus the total number of
     bytes accumulated. Then determines which is the minimum value.
 
Arguments: A ssize_t integer that holds the buffer_size
           A ssize_t integer that holds the difference of the num - total_nBr 

Returns: A ssize_t integer that holds the buffer_size and is returned if it is the minimum value
                                 OR
         A ssize_t integer that holds the difference of the num - total_nBr and is returned if it is the minimum value
Notes: None
*/
ssize_t min(ssize_t, ssize_t);

#endif
