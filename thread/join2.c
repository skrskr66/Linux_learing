#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

void *thr_start(void *arg)
{
  pthread_detach(pthread_self());
  pthread_exit((void*)"leihou");
  while(1) {
    printf("i am thread!!\n");
    sleep(1);

  }
  return NULL;

}
int main(int argc, char *argv[])
{
  pthread_t tid;

  int ret = pthread_create(&tid, NULL, thr_start, NULL);
  if (ret != 0) {
    printf("thread create error\n");
    return -1;

  }

  sleep(1);
  char *retval = NULL;
  int err = pthread_join(tid, (void**)&retval);
  if (err == EINVAL) {
    printf("thread can not be waited\n");

  }
  printf("retval:%s\n", retval);
  while(1) {
    printf("i am main thread\n");
    sleep(1);

  }
  return 0;

}

