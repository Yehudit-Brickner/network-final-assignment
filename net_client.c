







#include <sys/types.h>
#include <unistd.h>          
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>    
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#define SIM_LENGTH 10 
#define IP_ADDRESS "10.9.13.222" 
// #define IP_ADDRESS "????"
#define PORT 9999

int main(void)
{ 
  int sock; 
  int count;
  int value;  // creating int vars
  struct sockaddr_in cli_name; // creating a sockaddr_in struct named cli_name

  printf("Client is alive and establishing socket connection.\n");
  
  
  sock = socket(AF_INET, SOCK_STREAM, 0); // creating the socket. the int sock will get the socket number if succseful or -i if not.
  if (sock < 0) // checking if sucsesful.
    { perror ("Error opening channel"); // if not succsesful will write the error to  standard error and close the socket
      close(sock);
      exit(1);
    }
      

  bzero(&cli_name, sizeof(cli_name)); // changing the memory to '\0' in the struct cli_name. before it was all garbage.
  //(starting at the begining of the memory of the struct- its address, to the end of the struct -its size)

  /* initilizig the 3 parts of the struct cli_name: 
  sin_family= address family- ip type
  sin_addr.s_addr= ip address
  sin_port= port number */
  cli_name.sin_family = AF_INET; 
  cli_name.sin_addr.s_addr = inet_addr(IP_ADDRESS); 
  cli_name.sin_port = htons(PORT);


// open a connection between the socket and the port at the address of cli_name. return 0 i sucseful, -1 if not.
  if (connect(sock, (struct sockaddr *)&cli_name, sizeof(cli_name)) < 0)
    { perror ("Error establishing communications"); // if not succsesful will write the error to  standard error and close the socket
      close(sock);
      exit(1);
    }

  // reading the message from the server 4 bits at a time
  for (count = 1; count <= SIM_LENGTH; count++)
    { read(sock, &value, 4);
      printf("Client has received %d from socket.\n", value); // printing what we reseved.
    }

  printf("Exiting now.\n");

  close(sock); // closing the socket
  exit(0); 

} 
