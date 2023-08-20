#ifndef CONCRETE_SEARCHER_H
#define CONCRETE_SEARCHER_H

#include <string>
#include <vector>

#include "get_data.hpp"
#include "searcher.hpp"

namespace ks {

class ConcreteSearcher : public Searcher
{
public:    
    explicit ConcreteSearcher(GetData& db);

    std::vector<std::pair<std::string, int32_t>> search(std::string token) override;

private:
    GetData& m_db;
};

} // namespace ks

#endif