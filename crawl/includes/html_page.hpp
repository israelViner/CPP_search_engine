#ifndef HTML_PAGE_H
#define HTML_PAGE_H

#include <string>
#include <curlpp/Options.hpp>

namespace ks {

class HTMLPage 
{
public:
    explicit HTMLPage(std::string const& url, curlpp::Easy& request);    
    
    std::string const& get_html() const;

private:
    std::string m_html;
};

} // namespace ks

#endif