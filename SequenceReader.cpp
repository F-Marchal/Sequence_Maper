#include "SequenceReader.hpp"
#include <set>



// --- --- --- --- Static attributes --- --- --- --- 
std::set<char> SequenceReader::legalNucleicChar = {
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

std::set<char> SequenceReader::legalAminoChar = {

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

std::set<char> SequenceReader::legalMultiHeaderChar = {
    ';',
};

std::set<char> SequenceReader::legalMonoHeaderChar = {
    '>',
};

std::set<char> SequenceReader::legalCommentChar = {
    ';',
};

std::set<char> SequenceReader::blankChar = {
    (char)1,
    (char)2,
    (char)3,
    (char)4,
    (char)5,
    (char)6,
    (char)7,
    (char)8,
    (char)9,
    (char)10, // \n
    (char)11,
    (char)12,
    (char)13,
    (char)14,
    (char)15,
    (char)16,
    (char)17,
    (char)18,
    (char)19,
    (char)20,
    (char)21,
    (char)22,
    (char)23,
    (char)24,
    (char)25,
    (char)26,
    (char)27,
    (char)28,
    (char)29,
    (char)30,
    (char)31,
    (char)32,
};



// --- --- --- --- Static Methods --- --- --- --- 
bool SequenceReader::isNucleicChar(char nucleic){
    return (legalNucleicChar.find(nucleic) != legalNucleicChar.end());
}

bool SequenceReader::isAminoChar(char amino) {
    return (legalAminoChar.find(amino) != legalAminoChar.end());
}

bool SequenceReader::isLegalChar(char aminoNucl) {
     return (isAminoChar(aminoNucl) || isNucleicChar(aminoNucl));
}

bool SequenceReader::isHeaderChar(char header_char) {
    return (isMonoHeaderChar(header_char) || isMultiHeaderChar(header_char));
}

bool SequenceReader::isMonoHeaderChar(char header_char) {
    return (legalMonoHeaderChar.find(header_char) != legalMonoHeaderChar.end());
}

bool SequenceReader::isMultiHeaderChar(char header_char) {
    return (legalMultiHeaderChar.find(header_char) != legalMultiHeaderChar.end());
}

bool SequenceReader::isCommentChar(char comment_char) {
    return (legalCommentChar.find(comment_char) != legalCommentChar.end());
}

bool SequenceReader::isBlankChar(char blank) {
    return (blankChar.find(blank) != blankChar.end());
}



