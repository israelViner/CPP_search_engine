#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <sstream>

#include "tui.hpp" 
#include "concrete_searcher.hpp"
#include "search_factory.hpp"
#include "get_data.hpp" 

#include "client_searcher.hpp"


namespace ks {

void run_searches(Searcher& searcher)
{
    while (true) {
        std::cout << "Enter a words to search for: ";
        std::string line;
        std::getline(std::cin, line);
        if (line.empty()) {
            break;
        }
        
        std::vector<std::pair<std::string, int32_t>> results = searcher.search(line);     
               
        std::cout << "The amount of the results is: " << ((results.size() <= 10) ? results.size() : 10) << std::endl;

        for (size_t i = 0; i < results.size() && i < 10; ++i) {
            std::cout << i+1 << ". " << results[i].first << ", " << results[i].second << " times" << std::endl;
        }
        std::cout << std::endl;
        std::cout << "To the next search press Enter..." << std::endl; 
        std::cin.get();
    }
}

} // namespace ks
