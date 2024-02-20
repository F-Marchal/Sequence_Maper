#ifndef FASTA_HPP
#define FASTA_HPP

#include "Sequence.hpp"
#include <fstream>
#include <string>
#include <iostream>
#include <stdexcept>
#include <set>
#include <vector>

class Fasta {
private:
    Sequence sequence;
    std::string raw_header;

    static std::set<char> legalMultiHeaderChar;
    static std::set<char> legalMonoHeaderChar;
    static std::set<char> legalCommentChar;
    static std::set<char> blankChar;

    static std::map<std::string, std::tuple<char, bool>> extension_types;


public:
    static std::tuple<std::string, std::string, std::map<size_t, std::string>>
    parseFasta(std::ifstream& file_flux, unsigned int& current_line, bool verbose);

    static std::vector<Fasta> loadFastaFromFile(std::string path);
    static std::vector<Fasta> loadFastaFromFile(std::string path, bool verbose);
    
    

    static bool isHeaderChar(char header_char);
    static bool isMonoHeaderChar(char header_char);
    static bool isMultiHeaderChar(char header_char);
    static bool isCommentChar(char comment_char);
    static bool isBlankChar(char blank);

    Fasta(std::string header, Sequence sequence);

    Sequence& getSequence() {return this->sequence;}
    bool Fasta::isKnownExtension(std::string ext);
    void setExtension(std::string extension);

    // TODO: Write Files
    // static void writeFasta(vector<Fasta>)
    void write(std::string name);
    void write(std::string name, bool append);
    


};
// TODO: Manage file extension
#endif