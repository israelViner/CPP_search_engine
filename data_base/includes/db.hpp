#ifndef DB_H
#define DB_H

#include <string>
#include <unordered_map>

#include "get_data.hpp"
#include "set_data.hpp"

namespace ks
{

using matrix = std::unordered_map<std::string, std::unordered_map<std::string, int32_t>>;

class DB : public GetData, public SetData
{
public:
    explicit DB(std::vector<std::string> const& page_urls);
    
    size_t size_links() const override;
    size_t size_words() const override;
    void set_page_links(std::string const& url, std::unordered_map<std::string, int32_t> const& page_links) override;
    void set_page_words(std::string const& url, std::unordered_map<std::string, int32_t> const& page_words) override;
    bool is_link_exist(std::string const& url) const override;
    bool is_word_exist(std::string const& word) const override;
    std::vector<std::pair<std::string, int32_t>> get_word_results(std::string const& word) const override;
    std::vector<std::pair<std::string, int32_t>> get_links_results(std::string const& url) const override;
    std::vector<std::string> const& get_base_urls() const;

private:
    std::vector<std::string> m_base_urls;
    matrix m_data_links;
    matrix m_data_words;
};

} // namespace ks

#endif