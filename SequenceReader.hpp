#include <set>
/* TODO: 
 *
 *
 */
class SequenceReader {
    private:
        static std::set<char> legalNucleicChar;
        static std::set<char> legalAminoChar;
        static std::set<char> legalHeaderChar;
        static std::set<char> legalCommentChar;
        static std::set<char> blankChar;
 
    public:
        bool isNucleicChar(char nucleic);
        bool isAminoChar(char amino);
        bool isHeaderChar(char header_char);
        bool isCommentChar(char comment_char);
        bool isBlankChar(char blank);

};
