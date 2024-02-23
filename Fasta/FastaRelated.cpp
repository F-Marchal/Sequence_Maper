#include "FastaRelated.hpp"
#include <set>

std::set<char> FastaRelated::legalMultiHeaderChar = {
    ';',
};

std::set<char> FastaRelated::legalMonoHeaderChar = {
    '>',
};

std::set<char> FastaRelated::legalCommentChar = {
    ';',
};

std::set<char> FastaRelated::blankChar = {
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

bool FastaRelated::isHeaderChar(char header_char) {
    return (isMonoHeaderChar(header_char) || isMultiHeaderChar(header_char));
}

bool FastaRelated::isMonoHeaderChar(char header_char) {
    return (legalMonoHeaderChar.find(header_char) != legalMonoHeaderChar.end());
}

bool FastaRelated::isMultiHeaderChar(char header_char) {
    return (legalMultiHeaderChar.find(header_char) != legalMultiHeaderChar.end());
}

bool FastaRelated::isCommentChar(char comment_char) {
    return (legalCommentChar.find(comment_char) != legalCommentChar.end());
}

bool FastaRelated::isBlankChar(char blank) {
    return (blankChar.find(blank) != blankChar.end());
}
