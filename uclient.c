#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


char *socket_path = NULL;

int main(int argc, char *argv[]) {
  struct sockaddr_un addr;
  char buf[100];
  int val,rc;

  if (argc > 1) socket_path=argv[1];
   printf("socket path:%s",argv[1]);
  
 if ( (val = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) 
  {
    printf("socket creation failed..\n\n");
    exit(1);
  }

  /*memset(&addr, 0, sizeof(addr));*/
  
  addr.sun_family = AF_UNIX;/*specifying the usage of unix socket domain*/  
  if (*socket_path == '\0') 
 {   
    printf("socket path not specified..\n\n");
 } 
 else 
  {
    strncpy(addr.sun_path, socket_path, sizeof(addr.sun_path)-1);/*copying socket path to structure variable*/
  }

  if (connect(val, (struct sockaddr*)&addr, sizeof(addr)) == -1) 
  {
    printf("connect error");
    exit(-1);
  }

  while( (rc=read(STDIN_FILENO, buf, sizeof(buf))) > 0) /*readign from statndard input*/
  {
    if (write(val, buf, rc) != rc) 
    {
      if (rc > 0) 
            printf(stderr,"partial write");
      else {
            printf("write error");
            exit(1);
           }
    } 
 }

  return 0;
}
