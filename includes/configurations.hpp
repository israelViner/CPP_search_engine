#ifndef CONFIGURATIONS_H
#define CONFIGURATIONS_H

#include <string>
#include <vector>
#include <fstream>
#include <nlohmann/json.hpp>

namespace ks {

class Configurations
{
public:
    static void load_configurations();
    static std::vector<std::string> const& get_urls();
    static bool is_bounded();
    static bool is_limited();
    static size_t get_limit();

private:
    static Configurations&  get_instance(std::vector<std::string> base_url  = {""},  bool is_bounded = true, bool is_limited = true, size_t limit = 10);
    static void from_json(nlohmann::json const& j);
    Configurations(std::vector<std::string> base_url,  bool is_bounded, bool is_limited, size_t limit);
    bool is_number(std::string const& s);

private:
    std::vector<std::string> m_base_urls;
    bool m_is_bounded;
    bool m_is_limited;
    size_t m_limit;
};

} // namespace ks

#endif