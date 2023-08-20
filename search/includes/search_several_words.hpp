#ifndef SEARCH_SEVERAL_WORDS_H
#define SEARCH_SEVERAL_WORDS_H

#include <string>
#include <vector>

#include "search.hpp"
#include "get_data.hpp"

namespace ks {

class SearchSeveralWords : public Search
{
public:
    explicit SearchSeveralWords(GetData& db, std::vector<std::string> tokens);

    std::vector<std::pair<std::string, int32_t>> search() override;

private:
    GetData& m_db;
    std::vector<std::string> m_tokens;
};

} // namespace ks

#endif