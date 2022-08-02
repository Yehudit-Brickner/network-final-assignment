
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



int main(int argc, char *argv[]){
    char* p= argv[2]; //creating a pointer to the string for the third input passed when running the code.
    int srcport2 = atoi(p); // making the srcport number a int
    int destport2 = srcport2+1; // destport val
    
    int socket_fd1, socket_fd2, cc, fsize; // creating  int vars socket_fd1, socket_fd2, cc, fsize.
    struct sockaddr_in  src2, middle2, dest2; // creating 2 sockaddr_in structs named src2, middle2, dest2.
    struct { char head; int  body; char tail;} msg; // creatng an unnamed struct, the structs var name is msg it contains 2 chars and an int.
    struct hostent *hostptr; // creatig a pointer to a struct hostent named hostptr- ths struct has info abut the host.

    // creating a udp sockets. will return socket number, or -1 if there was a problem creating the socket.
    socket_fd1 = socket (AF_INET, SOCK_DGRAM, 0); 
   

    hostptr = gethostbyname(argv[1]); // hostptr is the ip of the second value passed in when running the code.

    bzero((char *) &src2, sizeof(src2));  /* They say you must do this    */ // changing the memory to '\0' in the struct src2. before it was all garbage.
    //(starting at the begining of the memory of the struct- its address, to the end of the struct -its size)
    bzero((char *) &dest2, sizeof(dest2)); // same for struct dest2.


    /* initilizig the 3 parts of the struct src2 and dest2: 
    sin_family= address family- ip typedest
    sin_addr.s_addr= ip address
    sin_port= port number */
    src2.sin_family = (short)AF_INET; 
    bcopy(hostptr->h_addr, (char *)&src2.sin_addr,hostptr->h_length);
    src2.sin_port = srcport2;

    dest2.sin_family = (short)AF_INET; 
    bcopy(hostptr->h_addr, (char *)&dest2.sin_addr,hostptr->h_length);
    dest2.sin_port = destport2;


   
    fflush(stdout); // clears the output stream

    bind(socket_fd1, (struct sockaddr *)&src2, sizeof(src2)); // bindng socket_fd1 to the struct src2
  
 

    for(;;) {// infinte loop
        fsize = sizeof(middle2); // fsize is the size of struct sockaddr_in middle
        cc = recvfrom(socket_fd1,&msg,sizeof(msg),0,(struct sockaddr *)&middle2,&fsize); //recieving the message sent
            float num=((float)random())/((float)RAND_MAX); // creating a float between 0 and 1
            if (num>0.5){ // if the number is bigger than 0.5 
                printf("Relaying data ::%c%d%c\n  i am port %d, recived from port %d, sending to port %d\n",msg.head,msg.body,msg.tail,src2.sin_port, middle2.sin_port, dest2.sin_port); // priniting out the struct msg.
                sendto(socket_fd1,&msg,sizeof(msg),0,(struct sockaddr *)&dest2,sizeof(dest2)); //sending the packet to the sink
            }
       
        fflush(stdout);  // clears the output stream
    }
  
    return 0;
}

