#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string>
#include <iostream>

#include "comunication_tcp.hpp"
#include "client_tcp.hpp"
#include "tcp_exceptions.hpp"
 
namespace ks {

TcpClient::TcpClient(std::string ip, int port)
    :  m_port(port)
    , m_ip(ip) 
    , m_socket(-1)
    , m_server_addr({0})  
{}    

void TcpClient::create_tcp()
{  
    m_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (m_socket < 0){
        throw CreateSocketExceptions(std::string("ERROR: Couldn't create socket"));
    }
    std::cout << "[+]TCP server socket created" << std::endl;
}

int TcpClient::connect_tcp()
{      
    memset(&m_server_addr, '\0', sizeof(m_server_addr));
    m_server_addr.sin_family = AF_INET;
    m_server_addr.sin_port = m_port;
    m_server_addr.sin_addr.s_addr = inet_addr(m_ip.c_str());

    if (connect(m_socket, (struct sockaddr*)&m_server_addr, sizeof(m_server_addr)) < 0) {
        throw ConeccetSocketExceptions(std::string("ERROR: Couldn't create socket"));        
    }else {
        std::cout << "Connected to the server" << std::endl;
    }

    return m_socket;
}

} // namespace ks
