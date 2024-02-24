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

    size_t split_point = findFirstWord(text_header[expected_size - 1]);
    return std::tuple{text_header[-1].substr(0, split_point), text_header[expected_size - 1].substr(split_point)};
}

// --- --- ---- --- --- --- --- --- 4 --- --- ---- --- --- --- --- ---


// --- --- ---- --- --- --- --- --- 3 --- --- ---- --- --- --- --- --- 
// --- ---- ---- ---- --- GenBank --- ---- ---- ---- --- 
std::map<std::string, std::string> FastaHeader::makePIRHeader(std::string accession, std::string locus, std::string comments) {
    std::map<std::string, std::string> final_map;
    final_map["Complete"] = "gb|" + accession + "|" + locus;
    final_map["Format"] = "gb";
    final_map["Comments"] = comments;
    final_map["accession"] = accession;
    final_map["locus"] = locus;

    return final_map;
}

std::map<std::string, std::string> FastaHeader::parsePIRHeader(std::vector<std::string> text_header) {
    std::tuple<std::string, std::string> temp_tup = intermediateMakeFormatFromVector(text_header, 3, "gb");
    return makePIRHeader(text_header[1], std::get<0>(temp_tup), std::get<1>(temp_tup));
}

std::map<std::string, std::string> FastaHeader::parsePIRHeader(std::string raw_header) {
    return parsePIRHeader(cutRawHeader(raw_header));
}

// --- ---- ---- ---- --- EMBL --- ---- ---- ---- --- 
std::map<std::string, std::string> FastaHeader::makePIRHeader(std::string accession, std::string locus, std::string comments) {
    std::map<std::string, std::string> final_map;
    final_map["Complete"] = "gb|" + accession + "|" + locus;
    final_map["Format"] = "gb";
    final_map["Comments"] = comments;
    final_map["accession"] = accession;
    final_map["locus"] = locus;

    return final_map;
}

std::map<std::string, std::string> FastaHeader::parsePIRHeader(std::vector<std::string> text_header) {
    std::tuple<std::string, std::string> temp_tup = intermediateMakeFormatFromVector(text_header, 3, "gb");
    return makePIRHeader(text_header[1], std::get<0>(temp_tup), std::get<1>(temp_tup));
}

std::map<std::string, std::string> FastaHeader::parsePIRHeader(std::string raw_header) {
    return parsePIRHeader(cutRawHeader(raw_header));
}

// --- ---- ---- ---- --- EMBL --- ---- ---- ---- --- 
std::map<std::string, std::string> FastaHeader::makeEMBLHeader(std::string accession, std::string locus, std::string comments) {
    std::map<std::string, std::string> final_map;
    final_map["Complete"] = "emb|" + accession + "|" + locus;
    final_map["Format"] = "emb";
    final_map["Comments"] = comments;
    final_map["accession"] = accession;
    final_map["locus"] = locus;

    return final_map;
}

std::map<std::string, std::string> FastaHeader::parseEMBLHeader(std::vector<std::string> text_header) {
    std::tuple<std::string, std::string> temp_tup = intermediateMakeFormatFromVector(text_header, 3, "emb");
    return makeEMBLHeader(text_header[1], std::get<0>(temp_tup), std::get<1>(temp_tup));
}

std::map<std::string, std::string> FastaHeader::parseEMBLHeader(std::string raw_header) {
    return parseEMBLHeader(cutRawHeader(raw_header));
}

// --- ---- ---- ---- --- PIR --- ---- ---- ---- --- 
std::map<std::string, std::string> FastaHeader::makePIRHeader(std::string accession, std::string locus, std::string comments) {
    std::map<std::string, std::string> final_map;
    final_map["Complete"] = "pir|" + accession + "|" + locus;
    final_map["Format"] = "pir";
    final_map["Comments"] = comments;
    final_map["accession"] = accession;
    final_map["locus"] = locus;

    return final_map;
}

std::map<std::string, std::string> FastaHeader::parsePIRHeader(std::vector<std::string> text_header) {
    std::tuple<std::string, std::string> temp_tup = intermediateMakeFormatFromVector(text_header, 3, "pir");
    return makePIRHeader(text_header[1], std::get<0>(temp_tup), std::get<1>(temp_tup));
}

std::map<std::string, std::string> FastaHeader::parsePIRHeader(std::string raw_header) {
    return parsePIRHeader(cutRawHeader(raw_header));
}

// --- ---- ---- ---- --- PIF --- ---- ---- ---- --- 
std::map<std::string, std::string> FastaHeader::makePIFHeader(std::string accession, std::string locus, std::string comments) {
    std::map<std::string, std::string> final_map;
    final_map["Complete"] = "pif|" + accession + "|" + locus;
    final_map["Format"] = "pif";
    final_map["Comments"] = comments;
    final_map["accession"] = accession;
    final_map["locus"] = locus;

    return final_map;
}

std::map<std::string, std::string> FastaHeader::parsePIFHeader(std::vector<std::string> text_header) {
    std::tuple<std::string, std::string> temp_tup = intermediateMakeFormatFromVector(text_header, 3, "pif");
    return makePIFHeader(text_header[1], std::get<0>(temp_tup), std::get<1>(temp_tup));
}

std::map<std::string, std::string> FastaHeader::parsePIFHeader(std::string raw_header) {
    return parsePIFHeader(cutRawHeader(raw_header));
}

// --- ---- ---- ---- --- SwissProt --- ---- ---- ---- --- 
std::map<std::string, std::string> FastaHeader::makeSwissProtHeader(std::string accession, std::string locus, std::string comments) {
    std::map<std::string, std::string> final_map;
    final_map["Complete"] = "sp|" + accession + "|" + locus;
    final_map["Format"] = "sp";
    final_map["Comments"] = comments;
    final_map["accession"] = accession;
    final_map["locus"] = locus;

    return final_map;
}

std::map<std::string, std::string> FastaHeader::parseSwissProtHeader(std::vector<std::string> text_header) {
    std::tuple<std::string, std::string> temp_tup = intermediateMakeFormatFromVector(text_header, 3, "sp");
    return makeSwissProtHeader(text_header[1], std::get<0>(temp_tup), std::get<1>(temp_tup));
}

std::map<std::string, std::string> FastaHeader::parseSwissProtHeader(std::string raw_header) {
    return parseSwissProtHeader(cutRawHeader(raw_header));
}


// --- ---- ---- ---- --- TrEMBL --- ---- ---- ---- --- 
std::map<std::string, std::string> FastaHeader::makeTrEMBLHeader(std::string accession, std::string locus, std::string comments) {
    std::map<std::string, std::string> final_map;
    final_map["Complete"] = "tr|" + accession + "|" + locus;
    final_map["Format"] = "tr";
    final_map["Comments"] = comments;
    final_map["accession"] = accession;
    final_map["locus"] = locus;

    return final_map;
}

std::map<std::string, std::string> FastaHeader::parseTrEMBLHeader(std::vector<std::string> text_header) {
    std::tuple<std::string, std::string> temp_tup = intermediateMakeFormatFromVector(text_header, 3, "tr");
    return makeTrEMBLHeader(text_header[1], std::get<0>(temp_tup), std::get<1>(temp_tup));
}

std::map<std::string, std::string> FastaHeader::parseTrEMBLHeader(std::string raw_header) {
    return parseTrEMBLHeader(cutRawHeader(raw_header));
}


// --- ---- ---- ---- --- ThirdPartyGenbank --- ---- ---- ---- --- 
std::map<std::string, std::string> FastaHeader::makeThirdPartyGenbankHeader(std::string accession, std::string locus, std::string comments) {
    std::map<std::string, std::string> final_map;
    final_map["Complete"] = "tpg|" + accession + "|" + locus;
    final_map["Format"] = "tpg";
    final_map["Comments"] = comments;
    final_map["accession"] = accession;
    final_map["locus"] = locus;

    return final_map;
}

std::map<std::string, std::string> FastaHeader::parseThirdPartyGenbankHeader(std::vector<std::string> text_header) {
    std::tuple<std::string, std::string> temp_tup = intermediateMakeFormatFromVector(text_header, 3, "tpg");
    return makeThirdPartyGenbankHeader(text_header[1], std::get<0>(temp_tup), std::get<1>(temp_tup));
}

std::map<std::string, std::string> FastaHeader::parseThirdPartyGenbankHeader(std::string raw_header) {
    return parseThirdPartyGenbankHeader(cutRawHeader(raw_header));
}

// --- ---- ---- ---- --- ThirdPartyEMBL --- ---- ---- ---- --- 
std::map<std::string, std::string> FastaHeader::makeThirdPartyEMBLHeader(std::string accession, std::string locus, std::string comments) {
    std::map<std::string, std::string> final_map;
    final_map["Complete"] = "tpe|" + accession + "|" + locus;
    final_map["Format"] = "tpe";
    final_map["Comments"] = comments;
    final_map["accession"] = accession;
    final_map["locus"] = locus;

    return final_map;
}

std::map<std::string, std::string> FastaHeader::parseThirdPartyEMBLHeader(std::vector<std::string> text_header) {
    std::tuple<std::string, std::string> temp_tup = intermediateMakeFormatFromVector(text_header, 3, "tpe");
    return makeThirdPartyEMBLHeader(text_header[1], std::get<0>(temp_tup), std::get<1>(temp_tup));
}

std::map<std::string, std::string> FastaHeader::parseThirdPartyEMBLHeader(std::string raw_header) {
    return parseThirdPartyEMBLHeader(cutRawHeader(raw_header));
}


// --- ---- ---- ---- --- ThirdPartyDDBJ --- ---- ---- ---- --- 
std::map<std::string, std::string> FastaHeader::makeThirdPartyDDBJHeader(std::string accession, std::string locus, std::string comments) {
    std::map<std::string, std::string> final_map;
    final_map["Complete"] = "tpd|" + accession + "|" + locus;
    final_map["Format"] = "tpd";
    final_map["Comments"] = comments;
    final_map["accession"] = accession;
    final_map["locus"] = locus;

    return final_map;
}

std::map<std::string, std::string> FastaHeader::parseThirdPartyDDBJHeader(std::vector<std::string> text_header) {
    std::tuple<std::string, std::string> temp_tup = intermediateMakeFormatFromVector(text_header, 3, "tpd");
    return makeThirdPartyDDBJHeader(text_header[1], std::get<0>(temp_tup), std::get<1>(temp_tup));
}

std::map<std::string, std::string> FastaHeader::parseThirdPartyDDBJHeader(std::string raw_header) {
    return parseThirdPartyDDBJHeader(cutRawHeader(raw_header));
}

// --- ---- ---- ---- --- PDB --- ---- ---- ---- --- 
std::map<std::string, std::string> FastaHeader::makePDBHeader(std::string accession, std::string locus, std::string comments) {
    std::map<std::string, std::string> final_map;
    final_map["Complete"] = "pdb|" + accession + "|" + locus;
    final_map["Format"] = "pdb";
    final_map["Comments"] = comments;
    final_map["accession"] = accession;
    final_map["locus"] = locus;

    return final_map;
}

std::map<std::string, std::string> FastaHeader::parsePDBHeader(std::vector<std::string> text_header) {
    std::tuple<std::string, std::string> temp_tup = intermediateMakeFormatFromVector(text_header, 3, "pdb");
    return makePDBHeader(text_header[1], std::get<0>(temp_tup), std::get<1>(temp_tup));
}

std::map<std::string, std::string> FastaHeader::parsePDBHeader(std::string raw_header) {
    return parsePDBHeader(cutRawHeader(raw_header));
}

// --- ---- ---- ---- --- GNL --- ---- ---- ---- --- 
std::map<std::string, std::string> FastaHeader::makeGNLHeader(std::string accession, std::string locus, std::string comments) {
    std::map<std::string, std::string> final_map;
    final_map["Complete"] = "gnl|" + accession + "|" + locus;
    final_map["Format"] = "gnl";
    final_map["Comments"] = comments;
    final_map["accession"] = accession;
    final_map["locus"] = locus;

    return final_map;
}

std::map<std::string, std::string> FastaHeader::parseGNLHeader(std::vector<std::string> text_header) {
    std::tuple<std::string, std::string> temp_tup = intermediateMakeFormatFromVector(text_header, 3, "gnl");
    return makeGNLHeader(text_header[1], std::get<0>(temp_tup), std::get<1>(temp_tup));
}

std::map<std::string, std::string> FastaHeader::parseGNLHeader(std::string raw_header) {
    return parseGNLHeader(cutRawHeader(raw_header));
}

// --- ---- ---- ---- --- NCBIRefSeq --- ---- ---- ---- --- 
std::map<std::string, std::string> FastaHeader::makeNCBIRefSeqHeader(std::string accession, std::string locus, std::string comments) {
    std::map<std::string, std::string> final_map;
    final_map["Complete"] = "ref|" + accession + "|" + locus;
    final_map["Format"] = "ref";
    final_map["Comments"] = comments;
    final_map["accession"] = accession;
    final_map["locus"] = locus;

    return final_map;
}

std::map<std::string, std::string> FastaHeader::parseNCBIRefSeqHeader(std::vector<std::string> text_header) {
    std::tuple<std::string, std::string> temp_tup = intermediateMakeFormatFromVector(text_header, 3, "ref");
    return makeNCBIRefSeqHeader(text_header[1], std::get<0>(temp_tup), std::get<1>(temp_tup));
}

std::map<std::string, std::string> FastaHeader::parseNCBIRefSeqHeader(std::string raw_header) {
    return parseNCBIRefSeqHeader(cutRawHeader(raw_header));
}


// --- ---- ---- ---- --- Patent --- ---- ---- ---- --- 
std::map<std::string, std::string> FastaHeader::makePatentHeader(std::string accession, std::string locus, std::string comments) {
    std::map<std::string, std::string> final_map;
    final_map["Complete"] = "pat|" + accession + "|" + locus;
    final_map["Format"] = "pat";
    final_map["Comments"] = comments;
    final_map["accession"] = accession;
    final_map["locus"] = locus;

    return final_map;
}

std::map<std::string, std::string> FastaHeader::parsePatentHeader(std::vector<std::string> text_header) {
    std::tuple<std::string, std::string> temp_tup = intermediateMakeFormatFromVector(text_header, 3, "pat");
    return makePatentHeader(text_header[1], std::get<0>(temp_tup), std::get<1>(temp_tup));
}

std::map<std::string, std::string> FastaHeader::parsePatentHeader(std::string raw_header) {
    return parsePatentHeader(cutRawHeader(raw_header));
}

// --- ---- ---- ---- --- DDBJ --- ---- ---- ---- --- 
std::map<std::string, std::string> FastaHeader::makeDDBJHeader(std::string accession, std::string locus, std::string comments) {
    std::map<std::string, std::string> final_map;
    final_map["Complete"] = "dbj|" + accession + "|" + locus;
    final_map["Format"] = "dbj";
    final_map["Comments"] = comments;
    final_map["accession"] = accession;
    final_map["locus"] = locus;

    return final_map;
}

std::map<std::string, std::string> FastaHeader::parseDDBJHeader(std::vector<std::string> text_header) {
    std::tuple<std::string, std::string> temp_tup = intermediateMakeFormatFromVector(text_header, 3, "dbj");
    return makeDDBJHeader(text_header[1], std::get<0>(temp_tup), std::get<1>(temp_tup));
}

std::map<std::string, std::string> FastaHeader::parseDDBJHeader(std::string raw_header) {
    return parseDDBJHeader(cutRawHeader(raw_header));
}

