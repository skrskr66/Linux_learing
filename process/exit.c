#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int main(){
  int pid = fork();
  if(pid < 0){
    perror("fork error");
    printf("fork error:%s\n",strerror(errno));
  }
  int i = 0;
  for( ;i < 256; i++){
    printf("errno:[%s]\n",strerror(i));
  }
  printf("hello bit");
  sleep(1);
  _exit(257);
}
