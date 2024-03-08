
/*
    Ajouts futurs
        Methode pour verifier que deux sequences sont égales
        Support des << pour pour pouboir cout la class
        Traduction / retroTraduction des sequences
        



*/
#ifndef SEQUENCE_HPP
#define SEQUENCE_HPP

#include <string>
#include <iostream>
#include <set>
#include <map>
#include <tuple>

class Sequence {
private:
    std::string seq;
    char type;
    bool strict;

    static std::map<char, char> legalDNA;
    static std::map<char, char> legalRNA;
    static std::map<char, char> bridgeDNA_RNA;
    static std::set<char> legalAmino;

public:
    // --- --- --- Constructors --- --- --
    Sequence(std::string sequence, char mod, bool verbose);

    Sequence()                                          : Sequence("", 'U', false) {};
    Sequence(std::string sequence, char mod)            : Sequence(sequence, mod, false) {};
    Sequence(std::string sequence, bool verbose)        : Sequence(sequence, 'U', verbose) {};
    Sequence(std::string sequence)                      : Sequence(sequence, 'U', false) {};

    // --- --- --- Getter & Setters --- --- --


    void setSeq(std::string sequence, char mod, bool verbose);
    void setSeq(std::string sequence, char mod);
    void setSeq(std::string sequence, bool verbose);
    void setSeq(std::string sequence);
    std::string getSeq() const;

    char getType() const;
    bool getStrict() const;
    void updateStrict();
    void updateStrict(bool verbose);

    // --- --- --- Sequence edition --- --- --
    void insertSeq(size_t position, Sequence seq, bool verbose);
    void insertSeq(size_t position, std::string seq, bool verbose);
    void insertSeq(size_t position, Sequence seq);
    void insertSeq(size_t position, std::string seq);
    
    void eraseSeq(size_t index, size_t length);
    
    // dup
    bool canBeTranscribed();
    bool canBeRetroTranscribed();
    
    Sequence getTranscribedSequence(bool verbose=false);
    Sequence getRetroTranscribedSequence(bool verbose=false);
    Sequence getReverseComplement(bool verbose=false);

    // --- --- --- Utilities --- --- --
    size_t size() {return this->seq.size();}
    std::string toString() {return this->getSeq();};

    // --- statics ---
    static std::tuple<std::string, char, bool> ParseSeq(std::string sequence, char mod, bool verbose);

    static bool isLegalNucleic(char symbol);
    static bool isLegalAmino(char symbol);
    static bool isLegalSymbol(char symbol);
    static bool isDNA(char symbol);
    static bool isRNA(char symbol);
    static bool isDNASpecific(char symbol);
    static bool isRNASpecific(char symbol);

    static const std::map<char, char>& getLegalDNA();
    static const std::map<char, char>& getLegalRNA();
    static const std::set<char>&  getLegalAmino();
    static const  std::map<char, char>& getBridgeDNA_RNA();

    static std::string makeReverseComplement(const Sequence& seq, bool change_type=false, bool verbose=false);
    

};

#endif