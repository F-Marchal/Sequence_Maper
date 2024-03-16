// #include "FastaSequence.hpp"
// #include "Fasta.hpp"
// #include "FastaHeader.hpp"
// #include <string>
// #include <iostream> // pour cout/endl/...
// #include <fstream>  // pour ifstream
// #include <map>
// #include <tuple>
// #include <vector>

// std::tuple<std::string, std::string, std::map<size_t, std::string>>
// Fasta::parseFasta(std::ifstream& file_flux, unsigned int& current_line, bool verbose) {
//     bool in_sequence = false;       // Do <current_char> is inside a sequence ?
//     bool in_comment = false;        // Do <current_char> is inside a comment ?
//     bool in_header = false;         // Do <current_char> is inside a header ?
//     bool exit = false;              // Do the loop should stop now ?

//     char current_char;      // Contain the current char that is read inside <file_flux>.
//     unsigned current_column = 1;
//     char last_char = '\n';  /* Contain the value that <current_char> contained during the last loop.
//                              * This var is initialised at '\n' since we assume that <file_flux.get> will return the first char of a line. 
//                              * With a few tweaks, this variable cane be removed. 
//                              * I prefer to keep it, since it increase the readability of the code. */

//     std::string header = "";    // Store chars that belong to the header.
//     std::string sequence = "";  // Store chars that belong to the sequence.
//     std::string current_comment = "";  // Store chars that belong to a comment.
//     std::map<size_t, std::string> comments; // Store comments. Comments are stored using their positions inside the sequences.

//     if (!file_flux.is_open()) {
//         //TODO: raise error
//         std::cout << "Can not use the file : "
//                     << "'file_flux'" << std::endl;
//         return std::tuple<std::string, std::string, std::map<size_t, std::string>> {
//                         header,      sequence,    comments,         
//         };
//     }

//     while (file_flux && !exit) {
//         // --- Header & sequence verifications --- :
//         if (last_char == '\n') {
//             // → We are at the beginning of a new line
            
//             current_char = file_flux.peek(); // We use <ifstream.peek> in order to avoid moving too far inside the file.
//             if ((int)current_char == -1) {
//                 // Assure that the end of the file is treated as a line break
//                 current_char = '\n';
//             }

//             // --- --- --- Header Detection --- --- --- 
//             if (isHeaderChar(current_char)) {    
//                 // → Header symbol at the beginning of the line.
        
//                 if (in_sequence) {
//                     // A new header has been reached. This sequence end here.
//                     exit = true;    // Will end the loop
//                     continue;
//                 }

//                 if (in_header) {
//                     // We are in a multi-line header. Nothing more to do.
//                 } else {
//                     // We start the header of the sequence.
//                     in_header = true;
//                 }

//             // --- --- --- Sequence Detection --- --- --- 
//             } else if (in_header) {
//                 // → We are leaving a header. (The last <if> assure that the next char does not announce a header)
//                 in_header = false;
//                 in_sequence = true;
//             }
//             current_column = 0;
//             current_line += 1;

//         }

//         //  --- Advance in the file --- 
//         current_char = (char)file_flux.get();
//         current_column += 1;
//         if ((int)current_char == -1) {
//             // Assure that the end of the file is treated as a line break
//             current_char = '\n';
//         }

//         // --- --- Header --- ---
//         if (in_header){
//             header += current_char;

//         // --- --- Sequence --- ---
//         } else if (in_sequence) {
//             // Being inside a comment
//             if (in_comment) {
//                 if (current_char == '\n') {
//                     // We are leaving this comment
//                     in_comment = false;

//                     // Save the comment
//                     if (comments.count(sequence.length()) >= 1){
//                         comments[sequence.length()] += current_comment;

//                     } else {
//                         comments[sequence.length()] = current_comment;
//                     }
                    
//                     // clear <current_comment>
//                     current_comment.clear();
        
//                 } else {
//                     current_comment += current_char;
//                 }
            
//             // Entering inside a comment
//             } else if (isCommentChar(current_char)) {
//                 in_comment = true;
            
//             // Normal sequence behaviour
//             } else if (isBlankChar(current_char)) {
//                 // pass

//             } else if (FastaSequence::isLegalSymbol(current_char)) {
//                 sequence += current_char;

//             } else if (verbose) {
//                 // This errors aren't store since they wont be used latter in this project.
//                 std::cout << "None invisible symbol ignored at ln " << current_line << " col " << current_column << " : '"
//                           << (char)current_char << "' (" << (int)current_char << ")." <<  std::endl;
//             }
            

//         } else {
//             // If this isn't a sequence nor a header, we have nothing to do.
//         }
    
//         // --- Update <last_char> --- 
//         last_char = current_char;
//     }

//     /* 
//     // DEBUG block : Display result
//     std::cout << header << std::endl;
//     std::cout << sequence << std::endl;
//     for(const auto& elem : comments) {std::cout << elem.first << " " << elem.second << "\n";}
//     */

//     return std::tuple<std::string, std::string, std::map<size_t, std::string>> {
//                       header,      sequence,    comments};
     

// }

// std::vector<Fasta> Fasta::loadFastaFromFile(std::string path) {
//     return loadFastaFromFile(path, false);
// }

// std::vector<Fasta> Fasta::loadFastaFromFile(std::string path, bool verbose) {
//     std::ifstream file_flux(path);
//     unsigned int file_line = 0;
//     std::tuple<std::string, std::string, std::map<size_t, std::string>> result_tup;
//     std::vector<Fasta> all_fasta;

//     while (file_flux) {
//         result_tup = parseFasta(file_flux, file_line, verbose);
//         FastaSequence c_seq(
//             std::get<1>(result_tup),
//             verbose
//         );
//         c_seq.loadComments(std::get<2>(result_tup));

//         FastaHeader header = FastaHeader(std::get<0>(result_tup));

//         all_fasta.insert(all_fasta.end(), Fasta(header, c_seq));
//     }
//     return all_fasta;

// }

// Fasta::Fasta(FastaHeader header, FastaSequence sequence) {
//     this->header = header;
//     this->sequence = sequence;
// }
// /*
// void Fasta::write(std::string path) {
//     return this->write(path, false, true);
// }

// void Fasta::write(std::string path, bool append, bool comments) {
//     return this->write(path, append, 10, 6, comments);
// }

// void Fasta::write(std::string path, unsigned int word_size, unsigned int paragraph_size) {
//     return this->write(path, word_size, paragraph_size, true);
// }

// void Fasta::write(std::string path, unsigned int word_size, unsigned int paragraph_size, bool comments) {
//     return this->write(path, false, word_size, paragraph_size, comments);
// }
// */

// void Fasta::write(std::string path, bool append=false, unsigned int word_size=10, unsigned int paragraph_size=6, bool comments=true) {
//     std::ofstream file_flux;
//     if (append) {
//         file_flux.open(path, std::ios_base::app);
//     } else {
//         file_flux.open(path, std::ios_base::trunc);
//     }
//     file_flux << this->getCleanSequence(word_size, paragraph_size, comments);
//     file_flux.close();
// }

// void Fasta::write(std::vector<Fasta> fasta_vector, std::string path, unsigned int word_size, unsigned int paragraph_size, bool comments) {
//     bool first = true;
//     for(Fasta& fasta : fasta_vector) {
//         if (first) {
//             first = false;
//             fasta.write(path, false, word_size, paragraph_size, comments);
//         } else {
//             fasta.write(path, true, word_size, paragraph_size, comments);
//         }
//     }
// }


// std::string Fasta::getCleanSequence(unsigned int word_size, unsigned int paragraph_size, bool comments) {
//     std::string result = "";
//     FastaSequence& seqOBJ = this->getSequence();
//     std::string seq = seqOBJ.getSeq();
 
//     unsigned int current_paragraph_size = 0;
//     unsigned int current_word_size = 0;

//     size_t pos = 0;
//     for (char c : seq) {
//         result += c;
//         pos += 1;

//         current_word_size += 1;

//         if (comments || seqOBJ.isCommentedPos(pos)) {
//             result += " ;" + seqOBJ.getComment(pos) + '\n';
//             current_paragraph_size = 0;
//             current_word_size = 0;
//         }

//         else if (current_word_size >= word_size) {
//             if (word_size > 0) {
//                 // When word_size == 0, a word have the same size as a paragraph
//                 result += ' ';
//             }
//             current_word_size = 0;

//             current_paragraph_size += 1;

//             if (current_paragraph_size >= paragraph_size) {

//                 if (paragraph_size > 0) {
//                     result += '\n';
//                 }
//                 current_paragraph_size = 0;

//             }
//         }


//     }
//     return result;
// }
