#include "FastaHeader.hpp"
#include <string>
#include <iostream>
#include <stdexcept>
#include <map>
#include <tuple>
#include <vector>
// Header can not have " " inside theirs pipes 

void FastaHeader::clearRawHeader(std::string& raw_header) {
    size_t i = 0;
    while (i < raw_header.size() && (isHeaderChar(raw_header[i]) || isBlankChar(raw_header[i]))){
        i += 1;
    }

    if (i != 0) {
        raw_header.erase(0, i);
    }
}
size_t FastaHeader::findFirstWord(std::string text) {
    if (text.size() == 0) {
        return 0;
    }

    size_t i = 0;
    while (i < text.size() && !isBlankChar(text[i])) {
        i += 1; 
    }
    
    return i;
}

std::vector<std::string> FastaHeader::cutRawHeader(std::string raw_header) {
    size_t i = 0;
    std::vector<std::string> text_subparts;
    std::string current_part = "";

    clearRawHeader(raw_header);
    for (char symbols : raw_header) {
        if (symbols == '|') {
            text_subparts.push_back(current_part);
            current_part = "";
        } else {
            current_part += symbols;
        }
        
    }
    text_subparts.push_back(current_part);
    
    return text_subparts;
 }



std::map<std::string, std::string> FastaHeader::parseRawHeader(std::vector<std::string> cut_raw_header) {
    std::string format;
    format = cut_raw_header[0];

};

std::map<std::string, std::string> FastaHeader::parseRawHeader(std::string raw_header) {return parseRawHeader(cutRawHeader(raw_header));}

// 
std::tuple<std::string, std::string> FastaHeader::intermediateMakeFormatFromVector(std::vector<std::string> text_header, 
    unsigned int expected_size, std::string format) {
    // Factorise the commun part of functions
    if (expected_size <= 1) {
         throw std::invalid_argument("expected_size should be greater or equal to 2. Got : " + std::to_string(expected_size));
    }

    if (text_header.size() != expected_size) {
        throw std::invalid_argument(std::to_string(expected_size) + " items are expected in order to parse a '" + format + "' header. Got : " + std::to_string(text_header.size()));
    
    } else if (text_header[0] != format) {
        throw std::invalid_argument("Wrong format identifier expected : '" + format + "' got : '" + text_header[0] + "'.");
    }

    size_t split_point = findFirstWord(text_header[-1]);
    return std::tuple{text_header[-1].substr(0, split_point), text_header[-1].substr(split_point)};
}

// --- ---- ---- ---- --- GenBank --- ---- ---- ---- --- 
std::map<std::string, std::string> FastaHeader::makeGenbankHeader(std::string accession, std::string locus, std::string comments) {
    std::map<std::string, std::string> final_map;
    final_map["Complete"] = "gb|" + accession + "|" + locus;
    final_map["Format"] = "gb";
    final_map["Comments"] = comments;
    final_map["accession"] = accession;
    final_map["locus"] = locus;

    return final_map;
}

std::map<std::string, std::string> FastaHeader::parseGenbankHeader(std::vector<std::string> text_header) {
    std::tuple<std::string, std::string> temp_tup = intermediateMakeFormatFromVector(text_header, 3, "gb");
    return makeGenbankHeader(text_header[1], std::get<0>(temp_tup), std::get<1>(temp_tup));
}

std::map<std::string, std::string> FastaHeader::parseGenbankHeader(std::string raw_header) {
    return parseGenbankHeader(cutRawHeader(raw_header));
}