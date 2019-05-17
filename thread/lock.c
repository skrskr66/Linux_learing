#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

int ticket = 100;
pthread_mutex_t mutex;// = PTHREAD_MUTEX_INITIALIZER;//定义初始化锁

void* thr_start(void* arg){
  while(1){
    pthread_mutex_lock(&mutex);
    if(ticket > 0){
      usleep(1000);
      printf("yellow bull:%d----get ticket:%d\n",arg,ticket);
      ticket--;
    }else{
      pthread_mutex_unlock(&mutex);
      pthread_exit(NULL);

    }
    pthread_mutex_unlock(&mutex);
  }
  return NULL;
}

int main(int argc, char* argv[]){
  pthread_t tid[4];
  int i = 0,ret;

  pthread_mutex_init(&mutex,NULL);
  for(i = 0;i < 4; i++){
    ret = pthread_create(&tid[i],NULL,thr_start,(void*)i);
    if(ret != 0){
      printf("yellow bull no exit!");
      return -1;
    }
  }
  for(i = 0;i < 4;i++){
    pthread_join(tid[i],NULL);
  }
  pthread_mutex_destroy(&mutex);
  return 0;
}
