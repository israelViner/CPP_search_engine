#ifndef COMUNICATION_TCP_H
#define COMUNICATION_TCP_H

#include <string>

namespace ks {

void send_tcp(int sock, std::string& buffer);
void recv_tcp(int sock, std::string& buffer); 

} // namespace ks

#endif