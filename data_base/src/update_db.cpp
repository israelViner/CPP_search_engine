#include <string>

#include "update_db.hpp"
#include "page_db.hpp"
#include "set_data.hpp"

namespace ks {

void update_data_base(std::string const& url, PageDB& page_data, SetData& data_base)
{
    data_base.set_page_links(url, page_data.get_data_links());
    data_base.set_page_words(url, page_data.get_data_words());
}

} // namespace ks