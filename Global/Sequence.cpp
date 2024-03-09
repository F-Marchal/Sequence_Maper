

#include "Sequence.hpp"
#include <fstream>
#include <string>
#include <iostream>
#include <stdexcept>
#include <set>
#include <map>

// --- --- --- Constructors --- --- --
Sequence::Sequence(std::string sequence, char mod, bool verbose) {
    this->setSeq(sequence, mod, verbose);
}

// --- --- --- Getter & Setters --- --- ---
void Sequence::setSeq(std::string sequence, char mod, bool verbose) {
    std::tuple<std::string, char, bool>  result = ParseSeq(sequence, mod, verbose);
    this->seq = std::get<0>(result);
    this->type = std::get<1>(result);
    this->strict = std::get<2>(result);
}

void Sequence::setSeq(std::string sequence) {
    this->setSeq(sequence, 'U', false);
}

void Sequence::setSeq(std::string sequence, char mod) {
     this->setSeq(sequence, mod, false);
}

void Sequence::setSeq(std::string sequence, bool verbose) {
     this->setSeq(sequence, 'U', verbose);
}

const std::string& Sequence::getSeq() const {
    return this->seq;
};

char Sequence::getType() const {
    return this->type;
};

bool Sequence::getStrict() const {
    return this->strict;
};

void Sequence::updateStrict() {
    this->updateStrict(false);
}

void Sequence::updateStrict(bool verbose) {
     std::tuple<std::string, char, bool>  result = ParseSeq(seq, this->getType(), verbose);
     this->strict = std::get<2>(result);
}


 // --- --- --- Sequence edition --- --- --
void Sequence::insertSeq(size_t position, const Sequence& seq, bool verbose)       {this->insertSeq(position, seq.getSeq(), verbose);}

void Sequence::insertSeq(size_t position, std::string seq, bool verbose) {
    std::tuple<std::string, char, bool>  result = ParseSeq(seq, this->getType(), verbose);
    this->seq.insert(position, seq);
    this->strict = this->strict && std::get<2>(result);
}

void Sequence::eraseSeq(size_t index, size_t length) {
    this->seq.erase(index, length);
}


 // --- --- Biological transformations --- ---
bool Sequence::canBeTranscribed() const {
    return (this->type == 'D');
}

bool Sequence::canBeRetroTranscribed() const {
    return (this->type == 'R');
}

Sequence Sequence::getTranscribedSequence(bool verbose) const {
    if (!this->canBeTranscribed()) {
        throw std::domain_error("Can only transcribe DNA sequences. Got : " + this->type);
    }
    
    std::string new_sequence = this->makeReverseComplement(*this, true, verbose);
    return Sequence(new_sequence, 'R', verbose);
}

Sequence Sequence::getRetroTranscribedSequence(bool verbose) const {
    if  (!this->canBeRetroTranscribed()) {
        throw std::domain_error("Can only retro-transcribe RNA sequences. Got : " + this->type);
    }
    
    std::string new_sequence = this->makeReverseComplement(*this, true, verbose);
    return Sequence(new_sequence, 'D', verbose);
}

Sequence Sequence::getReverseComplement(bool verbose) const { 
    std::string new_sequence = this->makeReverseComplement(*this, false, verbose);
    return Sequence(new_sequence, this->type, verbose);
}

// --- --- Utilities --- --
size_t Sequence::size() const {
    return this->seq.size();
}

std::string Sequence::toString() const {
    return this->getSeq();
}

// --- --- ---  statics --- --- --- 
// --- --- Attributes --- --
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

std::set<char> Sequence::validMod = {
    'P',
    'D',
    'R',
    'N',
    'U'
};

// --- --- Utilities --- --
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

bool Sequence::isDNASpecific(char symbol) {
    return (isDNA(symbol) && !isRNA(symbol));
}

bool Sequence::isRNASpecific(char symbol) {
    return (!isDNA(symbol) && isRNA(symbol));
}

bool Sequence::isValidMod(char symbol) {
       return (validMod.find(symbol) != validMod.end());
}

std::tuple<std::string, char, bool> Sequence::ParseSeq(std::string sequence, char mod, bool symbolErrorMode) {
    mod = (char)toupper(mod);
    bool can_be_rna = canBeRna(mod);
    bool can_be_dna = canBeDna(mod);
    bool can_be_protein = canBeAmino(mod);

    if (!isValidMod(mod)){
        throw std::invalid_argument("Invalid mod. Try 'U', 'N', 'P', 'D', 'R' instead of : " + mod);
    }

    std::string clean_seq = "";


    char symbol_mod;
    char symbol;
    size_t i = 0;
    while ((can_be_rna || can_be_dna || can_be_protein) && i < sequence.length()) {
        symbol_mod = identifyChar(symbol, symbolErrorMode);
        
        // Manage illegal chars


        i++;
        symbol = sequence[i];
    }
}
//     if (is_nucleic) {
//         if (mod == 'D') {
//             return std::tuple<std::string, char, bool> {clean_seq, 'D', (rna_marks==0)};
//         } else if (mod == 'R' || rna_marks > dna_marks) {
//             return std::tuple<std::string, char, bool> {clean_seq, 'R', (dna_marks==0)};
//         } else {
//             return std::tuple<std::string, char, bool> {clean_seq, 'D', (rna_marks==0)};
//         }
    
//     } else if (is_amino) {
//         return std::tuple<std::string, char, bool> {clean_seq, 'P', true};

//     } else {
//         throw std::invalid_argument("Can not proccess this sequence.");
//     }
// }

char Sequence::identifyChar(char symbol, bool errorMod) {
    if (!isLegalSymbol(symbol)) {
        if (errorMod) {
            throw std::domain_error("Illegal symbol found in this sequence : " + symbol);
        }

        return 'U';
    }
    if (isLegalNucleic(symbol)) {
        if (isDNASpecific(symbol)) {
            return 'D';

        } else if (isRNASpecific(symbol)) {
            return 'R';

        } else {
            return 'N';
        }

    } else if (isLegalAmino(symbol)) {
        return 'P';
    }

    // Not supposed to be reached.
    return 'U';
}
 

 bool canBeRna(char mod) {
    return (mod == 'R'  || mod == 'N' || mod == 'U');
 }
 bool canBeDna(char mod) {
    return (mod == 'D'  || mod == 'N' || mod == 'U');
 }  
 bool canBeAmino(char mod) {
    return (mod == 'P'  || mod == 'U');
 }  





// --- --- Getter --- --
const std::map<char, char>& Sequence::getLegalDNA() {
    return legalDNA;
}

const std::map<char, char>& Sequence::getLegalRNA() {
    return legalRNA;
}

const std::set<char>& Sequence::getLegalAmino() {
    return legalAmino;
}

const  std::map<char, char>& Sequence::getBridgeDNA_RNA() {
    return bridgeDNA_RNA;
}

const std::set<char>& Sequence::getValidMod() {
    return validMod;
}

// --- --- Biological transformations --- --
std::string Sequence::makeReverseComplement(const Sequence& seq, bool change_type, bool verbose) {
    std::string result = "";
    std::map<char, char>* equivalence_map;
    bool (*is_right_nucleotide_type)(char symbol);
    bool (*is_specific_to_nucleotide_type)(char symbol);
    bool is_strict = seq.getStrict();

    if (seq.getType() == 'D') {
        equivalence_map = &legalDNA;
        is_right_nucleotide_type = isDNA;
        is_specific_to_nucleotide_type = isDNASpecific;

    } else if (seq.getType() == 'R') {
        equivalence_map = &legalRNA;
        is_right_nucleotide_type = isRNA;
        is_specific_to_nucleotide_type = isRNASpecific;

    } else {
        throw std::domain_error("Can not make Reverse complement of a protein.");
    }

    if (!is_strict) {
        // std::cout << "This sequence is not strict. Their might be some data loss during the proccess. Sequence : \n" << seq << std::endl;
    }

    for (char symbols : seq.getSeq()) {
        if (!is_strict) {
            if (!is_right_nucleotide_type(symbols)) {
                symbols = bridgeDNA_RNA.at(symbols);
            }
        }

        symbols = equivalence_map->at(symbols);

        if (change_type && is_specific_to_nucleotide_type(symbols)) {
            symbols = bridgeDNA_RNA.at(symbols);
        }
        
        result.insert(0, 1, symbols);

    }

    return result;
}

// Message de Margaux Imbert : ":)"