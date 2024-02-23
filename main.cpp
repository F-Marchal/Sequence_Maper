#include "Fasta/Fasta.hpp"
#include "Fasta/FastaHeader.hpp"
#include <time.h>
#include <string>
#include <iostream> // pour cout/endl/...
#include <fstream>  // pour ifstream


/* TODO: Netoyer les fonctions 
 * TODO: Ranger les fonctions 
 * TODO: Faire les docstrings
 *  - TODO: Test de fonctionnenement
 *  - TODO: Test complexité
 *
 *
 * TODO: FastQ
 *
*/

/*
int main() {
    std::cout<< "Start : " << std::endl;

    for(Fasta& elem : Fasta::loadFastaFromFile("Tests/Fastas/nasty.fasta")) {
        std::cout << "------------------------------------------------" << std::endl;
        std::cout << elem.getHeader() << std::endl;
        std::cout << elem.getCleanSequence(5, 2) << "\n\n";
        for(const auto& alam : elem.getSequence().getAllComment()) {std::cout << alam.first << " " << alam.second << "\n";}
        std::cout << "------------------------------------------------" << std::endl;
    }

    std::cout<<"Yey"<<std::endl;



    return 0;
}

*/
int main() {
    std::cout<< "Start : " << std::endl;
    FastaHeader("gi|numéro gi|gb|numéro d'accession|locus prout adn alpha=1");
    std::cout<<"Yey"<<std::endl;
}