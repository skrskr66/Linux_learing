#include "udpsocket.hpp"

#define CHECK_RET(q) if((q) == false){return -1;}

int main(int argc,char *argv[])
{
  if(argc != 3)
  {
    cout<<"./udp_client ip port"<<endl;
    return -1;
  }
  string ip = argv[1];
  uint16_t port = atoi(argv[2]);

  UdpSocket sock;
  CHECK_RET(sock.Socket());

  struct sockaddr_in srv_addr;
  srv_addr.sin_family = AF_INET;
  srv_addr.sin_port = htons(port);
  srv_addr.sin_addr.s_addr = inet_addr(ip.c_str());

  while(1)
  {
    string buf;
    cout<<"client say:";
    fflush(stdout);
    cin>>buf;
    CHECK_RET(sock.Send(buf,&srv_addr));
    CHECK_RET(sock.Recv(buf,&srv_addr));
    cout<<"server say:"<<buf<<endl;

  }
  sock.Close();
}
