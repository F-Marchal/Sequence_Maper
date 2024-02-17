#include <set>
/* TODO: 
 *
 *
 */
class SequenceReader {
    private:
        static std::set<char> legalNucleicChar;
        static std::set<char> legalAminoChar;
        static std::set<char> blankChar;
 
    public:
        bool isNucleicChar(char nucleic);
        bool isAminoChar(char amino);
        bool isBlankChar(char blank);

};
