#include <string>
#include <vector>
#include <unordered_map>

#include "db.hpp"
#include "page_db.hpp"

namespace ks {

DB::DB(std::vector<std::string> const& page_url)
    : m_base_urls(page_url)   
{}

std::vector<std::string> const& DB::get_base_urls() const
{
    return m_base_urls;
}

void DB::set_page_links(std::string const& url, std::unordered_map<std::string, int32_t> const& page_links)
{
    m_data_links[url] = page_links;
} 

void DB::set_page_words(std::string const& url, std::unordered_map<std::string, int32_t> const& page_words)
{
    for (auto& word : page_words) {
        m_data_words[word.first][url] = word.second;
    } 
}

size_t DB::size_links() const
{
    return m_data_links.size();
}

size_t DB::size_words() const 
{
    return m_data_words.size();
}

bool DB::is_link_exist(std::string const& url) const
{
   return m_data_links.count(url);
}

bool DB::is_word_exist(std::string const& word) const
{
   return m_data_words.count(word);
}


std::vector<std::pair<std::string, int32_t>> DB::get_word_results(std::string const& word) const 
{
    std::vector<std::pair<std::string, int32_t>> results;    
      
    if (m_data_words.count(word)) {
        for (auto const& url : m_data_words.at(word)) {  
            results.push_back(std::make_pair(url.first, url.second));            
        }
    }

    return results;
}

std::vector<std::pair<std::string, int32_t>> DB::get_links_results(std::string const& url) const 
{
    std::vector<std::pair<std::string, int32_t>> results;    
      
    if (m_data_links.count(url)) {
        for (auto const& url : m_data_links.at(url)) {  
            results.push_back(std::make_pair(url.first, url.second));            
        }
    }

    return results;
}

} // namespace ks