#include<stdio.h>
#include<sys/types.h>
#include<string.h>    //strlen
#include<sys/socket.h>
#include<arpa/inet.h> //inet_addr
#include<unistd.h>    //write   
#define MAX 1024

 void func(int sockfd)
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

int main(int argc , char *argv[])
{   
    int socket_desc , client_sock , c , read_size,val;
    struct sockaddr_in server , client;
    char buff[1024];

    //Create socket
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1)
    {
        printf("Could not create socket");
    }
    puts("Socket created");

    //Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons( 9999 );

    //Bind
    if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
    {
        //print the error message
        perror("bind failed. Error");
        return 1;
    }
    puts("bind done");

    //Listen
    listen(socket_desc , 3);

    //Accept and incoming connection
    puts("Waiting for incoming connections...");
    c = sizeof(struct sockaddr_in);

    //accept connection from an incoming client
    client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);

    send(client_sock, "1", 1, 0);
    if (client_sock < 0)
    {
        perror("accept failed");
        return 1;
    }
    else
    {puts("Connection accepted");
       
      memset(buff,0,sizeof(buff));
      /*    if((val=recv(client_sock,buff,sizeof(buff),0))<0)
              {
                printf("\nerror while reading stream message from client..\n\n");
                }
           else if(val==0)
               {
                 printf("\nending connection..\n\n");
                 }
            else
               {

                  printf("\nmessage:%s\n",buff);/*recieved message*/
              /*}*/
                /*printf("\nmessage recieved successfully..(val=%d)\n\n",val);*/

                func(client_sock);

    }
    close(client_sock);
    close(socket_desc);

}
