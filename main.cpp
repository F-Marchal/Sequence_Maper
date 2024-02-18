
#include "FastaSeq.hpp"
#include <string>
#include <iostream> // pour cout/endl/...
#include <fstream>  // pour ifstream

int main() {

    FastaSeq fseq = FastaSeq();
    fseq.isAminoChar('h');

    std::ifstream file_flux("Tests/Fastas/nasty.fasta");

    while (file_flux)
    {
        fseq.readFasta(file_flux);
    }
    



    std::cout<<"Yey"<<std::endl;
    return 0;
}

