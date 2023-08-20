#ifndef SEARCH_MINUS_WORD_H
#define SEARCH_MINUS_WORD_H

#include <string>
#include <vector>

#include "search.hpp"
#include "get_data.hpp"

namespace ks {

class SearchNegativeWords : public Search
{
public:
    explicit SearchNegativeWords(GetData& db, std::vector<std::string> tokens);

    std::vector<std::pair<std::string, int32_t>> search() override;

private:
    std::vector<std::string> get_negative_tokens(std::vector<std::string>& words);
    std::vector<std::string> get_regular_tokens(std::vector<std::string>& words);

private:
    GetData& m_db;
    std::vector<std::string> m_tokens;
};

} // namespace ks

#endif