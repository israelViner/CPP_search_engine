#include <string>
#include <unordered_map>

#include "page_db.hpp"

namespace ks {

PageDB::PageDB(std::string const& page_url)
    : m_page_url(page_url)
{}

map const& PageDB::get_data_links() const
{
    return m_data_links;
}

map& PageDB::get_data_links()
{
    return m_data_links;
}

map const& PageDB::get_data_words() const
{
    return m_data_words;
}

map& PageDB::get_data_words()
{
    return m_data_words;
}

std::string const& PageDB::get_base_url() const
{
    return m_page_url;
}


} // namespace ks