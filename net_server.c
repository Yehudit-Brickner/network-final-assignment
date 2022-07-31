#include <sys/types.h>
#include <unistd.h>          
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>     
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>

#define PORT 9999
#define SIM_LENGTH 10 

int main(void)
{ 
  int sock; 
  int connect_sock; 
  int count; // creating int vars
  struct sockaddr_in serv_name; // creating a sockaddr_in struct named serv_name
  size_t len; //creating a vaiable that will be the size of somthing
  
  sock = socket(AF_INET, SOCK_STREAM, 0);  // creating the socket. the int sock will get the socket number if succseful or -i if not.
  // printf("socket number %d", sock); 
  bzero(&serv_name, sizeof(serv_name)); 
  serv_name.sin_family = AF_INET;                                   
  serv_name.sin_port = htons(PORT); 

  bind(sock, (struct sockaddr *)&serv_name, sizeof(serv_name));// changing the memory to '\0' in the struct cli_name. before it was all garbage.
  //(starting at the begining of the emory if the struct- its address to the end of the struct -its size)
          
  listen(sock, 1); // making the socket listen to 1 client at a time.

  len = sizeof(serv_name); // len get the value of the size of the struct serv_name
  
  connect_sock = accept(sock, (struct sockaddr *)&serv_name, &len); // open a connection between the socket and the peer at the eddress of serv_name. return 0 i sucseful, -1 if not.

  // writing the message to the client 4 bits at a time.
  for (count = 1; count <= SIM_LENGTH; count++)
    { write(connect_sock, &count, 4);
      printf("Server has written %d to socket.\n", count);
    }

  close(connect_sock); // clossing the connection
  close(sock); // closing the socket

}
