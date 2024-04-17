#include "Sequence.hpp"
#include <fstream>
#include <string>
#include <iostream>
#include <stdexcept>
#include <set>
#include <map>
#include <array>
#include <random>
#include "Utilities.hpp"





// --- --- Private attributes --- ---
const std::map<char, Sequence::SequenceSymbol> Sequence::legalDNA = {
    // 2 bits
    {'A', Sequence::SequenceSymbol('A', "A", Sequence::basic)}, //A → Adenine 
    {'T', Sequence::SequenceSymbol('T', "T", Sequence::basic)}, //T → Thymine
    {'C', Sequence::SequenceSymbol('C', "C", Sequence::basic)}, //C → Cytosine
    {'G', Sequence::SequenceSymbol('G', "G", Sequence::basic)}, //G → Guanine
    
    // 4 bits (+ 1 free space)
    {'B', Sequence::SequenceSymbol('B', "CGT", Sequence::most)}, //not A (i.e. C, G, T) → B comes after A
    {'D', Sequence::SequenceSymbol('D', "AGT", Sequence::most)}, //not C (i.e. A, G, T) → D comes after C

    {'H', Sequence::SequenceSymbol('H', "ACT", Sequence::most)}, //not G (i.e., A, C, T) → H comes after G

    {'K', Sequence::SequenceSymbol('K', "GT", Sequence::most)}, //G, T → bases which are Ketones

    {'M', Sequence::SequenceSymbol('M', "AC", Sequence::most)}, //A or C → bases with aMino groups
    {'N', Sequence::SequenceSymbol('N', "ACGT", Sequence::most)}, //A C G T → Nucleic acid

    {'R', Sequence::SequenceSymbol('R', "AG", Sequence::most)}, //A or G (I) → puRine
    {'S', Sequence::SequenceSymbol('S', "CG", Sequence::most)}, //C or G → Strong interaction

    {'V', Sequence::SequenceSymbol('R', "ACG", Sequence::most)}, //Not T  (i.e. A, C or G) → V comes after U
    {'W', Sequence::SequenceSymbol('W', "AT", Sequence::most)}, //A, T → Weak interaction
  
    {'Y', Sequence::SequenceSymbol('Y', "CT", Sequence::most)}, //C, T → pYrimidines
    
    {'I', Sequence::SequenceSymbol('I', "\0", Sequence::all)}, //i → inosine (non-standard)
    {'-', Sequence::SequenceSymbol('.', "\0", Sequence::all)}, //gap of indeterminate length 	
};


const std::map<char, Sequence::SequenceSymbol> Sequence::legalRNA = {
    // 2 bits
    {'A', Sequence::SequenceSymbol('A', "A", Sequence::basic)}, //A → Adenine 
    {'U', Sequence::SequenceSymbol('U', "U", Sequence::basic)}, //U → Uracil
    {'C', Sequence::SequenceSymbol('C', "C", Sequence::basic)}, //C → Cytosine
    {'G', Sequence::SequenceSymbol('G', "G", Sequence::basic)}, //G → Guanine
    
    // 4 bits (+ 1 free space)
    {'B', Sequence::SequenceSymbol('B', "CGU", Sequence::most)}, //not A (i.e. C, G, U) → B comes after A
    {'D', Sequence::SequenceSymbol('D', "AGU", Sequence::most)}, //not C (i.e. A, G, U) → D comes after C

    {'H', Sequence::SequenceSymbol('H', "ACU", Sequence::most)}, //not G (i.e., A, C, U) → H comes after G

    {'K', Sequence::SequenceSymbol('K', "GU", Sequence::most)}, //G, U → bases which are Ketones

    {'M', Sequence::SequenceSymbol('M', "AC", Sequence::most)}, //A or C → bases with aMino groups
    {'N', Sequence::SequenceSymbol('N', "ACGU", Sequence::most)}, //A C G U → Nucleic acid

    {'R', Sequence::SequenceSymbol('R', "AG", Sequence::most)}, //A or G (I) → puRine
    {'S', Sequence::SequenceSymbol('S', "CG", Sequence::most)}, //C or G → Strong interaction

    {'V', Sequence::SequenceSymbol('R', "ACG", Sequence::most)}, //Not U  (i.e. A, C or G) → V comes after U
    {'W', Sequence::SequenceSymbol('W', "AU", Sequence::most)}, //A, U → Weak interaction
  
    {'Y', Sequence::SequenceSymbol('Y', "CU", Sequence::most)}, //C, U → pYrimidines
    
    {'I', Sequence::SequenceSymbol('I', "\0", Sequence::all)}, //i → inosine (non-standard)
    {'-', Sequence::SequenceSymbol('.', "\0", Sequence::all)}, //gap of indeterminate length 	
};

const std::map<char, Sequence::SequenceSymbol> Sequence::legalAmino = {
    {'A', Sequence::SequenceSymbol('A', "A", Sequence::basic)}, //Alanine
   
    {'C', Sequence::SequenceSymbol('C', "C", Sequence::basic)}, //Cysteine
    {'D', Sequence::SequenceSymbol('D', "D", Sequence::basic)}, //Aspartic acid
    {'E', Sequence::SequenceSymbol('E', "E", Sequence::basic)}, //Glutamic acid
    {'F', Sequence::SequenceSymbol('F', "F", Sequence::basic)}, //Phenylalanine
    {'G', Sequence::SequenceSymbol('G', "G", Sequence::basic)}, //Glycine
    {'H', Sequence::SequenceSymbol('H', "H", Sequence::basic)}, //Histidine
    {'I', Sequence::SequenceSymbol('I', "I", Sequence::basic)}, //Isoleucine

    {'K', Sequence::SequenceSymbol('K', "K", Sequence::basic)}, //Lysine
    {'L', Sequence::SequenceSymbol('L', "L", Sequence::basic)}, //Leucine
    {'M', Sequence::SequenceSymbol('M', "M", Sequence::basic)}, //Methionine/Start codon
    {'N', Sequence::SequenceSymbol('N', "N", Sequence::basic)}, //Asparagine

    {'P', Sequence::SequenceSymbol('P', "P", Sequence::basic)}, //Proline
    {'Q', Sequence::SequenceSymbol('Q', "Q", Sequence::basic)}, //Glutamine
    {'R', Sequence::SequenceSymbol('R', "R", Sequence::basic)}, //Arginine
    {'S', Sequence::SequenceSymbol('S', "S", Sequence::basic)}, //Serine
    {'T', Sequence::SequenceSymbol('T', "T", Sequence::basic)}, //Threonine

    {'V', Sequence::SequenceSymbol('V', "V", Sequence::basic)}, //Valine
    {'W', Sequence::SequenceSymbol('W', "W", Sequence::basic)}, //Tryptophan
    {'Y', Sequence::SequenceSymbol('Y', "Y", Sequence::basic)}, //Tyrosine
    {'X', Sequence::SequenceSymbol('X', "\0", Sequence::most)}, //any

    {'O', Sequence::SequenceSymbol('O', "\0", Sequence::most)}, //Pyrrolysine (rare)
    {'U', Sequence::SequenceSymbol('U', "\0", Sequence::most)}, //Selenocysteine (rare)

    {'B', Sequence::SequenceSymbol('B', "DN", Sequence::most)}, //Aspartic acid (D) or Asparagine (N)
    {'J', Sequence::SequenceSymbol('J', "LI", Sequence::most)}, //Leucine (L) or Isoleucine (I)
    {'Z', Sequence::SequenceSymbol('Z', "EQ", Sequence::most)}, //Glutamic acid (E) or Glutamine (Q)

    {'-', Sequence::SequenceSymbol('-', "\0", Sequence::all)}, //gap of indeterminate length 
    {'*', Sequence::SequenceSymbol('*', "\0", Sequence::all)} //translation stop
};



std::set<char> Sequence::validType = {
    'P', // Protein
    'D', // DNA
    'R', // RNA
    'N', // Dna or RNA
    'U'  // undetermined
};


// --- --- Protected Methods --- ---
// --- Parsers ---  
char Sequence::parseChar(char symbol, errorMods error_mod) {

    symbol = std::toupper(symbol);
    std::array<bool, 5> char_type = identifySymbolType(symbol);

    bool char_is_dna_specific = char_type[0];
    bool char_is_rna_specific = char_type[1];
    bool char_is_amino_specific = char_type[2];
    bool char_is_nucleic_specific = char_type[3];
    bool char_is_legal = char_type[4];

    if (!char_is_legal) {
        displayDomainError(error_mod, "Illegal character found : '" + std::string(1, symbol) + "'", __FILE__, __func__);
        return '\0';
    }
    char symbol_type = readTypeArray(char_type);
    if (!char_is_dna_specific && !char_is_rna_specific && !char_is_amino_specific && !char_is_nucleic_specific) {
        // Not specific
        return getSequenceSymbol(symbol, symbol_type).get(this->_iupac);
    }
    
    bool sequence_is_dna_specific = this->type[0];
    bool sequence_is_rna_specific = this->type[1];
    bool sequence_is_amino_specific = this->type[2];
    bool sequence_is_nucleic_specific = this->type[3];
    bool sequence_research_his_type = this->type[4];
    

   
        
    if (sequence_research_his_type) {

        this->type[0] = (char_is_dna_specific || sequence_is_dna_specific);
        this->type[1] = (char_is_rna_specific || sequence_is_rna_specific);
        
        if (char_is_amino_specific && sequence_is_nucleic_specific) {
           return '\0';
        }

        if (char_is_nucleic_specific && sequence_is_amino_specific) {
           return '\0';
        }

        this->type[2] = (char_is_amino_specific || sequence_is_amino_specific);
        this->type[3] = (char_is_nucleic_specific || sequence_is_nucleic_specific);

    } else {  
       

        if (sequence_is_dna_specific && sequence_is_rna_specific) {
            if (!canBeDna(symbol_type) && !canBeRna(symbol_type)) {
                displayDomainError(error_mod, "Only Nucleic Acid are accepted by this sequence. Got : '" + std::string(1, symbol) + "'", __FILE__, __func__);
               return '\0';
            }


        } else {
            if (sequence_is_dna_specific && !canBeDna(symbol_type)) {
                displayDomainError(error_mod, "Only DNA is accepted by this sequence. Got : '" + std::string(1, symbol) + "'", __FILE__, __func__);
               return '\0';
            }

            if (sequence_is_rna_specific && !canBeRna(symbol_type)) {
                displayDomainError(error_mod, "Only RNA is accepted by this sequence. Got : '" + std::string(1, symbol) + "'", __FILE__, __func__);
               return '\0';
            } 
        }

        if (sequence_is_amino_specific && !canBeAmino(symbol_type)) {
            displayDomainError(error_mod, "Only Amino are accepted by this sequence. Got : '" + std::string(1, symbol) + "'", __FILE__, __func__);
           return '\0';
        }

        if (sequence_is_nucleic_specific && !canBeNucleic(symbol_type)) {
            displayDomainError(error_mod, "Only Nucleic Acid are accepted by this sequence. Got : " + std::string(1, symbol) + "'", __FILE__, __func__);
           return '\0';
        }
    }
    
    // This symbol can be used with defined type.
    return getSequenceSymbol(symbol, symbol_type).get(this->_iupac);
}

// --- --- Constructors --- ---


Sequence::Sequence(const std::string & sequence, char type, Sequence::IUPACMod iupac, errorMods error_mod, bool finalis_type) : 
                   seq(Sequence::elementMaxSize(type, iupac), sequence.size()) {
       
    type = (char)toupper(type);
    if (type == 'U' && iupac < Sequence::most) {
        displayInvalidArgument(raise, "When type is 'U', iupac mod should be most (or higher) (current=" + std::to_string(iupac) + ") due to Conflict in symbol replacement.", __FILE__, __func__);
    }
  
    this->type = this->readTypeChar(type);
    this->_encoding_type = type;
    this->_iupac = iupac;

    this->insertFront(sequence, error_mod);

    if (finalis_type) {
        this->endTypeResearch();
    }
}

// --- --- Utilities --- ---
// --- Getters and equivalents ---
 const BitVector & Sequence::getSeq() const {
    return this->seq;
 }

char Sequence::getType() const {
    return this->readTypeArray(this->getTypeArray(), true);
}
char Sequence::getEncodingType() const {
    return this->_encoding_type;
}
const std::array<bool, 5> & Sequence::getTypeArray() const {
    return this->type;
}
Sequence::IUPACMod Sequence::getIupac() const {
    return this->_iupac;
}

size_t Sequence::size() const {
    return this->seq.size();
}


Header & Sequence::getHeader() {
    return this->_header;
}

void Sequence::setHeader(Header header) {
    this->_header = header;
}


Sequence::SequenceSymbol Sequence::getSequenceSymbol(char symbol, char type) {
 
    if (canBeDna(type) && isDNA(symbol)) {
        return legalDNA.at(symbol);

    } else if (canBeRna(type) && isRNA(symbol)) {
        return legalRNA.at(symbol);

    } else if (canBeAmino(type) && isAmino(symbol)) {
        return legalAmino.at(symbol);
    } 

    displayLogicError(raise, "Can not determine Sequence::SequenceSymbol attached with " + std::to_string(symbol) + " (" + std::to_string(type) + ").",
                      __FILE__, __func__);
    return Sequence::SequenceSymbol('\0', "\0", Sequence::basic);
}

// --- Modify sequence ---
void Sequence::activeTypeResearch() {
    this->type[4] = true;
}
void Sequence::endTypeResearch() {
    this->type[4] = false;
}

void Sequence::insert(const std::string & sequence, size_t position, errorMods error_mod) {
          
    this->seq.makeRoomForElement(position, sequence.size());

    const std::map<char, char> & translation_tab = translationTab(this->_encoding_type, this->_iupac);
 
    size_t initial_position = position;
    

    try {
        for (char symbol : sequence) {
            symbol = parseChar(symbol, error_mod);
             
            if (symbol != '\0') {
                this->seq.set(position, translation_tab.at(symbol)) ;
                position +=1 ;
            }
        }

    } catch (const std::exception& e) {
        // The process failed, let remove unused position
        this->seq.remove(position, sequence.size() - (position - initial_position));
        throw ;
    }

    if (position - initial_position != sequence.size()) {
        // The process is incomplete, let remove unused position
        this->seq.remove(position, sequence.size() - (position - initial_position));
    }
        
}

void Sequence::insert(const char & symbol, size_t position, errorMods errorMod) {
    this->insert(std::string(1, symbol), position, errorMod);
}


void Sequence::insertFront(const std::string & sequence, errorMods errorMod)  {

    this->insert(sequence, this->size(), errorMod);
}

void Sequence::insertBack(const std::string & sequence, errorMods errorMod) {
     this->insert(sequence, 0, errorMod);
}

void Sequence::insertFront(const char & symbol, errorMods errorMod) {
    this->insertFront(std::string(1, symbol), errorMod);
}
void Sequence::insertBack(const char & symbol, errorMods errorMod) {
    this->insertFront(std::string(1, symbol), errorMod);
}


void Sequence::erase(size_t start, size_t length) {
    if (start >= this->size()) {
        return ;
    }

    this->seq.remove(start, length);
    
}

// --- Symbols ---
const Sequence::SequenceSymbol & Sequence::getSymbolDNA(char symbol){
    return legalDNA.at(symbol);
}

bool Sequence::isLegalNucleic(char symbol) {
    return (isDNA(symbol) || isRNA(symbol));
}

bool Sequence::isLegalAmino(char symbol) {
    return (legalAmino.find(symbol) != legalAmino.end());
}

bool Sequence::isLegalSymbol(char symbol) {
    return (isLegalAmino(symbol) || isLegalNucleic(symbol));
}

bool Sequence::isDNA(char symbol) {
    return (legalDNA.find(symbol) != legalDNA.end());
}

bool Sequence::isRNA(char symbol) {
    return (legalRNA.find(symbol) != legalRNA.end());
}

bool Sequence::isNucleic(char symbol) {
     return (isDNA(symbol) || isRNA(symbol));
}

bool Sequence::isAmino(char symbol){
    return isLegalAmino(symbol);
}

bool Sequence::isDnaSpecificNucleotide(char nucleic) {
    return (isDNA(nucleic) && !isRNA(nucleic));
}

bool Sequence::isRnaSpecificNucleotide(char nucleic) {
    return (!isDNA(nucleic) && isRNA(nucleic));
}

bool Sequence::isAminoSpecific(char symbol) {
    return (!isNucleic(symbol) && isAmino(symbol));
}

bool Sequence::isNucleicSpecific(char symbol) {
    // With IUPAC, This is always false.
    return (isNucleic(symbol) && !isAmino(symbol));
}
bool Sequence::isValidType(char symbol) {
       return (validType.find(symbol) != validType.end());
}
size_t Sequence::elementMaxSize(char encoding_type, Sequence::IUPACMod iupac) {
    return translationTab(encoding_type, iupac, false, ignore).size();
}

const std::map<char, char> & Sequence::translationTab (char encoding_type, Sequence::IUPACMod iupac, bool reverse, errorMods error_mod) {
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



void Sequence::fillCodeMap(std::map<Sequence::IUPACMod, std::map<char, char>> & normal_encoding, std::map<Sequence::IUPACMod, std::map<char, char>> & reverse_encoding, 
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
char Sequence::readTypeArray(std::array<bool, 5> type, bool ignore_illegal) {
    bool dna_specific = type[0];
    bool rna_specific = type[1];
    bool amino_specific = type[2];
    bool nucleic_specific = type[3];
    bool legal = type[4];

    if (nucleic_specific && amino_specific) {
        return 'Z';
    }

    if (!legal && !ignore_illegal) {
        return 'Z';
    }

    if (amino_specific) {
        return 'P';
    } else if (nucleic_specific) {
        return 'N';
    } else if (rna_specific && dna_specific) {
        return 'N';
    } else if (rna_specific) {
        return 'R';
    } else if (dna_specific) {
        return 'D';
    } 
    return 'U';

}

std::array<bool, 5> Sequence::readTypeChar(char type) {
    bool dna_specific = false;
    bool rna_specific = false;
    bool amino_specific = false;
    bool nucleic_specific = false;
    bool research = false;
    type = (char)toupper(type);

    if (type == 'P') {
        amino_specific = true;

    } else if (type == 'N') {
        nucleic_specific = true;
        
    } else if (type == 'R') {
        rna_specific = true;
        nucleic_specific = true;

    } else if (type == 'D') {
        dna_specific = true;
        nucleic_specific = true;
    
    } else if (type == 'U') {
        research = true;
    } else {
        throw std::invalid_argument("Type should be P, N, R, D or U.");
    }

    return std::array<bool, 5> {dna_specific, rna_specific, amino_specific, nucleic_specific, research};
}


std::array<bool, 5> Sequence::identifySymbolType(char symbol) {
    bool dna_specific = false;
    bool rna_specific = false;
    bool amino_specific = false;
    bool nucleic_specific = false;
    bool legal = true;

    if (!isLegalSymbol(symbol)) {
        
        legal = false;

    } else {
        if (isDnaSpecificNucleotide(symbol)) {
            dna_specific = true;
        }

        if (isRnaSpecificNucleotide(symbol)) {
            rna_specific = true;
        }

        if (isAminoSpecific(symbol)) {
            amino_specific = true;
        }

        if (isNucleicSpecific(symbol)) {
            nucleic_specific = true;
        }
    }
 
    return   std::array<bool, 5> {dna_specific, rna_specific, amino_specific, nucleic_specific, legal};
}


bool Sequence::canBeRna(char type) {
    return (type == 'R'  || type == 'N' || type == 'U');
 }
 
bool Sequence::canBeDna(char type) {
    return (type == 'D'  || type == 'N' || type == 'U');
 }  

bool Sequence::canBeNucleic(char type) {
    return (canBeRna(type) || canBeDna(type));
 }  

bool Sequence::canBeAmino(char type) {
    return (type == 'P'  || type == 'U');
 }  



 // --- --- SequenceSymbol --- ---
Sequence::SequenceSymbol::SequenceSymbol(char symbol, std::string replacement, Sequence::IUPACMod iupac)  {
    this->_symbol = (char) std::toupper(symbol);
    this->_replacement = replacement;
    this->_iupac = iupac;
}

bool Sequence::SequenceSymbol::correspondTo(char symbol, bool use_replacement) const {
    if (symbol == this->_symbol) {
        return true;
    }

    if (use_replacement) {
        for (char r_symbol : this->_replacement) {
            if (symbol == r_symbol) {
                return true;
            }
        }        
    }
    return false;
}

bool Sequence::SequenceSymbol::isUsableIn(IUPACMod iupac) const {
    return (iupac >= this->_iupac);
}

char Sequence::SequenceSymbol::getReplacementSymbol() const {
    return randChar(this->_replacement);
}

char Sequence::SequenceSymbol::getValue() const {
    return this->_symbol;
}

char Sequence::SequenceSymbol::get(Sequence::IUPACMod iupac) const {
    if (this->isUsableIn(iupac)) {
        return this->_symbol ; 
    } else {
        return this->getReplacementSymbol();
    }
}

Sequence::SequenceSymbol::operator char() const {
    return this->_symbol;
}


Sequence::SequenceSymbol::operator std::string() const {
    return std::string(1, this->_symbol);
}

std::string Sequence::SequenceSymbol::toString() const {
    return std::to_string(this->_symbol);
}

 // --- --- SequenceSymbol --- ---

// Overload the dereference operator to access the value
int Sequence::SequenceIterator::operator*() const {
    return this->_sequence[this->_index];
}

// Overload the pre-increment operator to move to the next element
 Sequence::SequenceIterator& Sequence::SequenceIterator::operator++() {
    ++this->_index;
    return *this;
}

// Overload the inequality operator
bool Sequence::SequenceIterator::operator!=(const SequenceIterator& other) const {
    return this->_index != other.getIndex();
}

size_t Sequence::SequenceIterator::getIndex() const {
    return this->_index;
}
const Sequence & Sequence::SequenceIterator::GetSequence() const {
    return this->_sequence;
}

Sequence::SequenceIterator Sequence::begin() const {
    return Sequence::SequenceIterator(*this, 0);
}

Sequence::SequenceIterator Sequence::end() const {
    return Sequence::SequenceIterator(*this, this->size());
}

//
bool Sequence::operator>(const Sequence& other) const {
    return this->size() > other.size();
}
bool Sequence::operator>=(const Sequence& other) const {
    return this->size() >= other.size();
}
bool Sequence::operator<(const Sequence& other) const {
    return this->size() < other.size();
}
bool Sequence::operator<=(const Sequence& other) const {
    return this->size() <= other.size();
}

Sequence::operator bool() const {
    bool search_mod = this->type[3];
    return (!search_mod);
}

char Sequence::get(size_t position) const {
    char * tab =  this->seq.get(position);
    char char_to_translate = tab[0];
    delete [] tab;
    
    return translationTab(this->getEncodingType(), this->_iupac, true).at(char_to_translate);
}

char Sequence::operator[](size_t position) const {
    return this->get(position);
}
