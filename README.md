# Search Engine Project

In this project, I implemented a search engine system, which includes building a database by crawling URLs and performing various types of search queries on the data. Search results are sorted by relevance, determined by the number of occurrences of the search terms on the web page. The search can also be performed over the network using the TCP protocol.

### Architecture:
In planning the project, efforts were made to separate the various classes as much as possible using interfaces so that object transfer is done only through interfaces. Several design patterns were also used, including singleton, factory, command, and proxy.

### The project is divided into several modules:

- The **data** module consists of the **database** itself, which inherits from two different interfaces: **set_data** and **get_data**, which provide precise access to building and retrieving data from the database.

- The **crawl** module encompasses the entire area of building the database. At the beginning of the process, the **crawler** class receives from the **configuration** file the URLs, the number of pages the software is requested to scan, and other various conditions, and iteratively performs the crawling process. At each stage, one web page is sent for analysis and data processing.

- The **search** module handles the search area. The software supports three different types of search: search by a single word, search by multiple words, and search when certain words are not present. In the first stage, a **searcher** object is created, loaded with the relevant query, and passed to the **search_factory** class, which identifies which search type each query belongs to and instantiates the appropriate search class accordingly.

- In order to enable receiving queries from remote servers, the TCP module was built, which is divided into **client_tcp** and **server_tcp**, and a complete server-client module was implemented to enable bidirectional data transfer from the client to the server and vice versa. Using the proxy pattern, the **TUI** interface creates a suitable **client_searcher** object, which is unique in that it does not perform the query itself, but sends the query via the TCP protocol to the **tcp_searcher** object, which performs the query and returns the results through the network protocol.

