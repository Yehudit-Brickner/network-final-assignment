
#include <sys/types.h>
#include <unistd.h>          
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>    
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

#define SIM_LENGTH 10 
#define IP_ADDRESS "10.9.13.222" 
// #define IP_ADDRESS "????"
#define PORT 9999 

int main(int argc, char *argv[])
{ 

    // getting the ip for the website given

    struct addrinfo* res; // creating a pointer to addrinfo struct that contains info about address of service provider.
    char* hostname;
    char* hostaddr; // char pointer vars
    struct sockaddr_in* saddr; // creating a pointer tosockaddr_in struct named saddr
    
    if (argc != 2) { // making sure we got the correct amount of variables in the command line
        perror("Usage: hostnamelookup <hostname>\n");
        exit(1);
    }

    hostname = argv[1]; // host name points to the string of chars that is the website given when running the code.
    
    if (0 != getaddrinfo(hostname, NULL, NULL, &res)) { // making sure we were able to get the ip address of the website given. the info about the website is put into the struct res.
        fprintf(stderr, "Error in resolving hostname %s\n", hostname); // if we werent able, we will write an error to the file stderr.
        exit(1);
    }
    
    saddr = (struct sockaddr_in*)res->ai_addr; // a pointer to a the socket address 
    hostaddr = inet_ntoa(saddr->sin_addr); // the hostaddr pointer points to the beginning of the string for the website ip.

    printf("Address for %s is %s\n", hostname, hostaddr); // printing the website and the ip addres for it.
    
    // got the ip address. the rest of the code is very similar to net_client. 

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
    //(starting at the begining of the memory of the struct- its address to the end of the struct -its size)

    /* initilizig the 3 parts of the struct cli_name: 
    sin_family= address family- ip type
    sin_addr.s_addr= ip address
    sin_port= port number */
    cli_name.sin_family = AF_INET; 
    cli_name.sin_addr.s_addr = inet_addr(hostaddr); 
    cli_name.sin_port = htons(PORT);


    // open a connection between the socket and the peer at the eddress of cli_name. return 0 i sucseful, -1 if not.
    if (connect(sock, (struct sockaddr *)&cli_name, sizeof(cli_name)) < 0)
        { perror ("Error establishing communications");
        close(sock);
        exit(1);
        }

    // reading the message from the server 4bits at a time
    for (count = 1; count <= SIM_LENGTH; count++)
        { read(sock, &value, 4);
        printf("Client has received %d from socket.\n", value);
        }

    printf("Exiting now.\n");

    close(sock); // closing the socket
    exit(0); 

} 
