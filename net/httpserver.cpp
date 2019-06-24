#include <iostream>
#include <sstream>
#include "tcpsocket.hpp"

int main(int argc,char* argv[])
{
  if(argc != 3)
  {
    cout<<"./httpserver ip port\n"<<endl;
    return -1;
  }

  string ip = argv[1];
  uint16_t port = atoi(argv[2]);

  TcpSocket sock;
  CHECK_RET(sock.Socket());
  CHECK_RET(sock.Bind(ip,port));
  CHECK_RET(sock.Listen());

  while(1)
  {
    TcpSocket clisock;
    if(sock.Accept(clisock) == false)
    {
      continue;
    }
    string buf;
    clisock.Recv(buf);
    cout<<"req:["<<buf<<"]"<<endl;

    string body;
    body = "<html><body><h1>Hello Donkey</h1></body></html>";
    stringstream ss;

    ss << "HTTP/1.1 502 Bad GateWay\r\n";
    ss << "Content-Length: " << body.size() <<"\r\n";
    ss << "Content-Type: text/html\r\n";
    ss << "Location: http://www.baidu.com\r\n";
    ss << "\r\n";

    string header = ss.str();

    clisock.Send(header);
    clisock.Send(body);
    clisock.Close();
  }
  sock.Close();
  return 0;
}
