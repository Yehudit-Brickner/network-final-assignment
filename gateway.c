// get packets fro port p


// random number decides if to sendo or not


// if should send sends to sink



#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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





void printsin(struct sockaddr_in *s, char *str1, char *str2) {
    printf("%s\n", str1);
    printf("%s: ", str2);
    // -- IP: sin->sin_addr (IP in dotted-decimal notation) 
    printf("--IP: %s ", inet_ntoa(s->sin_addr));
    //-- port: sin->sin_port (host integer type) 
    printf("-- port: %d ", s->sin_port);
    printf("\n");
}

int main(int argc, char *argv[]){
 
    int socket_fd1, socket_fd2, cc, fsize; // creating  int vars socket_fd, cc, fsize.
    struct sockaddr_in  s_in, from, to; // creating 2 sockaddr_in structs named s_in, from.
    struct { char head; int  body; char tail;} msg; // creatng an unamed struct, the stucts var name is msg it contains 2 chars and an unsigned long.

    socket_fd1 = socket (AF_INET, SOCK_DGRAM, 0); // creating a udp socket. will return socket number, or -1 if there was a problem creating the socket.
    
    bzero((char *) &s_in, sizeof(s_in));  /* They say you must do this    */ // changing the memory to '\0' in the struct s_in. before it was all garbage.
    //(starting at the begining f the emory if the struct- its address to the end of the struct -its size)

    /* initilizig the 3 parts of the struct s_in: 
    sin_family= address family- ip type
    sin_addr.s_addr= ip address
    sin_port= port number */
    s_in.sin_family = (short)AF_INET; 
    s_in.sin_addr.s_addr = htonl(INADDR_ANY);    /* WILDCARD */ 
    s_in.sin_port = htons((u_short)0x3333); 
    // s_in.sin_port = (1001);


   
    to.sin_family = (short)AF_INET; 
    to.sin_addr.s_addr = htonl(INADDR_ANY);    /* WILDCARD */ 
    to.sin_port = htons((u_short)0x3333);

    printsin( &s_in, "RECV_UDP", "Local socket is:"); 
    printf("\n");
    fflush(stdout); // clears the output stream

    bind(socket_fd1, (struct sockaddr *)&s_in, sizeof(s_in)); // bindng the socket 


    bzero((char *) &to, sizeof(to));
    to.sin_family = (short)AF_INET; 
    to.sin_addr.s_addr = htonl(INADDR_ANY);    /* WILDCARD */ 
    to.sin_port = htons((u_short)0x3333);
    bind(socket_fd, (struct sockaddr *)&to, sizeof(to)); // bindng the socket 

    for(;;) {// infinte loop
        printf("\n");
        printf("waiting to recieve a packet\n");
        float num=((float)random())/((float)RAND_MAX);
        // num=num/((float)300000);
        printf("num = %f",num);
        fsize = sizeof(from); // fsize is the size of struct sockaddr_in from
        cc = recvfrom(socket_fd,&msg,sizeof(msg),0,(struct sockaddr *)&from,&fsize); //recieving the message sent
        if (num>0.5){
        // sendto(socket_fd,&msg,sizeof(msg),0,(struct sockaddr *)&to,sizeof(to)); //sending the packet to the reciver
            printsin( &from, "recv_udp: ", "Packet from:"); // printing the message sent, the ip, and the port.
            printf("Got data ::%c%d%c\n",msg.head,msg.body,msg.tail); // priniting out the struct msg.
        }
        fflush(stdout); // clears the output stream
    }
  
    return 0;
}
