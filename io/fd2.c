
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
int main(){
  int fd;
  int refd;
  char *buf="Advanced Programming!\n";
  fd = open("test.txt",O_RDWR|O_CREAT,0644);
  if(fd==-1)
  {
    printf("open file error:%m\n");
    exit(-1);
  }
  refd = dup2(fd,fileno(stdout));
  if(refd==-1)
  {
    printf("redirect standard out error:%m\n");
    exit(-1);
  }

  printf("dup2的返回值：%d\n",refd);
  write(fileno(stdout),buf,strlen(buf));
  close(fd);
  exit(0);
  return 0;
}
