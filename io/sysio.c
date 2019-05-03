#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
int main(){
  
  //mode_t umask
  //修改调用进程的文件创建权限掩码
  umask(0);
  int fd = open("./tmp.txt",O_RDWR | O_CREAT | O_APPEND,0777);
  if(fd < 0){
    perror("open error");
    return -1;
  }
  char buf[1024] = "nihaoa~~!!";
  int ret = write(fd, buf, strlen(buf));
  if(ret < 0){
    perror("write error");
    return -1;
  }
  lseek(fd, 0, SEEK_SET);

  memset(buf, 0x00, 1024);//对buf数组所在的内存空间全部初始化为0，初始化的长度为1024
  ret = read(fd, buf, 1023);
  if(ret < 0){
    perror("read error");
    return -1;
  }
  printf("read buf:[%s]\n", buf);
  close(fd);
  return 0;
}
