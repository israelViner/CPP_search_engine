#ifndef SEARCH_FACORY_H
#define SEARCH_FACORY_H

#include <string>
#include <vector>
#include <memory>

#include "search.hpp"
#include "get_data.hpp"

namespace ks {

class SearchFactory
{
public:
    static std::shared_ptr<Search> create_searcher(std::string const& line, GetData& data);
};

} // namespace ks

#endif