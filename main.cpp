/*! \mainpage HAU803I Développement opérationnel avancé : application aux gros volumes de données | mapping de données issues de Nouvelles Générations de Séquenceurs (NGS) sur un génome de référence. 
 *
 * \section un_mot Un mot sur le projet
 * Dans le cadre du Master de bio-informatique de Montpellier, les étudiants ont suivi un module 
 * ayant pour but de les initier au développement opérationnel (HAU803I). Pour cela, il leur a été 
 * demandé de réaliser un projet visant à créer un mapper pour des séquences génomiques courtes tout 
 * en faisant attention aux complexités en temps et en espace. Ce module se conclut par un oral et
 *  un rapport (cf Readmed.pdf) visant à évaluer, non pas la qualité du code mais le degré de 
 * compréhension des concepts abordés tout au long de ce module.  
 *
 * Connaissant les règles d’évaluation et sachant que ce genre d’API existe déjà, 
 * je n’ai pas concentré mes efforts sur l’accomplissement du projet mais sur 
 * l’apprentissage du C++ et des sujets abordés en cours Ce projet n’est en aucun 
 * cas terminé. Si vous pouvez utilisez les différentes classes du projet, aucune 
 * garantie n’est proposé quand au fonctionnement de celles-ci.
 *
 * \section mention_leg Mention légale
 * CC-by-sa (Attribution / Partage dans les mêmes conditions)
 *
 */
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
