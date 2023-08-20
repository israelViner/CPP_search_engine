#ifndef UPDATE_DB_H
#define UPDATE_DB_H

#include <string>

#include "page_db.hpp"
#include "set_data.hpp"

namespace ks {

void update_data_base(std::string const& url, PageDB& page_data, SetData& data_base);

} // namespace ks

#endif