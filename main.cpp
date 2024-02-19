#include "Sequence.hpp"
#include "Fasta.hpp"
#include <time.h>
#include <string>
#include <iostream> // pour cout/endl/...
#include <fstream>  // pour ifstream

//TODO: Parse Fasta Header
//TODO: Start FastQ Class

int main() {
    std::cout<< "Start : " << std::endl;
    Sequence seq("AUUCGUUGTWTRP75", 'P');

    std::cout<<seq.getStrict()<<std::endl;
    std::cout<<seq.getType()<<std::endl;
    for(const auto& elem : seq.getComment()) {std::cout << elem.first << " " << elem.second << "\n";}

    
    for(auto& elem : Fasta::loadFastaFromFile("Tests/Fastas/nasty.fasta")) {std::cout << elem.getSequence().getSeq() << "\n\n";}

    std::cout<<"Yey"<<std::endl;



    return 0;
}

