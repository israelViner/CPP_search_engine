#ifndef TCP_LISTENER_H
#define TCP_LISTENER_H

#include <string>
#include <arpa/inet.h>

namespace ks
{

class TcpListener
{
public:
    explicit TcpListener(std::string ip = "127.0.0.1", int port = 8080);    
    //~TcpListener();

    void init();
    int accept_tcp();

private:
    void create_tcp();
    void connect_tcp();

private:
    int m_port;
    std::string m_ip;
    int m_socket;
    sockaddr_in m_server_addr;
};

} // namespace ks

#endif