#ifndef GET_DATA_H
#define GET_DATA_H

#include <string>
#include <unordered_map>

namespace ks
{

using matrix = std::unordered_map<std::string, std::unordered_map<std::string, int32_t>>;

class GetData
{
public:
    virtual ~GetData() = default;

    virtual bool is_word_exist(std::string const& word) const = 0;
    virtual std::vector<std::pair<std::string, int32_t>> get_word_results(std::string const& word) const = 0;
    virtual std::vector<std::pair<std::string, int32_t>> get_links_results(std::string const& url) const = 0;
};

} // namespace ks

#endif