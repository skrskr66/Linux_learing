#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int main(){
  //printf("hello world\n");
  //execl("./env","env","-l",NULL);//谁调用就对谁进行程序替换
  char *env[32];
  env[0] = "MYENV=10000";
  env[1] = NULL;
  extern char **environ;//保存环境变量
  execle("./env","env","-l",NULL,environ);
  printf("hello world~~\n");
  return 0;

}
