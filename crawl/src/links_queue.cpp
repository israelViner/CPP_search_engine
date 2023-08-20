#include <string>
#include <vector>
#include <queue>
#include <regex>

#include "links_queue.hpp"
#include "page_db.hpp"
#include "set_data.hpp"

namespace ks {

void new_links(PageDB& data, std::queue<std::string>& links_to_crawl, SetData& data_base)
{
    auto start_it = data.get_data_links().begin();
    auto end_it = data.get_data_links().end();
    while (start_it != end_it) {
        if (!data_base.get_data_links().count(start_it->first)) { 
            links_to_crawl.push(start_it->first);
        }
        start_it++;
    }
}

void new_bounded_links(PageDB& data, std::queue<std::string>& links_to_crawl, SetData& data_base, std::string const& base_url)
{
    std::regex pattern(R"((https?://[^/]+))");
    std::smatch match;
    std::regex_search(base_url, match, pattern);
    std::string domain = match[1];
    auto start_it = data.get_data_links().begin();
    auto end_it = data.get_data_links().end();
    while (start_it != end_it) {
        if (!data_base.get_data_links().count(start_it->first) && (start_it->first).find(domain)!= std::string::npos) { 
            links_to_crawl.push(start_it->first);
        }
        start_it++;
    }
}

} // namespace ks
