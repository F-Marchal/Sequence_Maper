#ifndef FASTACONSTS_HPP
#define FASTACONSTS_HPP
#include <set>

class FastaRelated {
private:
    static std::set<char> legalMultiHeaderChar;
    static std::set<char> legalMonoHeaderChar;
    static std::set<char> legalCommentChar;
    static std::set<char> blankChar;

public:
    static bool isHeaderChar(char header_char);
    static bool isMonoHeaderChar(char header_char);
    static bool isMultiHeaderChar(char header_char);
    static bool isCommentChar(char comment_char);
    static bool isBlankChar(char blank);
};





#endif