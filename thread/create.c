#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
void *thr_start(void *arg){
  pthread_t tid = pthread_self();
  while(1){
    printf("i am child----%s-%p\n",arg,tid);
    sleep(1);
  }
  return 0;
}

int main(int argc, char *agrv[]){
  pthread_t tid;
  int ret = pthread_create(&tid, NULL, thr_start, (void*)"nihao");
  if(ret != 0){
    printf("thread error\n");
    return -1;
  }
  printf("线程 tid-%p\n",tid);
  while(1){
    printf("hello world~~~\n");
    sleep(1);
  }
  return 0;
}
