#include <string>
#include <regex>

#include "fix_url.hpp"

namespace ks {

static auto start_with = [](std::string const& str, std::string const& prefix) { return !str.compare(0, prefix.size(), prefix); };
static void domain_missing(std::string& url, std::string const& base_url); 
static void relative_url(std::string& url, std::string const& base_url);
static void same_directory_url(std::string& url, std::string const& base_url);
static void document_relative_url(std::string& url, std::string const& base_url);

void fix_url(std::string& url, std::string const& base_url)
{
    if (url.size() < 5) {
        url = "";
        return;
    }
    if(start_with(url, "http")) {   
        return;
    }
    if(start_with(url, "//")) {         
        domain_missing(url, base_url);
    } else if(start_with(url, "/")) {         
        relative_url(url, base_url);
    } else if(start_with(url, "../")) {         
        same_directory_url(url, base_url);      
    } else {        
        document_relative_url(url, base_url);         
    }
}

void domain_missing(std::string& url, std::string const& base_url) 
{
    if (start_with(base_url, "https:")) {
        url = "https:" + url;
    } else {
        url = "http:" + url;
    }
}

void relative_url(std::string& url, std::string const& base_url)
{
    std::smatch mathces;
    std::regex e("^https?:\\/\\/(?:[a-zA-Z0-9]+)(?:\\.[a-zA-Z0-9]+)+");
    std::regex_search(base_url, mathces, e);
    std::string prefix = mathces[0].str();
    url = prefix + url;
}

void same_directory_url(std::string& url, std::string const& base_url)
{ 
    std::smatch mathces;
    std::regex e(R"((https?://[^/]+))");
    std::regex_search(base_url, mathces, e);
    std::string prefix = mathces[0].str();
    url = prefix + url;
}

void document_relative_url(std::string& url, std::string const& base_url)
{
    std::smatch mathces;
    std::regex e("^https?:\\/\\/(?:[a-zA-Z0-9]+)(?:\\.[a-zA-Z0-9]+)+\\/(?:[a-zA-Z0-9]+)*");
    std::regex_search(base_url, mathces, e);
    std::string prefix = mathces[1].str();
    url = prefix + url;
}

} // namespace ks
