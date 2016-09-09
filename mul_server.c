#include <stdio.h>
#include <stdlib.h>

#include <netdb.h>
#include <netinet/in.h>

#include <string.h>
#define MAX 1024
void doprocessing (int sock);

int main( int argc, char *argv[] ) {
   int sockfd, newsockfd, portno, clilen;
   char buffer[256];
   struct sockaddr_in serv_addr, cli_addr;
   int n, pid;
   
   /* First call to socket() function */
   sockfd = socket(AF_INET, SOCK_STREAM, 0);
   printf("\nI am the first call%d\n",sockfd);
   if (sockfd < 0) {
      perror("ERROR opening socket");
      exit(1);
   }
   
   /* Initialize socket structure */
   bzero((char *) &serv_addr, sizeof(serv_addr));
   portno = 5001;
   
   serv_addr.sin_family = AF_INET;
   serv_addr.sin_addr.s_addr = INADDR_ANY;
   serv_addr.sin_port = htons(portno);
   
   /* Now bind the host address using bind() call.*/
   if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
      perror("ERROR on binding");
      exit(1);
   }
   
   /* Now start listening for the clients, here
      * process will go in sleep mode and will wait
      * for the incoming connection
   */
   
   listen(sockfd,5);
   clilen = sizeof(cli_addr);
   
   while (1) {
      newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
      printf("\nI am in while loop%d\n",newsockfd);

      if (newsockfd < 0) {
         perror("ERROR on accept");
         exit(1);
      }
      
      /* Create child process */
      pid = fork();
		
      if (pid < 0) {
         perror("ERROR on fork");
         exit(1);
      }
      
      if (pid == 0) {
         /* This is the client process */
        close(sockfd);
         printf("I have pid:%d",getpid());
         doprocessing(newsockfd);
         exit(0);
      }
      else {
         
         close(newsockfd);
      }
		
   } /* end of while */
}


 void doprocessing(int sockfd)
{
  char buff[MAX];
  int n;
  for(;;)
{
  bzero(buff,MAX);
  read(sockfd,buff,sizeof(buff));
  printf("From client: %s\t To client : ",buff);
  bzero(buff,MAX);
  n=0;
  while((buff[n++]=getchar())!='\n');
  write(sockfd,buff,sizeof(buff));
if(strncmp("exit",buff,4)==0)
{
  printf("Server Exit...\n");
  break;
}
}
}
