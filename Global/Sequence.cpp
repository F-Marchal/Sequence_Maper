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
    {'X', Sequence::SequenceSymbol('X', "X", Sequence::basic)}, //any

    {'O', Sequence::SequenceSymbol('O', "O", Sequence::basic)}, //Pyrrolysine (rare)
    {'U', Sequence::SequenceSymbol('U', "U", Sequence::basic)}, //Selenocysteine (rare)

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

    if (!char_is_dna_specific && !char_is_rna_specific && !char_is_amino_specific && !char_is_nucleic_specific) {
        // Not specific
        return symbol;
    }

    bool sequence_is_dna_specific = this->type[0];
    bool sequence_is_rna_specific = this->type[1];
    bool sequence_is_amino_specific = this->type[2];
    bool sequence_is_nucleic_specific = this->type[3];
    bool sequence_research_his_type = this->type[4];

    char symbol_type = readTypeArray(char_type);
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

        if (sequence_is_amino_specific && !canBeAmino(symbol)) {
            displayDomainError(error_mod, "Only Amino are accepted by this sequence. Got : '" + std::string(1, symbol) + "'", __FILE__, __func__);
           return '\0';
        }

        if (sequence_is_nucleic_specific && !canBeNucleic(symbol)) {
            displayDomainError(error_mod, "Only Nucleic Acid are accepted by this sequence. Got : " + std::string(1, symbol) + "'", __FILE__, __func__);
           return '\0';
        }
    }

    // This symbol can be used with defined type.
    return getSequenceSymbol(symbol, symbol_type).get(this->_iupac);
}

// --- --- Constructors --- ---

Sequence::Sequence(std::string sequence, char type, Sequence::IUPACMod iupac, errorMods error_mod, bool finalis_type) {
    type = (char)toupper(type);
    this->type = this->readTypeChar(type);
    this->_iupac = iupac;

    this->insertFront(sequence, error_mod);

    if (finalis_type) {
        this->endTypeResearch();
    }
}

// --- --- Utilities --- ---
// --- Getters and equivalents ---

const std::string & Sequence::getSeq() const {
    return this->seq;
}

char Sequence::getType() const {
    return this->readTypeArray(this->getTypeArray(), true);
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

std::string Sequence::toString() const {
    return this->getSeq();
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
    /*
    
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
    */
}

// --- Modify sequence ---
void Sequence::activeTypeResearch() {
    this->type[4] = true;
}
void Sequence::endTypeResearch() {
    this->type[4] = false;
}

void Sequence::insert(const std::string & sequence, size_t position, errorMods error_mod) {
    std::string final_seq = "";

    for (char symbol : sequence) {
        symbol = parseChar(symbol, error_mod);

        if (symbol != '\0') {
            final_seq += symbol;
        }
    }

    this->seq.insert(position, final_seq);
}

void Sequence::insert(const Sequence & sequence, size_t position, errorMods errorMod) {
    this->insert(sequence.getSeq(), position, errorMod);
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


void Sequence::insertFront(const Sequence & sequence, errorMods errorMod) {
      this->insertFront(sequence.getSeq(), errorMod);
}

void Sequence::insertBack(const Sequence & sequence, errorMods errorMod) {
     this->insertBack(sequence.getSeq(), errorMod);
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

    this->seq.erase(start, length);
    
}

// --- Symbols ---
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


// --- Type ---
char Sequence::readTypeArray(std::array<bool, 5> type, bool ignore_illegal) {
    bool dna_specific = type[0];
    bool rna_specific = type[1];
    bool amino_specific = type[2];
    bool nucleic_specific = type[3];
    bool is_illegal = type[4];

    if (nucleic_specific && amino_specific) {
        return 'Z';
    }

    if (is_illegal && !ignore_illegal) {
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