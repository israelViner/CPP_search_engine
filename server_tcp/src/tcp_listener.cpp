#include <string.h>
#include <arpa/inet.h>
#include <string>
#include <iostream>

#include "tcp_listener.hpp"
#include "tcp_channel.hpp"
#include "tcp_exceptions.hpp"

namespace ks {

TcpListener::TcpListener(std::string ip, int port)   
    :  m_port(port)
    , m_ip(ip) 
    , m_socket(-1)
    , m_server_addr({0})  
{}

void TcpListener::init()
{
    create_tcp();
    connect_tcp();

    listen(m_socket, 5);
    std::cout << "....Listening....\n";
}

int TcpListener::accept_tcp()
{
    int client_sock = accept(m_socket, nullptr, nullptr);
    std::cout << "[+]Client connected.\n";
    return client_sock;
}


void TcpListener::create_tcp()
{
    m_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (m_socket < 0){
        throw CreateSocketExceptions(std::string("ERROR: Couldn't create socket"));
    }
    std::cout << "[+]TCP server socket created.\n";
}

void TcpListener::connect_tcp()
{
    int opt = 1;
    if (setsockopt(m_socket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        throw SetSocketExceptions(std::string("ERROR: Couldn't set socket"));
    }

    memset(&m_server_addr, '\0', sizeof(m_server_addr));
    m_server_addr.sin_family = AF_INET;
    m_server_addr.sin_port = m_port;
    m_server_addr.sin_addr.s_addr = inet_addr(m_ip.c_str());

    int n = bind(m_socket, (struct sockaddr*)&m_server_addr, sizeof(m_server_addr));
    if (n < 0){
        throw BindingExceptions(std::string("ERROR: Couldn't bind socket"));
    }
    std::cout << "[+]Bind to the port number: " << m_port << "\n";
}

} // namespace ks
