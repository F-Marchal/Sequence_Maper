/**
 * @file main.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-03-08
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "Global/Sequence.hpp"
#include "Global/BitVector.hpp"
#include "Fasta/Fasta.hpp"

#include <time.h>
#include <string>
#include "Global/Utilities.hpp"
#include <iostream> // pour cout/endl/...
#include <fstream>  // pour ifstream


#include <vector>
#include <map>
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
 *      Les methodes ne modifiant pas l'modifet doivent être marqués const
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
 * R O U D O U D O U $
 * 1 2 3 4 5 6 7 8 9 10
 * 
 * D est en position 4 et 7
 * D : 4, 7 :
 * O : 2, 5, 8:
 * 
 * A B C
 * 0 0 &
 * 7 0 Dou&
 * 4 3 DouDou&
 * 8 0 Ou$
 * 5 2 OuDou&
 * 2 5 OuDouDou&
 * 9 0 U&
 * 6 1 UDou&
 * 3 4 UDouDou&
 * 1 0 RouDouDou&
 * 
 * 
 * A = Table des suffixes
 * C = Equivalent en lettre des suffixes MOT[B[I] : ]
 * B = Nombre de lettre en commun avec le precedent suffixe (LCP)
 * 
 * Tout est ranger par ordre main_tabbetique.
 * 
 * 
 *  Construteur par copie  + Destructeur + destructeur
 * 
 * Economiser de l'espace en "compressant" les chars en bytes : A, T, C, G = 00, 01, 10, 11 : Codage sur 2 bytes
 * 
 * Operateur d'afectation if (&A != this) {...} retturn *this
 * 
 * ++ return nouvel seq
 * 
 * 
 * 
 * Doxy -X : Update doc ?
 * 
 * TODO: Debian test unnitaires
 * 
 * TODO: CICD
 * 
 * TODO: Lire compter la taille de la seqeunce pour faire l'alocation de maniére propre
 * 
 */




int main() {
   

    // std::cout << (mySet.find('A') != mySet.end()) << std::endl;
    // std::cout << (mySet.find(Sequence::SequenceSymbol('Z', "A", Sequence::all)) != mySet.end()) << std::endl;
    for (char c : Sequence("ABBBBBBGA", 'N', Sequence::most)) {
        std::cout << c << std::endl;
    }

}

    // BitVector vec(2);
    // void reserveCapacity(size_t element_number);
    // void resizeCapacity(size_t element_number);
    // void shrinkCapacity();

    // void append(const & std::array<short unsigned int> values);
    // void insert(size_t position, const & std::array<short unsigned int> values);





    


    // std::cout << a / 3 << " " << a / 6 <<  " " << a / 7 << std::endl; 
 
    // Double Size : b = a * 2 SI a < b

    // Sequence seq("ACG", display);

    // std::cout << "Seq\n" << seq << std::endl << std::endl;
    // std::cout << "Type\n" << seq.getType() << std::endl << std::endl;
    
    // seq.activeTypeResearch();

    // seq.insertFront("T");

    // seq.endTypeResearch();

    // seq.insertFront("U");

    // std::cout << "Seq\n" << seq << std::endl << std::endl;
    // std::cout << "Type\n" << seq.getType() << std::endl << std::endl;
    // seq.insertSeq(1, seq_2);

    // std::cout << "A\n" << seq << std::endl << std::endl;
    // seq.eraseSeq(1, 3);
    // std::cout << "B\n" << seq << std::endl << std::endl;


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
