#include <string>
#include <sstream>
#include <algorithm>

#include "string_cleaner.hpp"

namespace ks {

void clean_string(std::string& txt)
{
    std::transform(txt.begin(), txt.end(), txt.begin(), [](unsigned char c){ return std::tolower(c); });

    for (auto& c : txt) {
        if ((c < 'a' || c > 'z') && (c < '0' || c > 9)) {
            c = ' ';
        }
    }
}

std::vector<std::string> split_string(std::string const& txt)
{
    std::vector<std::string> result;
    std::string token;
    std::istringstream iss(txt);
    while (std::getline(iss, token,' ')) {
        if (token.size() > 1) {
            result.push_back(token);
        }
    }

    return result;
}

} // namespace ks
