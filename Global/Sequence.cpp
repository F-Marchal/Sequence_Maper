

#include "Sequence.hpp"
#include <fstream>
#include <string>
#include <iostream>
#include <stdexcept>
#include <set>

// Getter
Sequence::Sequence(std::string sequence, char mod, bool verbose) {
    std::tuple<std::string, char, bool>  result = ParseSeq(sequence, mod, verbose);

    this->seq = std::get<0>(result);
    this->type = std::get<1>(result);
    this->strict = std::get<2>(result);

}



std::tuple<std::string, char, bool> Sequence::ParseSeq(std::string sequence, char mod, bool verbose) {
    mod = (char)toupper(mod);
    bool is_amino = !(mod == 'R' || mod == 'D') ;
    bool is_nucleic = !(mod == 'P');
    char symbol;
    std::string clean_seq = "";

    size_t rna_marks = 0;
    size_t dna_marks = 0;
    size_t i = 0;

    while ((is_amino || is_nucleic) && i < sequence.length()) {
        symbol = sequence[i];

        if (!isLegalSymbol(symbol)) {
            if (verbose) {std::cout << "ParseSeq: ignored char at the position " << i << " : '" << symbol << "' (" << (int)symbol << ")." << std::endl;}
            i += 1;
            continue;
        }

        if (is_nucleic) {
            if (!isLegalNucleic(symbol)) {
                is_nucleic = false;
    
            } else if (isDnaSpecific(symbol)) {
                dna_marks += 1;
            } else if (isRnaSpecific(symbol)) {
                rna_marks += 1;
            }
        }

        if (is_amino && !isLegalAmino(symbol)) {
            is_amino = false;
        }

        clean_seq += symbol;
        i += 1;
    }

    if (is_nucleic) {
        if (mod == 'D') {
            return std::tuple<std::string, char, bool> {clean_seq, 'D', (rna_marks==0)};
        } else if (mod == 'R' || rna_marks > dna_marks) {
            return std::tuple<std::string, char, bool> {clean_seq, 'R', (dna_marks==0)};
        } else {
            return std::tuple<std::string, char, bool> {clean_seq, 'D', (rna_marks==0)};
        }
    
    } else if (is_amino) {
        return std::tuple<std::string, char, bool> {clean_seq, 'P', true};

    } else {
        throw std::invalid_argument("Can not proccess the sequence.");
    }

    
}

std::set<char> Sequence::legalNucleic = {
    'A', 'a', //A → Adenine 
    'B', 'b', //not A (i.e. C, G, T or U) → B comes after A
    'C', 'c', //C → Cytosine
    'D', 'd', //not C (i.e. A, G, T or U) → D comes after C

    'G', 'g', //G → Guanine
    'H', 'h', //not G (i.e., A, C, T or U) → H comes after G
    'I', 'i', //i → inosine (non-standard)
    'K', 'k', //G, T or U → bases which are Ketones

    'M', 'm', //A or C → bases with aMino groups
    'N', 'n', //A C G T U → Nucleic acid

    'R', 'r', //A or G (I) → puRine
    'S', 's', //C or G → Strong interaction
    'T', 't', //T → Thymine
    'U', 'u', //U → Uracil
    'V', 'v', //neither T nor U (i.e. A, C or G) → V comes after U
    'W', 'w', //A, T or U → Weak interaction
  
    'Y', 'y', //C, T or U → pYrimidines

    '-', //gap of indeterminate length 	
};

std::set<char> Sequence::dnaSpecific = {
    'T', 't', //T → Thymine
};

std::set<char> Sequence::rnaSpecific = {
     'U', 'u', //U → Uracil
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




bool Sequence::isLegalNucleic(char symbol) {
    return (legalNucleic.find(symbol) != legalNucleic.end());
}

bool Sequence::isLegalAmino(char symbol) {
    return (legalAmino.find(symbol) != legalAmino.end());
}

bool Sequence::isLegalSymbol(char symbol) {
    return (isLegalAmino(symbol) || isLegalNucleic(symbol));
}

bool Sequence::isDnaSpecific(char symbol) {
    return (dnaSpecific.find(symbol) != dnaSpecific.end());
}

bool Sequence::isRnaSpecific(char symbol) {
    return (rnaSpecific.find(symbol) != rnaSpecific.end());
}

