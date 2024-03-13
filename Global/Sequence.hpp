
/*

    TODO: Autoriser les sequence en plus des strings.
    TODO: Ajouter les foctions de 'complement inverse', 'transcription', 'retroTranscription'

    TODO: Compresser les caractéres utilisés dans la sequence

*/
#ifndef SEQUENCE_HPP
#define SEQUENCE_HPP

#include <string>
#include <iostream>
#include <set>
#include <map>
#include <tuple>
#include <array>
#include "Utilities.hpp"

class Sequence {
private:
    std::array<bool, 5> type;
    std::string seq;

    // --- --- Private attributes --- ---
    static std::map<char, char> legalDNA;
    static std::map<char, char> legalRNA;
    static std::map<char, char> bridgeDNA_RNA;
    static std::set<char> legalAmino;
    static std::set<char> validType;

protected:
    bool parseChar(char symbol, errorMods error_mod=display);

public:
    // --- --- Constructors --- ---
    Sequence(std::string sequence, char type, errorMods error_mod, bool finalis_type = true);
    Sequence()                                           : Sequence("", 'U', display, true) {};
    Sequence(std::string sequence, char type)            : Sequence(sequence, type, display) {};
    Sequence(std::string sequence, errorMods error_mod)  : Sequence(sequence, 'U', error_mod) {};
    Sequence(std::string sequence)                       : Sequence(sequence, 'U', display) {};


    // --- --- Utilities --- ---
    // --- Getters and equivalents ---
    const std::string & getSeq() const;
    char getType() const;
    std::array<bool, 5>  getTypeArray() const;

    size_t size() const;
    std::string toString() const;
    
    // --- Modify sequence ---
    void activeTypeResearch();
    void endTypeResearch();

    void insert(const std::string & sequence, size_t position, errorMods errorMod=display);
    void insert(const Sequence & sequence, size_t position, errorMods errorMod=display);
    void insert(const char & symbol, size_t position, errorMods errorMod=display);

    void insertFront(const std::string & sequence, errorMods errorMod=display);
    void insertBack(const std::string & sequence, errorMods errorMod=display);

    void insertFront(const Sequence & sequence, errorMods errorMod=display);
    void insertBack(const Sequence & sequence, errorMods errorMod=display);

    void insertFront(const char & sequence, errorMods errorMod=display);
    void insertBack(const char & sequence, errorMods errorMod=display);

    void erase(size_t start, size_t length);
    
    // --- --- Static Utilities --- ---
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
    static bool isNucleicSpecific(char symbol);
    static bool isValidType(char symbol);

    // --- Type ---
    static char readTypeArray(std::array<bool, 5> type, bool ignore_illegal=false);
    static std::array<bool, 5> readTypeChar(char type);
    static std::array<bool, 5> identifySymbolType(char symbol);

    static bool canBeRna(char type);
    static bool canBeDna(char type);
    static bool canBeAmino(char type);
    static bool canBeNucleic(char type);

    //
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
        bool search_mod = this->type[3];
        return (!search_mod);
    }
};

#endif