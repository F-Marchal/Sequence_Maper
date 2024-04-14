
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
#include <random> 
#include "Utilities.hpp"
#include "BitVector.hpp"
class Sequence {
public:
    enum IUPACMod {
    basic       = 0,
    most        = 1, 
    all         = 2,
    };

    class SequenceSymbol {
    private:
        std::string _replacement;
        char _symbol;
        Sequence::IUPACMod _iupac;

    public:
        SequenceSymbol(char symbol, std::string replacement, Sequence::IUPACMod iupac) {
            this->_symbol = (char) std::toupper(symbol);
            this->_replacement = replacement;
            this->_iupac = iupac;
        }

        bool isUsableIn(IUPACMod iupac) const {
            return (iupac >= this->_iupac);
        }

        char getReplacementSymbol() const {
            return randChar(this->_replacement);
        }

        char getValue() const {
            return this->_symbol;
        }

        char get(Sequence::IUPACMod iupac) const {
            if (this->isUsableIn(iupac)) {
                return this->_symbol ; 
            } else {
                return this->getReplacementSymbol();
            }
        }

        operator char() const {
            return this->_symbol;
        }


        operator std::string() const {
            return std::string(1, this->_symbol);
        }

        std::string toString() const {
            return std::to_string(this->_symbol);
        }

        friend std::ostream& operator<<(std::ostream& os, const Sequence::SequenceSymbol& symbol) {
            os << symbol.toString();
            return os;
        }


    };
    
private:


    std::array<bool, 5> type;
    BitVector seq;
    char _encoding_type;
    
    Sequence::IUPACMod _iupac;

    // --- --- Private attributes --- ---
    static const std::map<char, Sequence::SequenceSymbol> legalDNA;
    static const std::map<char, Sequence::SequenceSymbol> legalRNA;
    static const std::map<char, Sequence::SequenceSymbol> legalAmino;
    static std::set<char> validType;

protected:
    char parseChar(char symbol, errorMods error_mod=display);

public:
    class SequenceIterator {
        private:
            const Sequence& _sequence;
            size_t _index;

        public:
            SequenceIterator(const Sequence& seq, size_t index) : _sequence(seq), _index(index) {}

            // Overload the dereference operator to access the value
            int operator*() const {
                return this->_sequence[this->_index];
            }

            // Overload the pre-increment operator to move to the next element
            SequenceIterator& operator++() {
                ++this->_index;
                return *this;
            }

            // Overload the inequality operator
            bool operator!=(const SequenceIterator& other) const {
                return this->_index != other.getIndex();
            }

            size_t getIndex() const {
                return this->_index;
            }
            const Sequence & GetSequence() const {
                return this->_sequence;
            }
    };

    // Begin and end functions to get iterators
    SequenceIterator begin() const {
        return SequenceIterator(*this, 0);
    }

    SequenceIterator end() const {
        return SequenceIterator(*this, this->size());
    }

    // --- --- Constructors --- ---

    /**
     * @brief Main Constructor. Construct a new Sequence object
     * 
     * @param sequence          A string that represent a sequence of DNA / RNA / AMINO.
     * @param type              Specify type of this sequence. 'D'=DNA, 'R'=RNA, 'P'=Protein, 'N'=DNA and / or RNA 'U'=Unknown (Sequence will analyze chars in order to determine its type)
     * @param error_mod         See values inside Utilities::errorMods
     * @param iupac             
     * @param finalis_type      Do this sequence will continue analyze chars in order to determine its type.
     */
    Sequence(const std::string & sequence, char type,           IUPACMod iupac=most, errorMods error_mod=raise, bool finalis_type=true);
    
    /**
     * @brief Default Constructor. Construct a new Sequence object. Equivalent to 
     * 
     */
    Sequence(                                           IUPACMod iupac=most, errorMods error_mod=raise, bool finalis_type=false) : Sequence("", 'U', iupac, error_mod, finalis_type) {};
    Sequence(std::string sequence,                      IUPACMod iupac=most, errorMods error_mod=raise, bool finalis_type=true)  : Sequence(sequence, 'U', iupac, error_mod, finalis_type) {};
    
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
    char getEncodingType() const;
    Sequence::IUPACMod getIupac() const;
    const std::array<bool, 5> & getTypeArray() const;

    size_t size() const;
    
    static Sequence::SequenceSymbol getSequenceSymbol(char symbol, char type);

    // --- Modify sequence ---
    void activeTypeResearch();
    void endTypeResearch();

    void insert(const std::string & sequence, size_t position, errorMods errorMod=display);
    void insert(const char & symbol, size_t position, errorMods errorMod=display);

    void insertFront(const std::string & sequence, errorMods errorMod=display);
    void insertBack(const std::string & sequence, errorMods errorMod=display);

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

    static size_t elementMaxSize(char encoding_type, Sequence::IUPACMod iupac) {
        return translationTab(encoding_type, iupac, false, ignore).size();
    }

    static const std::map<char, char> & translationTab (char encoding_type, Sequence::IUPACMod iupac, bool reverse=false, errorMods error_mod=raise) {
        if (encoding_type == 'Z') {
            encoding_type = 'U';
        }
        static std::map<Sequence::IUPACMod, std::map<char, char>> U_encoding;
        static std::map<Sequence::IUPACMod, std::map<char, char>> N_encoding;
        static std::map<Sequence::IUPACMod, std::map<char, char>> R_encoding;
        static std::map<Sequence::IUPACMod, std::map<char, char>> D_encoding;
        static std::map<Sequence::IUPACMod, std::map<char, char>> P_encoding;
        static std::map<Sequence::IUPACMod, std::map<char, char>> U_rev_encoding;
        static std::map<Sequence::IUPACMod, std::map<char, char>> N_rev_encoding;
        static std::map<Sequence::IUPACMod, std::map<char, char>> R_rev_encoding;
        static std::map<Sequence::IUPACMod, std::map<char, char>> D_rev_encoding;
        static std::map<Sequence::IUPACMod, std::map<char, char>> P_rev_encoding;

        if (encoding_type == 'U') {
            if (U_encoding.find(iupac) == U_encoding.end()) {
                fillCodeMap(U_encoding, U_rev_encoding, legalDNA, iupac);
                fillCodeMap(U_encoding, U_rev_encoding, legalRNA, iupac);
                fillCodeMap(U_encoding, U_rev_encoding, legalAmino, iupac);
            }

            if (!reverse) {
                return U_encoding[iupac];
            }
            return U_rev_encoding[iupac];

        } else if (encoding_type == 'N') {
            if (N_encoding.find(iupac) == N_encoding.end()) {
                fillCodeMap(N_encoding, N_rev_encoding, legalDNA, iupac);
                fillCodeMap(N_encoding, N_rev_encoding, legalRNA, iupac);
            }

            if (!reverse) {
                return N_encoding[iupac];
            }
            return N_rev_encoding[iupac];

        } else if (encoding_type == 'D') {
            if (D_encoding.find(iupac) == D_encoding.end()) {
                fillCodeMap(D_encoding, D_rev_encoding, legalDNA, iupac);
            }

            if (!reverse) {
                return D_encoding[iupac];
            }
            return D_rev_encoding[iupac];

        } else if (encoding_type == 'R') {
            if (R_encoding.find(iupac) == R_encoding.end()) {
                fillCodeMap(R_encoding, R_rev_encoding, legalRNA, iupac);
            }

            if (!reverse) {
                return R_encoding[iupac];
            }
            return R_rev_encoding[iupac];

        } else if (encoding_type == 'P') {
            if (P_encoding.find(iupac) == P_encoding.end()) {
                fillCodeMap(P_encoding, P_rev_encoding, legalAmino, iupac);
            }

            if (!reverse) {
                return P_encoding[iupac];
            }
            return P_rev_encoding[iupac];
        } else {
            displayLogicError(error_mod, "Unable to determine map encoding_type", __FILE__, __func__);
        }

        return U_encoding[iupac];
    }

    
    
    static void fillCodeMap(std::map<Sequence::IUPACMod, std::map<char, char>> & normal_encoding, std::map<Sequence::IUPACMod, std::map<char, char>> & reverse_encoding, 
                            const std::map<char, Sequence::SequenceSymbol> & element_to_add, Sequence::IUPACMod iupac) {
        
        // Add this iupac to the dict
        if (normal_encoding.find(iupac) == normal_encoding.end()) {
            normal_encoding[iupac] = std::map<char, char> {};
            reverse_encoding[iupac] = std::map<char, char> {};
        }

        char encoded_symbol;
        char current_symbol;
        for (const auto & key_symbol : element_to_add) {
           
            // Verify that this symbol can be used with this iupac setting ?
            Sequence::SequenceSymbol sym_obj = key_symbol.second;
            current_symbol = key_symbol.first;
           
 
            if (!sym_obj.isUsableIn(iupac)) {
                continue;
            }

            if (normal_encoding[iupac].find(current_symbol) != normal_encoding[iupac].end()) {
                continue;
            }

            encoded_symbol = (char) normal_encoding[iupac].size();

            normal_encoding[iupac][current_symbol] = encoded_symbol;
            reverse_encoding[iupac][encoded_symbol] = current_symbol;
           
        }
    }

    // --- Type ---
    static char readTypeArray(std::array<bool, 5> type, bool ignore_illegal=false);
    static std::array<bool, 5> readTypeChar(char type);
    static std::array<bool, 5> identifySymbolType(char symbol);

    static bool canBeRna(char type);
    static bool canBeDna(char type);
    static bool canBeAmino(char type);
    static bool canBeNucleic(char type);

    
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

    char get(size_t position) const {
        char * tab =  this->seq.get(position);
        char char_to_translate = tab[0];
        delete [] tab;
        
        return translationTab(this->getEncodingType(), this->_iupac, true).at(char_to_translate);
    }
    char operator[](size_t position) const {
        return this->get(position);
    }
};

#endif