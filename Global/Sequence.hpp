#ifndef SEQUENCE_HPP
#define SEQUENCE_HPP


#include <string>
#include <iostream> // pour cout/endl/..
#include <set>
#include <map>
#include <tuple>

class Sequence {
private:
    std::string seq;
    char type;
    bool strict;

    static std::set<char> legalNucleic;
    static std::set<char> dnaSpecific;
    static std::set<char> rnaSpecific;
    static std::set<char> legalAmino;

public:
    // --- --- --- Getter & Setters --- --- --
    std::string getSeq() {return this->seq;};
    char getType() {return this->type;};
    bool getStrict() {return this->strict;};

    std::string toString() {return this->getSeq();};

    // --- --- --- Constructors --- --- --
    Sequence() : Sequence("", 'U', false) {};
    Sequence(std::string sequence, char mod, bool verbose);
    Sequence(std::string sequence, char mod) : Sequence(sequence, mod, false) {};
    Sequence(std::string sequence, bool verbose) : Sequence(sequence, 'U', verbose) {};
    Sequence(std::string sequence) : Sequence(sequence, 'U', false) {};

    // --- --- --- Methods --- --- --
    size_t size() {return this->seq.size();}

    // --- statics ---
    static std::tuple<std::string, char, bool> ParseSeq(std::string sequence, char mod, bool verbose);
    static bool isLegalNucleic(char symbol);
    static bool isLegalAmino(char symbol);
    static bool isLegalSymbol(char symbol);
    static bool isDnaSpecific(char symbol);
    static bool isRnaSpecific(char symbol);


};

#endif