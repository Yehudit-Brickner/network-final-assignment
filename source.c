#include <sys/types.h>
#include <netinet/in.h>
#include <inttypes.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <strings.h>
#include <unistd.h>

#include <stdio.h>  
#include <net/ethernet.h>      // ethernet header
#include <string.h>
#include <arpa/inet.h>




int main(int argc, char *argv[]){
    int count=0; // the number of the message sent
    char* p= argv[2]; //creating a pointer to the string for the third input passed when running the problem.
    int srcport1 = atoi(p); // making the srcport number a int
    int destport1 = srcport1+1; // destport val
    int socket_fd; // creating int var.
    struct sockaddr_in  src1, dest1; // creatng sockaddr_in structs named src and dest.
    struct hostent *hostptr; // creatig a pointer to a struct hostent named hostptr- ths struct has info abut the host.
    struct {char head; int body; char tail;} msgbuf; // creatng an unnamed struct, the stucts var name is msgbuf it contains 2 chars and an int.
    
    socket_fd = socket (AF_INET, SOCK_DGRAM, 0); // creating a udp socket. will return socket number, or -1 if there was a problem creating the socket.
    hostptr = gethostbyname(argv[1]); // hostptr is the second value passed in when running the poblem.
    
    bzero((char *) &dest1, sizeof(dest1)); /* They say you must do this */ // changing the memory to '\0' in the struct s_in. before it was all garbage.
    //(starting at the begining of the memory if the struct- its address to the end of the struct -its size).
    bzero((char *) &src1, sizeof(src1)); 
    
    
    dest1.sin_family = (short) AF_INET; // initilizing the ip address type of the struct dest1.
    bcopy(hostptr->h_addr, (char *)&dest1.sin_addr,hostptr->h_length); // initilizing the ip address of the of the struct dest1 by copying it from hostptr.
    dest1.sin_port = destport1;  // initilizing the port of the struct dest1 with the port number destport1.   


  
    src1.sin_family = AF_INET; // initilizing the ip address type of the struct src1.
    bcopy(hostptr->h_addr, (char *)&src1.sin_addr,hostptr->h_length); // initilizing the ip address of the of the struct dest1 by copying it from hostptr.
    src1.sin_port =srcport1; // initilizing the port of the struct src1 with the port number srcport1.

    bind(socket_fd, (struct sockaddr *)&src1, sizeof(src1)); // bindng the socket to the struct src1
  

    while(1){ // infinite loop 
        count++; // incrimanting the int count so that each message has the next number as the body
        msgbuf.head = '<'; // initilizing the head of struct msgbuf.
        msgbuf.body=count;
        msgbuf.tail = '>'; // initilizing the tail of struct msgbuf.
        sendto(socket_fd,&msgbuf,sizeof(msgbuf),0,(struct sockaddr *)&dest1,sizeof(dest1)); //sending the packet to the gateway
        sleep(2); // having the program sleep for 1 sec. 
    }
    return 0;
}



