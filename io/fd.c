#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
int main(){
  int fd = open("./tmp.txt",O_RDWR,0777);
  
  dup2(fd, 1);

  printf("%d\n",fd);
  
  fflush(stdout);
  close(fd);
    
  return 0;
}
