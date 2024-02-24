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
    static std::map< 
                    std::tuple<
                            std::string, 
                            size_t
                            >, 
                    std::function<void()>
                    > header_parsers; 

    //  std::function<std::string()>

public:
    static size_t findFirstWord(std::string text);     
    static void clearRawHeader(std::string& raw_header);
    static std::vector<std::string> cutRawHeader(std::string raw_header);
    static std::map<std::string, std::string> parseRawHeader(std::string raw_header);
    static std::map<std::string, std::string> parseRawHeader(std::vector<std::string>);

    static std::tuple<std::string, std::string> intermediateMakeFormatFromVector(std::vector<std::string> text_header, unsigned int min_size, std::string format);
    static std::map<std::string, std::string> makeGenbankHeader(std::string accession, std::string locus, std::string comments="");
    static std::map<std::string, std::string> parseGenbankHeader(std::vector<std::string> text_header);
    static std::map<std::string, std::string> parseGenbankHeader(std::string raw_header);


    FastaHeader() {this->identifier_format="";}


};



#endif