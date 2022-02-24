#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>


#define MAXLINE 4096 /*max text line length*/
#define SERV_PORT 46461 /*port*/

int
main(int argc, char **argv) 
{
 int sockfd, i;
 struct sockaddr_in servaddr;
 char *sendline = (char *)malloc(MAXLINE);
 char *recvline = (char *)malloc(MAXLINE);	
 
 //basic check of the arguments
 //additional checks can be inserted
 if (argc !=2) {
  perror("Usage: TCPClient <IP address of the server"); 
  exit(1);
 }
	
 //Create a socket for the client
 //If sockfd<0 there was an error in the creation of the socket
 if ((sockfd = socket (AF_INET, SOCK_STREAM, 0)) <0) {
  perror("Problem in creating the socket");
  exit(2);
 }
	
 //Creation of the socket
 memset(&servaddr, 0, sizeof(servaddr));
 servaddr.sin_family = AF_INET;
 servaddr.sin_addr.s_addr= inet_addr(argv[1]);
 servaddr.sin_port =  htons(SERV_PORT); //convert to big-endian order
	
 //Connection of the client to the socket 
 if (connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr))<0) {
  perror("Problem in connecting to the server");
  exit(3);
 }
	
 while (fgets(sendline, MAXLINE, stdin) != NULL) {
	
  send(sockfd, sendline, strlen(sendline), 0);
  
  if(sendline[0] == 'e'){
    if(sendline[1] == 'x'){
      if(sendline[2] == 'i'){
        if(sendline[3] == 't'){
          printf("Client, me, exited.\n\n");
          exit(0);
        }
      }
    }
  }
		
  if (recv(sockfd, recvline, MAXLINE,0) == 0){
   //error: server terminated prematurely
   perror("The server terminated prematurely"); 
   exit(4);
  }
  printf("%s", "String received from the server: ");
  fputs(recvline, stdout);
  i = 0;
  while(sendline[i] != 0){
    sendline[i] = 0;
    i = i + 1;
  }
  i = 0;
  while(recvline[i] != 0){
    recvline[i] = 0;
    i = i + 1;
  }
 }

 exit(0);
}
