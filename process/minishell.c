#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <ctype.h>
int main(){
  while(1){
    printf("[liuyucheng@localhost]$ ");
    fflush(stdout);
    char buf[1024] = {0};
    if(scanf("%[^\n]%*c", buf) != 1){
      getchar();
      continue;
    }
    //取出空白字符，获取程序名称和参数
    char *argv[32];//将自己定义的缓冲区的字符放入该数组中
    int argc = 0;
    char *ptr = buf;
    while(*ptr != '\0'){
      //若参数c为空格字符，则返回TRUE，否则返回NULL(0)。
      if(!isspace(*ptr)){
        argv[argc++] = ptr;
        while(!isspace(*ptr) && *ptr != '\0'){
          ptr++;
        }
      }else{
        *ptr = '\0';
        ptr++;
      }
    }
    argv[argc] = NULL;

  int pid = fork();
  //创建子进程
  if(pid < 0){
    exit(-1);//退出返回-1
  }
  else if(pid == 0){//如果子进程创建成功
    execvp(argv[0], argv);//程序替换
    exit(0);
  }
  wait(NULL);
  }
  return 0;
}
