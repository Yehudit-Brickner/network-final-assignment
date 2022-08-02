

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


int main(int argc ,char* argv[]){

    if (argc != 2) { // making sure we got the correct amount of variablesin the command line
        perror("Usage: hostnamelookup <hostname>\n");
        exit(1);
    }


    char *text = argv[1];
    const char t[200]; 
    char hostname[150];
    memset(&hostname[0], 0, sizeof(hostname));
    int port = 80;
    char path[150];
    memset(&path[0], 0, sizeof(path));
 
    

    sscanf(text, "http://%99[^/]/%99[^\n]", hostname, path);
    if(strchr(hostname, ':') != NULL){
        char * token = strtok(hostname, ":");
        token = strtok(NULL, " ");
        port = atoi(token);
    }
    
    
    const char h[150];
    memset(&h[0], 0, sizeof(h));
    strcpy(h,hostname);
    // printf("hostname = \"%s\"\n", hostname);
    // printf("port = \"%d\"\n", port);
    // printf("path = \"%s\"\n", path);



    struct addrinfo* res; // creating a pointer to addrinfo struct that contains info about address of service provider.
    char* hostaddr; // char pointer vars
    struct sockaddr_in* saddr; // creating a pointer tosockaddr_in struct named saddr
    
    
    if (0 != getaddrinfo(hostname, NULL, NULL, &res)) { // making sure we were able to get the ip address of the website given the info is put into the struct res.
        fprintf(stderr, "Error in resolving hostname %s\n", hostname);
        exit(1);
    }
    
    saddr = (struct sockaddr_in*)res->ai_addr; // a pointer to a the socket address 
    hostaddr = inet_ntoa(saddr->sin_addr); // the hostaddr pointer points to the beginning of the string for the website ip.

    printf("Address for %s is %s\n", hostname, hostaddr); // printing the website and the ip addres for it.
    

    int sock; 
    int count;
    int value;  // creating int vars
    struct sockaddr_in cli_name; // creating a sockaddr_in struct named cli_name
    
        
    printf("Client is alive and establishing socket connection.\n");
    
    
    sock = socket(AF_INET, SOCK_STREAM, 0); // creating the socket. the int sock will get the socket number if succseful or -i if not.
    if (sock < 0) // checking if sucsesful.
        { perror ("Error opening channel");
        close(sock);
        exit(1);
        };
        

    bzero(&cli_name, sizeof(cli_name)); // changing the memory to '\0' in the struct cli_name. before it was all garbage.
    //(starting at the begining of the emory if the struct- its address to the end of the struct -its size)

    /* initilizig the 3 parts of the struct cli_name: 
    sin_family= address family- ip type
    sin_addr.s_addr= ip address
    sin_port= port number */
    cli_name.sin_family = AF_INET; 
    cli_name.sin_addr.s_addr = inet_addr(hostaddr); 
    cli_name.sin_port = htons(port);

  
    const char  r1[] = "GET /";
    strcat(r1,path);
    const char r2[200]; 
    memset(&r2[0], 0, sizeof(r2));
    strcpy(r2,r1);
    // printf("string2 %s\n",r2);
    const char r3[] = " HTTP/1.0\r\n";
    strcat(r2,r3);
    const char r4[250]; 
    memset(&r4[0], 0, sizeof(r4));
    strcpy(r4,r2);
    const char r5[]="HOST: ";
    strcat(r4,r5);
    const char r6[400]; 
    memset(&r6[0], 0, sizeof(r6));
    strcpy(r6,r4);
    strcat(r6,h);
    const char r7[600];
    memset(&r7[0], 0, sizeof(r7));
    strcpy(r7,r6);
    const char r8 []= "\r\n\r\n";
    strcat(r7,r8);
    const char r9 [700];
    memset(&r9[0], 0, sizeof(r9));
    strcpy(r9,r7);
    printf("%s", r9);
   
  

   //open a connection between the socket and the peer at the eddress of cli_name. return 0 i sucseful, -1 if not.
    if (connect(sock, (struct sockaddr *)&cli_name, sizeof(cli_name)) < 0)
        { perror ("Error establishing communications");
        close(sock);
        exit(1);
        }

    printf("CONNECTED!\n\n\n");

    int n = write(sock,r9,strlen(r9));
    if (n < 0) herror("ERROR writing to socket");
    

    char buffer[2048];
    memset(&buffer[0], 0, sizeof(buffer));
    
    while(1){ 
        int x = read(sock,buffer,2047);
        printf("%s",buffer);
        memset(&buffer[0], 0, sizeof(buffer));
        if (x==0){
            printf("\n\n");
            break;
        }
    }
    

    printf("Exiting now.\n");

    close(sock); // closing the socket
    exit(0);

}