
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char* argv[]) {
  struct addrinfo* res; // creating a pointer to addrinfo struct that contains info about address of service provider.
  char* hostname;
  char* hostaddr; // char pointer vars
  struct sockaddr_in* saddr; // creating a pointer to sockaddr_in struct named saddr
  
  if (argc != 2) { // making sure we got the correct amount of variables in the command line
    perror("Usage: hostnamelookup <hostname>\n");
    exit(1);
  }

  hostname = argv[1]; // host name points to the string of chars that is the website given.
  
  if (0 != getaddrinfo(hostname, NULL, NULL, &res)) { // making sure we were able to get the ip address of the website given the info is put into the struct res.
    fprintf(stderr, "Error in resolving hostname %s\n", hostname);
    exit(1);
  }
  
  saddr = (struct sockaddr_in*)res->ai_addr; // a pointer to a the socket address 
  hostaddr = inet_ntoa(saddr->sin_addr); // the hostaddr pointer points to the beginning of the string for the website ip.

  printf("Address for %s is %s\n", hostname, hostaddr); // printing the website and the ip addres for it.
  exit(0);
}
