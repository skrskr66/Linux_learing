/*匿名管道模拟实现
 * 将一个命令的输出结果作为下一个命令的输入进行处理
 * ps -el     输出：所有的进程信息--写入标准输出
 * grep ssh   从标准输入读取数据，进行过滤处理*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <wait.h>
int main(){
  int pipefd[2];
  int ret = pipe(pipefd);
  if(ret < 0){
    perror("pipe error");
    return -1;
  }
  int pid1 = fork();
  if(pid1 == 0){
    close(pipefd[0]);//关闭从管道读数据
    dup2(pipefd[1],1);//将文件描述符表中 向管道写数据 替换 标准输出
    execlp("ps","ps","-ef",NULL);//程序替换
  }
  int pid2 = fork();
  if(pid2 == 0){
    close(pipefd[1]);
    dup2(pipefd[0],0);
    execlp("grep","grep","ssh",NULL);
  }
  close(pipefd[0]);//不用的时候将读端和写端都关闭
  close(pipefd[1]);
  waitpid(pid1,NULL,0);
  waitpid(pid2,NULL,0);
  return 0;
}
