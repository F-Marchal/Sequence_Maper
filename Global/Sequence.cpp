#include "Sequence.hpp"
#include <fstream>
#include <string>
#include <iostream>
#include <stdexcept>
#include <set>
#include <map>
#include <array>

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
    'P',
    'D',
    'R',
    'N',
    'U'
};


// --- --- Private Methods --- ---
void Sequence::addSeq(std::string sequence, size_t position, bool errorMod) {

    bool* dna_rna_amino_bool[3];
    for (int i = 0; i < 3; ++i) {
        dna_rna_amino_bool[i] = new bool;
    }

    std::string final_seq = "";
    bool is_usable_char;

    std::cout<< "A : " << std::endl;


    this->PrepareRnaDnaAminoBool(dna_rna_amino_bool);


    for (char symbol : sequence) {
        is_usable_char = parseChar(symbol, dna_rna_amino_bool, errorMod);
        if (is_usable_char) {
            final_seq += symbol;
        }
    }
    
    this->guessAndSetType(dna_rna_amino_bool);

}


// --- --- Constructors and parsers --- ---
Sequence::Sequence(std::string sequence, char type, bool errorMod) {
    this->type = type;
    this->addSeq(sequence, this->seq.size(), errorMod);
}

// --- Parsers ---
bool Sequence::parseChar(char symbol, bool* dna_rna_amino_bool[3], bool errorMode) {
    char symbol_type = identifyChar(symbol, errorMode);
    if (symbol_type == 'Z') {
        // Unknown symbol.
        return false;
    }
    RnaDnaAminoBoolManager(this->type, symbol, symbol_type,  dna_rna_amino_bool);
    return true;
 }

void Sequence::PrepareRnaDnaAminoBool(bool* dna_rna_amino_bool[3]) {

    if (this->type != 'U') {
        
        *(dna_rna_amino_bool[0]) = canBeDna(this->type);
        *(dna_rna_amino_bool[1]) = canBeRna(this->type);
        *(dna_rna_amino_bool[2]) = canBeAmino(this->type);
    } else {
    std::cout<< "go : " << (dna_rna_amino_bool == nullptr) << std::endl;
        *dna_rna_amino_bool[0] = false;
        *dna_rna_amino_bool[1] = false;
        *dna_rna_amino_bool[2] = false;
            std::cout<< "Good : " << std::endl;

    }
}

void Sequence::guessAndSetType(bool* dna_rna_amino_bool[3]) {
    if (this->type != 'U') {
        return ;
    }
    this->type = SequenceGuessType(dna_rna_amino_bool);
}

// --- --- Static Utilities --- ---
// --- Sequence parsing ---
char Sequence::identifyChar(char symbol, bool errorType) {
    if (!isLegalSymbol(symbol)) {
        if (errorType) {
            throw std::domain_error("Illegal symbol found in this sequence : " + symbol);
        }

        return 'Z';
    }
    if (isLegalNucleic(symbol)) {
        if (isDnaSpecificNucleotide(symbol)) {
            return 'D';

        } else if (isRnaSpecificNucleotide(symbol)) {
            return 'R';

        } else {
            return 'N';
        }

    } else if (isLegalAmino(symbol)) {
        return 'P';
    }

    // Not supposed to be reached.
    return 'Z';
}

void Sequence::RnaDnaAminoBoolManager(char type, char symbol, char symbol_type, bool* dna_rna_amino_bool[3]) {
    bool dna_bool = *(dna_rna_amino_bool[0]);
    bool rna_bool = *(dna_rna_amino_bool[1]);
    bool amino_bool = *(dna_rna_amino_bool[2]);

    if (type == 'U') {
        if (!amino_bool) {
            amino_bool = isAminoSpecific(symbol);
        }
        if (!rna_bool) {
            rna_bool = isRnaSpecificNucleotide(symbol);
        } 
        if (!dna_bool) {
            dna_bool = isDnaSpecificNucleotide(symbol);
        }
    } else {  
        if (dna_bool && !canBeDna(symbol_type)) {
            throw std::domain_error(" Only DNA is accepted by this sequence. Got : " + symbol);
        }

        if (rna_bool && !canBeRna(symbol_type)) {
            throw std::domain_error(" Only RNA is accepted by this sequence. Got : " + symbol);

        } 
        if (amino_bool && !canBeAmino(symbol)) {
            throw std::domain_error(" Only Amino are accepted by this sequence. Got : " + symbol);

        }
    }

    *(dna_rna_amino_bool[0]) = dna_bool;
    *(dna_rna_amino_bool[1]) = rna_bool;
    *(dna_rna_amino_bool[2]) = amino_bool;
}

char Sequence::SequenceGuessType(bool* dna_rna_amino_bool[3]) {
    bool dna_bool = *(dna_rna_amino_bool[0]);
    bool rna_bool = *(dna_rna_amino_bool[1]);
    bool amino_bool = *(dna_rna_amino_bool[2]);

    if (amino_bool) {
        return 'P';
    } else if (dna_bool && rna_bool) {
        return 'N';
    } else if (dna_bool) {
        return 'D';
    } else if (rna_bool) {
        return 'R';
    } 
    std::cout << dna_bool << " " << rna_bool << " " << amino_bool << " " << std::endl;
    throw std::domain_error(" Unable to determine sequence type. ");
    
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

bool Sequence::isValidType(char symbol) {
       return (validType.find(symbol) != validType.end());
}


// --- Type ---
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