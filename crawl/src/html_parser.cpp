#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <gumbo.h>

#include "html_parser.hpp"
#include "html_page.hpp"
#include "fix_url.hpp"

namespace ks {

HTMLParser::HTMLParser(std::string url, curlpp::Easy& request)
    : m_page(HTMLPage(url, request))
{}

// HTMLParser::~HTMLParser()
// {
//     gumbo_destroy_output(&kGumboDefaultOptions, m_gumbo_output);
// }
	
std::string HTMLParser::clean_text(GumboOutput* gumbo_output)
{
    gumbo_output = gumbo_parse(m_page.get_html().c_str());
    return clean_text(gumbo_output->root);
}

std::vector<std::string> HTMLParser::get_links(GumboOutput* gumbo_output)
{
    gumbo_output = gumbo_parse(m_page.get_html().c_str());
    return get_links(gumbo_output->root);
}

std::string HTMLParser::clean_text(GumboNode* node) 
{    
    if (node->type == GUMBO_NODE_TEXT) {
        return std::string(node->v.text.text);
    } else if (node->type == GUMBO_NODE_ELEMENT &&
        node->v.element.tag != GUMBO_TAG_SCRIPT &&
        node->v.element.tag != GUMBO_TAG_STYLE) {
        std::string contents = "";
        GumboVector* children = &node->v.element.children;
        for (unsigned int i = 0; i < children->length; ++i) {
            const std::string text = clean_text((GumboNode*) children->data[i]);
            if (i != 0 && !text.empty()) {
                contents.append(" ");
            }
            contents.append(text);
        }
        return contents;
    } else {
        return "";
    }
}

std::vector<std::string> HTMLParser::get_links(GumboNode* node)
{
    std::vector<std::string> links;
    search_for_links(node, links);
    for (auto& i : links) {
        fix_url(i, "https://harrypotter.fandom.com/wiki/Main_Page");
    }
    links.erase(std::remove_if(links.begin(), links.end(), [](std::string const& link) { return link.size() == 0; }), links.end());
    return links;
}

void HTMLParser::search_for_links(GumboNode* node, std::vector<std::string>& links) 
{
    if (node->type != GUMBO_NODE_ELEMENT) {
        return;
    }
    GumboAttribute* href;
    if (node->v.element.tag == GUMBO_TAG_A && (href = gumbo_get_attribute(&node->v.element.attributes, "href"))) {
        links.push_back(href->value);
    }

    GumboVector* children = &node->v.element.children;
    for (unsigned int i = 0; i < children->length; ++i) {
        search_for_links(static_cast<GumboNode*>(children->data[i]), links);
    }
}

} // namespace ks
