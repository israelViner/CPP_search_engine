#include <string>
#include <nlohmann/json.hpp>

#include "tcp_searcher.hpp"
#include "tcp_channel.hpp"
#include "searcher.hpp"


namespace ks {

TcpSearcher::TcpSearcher(Searcher& searcher)
    : m_searcher(searcher)
{}

void TcpSearcher::search(int client_socket) const
{
    while(true) {
        std::string msg = TcpChannel::recv_msg(client_socket);
        if (msg.empty()) {
            break;
        }
        auto results_pairs = m_searcher.search(msg);
        std::string json_str = serializer(results_pairs);
        TcpChannel::send_msg(client_socket, json_str);
    }
}

std::string TcpSearcher::serializer(std::vector<std::pair<std::string, int32_t>> results) const
{
    nlohmann::json json_res;
    for (const auto& [url, value] : results) {
        json_res.push_back({{"key", url}, {"value", value}});
    }

    return json_res.dump();
}

} // namespace ks
