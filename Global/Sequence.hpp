
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

    const std::string& getSeq() const;

    char getType() const;
    bool getStrict() const;
    void updateStrict();
    void updateStrict(bool verbose);

    // --- --- --- Sequence edition --- --- --
    void insertSeq(size_t position, const Sequence& seq, bool verbose=false);
    void virtual insertSeq(size_t position, std::string seq, bool verbose=false);
    
    void virtual eraseSeq(size_t index, size_t length);
    
    // --- --- Biological transformations --- ---
    bool canBeTranscribed() const;
    bool canBeRetroTranscribed() const;
    
    Sequence getTranscribedSequence(bool verbose=false) const;
    Sequence getRetroTranscribedSequence(bool verbose=false) const;
    Sequence getReverseComplement(bool verbose=false) const;

    // --- --- Utilities --- --
    size_t size() const {return this->seq.size();} 
    virtual std::string toString() const {return this->getSeq();} ;

    friend std::ostream& operator<<(std::ostream& os, const Sequence& seq_obj) {
        os << seq_obj.toString();
        return os;
    }

    // --- --- ---  statics --- --- --- 
    // --- --- Utilities --- --
    static std::tuple<std::string, char, bool> ParseSeq(std::string sequence, char mod, bool verbose);

    static bool isLegalNucleic(char symbol);
    static bool isLegalAmino(char symbol);
    static bool isLegalSymbol(char symbol);
    static bool isDNA(char symbol);
    static bool isRNA(char symbol);
    static bool isDNASpecific(char symbol);
    static bool isRNASpecific(char symbol);

    // --- --- Getter --- --
    static const std::map<char, char>& getLegalDNA();
    static const std::map<char, char>& getLegalRNA();
    static const std::set<char>&  getLegalAmino();
    static const std::map<char, char>& getBridgeDNA_RNA();

    // --- --- Biological transformations --- --
    static std::string makeReverseComplement(const Sequence& seq, bool change_type=false, bool verbose=false);
    
   

};

#endif