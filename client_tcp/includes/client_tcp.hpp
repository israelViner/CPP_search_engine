#ifndef CLIENT_TCP
#define CLIENT_TCP

#include <arpa/inet.h>

#include "string"

namespace ks {

class TcpClient
{
public:
    explicit TcpClient(std::string ip = "127.0.0.1", int port = 8080);    
    //~TcpClient();

    void create_tcp();
    int connect_tcp();

private:
    int m_port;
    std::string m_ip;
    int m_socket;
    sockaddr_in m_server_addr;
};

} // namespace ks

#endif