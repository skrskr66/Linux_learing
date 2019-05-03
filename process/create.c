#include <stdio.h>
#include <unistd.h>
int main(){
  printf("parent pid:%d\n",getpid());
  int a = 100;
  pid_t pid = fork();
  if(pid < 0){
    return -1;
  }else if(pid == 0){
    a = 20;
    printf("child !! pid:%d----a:%d--%p\n",getpid(),a ,&a);

  }else{
    sleep(15);
    printf("parent !! pid:%d----a:%d--%p\n",getpid(), a, &a);
  }
  printf("nihaoa %d\n",a);
  return 0;
}
