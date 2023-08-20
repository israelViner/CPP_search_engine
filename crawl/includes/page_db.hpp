#ifndef PAGE_DB_H
#define PAGE_DB_H

#include <string>
#include <unordered_map>

namespace ks
{
using map = std::unordered_map<std::string, int32_t>;

class PageDB
{
public:
    explicit PageDB(std::string const& page_url);

    map const& get_data_links() const;
    map& get_data_links();
    map const& get_data_words() const;
    map& get_data_words();
    std::string const& get_base_url() const;

private:
    std::string m_page_url;
    map m_data_links;
    map m_data_words;
};

} // namespace ks

#endif
