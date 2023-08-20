#include <string>
#include <vector>
#include <algorithm>

#include <iostream>

#include "search_negative_words.hpp"
#include "search_several_words.hpp"
#include "search_word.hpp"
#include "get_data.hpp"

namespace ks {

SearchNegativeWords::SearchNegativeWords(GetData& db, std::vector<std::string> tokens)
    : m_db(db)
    , m_tokens(tokens)
{}

std::vector<std::string> SearchNegativeWords::get_negative_tokens(std::vector<std::string>& words)
{
    std::vector<std::string> negative_tokens;
    for (auto& word : words) {
        if (word[0] == '-') {
            negative_tokens.push_back(word.substr(1));
        }
    }
    return negative_tokens;
}

std::vector<std::string> SearchNegativeWords::get_regular_tokens(std::vector<std::string>& words)
{
    std::vector<std::string> regular_tokens;
    for (auto& word : words) {
        if (word[0] != '-') {
            regular_tokens.push_back(word);
        }
    }
    return regular_tokens;
}

std::vector<std::pair<std::string, int32_t>> SearchNegativeWords::search() 
{
    std::vector<std::string> regular_tokens = get_regular_tokens(m_tokens);
    SearchSeveralWords first_search(m_db, regular_tokens);
    auto results = first_search.search();
    std::sort(results.begin(), results.end(), [](auto const& res1, auto const& res2) { return res1.first < res2.first; }); 

    if (results.empty()) {
        return results;
    }

    std::vector<std::string> negative_tokens = get_negative_tokens(m_tokens);    
    for (auto const& token : negative_tokens) {        
        SearchWord token_search(m_db, token);
        auto token_results = token_search.search();
        std::sort(token_results.begin(), token_results.end(), [](auto const& res1, auto const& res2) { return res1.first < res2.first; }); 

        std::vector<std::pair<std::string, int32_t>> tmp_results;        
        std::set_difference(results.begin(), results.end(), token_results.begin(), token_results.end(), std::back_inserter(tmp_results),
            [](std::pair<std::string, int32_t> const& p1, std::pair<std::string, int32_t> const& p2)
            {
                return p1.first < p2.first;
            });

        results = tmp_results;
    }

    std::sort(results.begin(), results.end(), [](auto &left, auto &right) { return left.second > right.second; });
    return results;
}

} // namespace ks
