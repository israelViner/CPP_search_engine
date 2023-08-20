#ifndef TCP_CHANNEL_H
#define TCP_CHANNEL_H

#include <string>

namespace ks {

class TcpChannel
{
public:
    static void send_msg(int client_sock, std::string const& msg);
    static std::string recv_msg(int client_sock);

};

} // namespace ks

#endif