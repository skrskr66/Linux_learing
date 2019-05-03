#include <stdio.h>
#include <unistd.h>
#include <signal.h>
void sigcb(int signo){
  printf("---------\n");
}

int main(){
  //int kill(pid_t pid,int sig);
  //给指定进程发送指定信号
  //kill(getpid(), SIGSEGV);//sig为可靠/非可靠信号的62种
  
  //int raise(int sig);
  //给调用进程/线程发送指定信号
  //raise(SIGQUIT);
  //abort();
  //通常由于库函数检测到内部错误或者某些限制。比如，当堆栈溢出导致内存被破坏，此时malloc()的话会调用abort()
  
  //unsigned int alarm(unsigned int seconds);
  //seconds秒之后给调用进程发送SIGALRM信号
  //seconds==0表示取消定时器
  //返回值上一个定时器剩余的时间或0
  //int ret = alarm(3);
  //sleep(1);
  //ret = alarm(0);
  signal(SIGINT, sigcb);
  while(1){
    printf("hello ~~~\n");
    sleep(2);
  }
  return 0;
}
