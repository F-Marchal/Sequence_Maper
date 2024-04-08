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
    // BitVector bv(5, 2);
    // std::cout << "----" << std::endl;
    // bv.set(0, (char) 0b00000111);
    // bv.set(1, (char) 0b00000001);
    // bv.set(2, (char) 0b00000111);
    // std::cout << "----" << std::endl;
    // char * str =  bv[0];

    // for (long unsigned int i = 0; i < 2; i++) {
    //     displayBits((char)str[i]);
    // }
    // delete [] str;
    int * pattern = new int[1] {0b00011010};
    int * final_list = new int [2] {0b00000000, 0b00000000};
    BitVector::Coords element(0, 5);
    BitVector::Coords pattern_coord(0, 0);
    BitVector::Coords final_coord(0, 0);

    BitVector::Coords pattern_end_coord = pattern_coord + element;
    BitVector::Coords final_end_coord = final_coord + element;
    BitVector::Coords step_left = element;
    
    
    bool final_end_is_right = false;
    bool pattern_end_is_right = true;

    short unsigned int pattern_bit_value;
    short unsigned int final_list_bit_value;

    char pattern_bit;
    char final_mask;

    while (final_coord != final_end_coord) {
        
        if (final_end_is_right && final_coord.getOctet() == final_end_coord.getOctet()) {
            final_list_bit_value = step_left.getBit();
        } else {
            final_list_bit_value = 7 - final_coord.getBit();
        }

        if (pattern_end_is_right && pattern_coord.getOctet() == pattern_end_coord.getOctet()) {
            pattern_bit_value = step_left.getBit();
        } else {
            pattern_bit_value = 7 - pattern_coord.getBit();
        }
        
        pattern_bit = 1 << pattern_bit_value;
        final_mask = 1 << final_list_bit_value;
        
        std::cout << pattern_bit_value << " " <<step_left.getBit() << std::endl;

        if (pattern[pattern_coord.getOctet()] & pattern_bit) {
            final_list[final_coord.getOctet()] |= final_mask;

        } else {
            final_list[final_coord.getOctet()] &= ~final_mask;
        }
        
        final_coord++;
        pattern_coord++;
        step_left --;

        
    }
    displayBits(pattern[0]);
    std::cout  << std::endl;
    displayBits(final_list[0]);
    displayBits(final_list[1]);
    // BitVector::copyBits(from_1, to, element,  BitVector::Coords(0, 0), to_coord, false, false);
    // displayBits(from_1[0]);
    // std::cout  << std::endl;
    // for (long unsigned int i = 0; i < 2; i++) {
    //     displayBits(to[i]);
    // }
    // to_coord += element;

    // std::cout << "----" << std::endl;
    // BitVector::copyBits(from_2, to, element,  BitVector::Coords(0, 0), to_coord, false, true);
    // displayBits(from_2[0]);
    // std::cout  << std::endl;
    // for (long unsigned int i = 0; i < 2; i++) {
    //     displayBits(to[i]);
    // }
    // to_coord += element;

    // std::cout << "----" << std::endl;
    // BitVector::copyBits(from_3, to, element,  BitVector::Coords(0, 0), to_coord, false, true);
    // displayBits(from_3[0]);
    // std::cout  << std::endl;
    // for (long unsigned int i = 0; i < 2; i++) {
    //     displayBits(to[i]);
    // }
    // to_coord += element;





    // Retransform to vit


    // size_t i = 0;
    // while (i != 48) {
    //    i ++;
    // }

    // size_t main_tab = SIZE_MAX;



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
