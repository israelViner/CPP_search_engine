#ifndef SEARCH_H
#define SEARCH_H

#include <string>
#include <vector>

namespace ks {

class Search
{
public:
    virtual ~Search() = default;

    virtual std::vector<std::pair<std::string, int32_t>> search() = 0;
};

} // namespace ks

#endif