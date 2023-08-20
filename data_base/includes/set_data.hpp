#ifndef SET_DATA_H
#define SET_DATA_H

#include <string>
#include <unordered_map>

namespace ks
{

using matrix = std::unordered_map<std::string, std::unordered_map<std::string, int32_t>>;

class SetData
{
public:
    virtual ~SetData() = default;

    virtual void set_page_links(std::string const& url, std::unordered_map<std::string, int32_t> const& page_links) = 0;
    virtual void set_page_words(std::string const& url, std::unordered_map<std::string, int32_t> const& page_words) = 0;
    virtual bool is_link_exist(std::string const& url) const = 0;
    virtual size_t size_links() const = 0;
    virtual size_t size_words() const = 0;
};

} // namespace ks

#endif