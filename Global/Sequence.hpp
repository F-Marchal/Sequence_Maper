
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
#include "Header.hpp"
class Sequence {
public:
    /**
     * @brief Allow IUPAC alphabet selection.
     * basic : A, T / U, C, G | 20 Amino acids
     * most : All iupac symbol less gap and rare / non standard symbols
     * all :  All iupac symbol
     */
    enum IUPACMod {
    basic       = 0,
    most        = 1, 
    all         = 2,
    };

    /**
     * @brief Represent a symbol that can be used inside \ref Sequence
     */
    class SequenceSymbol {
    private:
        /**
         * @brief When this symbol can not be used with the current IUPAC alphabet, what chars can be used ?
         */
        std::string _replacement;
        /**
         * @brief Symbol represented
         */
        char _symbol;
        /**
         * @brief In which alphabet thus symbol exist ?
         */
        Sequence::IUPACMod _iupac;

    public:
        /**
         * @brief Construct a new Sequence Symbol object
         * 
         * @param symbol A, T, C, G, B ....
         * @param replacement When this symbol can not be used with the current IUPAC alphabet, what chars can be used ? (Ex : B --} "CGT").
         * You can use '\0' if this symbol should be ignored.
         * @param iupac What is the lowest Iupac setting acceptable for this class ?
         */
        SequenceSymbol(char symbol, std::string replacement, Sequence::IUPACMod iupac) ;

        /**
         * @brief Do this object correspond to another char ?
         * 
         * @param symbol A symbol to test.
         * @param use_replacement Do \p symbol is also compared to replacement symbol 
         * @return true yes
         * @return false no
         */
        bool correspondTo(char symbol, bool use_replacement=true) const ;

        /**
         * @brief Do this symbol can be used with this \p iupac setting ?
         * 
         * @param iupac A iupac setting
         * @return true Yes
         * @return false No
         */
        bool isUsableIn(IUPACMod iupac) const ;

        /**
         * @brief Get the Replacement Symbol
         * @return char A random char from Sequence::SequenceSymbol::_replacement
         */
        char getReplacementSymbol() const ;

        /**
         * @brief Get the symbol contained into this object
         * @return char  Sequence::SequenceSymbol::_symbol
         */
        char getValue() const ;
        
        /**
         * @brief Get the value of this SequenceSymbol in a precise iupac alphabet.
         * 
         * @param iupac A iupac setting
         * @return char Sequence::SequenceSymbol::_symbol or Sequence::SequenceSymbol::getReplacementSymbol().
         */
        char get(Sequence::IUPACMod iupac) const ;

        /**
         * @brief Turn SequenceSymbol to a char.
         * @return char  Sequence::SequenceSymbol::_symbol
         */
        operator char() const ;

        /**
         * @brief Turn SequenceSymbol to a std::string.
         * @return std::string Sequence::SequenceSymbol::_symbol
         */
        operator std::string() const ;
        
        /**
         * @brief Turn SequenceSymbol to a std::string.
         * @return std::string Sequence::SequenceSymbol::_symbol
         */
        std::string toString() const ;

         /**
         * @brief Allow SequenceSymbol to be cout.
         * @return std::ostream 
         */
        friend std::ostream& operator<<(std::ostream& os, const Sequence::SequenceSymbol& symbol) {
            os << symbol.toString();
            return os;
        }
    };
    
private:


    std::array<bool, 5> type;
    BitVector seq;
    char _encoding_type;
    
    Header _header;
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
            /**
             * @brief Sequence in which SequenceIterator iter
             */
            const Sequence& _sequence;
            /**
             * @brief Current position in Sequence::SequenceIterator::_sequence
             */
            size_t _index;

        public:
            /**
             * @brief Construct a new Sequence Iterator object
             * @param seq Sequence in which SequenceIterator iter
             * @param index An index of a char inside the sequence.
             */
            SequenceIterator(const Sequence& seq, size_t index) : _sequence(seq), _index(index) {}

            /**
             * @brief Give the current value of the element at the position Sequence::SequenceIterator::_index
             * @return int Sequence::SequenceIterator:_sequence[Sequence::SequenceIterator:_index]
             */
            int operator*() const ;

            /**
             * @brief Increment the Sequence::SequenceIterator:_index by 1.
             * @return SequenceIterator& 
             */
            SequenceIterator& operator++() ;

            /**
             * @brief Compare two Sequence::SequenceIterator
             * @param other Another Sequence::SequenceIterator
             * @return true The two Sequence::SequenceIterator have not the same index
             * @return false The two Sequence::SequenceIterator have the same index
             */
            bool operator!=(const SequenceIterator& other) const ;

            /**
             * @brief Get  Sequence::SequenceIterator::_index
             * @return size_t  Sequence::SequenceIterator::_index
             */
            size_t getIndex() const ;

            /**
             * @brief Get  Sequence::SequenceIterator::_seq
             * @return Sequence  Sequence::SequenceIterator::_seq
             */
            const Sequence & GetSequence() const ;
    };

    /**
     * @brief Give an iterator to begin an iteration
     * @return SequenceIterator (index=0)
     */
    SequenceIterator begin() const ;

    /**
     * @brief Give an iterator to end an iteration
     * @return SequenceIterator 
     */
    SequenceIterator end() const ;

    // --- --- Constructors --- ---

    /**
     * @brief Main Constructor. Construct a new Sequence object
     * 
     * @param sequence          A string that represent a sequence of DNA / RNA / AMINO.
     * @param type              Specify type of this sequence. 'D'=DNA, 'R'=RNA, 'P'=Protein, 'N'=DNA and / or RNA 'U'=Unknown (Sequence will analyze chars in order to determine its type)
     * @param error_mod         See values inside Utilities::errorMods
     * @param iupac             Set the authorized alphabet for this Sequence. Modify how values will be encoded.
     * @param finalis_type      Do this sequence will continue analyze chars in order to determine its type.
     * @warning \p type == 'U', \p iupac should be at least Sequence::most.
     */
    Sequence(const std::string & sequence, char type,           IUPACMod iupac=most, errorMods error_mod=raise, bool finalis_type=true);
    
    
    /**
     * @brief Main Constructor. Construct a new Sequence object
     * 
     * @param error_mod         See values inside Utilities::errorMods
     * @param iupac             Set the authorized alphabet for this Sequence. Modify how values will be encoded.
     * @param finalis_type      Do this sequence will continue analyze chars in order to determine its type.
     * @warning \p iupac should be at least Sequence::most.
     */
    Sequence(                                           IUPACMod iupac=most, errorMods error_mod=raise, bool finalis_type=false) : Sequence("", 'U', iupac, error_mod, finalis_type) {};
    
    
    /**
     * @brief Main Constructor. Construct a new Sequence object
     * 
     * @param sequence          A string that represent a sequence of DNA / RNA / AMINO.
     * @param error_mod         See values inside Utilities::errorMods
     * @param iupac             Set the authorized alphabet for this Sequence. Modify how values will be encoded.
     * @param finalis_type      Do this sequence will continue analyze chars in order to determine its type.
     * @warning \p iupac should be at least Sequence::most.
     */
    Sequence(std::string sequence,                      IUPACMod iupac=most, errorMods error_mod=raise, bool finalis_type=true)  : Sequence(sequence, 'U', iupac, error_mod, finalis_type) {};
    
    // --- --- Utilities --- ---
    // --- Getters and equivalents ---

    /**
     * @brief Get the sequence contain in this object
     * 
     * @return const std::string& The sequence contain in this object
     */
    const BitVector & getSeq() const;

    /**
     * @brief Get a char that represent sequence type.
     * 
     * @return char 'D'=DNA, 'R'=RNA, 'P'=Protein, 'N'=DNA and / or RNA 'U'=Unspecified, 'Z'=Invalid type.
     */
    char getType() const;

    /**
     * @brief Return a char (same format as Sequence::getType()) that indicate which alphabet is used in the during encoding
     * @return char 
     */
    char getEncodingType() const;

    /**
     * @brief Say which iupac setting is used 
     * 
     * @return Sequence::IUPACMod Which iupac setting is used 
     */
    Sequence::IUPACMod getIupac() const;

    /**
     * @brief Get the Type Array object
     * 
     * @return const std::array<bool, 5>& = { 
     *       sequence_is_dna_specific ?,
     *       sequence_is_rna_specific ?,
     *       sequence_is_amino_specific ?,
     *       sequence_is_nucleic_specific ?,
     *       sequence_research_his_type ?,
     *       }
     */
    const std::array<bool, 5> & getTypeArray() const;

    /**
     * @brief Give the header attached to this Sequence
     * 
     * @return Header&  Sequence::_header
     */
    Header & getHeader() ;

    /**
     * @brief Set the Header attribute
     * 
     * @param header A new header.
     */
    void setHeader(Header header) ;

    /**
     * @brief Give the number of element contained in this sequence.
     * 
     * @return size_t Sequence::seq.size()
     */
    size_t size() const;
    
    /**
     * @brief Get the  Sequence::SequenceSymbol object attached to a symbol
     * 
     * @param symbol A symbol ex : A, T, C, G, U, B...
     * @param type Type of alphabet (U, P, D, R, N)
     * @return Sequence::SequenceSymbol 
     */
    static Sequence::SequenceSymbol getSequenceSymbol(char symbol, char type);

    // --- Modify sequence ---
    /**
     * @brief When the sequence append a new cars, the Sequence will search to update is Sequence::type.
     */
    void activeTypeResearch();
    /**
     * @brief When the sequence append a new cars, the Sequence will no longer search to update is Sequence::type.
     */
    void endTypeResearch();

    /**
     * @brief Insert a number of chars at the position \p position .
     * 
     * @param sequence A tab of chars
     * @param position the insertion position
     * @param errorMod What should we do with minor errors ?
     */
    virtual void insert(const std::string & sequence, size_t position, errorMods errorMod=display);
    
    /**
     * @brief Insert a char at the position \p position .
     * 
     * @param sequence A char
     * @param position the insertion position
     * @param errorMod What should we do with minor errors ?
     */
    void insert(const char & symbol, size_t position, errorMods errorMod=display);

     /**
     * @brief Insert a number of chars at the the front of the sequence \p position .
     * 
     * @param sequence A tab of chars
     * @param errorMod What should we do with minor errors ?
     */
    void insertFront(const std::string & sequence, errorMods errorMod=display);
    /**
     * @brief Insert a number of chars at the the back of the sequence \p position .
     * 
     * @param sequence A tab of chars
     * @param errorMod What should we do with minor errors ?
     */
    void insertBack(const std::string & sequence, errorMods errorMod=display);
    
    /**
     * @brief Insert a char at the the front of the sequence \p position .
     * 
     * @param sequence A char
     * @param errorMod What should we do with minor errors ?
     */
    void insertFront(const char & sequence, errorMods errorMod=display);
    
    /**
     * @brief Insert a char at the the back of the sequence \p position .
     * 
     * @param sequence A char
     * @param errorMod What should we do with minor errors ?
     */
    void insertBack(const char & sequence, errorMods errorMod=display);

    /**
     * @brief Remove a portion of the sequence.
     * 
     * @param start First position
     * @param length Last position
     */
    virtual void erase(size_t start, size_t length) ;
    
    // --- --- Static Utilities --- ---
    // --- Symbols ---
    static const Sequence::SequenceSymbol & getSymbolDNA(char symbol){
        return legalDNA.at(symbol);
    }
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

    friend std::ostream& operator<<(std::ostream& os, const Sequence& seq) {
        for (char symbol : seq) {
            os << symbol;
        }
        return os;
    }

};

#endif