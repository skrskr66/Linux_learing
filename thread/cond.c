//模拟一个skr与cxk使用比赛舞台的Demo
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>

int have_stage = 1;

pthread_cond_t skr;
pthread_cond_t cxk;
pthread_mutex_t mutex;

void* thr_skr(void* arg){//skr此时要上台dancing
  while(1){
    pthread_mutex_lock(&mutex);
    //若此时舞台有人用，那么skr进行等待
    while(have_stage == 1){
      pthread_cond_wait(&skr,&mutex);
    }
    //舞台被人使用了，此时0；因为之前1，代表可以使用
    printf("skr~~ is freestyle!!!\n");
    sleep(1);
    //跳完舞后舞台空了出来
    have_stage += 1;
    //有舞台了，叫cxk来使用
    pthread_cond_signal(&cxk);
    pthread_mutex_unlock(&mutex);
  }
  return NULL;
}

void* thr_cxk(void* arg){
  while(1){
    pthread_mutex_lock(&mutex);
    //没有舞台，那么在这里等待
    while(have_stage == 0){
      pthread_cond_wait(&cxk,&mutex);
    }
    //有了舞台就是可以唱跳rap篮球了。。
    printf("cxk~~ is singing,dancing,playing rapping and basketball!!\n");
    sleep(1);
    have_stage -= 1;
    //跳完还想跳。。因此叫skr快跳完换他跳。。
    pthread_mutex_unlock(&mutex);
    pthread_cond_signal(&skr);
  }
  return NULL;
}

int main(int argc,char * argv[]){
  pthread_t tid1,tid2;
  int ret;

  pthread_cond_init(&skr,NULL);
  pthread_cond_init(&cxk,NULL);
  pthread_mutex_init(&mutex,NULL);
  int i = 0;
  for(i = 0;i < 2;i++){
    ret = pthread_create(&tid1,NULL,thr_skr,NULL);
    if(ret != 0){
      printf("skr error");
      return -1;
    }
  }
  for(i = 0;i < 2; i++){
    ret = pthread_create(&tid2,NULL,thr_cxk,NULL);
    if(ret != 0){
      printf("cxk error");
      return -1;
    }
  }
  pthread_join(tid1,NULL);
  pthread_join(tid2,NULL);

  pthread_cond_destroy(&skr);
  pthread_cond_destroy(&cxk);
  pthread_mutex_destroy(&mutex);
  return 0;
}
