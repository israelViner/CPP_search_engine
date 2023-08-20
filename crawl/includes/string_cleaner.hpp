#ifndef STRING_CLEANER_H
#define STRING_CLEANER_H

#include <string>

namespace ks {

void clean_string(std::string& txt);

std::vector<std::string> split_string(std::string const& txt);

} // namespace ks

#endif