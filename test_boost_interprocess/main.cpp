#include <boost/process.hpp>
#include <iostream>

using namespace std;

void testStringChild() {
    // std::setlocale(LC_ALL, "en_US.utf8");
    boost::process::ipstream ps;
    boost::process::child c(boost::process::search_path("curl"), "http://localhost:8000/data/wp_utf8.txt", boost::process::std_out > ps);  // "http://tarsenyss.narod.ru/"
    std::string token;
    while (/*c.running() &&*/ (ps >> token) /*&& !token.empty()*/) {
        std::cout << "token = " << token << std::endl;
    }
    c.wait();
}

void testWstringChild() {
    std::setlocale(LC_ALL, "en_US.utf8");
    boost::process::wipstream ps;
    boost::process::child c(boost::process::search_path("curl"), "bash.org", boost::process::std_out > ps);
    std::wstring token;
    while (c.running() && std::getline(ps, token) && !token.empty()) {
        std::wcout << "token = " << token << std::endl;
    }
    c.wait();
}

int main()
{
    testStringChild();
    return 0;
}
