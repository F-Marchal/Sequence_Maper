#ifndef FASTAHEADER_HPP
#define FASTAHEADER_HPP

#include "../Global/Header.hpp"
#include "FastaRelated.hpp"
#include <string>
#include <map>
#include <tuple>
#include <functional>

class FastaHeader : public FastaRelated, public Header {
private:
    std::string identifier_format;
    std::map<std::string, std::string> identifier;

public:
    static void clear_string(std::string&);
    static std::string find_format(std::string text);

};



#endif