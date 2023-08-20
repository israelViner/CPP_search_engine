#include <string>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <nlohmann/json.hpp>

#include "configurations.hpp"
#include "config_exceptions.hpp"

namespace ks {

Configurations::Configurations(std::vector<std::string> base_url,  bool is_bounded, bool is_limited, size_t limit)
    : m_base_urls(base_url)
    , m_is_bounded(is_bounded)
    , m_is_limited(is_limited)
    , m_limit(limit)
{
    // std::string a;
    // std::string b;
    // std::cout << "Enter the base url that you want to crawl: " << std::endl;
    // std::getline(std::cin, m_base_url);
    // while (true) {
    //     std::cout << "Do you want a limited crawling? [y / n] " << std::endl;
    //     std::getline(std::cin, a);
    //     if (a == "n") {
    //         m_is_limited = false;
    //         m_limit = INT32_MAX;
    //         break;
    //     } else if (a == "y") {
    //         m_is_limited = true;
    //         std::cout << "Enter the number of pages that you want to crawl: " << std::endl;
    //         std::getline(std::cin, a);
    //         if (is_number(a)) {
    //             m_limit = std::stoi(a);
    //             break;
    //         }
    //     }
    // }
    // while (true) {
    //     std::cout << "Do you want a bounded crawling? [y / n]" << std::endl;
    //     std::getline(std::cin, b);
    //     if (b == "n") {
    //         m_is_bounded = false;
    //         break;
    //     } else if (b == "y") {
    //         m_is_bounded = true;
    //         break; 
    //     }   
    // }    
}

Configurations& Configurations::get_instance(std::vector<std::string> base_url,  bool is_bounded, bool is_limited, size_t limit)
{
    static Configurations instance(base_url, is_bounded, is_limited, limit);
    return instance;
}


std::vector<std::string> const& Configurations::get_urls()
{
    Configurations& config = get_instance();
    return config.m_base_urls;
}

bool Configurations::is_bounded()
{
    Configurations& config = get_instance();
    return config.m_is_bounded;
}

bool Configurations::is_limited()
{
    Configurations& config = get_instance();
    return config.m_is_limited;
}

size_t Configurations::get_limit()
{
    Configurations& config = get_instance();
    return config.m_limit;
}

bool Configurations::is_number(std::string const& s)
{
    return !s.empty() && std::find_if(s.begin(), s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}

void Configurations::load_configurations()
{
    try {
        std::ifstream file("config.json");
        nlohmann::json json;
        file >> json;
        from_json(json);
    } catch (const nlohmann::json::out_of_range& e) {
        throw TxtExceptions(std::string(std::string("Wrong json text: ") + e.what()));
    } catch (const nlohmann::json::exception& e) {
        throw ConfigFileExceptions(std::string(std::string("Error loading file ") + e.what()));
    }
}

void Configurations::from_json(nlohmann::json const& j)
{
    std::vector<std::string> base_urls;
    bool is_bounded;
    bool is_limited;
    size_t limit;

    j.at("base_url").get_to(base_urls);
    j.at("is_bounded").get_to(is_bounded);
    j.at("is_limited").get_to(is_limited);
    j.at("limit").get_to(limit);

    Configurations& config = get_instance(base_urls, is_bounded, is_limited, limit);
    config.is_limited(); 
}

} // namespace ks