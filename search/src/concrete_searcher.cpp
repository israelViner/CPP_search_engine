#include <string>
#include <vector>

#include "get_data.hpp"
#include "searcher.hpp"
#include "concrete_searcher.hpp"
#include "search_factory.hpp"

namespace ks {

ConcreteSearcher::ConcreteSearcher(GetData& db)
    : m_db(db)
{}

std::vector<std::pair<std::string, int32_t>> ConcreteSearcher::search(std::string token)
{
    auto search_ = SearchFactory::create_searcher(token, m_db);
    std::vector<std::pair<std::string, int32_t>> results = search_->search();
    return results;
}


} // namespace ks
