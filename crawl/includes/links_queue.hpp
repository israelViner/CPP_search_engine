#ifndef LINKS_QUEUE_H
#define LINKS_QUEUE_H

#include <string>
#include <queue>

#include "page_db.hpp"
#include "set_data.hpp"

namespace ks {

void new_links(PageDB& data, std::queue<std::string>& links_to_crawl, SetData& data_base);
void new_bounded_links(PageDB& data, std::queue<std::string>& links_to_crawl, SetData& data_base, std::string const& base_url);

} // namespace ks

#endif