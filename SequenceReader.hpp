#include <set>
/* TODO: 
 *
 *
 */
class SequenceReader {
    private:
        static std::set<char> legalNucleicChar;
        static std::set<char> legalAminoChar;
        static std::set<char> legalMultiHeaderChar;
        static std::set<char> legalMonoHeaderChar;
        static std::set<char> legalCommentChar;
        static std::set<char> blankChar;
 
    public:
        bool static isNucleicChar(char nucleic);
        bool static isAminoChar(char amino);
        bool static isLegalChar(char aminoNucl);
        bool static isHeaderChar(char header_char);
        bool static isMonoHeaderChar(char header_char);
        bool static isMultiHeaderChar(char header_char);
        bool static isCommentChar(char comment_char);
        bool static isBlankChar(char blank);

};
