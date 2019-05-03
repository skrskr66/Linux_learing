#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

struct sigaction act,  oldact;

void sigcb(int signo){
  printf("revc signo:%d\n", signo);
  sigaction(signo, &oldact, NULL);
}

int main(){
  act.sa_handler = sigcb;
  act.sa_flags = 0;

  sigemptyset(&act.sa_mask);
  sigaction(SIGINT, &act, &oldact);

  while(1){
    printf("---------\n");
    sleep(2);
  }
  return 0;
}
