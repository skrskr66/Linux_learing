/*===============================================================
 * *   Copyright (C) 2019 All rights reserved.
 * *   
 * *   文件名称：sem.cpp
 * *   创 建 者：herb
 * *   创建日期：2019年05月29日
 * *   描    述：实现线程安全的环形队列 （线性表实现的环形队列）
 * *  使用信号量实现队列操作的同步与互斥
 * ================================================================*/

#include <iostream>
#include <vector>
#include <pthread.h>
#include <semaphore.h>

using namespace std;

class RingQueue
{
public:
  RingQueue(int cap = 5)
     :_queue(5)
     ,_capacity(cap)
     ,_write_step(0)
     ,_read_step(0)
  {
   sem_init(&_sem_data,0,0);
   sem_init(&_sem_lock,0,0);
   sem_init(&_sem_idle,0,cap);
  }
  ~RingQueue()
  {
    sem_destroy(&_sem_data);
    sem_destroy(&_sem_idle);
    sem_destroy(&_sem_lock);
  }
  bool QueuePush(int data)
  {
    ProductWait();
    QueueLock();
    _queue[_write_step] = data;
    _write_step = (_write_step + 1) % _capacity;
    QueueUnLock();
    ConsumerWakeUp();
    return true;
  }
  bool QueuePop(int *data)
  {
    ConsumerWait();
    QueueLock();
    *data = _queue[_read_step];
    _read_step = (_read_step + 1) % _capacity;
    QueueUnLock();
    ProductWakeUp();
    return true;
  } 
private:
  void QueueLock()//加锁
  {
    sem_wait(&_sem_lock);
  }
  void QueueUnLock()//解锁
  {
    sem_post(&_sem_lock);
  }
  void ProductWait()//生产者等待
  {
    sem_wait(&_sem_idle);
  }
  void ProductWakeUp()//生产者唤醒
  {
    sem_post(&_sem_idle);
  }
  void ConsumerWait()//消费者等待
  {
    sem_wait(&_sem_data);
  }
  void ConsumerWakeUp()//消费者唤醒
  {
    sem_post(&_sem_data);
  }
private:
  vector<int> _queue;
  int _capacity;
  int _write_step;
  int _read_step;
  sem_t _sem_data;//数据资源计数
  sem_t _sem_idle;//空闲空间计数
  sem_t _sem_lock;//实现互斥
};

void *thr_consumer(void *arg)
{
  RingQueue *q = (RingQueue*)arg;
  while(1)
  {
    int data;
    q->QueuePop(&data);
    cout<<"consumer thread get data:"<<data<<endl;
  }
  return NULL;
}

void *thr_productor(void *arg)
{
  RingQueue *q = (RingQueue*)arg;
  int i =0;
  while(1)
  {
    q->QueuePush(i);
    cout<<"productor thread get data"<<i<<endl;
    i++;
  }
  return NULL;
}
int main(int argc,char* argv[])
{
  pthread_t ctid[4],ptid[4];
  int ret,i;
  RingQueue q;

  for(i = 0;i<4;i++)
  {
    ret = pthread_create(&ctid[i],NULL,thr_consumer,(void*)&q);
    if(ret != 0)
    {
      cout<<"thread create error"<<endl;
      return -1;
    }
  }

  for(i = 0;i<4;i++)
  {
   ret = pthread_create(&ptid[i],NULL,thr_productor,(void*)&q);
   if(ret != 0)
   {
     cout<<"thread create error"<<endl;
     return -1;
   }
  }
  for(i=0;i<4;i++)
  {
    pthread_join(ctid[i],NULL);
  }
  for(i=0;i<4;i++)
  {
    pthread_join(ptid[i],NULL);
  }
}
