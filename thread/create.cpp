#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

void * thr_start(void *arg){
  while(1){
    std::cout<<"I am child thread-----"<<(char*)arg<<std::endl;
    sleep(1);

  }
  return NULL;
}

int main(int argc, char* argv[]){
  pthread_t tid;

  int ret = pthread_create(&tid,NULL,thr_start,(void*)"I am hujun!");
  
  if(ret != 0){
    std::cout<< "thread create error"<<std::endl;
    return -1;
  }
  sleep(5);
  pthread_cancel(tid);
  while(1){
    std::cout<<"I am main thread "<< &tid << std::endl;
    sleep(1);
  }
  return 0;
}
