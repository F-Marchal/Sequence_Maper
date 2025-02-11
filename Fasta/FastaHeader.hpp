#ifndef FASTAHEADER_HPP
#define FASTAHEADER_HPP

#include "../Global/Header.hpp"
#include "FastaRelated.hpp"
#include <string>
#include <map>
#include <tuple>
#include <functional>
#include <vector>
/**
 * @brief A header function that is supposed to be hubble to parse Header from Fasta file.
 * @warning THIS CLASS DO NOT FUNCTION YET.
 */

class FastaHeader : public FastaRelated, public Header {
private:
    /**
     * @brief Indicate the format of this Header ex : gb
     */
    std::string identifier_format;

    /**
     * @brief Contain information related to intermediateMakeFormatFromVector
     */
    std::map<std::string, std::string> identifier;

public:
    /**
     * @brief Construct a new Fasta Header object
     * @warning NOT IMPLEMENTED YET
     * @param raw_header Header from a text
     */

    FastaHeader(std::string raw_header);

    /**
     * @brief Construct a new Fasta Header object
     * @warning NOT IMPLEMENTED YET 
     */
     FastaHeader();

    /**
     * @brief Construct a new Fasta Header object
     * @warning NOT IMPLEMENTED YET
     * @param raw_header 
     */
    void load(std::string raw_header);
    
    /**
     * @brief Give a map that contain all informations related to this header
     * @return const std::map<std::string, std::string>& 
     */
    const std::map<std::string, std::string> & getIdentifiers();

    /**
     * @brief Five the header format (ex: gb)
     * @return std::string 
     */
    std::string getFormat();

    //
    static size_t findFirstWord(std::string text);     
    static void clearRawHeader(std::string& raw_header);
    static std::vector<std::string> cutRawHeader(std::string raw_header);
    static std::map<std::string, std::string> parseRawHeader(std::string raw_header);
    static std::map<std::string, std::string> parseRawHeader(std::vector<std::string>);

    static std::tuple<std::string, std::string> intermediateMakeFormatFromVector(std::vector<std::string> text_header, unsigned int min_size, std::string format);
    
    //
    static std::map<std::string, std::string> makeGenInfoBackboneIdHeader(std::string accession, std::string comments="");
    static std::map<std::string, std::string> parseGenInfoBackboneIdHeader(std::vector<std::string> text_header);
    static std::map<std::string, std::string> parseGenInfoBackboneIdHeader(std::string raw_header);

    static std::map<std::string, std::string> makeGenInfoBackboneMoltypeHeader(std::string accession, std::string comments="");
    static std::map<std::string, std::string> parseGenInfoBackboneMoltypeHeader(std::vector<std::string> text_header);
    static std::map<std::string, std::string> parseGenInfoBackboneMoltypeHeader(std::string raw_header);

    static std::map<std::string, std::string> makeGenInfoImportIdHeader(std::string accession, std::string comments="");
    static std::map<std::string, std::string> parseGenInfoImportIdHeader(std::vector<std::string> text_header);
    static std::map<std::string, std::string> parseGenInfoImportIdHeader(std::string raw_header);

    static std::map<std::string, std::string> makeGenInfoIntegratedDatabaseHeader(std::string accession, std::string comments="");
    static std::map<std::string, std::string> parseGenInfoIntegratedDatabaseHeader(std::vector<std::string> text_header);
    static std::map<std::string, std::string> parseGenInfoIntegratedDatabaseHeader(std::string raw_header);


    static std::map<std::string, std::string> makeLocalSequenceIdentifierHeader(std::string accession, std::string comments="");
    static std::map<std::string, std::string> parseLocalSequenceIdentifierHeader(std::vector<std::string> text_header);
    static std::map<std::string, std::string> parseLocalSequenceIdentifierHeader(std::string raw_header);

    //
    static std::map<std::string, std::string> makeGenbankHeader(std::string accession, std::string locus, std::string comments="");
    static std::map<std::string, std::string> parseGenbankHeader(std::vector<std::string> text_header);
    static std::map<std::string, std::string> parseGenbankHeader(std::string raw_header);
    
    static std::map<std::string, std::string> makeEMBLHeader(std::string accession, std::string locus, std::string comments="");
    static std::map<std::string, std::string> parseEMBLHeader(std::vector<std::string> text_header);
    static std::map<std::string, std::string> parseEMBLHeader(std::string raw_header);

    static std::map<std::string, std::string> makePIRHeader(std::string accession, std::string name, std::string comments="");
    static std::map<std::string, std::string> parsePIRHeader(std::vector<std::string> text_header);
    static std::map<std::string, std::string> parsePIRHeader(std::string raw_header);
    
    static std::map<std::string, std::string> makePIFHeader(std::string accession, std::string name, std::string comments="");
    static std::map<std::string, std::string> parsePIFHeader(std::vector<std::string> text_header);
    static std::map<std::string, std::string> parsePIFHeader(std::string raw_header);
    
    static std::map<std::string, std::string> makeSwissProtHeader(std::string accession, std::string name, std::string comments="");
    static std::map<std::string, std::string> parseSwissProtHeader(std::vector<std::string> text_header);
    static std::map<std::string, std::string> parseSwissProtHeader(std::string raw_header);
    
    static std::map<std::string, std::string> makeTrEMBLHeader(std::string accession, std::string name, std::string comments="");
    static std::map<std::string, std::string> parseTrEMBLHeader(std::vector<std::string> text_header);
    static std::map<std::string, std::string> parseTrEMBLHeader(std::string raw_header);
    
    static std::map<std::string, std::string> makeThirdPartyGenbankHeader(std::string accession, std::string name, std::string comments="");
    static std::map<std::string, std::string> parseThirdPartyGenbankHeader(std::vector<std::string> text_header);
    static std::map<std::string, std::string> parseThirdPartyGenbankHeader(std::string raw_header);
    
    static std::map<std::string, std::string> makeThirdPartyEMBLHeader(std::string accession, std::string name, std::string comments="");
    static std::map<std::string, std::string> parseThirdPartyEMBLHeader(std::vector<std::string> text_header);
    static std::map<std::string, std::string> parseThirdPartyEMBLHeader(std::string raw_header);
    
    static std::map<std::string, std::string> makeThirdPartyDDBJHeader(std::string accession, std::string name, std::string comments="");
    static std::map<std::string, std::string> parseThirdPartyDDBJHeader(std::vector<std::string> text_header);
    static std::map<std::string, std::string> parseThirdPartyDDBJHeader(std::string raw_header);
    
    static std::map<std::string, std::string> makePDBHeader(std::string accession, std::string name, std::string comments="");
    static std::map<std::string, std::string> parsePDBHeader(std::vector<std::string> text_header);
    static std::map<std::string, std::string> parsePDBHeader(std::string raw_header);
    
    static std::map<std::string, std::string> makeGNLHeader(std::string accession, std::string name, std::string comments="");
    static std::map<std::string, std::string> parseGNLHeader(std::vector<std::string> text_header);
    static std::map<std::string, std::string> parseGNLHeader(std::string raw_header);
    
    static std::map<std::string, std::string> makeNCBIRefSeqHeader(std::string accession, std::string name, std::string comments="");
    static std::map<std::string, std::string> parseNCBIRefSeqHeader(std::vector<std::string> text_header);
    static std::map<std::string, std::string> parseNCBIRefSeqHeader(std::string raw_header);
    
    static std::map<std::string, std::string> makePatentSHeader(std::string accession, std::string name, std::string comments="");
    static std::map<std::string, std::string> parsePatentSHeader(std::vector<std::string> text_header);
    static std::map<std::string, std::string> parsePatentSHeader(std::string raw_header);
    
    static std::map<std::string, std::string> makeDDBJHeader(std::string accession, std::string name, std::string comments="");
    static std::map<std::string, std::string> parseDDBJHeader(std::vector<std::string> text_header);
    static std::map<std::string, std::string> parseDDBJHeader(std::string raw_header);
    
    static std::map<std::string, std::string> makePatentLHeader(std::string country, std::string patent, std::string sequence_number, std::string comments="");
    static std::map<std::string, std::string> parsePatentLHeader(std::vector<std::string> text_header);
    static std::map<std::string, std::string> parsePatentLHeader(std::string raw_header);
    
    static std::map<std::string, std::string> makePreGrantPatentHeader(std::string country, std::string application_number, std::string sequence_number, std::string comments="");
    static std::map<std::string, std::string> parsePreGrantPatentHeader(std::vector<std::string> text_header);
    static std::map<std::string, std::string> parsePreGrantPatentHeader(std::string raw_header);
};



#endif