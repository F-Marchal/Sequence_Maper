
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

    static std::map<char, char> legalDNA;
    static std::map<char, char> legalRNA;
    static std::map<char, char> bridgeDNA_RNA;
    static std::set<char> legalAmino;
    static std::set<char> validMod;

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
    void updateStrict();

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
    size_t size() const; 
    virtual std::string toString() const;


    // --- --- Overloading operator --- --
    friend std::ostream& operator<<(std::ostream& os, const Sequence& seq_obj) {
        os << seq_obj.toString();
        return os;
    }

    virtual bool operator==(const Sequence& other) const {
        return this->seq == other.getSeq();
    }

    bool operator>(const Sequence& other) const {
        return this->size() > other.size();
    }
    bool operator>=(const Sequence& other) const {
        return this->size() >= other.size();
    }
    bool operator<(const Sequence& other) const {
        return this->size() < other.size();
    }
    bool operator<=(const Sequence& other) const {
        return this->size() <= other.size();
    }

    operator bool() const {
        return (this->type != 'U');
    }

    // --- --- ---  statics --- --- --- 
    // --- --- Utilities --- --
    static std::tuple<std::string, char> ParseSeq(std::string sequence, char mod, bool errorMode=true, bool symbolErrorMode=false);
    
    // ParseSeq should be replaced by stepParse.
    // stepParse should be private
    void stepParser(char symbol, char mod, bool errorMode=true, bool symbolErrorMode=false, bool flush=false);


    static char identifyChar(char symbol, bool errorMode=false);
    static void RnaDnaAminoBoolManager(char mod, char symbol, char symbol_mod, bool (&boolArray)[3]);
    static char SequenceGuessType(const bool (&boolArray)[3]);

    static bool canBeRna(char mod);
    static bool canBeDna(char mod);
    static bool canBeAmino(char mod);
    static bool canBeNucleic(char mod);
    static bool isLegalNucleic(char symbol);
    static bool isLegalAmino(char symbol);
    static bool isLegalSymbol(char symbol);
    static bool isDNA(char symbol);
    static bool isRNA(char symbol);
    static bool isAmino(char symbol);
    static bool isNucleic(char symbol);
    static bool isDnaSpecificNucleotide(char nucleic);
    static bool isRnaSpecificNucleotide(char nucleic);
    static bool isAminoSpecific(char symbol);
    static bool isValidMod(char symbol);

    // --- --- Getter --- --
    static const std::map<char, char>& getLegalDNA();
    static const std::map<char, char>& getLegalRNA();
    static const std::set<char>&  getLegalAmino();
    static const std::map<char, char>& getBridgeDNA_RNA();
    static const std::set<char>&  getValidMod();

    // --- --- Biological transformations --- --
    static std::string makeReverseComplement(const Sequence& seq, bool change_type=false, bool verbose=false);
    
   

};

#endif