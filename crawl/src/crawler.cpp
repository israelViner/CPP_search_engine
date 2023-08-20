#include <string>
#include <vector>
#include <regex>
#include <iostream>
#include <memory>
#include <queue>
#include <gumbo.h>

#include <curlpp/cURLpp.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/Infos.hpp>

#include "crawler.hpp"
#include "bin_separator.hpp"
#include "configurations.hpp"
#include "set_data.hpp"
#include "update_db.hpp"

namespace ks {

Crawler::Crawler(SetData& data_base, std::vector<std::string> const& urls)
 : m_data_base(data_base)
 , m_urls(urls)
{}

void Crawler::crawler()
{
    std::cout << "...Crawl processing.... " << std::endl;   
    
    curlpp::Easy requester;
    GumboOutput* gumbo_output = gumbo_parse("Hello");;
    size_t base_url_index = 0;
    while (base_url_index < m_urls.size()) {        
        while (!m_links_to_crawl.empty()) {
            m_links_to_crawl.pop();
        }
        m_links_to_crawl.push(m_urls[base_url_index]);
        size_t count = 0;        
        while (!m_links_to_crawl.empty() && count < Configurations::get_limit() / Configurations::get_urls().size()) {
            try {        
                std::string url = m_links_to_crawl.front();
                if (Configurations::is_limited() && m_data_base.size_links() >= Configurations::get_limit()) { 
                    return;
                }         
                PageDB page_data = bin_separator(url, requester, gumbo_output);        
                std::cout << m_data_base.size_links() + 1 << ". " << url << std::endl; 
                if (Configurations::is_bounded()) {
                    new_bounded_links(page_data, m_links_to_crawl, m_urls[base_url_index]);
                } else {
                    new_links(page_data, m_links_to_crawl);
                } 
                update_data_base(url, page_data, m_data_base);
                ++count;
            } catch (std::exception const& e) {
                std::cout << e.what() << std::endl;
            }
            m_links_to_crawl.pop();
        } 

        ++base_url_index;
    }

    gumbo_destroy_output(&kGumboDefaultOptions, gumbo_output);
    std::cout << "The crawling process is finished.\nthe amount of the unique links in the data base is: " << m_data_base.size_links() << ", and the amount of the indexed words is: " << m_data_base.size_words() << std::endl;  
}


void Crawler::new_links(PageDB& data, std::queue<std::string>& links_to_crawl)
{
    auto start_it = data.get_data_links().begin();
    auto end_it = data.get_data_links().end();
    while (start_it != end_it) {
        if (!m_data_base.is_link_exist(start_it->first)) { 
            links_to_crawl.push(start_it->first);
        }
        start_it++;
    }
}

void Crawler::new_bounded_links(PageDB& data, std::queue<std::string>& links_to_crawl, std::string const& base_url)
{
    std::regex pattern(R"((https?://[^/]+))");
    std::smatch match;
    std::regex_search(base_url, match, pattern);
    std::string domain = match[1];
    auto start_it = data.get_data_links().begin();
    auto end_it = data.get_data_links().end();
    while (start_it != end_it) {
        if (!m_data_base.is_link_exist(start_it->first) && (start_it->first).find(domain)!= std::string::npos) { 
            links_to_crawl.push(start_it->first);
        }
        start_it++;
    }
}

} // namespace ks