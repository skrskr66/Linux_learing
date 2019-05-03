#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>
int main()
{
  int pid = fork();
  if (pid < 0) {
    perror("fork error");
    exit(-1);

  }else if (pid == 0) {
    sleep(5);
    exit(255);
  }
  int Stauts;
  //while(wait(&Stauts) == 65280){
  //    printf("nihaoa\n"); 
  //}
  while(waitpid(pid, &Stauts, WNOHANG)==0){
    printf("no exit~~~ smoking\n");
    sleep(1);
  }
  //低7位则为正常退出
  if(!(Stauts & 0x7f)){
    printf("exut code:%d\n",(Stauts >> 8) &0xff);
  }
  if(WIFEXITED(Stauts)){
    printf("child exit code:%d",WIFEXITED(Stauts));
  }
  if(WIFSIGNALED(Stauts)){
    printf("exit signal:%d\n",WIFEXITED(Stauts));
  }
  while(1){
    printf("打麻将\n");
    sleep(1);
  }
}
