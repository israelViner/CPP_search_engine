#ifndef BIN_SEPARATOR_H
#define BIN_SEPARATOR_H

#include <string>
#include <curlpp/Options.hpp>
#include <gumbo.h>

#include "page_db.hpp"

namespace ks {

PageDB bin_separator(std::string const& url, curlpp::Easy& request, GumboOutput* gumbo_output);

} // namespace ks

#endif