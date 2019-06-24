/*=============================================================== 
 *   Copyright (C) . All rights reserved.")
 *   文件名称： 
 *   创 建 者：zhang
 *   创建日期：
 *   描    述：在这里属用c++封装TcpSocket类
 *       创建套接字
 *           bool Socket() 
 *       绑定地址信息
 *           bool Bind(std::string &ip, uint16_t port)
 *       服务端开始监听
 *           bool Listen(int backlog = 5)
 *       客户端发起连接请求
 *           bool Connect(std::string &ip, uint16_t port)
 *       服务端获取已经连接完成的客户端新建socket
 *           bool Accept(TcpSocket &clisock, struct sockaddr_in *addr)
 *       接收数据
 *           bool Recv(std::string &buf)
 *       发送数据
 *           bool Send(std::string &buf)
 *       关闭套接字
 *           bool Close()
 ================================================================*/

#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <error.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string>
#include <sys/types.h>
using namespace std;
#define CHECK_RET(q) if((q) == false){return -1;}

class TcpSocket
{
public:
  TcpSocket()
    :_sockfd(-1)
  {
    
  }
  ~TcpSocket()
  {

  }
  void SetSockFd(int fd)
  {
     _sockfd = fd;
  }
  bool Socket()
  {
    _sockfd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    if(_sockfd < 0)
    {
      perror("socket error");
      return false;
    }
    return true;
  }
  bool Bind(string &ip,uint16_t port)
  {
    struct sockaddr_in addr; //网络套接字常用
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(ip.c_str());

    socklen_t len = sizeof(struct sockaddr_in);
    int ret = bind(_sockfd,(struct sockaddr*)&addr,len);
    if(ret < 0)
    {
      perror("bind error");
      return false;
    }
    return true;
  }
  bool Listen(int backlog = 10)
  {
    int ret = listen(_sockfd,backlog);
    if(ret < 0)
    {
      perror("listen error");
      return false;
    }
    return true;
  }
  bool Connect(string &ip,uint16_t port)
  {
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(ip.c_str());
    socklen_t len = sizeof(struct sockaddr_in);
    int ret = connect(_sockfd,(struct sockaddr*)&addr,len);
    if(ret < 0)
    {
      return false;
    }
    return true;
  }
  bool Accept(TcpSocket &csock,struct sockaddr_in *addr = NULL)
  {
    struct sockaddr_in _addr;
    socklen_t len = sizeof(struct sockaddr_in);
    int newfd = accept(_sockfd,(struct sockaddr*)&_addr,&len);
    if(newfd < 0)
    {
      perror("accept error");
      return false;
    }
    if(addr != NULL)
    {
      memcpy(addr,&addr,len);
    }
    csock.SetSockFd(newfd);
    return true;
  }
  bool Recv(string &buf)
  {
    char tmp[4096] = {0};
    int ret = recv(_sockfd,tmp,4096,0);
    if(ret < 0)
    {
      perror("recv error");
      return false;
    }
    else if(ret == 0)
    {
      cout<<"peer shutdown"<<endl;
      return false;
    }
    buf.assign(tmp,ret);
    //C++ string类的成员函数，用于拷贝、赋值操作
    //它们允许我们顺次地把一个string 对象的部分内容拷贝到另一个string 对象上。
    return true;
  }
  bool Send(string &buf)
  {
    int ret = send(_sockfd,buf.c_str(),buf.size(),0);
    if(ret < 0)
    {
      perror("send error");
      return false;
    }
    return true;
  }
  bool Close()
  {
    close(_sockfd);
    _sockfd = -1;
  }
private:
  int _sockfd;
};
