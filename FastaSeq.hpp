#include "SequenceReader.hpp"
#include <string>
class FastaSeq : public SequenceReader {
public:
    void readFasta(std::string path);
};

