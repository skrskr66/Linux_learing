#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


class UdpSocket
{
public:
  UdpSocket()
  :_sock(-1)
  { 
  }
  ~UdpSocket()
  {
  }
  bool Socket()
  {
    _sock = socket(AF_INET, SOCK_DGRAM,IPPROTO_UDP);
    if(_sock < 0)
    {
      perror("socket errno");
      return false;
    }
    return true;
  }

  bool Bind(std::string &ip, uint16_t port)
  {
    
  }
private:
  int _sock;
};
