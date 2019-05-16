#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>

void *thr_start(void *arg){
sleep(3);
return (void*)"hihao~~~~";  
}

int main(){
  pthread_t tid;
  int ret = pthread_create(&tid,NULL,thr_start,NULL);
  if(ret != 0){
    perror("thread create error\n");
    return -1;
  }
  char **ptr = NULL;
  pthread_join(tid,(void**)&ptr);
  printf("retval:%s\n",ptr);
  return 0;
}
