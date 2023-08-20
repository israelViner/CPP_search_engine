#include <string>
#include <vector>
#include <algorithm>

#include <iostream>

#include "search_several_words.hpp"
#include "search_word.hpp"
#include "get_data.hpp"

namespace ks {

SearchSeveralWords::SearchSeveralWords(GetData& db, std::vector<std::string> tokens)
    : m_db(db)
    , m_tokens(tokens)
{}

std::vector<std::pair<std::string, int32_t>> SearchSeveralWords::search() 
{
    std::string word = m_tokens.front();
    m_tokens.erase(m_tokens.begin());
    SearchWord search_word(m_db, word);
    std::vector<std::pair<std::string, int32_t>> results = search_word.search(); 
        
    if (results.empty()) {
        return results;
    }

    for (auto const& token : m_tokens) {        
        SearchWord token_search(m_db, token);
        auto token_results = token_search.search();
        std::sort(token_results.begin(), token_results.end(), [](auto const& res1, auto const& res2) { return res1.first < res2.first; }); 
        std::sort(results.begin(), results.end(), [](auto const& res1, auto const& res2) { return res1.first < res2.first; }); 

        std::vector<std::pair<std::string, int32_t>> tmp_results;        
        std::set_intersection(results.begin(), results.end(), token_results.begin(), token_results.end(), std::back_inserter(tmp_results),
            [](std::pair<std::string, int32_t> const& p1, std::pair<std::string, int32_t> const& p2)
            {
                return p1.first < p2.first;
            });

        for (auto& pair : tmp_results) {
            auto it = std::find_if(token_results.begin(), token_results.end(), [pair](std::pair<std::string, int32_t> const& q) { return q.first == pair.first; });
            pair.second = std::min(pair.second, it->second);
        }
        results = tmp_results;
    }

    std::sort(results.begin(), results.end(), [](auto &left, auto &right) { return left.second > right.second; });
    return results;
}

} // namespace ks
