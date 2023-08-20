#include <string>
#include <vector>
#include <curlpp/Options.hpp>
#include <gumbo.h>

#include "bin_separator.hpp"
#include "page_db.hpp"
#include "string_cleaner.hpp"
#include "html_parser.hpp"

namespace ks {

static void bin_words(std::vector<std::string> words, PageDB& data)
{
    for (auto const& word : words) {
        if (data.get_data_words()[word] > 0) {
           data.get_data_words()[word] += 1;
        } else {
            data.get_data_words()[word] = 1;
        }
    }
}

static void bin_links(std::vector<std::string> links, PageDB& data)
{
    for (auto const& link : links) {
        if (data.get_data_links()[link] > 0) {
           data.get_data_links()[link] += 1;
        } else {
            data.get_data_links()[link] = 1;
        }
    }
}

PageDB bin_separator(std::string const& url, curlpp::Easy& request, GumboOutput* gumbo_output)
{
    PageDB data(url);

    try {
        HTMLParser html(url, request); 
        std::string txt = html.clean_text(gumbo_output);
        clean_string(txt);
        std::vector<std::string> words = split_string(txt);
        bin_words(words, data);

        std::vector<std::string> links = html.get_links(gumbo_output);
        bin_links(links, data);
	}
	catch(curlpp::RuntimeError& e) {
		std::cout << e.what() << std::endl;
	}
	catch(curlpp::LogicError& e) {
		std::cout << e.what() << std::endl;
	}  

    return data;
}

} // namespace ks