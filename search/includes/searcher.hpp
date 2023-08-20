#ifndef SEARCHER_H
#define SEARCHER_H

#include <string>
#include <vector>

namespace ks {

class Searcher
{
public:
    virtual ~Searcher() = default;

    virtual std::vector<std::pair<std::string, int32_t>> search(std::string token) = 0;
};

} // namespace ks

#endif