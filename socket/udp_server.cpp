#include "udpsocket.hpp"

#define CHECK_RET(q) if((q) == false){return -1;}

int main(int argc,char *argv[])
{
  if(argc != 3)
  {
    cout<<"./udp_server ip port:"<<endl;
    return -1;
  }
  string ip = argv[1];
  uint16_t port = atoi(argv[2]);

  UdpSocket sock;
  CHECK_RET(sock.Socket());
  CHECK_RET(sock.Bind(ip,port));

  while(1)
  {
    string buf;
    struct sockaddr_in cli_addr;
    CHECK_RET(sock.Recv(buf,&cli_addr));
    cout<<"client say:"<<buf<<endl;

    cout<<"server say:";
    fflush(stdout);
    cin>>buf;
    CHECK_RET(sock.Send(buf,&cli_addr));
  }
  sock.Close();
}
