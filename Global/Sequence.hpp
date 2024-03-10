
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
    char type;
    std::string seq;
    
    // --- --- Private attributes --- ---
    static std::map<char, char> legalDNA;
    static std::map<char, char> legalRNA;
    static std::map<char, char> bridgeDNA_RNA;
    static std::set<char> legalAmino;
    static std::set<char> validType;

    // --- --- Private Methods --- ---
    void addSeq(std::string sequence, size_t position, bool errorMod=false);


public:
    // --- --- Constructors and parsers --- ---
     // --- Constructors ---
    Sequence(std::string sequence, char type, bool errorMod);
    Sequence()                                           : Sequence("", 'U', false) {};
    Sequence(std::string sequence, char type)            : Sequence(sequence, type, false) {};
    Sequence(std::string sequence, bool errorMod)        : Sequence(sequence, 'U', errorMod) {};
    Sequence(std::string sequence)                       : Sequence(sequence, 'U', false) {};

    // --- Parsers ---
    bool parseChar(char symbol, bool* dna_rna_amino_bool[3], bool errorMode=true);
    void PrepareRnaDnaAminoBool(bool* dna_rna_amino_bool[3]);
    void guessAndSetType(bool* dna_rna_amino_bool[3]);
    
    // --- --- Static Utilities --- ---
    // --- Sequence parsing ---
    static char identifyChar(char symbol, bool errorType=false);
    static void RnaDnaAminoBoolManager(char type, char symbol, char symbol_type, bool* boolArray[3]);
    static char SequenceGuessType(bool* dna_rna_amino_bool[3]);

    // --- Symbols ---
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

    // --- Type ---
    static bool canBeRna(char type);
    static bool canBeDna(char type);
    static bool canBeAmino(char type);
    static bool canBeNucleic(char type);

};

#endif