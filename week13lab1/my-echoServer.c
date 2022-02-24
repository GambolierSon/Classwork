#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

#define MAXLINE 4096 /*max text line length*/
#define SERV_PORT 46461 /*my port*/
#define LISTENQ 8 /*maximum number of client connections */

int main (int argc, char **argv)
{
 printf("\n\n ** my-echoServer is running on port 46461 ** \n\n ** netid: arm190020 ** \n\n");
 system("date; hostname; whoami; ls *");
 int listenfd, connfd, n, i;
 socklen_t clilen;
 char buf[MAXLINE];
 struct sockaddr_in cliaddr, servaddr;
	
 //creation of the socket
 listenfd = socket (AF_INET, SOCK_STREAM, 0);
	
 //preparation of the socket address 
 servaddr.sin_family = AF_INET;
 servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
 servaddr.sin_port = htons(SERV_PORT);
	
 bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
	
 listen(listenfd, LISTENQ);
	
 printf("%s\n","Server running...waiting for connections.");
	
 for ( ; ; ) {

  clilen = sizeof(cliaddr);
  //accept a connection
  connfd = accept (listenfd, (struct sockaddr *) &cliaddr, &clilen);

  printf("%s\n","Received request...");

  int childpid;

  if ( (childpid = fork()) == 0 ) {//Make a child do it. That's kinda f'ed

    printf ("%s\n","Child created for dealing with client requests");

    //close listening socket
    close (listenfd);

    while ( (n = recv(connfd, buf, MAXLINE,0)) > 0)  {
     if(buf[0] == 'e'){
       if(buf[1] == 'x'){
         if(buf[2] == 'i'){
           if(buf[3] == 't'){
             printf("Client exited. This child will now end.\n\n");
             exit(0);
           }
         }
       }
     }
    
     printf("%s","String received from and resent to the client:");
     puts(buf);
     send(connfd, buf, n, 0);
     i = 0;
     while(buf[i] != 0){
       buf[i] = 0;
       i = i + 1;
     } 
    }

    if (n < 0)
      printf("%s\n", "Read error");
    exit(0);
  }
  //close socket of the server
  close(connfd);
 } 
}
