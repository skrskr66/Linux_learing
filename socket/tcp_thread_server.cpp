#include <pthread.h>
#include "tcpsocket.hpp"

void *thr_start(void *arg)
{
  TcpSocket *sock = (TcpSocket*)arg;
  while(1)
  {
    string buf;
    sock->Recv(buf);
    printf("client say:%s\n",buf.c_str());

    buf.clear();
    printf("server say:\n");
    fflush(stdout);
    cin>>buf;
    sock->Send(buf);
  }
  sock->Close();
  delete sock;
  return NULL;
}

int main(int argc,char* argv[])
{
  if(argc != 3)
  {
    printf("./tcp_server ip port");
  }
  string ip = argv[1];
  uint16_t port = atoi(argv[2]);
  
  TcpSocket sock;
  CHECK_RET(sock.Socket());
  CHECK_RET(sock.Bind(ip,port));
  CHECK_RET(sock.Listen());

  while(1)
  {
    TcpSocket *clisock = new TcpSocket();
    struct sockaddr_in cliaddr;

    if(sock.Accept(*clisock,&cliaddr) == false)
    {
      continue;
    }
    printf("new connect client %s:%d",inet_ntoa(cliaddr.sin_addr),ntohs(cliaddr.sin_port));

    pthread_t tid;
    pthread_create(&tid,NULL,thr_start,(void*)clisock);
    pthread_detach(tid);
    //多线程中，主线程不能关闭socket，因为线程之间共享文件描述符
    //如果在主线程中的描述符关闭了，那么其他线程的描述符也就关闭了
  }
  sock.Close();
  return 0;
}
