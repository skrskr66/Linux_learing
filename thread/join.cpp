#include <iostream>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
using std::cout;
using std::endl;

extern void *thr_start(void* arg){
  pthread_detach(pthread_self());
  pthread_exit((void*)"leihou");
  while(1){
    cout<<"i am thread"<<endl;
    sleep(1);
  }
  return NULL;
}

int main(int argc, char* argv[]){
  pthread_t tid;
  int ret = pthread_create(&tid, NULL, thr_start, NULL);
  if(ret != 0){
    cout<<"pthread create error"<<endl;
    return -1;
  }
  sleep(1);
  char* retval = NULL;
  int err = pthread_join(tid,(void**)&retval);
  if(err == EINVAL){
    cout<<"thread can not be waited"<<endl;
  }
  //cout<<retval<<endl;
  printf("retval:%s\n",retval);
  while(1){
    cout<<"i am main thread"<<endl;
    sleep(1);
  }
  return 0;
}

