#include "Sequence.hpp"
#include <fstream>
#include <string>
#include <iostream>
#include <stdexcept>
#include <set>
#include <map>
#include <array>
#include "Utilities.hpp"

/**
 * Tester le constructeur
 * Finit la class...
 * 
 */





// --- --- Private attributes --- ---
std::map<char, char> Sequence::legalDNA = {
    {'A', 'T'}, {'a', 't'}, //A → Adenine 
    {'B', 'V'}, {'b', 'v'}, //not A (i.e. C, G, T) → B comes after A
    {'C', 'G'}, {'c', 'g'}, //C → Cytosine
    {'D', 'H'}, {'d', 'h'}, //not C (i.e. A, G, T) → D comes after C

    {'G', 'C'}, {'g', 'c'}, //G → Guanine
    {'H', 'D'}, {'h', 'd'}, //not G (i.e., A, C, T) → H comes after G
    {'I', 'I'}, {'i', 'i'}, //i → inosine (non-standard)
    {'K', 'M'}, {'k', 'm'}, //G, T → bases which are Ketones

    {'M', 'K'}, {'m', 'k'}, //A or C → bases with aMino groups
    {'N', 'N'}, {'n', 'n'}, //A C G T → Nucleic acid

    {'R', 'Y'}, {'r', 'y'}, //A or G (I) → puRine
    {'S', 'S'}, {'s', 's'}, //C or G → Strong interaction

    {'T', 'A'}, {'t', 'a'}, //T → Thymine

    {'V', 'B'}, {'v', 'b'}, //Not T  (i.e. A, C or G) → V comes after U
    {'W', 'W'}, {'w', 'w'}, //A, T → Weak interaction
  
    {'Y', 'R'}, {'y', 'r'}, //C, T → pYrimidines

    {'-', '-'} //gap of indeterminate length 	
};

std::map<char, char> Sequence::legalRNA = {
    {'A', 'U'}, {'a', 'u'}, //A → Adenine 
    {'B', 'V'}, {'b', 'v'}, //not A (i.e. C, G or U) → B comes after A
    {'C', 'G'}, {'c', 'g'}, //C → Cytosine
    {'D', 'H'}, {'d', 'h'}, //not C (i.e. A, G or U) → D comes after C

    {'G', 'C'}, {'g', 'c'}, //G → Guanine
    {'H', 'D'}, {'h', 'd'}, //not G (i.e., A, C or U) → H comes after G
    {'I', 'I'}, {'i', 'i'}, //i → inosine (non-standard)
    {'K', 'M'}, {'k', 'm'}, //G or U → bases which are Ketones

    {'M', 'K'}, {'m', 'k'}, //A or C → bases with aMino groups
    {'N', 'N'}, {'n', 'n'}, //A C G U → Nucleic acid

    {'R', 'Y'}, {'r', 'y'}, //A or G (I) → puRine
    {'S', 'S'}, {'s', 's'}, //C or G → Strong interaction

    {'U', 'A'}, {'u', 'a'}, //U → Uracil

    {'V', 'B'}, {'v', 'b'}, //not U (i.e. A, C or G) → V comes after U
    {'W', 'W'}, {'w', 'w'}, //A or U → Weak interaction

    {'Y', 'R'}, {'y', 'r'}, //C or U → pYrimidines

    {'-', '-'} //gap of indeterminate length 	
};

std::set<char> Sequence::legalAmino = {
    'A', 'a', //Alanine
    'B', 'b', //Aspartic acid (D) or Asparagine (N)
    'C', 'c', //Cysteine
    'D', 'd', //Aspartic acid
    'E', 'e', //Glutamic acid
    'F', 'f', //Phenylalanine
    'G', 'g', //Glycine
    'H', 'h', //Histidine
    'I', 'i', //Isoleucine
    'J', 'j', //Leucine (L) or Isoleucine (I)
    'K', 'k', //Lysine
    'L', 'l', //Leucine
    'M', 'm', //Methionine/Start codon
    'N', 'n', //Asparagine
    'O', 'o', //Pyrrolysine (rare)
    'P', 'p', //Proline
    'Q', 'q', //Glutamine
    'R', 'r', //Arginine
    'S', 's', //Serine
    'T', 't', //Threonine
    'U', 'u', //Selenocysteine (rare)
    'V', 'v', //Valine
    'W', 'w', //Tryptophan
    'Y', 'y', //Tyrosine
    'X', 'x', //any
    'Z', 'z', //Glutamic acid (E) or Glutamine (Q)
    '-', //gap of indeterminate length 
    '*', //translation stop
};

std::map<char, char> Sequence::bridgeDNA_RNA{
    {'t', 'u'}, {'T', 'U'},
    {'u', 't'}, {'U', 'T'}
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
bool Sequence::parseChar(char symbol, errorMods error_mod) {
    std::array<bool, 5> char_type = identifySymbolType(symbol);
    bool char_is_dna_specific = char_type[0];
    bool char_is_rna_specific = char_type[1];
    bool char_is_amino_specific = char_type[2];
    bool char_is_nucleic_specific = char_type[3];
    bool char_is_legal = char_type[4];

    if (!char_is_legal) {
        displayDomainError(error_mod, "Illegal character found : '" + std::string(1, symbol) + "'", __FILE__, __func__);
        return false;
    }

    if (!char_is_dna_specific && !char_is_rna_specific && !char_is_amino_specific && !char_is_nucleic_specific) {
        // Not specific
        return true;
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
            return false;
        }

        if (char_is_nucleic_specific && sequence_is_amino_specific) {
            return false;
        }

        this->type[2] = (char_is_amino_specific || sequence_is_amino_specific);
        this->type[3] = (char_is_nucleic_specific || sequence_is_nucleic_specific);

    } else {  
        char symbol_type = readTypeArray(char_type);

        if (sequence_is_dna_specific && sequence_is_rna_specific) {
            if (!canBeDna(symbol_type) && !canBeRna(symbol_type)) {
                displayDomainError(error_mod, "Only Nucleic Acid are accepted by this sequence. Got : '" + std::string(1, symbol) + "'", __FILE__, __func__);
                return false;
            }


        } else {
            if (sequence_is_dna_specific && !canBeDna(symbol_type)) {
                displayDomainError(error_mod, "Only DNA is accepted by this sequence. Got : '" + std::string(1, symbol) + "'", __FILE__, __func__);
                return false;
            }

            if (sequence_is_rna_specific && !canBeRna(symbol_type)) {
                displayDomainError(error_mod, "Only RNA is accepted by this sequence. Got : '" + std::string(1, symbol) + "'", __FILE__, __func__);
                return false;
            } 
        }

        if (sequence_is_amino_specific && !canBeAmino(symbol)) {
            displayDomainError(error_mod, "Only Amino are accepted by this sequence. Got : '" + std::string(1, symbol) + "'", __FILE__, __func__);
            return false;
        }

        if (sequence_is_nucleic_specific && !canBeNucleic(symbol)) {
            displayDomainError(error_mod, "Only Nucleic Acid are accepted by this sequence. Got : " + std::string(1, symbol) + "'", __FILE__, __func__);
            return false;
        }
    }

    return true;
}

// --- --- Constructors --- ---

Sequence::Sequence(std::string sequence, char type, errorMods error_mod, bool finalis_type) {
    type = (char)toupper(type);
    this->type = this->readTypeChar(type);
    
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

std::array<bool, 5> Sequence::getTypeArray() const {
    return this->type;
}

size_t Sequence::size() const {
    return this->seq.size();
}

std::string Sequence::toString() const {
    return this->getSeq();
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
    bool is_usable_char;

    for (char symbol : sequence) {
        is_usable_char = parseChar(symbol, error_mod);

        if (is_usable_char) {
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