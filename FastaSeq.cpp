#include "FastaSeq.hpp"

#include <iostream> // pour cout/endl/...
#include <fstream>  // pour ifstream

void FastaSeq::readFasta(std::string path) {
    std::ifstream file_flux(path);

    if (!file_flux.is_open()) {
        std::cout << "Can not open the file : "
                  << "'" << path << "'" << std::endl;
        return ;
    }

    // prepare to loop into the file.
    char current_char;                  // Memorize the value of the current char.
    char next_char;                     // Memorize the value of the next char.

    std::string current_header;         // Memorize the value of the next char.

    unsigned int file_column;           // Store the 'x' position of <current_char> 
    unsigned int file_line;             // Store the 'y' position of <current_char> 

    bool in_header = false;             // Do <current_char> is inside an Header
    bool in_sequence = false;           // Do <current_char> is inside an sequence
    bool in_comment = false;            // Do <current_char> is inside an comment

    while (file_flux) {
        current_char = file_flux.get();
        file_column += 1;

        if (current_char == '\n') {
            // End the line and start a new one:
            file_column = 0;
            file_line += 1;
            in_comment = false;

            next_char = file_flux.peek();

            if (this->isHeaderChar(next_char)) {
                if (!in_header) {
                    // We quit a sequence and we enter inside a new header
                    bool in_sequence = false;
                    bool in_sequence = true;
                }

            } else {
                bool in_sequence = false;
                bool in_sequence = true;
            }

            continue;
        }

        
     }
    





}