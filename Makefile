CXX = g++
CC = $(CXX)

CXXFLAGS = -Wall -pedantic -std=c++17
CXXFLAGS +=  -Werror
#CXXFLAGS += -g3

CPPFLAGS =  -I ./includes -I ./src -I ./server_tcp/src \
            -I ./server_tcp/includes -I ./client_tcp/src \
            -I ./client_tcp/includes -I ./server_tcp/includes \
            -I ./exceptions/includes -I ./search/src -I ./search/includes \
            -I ./crawl/src -I ./crawl/includes \
            -I ./data_base/src -I ./data_base/includes

LDLIBS = -lgumbo -lcurl -lcurlpp
# -lpthreads

SERVER_FILES = main_server.o crawl/src/html_page.o \
               crawl/src/html_parser.o crawl/src/string_cleaner.o \
               crawl/src/fix_url.o crawl/src/bin_separator.o \
               crawl/src/crawler.o search/src/search_word.o \
               search/src/search_several_words.o search/src/search_negative_words.o \
               search/src/search_factory.o search/src/concrete_searcher.o data_base/src/db.o \
               crawl/src/page_db.o data_base/src/update_db.o \
               src/configurations.o src/tui.o server_tcp/src/tcp_listener.o \
               server_tcp/src/tcp_channel.o server_tcp/src/tcp_searcher.o \
               client_tcp/src/client_searcher.o

CLIENT_FILES = main_client.o client_tcp/src/client_searcher.o client_tcp/src/client_tcp.o \
               client_tcp/src/comunication_tcp.o client_tcp/src/client_searcher.o \
               src/tui.o server_tcp/src/tcp_channel.o


main_server : $(SERVER_FILES)

main_client : $(CLIENT_FILES)

main_server.o: main_server.cpp data_base/includes/db.hpp \
               includes/configurations.hpp exceptions/includes/exceptions.hpp \
               crawl/includes/crawler.hpp search/includes/concrete_searcher.hpp \
               includes/tui.hpp server_tcp/includes/tcp_listener.hpp \
               server_tcp/includes/tcp_searcher.hpp

main_client.o : main_client.cpp includes/tui.hpp \
                client_tcp/includes/client_tcp.hpp client_tcp/includes/client_searcher.hpp \
                exceptions/includes/tcp_exceptions.hpp

crawl/src/html_page.o : crawl/src/html_page.cpp crawl/includes/html_page.hpp \
                        exceptions/includes/request_exceptions.hpp
crawl/src/html_parser.o : crawl/src/html_parser.cpp crawl/includes/html_parser.hpp \
                          crawl/includes/html_page.hpp crawl/includes/fix_url.hpp
crawl/src/string_cleaner.o : crawl/src/string_cleaner.cpp crawl/includes/string_cleaner.hpp
crawl/src/fix_url.o : crawl/src/fix_url.cpp crawl/includes/fix_url.hpp
crawl/src/bin_separator.o : crawl/src/bin_separator.cpp crawl/includes/bin_separator.hpp \
                            crawl/includes/html_parser.hpp crawl/includes/string_cleaner.hpp
crawl/src/crawler.o : crawl/src/crawler.cpp crawl/includes/crawler.hpp data_base/includes/db.hpp \
                crawl/includes/bin_separator.hpp includes/configurations.hpp \
				data_base/includes/set_data.hpp data_base/includes/update_db.hpp
crawl/src/page_db.o : crawl/src/page_db.cpp crawl/includes/page_db.hpp

search/src/search_word.o : search/src/search_word.cpp search/includes/search_word.hpp \
                           search/includes/search.hpp data_base/includes/get_data.hpp
search/src/search_several_words.o : search/src/search_several_words.cpp search/includes/search_several_words.hpp \
                                    search/includes/search.hpp data_base/includes/get_data.hpp search/includes/search_word.hpp
search/src/search_negative_words.o : search/src/search_negative_words.cpp search/includes/search_negative_words.hpp \
                                     search/includes/search.hpp data_base/includes/get_data.hpp \
                                     search/includes/search_several_words.hpp search/includes/search_word.hpp
search/src/search_factory.o : search/src/search_factory.cpp search/includes/search_factory.hpp \
                              search/includes/search.hpp data_base/includes/get_data.hpp
search/src/concrete_searcher.o : search/src/concrete_searcher.cpp search/includes/concrete_searcher.hpp \
                                 search/includes/searcher.hpp data_base/includes/get_data.hpp search/includes/search_factory.hpp

data_base/src/db.o : data_base/src/db.cpp data_base/includes/db.hpp data_base/includes/set_data.hpp \
                     data_base/includes/get_data.hpp
data_base/src/update_db.o : data_base/src/update_db.cpp data_base/includes/update_db.hpp crawl/includes/page_db.hpp

src/configurations.o : src/configurations.cpp includes/configurations.hpp
src/tui.o : src/tui.cpp includes/tui.hpp search/includes/search_factory.hpp search/includes/concrete_searcher.hpp \
            data_base/includes/get_data.hpp client_tcp/includes/client_searcher.hpp

server_tcp/src/tcp_listener.o : server_tcp/src/tcp_listener.cpp server_tcp/includes/tcp_listener.hpp \
                                exceptions/includes/tcp_exceptions.hpp
server_tcp/src/tcp_channel.o : server_tcp/src/tcp_channel.cpp server_tcp/includes/tcp_channel.hpp 
server_tcp/src/tcp_searcher.o : server_tcp/src/tcp_searcher.cpp server_tcp/includes/tcp_searcher.hpp

client_tcp/src/client_searcher.o : client_tcp/src/client_searcher.cpp client_tcp/includes/client_searcher.hpp 
client_tcp/src/client_tcp.o : client_tcp/src/client_tcp.cpp client_tcp/includes/client_tcp.hpp client_tcp/includes/comunication_tcp.hpp
client_tcp/src/comunication_tcp.o : client_tcp/src/comunication_tcp.cpp client_tcp/includes/comunication_tcp.hpp
client_tcp/src/client_searcher.o : client_tcp/src/client_searcher.cpp client_tcp/includes/client_searcher.hpp server_tcp/includes/tcp_channel.hpp search/includes/searcher.hpp

clean: 
	$(RM) $(CLIENT_FILES) $(SERVER_FILES) main_client main_server
