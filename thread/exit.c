#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>

void *thr_start(void *arg){
while(1){  
printf("child thread----\n");
sleep(1);
pthread_exit(NULL);
}  
return NULL;  
}

int main(int argc , char *argv[]){
  pthread_t tid;
  int ret = pthread_create(&tid, NULL, thr_start,NULL);
  if(ret != 0){
    printf("thread create error\n");
    return -1;
  }
  //使指定的线程退出tid == thread
  pthread_cancel(tid);
  while(1){
    printf("main thread -------\n");
    sleep(1);
  }
  return 0;
}
