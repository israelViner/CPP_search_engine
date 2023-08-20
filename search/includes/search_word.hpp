#ifndef SEARCH_WORD_H
#define SEARCH_WORD_H

#include <string>
#include <vector>

#include "search.hpp"
#include "get_data.hpp"

namespace ks {

class SearchWord : public Search
{
public:
    explicit SearchWord(GetData& db, std::string token);

    std::vector<std::pair<std::string, int32_t>> search() override;

private:
    GetData& m_db;
    std::string m_token;
};

} // namespace ks

#endif