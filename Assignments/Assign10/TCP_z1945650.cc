/**
 * @file TCP_z1945650.cc
 * @author Jacob Kurbis ZID: z1945650
 * @brief UNIX 330 Section 1: Assignment 10
 * @date 11-30-22
 * 
 */

#include <dirent.h>
#include <string.h>
#include <fstream>
#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

using namespace std;

//TCP server structs
struct sockaddr_in TCPserver;
struct sockaddr_in TCPclient;

//Function Prototypes
bool file_existsCheck(const char*);
bool file_nameCheck(const char*);
void transferFile(char*, int);
void chomp(char*);

int main(int argc, char *argv[])
{

   //Error checking for the correct number of arguments
   if (argc != 3)
   {
      cerr << "Usage: " << argv[0] << " port directory" << endl;
      exit(1);
   }

   //Initial Variables
   int sockTest;
   int FDsock_2;

   ssize_t readTest;

   char buffer[256];
   char* commandTest[2];
   char* HTML_direct = argv[2];

   socklen_t TCPserver_len = sizeof(sockaddr_in);
   socklen_t TCPclient_len = sizeof(sockaddr_in);

   DIR* direct_1;


   //New socket; Then error checking
   int FDsock_1 = socket(AF_INET, SOCK_STREAM, 0);

   if (FDsock_1 < 0)
   {
      perror("Error opening socket!\n");
      exit(1);
   }

   //Setting up TCP server values
   memset(&TCPserver, 0, sizeof(TCPserver));
   TCPserver.sin_family = AF_INET;
   TCPserver.sin_addr.s_addr = INADDR_ANY;
   TCPserver.sin_port = htons(atoi(argv[1]));

   //Getting size of TCP server & TCP client
   TCPserver_len = sizeof(TCPserver);
   TCPclient_len = sizeof(TCPclient);

   //Socket binding error checking
   sockTest = bind(FDsock_1, (struct sockaddr*) &TCPserver, TCPserver_len);

   if (sockTest < 0)
   {
      perror("Error binding socket!\n");
      exit(1);
   }

   //Socket listen error checking
   sockTest = listen(FDsock_1, 128);
   
   if (sockTest < 0)
   {
      perror("Error listening to socket!\n");
      exit(1);
   }
   
   //While loop to keep server running
   //Loop until the user exits the program(foreign host closes connection)
   while (true)
   {
      //Establishing new connection
      FDsock_2 = accept(FDsock_1, (struct sockaddr*) &TCPclient, &TCPclient_len);
      
      //Error for connection test
      if (FDsock_2 < 0)
      {
         perror("Could not accept connection\n");
	      exit(1);
      }
      
      
      //Parent; Accepts new request
      if (fork())
      {
         close(FDsock_2);
      }

      //Child; Processes request
      else
      {
         //Read; Then error check for read errors
	      readTest = read(FDsock_2, buffer, 256);

         if (readTest < 0)
         {
            perror("Could not read from socket\n");
	         exit(1);
         }

         //Error checking for 'GET' command
         commandTest[0] = strtok(buffer, " ");

         if (strcmp(commandTest[0], "GET") == 0)
         {
            commandTest[1] = strtok(NULL, " \n");
         }
         else
         {
            perror("Error: Invalid command\n");
            exit(1);
         }
	    
	      //Error checking for '/'
	      if (commandTest[1][0] != '/')
	      {
	         char error_1[] = "GET Request must begin with a '/'!\n";
	         write(FDsock_2, error_1, strlen(error_1));
	         exit(1);
	      }
	    
	      //Error checking for '..'
	      if (strstr(commandTest[1], "..") != NULL)
	      {
	         char error_2[] = "GET Request cannot contain \"..\"\n";
	         write(FDsock_2, error_2, strlen(error_2));
	         exit (1);
	      }
	    
	    
	      chomp(commandTest[1]);
	      strcat(HTML_direct, commandTest[1]);
	    
	      //If the last character in the path is a '/'
	      if (HTML_direct[strlen(HTML_direct)-1] != '/')
	      {
	         //Check if the file exists by name
	         if (file_nameCheck(HTML_direct))
	         {
	            transferFile(HTML_direct, FDsock_2);
	            close(FDsock_2);
	            exit(1);
	         }
	      }

         //The path is a directory instead of a file
	      else
	      {
	         char index[128];
	         char indexName[] = "index.html";
            
	         strcpy(index, HTML_direct);
	         strcat(index, indexName);
	         chomp(index);
	       
	         //If the directory contains a file called 'index.html'
	         if (file_existsCheck(index))
	         {
	            transferFile(index, FDsock_2);
		         sleep(10);
	            close(FDsock_2);
	            exit(1);
	         }

	      }
	    
	      //Open the directory containing the file
	      direct_1 = opendir((const char*) HTML_direct);

	      if (direct_1 == NULL)
	      {
            char error_3[] = "Could not open directory\n";
	         write(FDsock_2, error_3, strlen(error_3));
	         exit(1);
	      } 
   
         struct dirent* parent_direct;
	    
	      //Output file to the TCPclient
         if (dup2(FDsock_2, 1) < 0)
	      {
            perror("Could not redirect output\n");
	         exit(1);
	      }
	    
	      //Read and output the directory contents
	      while ((parent_direct = readdir(direct_1)) != NULL)
	      {
	         if (parent_direct->d_name[0] != '.')
	         {
	            cout << parent_direct->d_name << endl;
	         }
	      }
	 
	   }
	   
      //Close the socket the child process opened
      close(FDsock_2);
	   exit(1);
   }
      
   //Set the buffer to null characters
   memset(buffer, 0, sizeof(buffer));
   
   //Close the socket
   close(FDsock_1);
}


/**
 * @brief: This function will checks to see if a file exists or not
 * 
 * @param index: The path to the file
 *  
 * @return true or false 
 */
bool file_existsCheck(const char* index)
{
   struct stat buffer;
   return (stat(index, &buffer) == 0);
}


/**
 * @brief: This function will check to see if the name is a file or not
 * 
 * @param HTML_direct: The path to the file
 * 
 * @return true or false 
 */
bool file_nameCheck(const char* HTML_direct)
{
   struct stat buffer;
   stat(HTML_direct, &buffer);

   if ((buffer.st_mode & S_IFMT) == S_IFREG)
      {
         return true;
      }
   else
      {
         return false;
      }
}


/**
 * @brief: This function will transfer the file to the client
 * 
 * @param HTML_direct: The path to the file 
 * @param FDsock_2: The socket to send the file to
 */ 
void transferFile(char* HTML_direct, int FDsock_2)
{
   int FD;
   ssize_t num_bytes;
   char buffer[256];
   char error_4[] = "File does not exist\n";

   FD = open(HTML_direct, O_RDWR);

   if (FD < 0)
   {
      write(FDsock_2, error_4, strlen(error_4));
      exit(1);
   }

   num_bytes = read(FD, (char*) buffer, 256);
   write(FDsock_2, buffer, (size_t) num_bytes);

   while ((int) num_bytes >= 256)
   {
      num_bytes = read(FD, (char*) buffer, 256);
      write(FDsock_2, buffer, (size_t) num_bytes);
   }
}


/**
 * @brief: This function will remove the newline character from a string
 * 
 * @param string: The string to remove the newline character from
 */
void chomp(char *string) 
{
   int i = strlen(string) - 1;

   while (i >= 0 && (string[i] == '\n' || string[i] == '\r'))
   {
      string[i] = '\0';
      i--;
   }
}
