#include "SequenceReader.hpp"
#include <string>
#include <map>
#include <tuple>
#include <fstream>  // pour ifstream

class FastaSeq : public SequenceReader {
    private:
        std::string header;
        std::string sequence;
        std::map<unsigned int, std::string> comments;

    public:
       void readFasta(std::ifstream& file_flux);

    

};

