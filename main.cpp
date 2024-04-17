#include <time.h>
#include <string>
#include <iostream> // pour cout/endl/...
#include <fstream>  // pour ifstream
#include <vector>
#include <map>

#include "Global/Sequence.hpp"
#include "Global/Utilities.hpp"
#include "Fasta/FastaRelated.hpp"
#include "Fasta/FastaHeader.hpp"







int main() {
    std::string seq =  "AAADDDAAAABBTTTTTCCCCGGGG";
    std::cout << "Test sequence " << seq << std::endl;
    std::cout << "Resultats :" << std::endl;
    std::cout << "             " << Sequence(seq, 'D', Sequence::basic) << std::endl;
    std::cout << "             " << Sequence(seq, 'D', Sequence::basic) << std::endl;
    std::cout << "             " << Sequence(seq, 'D', Sequence::basic) << std::endl;
    std::cout << "             " << Sequence(seq, 'D', Sequence::basic) << std::endl;
    std::cout << "             " << Sequence(seq, 'D', Sequence::basic) << std::endl;
    return 0;
}
