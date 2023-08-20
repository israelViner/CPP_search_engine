#ifndef TCP_SEARCHER_H
#define TCP_SEARCHER_H

#include <string>
#include <vector>

#include "searcher.hpp"

namespace ks
{

class TcpSearcher
{
public:
    explicit TcpSearcher(Searcher& searcher);

    void search(int client_socket) const;

private:
    std::string serializer(std::vector<std::pair<std::string, int32_t>> results) const;

private:
    Searcher& m_searcher;
};

} // namespace ks

#endif