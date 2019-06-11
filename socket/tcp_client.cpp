#include "tcpsocket.hpp"

int main(int argc,char* argv[])
{
  if(argc != 3)
  {
    cout<<"./tcp_client ip port"<<endl;
    return -1;
  }
  string ip = argv[1];
  uint16_t port = atoi(argv[2]);
  //字符串转换成整型数的一个函数
  TcpSocket sock;
  CHECK_RET(sock.Socket());
  CHECK_RET(sock.Connect(ip,port));
  
  while(1)
  {
    string buf;
    cout<<"client say:";
    fflush(stdout);
    //fflush(stdout)：清空输出缓冲区，并把缓冲区内容输出。
    cin>>buf;
    sock.Send(buf);

    buf.clear();
    sock.Recv(buf);
    cout<<"server say:"<<buf<<endl;
  }
  sock.Close();
  return 0;
}
