#include "FastaSeq.hpp"
#include <string>
#include <iostream> // pour cout/endl/...
#include <fstream>  // pour ifstream


void FastaSeq::readFasta(std::ifstream& file_flux) {
    if (!file_flux.is_open()) {
        std::cout << "Can not use the file : "
                  << "'file_flux'" << std::endl;
        return ;
    }

    bool in_sequence = false;       // Do <current_char> is inside a sequence ?
    bool in_comment = false;        // Do <current_char> is inside a comment ?
    bool in_header = false;         // Do <current_char> is inside a header ?
    bool exit = false;          // Do the loop should stop now ?

    char current_char;      // Contain the current char that is read inside <file_flux>.
    char last_char = '\n';  /* Contain the value that <current_char> contained during the last loop.
                             * This var is initialised at '\n' since we assume that <file_flux.get> will return the first char of a line. 
                             * With a few tweaks, this variable cane be removed. 
                             * I prefer to keep it, since it increase the readability of the code. */

    std::string header = "";    // Store chars that belong to the header.
    std::string sequence = "";  // Store chars that belong to the sequence.
    std::string current_comment = "";  // Store chars that belong to a comment.

    while (file_flux && !exit) {
        // --- Header & sequence verifications --- :
        if (last_char == '\n') {
            // → We are at the beginning of a new line
            current_char = file_flux.peek(); // We use <ifstream.peek> in order to avoid moving too far inside the file.

            // --- --- --- Header Detection --- --- --- 
            if (this->isHeaderChar(current_char)) {    
                // → Header symbol at the beginning of the line.
        
                if (in_sequence) {
                    // A new header has been reached. This sequence end here.
                    exit = true;    // Will end the loop
                    continue;
                }

                if (in_header) {
                    // We are in a multi-line header. Nothing more to do.
                } else {
                    // We start the header of the sequence.
                    in_header = true;
                }

            // --- --- --- Sequence Detection --- --- --- 
            } else if (in_header) {
                // → We are leaving a header. (The last <if> assure that the next char does not announce a header)
                in_header = false;
                in_sequence = true;
            }
        }

        //  --- Advance in the file --- 
        current_char = (char)file_flux.get();


        // --- --- Header --- ---
        if (in_header){
            header += current_char;

        // --- --- Sequence --- ---
        } else if (in_sequence) {
            // Being inside a comment
            if (in_comment) {
                if (current_char == '\n') {
                    // We are leaving this comment
                    in_comment = false;
                    //TODO: Save the comment
                    current_comment = "";
        
                } else {
                    current_comment += current_char;
                }
            
            // Entering inside a comment
            } else if (this->isCommentChar(current_char)) {
                in_comment = true;
                current_comment += current_char;
            
            // Normal sequence behaviour
            } else if (!this->isBlankChar(current_char)) {
                sequence += current_char;
            }
            

        } else {
            // If this isn't a sequence nor a header, we have nothing to do.
        }
    
        // --- Update <last_char> --- 
        last_char = current_char;

    }
    std::cout << header << std::endl;
    std::cout << sequence << std::endl;
}

    

/* 
void old(std::string path) {
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
                std::cout << clean_sequence << std::endl;

            }

            if (in_comment) {
                // TODO: Save the comment
                std::cout << comment << std::endl;
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
*/