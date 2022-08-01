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
    int count=0;
    char* p= argv[2];
    int srcport = atoi(p);
    int destport = srcport+1;
    printf("port= %d\n", srcport);

    int socket_fd; // creating int var.
    struct sockaddr_in  src, dest; // creatng sockaddr_in structs named src and dest.
    struct hostent *hostptr; // creatig a pointer to a struct hostent named hostptr- ths struct has info abut the host.
    // struct { char head; u_long body; char tail; } msgbuf; // creatng an unamed struct, the stucts var name is msgbuf it contains 2 chars and an unsigned long.
    struct {char head; int body; char tail;} msgbuf;
    
    socket_fd = socket (AF_INET, SOCK_DGRAM, 0); // creating a udp socket. will return socket number, or -1 if there was a problem creating the socket.
    
    
    bzero((char *) &dest, sizeof(dest)); /* They say you must do this */ // changing the memory to '\0' in the struct s_in. before it was all garbage.
    //(starting at the begining of the memory if the struct- its address to the end of the struct -its size).
    
    hostptr = gethostbyname(argv[1]); // hostptr is the second value passed in the when running the main.
    
    dest.sin_family = (short) AF_INET; // initilizing the ip address type of the struct dest.
    bcopy(hostptr->h_addr, (char *)&dest.sin_addr,hostptr->h_length); // initilizing the ip address of the of the struct dest by copying it from hostptr.
    // dest.sin_port = htons((u_short)0x3333); // initilizing the port of the struct dest.
    dest.sin_port = destport;     



    bzero((char *) &src, sizeof(src));
    src.sin_family = AF_INET;
    bcopy(hostptr->h_addr, (char *)&dest.sin_addr,hostptr->h_length);
    src.sin_port =srcport;

    bind(socket_fd, (struct sockaddr *)&src, sizeof(src)); // bindng the socket 
  

    while(1){
        count++;
        msgbuf.head = '<'; // initilizing the head of struct msgbuf.
        // msgbuf.body = htonl(getpid()); /* IMPORTANT! */ //the size of the body is the process id long 
        msgbuf.body=count;
        msgbuf.tail = '>'; // initilizing the tail of struct msgbuf.

        sendto(socket_fd,&msgbuf,sizeof(msgbuf),0,(struct sockaddr *)&dest,sizeof(dest)); //sending the packet to the reciver
        sleep(1);
    }
    return 0;
}



