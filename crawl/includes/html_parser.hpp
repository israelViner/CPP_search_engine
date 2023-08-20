#ifndef HTML_PARSER_H
#define HTML_PARSER_H

#include <string>
#include <vector>
#include <gumbo.h>
#include <curlpp/Options.hpp>

#include "html_page.hpp"

namespace ks {

class HTMLParser 
{
public:
    explicit HTMLParser(std::string url, curlpp::Easy& request);
    //~HTMLParser();

    std::string clean_text(GumboOutput* gumbo_output);
    std::vector<std::string> get_links(GumboOutput* gumbo_output);

private:
    std::string clean_text(GumboNode* node);
    std::vector<std::string> get_links(GumboNode* node);
    void search_for_links(GumboNode* node, std::vector<std::string>& links);

private:
    HTMLPage m_page;   
    //GumboOutput* m_gumbo_output; 
};

} // namespace ks

#endif