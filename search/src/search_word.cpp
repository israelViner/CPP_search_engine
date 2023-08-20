#include <string>
#include <vector>
#include <algorithm>

#include "search_word.hpp"
#include "get_data.hpp"

namespace ks {

SearchWord::SearchWord(GetData& db, std::string token)
    : m_db(db)
    , m_token(token)
{}

std::vector<std::pair<std::string, int32_t>> SearchWord::search() 
{
    std::vector<std::pair<std::string, int32_t>> results;    
    results = m_db.get_word_results(m_token);
    if (!results.empty()) {
        std::sort(results.begin(), results.end(), [](auto &left, auto &right) { return left.second > right.second; });
    }
    return results;
}

} // namespace ks
