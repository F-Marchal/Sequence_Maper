#include "FastaHeader.hpp"
#include <string>
#include <map>
#include <tuple>
#include <vector>
// Header can not have " " inside theirs pipes 

void FastaHeader::clear_string(std::string& text) {
    size_t i = 0;
    while (i < text.size() && (isHeaderChar(text[i]) || isBlankChar(text[i]))){
        i += 1;
    }

    if (i != 0) {
        text.erase(0, i);
    }
}

 std::string FastaHeader::find_format(std::string text) {
    size_t i = 0;
    std::vector<std::string> text_subparts;
    std::string current_part = "";
    std::string format;

    clear_string(text);
    for (char symbols : text) {
        if (symbols == '|') {
            text_subparts.push_back(current_part);
            current_part = "";
        }
    }
    text_subparts.push_back(current_part);
    i += 1;

    size_t pipe_number = text_subparts.size() - 1;
    if (text_subparts[-1][-1] == '|') {
        pipe_number += 1;
    }

    if (pipe_number == 0) {
        format = "FIRST WORD";
    } else {
        format = text_subparts[0];

        if 
    }

    





 }
