#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#define MAX 1024
#define DATA "socket programming using TCP"

 void func(int sockfd)
{
char buff[MAX];
int n;
for(;;)
{
 bzero(buff,sizeof(buff));
 printf("Enter the string : ");
 n=0;
 while((buff[n++]=getchar())!='\n');
  write(sockfd,buff,sizeof(buff));
  bzero(buff,sizeof(buff));
  read(sockfd,buff,sizeof(buff));
  printf("From Server : %s",buff);
if((strncmp(buff,"exit",4))==0)
{
 printf("Client Exit...\n");
 break;
}
}
}
int main(int argc,char *argv[])
{
  int sock;
  struct sockaddr_in server;
  char buff[MAX];
  struct hostent *hp;
  sock=socket(AF_INET,SOCK_STREAM,0);
    
  if(sock< 0)
  { 
   printf("socket failed\n");
   exit(1);
  }
  
  server.sin_family = AF_INET;
  
  hp=gethostbyname(argv[1]);
 
   if(hp==0)
   {
    printf("\ngethostbyname failed...\n");
    close(sock);   
    exit(1);
   }  
 
  memcpy(&server.sin_addr,hp->h_addr,hp->h_length);

  server.sin_port=htons(5001);
 

  if(connect(sock, (struct sockaddr *) &server,sizeof(server)) < 0)
  {
   printf("\nconnect failed...\n");
   close(sock);  
   exit(1);
  }
  
 /* if(send(sock,DATA,sizeof(DATA), 0) < 0)
  {
   printf("send failed...\n");
   close(sock);
  }
  printf("sent %s",DATA);*/
 func(sock);
  close(sock);
 return 0;
}
 
