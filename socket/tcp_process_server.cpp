#include "tcpsocket.hpp"
#include <signal.h>
#include <sys/wait.h>

void sigcb(int no)
{
  while(waitpid(-1,NULL,WNOHANG) > 0);
}

int main(int argc,char* argv[])
{
  if(argc != 3)
  {
    printf("./tcp_server ip port");
    return -1;
  }
  signal(SIGCHLD , sigcb);
  string ip = argv[1];
  uint16_t port = atoi(argv[2]);

  TcpSocket sock;
  CHECK_RET(sock.Socket());
  CHECK_RET(sock.Bind(ip,port));
  CHECK_RET(sock.Listen());

  while(1)
  {
    TcpSocket clisock;
    struct sockaddr_in cliaddr;
    //accept是阻塞获取已经完成的连接
    if(sock.Accept(clisock,&cliaddr) == false)
    {
      continue;
    }
    printf("new connect client:%s:%d\n",inet_ntoa(cliaddr.sin_addr),ntohs(cliaddr.sin_port));
    
    int pid = fork();
    if(pid == 0)
    {
      while(1)
      {
        string buf;
        clisock.Recv(buf);
        printf("client say:%s",buf.c_str());

        buf.clear();
        printf("server say:");
        fflush(stdout);
        cin>>buf;
        clisock.Send(buf);
      }
    }
    clisock.Close();
  }
  sock.Close();
  return 0;
}
