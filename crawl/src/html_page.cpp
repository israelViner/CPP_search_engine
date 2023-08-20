#include <sstream>
#include <string>
#include <curlpp/cURLpp.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/Infos.hpp>

#include "html_page.hpp"
#include "request_exceptions.hpp"

namespace ks {

HTMLPage::HTMLPage(std::string const& url, curlpp::Easy& request)
{
    std::ostringstream os;
    request.setOpt(cURLpp::options::Url(url));
    request.setOpt(cURLpp::options::WriteStream(&os));
    request.setOpt(cURLpp::options::FollowLocation(true));
    try {
        request.perform();
	}
	catch(curlpp::RuntimeError& e) {
		throw ComunicationExceptions(std::string(std::string("curlpp throwed curlpp::RuntimeError: ") + e.what()));
    }
    int status_code = curlpp::infos::ResponseCode::get(request);
    if (status_code / 100 != 2) {
        throw BrokenUrlExceptions(std::string("HTTP status code for: ") + url + "\nis: " + std::to_string(status_code));
    }
    
    m_html = os.str();
}
	
std::string const& HTMLPage::get_html() const
{
    return m_html;
}

} // namespace ks
