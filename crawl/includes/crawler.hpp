#ifndef CRAWLER_H
#define CRAWLER_H

#include <string>
#include <queue>

#include "page_db.hpp"
#include "set_data.hpp"

namespace ks {

class Crawler 
{
public:
    explicit Crawler(SetData& data_base, std::vector<std::string>  const& urls);

    void crawler();

private:
    void new_links(PageDB& data, std::queue<std::string>& links_to_crawl);
    void new_bounded_links(PageDB& data, std::queue<std::string>& links_to_crawl, std::string const& base_url);

private:
    SetData& m_data_base;
    std::vector<std::string>  m_urls;
    std::queue<std::string> m_links_to_crawl;
};

} // namespace ks

#endif
