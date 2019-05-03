#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>

int main(){
  int pipefd[2];
  int ret = pipe(pipefd);
  if(ret < 0){
    perror("pipe error");
    return -1;
  }
  int pid = fork();
  if(pid < 0){
    perror("fork error");
    return -1;
  }else if(pid == 0){
    close(pipefd[1]);
  }else{
    sleep(1);
    close(pipefd[1]);
    char buf[1024] = {0};
    int ret = read(pipefd[0], buf, 1023);
    printf("read buf:[%d - %s]\n",ret, buf);
  }
  return 0;
}
