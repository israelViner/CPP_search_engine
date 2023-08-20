#ifndef CLIENT_SEARCHER_H
#define CLIENT_SEARCHER_H

#include <string>
#include <vector>

#include "searcher.hpp"

namespace ks {

class ClientSearcher : public Searcher
{
public:    
    explicit ClientSearcher(int client_sock);

    std::vector<std::pair<std::string, int32_t>> search(std::string token) override;

private:
    std::vector<std::pair<std::string, int32_t>> deserializer(std::string json_str); 

private:
    int m_client_sock;
};

} // namespace ks

#endif