#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

int main(){
  char *file = "./test.fifo";
  umask(0);
  int ret = mkfifo(file, 0664);
  if(ret < 0){
      if(errno != EEXIST){// EEXIST是文件存在的意思 errno != EEXIST，也就是判断mkfifo函数是否出现“已存在同名管道”的错。
        perror("mkfifo error");
        return -1;
      }
  }
  printf("open file\n");
  int fd = open(file, O_WRONLY);
  if(fd < 0){
    perror("open error");
    return -1;
  }
  printf("open success!!\n");
  while(1){
    char buf[1024] = {0};
    scanf("%s", buf);
    write(fd, buf, strlen(buf));
  }
  return 0;
}
