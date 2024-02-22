#include "FastaSequence.hpp"
#include <string>
#include <map>

void FastaSequence::addComment(size_t position, std::string comment) {
    if (position > this->size()) {
        return ;
    }
    
    size_t lineB_pos = comment.find('\n');
    if (lineB_pos < comment.length()) {
        throw std::invalid_argument("Comments are not allowed to contain \\n");
    }

    if (this->isCommentedPos(position)){
        this->comments[position] += comment;

    } else {
        this->comments[position] = comment;
    }
}

void FastaSequence::loadComments(std::map<size_t, std::string>& comment_map) {
     for(const auto& elem : comment_map) {
        std::cout << "COM:" << elem.first << " " << elem.second << std::endl;
        this->addComment(elem.first, elem.second);
     }
}


void FastaSequence::removeComment(size_t position) {
    if (this->isCommentedPos(position)){
        this->comments.erase(position);
 
    } 
}

std::string FastaSequence::getComment(size_t position) {
    if (this->isCommentedPos(position)){
        return this->comments[position];
    } 
    return "";
}

bool FastaSequence::isCommentedPos(size_t position) {
    return (this->comments.count(position) >= 1);
}
