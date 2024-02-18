#include "FastaSeq.hpp"
#include <string>
#include <iostream> // pour cout/endl/...
#include <fstream>  // pour ifstream
#include <map>

//debug
#include <typeinfo>

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
    std::map<size_t, std::string> comments;


    while (file_flux && !exit) {
        // --- Header & sequence verifications --- :
        if (last_char == '\n') {
            // → We are at the beginning of a new line
            
            current_char = file_flux.peek(); // We use <ifstream.peek> in order to avoid moving too far inside the file.
            if ((int)current_char == -1) {
                // Assure that the end of the file is treated as a line break
                current_char = '\n';
            }

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
        if ((int)current_char == -1) {
            // Assure that the end of the file is treated as a line break
            current_char = '\n';
        }

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

                    // Save the comment
                    if (comments.count(sequence.length()) >= 1){
                        comments[sequence.length()] += current_comment;

                    } else {
                        comments[sequence.length()] = current_comment;
                    }
                    
                    // clear <current_comment>
                    current_comment.clear();
        
                } else {
                    current_comment += current_char;
                }
            
            // Entering inside a comment
            } else if (this->isCommentChar(current_char)) {
                in_comment = true;
            
            // Normal sequence behaviour
            } else if (this->isBlankChar(current_char)) {
                // pass

            } else if (this->isLegalChar(current_char)) {
                //TODO: Store an error when is not legal char
                sequence += current_char;
            } else {
                std::cout << current_char << std::endl;
            }
            

        } else {
            // If this isn't a sequence nor a header, we have nothing to do.
        }
    
        // --- Update <last_char> --- 
        last_char = current_char;
    }

    std::cout << header << std::endl;
    std::cout << sequence << std::endl;
    for(const auto& elem : comments) {std::cout << elem.first << " " << elem.second << "\n";}


}

