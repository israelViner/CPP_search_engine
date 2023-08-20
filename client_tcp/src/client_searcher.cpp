#include <iostream>
#include <string>
#include <nlohmann/json.hpp>

#include "tcp_channel.hpp"
#include "client_searcher.hpp"

namespace ks {

ClientSearcher::ClientSearcher(int client_sock)
    : m_client_sock(client_sock)
{}

std::vector<std::pair<std::string, int32_t>> ClientSearcher::search(std::string token)
{    
    TcpChannel::send_msg(m_client_sock, token);
    std::string results = TcpChannel::recv_msg(m_client_sock);
    std::vector<std::pair<std::string, int32_t>> updated_results = deserializer(results);
    return updated_results;
}

std::vector<std::pair<std::string, int32_t>> ClientSearcher::deserializer(std::string json_str)
{
    std::vector<std::pair<std::string, int32_t>> results_vector;

    nlohmann::json json_res = nlohmann::json::parse(json_str);
    for (auto const& j_elm : json_res) {
        results_vector.push_back({j_elm["key"].get<std::string>(), j_elm["value"].get<int32_t>()});
    }

    return results_vector;  
}
 
} // namespace ks
