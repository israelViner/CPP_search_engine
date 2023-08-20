#include <iostream>

#include "client_tcp.hpp"
#include "tui.hpp"
#include "client_searcher.hpp"
#include "tcp_exceptions.hpp"

using namespace ks;
    
int main()
{
    try {
        TcpClient socket;    
        socket.create_tcp();
        int sock = socket.connect_tcp();

        ClientSearcher searcher(sock);    
    
        run_searches(searcher);
    } catch (TcpExceptions const& e) {
        std::cout << e.what() << std::endl;
    }
   
    return 0;     
}
