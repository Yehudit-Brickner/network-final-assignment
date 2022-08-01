

#include <sys/types.h>
#include <netinet/in.h>
#include <inttypes.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <strings.h>
#include <unistd.h>
#include <stdio.h>




int main(int argc, char *argv[]){
 
    char* p= argv[1]; //creating a pointer to the string for the second input passed when running the problem.
    int srcport = atoi(p); // making the srcport number a int
   

    int socket_fd, cc, fsize; // creating  int vars socket_fd, cc, fsize.
    struct sockaddr_in  s_in, from; // creating 2 sockaddr_in structs named s_in, from.
    struct { char head; int  body; char tail;} msg; // creatng an unamed struct, the stucts var name is msg it contains 2 chars and an unsigned long.

    socket_fd = socket (AF_INET, SOCK_DGRAM, 0); // creating a udp socket. will return socket number, or -1 if there was a problem creating the socket.
    
    bzero((char *) &s_in, sizeof(s_in));  /* They say you must do this    */ // changing the memory to '\0' in the struct s_in. before it was all garbage.
    //(starting at the begining f the emory if the struct- its address to the end of the struct -its size)

    /* initilizig the 3 parts of the struct s_in: 
    sin_family= address family- ip type
    sin_addr.s_addr= ip address
    sin_port= port number */
    s_in.sin_family = (short)AF_INET; 
    s_in.sin_addr.s_addr = htonl(INADDR_ANY);    /* WILDCARD */ 
    s_in.sin_port = srcport;


    
    fflush(stdout); // clears the output stream

    bind(socket_fd, (struct sockaddr *)&s_in, sizeof(s_in)); // bindng the socket 

    for(;;) {// infinte loop
        fsize = sizeof(from); // fsize is the size of struct sockaddr_in from
        cc = recvfrom(socket_fd,&msg,sizeof(msg),0,(struct sockaddr *)&from,&fsize); //recieving the message sent
        printf("Got data ::%c%d%c\n i am port %d, recived from port %d\n",msg.head,msg.body,msg.tail,s_in.sin_port, from.sin_port);; // priniting out the struct msg.
        fflush(stdout); // clears the output stream
    }
  
    return 0;
}

