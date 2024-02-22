#ifndef FASTA_HPP
#define FASTA_HPP

#include "FastaSequence.hpp"
#include <fstream>
#include <string>
#include <iostream>
#include <stdexcept>
#include <set>
#include <vector>

class Fasta {
private:
    FastaSequence sequence;
    std::string header;

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
    
    std::string getCleanSequence(unsigned int word_size, unsigned int paragraph_size) {return getCleanSequence(word_size, paragraph_size, false);};
    std::string getCleanSequence(unsigned int word_size, unsigned int paragraph_size, bool comments);

    std::string getHeader() {return this->header;}

    static bool isHeaderChar(char header_char);
    static bool isMonoHeaderChar(char header_char);
    static bool isMultiHeaderChar(char header_char);
    static bool isCommentChar(char comment_char);
    static bool isBlankChar(char blank);

    Fasta(std::string header, FastaSequence& sequence);
    FastaSequence& getSequence() {return this->sequence;}
    

    // TODO: Write Files
    // static void writeFasta(vector<Fasta>)
    /*
    void write(std::string path);
    void write(std::string path, bool append, bool comments);
    void write(std::string path, unsigned int word_size, unsigned int paragraph_size);
    void write(std::string path, unsigned int word_size, unsigned int paragraph_size, bool comments);
    */
    void write(std::string path, bool append, unsigned int word_size, unsigned int paragraph_size, bool comments);
    void write(std::vector<Fasta> fasta_vector, std::string path, unsigned int word_size=10, unsigned int paragraph_size=6, bool comments=true);
    
    //
    void setHeader(std::string header) {
        this->header = header;
    }

    
};
// TODO: Manage file extension
#endif