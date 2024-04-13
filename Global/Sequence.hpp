
/*
    Changements mineurs :
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
    enum IUPACMod {
    without     = 0,
    most        = 1, 
    all         = 2,
    };

    std::array<bool, 5> type;
    std::string seq;
    
    IUPACMod iupac;

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

    /**
     * @brief Main Constructor. Construct a new Sequence object
     * 
     * @param sequence          A string that represent a sequence of DNA / RNA / AMINO.
     * @param type              Specify type of this sequence. 'D'=DNA, 'R'=RNA, 'P'=Protein, 'N'=DNA and / or RNA 'U'=Unknown (Sequence will analyze chars in order to determine its type)
     * @param error_mod         See values inside Utilities::errorMods
     * @param finalis_type      Do this sequence will continue analyze chars in order to determine its type.
     */
    Sequence(std::string sequence, char type, errorMods error_mod, bool finalis_type = true);
    
    /**
     * @brief Default Constructor. Construct a new Sequence object. Equivalent to 
     * 
     */
    Sequence()                                           : Sequence("", 'U', display, true) {};
    Sequence(std::string sequence, char type)            : Sequence(sequence, type, display) {};
    Sequence(std::string sequence, errorMods error_mod)  : Sequence(sequence, 'U', error_mod) {};
    Sequence(std::string sequence)                       : Sequence(sequence, 'U', display) {};

    // --- --- Utilities --- ---
    // --- Getters and equivalents ---

    /**
     * @brief Get the sequence contain in this object
     * 
     * @return const std::string& The sequence contain in this object
     */
    const std::string & getSeq() const;

    /**
     * @brief Get a char that represent sequence type.
     * 
     * @return char 'D'=DNA, 'R'=RNA, 'P'=Protein, 'N'=DNA and / or RNA 'U'=Unspecified, 'Z'=Invalid type.
     */
    char getType() const;
    IUPACMod getIupac() const;
    const std::array<bool, 5> & getTypeArray() const;

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