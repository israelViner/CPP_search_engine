#include <string.h>
#include <arpa/inet.h>
#include <string>
#include <iostream>

#include "tcp_channel.hpp"

namespace ks {

void TcpChannel::send_msg(int client_sock , std::string const& msg)
{
    send(client_sock, msg.data(), msg.size(), 0);
}

std::string TcpChannel::recv_msg(int client_sock)
{
    std::string msg;
    msg.reserve(1024);
    msg.resize(1024);
    recv(client_sock, msg.data(), msg.size(), 0);
    msg.resize(strlen(msg.data()));
    return msg;
}

} // namespace ks
