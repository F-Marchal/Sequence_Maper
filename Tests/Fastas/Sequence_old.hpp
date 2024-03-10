
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
    static std::set<char> validType;

    void addSeq(std::string sequence, size_t position, bool errorMod=false);


public:
    // --- --- --- Constructors --- --- --
    Sequence(std::string sequence, char type, bool errorMod);
    Sequence()                                          : Sequence("", 'U', false) {};
    Sequence(std::string sequence, char type)            : Sequence(sequence, type, false) {};
    Sequence(std::string sequence, bool errorMod)        : Sequence(sequence, 'U', errorMod) {};
    Sequence(std::string sequence)                      : Sequence(sequence, 'U', false) {};

    bool parseChar(char symbol, bool* dna_rna_amino_bool[3], bool errorMode=true);
    void PrepareRnaDnaAminoBool(bool* dna_rna_amino_bool[3]);

    // --- --- --- Getter & Setters --- --- --
    void setSeq(std::string sequence, char type, bool errorMod);
    void setSeq(std::string sequence, char type);
    void setSeq(std::string sequence, bool errorMod);
    void setSeq(std::string sequence);

    const std::string& getSeq() const;

    char getType() const;
    void guessAndSetType(bool* dna_rna_amino_bool[3]);
    
    // --- --- --- Sequence edition --- --- --
    void insertSeq(size_t position, const Sequence& seq, bool errorMod=false);
    void virtual insertSeq(size_t position, std::string seq, bool errorMod=false);
    void virtual eraseSeq(size_t index, size_t length);

    
    // --- --- Biological transformations --- ---
    bool canBeTranscribed() const;
    bool canBeRetroTranscribed() const;
    
    Sequence getTranscribedSequence(bool errorMod=false) const;
    Sequence getRetroTranscribedSequence(bool errorMod=false) const;
    Sequence getReverseComplement(bool errorMod=false) const;

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

    // ParseSeq should be replaced by stepParse.
    // stepParse should be private



    static char identifyChar(char symbol, bool errorType=false);
    static void RnaDnaAminoBoolManager(char type, char symbol, char symbol_type, bool* boolArray[3]);
    static char SequenceGuessType(bool* dna_rna_amino_bool[3]);

    static bool canBeRna(char type);
    static bool canBeDna(char type);
    static bool canBeAmino(char type);
    static bool canBeNucleic(char type);
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
    static bool isValidType(char symbol);

    // --- --- Getter --- --
    static const std::map<char, char>& getLegalDNA();
    static const std::map<char, char>& getLegalRNA();
    static const std::set<char>&  getLegalAmino();
    static const std::map<char, char>& getBridgeDNA_RNA();
    static const std::set<char>&  getValidType();

    // --- --- Biological transformations --- --
    static std::string makeReverseComplement(const Sequence& seq, bool change_type=false, bool errorMod=false);
    
   

};

#endif