#include <string.h>
#include <arpa/inet.h>
#include <string>
 
namespace ks {

void send_tcp(int sock, std::string& buffer) 
{
    send(sock, buffer.data(), buffer.size(), 0);
}

void recv_tcp(int sock, std::string& buffer) 
{
    buffer = buffer.replace(0, buffer.size(), buffer.size(), '\0');
    buffer.resize(1024);
    recv(sock, buffer.data(), buffer.capacity(), 0);
    buffer.resize(strlen(buffer.data()));
}   

} // namespace ks
