#include <string>
#include <iostream> // pour cout/endl/..
#include <set>
#include <tuple>

class Sequence
{
private:
    std::string seq;
    char type;
    bool strict;

    static std::set<char> legalNucleic;
    static std::set<char> dnaSpecific;
    static std::set<char> rnaSpecific;
    static std::set<char> legalAmino;





public:
    // --- --- --- Getter & Setters --- --- --
    std::string getSeq() {return this->seq;}
    char getType() {return this->type;}
    bool getStrict() {return this->strict;}

    Sequence(std::string sequence);
    Sequence(std::string Sequence, char mod);
    Sequence(std::string Sequence, bool verbose);
    Sequence(std::string Sequence, char mod, bool verbose);



    static std::tuple<std::string, char, bool> ParseSeq(std::string sequence, char mod, bool verbose);
    static bool isLegalNucleic(char symbol);
    static bool isLegalAmino(char symbol);
    static bool isLegalSymbol(char symbol);
    static bool isDnaSpecific(char symbol);
    static bool isRnaSpecific(char symbol);




};

