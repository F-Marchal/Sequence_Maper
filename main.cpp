
#include "FastaSeq.hpp"
#include <string>
#include <iostream> // pour cout/endl/...
#include <fstream>  // pour ifstream

int main() {

    FastaSeq fseq = FastaSeq();
    fseq.isAminoChar('h');
    fseq.readFasta("Tests/Fastas/multi.fasta");
    return 0;
}

