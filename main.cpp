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


#include <array>
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
 * Tout est ranger par ordre alphabetique.
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
    // BitVector vec(8);

    // std::cout << vec.getMaximalNumberOfElements() <<std::endl;
    // std::cout << vec.getMaximalNumberOfOctet() << std::endl;


    // size_t elementNumber = SIZE_MAX - 1;
    // unsigned short int element_size = 9;
    
    // double octet_usage_per_element = element_size / 8.0;
    // size_t octet_number = elementNumber * octet_usage_per_element;


    // std::cout <<octet_number << " " << octet_usage_per_element << std::endl; 


    // Do not wotk due to double memory limitations.
    // size_t octet_number =  (__SIZE_MAX__) / 10;
    // size_t bit_number = 8;
    // unsigned short int element_size = 9;


    // double element_per_octet = 8.0 / element_size;
    // size_t elements_count = octet_number * element_per_octet;
    // std::cout << octet_number << " " <<  elements_count / element_per_octet << std::endl; 
    // size_t bit_left = (octet_number - elements_count / element_per_octet) * 8 + bit_number;
    // std::cout << elements_count << " " << bit_left << std::endl; 
    // elements_count += bit_left / element_size;
    // bit_left -= (bit_left / element_size) * element_size;
    // std::cout <<elements_count << " " << bit_left << std::endl; 
    

    size_t octet_number =  (__SIZE_MAX__) / 1000 * 1000;
    // size_t bit_number = 8;
    unsigned short int element_size = 8;
    std::cout << element_size << " " << ( unsigned short int)((double)(element_size)) << std::endl;
    // Missing bits :
    
    // Extract number of octet that can be filled by a unique element.
    unsigned short int uncompleted_octet_per_element = element_size / 8;  
    unsigned short int bit_per_element = element_size - uncompleted_octet_per_element * 8;  

    size_t octet_per_element = uncompleted_octet_per_element * 1000 + (bit_per_element / 8.0) * 1000;
    
    // Use the power of division to retrieve how much can be stuffed intoo octet_number
    size_t number_of_elements = octet_number / octet_per_element;
    size_t really_used_octet = octet_number / octet_per_element * octet_per_element;
    size_t unused_octet = octet_number - really_used_octet;

    
    std::cout << number_of_elements << " \n" << really_used_octet << " \n" << unused_octet << std::endl;
    
    // Retransform to vit


    // size_t i = 0;
    // while (i != 48) {
    //    i ++;
    // }

    // size_t alpha = SIZE_MAX;



            // float temp = 1.0 / 3.0;
    // float a = 0;
    // float b = 0;
    // float temp2;
    // std::cout << temp * 3 <<  " " << temp * 3.0 + 1.0 / 10.0 << std::endl; 
    // short unsigned int i = 1;
    // float j = 1;
    // while (i != 0) {
    //     i+=1;
    //     j+=1;
    //     b = j;
    //     a = 8;
    //     temp = a / b;
    //     temp2 = (1.0 / temp * a);
    //     std::cout << "Bool=" << (temp2==j) << " " << temp2 << " " << j  << " "<< (j == i)<< " "<< (unsigned int)(temp2) <<std::endl;
    // }
    // std::cout << 1.0 / 3 * 3  <<std::endl;
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
