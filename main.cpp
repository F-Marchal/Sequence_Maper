#include "Global/Sequence.hpp"
#include "Global/Header.hpp"
#include "Fasta/FastaSequence.hpp"
#include "Fasta/Fasta.hpp"
#include "Fasta/FastaHeader.hpp"

#include <time.h>
#include <string>
#include <iostream> // pour cout/endl/...
#include <fstream>  // pour ifstream

/* Methodes abstracts :
 * Les fonctions sans corps sont abstraites ET DOIVENT être implementés dans les class filles
 *
 * 
 * virtual void mv1();
 * virtual void mv2() = 0;
 * 
 * 
 * 
 * virtual -> Les redifinitions primes sur la truc la plus gaure (Ce qui est surchargeable)
 * non virtual -> Ce qui n'est pas surchargeable (Cette methode prime)
 * 
 * penser au mot clef @overide
 * 
 * ClassName::ClassName(Classname ref&) {
 *      (# constructeur par copie)
 *      # Do somethinf if the item is copied
 * } // Possibilité d'avoir un switch de passage de ref ou de truc differet
 * 
 * 
 * mot clef const :  (lecture seule)
 *      dans fonction(const item) -- On ne peut utilisier que les methodes 'const') 
 *      'const' permet de passer une reference (moins gourmand que qu'une copie complete) mais restreind les methodes 
 *      Les methodes ne modifiant pas l'objet doivent être marqués const
 *       
 * 
 * 
 * 
 *  Make  -c --> fichier en .O Permet de faiee un test simple ( un seul truv vompilé)
 *  On peut compiler le truc total à partir de des .O (pas obligé de recompiler tout le prog)
 * Utiliser g++ -MM *.cpp --> Donne toutes le dependences de tous le cpp : Permet d'avoir toutes les regles pour faire tous les .o
 * 
 * 
 * Table des suffixes :
 *  Determiner facilement a quels endroits se trouvent une sous sequence
 *  Methode simple : Tout lire (Fouille de donné c'est long)
 *  Methode rapide : Dictionnaire :
 *      Ensemble des mots ecrits dans un texte
 *      On range tous les mots du textes dans l'ordre
 * 
 *  Foncteur : Class qui se comporte comme une fonction
 * 
 *  git bissect
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 */

/* TODO: Netoyer les fonctions 
 * TODO: Ranger les fonctions 
 * TODO: Faire les docstrings
 *  - TODO: Test de fonctionnenement
 *  - TODO: Test complexité
 *
 * TODO: Convention de nommage : _privateAttr
 * TODO: FastQ 
 *
*/

int main() {
    std::cout<< "Start : " << std::endl;

    Sequence seq("ATCG");
    std::cout << "INI   " << seq.getSeq() << std::endl;
    std::cout << "Rev   " << seq.getReverseComplement().toString() << std::endl;
    std::cout << "Trans " << seq.makeReverseComplement(seq) << std::endl;

    std::cout<< seq.toString() << std::endl;
    std::cout<< "End : " << std::endl;

}

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
