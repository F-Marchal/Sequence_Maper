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

    std::string current_header = "";         // Memorize the value of the next char.
    std::string clean_line = "";
    std::string clean_sequence = "";         // Save the sequence 
    std::string comment = "";

    unsigned int file_column;           // Store the 'x' position of <current_char> 
    unsigned int file_line;             // Store the 'y' position of <current_char> 

    bool in_header = false;             // Do <current_char> is inside an Header
    bool in_sequence = false;           // Do <current_char> is inside an sequence
    bool in_comment = false;            // Do <current_char> is inside an comment

    while (file_flux) {
        current_char = file_flux.get();
        file_column += 1;


        // --- --- --- \n --- --- ---
        if (current_char == '\n') {
            // End the line and start a new one:
            file_column = 0;
            file_line += 1;
            in_comment = false;

            next_char = file_flux.peek();

            if (this->isHeaderChar(next_char)) {
                // We are entering / continuing inside a header
                if (!in_header) {
                    // We quit a sequence and we enter inside a new header
                    bool in_sequence = false;
                    bool in_header = true;
                    // TODO: Save the header and the sequence
                    current_header = clean_line;

                } else {
                    // We are continuing inside a header
                    current_header += "\n" + clean_line;
                }

            } else {
                // We are leaving the header OR we are not inside an header
                bool in_header = false;
                bool in_sequence = true;
                bool in_comment = false;
                clean_sequence += clean_line;

            }

            if (in_comment) {
                // TODO: Save the comment
                comment = "";
            }

            continue;
        }

        // --- --- --- Special situations --- --- ---
        if (in_header){
            // save the char for latter
            clean_line += current_char;

        } else if (in_comment){
            // save the char for latter
            comment += current_char;

        } else if (in_sequence) {
            // --- --- Blank chars --- ---
            if (this->isBlankChar(current_char)) {
                continue;
            }

            // --- --- Comments chars --- --- 
            if (this->isCommentChar(current_char)) {
                in_comment = true;
                continue;
            }
            
            //TODO: Verify the char 
            clean_line += current_char;
        }
    } // close while
}