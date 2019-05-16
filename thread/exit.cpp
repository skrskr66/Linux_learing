#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>


void *thr_start(void* argc){
  while(1){
    std::cout<<"child thread-----"<<std::endl;
    sleep(1);
    //pthread_exit((void*)9527);
    pthread_exit(NULL);
  }
  return NULL;
}

int main(int argc , char* argv[]){
  pthread_t tid;
  int ret = pthread_create(&tid,NULL,thr_start,NULL);
  if(ret != 0){
      std::cout<<"thread create error"<<std::endl;
      return -1;
  }
  pthread_cancel(tid);
  while(1){
    std::cout<<"main thread -------"<<std::endl;
    sleep(1);
  }
  return 0;
}
