#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <wait.h>
//之前写过一个关于minishell的文件，先对之前的一些进行封装函数

char buf[1024] = {0};
char *argv[32];
int argc = 0;


void do_face(){
  printf("[liuyucheng@localhost]$ ");
  fflush(stdout);
  memset(buf, 0x00, 1024);
  if(scanf("%[^\n]",buf) != 1){
    getchar();
  }
}

void do_parse(){
  char *ptr = buf;
  argc = 0;
  while(*ptr != '\0'){
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
  return;
}

int main(){
  while(1){
  do_face();
  int redirect = 0;
  char *file = NULL;
  char *ptr = buf;
  while(*ptr != '\0'){
    if(*ptr == '>'){
      redirect = 1;//清空重定向
      *ptr++ = '\0';
      if(*ptr == '>'){
        redirect = 2;
        *ptr++ = '\0';
      }
      while(isspace(*ptr) && *ptr != '\0'){
        ptr++;
      }
      file = ptr;
      while(!isspace(*ptr) && *ptr != '\0'){
        ptr++;
      }
      *ptr = '\0';
    }
    ptr++;
  }
  do_parse();
  int pid = fork();
  if(pid < 0){
    exit(-1);
  }else if(pid == 0){
    if(redirect == 1){
      int fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0664);
      dup2(fd, 1);
    }else if(redirect == 2){
      int fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0664);
      dup2(fd, 1);
    }
    execvp(argv[0], argv);
    exit(0);
  }
  wait(NULL);
  }
  return 0;
}
