#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <sstream>
#include <iostream>

#include "search_factory.hpp"
#include "search.hpp"
#include "search_word.hpp"
#include "search_several_words.hpp"
#include "search_negative_words.hpp"
#include "get_data.hpp"

namespace ks {

std::shared_ptr<Search> SearchFactory::create_searcher(std::string const& line, GetData& data)
{
    std::istringstream iss(line);
    std::vector<std::string> tokens;
    std::string token;
    while (std::getline(iss, token, ' ')) {
        std::transform(token.begin(), token.end(), token.begin(), [](unsigned char c){ return std::tolower(c); });
        tokens.push_back(token);
    }
    
    if (tokens.size() <= 1) {
        return std::make_shared<SearchWord>(data, tokens.front());
    } else if (std::any_of(tokens.begin(), tokens.end(), [](std::string const& word){ return word[0] == '-'; })) {
        return std::make_shared<SearchNegativeWords>(data, tokens);
    } else {
        return std::make_shared<SearchSeveralWords>(data, tokens);
    }
}

} // namespace ks
