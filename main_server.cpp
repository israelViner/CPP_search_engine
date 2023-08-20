#include <string>
#include <vector>
#include <iostream>

#include "db.hpp"
#include "configurations.hpp"
#include "crawler.hpp"
#include "concrete_searcher.hpp"
//#include "tui.hpp"
#include "tcp_listener.hpp"
#include "tcp_searcher.hpp"
#include "exceptions.hpp"

using namespace ks;
    
int main()
{
    //std::string url("https://harrypotter.fandom.com/wiki/Main_Page");
    //std::string url("https://en.wikipedia.org/wiki/Chess");
    Configurations::load_configurations();
    
    std::vector<std::string> base_urls = Configurations::get_urls();
    DB db(base_urls);

    Crawler crawl(db, Configurations::get_urls()); 
    crawl.crawler(); 

    ConcreteSearcher searcher(db);

    try {    
        TcpSearcher tcp_searcher(searcher);
        TcpListener listener;
        listener.init();        

        while (true) {
            int sock = listener.accept_tcp();
            tcp_searcher.search(sock);         
      
        }

    } catch (TcpExceptions const& e) {
        std::cout << e.what() << std::endl;
    }
    // run_searches(db);

    return 0;     
}
